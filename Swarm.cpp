#include "Swarm.h"

Swarm::Swarm(): lastTime(0)
{
	// initializing number of particles 
	m_ptrParticles = new Particle[N_PARTICLES];
}

Swarm::~Swarm()
{
	// clearing the memory 
	delete [] m_ptrParticles;
}

void Swarm::update(int elapsed)
{
	int interval = elapsed - lastTime;

	for (int i = 0; i < Swarm::N_PARTICLES; i++) {
		m_ptrParticles[i].update(interval); // updating each particles
	}

	lastTime = elapsed;
}
