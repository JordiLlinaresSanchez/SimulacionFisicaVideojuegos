#pragma once
#include "windGenerator.h"
class HurricaneGenerator : public WindGenerator
{
private:
	double _windMagnitude, _height, _spinMagnitude;
public:
	//genera un area de viento en una esfera
	HurricaneGenerator(double windMagnitude, double height, double spinMagnitude, Vector3 center, double radius);

	Vector3 applyForce(Particle* particle) override;
};

