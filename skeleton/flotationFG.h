#pragma once
#include "forceGenerator.h"
#include "particle.h"
class FlotationFG: public ForceGenerator
{
protected:
	Particle* _waterTop;
	double _liquidDensity;
	double _height;
	double _volume;
	const double GRAVITY = 9.8;
public:
	FlotationFG(Particle* water, double h, double v, double d = 1000);
	~FlotationFG();

	void update(double t) override;
	bool checkCondition(Particle* particle) override;
	Vector3 applyForce(Particle* particle) override;
};

