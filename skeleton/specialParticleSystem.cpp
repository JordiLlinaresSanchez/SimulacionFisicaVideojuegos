#include "specialParticleSystem.h"
#include "forceGenerator.h"

SpecialParticleSystem::SpecialParticleSystem(std::vector<ParticleGenerator*> particleGenerators, std::vector<ParticleDT> particles, std::vector<ForceGenerator*> forces): ParticleSystem(particleGenerators, particles, forces) {}

void
SpecialParticleSystem::update(double t) {
	for (ForceGenerator* fg : _forceGenerators) fg->update(t);
	integrateParticles(t);
	deleteParticles(t);
}