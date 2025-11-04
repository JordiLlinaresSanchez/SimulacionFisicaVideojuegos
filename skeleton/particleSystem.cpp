#include "particleSystem.h"
#include "particle.h"
#include "forceGenerator.h"
#include "iostream"

ParticleSystem::ParticleSystem(std::vector<ParticleGenerator*> particleGenerators = std::vector<ParticleGenerator*>(), std::vector<ParticleDT> particles = std::vector<ParticleDT>(), std::vector<ForceGenerator*> forces = std::vector<ForceGenerator*>()) :
							   _particles(particles), _particleGenerators(particleGenerators), _forceGenerators(forces) {}

ParticleSystem::~ParticleSystem() {
	for (ParticleGenerator* pg : _particleGenerators) delete pg;
	for (ParticleDT& p : _particles) delete p.particle;
	for (ForceGenerator* fg : _forceGenerators) delete fg;
}

void
ParticleSystem::addParticleGenerator(ParticleGenerator* particleGenerator) {
	_particleGenerators.push_back(particleGenerator);
}

void 
ParticleSystem::generateParticles(Particle* part, double lifeDistance, double lifeTime, Vector3 origin) {
	ParticleDT newPart;
	newPart.lifeDistance = lifeDistance;
	newPart.lifeTime = lifeTime;
	newPart.origin = origin;
	newPart.particle = part;
	_particles.push_back(newPart);
}

void
ParticleSystem::generateParticles(ParticleDT part) {
	_particles.push_back(part);
}

void
ParticleSystem::update(double t) {
	for (ForceGenerator* fg : _forceGenerators) fg->update(t);
	integrateParticles(t);
	deleteParticles(t);
	generateParticle();
}

void 
ParticleSystem::integrateParticles(double t) {
	for (ParticleDT& part : _particles) {
		Vector3 force(0);
		for (ForceGenerator* fg : _forceGenerators) {
			if (fg->checkCondition(part.particle)) {
				force += fg->applyForce(part.particle);
			}
		}
		part.particle->setAccel(force / part.particle->getMass());
		part.particle->integrate(t);

	}
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
		if (_particles[i].lifeDistance < (_particles[i].particle->getPos() - _particles[i].origin).magnitude() || _particles[i].lifeTime<0) {
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