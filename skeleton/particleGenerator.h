#pragma once
#include "PxPhysicsAPI.h"
#include "core.hpp"

class Particle;

struct ParticleDT {
	Particle* particle;
	Vector3 origin;
	double lifeDistance;
	double lifeTime;
};

class ParticleGenerator
{
protected:
	physx::PxShape* _shape;
	Vector3 _particleSource, _velocity, _acceleration;
	Vector4 _color;
	double _lifeTime, _lifeDistance, _mass, _dumping, _genProb;
	int _partsPerFrame;

public:
	ParticleGenerator(Vector3 particleSource, Vector3 vel, Vector3 accel, physx::PxShape* shape, double lifeTime, double lifeDistance, double dumping, Vector4 color, int partsPerFrame, double genProb);
	virtual std::vector<ParticleDT> generateParticle()=0;

	inline void setParticleSource(Vector3 pSource) { _particleSource = pSource; }
	inline void setVelocity(Vector3 vel) { _velocity = vel; }
	inline void setLifeTime(double lifeT) { _lifeTime = lifeT; }
	inline void setGenProb(double genProb) { _genProb = genProb; }

	inline Vector3 setParticleSource() { return _particleSource; }
	inline Vector3 setVelocity() { return _velocity; }
	inline double setLifeTime() { return _lifeTime; }
	inline double setGenProb() { return _genProb; }
};

