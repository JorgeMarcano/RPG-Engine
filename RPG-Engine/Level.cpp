#include "Level.h"

using namespace tinyxml2;

void Level::LoadMap()
{
	//Parsing the TMX file
	XMLDocument doc;

	std::stringstream ss;
	ss << "content/map/" << _lvlName << ".tmx";

	doc.LoadFile(ss.str().c_str());

	XMLElement* mapNode = doc.FirstChildElement("map");

	mapNode->QueryIntAttribute("width", &_width);
	mapNode->QueryIntAttribute("height", &_height);

	mapNode->QueryIntAttribute("tilewidth", &_tileWidth);
	mapNode->QueryIntAttribute("tileheight", &_tileHeight);

	std::map<int, Animation> animations;
	Animation* tempAnim;
	Frame* frame;
	int tempID;

	//Loading the tilesets
	XMLElement* tilesetNode = mapNode->FirstChildElement("tileset");
	XMLElement* imageNode;
	XMLElement* animationNode;
	XMLElement* frameNode;
	Tileset* set;
	int gid;
	int tsH;
	int tsW;
	while (tilesetNode)
	{
		set = new Tileset();

		imageNode = tilesetNode->FirstChildElement("image");

		std::stringstream ss;
		ss << "content/tilesets/" << imageNode->Attribute("source");

		tilesetNode->QueryIntAttribute("firstgid", &(set->firstGid));
		tilesetNode->QueryIntAttribute("tilecount", &(set->tileCount));
		set->texture = _graphics->LoadTextureFromPNG(ss.str().c_str());

		_tileSets.push_back(*set);

		//look for animated tiles
		animationNode = tilesetNode->FirstChildElement("tile");
		while (animationNode)
		{
			animationNode->QueryIntAttribute("id", &tempID);

			tempAnim = new Animation; 
			std::vector<Frame> frames;

			frameNode = animationNode->FirstChildElement("animation")->FirstChildElement("frame");
			while (frameNode)
			{
				frame = new Frame;
				frameNode->QueryIntAttribute("duration", &(frame->timeToUpdate));
				frame->dstRect.h = _tileHeight;
				frame->dstRect.w = _tileWidth;

				frameNode->QueryIntAttribute("tileid", &gid);

				SDL_QueryTexture(set->texture, NULL, NULL, &tsW, &tsH);

				frame->dstRect.x = gid % (tsW / _tileWidth);
				frame->dstRect.y = gid * _tileWidth / tsW;

				frames.push_back(*frame);
				frameNode = frameNode->NextSiblingElement("frame");
			}

			tempAnim->frames = frames;
			tempAnim->frameCount = frames.size();
			tempAnim->name = std::string(animationNode->Attribute("id"));

			animations[tempID] = *tempAnim;

			animationNode = animationNode->NextSiblingElement("tile");
		}

		tilesetNode = tilesetNode->NextSiblingElement("tileset");
	}

	//Loading layers
	XMLElement* layersNode = mapNode->FirstChildElement("layer");
	XMLElement* dataNode;
	XMLElement* tileNode;
	Layer* layer;
	int tileCount = 0;
	Tileset tls;
	int xPos;
	int yPos;
	int xts;
	int yts;
	Tile* tempTile;
	TileStruct* tileStruct;
	while (layersNode)
	{
		//check to see if it is a collision layer
		if (layersNode->Attribute("name") != NULL)
		{
			std::stringstream ss;
			ss << layersNode->Attribute("name");
			if (ss.str()._Equal("collision"))
			{
				//parse but save in collision instead;
				dataNode = layersNode->FirstChildElement("data");
				while (dataNode)
				{
					tileNode = dataNode->FirstChildElement("tile");
					tileCount = 0;
					while (tileNode)
					{
						//if gid is 0, do not consider

						if (tileNode->QueryIntAttribute("gid", &gid) == XML_SUCCESS && gid != 0) {

							tileStruct = new TileStruct;
							tileStruct->x = tileCount % _width;
							tileStruct->y = yPos = tileCount / _width;

							_collisionList.push_back(*tileStruct);
						}

						tileCount++;

						tileNode = tileNode->NextSiblingElement("tile");
					}

					dataNode = dataNode->NextSiblingElement("data");
				}

				layersNode = layersNode->NextSiblingElement("layer");
				continue;
			}
		}

		//save as a layer to render
		layer = new Layer();

		layersNode->QueryIntAttribute("height", &(layer->height));
		layersNode->QueryIntAttribute("width", &(layer->width));

		dataNode = layersNode->FirstChildElement("data");
		while (dataNode)
		{
			tileNode = dataNode->FirstChildElement("tile");
			tileCount = 0;
			while (tileNode)
			{
				//if gid is 0, do not draw
				if (tileNode->QueryIntAttribute("gid", &gid) == XML_SUCCESS && gid != 0) {
					//get tileset
					for (int i = 0; i < _tileSets.size(); i++)
					{
						if (gid >= _tileSets[i].firstGid && gid <= _tileSets[i].firstGid + _tileSets[i].tileCount)
						{
							tls = _tileSets.at(i);
							break;
						}
					}

					xPos = tileCount % _width;
					yPos = tileCount / _width;

					SDL_QueryTexture(tls.texture, NULL, NULL, &tsW, &tsH);

					gid -= tls.firstGid;

					xts = gid % (tsW / _tileWidth);
					yts = gid * _tileWidth / tsW;

					if (animations.count(gid) != 0)
					{
						tempTile = new AnimatedTile(tls.texture, _graphics, _tileWidth, _tileWidth, xts, yts, xPos, yPos);
						((AnimatedTile*)tempTile)->AddAnimation(animations.at(gid));
						((AnimatedTile*)tempTile)->StartAnimation(animations.at(gid).name);
					}
					else
						tempTile = new Tile(tls.texture, _graphics, _tileWidth, _tileWidth, xts, yts, xPos, yPos);
					
					layer->tileList.push_back(tempTile);
				}

				tileCount++;

				tileNode = tileNode->NextSiblingElement("tile");
			}

			dataNode = dataNode->NextSiblingElement("data");
		}

		_layers.push_back(*layer);

		layersNode = layersNode->NextSiblingElement("layer");
	}

	XMLElement* exitObjGrpNode = mapNode->FirstChildElement("objectgroup");
	std::string name;
	Exit* tempExit;
	if (exitObjGrpNode)
	{
		XMLElement* exitObjNode = exitObjGrpNode->FirstChildElement("object");
		while (exitObjNode)
		{
			tempExit = new Exit;

			std::stringstream ss;
			ss << exitObjNode->Attribute("name");

			//get the map name
			std::getline(ss, tempExit->mapName, ',');
			//get spawnX
			std::getline(ss, name, ',');
			tempExit->spawnX = std::stoi(name);
			//get spawnY
			std::getline(ss, name, ',');
			tempExit->spawnY = std::stoi(name);

			_exitInfos.push_back(*tempExit);

			tileStruct = new TileStruct;
			exitObjNode->QueryIntAttribute("x", &xPos);
			exitObjNode->QueryIntAttribute("y", &yPos);
			tileStruct->x = (int)(xPos / _tileWidth);
			tileStruct->y = (int)(yPos / _tileHeight);

			_exitTiles.push_back(*tileStruct);

			exitObjNode = exitObjNode->NextSiblingElement("object");
		}
	}
}

