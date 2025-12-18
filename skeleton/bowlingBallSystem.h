#pragma once
#include "solidSystem.h"
class BowlingBallSystem : public SolidSystem
{
public:
	BowlingBallSystem(physx::PxScene* scene, physx::PxPhysics* physics, int maxSolid = 500);
	~BowlingBallSystem();
	void update(double t) override;
};

