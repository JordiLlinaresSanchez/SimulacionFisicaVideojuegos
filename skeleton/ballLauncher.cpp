#include "ballLauncher.h"

BallLauncher::BallLauncher(Vector3 particleSource, Vector3 vel, physx::PxShape* shape, double lifeTime, double lifeDistance, double mass, Vector4 color, Vector3 velVar, Vector4 colorVar) : 
	UniformParticleGenerator(particleSource,vel, Vector3(0.0), shape, lifeTime, lifeDistance, mass, 0.9, color, 1, 1.0, Vector3(0.0), velVar, 0.0, 0.0, 0.0, colorVar) {}