Level::Level()
{
}

Level::Level(std::string lvlName, float playerX, float playerY, Graphics* graph, Input* input, int screenW, int screenH)
{
	_lvlName = lvlName;
	_spawnX = playerX;
	_spawnY = playerY;
	_graphics = graph;
	_input = input;

	_width = 0;
	_height = 0;

	_screenH = screenH;
	_screenW = screenW;

	LoadMap();

	_player = new Player(_graphics, _spawnX, _spawnY, _input, _tileWidth, _tileHeight, _screenW, _screenH);
}

Level::~Level()
{
}

void Level::Update(Uint32 dt)
{
	_player->Update(dt, _collisionList);

	TileStruct offset;
	_player->CalcOffset(&offset);

	for (int i = 0; i < _layers.size(); i++)
	{
		for (int j = 0; j < _layers[i].tileList.size(); j++)
		{
			_layers[i].tileList[j]->Update(dt, offset);
		}
	}
}

void Level::Draw()
{

	//3 layers, floor (at 0), botObj (at 1) and topObj (at 2)
	//player is drawn between botObj and topObj

	//draw floor

	for (int j = 0; j < _layers[0].tileList.size(); j++)
	{
		_layers[0].tileList[j]->Draw();
	}

	//draw botObj
	if (_layers.size() >= 2)
	{
		for (int j = 0; j < _layers[1].tileList.size(); j++)
		{
			_layers[1].tileList[j]->Draw();
		}
	}

	//draw player
	_player->Draw();


	//draw topObj
	if (_layers.size() < 3)
		return;

	for (int j = 0; j < _layers[2].tileList.size(); j++)
	{
		_layers[2].tileList[j]->Draw();
	}
}

Level* Level::checkExits(Uint32 dt)
{
	Level* returnLvl = NULL;

	int indx = -1;

	if (_player->IsColliding(dt, _exitTiles, &indx)) {
		//load info for new level
		returnLvl = new Level(_exitInfos[indx].mapName, _exitInfos[indx].spawnX, _exitInfos[indx].spawnY,
			_graphics, _input, _screenW, _screenH);
	}

	return returnLvl;
}
