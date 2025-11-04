#include "uniformParticleGenerator.h"
#include "particle.h"

UniformParticleGenerator::UniformParticleGenerator(Vector3 particleSource, Vector3 vel, Vector3 accel, physx::PxShape* shape,
	double lifeTime, double lifeDistance, double mass, double dumping, Vector4 color, int partsPerFrame, double genProb, Vector3 sourceVar,
	Vector3 velVar, double lifeVar, double distanceVar, double massVar, Vector4 colorVar) : _velocityVar(velVar), _particleSourceVar(sourceVar),
	_lifeTimeVar(lifeVar), _lifeDistanceVar(distanceVar), _massVar(massVar), _colorVar(colorVar),
	ParticleGenerator(particleSource, vel, accel, shape, lifeTime, lifeDistance, mass, dumping, color, partsPerFrame, genProb) {}

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
		double mass = abs(_mass + _u(_mt) * _massVar);
		particle.particle = new Particle(pSource, vel, _acceleration, _dumping, mass, _shape, color);
		particles.push_back(particle);
	}
	return particles;
}