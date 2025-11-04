#pragma once
#include "forceGenerator.h"
class ExplosionGenerator : public ForceGenerator
{
protected:
	double _radius, _tau, _elapsedTime, _intensity;
	Vector3 _initPos;

public:
	ExplosionGenerator(Vector3 pos, double radius, double intensity, double tau);

	void update(double t) override;
	bool checkCondition(const Particle* particle) override;
	virtual Vector3 applyForce(Particle* particle) override;
};

