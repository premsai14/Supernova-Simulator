#include "Screen.h"
#include <iostream>

using namespace std;

// constructor initialization
Screen::Screen():
	m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer(NULL)
{
}

bool Screen::init()
{
	//Initialization of the system
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {

		cout << "SDL initialization failed." << endl;
		return false;
	}

	cout << "SDL Initialization suceeded." << endl;

	// create a window by passing required parameters 
	m_window = SDL_CreateWindow("Supernova Simulator",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	// if for some reason SDL couldn't create window it returns NULL, so we check it here
	if (m_window == NULL) {
		cout << "Could not create window" << endl;
		SDL_Quit();
		return false;

	}



	// creating renderer and texture for pixel manipulation
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);


	// Error condition checking
	if (m_renderer == NULL) {
		cout << "Renderer couldn't be created !!!" << endl;
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}
	if (m_texture == NULL) {
		cout << "Texture couldn't be created !!!" << endl;
		SDL_DestroyRenderer(m_renderer); // at this point the renderer is successfully created hence it has to be cleaned
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}


	// 32 bit int in SDL
	// allocating 32 bit space for each pixel in the screen for changing its colour ( 32 bit color space )
	// contains all the information for the pixels
	m_buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

	//writing pixel information into the buffer
	memset(m_buffer, 0xFF, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

	/*
	===================================================
	// setting indivial pixel colour
	m_buffer[1000] = 0x00000000; // hexa colour

	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++){
		m_buffer[i] = 0x1234567F;
	}
	===================================================
	*/
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
		m_buffer[i] = 0x0; // black background
	}

	



	return true;
}

bool Screen::processEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
		{
			return false;
		}
	}
	return true;
}

void Screen::close()
{
	// DeInitialize the system
	delete[] m_buffer; // deleting all the pixel memory spaces in memory
	SDL_DestroyRenderer(m_renderer); // destroying renderer first since renderer uses texture
	SDL_DestroyTexture(m_texture);
	SDL_DestroyWindow(m_window); // clean up resources
	SDL_Quit();
}

void Screen::update()
{
	SDL_UpdateTexture(m_texture, NULL, m_buffer, SCREEN_WIDTH * sizeof(Uint32));
	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
	SDL_RenderPresent(m_renderer);

}

void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue)
{
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
		return;
	}

	Uint32 colour = 0;

	// adding and left bit shifting 1 byte(8bit) to have a hexadecimal colour space output
	colour += red;
	colour <<= 8;

	colour += green;
	colour <<= 8;

	colour += blue;
	colour <<= 8;

	colour += 0xFF; // Alpha value in SDL is preset as in the documentation

	m_buffer[(y * SCREEN_WIDTH) + x] = colour;
}

void Screen::clear()
{
	memset(m_buffer, 0x00, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
	// memset each byte to 0
}
