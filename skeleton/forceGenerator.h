#pragma once

#include "PxPhysicsAPI.h"
#include "core.hpp"

class Particle;
class ForceGenerator
{
protected:
	Vector3 _magnitude;
	double _elapsedTime;
	bool canAply;
public:
	ForceGenerator(Vector3 force = Vector3(0.0));
	Vector3 getForce() const{ return _magnitude; }
	inline void setForce(Vector3 force) { _magnitude = force; }
	inline void setTimer(double time) { _elapsedTime = time; }
	inline void setCanAply(bool aply) { canAply = aply; }
	inline bool getCanAply() { return canAply; }
	virtual void update(double t) = 0;
	virtual bool checkCondition(Particle* particle) = 0;
	virtual bool checkCondition(physx::PxRigidDynamic* solid) = 0;
	virtual Vector3 applyForce(Particle* particle) = 0;
	virtual Vector3 applyForce(physx::PxRigidDynamic* solid) = 0;
};

