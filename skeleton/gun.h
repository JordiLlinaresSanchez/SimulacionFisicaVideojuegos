#pragma once
#include "projectile.h"

class Projectile;
class Gun
{
private:
	struct projInfo {
		Projectile* proj;
		double lifeTime;
	};
	Vector3 _pos;
	Vector3 _dir;
	Vector3 _accel;
	double _lifeTime;
	double _dumping;
	double _mass;
	ProjType _type;
	std::vector<projInfo> _projectiles;
public:
	Gun(Vector3 pos = Vector3(0.0), Vector3 dir = Vector3(0.0), Vector3 accel = Vector3(0.0, -9.4, 0.0), double lifeTime = 5.0, double mass = 1.0, double dumping = 0.9, ProjType type = None);
	~Gun();
	void shoot();
	void clean(double t);
	void integrate(double t);

	void setDir(Vector3 dir);
	void setPos(Vector3 pos);
	void setType(ProjType);

	Vector3 getPos() const;
	Vector3 getDir() const;
};

