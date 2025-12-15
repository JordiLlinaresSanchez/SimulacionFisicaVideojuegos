#pragma once
#include "solidGenerator.h"

class SolidSystem
{
protected:
	std::vector<SolidDT> _solids;
	std::vector<SolidGenerator*> _solidGenerators;
	//std::vector<ForceGenerator*> _forceGenerators;

	void integrateSolids(double t);
	void deleteSolids(double t);
public:
	SolidSystem(std::vector<SolidGenerator*> solidGenerators = std::vector<SolidGenerator*>(), std::vector<SolidDT> solids = std::vector<SolidDT>()/*, std::vector<ForceGenerator*> forces = std::vector<ForceGenerator*>()*/);
	~SolidSystem();

	void generateSolid();
	void addSolid(physx::PxRigidActor* solid, Vector3 origin, double lifeDistance, double lifeTime = std::numeric_limits<double>::infinity());
	void addSolid(SolidDT part);
	void addSolidGenerator(SolidGenerator* particleGenerator);
	//void addForceGenerator(ForceGenerator* fg);
	virtual void update(double t);
};

