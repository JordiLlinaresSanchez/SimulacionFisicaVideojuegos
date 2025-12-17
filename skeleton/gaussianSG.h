#pragma once
#include "solidGenerator.h"
#include <random>

class GaussianSG : public SolidGenerator
{
private:
	Vector3 _velocityVar, _sourceVar;
	Vector4 _colorVar;
	double _lifeTimeVar, _lifeDistanceVar, _massVar;
	std::mt19937 _mt;
	std::normal_distribution<double> _u{ 0.0 , 1.0 };
public:
	GaussianSG(const Vector3& sSource, const Vector3& vel, physx::PxShape* shape, double lifeTime, double lifeDistance, double mass, double genProb = 1.0, const Vector4& color = const Vector4(1.0), int partsPerFrame = 1,
		const Vector3& sourceVar = const Vector3(0.0), const Vector3& velVar = const Vector3(0.0), double lifeVar = 0.0, double distanceVar = 0.0, double massVar = 0.0, const Vector4& colorVar = const Vector4(0.0));
	std::vector<SolidDT> generate(physx::PxScene* scene) override;
};

