#include "flotationFG.h"

FlotationFG::FlotationFG(Particle* water, double h, double v, double d) : _liquidDensity(d), _height(h), _volume(v), _waterTop(water), ForceGenerator() {}

FlotationFG::~FlotationFG() {
	delete _waterTop;
}

void 
FlotationFG::update(double t) {

}

bool 
FlotationFG::checkCondition(Particle* particle){
	return _waterTop->getPos().y - particle->getPos().y >= _height * 0.5;
}

Vector3 
FlotationFG::applyForce(Particle* particle){
	double h = particle->getPos().y;
	double h1 = _waterTop->getPos().y;

	double immersed = 0.0;

	if (h1 - h > _height * 0.5) immersed = 1.0;
	else immersed = (h1 - h) / _height + 0.5;

	return Vector3(0.0, _liquidDensity * _volume * immersed * GRAVITY, 0.0);
}