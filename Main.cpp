#include <iostream>
#include <SDL.h>
#include "Screen.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Swarm.h"

using namespace std;


int main(int argc, char* argv[])
{
	srand(time(NULL));

	//creating a Screen object
	Screen screen; 

	// initializing the screen
	screen.init();
	
	// creating Swarm object
	Swarm swarm;


	

	double const red_speedOfColourChange = 0.0005; 
	double const green_speedOfColourChange = 0.0003;
	double const blue_speedOfColourChange = 0.0009;
	
	while (true){
		// updating individual particles

		
		// drawing particles =========================
		double elapsed = SDL_GetTicks(); // returns the time elapsed

		screen.clear(); // clears the screen before updating for not leaving trace
		swarm.update(elapsed); // motion of the particle

		// creating a range of value from 0 to 255 for the colour RGB parameter to update and ultimately change colour gradually
		int red = (sin(elapsed * red_speedOfColourChange) + 1) * 128; // returns value between 0 and 256 (integer) --> 0 <= x < 256
		int green = (sin(elapsed * green_speedOfColourChange) + 1) * 128;
		int blue = (sin(elapsed * blue_speedOfColourChange) + 1) * 128;

		const Particle* const ptrParticles = swarm.getParticles();
		for (int i = 0; i < Swarm::N_PARTICLES; i++)
		{
			// getting individual particle on the screen an plotting them
			Particle particle = ptrParticles[i];

			int x = (particle.m_x + 1) * Screen::SCREEN_WIDTH / 2;
			int y = particle.m_y * Screen::SCREEN_WIDTH / 2 + Screen::SCREEN_HEIGHT / 2;

			//RGB colour is choosen such that in a supernova the actual color change occurs
			// supernova colour = 0xffb437
			screen.setPixel(x, y, red, 0xb4, 0x37); 
			
			
		}

		
		// drawing particles =========================
		
		
		/*
		// visiting every pixel in the screen
		for (int y = 0; y < Screen::SCREEN_HEIGHT; y++)
		{
			for (int x = 0; x < Screen::SCREEN_WIDTH; x++)
			{
				screen.setPixel(x, y, red, green, blue); // setting colour of the particle
			}
		}
		*/
		

		// Draw the screen
		screen.update();

		
		// check for messages
		if (screen.processEvents() == false) {
			break;
		}
	}




	

	// closing the screen
	screen.close();

	return 0;
}