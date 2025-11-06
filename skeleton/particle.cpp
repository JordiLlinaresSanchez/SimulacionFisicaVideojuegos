#include "particle.h"
#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>
#include <math.h>
using namespace physx;

Particle::Particle(Vector3 pos, Vector3 vel, Vector3 accel, double mass, double dumping, PxShape* shape, Vector4 color = Vector4(1.0,1.0,1.0,1.0)) : _accel(accel), _vel(vel), _dumping(dumping), _mass(mass) {
	_pose = physx::PxTransform(pos);
	if (shape != NULL) _renderItem = new RenderItem(shape, &_pose, color);
	else _renderItem = NULL;
}

Particle::Particle(PxTransform& pos, Vector3 vel, Vector3 accel, double mass, double dumping, PxShape* shape, Vector4 color = Vector4(1.0, 1.0, 1.0, 1.0)) : _accel(accel), _vel(vel), _dumping(dumping), _mass(mass) {
	_pose = physx::PxTransform(pos);
	if (shape != NULL) _renderItem = new RenderItem(shape, &_pose, color);
	else _renderItem = NULL;
}

Particle::~Particle(){
	DeregisterRenderItem(_renderItem);
	delete _renderItem;
}

void 
Particle::integrate(double t){
	_vel += _accel * t;
	_pose.p += t * _vel;

	_vel *= pow(_dumping, t);
}

Vector3
Particle::getPos()const { return _pose.p; }

Vector3
Particle::getAccel()const { return _accel; }

Vector3
Particle::getVel()const { return _vel; }

double
Particle::getMass()const { return _mass; }

void
Particle::setAccel(Vector3 accel) { _accel = accel; }