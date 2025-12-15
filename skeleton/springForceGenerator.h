#pragma once
#include "forceGenerator.h"
#include "unordered_map"

class SpringForceGenerator : public ForceGenerator
{
protected:
	double _k;
	double _restingLength;
	std::unordered_map<Particle*, std::vector<Particle*>> _atached;
public:
	SpringForceGenerator(double k, double restingLength);
	~SpringForceGenerator();

	void update(double t) override;
	bool checkCondition(Particle* particle) override;
	Vector3 applyForce(Particle* particle) override;
	virtual void asignParticles(Particle* part, Particle* root);
};

