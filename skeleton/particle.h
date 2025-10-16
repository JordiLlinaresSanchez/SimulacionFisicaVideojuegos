#pragma once
#include "PxPhysicsAPI.h"
#include "core.hpp"

class RenderItem;
class Particle
{
protected:
	RenderItem* _renderItem;
	physx::PxTransform _pose;
	Vector3 _vel, _accel;
	double _dumping;
public:
	Particle(Vector3 pos, Vector3 vel, Vector3 accel, double dumping, physx::PxShape* shape, Vector4 color);
	~Particle();

	virtual void integrate(double t);
};

