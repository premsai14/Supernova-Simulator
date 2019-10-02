#include "Particle.h"
#include <stdlib.h>
#define PI 3.14159265358979323846
#include <math.h>

Particle::Particle()
{
	// mapping x,y co-ordinates to the center for stating of the supernova explosion
	m_x = 0;
	m_y = 0;

	// returns value b/w 0 to 360 degree
	m_direction = 2 * PI * rand() / RAND_MAX;
	m_speed = 0.0004 * rand() / RAND_MAX;
}

Particle::~Particle()
{
}

void Particle::update(int interval)
{

	double x_speed = m_speed * cos(m_direction);
	double y_speed = m_speed * sin(m_direction);

	m_x += x_speed * interval;
	m_y += y_speed * interval;
}
