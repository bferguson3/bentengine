#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

typedef unsigned char bool;
#define false 0
#define true 1
#define False false 
#define True true 
#define FALSE False 
#define TRUE True 
typedef unsigned char u8;
typedef signed char s8;
#define NULL ((void*)0)
#define null NULL 
#define Null NULL 
#define bit(n) (1<<n)

#define OPAQUE 0

#define DEBUG

#define BPP_16 16
#define BPP_32 32
#define TILESIZE 16
#define PIXELSCALE 2
// 720x360 - 1/2 720p
// 640x400 - 2x vga
// 420x240 - 1/3 720p
#define SCREEN_WIDTH 320*PIXELSCALE//720*PIXELSCALE
#define SCREEN_HEIGHT 200*PIXELSCALE//360*PIXELSCALE

#define FPS_120 ((float)(1000.0f / 120.0f))
#define FPS_90 ((float)(1000.0f / 90.0f))
#define FPS_70 ((float)(1000.0f / 70.0f))
#define FPS_60 ((float)(1000.0f / 60.0f))
#define FPS_30 ((float)(1000.0f / 30.0f))
#define FPS_15 ((float)(1000.0f / 15.0f))

#define JOY_UP bit(0)
#define JOY_DOWN bit(1)
#define JOY_LEFT bit(2)
#define JOY_RIGHT bit(3)
#define JOY_A bit(4)
#define JOY_B bit(5)

// structs 
typedef struct tile { 
	SDL_Surface* source;
} Tile;

Tile loadedTiles[256];

typedef struct sprite { 
	SDL_Surface* source;
	SDL_Texture* texture;
	SDL_Rect pos;
} Sprite;

typedef struct xypos { 
	float x;
	float y;
} XYPos;

// MAP DATAS
#include "map1.c" // const u8[] map1
#include "map1_obj.c"

u8 joy1_state;
u8 currentMapWidth;
u8 currentMapHeight;

// WINDOWS, RENDERERS AND TEXTURES must be DESTROYED
SDL_Window* window;
SDL_Renderer* renderer;
// SURFACES must be FREEd
SDL_Surface* canvas;
SDL_Rect mapCamera;

bool scrolling = false;

unsigned long long frameStart;
unsigned long long frameEnd;
float frameElapsed;
float perfFrequency;
float deltaTime;
float secondCounter;
int frameCounter;
int tickCounter;

float mapCameraX;
float mapCameraY;	
float cameraSpeed;

SDL_Texture* maptex;
SDL_Texture* mapobjtex;

SDL_Texture* dotSelector;
float mapSelectorSpeed;

Uint32 rmask, gmask, bmask, amask;

SDL_Rect mapSelector;

const SDL_Color clrWhite = { 255, 255, 255, 0 };
const SDL_Color clrBlack = { 0, 0, 0, 0 };

// enums
u8 inputMode;
#define MAP_GENERIC 1

// functions
//int main(int argn, char** args);
void LoadObjects(SDL_Surface* map, const char* objData, u8 mapWidth, u8 mapHeight);
void LoadMap(SDL_Surface* map, const char* mapData, u8 mapWidth, u8 mapHeight);
void LoadAllTiles(const char* filename, \
					Tile* tileArray, \
					u8 tilesX, u8 tilesY, \
					u8 tileW, u8 tileH);
void StateInput(volatile u8* keystate);
void Draw();
Sprite* NewSprite(char* imgsrc, SDL_Renderer* renderer, int x, int y, int w, int h);
//Tile* NewTile(char* imgsrc, u8 index);
void Input(SDL_Event e);
SDL_Surface* LoadBitmapToCanvas(char* path);
bool Initialize();
void Cleanup();


