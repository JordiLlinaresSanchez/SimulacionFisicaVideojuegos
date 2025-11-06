#include "locatedGravity.h"
#include "particle.h"

LocatedGravity::LocatedGravity(Vector3 force, Vector3 initPos, Vector3 endPos): _initPos(initPos), _endPos(endPos), GravityForceGenerator(force){}

bool 
LocatedGravity::checkCondition(const Particle* particle) {
	return particle->getPos().x <= _initPos.x && particle->getPos().y <= _initPos.y && particle->getPos().z <= _initPos.z &&
		particle->getPos().x >= _endPos.x && particle->getPos().y >= _endPos.y && particle->getPos().z >= _endPos.z;
}
