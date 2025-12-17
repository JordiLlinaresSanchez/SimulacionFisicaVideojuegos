#include "gaussianSG.h"

//					   const Vector3& source, const Vector3& vel, physx::PxShape* shape, double lifeTime, double lifeDistance, double genProb, const Vector4& color, int partsPerFrame,
//	const Vector3& sourceVar, const Vector3& velVar, double lifeVar, double distanceVar, double massVar, const Vector4& colorVar
GaussianSG::GaussianSG(const Vector3& source, const Vector3& vel, physx::PxShape* shape, double lifeTime, double lifeDistance, double mass, double genProb, const Vector4& color, int partsPerFrame,
	const Vector3& sourceVar, const Vector3& velVar, double lifeVar, double distanceVar, double massVar, const Vector4& colorVar) : _velocityVar(velVar), _sourceVar(sourceVar),
	_lifeTimeVar(lifeVar), _lifeDistanceVar(distanceVar), _massVar(massVar), _colorVar(colorVar),
	SolidGenerator(source, vel, shape, lifeTime, lifeDistance, mass, genProb, color, partsPerFrame) {}

std::vector<SolidDT>
GaussianSG::generate(physx::PxScene* scene) {
	std::vector<SolidDT> solids(0);
	for (int i = 0; i < _partsPerFrame && _generate; i++) {
		if (abs(_u(_mt)) > _genProb) continue;
		SolidDT solidDT;
		solidDT.lifeDistance = _lifeDistance + _u(_mt) * _lifeDistanceVar;
		solidDT.lifeTime = _lifeTime + _u(_mt) * _lifeTimeVar;

		Vector3 source = Vector3(_source.x + _u(_mt) * _sourceVar.x, _source.y + _u(_mt) * _sourceVar.y, _source.z + _u(_mt) * _sourceVar.z),
			vel = Vector3(_velocity.x + _u(_mt) * _velocityVar.x, _velocity.y + _u(_mt) * _velocityVar.y, _velocity.z + _u(_mt) * _velocityVar.z);

		solidDT.origin = source;
		double mass = abs(_mass + _u(_mt) * _massVar);
		Vector4 color = Vector4(_color.x + _u(_mt) * _colorVar.x, _color.y + _u(_mt) * _colorVar.y, _color.z + _u(_mt) * _colorVar.z, _color.w + _u(_mt) * _colorVar.w);
		
		physx::PxRigidActor* solid = scene->getPhysics().createRigidStatic(physx::PxTransform(source));
		solidDT.solid = solid;

		solid->attachShape(*_shape);
		scene->addActor(*solid);

		solidDT.ri = new RenderItem(_shape, solid, color);

		solids.push_back(solidDT);
	}
	return solids;
}