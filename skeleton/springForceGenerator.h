#pragma once
#include "forceGenerator.h"
#include "unordered_map"

class SpringForceGenerator : public ForceGenerator
{
protected:
	double _k;
	double _restingLength;
	std::unordered_map<Particle*, Particle*> _atached;
public:
	SpringForceGenerator(double k, double _restingLength);
	~SpringForceGenerator();

	void update(double t) override;
	bool checkCondition(Particle* particle) override;
	Vector3 applyForce(Particle* particle) override;
	void asignParticles(Particle* up, Particle* down);
};

