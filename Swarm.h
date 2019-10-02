#pragma once
#include "Particle.h"

class Swarm
{
public:
	// number of particle in the screen
	const static int N_PARTICLES = 50000;
private:
	Particle* m_ptrParticles;
	int lastTime; 

public:
	Swarm();
	virtual ~Swarm();

	const Particle* const getParticles() {
		return m_ptrParticles;
	};

	void update(int elapsed);
};

