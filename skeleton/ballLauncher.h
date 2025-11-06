#pragma once
#include "uniformParticleGenerator.h"
class BallLauncher: public UniformParticleGenerator
{
public:
	BallLauncher(Vector3 particleSource, Vector3 vel, physx::PxShape* shape, double lifeTime, double lifeDistance, double mass, Vector4 color, Vector3 velVar, Vector4 colorVar);
};

