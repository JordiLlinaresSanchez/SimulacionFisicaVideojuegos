#pragma once
#include "particleGenerator.h"
#include <random>

class UniformParticleGenerator :public ParticleGenerator
{
private:
	Vector3 _velocityVar, _particleSourceVar;
	Vector4 _colorVar;
	double _lifeTimeVar, _lifeDistanceVar, _massVar;
	std::mt19937 _mt;
	std::uniform_real_distribution<double> _u{ 0.0 , 1.0 };
public:
	UniformParticleGenerator(const Vector3& particleSource, const Vector3& vel, const Vector3& accel, physx::PxShape* shape, double lifeTime, double lifeDistance, double mass, double dumping,
		const Vector4& color, int partsPerFrame, double genProb, const Vector3& sourceVar, const Vector3& velVar, double lifeVar, double distanceVar, double massVar, const Vector4& colorVar);
	virtual std::vector<ParticleDT> generateParticle() override;
};

