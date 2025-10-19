#include "uniformParticleGenerator.h"
#include "particle.h"

UniformParticleGenerator::UniformParticleGenerator(Vector3 particleSource, Vector3 vel, Vector3 accel, physx::PxShape* shape,
	double lifeTime, double lifeDistance, double dumping, Vector4 color, int partsPerFrame, double genProb, Vector3 sourceVar,
	Vector3 velVar, double lifeVar, double distanceVar, Vector4 colorVar) : _velocityVar(sourceVar), _particleSourceVar(velVar),
	_lifeTimeVar(lifeVar), _lifeDistanceVar(distanceVar), _colorVar(colorVar),
	ParticleGenerator(particleSource, vel, accel, shape, lifeTime, lifeDistance, dumping, color, partsPerFrame, genProb) {}

std::vector<ParticleDT>
UniformParticleGenerator::generateParticle() {
	std::vector<ParticleDT> particles(0);
	for (int i = 0; i < _partsPerFrame; i++) {
		if (abs(_u(_mt)) > _genProb) continue;
		ParticleDT particle;
		particle.lifeDistance = _lifeDistance + _u(_mt) * _lifeDistanceVar;
		particle.lifeTime = _lifeTime + _u(_mt) * _lifeTimeVar;
		Vector3 pSource = Vector3(_particleSource.x + _u(_mt) * _particleSourceVar.x, _particleSource.y + _u(_mt) * _particleSourceVar.y, _particleSource.z + _u(_mt) * _particleSourceVar.z),
			vel = Vector3(_velocity.x + _u(_mt) * _velocityVar.x, _velocity.y + _u(_mt) * _velocityVar.y, _velocity.z + _u(_mt) * _velocityVar.z);
		particle.origin = pSource;
		Vector4 color = Vector4(_color.x + _u(_mt) * _colorVar.x, _color.y + _u(_mt) * _colorVar.y, _color.z + _u(_mt) * _colorVar.z, _color.w + _u(_mt) * _colorVar.w);
		particle.particle = new Particle(pSource, vel, _acceleration, _dumping, _shape, color);
		particles.push_back(particle);
	}
	return particles;
}