#pragma once
#include <PxPhysicsAPI.h>
#include "core.hpp"
#include "particle.h"

class Projectile: public Particle
{
private:
	double _mass;
public:
	Projectile(Vector3 pos, Vector3 vel, Vector3 accel, double mass, double dumping, physx::PxShape* shape, Vector4 color);
	Vector3 getForce();
};