int main(int argn, char** args)
{
	//f
	// start SDL2 and open window
	Initialize();
	
	secondCounter = 0;
	frameCounter = 0;

	char* fontPath = "cc.ttf";
	TTF_Font* font = TTF_OpenFont(fontPath, 64);
	if(font == NULL)
		printf("Failed to load font from path: %s\n", fontPath);

	SDL_Surface* msg = TTF_RenderText_Solid(font, "Hello World", clrWhite);
	SDL_Surface* msg2 = TTF_RenderText_Solid(font, "Hello World", clrBlack);
	SDL_Texture* msgtex = SDL_CreateTextureFromSurface(renderer, msg);
	SDL_Texture* msgtex2 = SDL_CreateTextureFromSurface(renderer, msg2);
	SDL_FreeSurface(msg);
	SDL_FreeSurface(msg2);
	
	// Set pixel scaling mode 
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH/PIXELSCALE, SCREEN_HEIGHT/PIXELSCALE);
	// Set NEAREST vs LINEAR - doesnt work?
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
	// black background color
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

	currentMapHeight = 64;
	currentMapWidth = 64;

	// To set the tile map, we have to load in the PNGs into a Surface 
	// then we stamp the Tile Surface onto the Map Surface in order when needed
	// and only draw the Map Surface once per frame. 
	SDL_Surface* map 		= 	SDL_CreateRGBSurface(0, 1024, 1024, BPP_32, rmask, gmask, bmask, OPAQUE);
	SDL_Surface* mapObjects = 	SDL_CreateRGBSurface(0, 1024, 1024, BPP_32, rmask, gmask, bmask, amask);
	
	// Load all tiles 
	LoadAllTiles("tileset.png", &loadedTiles[0], 16, 16, 16, 16);	
	
	// Load in the map from data 
	LoadMap(map, &map1[0], 64, 64);
	LoadObjects(mapObjects, &map1_obj[0], 64, 64);
	
	// dot icon
	SDL_Surface* dotsurf = IMG_Load("selectdot.png");
	dotSelector = SDL_CreateTextureFromSurface(renderer, dotsurf);
	SDL_FreeSurface(dotsurf);
	
	// create texture from map surface
	maptex = SDL_CreateTextureFromSurface(renderer, map);
	mapobjtex = SDL_CreateTextureFromSurface(renderer, mapObjects);
	
	// the tile map must be sliced to display the right scale in the window
	mapCamera.x = 0;
	mapCamera.y = 0;
	mapSelector.x = 0.0f;
	mapSelector.y = 0.0f;
	mapSelector.h = 8;// * PIXELSCALE;
	mapSelector.w = 8;// * PIXELSCALE;
	mapCameraX = 0.0f;
	mapCameraY = 0.0f;
	mapSelectorSpeed = 200.0f;
	cameraSpeed = 100.0f;
	mapCamera.h = SCREEN_HEIGHT / PIXELSCALE;
	mapCamera.w = SCREEN_WIDTH / PIXELSCALE;

	volatile unsigned char* keystate = SDL_GetKeyboardState(NULL);
		
	SDL_Event e;
	bool quit = false;

	inputMode = MAP_GENERIC;
	
	while(!quit)
	{
		// FPS timing
		frameStart = SDL_GetPerformanceCounter();

		deltaTime /= 1000.0f;
		secondCounter += deltaTime;
		if(secondCounter > 1.0f)
		{
			secondCounter -= 1.0f;
			printf("FPS: %d\n", frameCounter);
			frameCounter = 0;
		}

		// sdl events:
		while(SDL_PollEvent(&e))
		{
			if(e.type == SDL_QUIT) // clicked X
			{
				quit = true;
			}
			// Triggered input:
			Input(e);
			
		}

		keystate = SDL_GetKeyboardState(NULL);
		StateInput(keystate);
		
		// round camera
		mapCamera.x = floor(mapCameraX);
		mapCamera.y = floor(mapCameraY);
		Draw();
		
		// 60 FPS Cap 
		frameEnd = SDL_GetPerformanceCounter();
		frameElapsed = (frameEnd - frameStart);
		deltaTime = frameElapsed / perfFrequency; // ticks / how many ticks per milisecond = time
		
		deltaTime = floor(FPS_60) - deltaTime;
		
		SDL_Delay(deltaTime);
	}
	
	// cleanup
	// all surfaces - tiles
	for(int i = 0; i <= 255; i++)
	{
		if(loadedTiles[i].source != NULL)
			SDL_FreeSurface(loadedTiles[i].source);
	}
	// and sprites
	// TODO 
	// all maps and UIs
	SDL_FreeSurface(map);
	SDL_FreeSurface(mapObjects);
	//msgtexs
	SDL_DestroyTexture(msgtex);
	SDL_DestroyTexture(msgtex2);
	//selector 
	SDL_DestroyTexture(dotSelector);
	//maptex/mapobjtex
	SDL_DestroyTexture(maptex);
	SDL_DestroyTexture(mapobjtex);
	Cleanup();
	// End game
	return 0;
}


void LoadObjects(SDL_Surface* map, const char* objData, u8 mapWidth, u8 mapHeight)
{
	SDL_Rect r;
	r.x = 0; 
	r.y = 0;
	r.w = TILESIZE * PIXELSCALE;
	r.h = TILESIZE * PIXELSCALE;
	for(int y = 0; y < mapHeight; y++)
	{
		for(int i = 0; i < mapWidth; i++)
		{
			int ix = (y * mapHeight) + i;
			if(objData[ix] != 0)
			{
				Tile* t = &loadedTiles[objData[ix]];
				SDL_BlitSurface(t->source, NULL, map, &r);
			}
			r.x += TILESIZE;
		}
		r.x = 0;
		r.y += TILESIZE;
	}
}


void LoadMap(SDL_Surface* map, const char* mapData, u8 mapWidth, u8 mapHeight)
{
	SDL_Rect r;
	r.x = 0; 
	r.y = 0;
	r.w = TILESIZE * PIXELSCALE;
	r.h = TILESIZE * PIXELSCALE;
	for(u8 y = 0; y < mapHeight; y++)
	{
		for(u8 i = 0; i < mapWidth; i++)
		{
			Tile* t = &loadedTiles[mapData[(y*mapHeight) + i]];
			SDL_BlitSurface(t->source, NULL, map, &r);
			r.x += TILESIZE;
		}
		r.x = 0;
		r.y += TILESIZE;
	}
	
}


