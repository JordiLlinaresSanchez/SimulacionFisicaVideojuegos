#include "gravityForceGenerator.h"
#include "particle.h"

GravityForceGenerator::GravityForceGenerator(Vector3 force) : ForceGenerator(force){}

void 
GravityForceGenerator::update(double t){}

bool
GravityForceGenerator::checkCondition(Particle* p){
	return true;
}

bool
GravityForceGenerator::checkCondition(physx::PxRigidDynamic* s) {
	return true;
}

Vector3
GravityForceGenerator::applyForce(Particle* p) {
	return p->getMass() * _magnitude;
}

Vector3
GravityForceGenerator::applyForce(physx::PxRigidDynamic* s) {
	return Vector3(0.0);
}
