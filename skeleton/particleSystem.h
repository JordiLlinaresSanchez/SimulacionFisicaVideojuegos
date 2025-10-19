#pragma once

#include "particleGenerator.h"


class ParticleSystem
{
	
private:

	Vector3 _particleSource;
	std::vector<ParticleDT> _particles;
	std::vector<ParticleGenerator*> _particleGenerators;

	void integrateParticles(double t);
	void generateParticle();
	void deleteParticles(double t);

public:
	ParticleSystem(std::vector<ParticleGenerator*> particleGenerators, std::vector<ParticleDT> particles);
	~ParticleSystem();
	void generateParticles();
	void addParticleGenerator(ParticleGenerator* particleGenerator);
	void update(double t);
};

