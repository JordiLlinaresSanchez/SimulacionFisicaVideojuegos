#include "gaussianParticleGenerator.h"
#include "particle.h"

GaussianParticleGenerator::GaussianParticleGenerator(Vector3 particleSource, Vector3 vel, Vector3 accel, physx::PxShape* shape, 
	double lifeTime, double lifeDistance, double mass, double dumping, Vector4 color, double genProb, Vector3 sourceVar, 
	Vector3 velVar, double lifeVar, double distanceVar, Vector4 colorVar) : _velocityVar(sourceVar), _particleSourceVar(velVar), 
	_lifeTimeVar(lifeVar), _lifeDistanceVar(distanceVar), _colorVar(colorVar),
	ParticleGenerator(particleSource, vel, accel, shape, lifeTime, lifeDistance, mass, dumping, color, genProb) {}

std::vector<ParticleDT>
GaussianParticleGenerator::generateParticle(int particlesNumber) {
	std::vector<ParticleDT> particles(0);
	for (int i = 0; i < particlesNumber; i++) {
		if (_d(_mt) > _genProb) continue;
		ParticleDT particle;
		particle.lifeDistance = _lifeDistance + _d(_mt) * _lifeDistanceVar;
		particle.lifeTime = _lifeTime + _d(_mt) * _lifeTimeVar;
		Vector3 pSource = Vector3(_particleSource.x + _d(_mt) * _particleSourceVar.x, _particleSource.y + _d(_mt) * _particleSourceVar.y, _particleSource.z + _d(_mt) * _particleSourceVar.z),
			vel = Vector3(_velocity.x + _d(_mt) * _velocityVar.x, _velocity.y + _d(_mt) * _velocityVar.y, _velocity.z + _d(_mt) * _velocityVar.z);
		particle.origin = pSource;
		Vector4 color = Vector4(_color.x + _d(_mt) * _colorVar.x, _color.y + _d(_mt) * _colorVar.y, _color.z + _d(_mt) * _colorVar.z, _color.w + _d(_mt) * _colorVar.w);
		particle.particle = new Particle(pSource, vel, _acceleration, _dumping, _shape, _color + _d(_mt) * _colorVar);
		particles.push_back(particle);
	}
	return particles;
}