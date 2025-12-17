#pragma once
#include "PxPhysicsAPI.h"
#include "core.hpp"
#include "RenderUtils.hpp"

struct SolidDT {
	physx::PxRigidActor* solid;
	RenderItem* ri;
	Vector3 origin;
	double lifeDistance;
	double lifeTime;
};

class SolidGenerator
{
protected:
	physx::PxShape* _shape;
	Vector3 _source, _velocity;
	Vector4 _color;
	double _lifeTime, _lifeDistance, _mass, _dumping, _genProb;
	int _partsPerFrame;
	bool _generate;

public:
	SolidGenerator(const Vector3& source, const Vector3& vel, physx::PxShape* shape, double lifeTime, double lifeDistance, double mass = 1.0, double genProb = 1.0, const Vector4& color = Vector4(1.0), int partsPerFrame = 1);
	~SolidGenerator();
	virtual std::vector<SolidDT> generate(physx::PxScene* scene) = 0;

	void setSource(Vector3 source);
	void setVelocity(Vector3 vel);
	inline void setLifeTime(double lifeT) { _lifeTime = lifeT; }
	inline void setGenProb(double genProb) { _genProb = genProb; }
	inline void setGenerate(bool generate) { _generate = generate; }

	inline Vector3 getSource() { return _source; }
	inline Vector3 getVelocity() { return _velocity; }
	inline double getLifeTime() { return _lifeTime; }
	inline double getGenProb() { return _genProb; }
	inline bool getGenerate() { return _generate; }


};



