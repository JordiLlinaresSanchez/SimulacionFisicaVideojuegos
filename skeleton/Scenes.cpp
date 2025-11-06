#include "Scenes.h"

#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>

#include "particle.h"
#include "projectile.h"
#include "gun.h"
#include "gaussianParticleGenerator.h"
#include "uniformParticleGenerator.h"
#include "particleSystem.h"
#include "forceGenerator.h"
#include "gravityForceGenerator.h"
#include "windGenerator.h"
#include "hurricaneGenerator.h"
#include "explosionGenerator.h"
#include "pin.h"
#include "locatedGravity.h"


using namespace physx;

Scene0::Scene0():RI(std::vector<RenderItem*>(0)), gun(NULL){}

Scene0::~Scene0() {
	delete gun;
	for (auto ri : RI) delete ri;
}

void 
Scene0::initPhysics(bool interactive) {
	PxShape* shape = CreateShape(PxCapsuleGeometry(1.0, 10.0));
	PxShape* sphere = CreateShape(PxSphereGeometry(1.0));

	RI.push_back(new RenderItem(shape, new PxTransform(Vector3(10.0, 0.0, 0.0), PxQuat(3.1416 / 2, Vector3(1.0, 0.0, 0.0))), Vector4(1.0, 0.0, 0.0, 1.0)));
	RI.push_back(new RenderItem(shape, new PxTransform(Vector3(0.0, 10.0, 0.0), PxQuat(3.1416 / 2, Vector3(0.0, 0.0, 1.0))), Vector4(0.0, 1.0, 0.0, 1.0)));
	RI.push_back(new RenderItem(shape, new PxTransform(Vector3(0.0, 0.0, 10.0), PxQuat(3.1416 / 2, Vector3(0.0, 1.0, 0.0))), Vector4(0.0, 0.0, 1.0, 1.0)));

	gun = new Gun(Vector3(0.0, 0.0, 0.0), Vector3(-1.0, 0.0, -1.0), Vector3(0.0, -9.4, 0.0), 5.0, 40.0, 0.9, CanonBall);

	shape->release();
	sphere->release();
}

void 
Scene0::update(double t) {
	gun->integrate(t);
}

void 
Scene0::keyPress(unsigned char key, const PxTransform& camera) {
	switch (toupper(key)) {
	case 'B':
	{
		gun->setDir(-camera.q.getBasisVector2());
		gun->setPos(camera.p);
		gun->setType(GunBullet);
		gun->shoot();
		break;
	}
	case 'N':
	{
		gun->setDir(-camera.q.getBasisVector2());
		gun->setPos(camera.p);
		gun->setType(CanonBall);
		gun->shoot();
		break;
	}
	case 'M':
	{
		gun->setDir(-camera.q.getBasisVector2());
		gun->setPos(camera.p);
		gun->setType(TankBullet);
		gun->shoot();
		break;
	}
	default:
		break;
	}
}

Scene1::Scene1() :RI(std::vector<RenderItem*>(0)), pS(NULL), explosion(NULL) {}

Scene1::~Scene1() {
	for (auto ri : RI) delete ri;
	delete pS;
	delete explosion;
}

void
Scene1::initPhysics(bool interactive) {
	PxShape* shape = CreateShape(PxCapsuleGeometry(1.0, 10.0));
	PxShape* sphere = CreateShape(PxSphereGeometry(1.0));

	RI.push_back(new RenderItem(shape, new PxTransform(Vector3(10.0, 0.0, 0.0), PxQuat(3.1416 / 2, Vector3(1.0, 0.0, 0.0))), Vector4(1.0, 0.0, 0.0, 1.0)));
	RI.push_back(new RenderItem(shape, new PxTransform(Vector3(0.0, 10.0, 0.0), PxQuat(3.1416 / 2, Vector3(0.0, 0.0, 1.0))), Vector4(0.0, 1.0, 0.0, 1.0)));
	RI.push_back(new RenderItem(shape, new PxTransform(Vector3(0.0, 0.0, 10.0), PxQuat(3.1416 / 2, Vector3(0.0, 1.0, 0.0))), Vector4(0.0, 0.0, 1.0, 1.0)));

	pS = new ParticleSystem();

	ParticleGenerator* pg = new GaussianParticleGenerator(Vector3(0.0, 30.0, 0.0), Vector3(0.0, 0.0, 0.0), Vector3(0.0),
		sphere, 5.0, 300.0, 1.0, 0.9, Vector4(0.4, 0.5, 1.0, 1.0), 3, 2.0, Vector3(20.0, 0.0, 20.0), Vector3(0.0, 0.0, 0.0), 1.5, 3.0,
		0.1, Vector4(0.0, 0.2, 0.05, 0.0));
	pS->addParticleGenerator(pg);

	pS->addForceGenerator(new GravityForceGenerator(Vector3(0.0, -9.4, 0.0)));
	pS->addForceGenerator(new WindGenerator(Vector3(-15.0, 0.0, -0.0), Vector3(0.0), 50.0));

	explosion = new ExplosionGenerator(Vector3(0.0, 10.0, 0.0), 20.0, 10000.0, 0.3);
	pS->addForceGenerator(explosion);

	shape->release();
	sphere->release();
}

