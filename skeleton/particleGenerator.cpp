#include "particleGenerator.h"
#include "particle.h"

ParticleGenerator::ParticleGenerator(Vector3 particleSource, Vector3 vel, Vector3 accel, physx::PxShape* shape, double lifeTime, double lifeDistance, double dumping, Vector4 color, int partsPerFrame, double genProb)
	:_particleSource(particleSource), _velocity(vel), _acceleration(accel), _shape(shape), _lifeTime(lifeTime), _lifeDistance(lifeDistance), _dumping(dumping), _color(color), _partsPerFrame(partsPerFrame), _genProb(genProb){}
