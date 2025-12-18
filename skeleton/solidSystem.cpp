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
SolidSystem::addSolid(Vector3& origin, physx::PxShape* shape, Vector4 color, double lifeDistance, double lifeTime, Vector3 vel) {
	SolidDT newSolid;
	newSolid.lifeDistance = lifeDistance;
	newSolid.lifeTime = lifeTime;
	newSolid.origin = origin;
	
	physx::PxRigidDynamic* solid = _gPhysics->createRigidDynamic(physx::PxTransform(origin));
	solid->attachShape(*shape);
	_gScene->addActor(*solid);
	physx::PxRigidBodyExt::updateMassAndInertia(*newSolid.solid, 0.15);

	newSolid.solid = solid;
	newSolid.ri = new RenderItem(shape, solid, color);
	
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
	for (int i = _solids.size() - 1; i >= 0; --i) {
		_solids[i].lifeTime -= t;
		if (_solids[i].lifeDistance < (_solids[i].solid->getGlobalPose().p - _solids[i].origin).magnitude() ||  _solids[i].lifeTime < 0) {
			std::cout << _solids[i].solid->getGlobalPose().p.x << ' ' << _solids[i].solid->getGlobalPose().p.y << ' ' << _solids[i].solid->getGlobalPose().p.z << '\n';
			SolidDT& temp = _solids[i];
			_solids[i] = _solids[_solids.size() - 1];
			_solids[_solids.size() - 1] = temp;

			_gScene->removeActor(*temp.solid);
			_solids[_solids.size() - 1].ri->release();

			//_solids[_solids.size() - 1].solid = NULL;
			_solids.pop_back();
		}
	}
}