void
Scene1::update(double t) {
	pS->update(t);
}

void
Scene1::keyPress(unsigned char key, const PxTransform& camera) {
	switch (toupper(key)) {
	case 'E': {
		explosion->restartTimer();
	}
	default:
		break;
	}
}

Scene2::Scene2() :RI(std::vector<RenderItem*>(0)), pS(NULL) {}

Scene2::~Scene2() {
	for (auto ri : RI) delete ri;
	delete pS;
}

void
Scene2::initPhysics(bool interactive) {
	PxShape* shape = CreateShape(PxCapsuleGeometry(1.0, 10.0));
	PxShape* sphere = CreateShape(PxSphereGeometry(1.0));

	RI.push_back(new RenderItem(shape, new PxTransform(Vector3(10.0, 0.0, 0.0), PxQuat(3.1416 / 2, Vector3(1.0, 0.0, 0.0))), Vector4(1.0, 0.0, 0.0, 1.0)));
	RI.push_back(new RenderItem(shape, new PxTransform(Vector3(0.0, 10.0, 0.0), PxQuat(3.1416 / 2, Vector3(0.0, 0.0, 1.0))), Vector4(0.0, 1.0, 0.0, 1.0)));
	RI.push_back(new RenderItem(shape, new PxTransform(Vector3(0.0, 0.0, 10.0), PxQuat(3.1416 / 2, Vector3(0.0, 1.0, 0.0))), Vector4(0.0, 0.0, 1.0, 1.0)));

	pS = new ParticleSystem();

	ParticleGenerator* pg = new GaussianParticleGenerator(Vector3(0.0), Vector3(0.0, 0.0, 0.0), Vector3(0.0),
		sphere, 20.0, 220.0, 1.0, 0.9, Vector4(0.55, 0.3, 0.15, 1.0), 3, 2.0, Vector3(20.0, 0.0, 20.0), Vector3(0.0, 0.0, 0.0), 1.5, 3.0,
		0.1, Vector4(0.05, 0.05, 0.05, 0.0));
	pS->addParticleGenerator(pg);

	pS->addForceGenerator(new GravityForceGenerator(Vector3(0.0, -9.4, 0.0)));
	pS->addForceGenerator(new HurricaneGenerator(2, 100, 1.0, Vector3(0.0), 170.0));

	shape->release();
	sphere->release();
}

void
Scene2::update(double t) {
	pS->update(t);
}

void
Scene2::keyPress(unsigned char key, const PxTransform& camera) {
	switch (toupper(key)) {

	default:
		break;
	}
}

GameScene::GameScene() :RI(std::vector<RenderItem*>(0)), pS(NULL) {}

GameScene::~GameScene() {
	for (auto ri : RI) delete ri;
	delete pS;
}

void
GameScene::generatePins() {
	for (int i = 0; i < 3; ++i) {
		double distance = 0.4, pos = 0;
		for (int j = 0; j < i+1; ++j) {
			pos = distance * j;
			Vector3 initPos = Vector3(30.0 + distance * i, 0.4, 0.0 - (distance * i / 2) + distance * j);
			pS->generateParticles(new Pin(PxTransform(initPos, PxQuat(3.1416 / 2, Vector3(0.0, 0.0, 1.0))), Vector3(0.0), Vector3(0.0), 7.3, 0.9), initPos, 100.0);
		}
	}
}

void
GameScene::initPhysics(bool interactive) {
	PxShape* shape = CreateShape(PxCapsuleGeometry(0.15, 0.33));
	PxShape* sphere = CreateShape(PxSphereGeometry(0.33));
	PxShape* plane = CreateShape(PxBoxGeometry(1.2, 0.1, 20.0));

	RI.push_back(new RenderItem(plane, new PxTransform(Vector3(15.0, 0.0, 0.0), PxQuat(3.1415/2, Vector3(0.0, 1.0, 0.0))), Vector4(0.23, 0.22, 0.1, 1.0)));
	RI.push_back(new RenderItem(sphere, new PxTransform(Vector3(0.0, 0.0, 0.0), PxQuat(3.1416 / 2, Vector3(0.0, 0.0, 1.0))), Vector4(0.0, 1.0, 1.0, 1.0)));

	pS = new ParticleSystem();
	//generatePins();


	/*ParticleGenerator* pg = 
	pS->addParticleGenerator(pg);*/

	pS->addForceGenerator(new GravityForceGenerator(Vector3(0.0, -9.4, 0.0)));
	pS->addForceGenerator(new LocatedGravity(Vector3(0.0, 100.0, 0.0), Vector3(40.0, 0.3, 0.6), Vector3(0.0, -5.0, -0.6)));
	explosion = new ExplosionGenerator(Vector3(35.0, 0.0, 0.0), 10.0, 1000.0, 0.2);
	pS->addForceGenerator(explosion);
	
	shape->release();
	sphere->release();
}

void
GameScene::update(double t) {
	pS->update(t);
}

void
GameScene::keyPress(unsigned char key, const PxTransform& camera) {
	switch (toupper(key)) {
	case'P': {
		generatePins();
		break;
	}
	case'E': {
		explosion->restartTimer();
		break;
	}
	default:
		break;
	}
}