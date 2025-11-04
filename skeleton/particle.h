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
	double _dumping, _mass;
public:
	Particle(Vector3 pos, Vector3 vel, Vector3 accel, double mass, double dumping, physx::PxShape* shape, Vector4 color);
	~Particle();


	Vector3 getPos()const;
	Vector3 getAccel()const;
	Vector3 getVel()const;
	double getMass()const;

	void setAccel(Vector3 accel);

	virtual void integrate(double t);
};

