#pragma once
#include "gravityForceGenerator.h"
class LocatedGravity : public GravityForceGenerator
{
private: 
	Vector3 _initPos, _endPos;
public:
	LocatedGravity(Vector3 force, Vector3 initPos, Vector3 endPos);

	bool checkCondition(const Particle* particle) override;
};

