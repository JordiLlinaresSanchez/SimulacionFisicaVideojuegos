#pragma once
#include "forceGenerator.h"
class GravityForceGenerator : public ForceGenerator
{
public:
	GravityForceGenerator(Vector3 force);
	void update(double t) override;
	bool checkCondition(const Particle* particle) override;
	Vector3 applyForce(Particle* particle) override;
};

