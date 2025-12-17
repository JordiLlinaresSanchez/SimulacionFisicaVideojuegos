#pragma once
#include "solidGenerator.h"

class RenderItem;
class SolidSystem
{
protected:
	std::vector<SolidDT> _solids;
	std::vector<SolidGenerator*> _solidGenerators;
	//std::vector<ForceGenerator*> _forceGenerators;
	physx::PxScene* _gScene = NULL;
	physx::PxPhysics* _gPhysics = NULL;

	void integrateSolids(double t);
	void deleteSolid(double t);
public:
	SolidSystem(physx::PxScene* scene, physx::PxPhysics* physics);
	~SolidSystem();

	void generateSolid();
	void addSolid(physx::PxRigidActor* solid, Vector3& origin, physx::PxShape* shape, Vector4 color, double lifeDistance, double lifeTime = std::numeric_limits<double>::infinity());
	void addSolidGenerator(SolidGenerator* particleGenerator);
	//void addForceGenerator(ForceGenerator* fg);
	void update(double t);
	
};

