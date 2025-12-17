#include "solidSystem.h"
#include "forceGenerator.h"
#include "RenderUtils.hpp"
#include <iostream>

SolidSystem::SolidSystem(physx::PxScene* scene, physx::PxPhysics* physics) :
	_solids(0, SolidDT()), _solidGenerators(0)/*, _forceGenerators(forces)*/, _gScene(scene), _gPhysics(physics) {}

SolidSystem::~SolidSystem() {
	for (SolidGenerator* sg : _solidGenerators) delete sg;
	
	for (SolidDT& s : _solids) {
		_gScene->removeActor(*s.solid);
		s.ri->shape->release();
		delete s.ri;
	}
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
SolidSystem::addSolid(physx::PxRigidActor* solid, Vector3& origin, physx::PxShape* shape, Vector4 color, double lifeDistance, double lifeTime) {
	SolidDT newSolid;
	newSolid.lifeDistance = lifeDistance;
	newSolid.lifeTime = lifeTime;
	newSolid.origin = origin;
	newSolid.solid = solid;
	
	solid = _gPhysics->createRigidDynamic(physx::PxTransform(origin));
	solid->attachShape(*shape);
	_gScene->addActor(*solid);

	newSolid.ri = new RenderItem(shape, solid, color);
	
	_solids.push_back(newSolid);
}


void
SolidSystem::update(double t) {
	//for (ForceGenerator* fg : _forceGenerators) fg->update(t);
	//integrateParticles(t);
	for (auto a : _solids) std::cout<< a.solid->getGlobalPose().p.y << '\n';
	deleteSolid(t);
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
		if (_solids[i].lifeDistance < (_solids[i].solid->getGlobalPose().p - _solids[i].origin).magnitude() || _solids[i].lifeTime < 0) {
			auto temp = _solids[i];
			_solids[i] = _solids[_solids.size() - 1];
			_solids[_solids.size() - 1] = temp;
			auto a = _solids[i];
			auto p = --_solids.end();
			_solids.pop_back();
			_gScene->removeActor(*p->solid);
			p->solid = NULL;
		}
	}
}