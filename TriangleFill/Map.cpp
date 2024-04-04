#include <time.h>
#include "Map.h"
#include "Artist.h"
#include "Controller.h"

struct triangle {
	Artist::pos a;
	Artist::pos b;
	Artist::pos c;
};

std::vector<triangle> mapObjects;
int selectedObjectID = -1;
int selectedPointID = 0;

Artist::RGB tempTileColor = { 0, 255, 0 };

//try drawing them all and changing color per pixel 
//and also try running though it and oly drawing each type so you only change color once

void Map::loadMap()
{
	srand(clock());

	triangle tri = { { rand() % 1920, rand() % 1080 }, { rand() % 1920, rand() % 1080 }, { rand() % 1920, rand() % 1080 } };
	mapObjects.push_back(tri);

	triangle tri2 = { { rand() % 1920, rand() % 1080 }, { rand() % 1920, rand() % 1080 }, { rand() % 1920, rand() % 1080 } };
	mapObjects.push_back(tri2);


	
}

void drawMap()
{
	Artist artist;

	for (int i = 0; i < mapObjects.size(); i++)
	{
		artist.drawTriangle(mapObjects[i].a.x, mapObjects[i].a.y, mapObjects[i].b.x, mapObjects[i].b.y, mapObjects[i].c.x, mapObjects[i].c.y);
	}

	//draw selected point
	if (selectedObjectID >= 0)
	{
		Artist::pos* selectedPointPos = &mapObjects[selectedObjectID].a;
		switch (selectedPointID)
		{
		case 0:
			selectedPointPos = &mapObjects[selectedObjectID].a;
			break;
		case 1:
			selectedPointPos = &mapObjects[selectedObjectID].b;
			break;
		case 2:
			selectedPointPos = &mapObjects[selectedObjectID].c;
			break;
		}


		artist.changeRenderColor(0, 255, 0);
		artist.drawRectangle(selectedPointPos->x - 5, selectedPointPos->y - 5, 10, 10);
		artist.changeRenderColor(0, 0, 0);
	}
}

void Map::draw()
{
	

	drawMap();

	

	
}

void dragTriangles()
{
	if (Controller::mouseStates[0] == 1)
	{
		for (int i = 0; mapObjects.size() > i; i++)
		{
			if (Controller::mouseX + 5 > mapObjects[i].a.x && Controller::mouseX - 5 < mapObjects[i].a.x && Controller::mouseY + 5 > mapObjects[i].a.y && Controller::mouseY - 5 < mapObjects[i].a.y)
			{
				selectedObjectID = i;
				selectedPointID = 0;
				printf("selected A \n");
			}
			if (Controller::mouseX + 5 > mapObjects[i].b.x && Controller::mouseX - 5 < mapObjects[i].b.x && Controller::mouseY + 5 > mapObjects[i].b.y && Controller::mouseY - 5 < mapObjects[i].b.y)
			{
				selectedObjectID = i;
				selectedPointID = 1;
				printf("selected B \n");
			}
			if (Controller::mouseX + 5 > mapObjects[i].c.x && Controller::mouseX - 5 < mapObjects[i].c.x && Controller::mouseY + 5 > mapObjects[i].c.y && Controller::mouseY - 5 < mapObjects[i].c.y)
			{
				selectedObjectID = i;
				selectedPointID = 2;
				printf("selected C \n");
			}
		}
	}
	if (Controller::mouseStates[0] == 3)
	{
		selectedObjectID = -1;
	}
	if (Controller::mouseMoved && selectedObjectID >= 0)
	{
		Artist::pos* selectedPoint = &mapObjects[selectedObjectID].a;
		switch (selectedPointID)
		{
		case 0:
			selectedPoint = &mapObjects[selectedObjectID].a;
			break;
		case 1:
			selectedPoint = &mapObjects[selectedObjectID].b;
			break;
		case 2:
			selectedPoint = &mapObjects[selectedObjectID].c;
			break;
		}

		selectedPoint->x = Controller::mouseX;
		selectedPoint->y = Controller::mouseY;
	}
	
}

void Map::controller()
{
	dragTriangles();
}