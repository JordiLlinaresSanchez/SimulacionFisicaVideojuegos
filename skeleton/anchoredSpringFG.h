#pragma once
#include "springForceGenerator.h"
class AnchoredSpringFG : public SpringForceGenerator
{
protected:
	Particle* _square;
public:
	AnchoredSpringFG(double k, double restingLength, Vector3 pos, physx::PxShape* shape, Vector4 color = Vector4(1.0, 1.0, 1.0, 1.0));
	
	void atachToRoot(Particle* part);
};

