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
	Vector3 relativePos = _atached[particle]->getPos() - particle->getPos();

	double lenght = relativePos.normalize();
	double deltaX = lenght - _restingLength;

	return relativePos * deltaX * _k;
}

void 
SpringForceGenerator::asignParticles(Particle* up, Particle* down) {
	_atached[down] = up;
}
