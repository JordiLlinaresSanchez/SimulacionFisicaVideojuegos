#include "particleSystem.h"
#include "particle.h"

ParticleSystem::ParticleSystem(std::vector<ParticleGenerator*> particleGenerators = std::vector<ParticleGenerator*>(), std::vector<ParticleDT> particles = std::vector<ParticleDT>()) : 
							   _particles(particles), _particleGenerators(particleGenerators) {}

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
	deleteParticles(t);
	generateParticle();
}

void 
ParticleSystem::integrateParticles(double t) {
	for (ParticleDT& part : _particles) part.particle->integrate(t);
}

void 
ParticleSystem::generateParticle() {
	for (int i = 0; i < _particleGenerators.size(); i++) {
		auto parts = _particleGenerators[i]->generateParticle();
		for (ParticleDT& part : parts) _particles.push_back(part);
	}
}

void 
ParticleSystem::deleteParticles(double t) {
	for (int i = _particles.size() - 1; i >= 0; --i) {
		_particles[i].lifeTime -= t;
		if (/*_particles[i].lifeDistance < (_particles[i].particle->getPos() - _particles[i].origin).magnitude() ||*/ _particles[i].lifeTime<0) {
			auto temp = _particles[i];
			_particles[i] = _particles[_particles.size() - 1];
			_particles[_particles.size() - 1] = temp;
			auto a = _particles[i];
			auto p = --_particles.end();
			_particles.pop_back();
			delete p._Ptr->particle;
		}
	}
}