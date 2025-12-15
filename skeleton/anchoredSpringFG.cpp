#include "anchoredSpringFG.h"
#include "RenderUtils.hpp"
#include "particle.h"
#include <PxPhysicsAPI.h>

AnchoredSpringFG::AnchoredSpringFG(double k, double restingLength, Vector3 pos, physx::PxShape* shape, Vector4 color) : SpringForceGenerator(k, restingLength){
	_square = new Particle(pos, Vector3(0.0), Vector3(0.0), 1e6, 0.0, shape, color);
}

void 
AnchoredSpringFG::atachToRoot(Particle* part) {
	_atached[part].push_back(_square);
}