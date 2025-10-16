#include "gaussianParticleGenerator.h"
#include "particle.h"

GaussianParticleGenerator::GaussianParticleGenerator(Vector3 particleSource, Vector3 vel, Vector3 accel, physx::PxShape* shape, double lifeTime, double lifeDistance, double mass, 
													 double dumping, Vector4 color, double genProb, Vector3 sourceVar, Vector3 velVar, double lifeVar, double distanceVar, Vector4 colorVar) : _velocityVar(sourceVar),
													 _particleSourceVar(velVar), _lifeTimeVar(lifeVar), _lifeDistanceVar(distanceVar),
													 ParticleGenerator(particleSource, vel, accel, shape, lifeTime, lifeDistance, mass, dumping, color, genProb) {}

std::vector<ParticleDT>
GaussianParticleGenerator::generateParticle(int particlesNumber) {
	std::vector<ParticleDT> particles(0);
	for (int i = 0; i < particlesNumber; i++) {
		if (_d(_mt) > _genProb) continue;
		ParticleDT particle;
		particle.lifeDistance = _lifeDistance + _d(_mt) * _lifeDistanceVar;
		particle.lifeTime = _lifeTime + _d(_mt) * _lifeTimeVar;
		particle.particle = new Particle(_particleSource + _d(_mt) * _particleSourceVar, _velocity + _d(_mt) * _velocityVar, _acceleration, _dumping, _shape, _color + _d(_mt) * _colorVar);
		particles.push_back(particle);
	}
	return particles;
}