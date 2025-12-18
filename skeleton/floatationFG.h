#pragma once
#include "forceGenerator.h"
#include "particle.h"
class FloatationFG: public ForceGenerator
{
protected:
	Particle* _waterTop;
	double _liquidDensity;
	double _height;
	double _volume;
	const double GRAVITY = 9.8;
public:
	FloatationFG(Particle* water, double h, double v, double d = 1000);
	~FloatationFG();

	void update(double t) override;
	bool checkCondition(Particle* particle) override;
	Vector3 applyForce(Particle* particle) override;
	bool checkCondition(physx::PxRigidDynamic* a) override;
	Vector3 applyForce(physx::PxRigidDynamic* a) override;

	inline void setDensity(double d) { _liquidDensity = d; }
};

