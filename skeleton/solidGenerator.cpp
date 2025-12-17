#include "solidGenerator.h"

SolidGenerator::SolidGenerator(const Vector3& source, const Vector3& vel, physx::PxShape* shape, double lifeTime, double lifeDistance, double mass, double genProb, const Vector4& color, int partsPerFrame)
	:_source(source), _velocity(vel), _shape(shape), _lifeTime(lifeTime), _lifeDistance(lifeDistance), _mass(mass), _color(color), _partsPerFrame(partsPerFrame), _genProb(genProb), _generate(true) {}

SolidGenerator::~SolidGenerator() {
	_shape->release();
}

void 
SolidGenerator::setSource(Vector3 source) { _source = source; }

void 
SolidGenerator::setVelocity(Vector3 vel) { _velocity = vel; }