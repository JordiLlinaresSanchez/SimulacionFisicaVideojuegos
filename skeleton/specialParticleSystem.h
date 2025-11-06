#pragma once
#include "particleSystem.h"
class SpecialParticleSystem: public ParticleSystem
{
public:
	SpecialParticleSystem(std::vector<ParticleGenerator*> particleGenerators = std::vector<ParticleGenerator*>(), std::vector<ParticleDT> particles = std::vector<ParticleDT>(), std::vector<ForceGenerator*> forces = std::vector<ForceGenerator*>());
	void update(double t) override;
};