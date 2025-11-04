#include "hurricaneGenerator.h"
#include "particle.h"

HurricaneGenerator::HurricaneGenerator(double windMagnitude, double height, double spinMagnitude, Vector3 initPos, double radius) :
	_windMagnitude(windMagnitude), _height(height), _spinMagnitude(spinMagnitude), WindGenerator(Vector3(), initPos, radius) {}

Vector3
HurricaneGenerator::applyForce(Particle* p) {
	return Vector3(-(p->getPos().z-_initPos.z) - _spinMagnitude*(p->getPos().x - _initPos.x), _height - (p->getPos().y - _initPos.y), (p->getPos().x - _initPos.x) - _spinMagnitude*(p->getPos().z - _initPos.z)) * _windMagnitude;
}