#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <time.h>
#include "Artist.h"
#include "Map.h"
#include "FPSCounter.h"



//Screen dimension constants    Windowed 1440x1080 or 720x540   Fullscreen 1920x1080  
int Artist::SCREEN_WIDTH = 1920;
int Artist::SCREEN_HEIGHT = 1080;
float Artist::SCREEN_SCALE = 2;
bool Artist::FULLSCREEN = true;
bool Artist::drawMenus = true;
bool Artist::displayFPS = true;




//The window we'll be rendering to
SDL_Window* Artist::gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;






//Initialize textures in the header

//std::vector<SDL_Texture*> Artist::gLvl4ClassIconBorderAnimation;

//letters

Artist::fontTextureSet Artist::largeFont;
Artist::fontTextureSet Artist::smallFont;




//Update screen
void Artist::updateScreen()
{
	SDL_RenderPresent(gRenderer);
}

//Clear screen
void Artist::clearScreen()
{
	SDL_RenderClear(gRenderer);
}

SDL_Texture* Artist::loadTexture(std::string path)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}



bool Artist::init()
{

	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear. NOT!!
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("Caliber", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Artist::SCREEN_WIDTH, Artist::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		Artist artist;
		SDL_Surface* icon = IMG_Load("Resource/icon.png");
		SDL_SetWindowIcon(gWindow, icon);
		SDL_FreeSurface(icon);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);
				SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

void loadFontTextures(Artist::fontTextureSet* fontToLoad, std::string fontName)
{
	Artist artist;
	fontToLoad->LowerA = artist.loadTexture("Resource/fonts/" + fontName + "/a.png");
	fontToLoad->LowerB = artist.loadTexture("Resource/fonts/" + fontName + "/b.png");
	fontToLoad->LowerC = artist.loadTexture("Resource/fonts/" + fontName + "/c.png");
	fontToLoad->LowerD = artist.loadTexture("Resource/fonts/" + fontName + "/d.png");
	fontToLoad->LowerE = artist.loadTexture("Resource/fonts/" + fontName + "/e.png");
	fontToLoad->LowerF = artist.loadTexture("Resource/fonts/" + fontName + "/f.png");
	fontToLoad->LowerG = artist.loadTexture("Resource/fonts/" + fontName + "/g.png");
	fontToLoad->LowerH = artist.loadTexture("Resource/fonts/" + fontName + "/h.png");
	fontToLoad->LowerI = artist.loadTexture("Resource/fonts/" + fontName + "/i.png");
	fontToLoad->LowerJ = artist.loadTexture("Resource/fonts/" + fontName + "/j.png");
	fontToLoad->LowerK = artist.loadTexture("Resource/fonts/" + fontName + "/k.png");
	fontToLoad->LowerL = artist.loadTexture("Resource/fonts/" + fontName + "/l.png");
	fontToLoad->LowerM = artist.loadTexture("Resource/fonts/" + fontName + "/m.png");
	fontToLoad->LowerN = artist.loadTexture("Resource/fonts/" + fontName + "/n.png");
	fontToLoad->LowerO = artist.loadTexture("Resource/fonts/" + fontName + "/o.png");
	fontToLoad->LowerP = artist.loadTexture("Resource/fonts/" + fontName + "/p.png");
	fontToLoad->LowerQ = artist.loadTexture("Resource/fonts/" + fontName + "/q.png");
	fontToLoad->LowerR = artist.loadTexture("Resource/fonts/" + fontName + "/r.png");
	fontToLoad->LowerS = artist.loadTexture("Resource/fonts/" + fontName + "/s.png");
	fontToLoad->LowerT = artist.loadTexture("Resource/fonts/" + fontName + "/t.png");
	fontToLoad->LowerU = artist.loadTexture("Resource/fonts/" + fontName + "/u.png");
	fontToLoad->LowerV = artist.loadTexture("Resource/fonts/" + fontName + "/v.png");
	fontToLoad->LowerW = artist.loadTexture("Resource/fonts/" + fontName + "/w.png");
	fontToLoad->LowerX = artist.loadTexture("Resource/fonts/" + fontName + "/x.png");
	fontToLoad->LowerY = artist.loadTexture("Resource/fonts/" + fontName + "/y.png");
	fontToLoad->LowerZ = artist.loadTexture("Resource/fonts/" + fontName + "/z.png");
	fontToLoad->CapA = artist.loadTexture("Resource/fonts/" + fontName + "/capA.png");
	fontToLoad->CapB = artist.loadTexture("Resource/fonts/" + fontName + "/capB.png");
	fontToLoad->CapC = artist.loadTexture("Resource/fonts/" + fontName + "/capC.png");
	fontToLoad->CapD = artist.loadTexture("Resource/fonts/" + fontName + "/capD.png");
	fontToLoad->CapE = artist.loadTexture("Resource/fonts/" + fontName + "/capE.png");
	fontToLoad->CapF = artist.loadTexture("Resource/fonts/" + fontName + "/capF.png");
	fontToLoad->CapG = artist.loadTexture("Resource/fonts/" + fontName + "/capG.png");
	fontToLoad->CapH = artist.loadTexture("Resource/fonts/" + fontName + "/capH.png");
	fontToLoad->CapI = artist.loadTexture("Resource/fonts/" + fontName + "/capI.png");
	fontToLoad->CapJ = artist.loadTexture("Resource/fonts/" + fontName + "/capJ.png");
	fontToLoad->CapK = artist.loadTexture("Resource/fonts/" + fontName + "/capK.png");
	fontToLoad->CapL = artist.loadTexture("Resource/fonts/" + fontName + "/capL.png");
	fontToLoad->CapM = artist.loadTexture("Resource/fonts/" + fontName + "/capM.png");
	fontToLoad->CapN = artist.loadTexture("Resource/fonts/" + fontName + "/capN.png");
	fontToLoad->CapO = artist.loadTexture("Resource/fonts/" + fontName + "/capO.png");
	fontToLoad->CapP = artist.loadTexture("Resource/fonts/" + fontName + "/capP.png");
	fontToLoad->CapQ = artist.loadTexture("Resource/fonts/" + fontName + "/capQ.png");
	fontToLoad->CapR = artist.loadTexture("Resource/fonts/" + fontName + "/capR.png");
	fontToLoad->CapS = artist.loadTexture("Resource/fonts/" + fontName + "/capS.png");
	fontToLoad->CapT = artist.loadTexture("Resource/fonts/" + fontName + "/capT.png");
	fontToLoad->CapU = artist.loadTexture("Resource/fonts/" + fontName + "/capU.png");
	fontToLoad->CapV = artist.loadTexture("Resource/fonts/" + fontName + "/capV.png");
	fontToLoad->CapW = artist.loadTexture("Resource/fonts/" + fontName + "/capW.png");
	fontToLoad->CapX = artist.loadTexture("Resource/fonts/" + fontName + "/capX.png");
	fontToLoad->CapY = artist.loadTexture("Resource/fonts/" + fontName + "/capY.png");
	fontToLoad->CapZ = artist.loadTexture("Resource/fonts/" + fontName + "/capZ.png");
	fontToLoad->num1 = artist.loadTexture("Resource/fonts/" + fontName + "/1.png");
	fontToLoad->num2 = artist.loadTexture("Resource/fonts/" + fontName + "/2.png");
	fontToLoad->num3 = artist.loadTexture("Resource/fonts/" + fontName + "/3.png");
	fontToLoad->num4 = artist.loadTexture("Resource/fonts/" + fontName + "/4.png");
	fontToLoad->num5 = artist.loadTexture("Resource/fonts/" + fontName + "/5.png");
	fontToLoad->num6 = artist.loadTexture("Resource/fonts/" + fontName + "/6.png");
	fontToLoad->num7 = artist.loadTexture("Resource/fonts/" + fontName + "/7.png");
	fontToLoad->num8 = artist.loadTexture("Resource/fonts/" + fontName + "/8.png");
	fontToLoad->num9 = artist.loadTexture("Resource/fonts/" + fontName + "/9.png");
	fontToLoad->num0 = artist.loadTexture("Resource/fonts/" + fontName + "/0.png");
	fontToLoad->Pound = artist.loadTexture("Resource/fonts/" + fontName + "/#.png");
	fontToLoad->$ = artist.loadTexture("Resource/fonts/" + fontName + "/$.png");
	fontToLoad->Percent = artist.loadTexture("Resource/fonts/" + fontName + "/%.png");
	fontToLoad->Ampersand = artist.loadTexture("Resource/fonts/" + fontName + "/&.png");
	fontToLoad->LeftParentheses = artist.loadTexture("Resource/fonts/" + fontName + "/(.png");
	fontToLoad->RightParentheses = artist.loadTexture("Resource/fonts/" + fontName + "/).png");
	fontToLoad->Comma = artist.loadTexture("Resource/fonts/" + fontName + "/,.png");
	fontToLoad->Apostrophe = artist.loadTexture("Resource/fonts/" + fontName + "/'.png");
	fontToLoad->Minus = artist.loadTexture("Resource/fonts/" + fontName + "/-.png");
	fontToLoad->SemiColon = artist.loadTexture("Resource/fonts/" + fontName + "/;.png");
	fontToLoad->Colon = artist.loadTexture("Resource/fonts/" + fontName + "/colon.png");
	fontToLoad->At = artist.loadTexture("Resource/fonts/" + fontName + "/@.png");
	fontToLoad->LeftBracket = artist.loadTexture("Resource/fonts/" + fontName + "/[.png");
	fontToLoad->RightBracket = artist.loadTexture("Resource/fonts/" + fontName + "/].png");
	fontToLoad->Caret = artist.loadTexture("Resource/fonts/" + fontName + "/^.png");
	fontToLoad->UnderScore = artist.loadTexture("Resource/fonts/" + fontName + "/_.png");
	fontToLoad->Tilde = artist.loadTexture("Resource/fonts/" + fontName + "/~.png");
	fontToLoad->Acute = artist.loadTexture("Resource/fonts/" + fontName + "/`.png");
	fontToLoad->LeftBrace = artist.loadTexture("Resource/fonts/" + fontName + "/{.png");
	fontToLoad->RightBrace = artist.loadTexture("Resource/fonts/" + fontName + "/}.png");
	fontToLoad->Plus = artist.loadTexture("Resource/fonts/" + fontName + "/+.png");
	fontToLoad->Equals = artist.loadTexture("Resource/fonts/" + fontName + "/=.png");
	fontToLoad->Asterisk = artist.loadTexture("Resource/fonts/" + fontName + "/asterisk.png");
	fontToLoad->BackSlash = artist.loadTexture("Resource/fonts/" + fontName + "/backSlash.png");
	fontToLoad->ForwardSlash = artist.loadTexture("Resource/fonts/" + fontName + "/forwardSlash.png");
	fontToLoad->ExclamationMark = artist.loadTexture("Resource/fonts/" + fontName + "/exclamationMark.png");
	fontToLoad->QuestionMark = artist.loadTexture("Resource/fonts/" + fontName + "/questionMark.png");
	fontToLoad->GreaterThan = artist.loadTexture("Resource/fonts/" + fontName + "/greaterThan.png");
	fontToLoad->LessThan = artist.loadTexture("Resource/fonts/" + fontName + "/lessThan.png");
	fontToLoad->Period = artist.loadTexture("Resource/fonts/" + fontName + "/period.png");
	fontToLoad->QuotationMark = artist.loadTexture("Resource/fonts/" + fontName + "/quotationMark.png");
	fontToLoad->VerticalBar = artist.loadTexture("Resource/fonts/" + fontName + "/verticalBar.png");
}

std::vector<SDL_Texture*> loadAnimationData(std::string textureFolderLocation, std::string textureSetName, int textureAmount)
{
	Artist artist;

	std::vector<SDL_Texture*> tempTexSet;
	for (int i = 1; i <= textureAmount; i++)
	{
		tempTexSet.push_back(artist.loadTexture("Resource/" + textureFolderLocation + "/" + textureSetName + "/" + textureSetName + std::to_string(i) + ".png"));
	}
	return tempTexSet;
}

bool Artist::loadMedia()
{
	Artist artist;
	//Loading success flag
	bool success = true;


	//Load texture
	


	//Artist::gLvl4ClassIconBorderAnimation = loadAnimationData("classes", "lvl4IconBorder", 66);

	//letters
	loadFontTextures(&Artist::largeFont, "large");
	loadFontTextures(&Artist::smallFont, "small");


	return success;
}

void Artist::close()
{
	//Free loaded image
	//SDL_DestroyTexture(gBackground);
	//gBackground = NULL;






	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}



void Artist::changeRenderColor(int r, int g, int b, int alpha)
{
	
	SDL_SetRenderDrawColor(gRenderer, r, g, b, alpha);
}

void Artist::drawPoint(int x, int y, Artist::RGB color)
{
	SDL_SetRenderDrawColor(gRenderer, color.r, color.g, color.b, 255);

	SDL_RenderDrawPoint(gRenderer, x, y);
	
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
}

void Artist::drawLineFromPoints(int sX, int sY, int eX, int eY)
{
	//SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 0xFF);
	SDL_RenderDrawLine(gRenderer, sX, sY, eX, eY);
}

void Artist::drawLinesFromPoints(std::vector <Artist::pos> pointList)
{
	SDL_Point vertList[3000];

	for (int i = 0; i < pointList.size(); i++)
	{
		vertList[i].x = pointList[i].x;
		vertList[i].y = pointList[i].y;
	}
	//close of shape by adding start to the end
	if (pointList.size() > 1)
	{
		vertList[pointList.size()].x = pointList[0].x;
		vertList[pointList.size()].y = pointList[0].y;
	}

	SDL_RenderDrawLines(gRenderer, vertList, pointList.size() + 1);
}

bool lineCollision(Artist::pos A1, Artist::pos A2, Artist::pos B1, Artist::pos B2, float* out = 0)
{
	Artist::pos a = { A2.x - A1.x ,  A2.y - A1.y };
	Artist::pos b = { B2.x - B1.x ,  B2.y - B1.y };

	double f = (a.y * b.x) - (a.x * b.y);
	if (!f)      // lines are parallel
		return false;

	Artist::pos c = { B2.x - A2.x, B2.y - A2.y };
	double aa = (a.y * c.x) - (a.x * c.y);
	double bb = (b.y * c.x) - (b.x * c.y);

	if (f < 0)
	{
		if (aa > 0)     return false;
		if (bb > 0)     return false;
		if (aa < f)     return false;
		if (bb < f)     return false;
	}
	else
	{
		if (aa < 0)     return false;
		if (bb < 0)     return false;
		if (aa > f)     return false;
		if (bb > f)     return false;
	}

	if (out)
		* out = 1.0 - (aa / f);
	return true;
}

void Artist::drawTriangle(float aX, float aY, float bX, float bY, float cX, float cY, bool fill)
{
	std::vector<pos> fillPoints;
	if (fill)
	{
		float leftMostX = aX; // the x we are going to use to scan right from, should be the left most X then 1 more to the left, wont change
		if (leftMostX > bX)
		{
			leftMostX = bX;
		}
		if (leftMostX > cX)
		{
			leftMostX = cX;
		}
		leftMostX -= 1;

		float rightMostX = aX; // the x we are going to use to scan to, should be the right most X then 1 more to the right, wont change
		if (rightMostX < bX)
		{
			rightMostX = bX;
		}
		if (rightMostX < cX)
		{
			rightMostX = cX;
		}
		rightMostX += 1;

		float upMostY = aY; // the highest Y, used to find the hight of the triangle
		if (upMostY > bY)
		{
			upMostY = bY;
		}
		if (upMostY > cY)
		{
			upMostY = cY;
		}

		float downMostY = aY; // the lowset Y, used to find the hight of the triangle
		if (downMostY < bY)
		{
			downMostY = bY;
		}
		if (downMostY < cY)
		{
			downMostY = cY;
		}

		float endY = downMostY - 1; // the lowest we draw a line for filling
		float currentY = upMostY + 1; //set to the highest Y point of the 3. then 1 pixel down

		//make loop here
		while (currentY <= endY)
		{
			//get nodes from where we intersect
			//check line a->b first then b->c then c->a
			std::vector<pos> nodeList; // list of where we should start and stop drawing lines
			float nodeToConvert; // holds the raw data of where they intersect
			pos nodeToAdd; // the position where the lines interesct to be added to the node list

			if (lineCollision({ leftMostX, currentY }, { rightMostX, currentY }, { aX, aY }, { bX, bY }, &nodeToConvert))
			{
				nodeToAdd = { ((bX - aX) * nodeToConvert) + aX, ((bY - aY) * nodeToConvert) + aY };

				nodeList.push_back(nodeToAdd);
			}
			if (lineCollision({ leftMostX, currentY }, { rightMostX, currentY }, { bX, bY }, { cX, cY }, &nodeToConvert))
			{
				nodeToAdd = { ((cX - bX) * nodeToConvert) + bX, ((cY - bY) * nodeToConvert) + bY };

				nodeList.push_back(nodeToAdd);
			}
			if (lineCollision({ leftMostX, currentY }, { rightMostX, currentY }, { cX, cY }, { aX, aY }, &nodeToConvert))
			{
				nodeToAdd = { ((aX - cX) * nodeToConvert) + cX, ((aY - cY) * nodeToConvert) + cY };

				nodeList.push_back(nodeToAdd);
			}

			

			//add points to list to be drawn later
			pos addPos1 = { nodeList[0].x, currentY };
			fillPoints.push_back(addPos1);
			pos addPos2 = { nodeList[1].x, currentY };
			fillPoints.push_back(addPos2);


			nodeList.clear();
			currentY++;
		}

		//if (aY > bY && bY > cY)//bug when b on right side
		//{
		//	float bYIntercept = 0;
		//	lineCollision({ bX, bY }, { rightMostX, bY }, { cX, cY }, { aX, aY }, &bYIntercept);
		//	pos bYInterceptPos = { ((aX - cX) * bYIntercept) + cX, ((aY - cY) * bYIntercept) + cY };
		//	SDL_RenderDrawLine(gRenderer, bX, bY, bYInterceptPos.x, bY);
		//}
		changeRenderColor(0, 0, 255);
		if (aY < bY && bY < cY)
		{
			float bYIntercept = 0;
			lineCollision({ bX, bY }, { rightMostX, bY }, { cX, cY }, { aX, aY }, &bYIntercept);
			pos bYInterceptPos = { ((aX - cX) * bYIntercept) + cX, ((aY - cY) * bYIntercept) + cY };
			SDL_RenderDrawLine(gRenderer, bX, bY, bYInterceptPos.x, bY);
		}
		
	}
	//draw list of points to fill
	changeRenderColor(0, 0, 255);

	drawLinesFromPoints(fillPoints);

	//draw red outline
	changeRenderColor(255, 0, 0);

	SDL_Point points[4] = {
	{aX, aY},
	{bX, bY},
	{cX, cY},
	{aX, aY}
	};

	SDL_RenderDrawLines(gRenderer, points, 4);
	

	changeRenderColor(0, 0, 0);
}

void Artist::drawRectangle(int x, int y, int w, int h)
{
	SDL_Rect tempRect;
	tempRect.x = x;
	tempRect.y = y;
	tempRect.w = w;
	tempRect.h = h;
	SDL_RenderFillRect(gRenderer, &tempRect);
}

void Artist::drawImage(SDL_Texture * tex, int x, int y, int w, int h, double r, SDL_Point * center, SDL_RendererFlip flip, bool scaled)
{
	SDL_Rect img;
	img.x = x * Artist::SCREEN_SCALE;
	img.y = y * Artist::SCREEN_SCALE;
	int drawW, drawH;
	if (w < 1)
	{
		SDL_QueryTexture(tex, NULL, NULL, &drawW, NULL);
	}
	else
	{
		drawW = w;
	}
	if (h < 1)
	{
		SDL_QueryTexture(tex, NULL, NULL, NULL, &drawH);
	}
	else
	{
		drawH = h;
	}
	if (scaled)
		img.w = drawW * Artist::SCREEN_SCALE;
	else
		img.w = drawW;
	if (scaled)
		img.h = drawH * Artist::SCREEN_SCALE;
	else
		img.h = drawH;
	SDL_RenderCopyEx(gRenderer, tex, NULL, &img, r, center, flip);
}

void Artist::drawAnimation(std::vector < SDL_Texture*> texSet, int x, int y, int frameTime)
{
	int frameToDraw = clock() / frameTime % texSet.size();
	//printf("FrameTime: %i, DisplayedFrame: %i \n", clock(), frameToDraw);
	drawImage(texSet[frameToDraw], x, y);
}

void Artist::drawLetters(std::string string, int x, int y, Artist::fontTextureSet font)
{
	std::string letterS;
	SDL_Texture* letterT = NULL;
	int count = 0;
	int offset = 0;
	//std::cout << string << std::endl;
	while (count < string.length())
	{
		letterS = string[count];
		if (letterS == "a")
		{
			letterT = font.LowerA;
		}
		else if (letterS == "b")
		{
			letterT = font.LowerB;
		}
		else if (letterS == "c")
		{
			letterT = font.LowerC;
		}
		else if (letterS == "d")
		{
			letterT = font.LowerD;
		}
		else if (letterS == "e")
		{
			letterT = font.LowerE;
		}
		else if (letterS == "f")
		{
			letterT = font.LowerF;
		}
		else if (letterS == "g")
		{
			letterT = font.LowerG;
		}
		else if (letterS == "h")
		{
			letterT = font.LowerH;
		}
		else if (letterS == "i")
		{
			letterT = font.LowerI;
		}
		else if (letterS == "j")
		{
			letterT = font.LowerJ;
		}
		else if (letterS == "k")
		{
			letterT = font.LowerK;
		}
		else if (letterS == "l")
		{
			letterT = font.LowerL;
		}
		else if (letterS == "m")
		{
			letterT = font.LowerM;
		}
		else if (letterS == "n")
		{
			letterT = font.LowerN;
		}
		else if (letterS == "o")
		{
			letterT = font.LowerO;
		}
		else if (letterS == "p")
		{
			letterT = font.LowerP;
		}
		else if (letterS == "q")
		{
			letterT = font.LowerQ;
		}
		else if (letterS == "r")
		{
			letterT = font.LowerR;
		}
		else if (letterS == "s")
		{
			letterT = font.LowerS;
		}
		else if (letterS == "t")
		{
			letterT = font.LowerT;
		}
		else if (letterS == "u")
		{
			letterT = font.LowerU;
		}
		else if (letterS == "v")
		{
			letterT = font.LowerV;
		}
		else if (letterS == "w")
		{
			letterT = font.LowerW;
		}
		else if (letterS == "x")
		{
			letterT = font.LowerX;
		}
		else if (letterS == "y")
		{
			letterT = font.LowerY;
		}
		else if (letterS == "z")
		{
			letterT = font.LowerZ;
		}
		else if (letterS == "A")
		{
			letterT = font.CapA;
		}
		else if (letterS == "B")
		{
			letterT = font.CapB;
		}
		else if (letterS == "C")
		{
			letterT = font.CapC;
		}
		else if (letterS == "D")
		{
			letterT = font.CapD;
		}
		else if (letterS == "E")
		{
			letterT = font.CapE;
		}
		else if (letterS == "F")
		{
			letterT = font.CapF;
		}
		else if (letterS == "G")
		{
			letterT = font.CapG;
		}
		else if (letterS == "H")
		{
			letterT = font.CapH;
		}
		else if (letterS == "I")
		{
			letterT = font.CapI;
		}
		else if (letterS == "J")
		{
			letterT = font.CapJ;
		}
		else if (letterS == "K")
		{
			letterT = font.CapK;
		}
		else if (letterS == "L")
		{
			letterT = font.CapL;
		}
		else if (letterS == "M")
		{
			letterT = font.CapM;
		}
		else if (letterS == "N")
		{
			letterT = font.CapN;
		}
		else if (letterS == "O")
		{
			letterT = font.CapO;
		}
		else if (letterS == "P")
		{
			letterT = font.CapP;
		}
		else if (letterS == "Q")
		{
			letterT = font.CapQ;
		}
		else if (letterS == "R")
		{
			letterT = font.CapR;
		}
		else if (letterS == "S")
		{
			letterT = font.CapS;
		}
		else if (letterS == "T")
		{
			letterT = font.CapT;
		}
		else if (letterS == "U")
		{
			letterT = font.CapU;
		}
		else if (letterS == "V")
		{
			letterT = font.CapV;
		}
		else if (letterS == "W")
		{
			letterT = font.CapW;
		}
		else if (letterS == "X")
		{
			letterT = font.CapX;
		}
		else if (letterS == "Y")
		{
			letterT = font.CapY;
		}
		else if (letterS == "Z")
		{
			letterT = font.CapZ;
		}
		else if (letterS == " ")
		{
			letterT = NULL;
		}
		else if (letterS == "1")
		{
			letterT = font.num1;
		}
		else if (letterS == "2")
		{
			letterT = font.num2;
		}
		else if (letterS == "3")
		{
			letterT = font.num3;
		}
		else if (letterS == "4")
		{
			letterT = font.num4;
		}
		else if (letterS == "5")
		{
			letterT = font.num5;
		}
		else if (letterS == "6")
		{
			letterT = font.num6;
		}
		else if (letterS == "7")
		{
			letterT = font.num7;
		}
		else if (letterS == "8")
		{
			letterT = font.num8;
		}
		else if (letterS == "9")
		{
			letterT = font.num9;
		}
		else if (letterS == "0")
		{
			letterT = font.num0;
		}
		else if (letterS == "`")
		{
			letterT = font.Acute;
		}
		else if (letterS == "~")
		{
			letterT = font.Tilde;
		}
		else if (letterS == "!")
		{
			letterT = font.ExclamationMark;
		}
		else if (letterS == "?")
		{
			letterT = font.QuestionMark;
		}
		else if (letterS == "#")
		{
			letterT = font.Pound;
		}
		else if (letterS == "$")
		{
			letterT = font.$;
		}
		else if (letterS == "%")
		{
			letterT = font.Percent;
		}
		else if (letterS == "^")
		{
			letterT = font.Caret;
		}
		else if (letterS == "&")
		{
			letterT = font.Ampersand;
		}
		else if (letterS == "*")
		{
			letterT = font.Asterisk;
		}
		else if (letterS == "(")
		{
			letterT = font.LeftParentheses;
		}
		else if (letterS == ")")
		{
			letterT = font.RightParentheses;
		}
		else if (letterS == "-")
		{
			letterT = font.Minus;
		}
		else if (letterS == "_")
		{
			letterT = font.UnderScore;
		}
		else if (letterS == "=")
		{
			letterT = font.Equals;
		}
		else if (letterS == "+")
		{
			letterT = font.Plus;
		}
		else if (letterS == "[")
		{
			letterT = font.LeftBracket;
		}
		else if (letterS == "]")
		{
			letterT = font.RightBracket;
		}
		else if (letterS == "{")
		{
			letterT = font.LeftBrace;
		}
		else if (letterS == "}")
		{
			letterT = font.RightBrace;
		}
		else if (letterS == "\\")
		{
			letterT = font.BackSlash;
		}
		else if (letterS == "|")
		{
			letterT = font.VerticalBar;
		}
		else if (letterS == ";")
		{
			letterT = font.SemiColon;
		}
		else if (letterS == ":")
		{
			letterT = font.Colon;
		}
		else if (letterS == "'")
		{
			letterT = font.Apostrophe;
		}
		else if (letterS == "\"")
		{
			letterT = font.QuotationMark;
		}
		else if (letterS == ",")
		{
			letterT = font.Comma;
		}
		else if (letterS == "<")
		{
			letterT = font.LessThan;
		}
		else if (letterS == ".")
		{
			letterT = font.Period;
		}
		else if (letterS == ">")
		{
			letterT = font.GreaterThan;
		}
		else if (letterS == "/")
		{
			letterT = font.ForwardSlash;
		}
		else if (letterS == "@")
		{
			letterT = font.At;
		}
		else
		{
			letterT = font.QuestionMark;
		}
		int w, h;
		//Make it sized based on width but adding the count and TO the count each time
		SDL_QueryTexture(letterT, NULL, NULL, &w, &h);
		drawImage(letterT, offset + x, y, w, h);
		offset += w;
		//std::cout << count << std::endl;
		//std::cout << letterS << std::endl;
		count++;
	}


}














void Artist::draw()
{
	Artist artist;
	Map map;
	FPSCounter fpscounter;

	

	map.draw();

	

	

	if (Artist::displayFPS)
	{
		fpscounter.updateFPS();

		artist.drawLetters(std::to_string(fpscounter.getFPS()), 0, 1, Artist::largeFont);
	}
}
