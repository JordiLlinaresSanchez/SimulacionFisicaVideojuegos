#pragma once
#include "solidGenerator.h"

class RenderItem;
class ForceGenerator;
class SolidSystem
{
protected:
	std::vector<SolidDT> _solids;
	std::vector<SolidGenerator*> _solidGenerators;
	std::vector<ForceGenerator*> _forceGenerators;
	physx::PxScene* _gScene = NULL;
	physx::PxPhysics* _gPhysics = NULL;
	int _maxSolids;

	void integrate(double t);
	void deleteSolid(double t);
public:
	SolidSystem(physx::PxScene* scene, physx::PxPhysics* physics, int maxSolid = 500);
	~SolidSystem();

	void generateSolid();
	void addSolid(Vector3& origin, physx::PxShape* shape, Vector4 color, double lifeDistance, double lifeTime = std::numeric_limits<double>::infinity(), Vector3 vel = Vector3(0));
	void addSolidGenerator(SolidGenerator* particleGenerator);
	void addForceGenerator(ForceGenerator* fg);
	virtual void update(double t);
	
};

