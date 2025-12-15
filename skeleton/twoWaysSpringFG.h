#pragma once
#include "springForceGenerator.h"
class TwoWaysSpringFG : public SpringForceGenerator
{
public:
	TwoWaysSpringFG(double k, double restingLength);
	void asignParticles(Particle* part, Particle* root) override;
};