void LoadAllTiles(const char* filename, \
					Tile* tileArray, \
					u8 tilesX, u8 tilesY, \
					u8 tileW, u8 tileH)
{
	SDL_Surface* tileMap = IMG_Load(filename);
	SDL_Rect tslice;
	tslice.x = 0;
	tslice.y = 0;
	tslice.w = 16;
	tslice.h = 16;
	// Create individual surfaces and blit them in 
	for(u8 y = 0; y < tilesY; y++)
	{
		for(u8 x = 0; x < tilesX; x++)
		{
			u8 i = (y * tilesY) + x;
			tileArray[i].source = SDL_CreateRGBSurface(NULL, tileW, tileH, BPP_32, rmask, gmask, bmask, amask);
			tslice.x = x * tileW;
			tslice.y = y * tileH;
			SDL_BlitSurface(tileMap, &tslice, tileArray[i].source, NULL);
		}
	}
	// free it!
	SDL_FreeSurface(tileMap);
}

void StateInput(volatile u8* keystate)
{
	switch(inputMode)
	{
		case MAP_GENERIC:
			if(keystate[SDL_SCANCODE_RIGHT])
			{
				mapSelector.x += mapSelectorSpeed * deltaTime;
			}
			else if(keystate[SDL_SCANCODE_LEFT])
			{
				mapSelector.x -= mapSelectorSpeed * deltaTime;
			}
			if(keystate[SDL_SCANCODE_DOWN])
			{
				mapSelector.y += mapSelectorSpeed * deltaTime;
			}
			else if(keystate[SDL_SCANCODE_UP])
			{
				mapSelector.y -= mapSelectorSpeed * deltaTime;
			}
			// if the selector is outside of bounds, set it to bounds,
			// and add the difference to camera pos 
			if (mapSelector.x > 280)
			{
				mapCameraX += mapSelectorSpeed * deltaTime;
				mapSelector.x = 280;
			}
			if (mapSelector.y > 164)
			{
				mapCameraY += mapSelectorSpeed * deltaTime;
				mapSelector.y = 164;
			}
			if (mapSelector.x < 32)
			{
				mapCameraX -= mapSelectorSpeed * deltaTime;
				mapSelector.x = 32;
			}
			if (mapSelector.y < 24)
			{
				mapCameraY -= mapSelectorSpeed * deltaTime;
				mapSelector.y = 24;
			}
			break;
	}
}

void Draw()
{
	// non event:
	// CLS
	SDL_RenderClear(renderer);

	// MAP!
	SDL_RenderCopy(renderer, maptex, &mapCamera, NULL);
	SDL_RenderCopy(renderer, mapobjtex, &mapCamera, NULL);

	// sel 
	SDL_RenderCopy(renderer, dotSelector, NULL, &mapSelector);

	// Drawit
	SDL_RenderPresent(renderer);    
	frameCounter++;

}

Sprite* NewSprite(char* imgsrc, SDL_Renderer* renderer, int x, int y, int w, int h)
{
	Sprite s;
	s.source = IMG_Load(imgsrc);
	if(s.source == NULL)
	{
		printf("Failed to load sprite image from path: %s\n", imgsrc);
	}
	s.texture = SDL_CreateTextureFromSurface(renderer, s.source);
	s.pos.x = x;
	s.pos.y = y;
	s.pos.w = w;
	s.pos.h = h;
	SDL_FreeSurface(s.source);
	return &s;
}

/*
Tile* NewTile(char* imgsrc, u8 index)
{
	Tile t;
	t.source = IMG_Load(imgsrc);
	if(t.source == NULL)
		printf("Failed to load tile image from path: %s\n", imgsrc);
	loadedTiles[index] = t;
	return &loadedTiles[index];
}
*/

void Input(SDL_Event e)
{	
	
}


SDL_Surface* LoadBitmapToCanvas(char* path)
{
	SDL_Surface* cv = SDL_LoadBMP(path);
	if(cv == NULL)
	{
		printf("Couldn't load image %s. Error: %s", path, SDL_GetError());
	}
	return cv;
}


bool Initialize()
{
	// backend
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL2 failed to initialize!\n");
		return false;
	}
	// fonts 
	TTF_Init();
	// window and renderer
	if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, \
									SCREEN_HEIGHT, \
									SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE, \
									&window, &renderer) == -1)
	{
		printf("Couldn't make window. SDL error: %s\n", SDL_GetError());
		return false;
	}
	// system specific 
	perfFrequency = SDL_GetPerformanceFrequency();

	// define bitmasking
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		rmask = 0xff000000;
		gmask = 0x00ff0000;
		bmask = 0x0000ff00;
		amask = 0x000000ff;
	#else
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;
	#endif

	return true;
}


void Cleanup()
{
	
	//windows and renderers
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
	
	SDL_Quit();
	#ifdef DEBUG 
		printf("Cleanup done.\n");
	#endif 
}
