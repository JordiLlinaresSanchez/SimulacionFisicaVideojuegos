#include "windGenerator.h"
#include "particle.h"

WindGenerator::WindGenerator(Vector3 windVel, Vector3 initPos, Vector3 endPos): _initPos(initPos), _endPos(endPos), _isSphere(false), _radius(0), ForceGenerator(windVel) {}

WindGenerator::WindGenerator(Vector3 windVel, Vector3 initPos, double radius) : _initPos(initPos), _endPos(), _isSphere(true), _radius(radius), ForceGenerator(windVel) {}

void 
WindGenerator::update(double t) {}

bool 
WindGenerator::checkCondition(Particle* particle) {
	if (!_isSphere)
		return particle->getPos().x <= _initPos.x && particle->getPos().y <= _initPos.y && particle->getPos().z <= _initPos.z &&
		particle->getPos().x >= _endPos.x && particle->getPos().y >= _endPos.y && particle->getPos().z >= _endPos.z && canAply;
	else
		return (particle->getPos() - _initPos).magnitude() <= _radius && canAply;
}

Vector3 
WindGenerator::applyForce(Particle* particle) {
	return 0.5 * (_magnitude - particle->getVel()) ;
}

bool
WindGenerator::checkCondition(physx::PxRigidDynamic* solid) {
	if (!_isSphere)
		return solid->getGlobalPose().p.x <= _initPos.x && solid->getGlobalPose().p.y <= _initPos.y && solid->getGlobalPose().p.z <= _initPos.z &&
		solid->getGlobalPose().p.x >= _endPos.x && solid->getGlobalPose().p.y >= _endPos.y && solid->getGlobalPose().p.z >= _endPos.z;
	else
		return (solid->getGlobalPose().p - _initPos).magnitude() <= _radius;
}

Vector3
WindGenerator::applyForce(physx::PxRigidDynamic* solid) {
	return 0.5 * (_magnitude - solid->getLinearVelocity());
}