#include "projectile.h"
#include "RenderUtils.hpp"
#include <math.h>
using namespace physx;

Projectile::Projectile(Vector3 pos, Vector3 vel, Vector3 accel, double mass, double dumping, PxShape* shape, ProjType proj = None,  Vector4 color = Vector4(1.0, 1.0, 1.0, 1.0)) 
	: _simMass(0), Particle(pos, vel, accel, dumping, mass, shape, color){

	switch(proj)
	{
	case GunBullet:
		Particle::_accel /= 3;
		Particle::_vel /= 3;
		_mass *= pow(vel.magnitude() / _vel.magnitude(), 2);
		_renderItem->color = Vector4(0.7, 0.7, 0.7, 1);
		break;
	case CanonBall:
		Particle::_accel /= 2;
		Particle::_vel /= 2;
		_mass *= pow(vel.magnitude() / _vel.magnitude(), 2);
		_renderItem->color = Vector4(0.0, 0.2, 0.7, 1);
		break;
	case TankBullet:
		Particle::_accel /= 3;
		Particle::_vel /= 3;
		_mass *= pow(vel.magnitude() / _vel.magnitude(), 2);
		_renderItem->color = Vector4(0.7, 0.1, 0.1, 1);
		break;
	default:
		break;
	}
	
}

Projectile::Projectile(Vector3 pos, Vector3 dir, Vector3 accel, double mass, double dumping, ProjType proj)
	: _simMass(0), Particle(pos, dir, accel, dumping, mass, CreateShape(PxSphereGeometry(1.0f)), Vector4()) {
	Vector3 vel = Vector3();
	switch (proj)
	{
	case GunBullet:
		vel = dir.getNormalized() * 330;
		Particle::_accel /= 3;
		Particle::_vel = vel / 3;
		_mass *= pow(vel.magnitude() / _vel.magnitude(), 2);
		_renderItem->color = Vector4(0.7, 0.7, 0.7, 1);
		_renderItem->shape->setGeometry(PxSphereGeometry(3.0f));
		break;
	case CanonBall:
		vel = dir.getNormalized() * 250;
		Particle::_accel /= 2;
		Particle::_vel = vel / 2;
		_mass *= pow(vel.magnitude() / _vel.magnitude(), 2);
		_renderItem->color = Vector4(0.0, 0.2, 0.7, 1);
		_renderItem->shape->setGeometry(PxSphereGeometry(8.0f));

		break;
	case TankBullet:
		vel = dir.getNormalized() * 1800;
		Particle::_accel /= 3;
		Particle::_vel = vel / 3;
		_mass *= pow(vel.magnitude() / _vel.magnitude(), 2);
		_renderItem->color = Vector4(0.7, 0.1, 0.1, 1);
		_renderItem->shape->setGeometry(PxCapsuleGeometry(5.0, 12.0));
		break;
	default:
		break;
	}
}

Projectile::Projectile() : Particle(Vector3(), Vector3(), Vector3(), 1, 0, CreateShape(PxSphereGeometry(8.0f)), Vector4()){

}


Vector3 Projectile::getForce() {

	return _mass * _accel;
}