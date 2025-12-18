#include "bowlingBallSystem.h"
#include "forceGenerator.h"

BowlingBallSystem::BowlingBallSystem(physx::PxScene* scene, physx::PxPhysics* physics, int maxSolid) : SolidSystem(scene, physics, maxSolid) {}

void
BowlingBallSystem::update(double t) {
	for (ForceGenerator* fg : _forceGenerators) fg->update(t);
	integrate(t);
	deleteSolid(t);
}
BowlingBallSystem::~BowlingBallSystem(){}