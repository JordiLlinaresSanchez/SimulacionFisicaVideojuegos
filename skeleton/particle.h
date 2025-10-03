#pragma once
#include "PxPhysicsAPI.h"
#include "core.hpp"

class RenderItem;
class Particle
{
private:
	RenderItem* _renderItem;
	physx::PxTransform _pose;
	Vector3 _vel;
	Vector3 _accel;
	double _dumping;
public:
	Particle(Vector3 pos, Vector3 vel, Vector3 accel, double dumping, physx::PxShape* shape, Vector4 color);
	~Particle();

	void integrate(double t);
};

