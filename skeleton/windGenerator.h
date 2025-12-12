#pragma once
#include "forceGenerator.h"
class WindGenerator : public ForceGenerator
{
protected:
	Vector3 _initPos, _endPos;
	bool _isSphere;
	double _radius;
public:
	//genera un area de viento en un paralelepipedo
	WindGenerator(Vector3 windVel, Vector3 initPos, Vector3 endPos);
	//genera un area de viento en una esfera
	WindGenerator(Vector3 windVel, Vector3 center, double radius);
	void update(double t) override;
	bool checkCondition(Particle* particle) override;
	virtual Vector3 applyForce(Particle* particle) override;
};

