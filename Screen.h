#pragma once
#include <SDL.h>

class Screen{
public:
	// declaring screen size as static since only one is needed
	const static int SCREEN_WIDTH = 800;
	const static int SCREEN_HEIGHT = 600;

private:
	// declaring as member variable m_<****>
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_Texture* m_texture;
	Uint32* m_buffer;

public:
	Screen();
	bool init();
	bool processEvents();
	void close();
	void update();
	void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue); // takes (x,y) co-ordinates to set the pixels at
	void clear(); // clears the particle after update

};

