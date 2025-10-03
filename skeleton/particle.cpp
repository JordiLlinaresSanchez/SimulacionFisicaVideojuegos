#include "particle.h"
#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>
#include <math.h>
using namespace physx;

Particle::Particle(Vector3 pos, Vector3 vel, Vector3 accel, double dumping, PxShape* shape, Vector4 color = Vector4(1.0,1.0,1.0,1.0)) : _accel(accel), _vel(vel), _dumping(dumping) {
	_pose = physx::PxTransform(pos);
	_renderItem = new RenderItem(shape, &_pose, color);
}
Particle::~Particle(){
	DeregisterRenderItem(_renderItem);
	delete _renderItem;
}

void Particle::integrate(double t){
	_vel += _accel * t;
	_pose.p += t * _vel;

	_vel *= pow(_dumping, t);
}