#include "solidSystem.h"
#include "forceGenerator.h"
#include "RenderUtils.hpp"
#include "solidGenerator.h"
#include <iostream>

SolidSystem::SolidSystem(physx::PxScene* scene, physx::PxPhysics* physics, int maxSolids) :
	_solids(0, SolidDT()), _solidGenerators(), _forceGenerators(), _gScene(scene), _gPhysics(physics), _maxSolids(maxSolids) {
	_solidGenerators = std::vector<SolidGenerator*>();
	_forceGenerators = std::vector<ForceGenerator*>();
}

SolidSystem::~SolidSystem() {
	for (SolidGenerator* sg : _solidGenerators) delete sg;
	
	for (SolidDT& s : _solids) {
		_gScene->removeActor(*s.solid);
		DeregisterRenderItem(s.ri);
		s.ri->release();
	}
	for (ForceGenerator* fg : _forceGenerators) delete fg;
}

void
SolidSystem::addSolidGenerator(SolidGenerator* solidGenerator) {
	_solidGenerators.push_back(solidGenerator);
}

void
SolidSystem::addForceGenerator(ForceGenerator* fg) {
	_forceGenerators.push_back(fg);
}

void
SolidSystem::addSolid(Vector3& origin, physx::PxShape* shape, Vector4 color, double lifeDistance, double lifeTime, Vector3 vel, double mass) {
	SolidDT newSolid;
	newSolid.lifeDistance = lifeDistance;
	newSolid.lifeTime = lifeTime;
	newSolid.origin = origin;
	
	newSolid.solid = _gPhysics->createRigidDynamic(physx::PxTransform(origin));
	newSolid.solid->attachShape(*shape);
	_gScene->addActor(*newSolid.solid);
	physx::PxRigidBodyExt::updateMassAndInertia(*newSolid.solid, 0.15);

	newSolid.ri = new RenderItem(shape, newSolid.solid, color);
	newSolid.solid->setMass(mass);

	_solids.push_back(newSolid);
}


void
SolidSystem::update(double t) {
	for (ForceGenerator* fg : _forceGenerators) fg->update(t);
	deleteSolid(t);
	integrate(t);
	generateSolid();
}

void
SolidSystem::integrate(double t) {
	for (SolidDT& sol : _solids) {
		Vector3 force(0);
		for (ForceGenerator* fg : _forceGenerators) {
			if (fg->checkCondition(sol.solid)) {
				force += fg->applyForce(sol.solid);
			}
		}
		sol.solid->addForce(force);

	}
}

void
SolidSystem::generateSolid() {
	for (int i = 0; i < _solidGenerators.size() && _solids.size() < _maxSolids; i++) {
		auto parts = _solidGenerators[i]->generate(_gScene);
		for (SolidDT& part : parts) {
			if (_solids.size() < _maxSolids) _solids.push_back(part);
			else {
				_gScene->removeActor(*part.solid);
				part.ri->release();
			}
		}
	}
}

void
SolidSystem::deleteSolid(double t) {
	int size = _solids.size();

	for (int i = 0; i < size; ++i) {
		auto aux = _solids.front();
		_solids.pop_front();
		if (aux.lifeDistance < (aux.solid->getGlobalPose().p - aux.origin).magnitude() || aux.lifeTime < 0) {
			aux.solid->release();
			DeregisterRenderItem(aux.ri);
		}
		else {
			_solids.push_back(aux);
		}
	}
}
