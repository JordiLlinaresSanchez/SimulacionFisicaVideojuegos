#include "particleSystem.h"
#include "particle.h"

ParticleSystem::ParticleSystem(std::vector<ParticleGenerator*> particleGenerators = std::vector<ParticleGenerator*>(), int partsPerFrame = 3, std::vector<ParticleDT> particles = std::vector<ParticleDT>()) : 
							   _particles(particles), _particleGenerators(particleGenerators), _partsPerFrame(partsPerFrame) {}

ParticleSystem::~ParticleSystem() {
	for (ParticleGenerator* pg : _particleGenerators) delete pg;
	for (ParticleDT& p : _particles) delete p.particle;
}

void
ParticleSystem::addParticleGenerator(ParticleGenerator* particleGenerator) {
	_particleGenerators.push_back(particleGenerator);
}

void
ParticleSystem::update(double t) {
	integrateParticles(t);
	deleteParticles();
	generateParticle();
}

void 
ParticleSystem::integrateParticles(double t) {
	for (ParticleDT& part : _particles) part.particle->integrate(t);
}

void 
ParticleSystem::generateParticle() {
	for (int i = 0; i < _particleGenerators.size(); i++) {
		auto parts = _particleGenerators[i]->generateParticle(_partsPerFrame);
		for (ParticleDT& part : parts) _particles.push_back(part);
	}
}

void 
ParticleSystem::deleteParticles() {

}