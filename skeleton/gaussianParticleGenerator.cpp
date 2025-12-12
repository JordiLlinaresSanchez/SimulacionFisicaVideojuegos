#include "gaussianParticleGenerator.h"
#include "particle.h"

GaussianParticleGenerator::GaussianParticleGenerator(const Vector3& particleSource, const Vector3& vel, const Vector3& accel, physx::PxShape* shape, 
	double lifeTime, double lifeDistance, double mass, double dumping, const Vector4& color, int partsPerFrame, double genProb, const Vector3& sourceVar,
	const Vector3& velVar, double lifeVar, double distanceVar, double massVar , const Vector4& colorVar) : _velocityVar(velVar), _particleSourceVar(sourceVar), 
	_lifeTimeVar(lifeVar), _lifeDistanceVar(distanceVar), _massVar(massVar), _colorVar(colorVar),
	ParticleGenerator(particleSource, vel, accel, shape, lifeTime, lifeDistance, mass, dumping, color, partsPerFrame, genProb) {}

std::vector<ParticleDT>
GaussianParticleGenerator::generateParticle() {
	std::vector<ParticleDT> particles(0);
	for (int i = 0; i < _partsPerFrame && _generate; i++) {
		if (abs(_u(_mt)) > _genProb) continue;
		ParticleDT particle;
		particle.lifeDistance = _lifeDistance + _u(_mt) * _lifeDistanceVar;
		particle.lifeTime = _lifeTime + _u(_mt) * _lifeTimeVar;

		Vector3 pSource = Vector3(_particleSource.x + _u(_mt) * _particleSourceVar.x, _particleSource.y + _u(_mt) * _particleSourceVar.y, _particleSource.z + _u(_mt) * _particleSourceVar.z),
			vel = Vector3(_velocity.x + _u(_mt) * _velocityVar.x, _velocity.y + _u(_mt) * _velocityVar.y, _velocity.z + _u(_mt) * _velocityVar.z);

		particle.origin = pSource;
		double mass = abs(_mass + _u(_mt) * _massVar);
		Vector4 color = Vector4(_color.x + _u(_mt) * _colorVar.x, _color.y + _u(_mt) * _colorVar.y, _color.z + _u(_mt) * _colorVar.z, _color.w + _u(_mt) * _colorVar.w);
		particle.particle = new Particle(pSource, vel, _acceleration, mass, _dumping, _shape, color);
		particles.push_back(particle);
	}
	return particles;
}