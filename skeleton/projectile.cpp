#include "projectile.h"
using namespace physx;

Projectile::Projectile(Vector3 pos, Vector3 vel, Vector3 accel, double mass, double dumping, PxShape* shape, Vector4 color = Vector4(1.0, 1.0, 1.0, 1.0)) :  
	_mass(mass), Particle(pos, vel, accel, dumping, shape, color){

}

Vector3 Projectile::getForce() {

	return _mass * _accel;
}