#include "particleGenerator.h"
#include "particle.h"

ParticleGenerator::ParticleGenerator(const Vector3& particleSource, const Vector3& vel, const Vector3& accel, physx::PxShape* shape, double lifeTime, double lifeDistance, double mass, double dumping, const Vector4& color, int partsPerFrame, double genProb)
	:_particleSource(particleSource), _velocity(vel), _acceleration(accel), _shape(shape), _lifeTime(lifeTime), _lifeDistance(lifeDistance), _mass(mass), _dumping(dumping), _color(color), _partsPerFrame(partsPerFrame), _genProb(genProb), _generate(true){}

ParticleGenerator::~ParticleGenerator() {
	_shape->release();
}