#pragma once


struct Particle // these are Star Dust in the language of cosmos
{
	// particles have x,y co-ordinates in this 2D GUI 
	double m_x; 
	double m_y;

	// speed and direction of the particles 
	// represented as polar co-ordinates for the spreading of the particles
	double m_speed;
	double m_direction;

public:
	Particle();
	virtual ~Particle();
	void update(int interval);
};

