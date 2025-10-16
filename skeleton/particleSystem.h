#pragma once

#include "particleGenerator.h"


class ParticleSystem
{
	
private:
	int _partsPerFrame;

	Vector3 _particleSource;
	std::vector<ParticleDT> _particles;
	std::vector<ParticleGenerator*> _particleGenerators;

	void integrateParticles(double t);
	void generateParticle();
	void deleteParticles();

public:
	ParticleSystem(std::vector<ParticleGenerator*> particleGenerators, int partsPerFrame, std::vector<ParticleDT> particles);
	~ParticleSystem();
	void generateParticles();
	void addParticleGenerator(ParticleGenerator* particleGenerator);
	void update(double t);
};

