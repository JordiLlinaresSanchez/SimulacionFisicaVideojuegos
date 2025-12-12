#include "pin.h"
#include "RenderUtils.hpp"
#include <PxPhysicsAPI.h>

using namespace physx;

Pin::Pin(PxTransform& pos, Vector3 vel, Vector3 accel, double mass, double dumping) : Particle(pos, vel, accel, mass, dumping, NULL, Vector4()) {

	PxShape* shape = CreateShape(PxCapsuleGeometry(0.08, 0.12));
	PxShape* headShape = CreateShape(PxCapsuleGeometry(0.04, 0.06));
	_renderItem = new RenderItem(shape, &_pose, Vector4(1.0, 1.0, 1.0, 1.0));
	_headPose = new PxTransform(_pose);
	_headPose->p += Vector3(0.0, 0.25, 0.0);
	_head = new RenderItem(headShape, _headPose, Vector4(1.0, 0.0, 0.0, 1.0));
}

Pin::~Pin() {
	_head->shape->release();
	DeregisterRenderItem(_head);
	delete _head;
	delete _headPose;
}

void Pin::integrate(double t){
	Particle::integrate(t);
	_headPose->p += t * _vel;

	_vel *= pow(_dumping, t);
}