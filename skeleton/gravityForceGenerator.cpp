#include "gravityForceGenerator.h"
#include "particle.h"

GravityForceGenerator::GravityForceGenerator(Vector3 force) : ForceGenerator(force){}

void 
GravityForceGenerator::update(double t){}

bool
GravityForceGenerator::checkCondition(Particle* p){
	return true;
}

Vector3
GravityForceGenerator::applyForce(Particle* p) {
	return p->getMass() * _magnitude;
}