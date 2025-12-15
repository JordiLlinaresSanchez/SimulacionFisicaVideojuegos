#include "floatationFG.h"

FloatationFG::FloatationFG(Particle* water, double h, double v, double d) : _liquidDensity(d), _height(h), _volume(v), _waterTop(water), ForceGenerator() {}

FloatationFG::~FloatationFG() {
	delete _waterTop;
}

void 
FloatationFG::update(double t) {

}

bool 
FloatationFG::checkCondition(Particle* particle){
	return true;//_waterTop->getPos().y - particle->getPos().y >= _height * 0.5;
}

Vector3 
FloatationFG::applyForce(Particle* particle){
	double h = particle->getPos().y;
	double h0 = _waterTop->getPos().y;

	double immersed = 0.0;
	if (h - h0 > _height * 0.5) immersed = 0.0;
	else if (h0 - h > _height * 0.5) immersed = 1.0;
	else immersed = (h0 - h) / _height + 0.5;

	return Vector3(0.0, _liquidDensity * _volume * immersed * GRAVITY, 0.0);
}