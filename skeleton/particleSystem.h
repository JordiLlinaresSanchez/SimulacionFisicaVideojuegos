#pragma once

#include "PxPhysicsAPI.h"
#include "core.hpp"

class Particle;
class ParticleSystem
{
private:
	Vector3 _particleSource;
	Vector3 _direction;
	std::vector<Particle*> _particles;
	double _lifeTime;
	double _lifeDistance;
	double _speed;

public:
	ParticleSystem(Vector3 particleSource, Vector3 dir, double lifeTime, double lifeDistance, double speed);


};

