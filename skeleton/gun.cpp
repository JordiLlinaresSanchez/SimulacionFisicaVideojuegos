#include "gun.h"
#include "projectile.h"

Gun::Gun(Vector3 pos, Vector3 dir, Vector3 accel, double lifeTime, double mass, double dumping, ProjType type) 
	:_pos(pos), _dir(dir), _accel(accel), _lifeTime(lifeTime), _dumping(dumping), _mass(mass), _type(type), _projectiles(std::vector<projInfo>()){

}
Gun::~Gun() {
	for (projInfo p : _projectiles) delete &p.proj;
}
void 
Gun::shoot(){
	_projectiles.push_back({ new Projectile(_pos, _dir, _accel, _mass, _dumping, _type), 0 });
}

void
Gun::clean(double t) {
	int toDelete = 0;
	for (int i = 0; i < _projectiles.size(); i++) {
		_projectiles[i].lifeTime += t;
		if (_projectiles[i].lifeTime > _lifeTime) {
			(_projectiles[i], _projectiles[_projectiles.size() - 1 - toDelete]) = (_projectiles[_projectiles.size() - 1 - toDelete], _projectiles[i]);
			toDelete++;
		}
	}
	for (int i = 0; i < toDelete; i++) _projectiles[_projectiles.size() - 1 - toDelete].proj;
	_projectiles.resize(_projectiles.size() - toDelete);
}

void
Gun::integrate(double t) {
	for (auto& projectile : _projectiles) projectile.proj->integrate(t);
}

void 
Gun::setDir(Vector3 dir) { _dir = dir; }

void 
Gun::setPos(Vector3 pos) { _pos = pos; }

Vector3
Gun::getPos()const { return _pos; }

Vector3
Gun::getDir()const { return _dir; } 