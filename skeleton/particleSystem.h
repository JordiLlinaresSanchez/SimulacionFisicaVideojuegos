#pragma once

#include "particleGenerator.h"

class ForceGenerator;

class ParticleSystem
{
	
private:

	Vector3 _particleSource;
	std::vector<ParticleDT> _particles;
	std::vector<ParticleGenerator*> _particleGenerators;
	std::vector<ForceGenerator*> _forceGenerators;

	void integrateParticles(double t);
	void generateParticle();
	void deleteParticles(double t);

public:
	ParticleSystem(std::vector<ParticleGenerator*> particleGenerators, std::vector<ParticleDT> particles, std::vector<ForceGenerator*> forceGen);
	~ParticleSystem();
	void generateParticles();
	void addParticleGenerator(ParticleGenerator* particleGenerator);
	void update(double t);
};

