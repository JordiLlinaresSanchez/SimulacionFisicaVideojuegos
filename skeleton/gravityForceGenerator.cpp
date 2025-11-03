#include "gravityForceGenerator.h"
#include "particle.h"

GravityForceGenerator::GravityForceGenerator(Vector3 force) : ForceGenerator(Vector3(), force){}

void 
GravityForceGenerator::update(double t){}

bool
GravityForceGenerator::checkCondition(const Particle* p){
	return true;
}

Vector3
GravityForceGenerator::applyForce(Particle* p) {
	return p->getMass() * _force;
}