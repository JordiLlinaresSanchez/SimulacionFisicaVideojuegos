#pragma once

#include "PxPhysicsAPI.h"
#include "core.hpp"

class Particle;
class ForceGenerator
{
protected:
	Vector3 _pos, _force;
public:
	ForceGenerator(Vector3 pos, Vector3 force);
	Vector3 getForce() const{ return _force; }
	void setForce(Vector3 force) { _force = force; }
	virtual void update(double t) = 0;
	virtual bool checkCondition(const Particle* particle) = 0;
	virtual Vector3 applyForce(Particle* particle) = 0;
};

