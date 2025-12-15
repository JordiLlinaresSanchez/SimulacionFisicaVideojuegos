#include "particleSystem.h"
#include "particle.h"
#include "forceGenerator.h"

ParticleSystem::ParticleSystem(std::vector<ParticleGenerator*> particleGenerators, std::vector<ParticleDT> particles, std::vector<ForceGenerator*> forces) :
							   _solids(particles), _particleGenerators(particleGenerators), _forceGenerators(forces) {}

ParticleSystem::~ParticleSystem() {
	for (ParticleGenerator* pg : _particleGenerators) delete pg;
	for (ParticleDT& p : _solids) delete p.particle;
	for (ForceGenerator* fg : _forceGenerators) delete fg;
}

void
ParticleSystem::addParticleGenerator(ParticleGenerator* particleGenerator) {
	_particleGenerators.push_back(particleGenerator);
}

void
ParticleSystem::addForceGenerator(ForceGenerator* fg) {
	_forceGenerators.push_back(fg);
}

void 
ParticleSystem::addParticle(Particle* part, Vector3 origin, double lifeDistance, double lifeTime) {
	ParticleDT newPart;
	newPart.lifeDistance = lifeDistance;
	newPart.lifeTime = lifeTime;
	newPart.origin = origin;
	newPart.particle = part;
	_solids.push_back(newPart);
}

void
ParticleSystem::addParticle(ParticleDT part) {
	_solids.push_back(part);
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
	for (ParticleDT& part : _solids) {
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
		for (ParticleDT& part : parts) _solids.push_back(part);
	}
}

void 
ParticleSystem::deleteParticles(double t) {
	for (int i = _solids.size() - 1; i >= 0; --i) {
		_solids[i].lifeTime -= t;
		if (_solids[i].lifeDistance < (_solids[i].particle->getPos() - _solids[i].origin).magnitude() || _solids[i].lifeTime<0) {
			auto temp = _solids[i];
			_solids[i] = _solids[_solids.size() - 1];
			_solids[_solids.size() - 1] = temp;
			auto a = _solids[i];
			auto p = --_solids.end();
			_solids.pop_back();
			delete p._Ptr->particle;
		}
	}
}