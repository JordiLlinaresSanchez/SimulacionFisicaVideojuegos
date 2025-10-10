#include "projectile.h"
#include <math.h>
using namespace physx;

Projectile::Projectile(Vector3 pos, Vector3 vel, Vector3 accel, double mass, double dumping, PxShape* shape, ProjType proj = None,  Vector4 color = Vector4(1.0, 1.0, 1.0, 1.0)) :
	_mass(mass), Particle(pos, vel, accel, dumping, shape, color){
	switch(proj)
	{
	case GunBullet:
		Particle::_accel /= 5;
		Particle::_vel /= 5;
		_mass *= pow(vel.magnitude() / _vel.magnitude(), 2);
		break; 
	case CanonBall:
		Particle::_accel /= 4;
		Particle::_vel /= 4;
		_mass *= pow(vel.magnitude() / _vel.magnitude(), 2);
		break;
	case TankBullet:
		Particle::_accel /= 6;
		Particle::_vel /= 6;
		_mass *= pow(vel.magnitude() / _vel.magnitude(), 2);
		break;
	default:
		break;
	}
	
}

Vector3 Projectile::getForce() {

	return _mass * _accel;
}