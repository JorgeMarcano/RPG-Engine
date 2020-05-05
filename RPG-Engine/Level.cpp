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

	//Loading the tilesets
	XMLElement* tilesetNode = mapNode->FirstChildElement("tileset");
	XMLElement* imageNode;
	Tileset* set;
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

		tilesetNode = tilesetNode->NextSiblingElement("tileset");
	}

	//Loading layers
	XMLElement* layersNode = mapNode->FirstChildElement("layer");
	XMLElement* dataNode;
	XMLElement* tileNode;
	Layer* layer;
	int tileCount = 0;
	int gid;
	Tileset tls;
	int xPos;
	int yPos;
	int xts;
	int yts;
	int tsH;
	int tsW;
	while (layersNode)
	{
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

					layer->tileList.push_back(Tile(tls.texture, _graphics, _tileWidth, _tileWidth, xts, yts, xPos, yPos));
				}

				tileCount++;

				tileNode = tileNode->NextSiblingElement("tile");
			}

			dataNode = dataNode->NextSiblingElement("data");
		}

		_layers.push_back(*layer);

		layersNode = layersNode->NextSiblingElement("layer");
	}
}

Level::Level()
{
}

Level::Level(std::string lvlName, float playerX, float playerY, Graphics* graph, Input* input)
{
	_lvlName = lvlName;
	_spawnX = playerX;
	_spawnY = playerY;
	_graphics = graph;
	_input = input;

	_width = 0;
	_height = 0;

	LoadMap();
}

Level::~Level()
{
}

void Level::Update(Uint32 dt)
{
	Layer currLayer;
	for (int i = 0; i < _layers.size(); i++)
	{
		currLayer = _layers[i];
		for (int j = 0; j < currLayer.tileList.size(); j++)
		{
			currLayer.tileList[j].Update(dt);
		}
	}
}

void Level::Draw()
{
	//_graphics->DrawBlitOnWin(_bgTexture, NULL, NULL);

	for (int i = 0; i < _layers.size(); i++)
	{
		for (int j = 0; j < _layers[i].tileList.size(); j++)
		{
			_layers[i].tileList[j].Draw();
		}
	}
}
