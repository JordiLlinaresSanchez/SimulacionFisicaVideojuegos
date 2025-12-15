#include "solidSystem.h"
#include "forceGenerator.h"

SolidSystem::SolidSystem(std::vector<SolidGenerator*> solidGenerators, std::vector<SolidDT> solids/*, std::vector<ForceGenerator*> forces*/ ) :
	_solids(solids), _solidGenerators(solidGenerators)/*, _forceGenerators(forces)*/ {}

SolidSystem::~SolidSystem() {
	for (SolidGenerator* sg : _solidGenerators) delete sg;
	//for (SolidDT& s : _solids) delete s.solid;
	//for (ForceGenerator* fg : _forceGenerators) delete fg;
}

void
SolidSystem::addSolidGenerator(SolidGenerator* solidGenerator) {
	_solidGenerators.push_back(solidGenerator);
}

//void
//SolidSystem::addForceGenerator(ForceGenerator* fg) {
//	_forceGenerators.push_back(fg);
//}

void
SolidSystem::addSolid(physx::PxRigidActor* solid, Vector3 origin, double lifeDistance, double lifeTime) {
	SolidDT newSolid;
	newSolid.lifeDistance = lifeDistance;
	newSolid.lifeTime = lifeTime;
	newSolid.origin = origin;
	newSolid.solid = solid;
	_solids.push_back(newSolid);
}

void
SolidSystem::addSolid(SolidDT solid) {
	_solids.push_back(solid);
}

void
SolidSystem::update(double t) {
	//for (ForceGenerator* fg : _forceGenerators) fg->update(t);
	//integrateParticles(t);
	deleteSolids(t);
	generateSolid();
}

//void
//SolidSystem::integrateSolids(double t) {
//	for (SolidDT& part : _solids) {
//		Vector3 force(0);
//		for (ForceGenerator* fg : _forceGenerators) {
//			if (fg->checkCondition(part.particle)) {
//				force += fg->applyForce(part.particle);
//			}
//		}
//		part.particle->setAccel(force / part.particle->getMass());
//		part.particle->integrate(t);
//
//	}
//}

void
SolidSystem::generateSolid() {
	for (int i = 0; i < _solidGenerators.size(); i++) {
		auto parts = _solidGenerators[i]->generate();
		for (SolidDT& part : parts) _solids.push_back(part);
	}
}

void
SolidSystem::deleteSolid(double t) {
	for (int i = _solids.size() - 1; i >= 0; --i) {
		_solids[i].lifeTime -= t;
		if (_solids[i].lifeDistance < (_particles[i].particle->getPos() - _particles[i].origin).magnitude() || _particles[i].lifeTime < 0) {
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