#include "explosionGenerator.h"
#include "particle.h"
#include "cmath"

ExplosionGenerator::ExplosionGenerator(Vector3 pos, double radius, double intensity, double tau): 
	_radius(radius), _intensity(intensity), _tau(tau), _elapsedTime(0), _initPos(pos), ForceGenerator(Vector3()){}

void 
ExplosionGenerator::update(double t) {
	_elapsedTime += t;
}

bool 
ExplosionGenerator::checkCondition(const Particle* particle) {
	return (particle->getPos() - _initPos).magnitude() <= _radius;
}

Vector3 
ExplosionGenerator::applyForce(Particle* particle) {
	return (_intensity / (_radius * _radius)) * (particle->getPos() - _initPos) * exp(-_elapsedTime / _tau);
}