#pragma once

#include <limits>
#include "particleGenerator.h"

class ForceGenerator;

class ParticleSystem
{
	
protected:

	Vector3 _particleSource;
	std::vector<ParticleDT> _particles;
	std::vector<ParticleGenerator*> _particleGenerators;
	std::vector<ForceGenerator*> _forceGenerators;

	void integrateParticles(double t);
	void deleteParticles(double t);

public:
	ParticleSystem(std::vector<ParticleGenerator*> particleGenerators = std::vector<ParticleGenerator*>(), std::vector<ParticleDT> particles = std::vector<ParticleDT>(), std::vector<ForceGenerator*> forces = std::vector<ForceGenerator*>());
	~ParticleSystem();
	void generateParticle();
	void addParticle(Particle* part, Vector3 origin, double lifeDistance, double lifeTime = std::numeric_limits<double>::infinity());
	void addParticle(ParticleDT part);
	void addParticleGenerator(ParticleGenerator* particleGenerator);
	void addForceGenerator(ForceGenerator* fg);
	virtual void update(double t);
};

