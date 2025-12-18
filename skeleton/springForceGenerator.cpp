#include "springForceGenerator.h"
#include "particle.h"

SpringForceGenerator::SpringForceGenerator(double k, double restingLength) : _k(k), _restingLength(restingLength), ForceGenerator() {

}

SpringForceGenerator::~SpringForceGenerator() {
}

void 
SpringForceGenerator::update(double t){}

bool 
SpringForceGenerator::checkCondition(Particle* particle){ 
	return _atached.count(particle);
}

Vector3 
SpringForceGenerator::applyForce(Particle* particle){
	Vector3 force = Vector3(0.0);
	for (auto part : _atached[particle]) {
		Vector3 relativePos = part->getPos() - particle->getPos();

		double lenght = relativePos.normalize();
		double deltaX = lenght - _restingLength;

		force += relativePos * deltaX * _k;
	}
	

	return force;
}

void 
SpringForceGenerator::asignParticles(Particle* part, Particle* root) {
	_atached[part].push_back(root);
}

bool
SpringForceGenerator::checkCondition(physx::PxRigidDynamic* solid) {
	return _atachedSolid.count(solid);
}

Vector3
SpringForceGenerator::applyForce(physx::PxRigidDynamic* solid) {
	Vector3 force = Vector3(0.0);
	for (auto part : _atachedSolid[solid]) {
		Vector3 relativePos = part->getPos() - solid->getGlobalPose().p;

		double lenght = relativePos.normalize();
		double deltaX = lenght - _restingLength;

		force += relativePos * deltaX * _k;

	}

	return force;
}