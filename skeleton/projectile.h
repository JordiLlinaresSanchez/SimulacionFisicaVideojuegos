#pragma once
#include <PxPhysicsAPI.h>
#include "core.hpp"
#include "particle.h"

enum ProjType {
	GunBullet,
	CanonBall,
	TankBullet,
	None
};

class Projectile: public Particle
{
private:
	double _mass;
	double _simMass;
public:
	Projectile(Vector3 pos, Vector3 vel, Vector3 accel, double mass, double dumping, physx::PxShape* shape, ProjType proj, Vector4 color);
	Vector3 getForce();
};

