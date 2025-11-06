#pragma once
#include "particle.h"
class Pin : public Particle
{
protected:
	RenderItem* _head;
	physx::PxTransform* _headPose;
public:
	Pin(physx::PxTransform& pose, Vector3 vel, Vector3 accel, double mass, double dumping);
	~Pin();

	void integrate(double t) override;
};

