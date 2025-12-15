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
#include "specialParticleSystem.h"
#include "ballLauncher.h"
#include "anchoredSpringFG.h"
#include "twoWaysSpringFG.h"
#include "flotationFG.h"


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
	for (auto ri : RI) {
		ri->shape->release();
		delete ri;
	}
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
}

void
Scene1::update(double t) {
	pS->update(t);
}

void
Scene1::keyPress(unsigned char key, const PxTransform& camera) {
	switch (toupper(key)) {
	case 'E': {
		explosion->setTimer(0.0);
	}
	default:
		break;
	}
}

Scene2::Scene2() :RI(std::vector<RenderItem*>(0)), pS(NULL) {}

Scene2::~Scene2() {
	for (auto ri : RI) {
		ri->shape->release();
		delete ri;
	}
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

GameScene::GameScene() :RI(std::vector<RenderItem*>(0)), pS(NULL), ballSystem(NULL) {}

GameScene::~GameScene() {
	for (auto ri : RI) {
		ri->shape->release();
		delete ri;
	}
	delete pS;
	delete explosion;
	delete ballSystem;
	delete explosion;
	delete balls;
}

void
GameScene::generatePins() {
	for (int i = 0; i < 4; ++i) {
		double distance = 0.4, pos = 0;
		for (int j = 0; j < i+1; ++j) {
			pos = distance * j;
			Vector3 initPos = Vector3(30.0 + distance * i, 0.4, 0.0 - (distance * i / 2) + distance * j);
			pS->addParticle(new Pin(PxTransform(initPos, PxQuat(3.1416 / 2, Vector3(0.0, 0.0, 1.0))), Vector3(0.0), Vector3(0.0), 7.3, 0.9), initPos, 100.0);
		}
	}
}

void
GameScene::initPhysics(bool interactive) {
	PxShape* sphere = CreateShape(PxSphereGeometry(0.15));
	PxShape* confettiShape = CreateShape(PxSphereGeometry(0.05));
	PxShape* plane = CreateShape(PxBoxGeometry(1.2, 0.1, 20.0));

	RI.push_back(new RenderItem(plane, new PxTransform(Vector3(15.0, 0.0, 0.0), PxQuat(3.1415/2, Vector3(0.0, 1.0, 0.0))), Vector4(0.23, 0.22, 0.1, 1.0)));

	pS = new ParticleSystem();
	ballSystem = new SpecialParticleSystem();

	balls = new BallLauncher(Vector3(0.0), Vector3(10.0, 0.0, 0.0), sphere, 10.0, 50.0, 10.0, Vector4(0.7, 0.1, 0.1, 1.0), Vector3(2.0, 1.0, 0.1), Vector4(0.2, 0.0, 0.0, 0.0));
	ballSystem->addParticleGenerator(balls);

	confetti.push_back(new GaussianParticleGenerator(Vector3(10.0, 5.0, 6.0), Vector3(0.0), Vector3(0.0), confettiShape, 5.0, 10.0, 0.001, 0.999,
		Vector4(1.0, 0.3, 0.3, 1.0), 1, 0.01, Vector3(1.0, 1.0, 1.0), Vector3(3.0, 2.0, 2.0), 2.0, 5.0, 0.006, Vector4(0.1, 0.1, 0.1, 0.0)));
	confetti.push_back(new GaussianParticleGenerator(Vector3(10.0, 5.0, 6.0), Vector3(0.0), Vector3(0.0), confettiShape, 5.0, 10.0, 0.001, 0.999,
		Vector4(0.3, 1.0, 0.3, 1.0), 1, 0.011, Vector3(1.1, 1.1, 1.1), Vector3(2.0, 6.0, 2.0), 2.0, 5.0, 0.006, Vector4(0.1, 0.1, 0.1, 0.0)));
	confetti.push_back(new GaussianParticleGenerator(Vector3(10.0, 5.0, 6.0), Vector3(0.0), Vector3(0.0), confettiShape, 5.0, 10.0, 0.001, 0.999,
		Vector4(0.3, 0.3, 1.0, 1.0), 1, 0.012, Vector3(1.2, 1.2, 1.2), Vector3(3.0, 2.0, 2.5), 2.0, 5.0, 0.006, Vector4(0.1, 0.1, 0.1, 0.0)));

	confetti.push_back(new GaussianParticleGenerator(Vector3(10.0, 5.0, -6.0), Vector3(0.0), Vector3(0.0), confettiShape, 5.0, 10.0, 0.001, 0.999,
		Vector4(1.0, 0.3, 0.3, 1.0), 1, 0.014, Vector3(1.0, 1.0, 1.0), Vector3(2.0, 2.0, 2.5), 2.0, 5.0, 0.0006, Vector4(0.1, 0.1, 0.1, 0.0)));
	confetti.push_back(new GaussianParticleGenerator(Vector3(10.0, 5.0, -6.0), Vector3(0.0), Vector3(0.0), confettiShape, 5.0, 10.0, 0.001, 0.999,
		Vector4(0.3, 1.0, 0.3, 1.0), 1, 0.013, Vector3(1.2, 1.2, 1.2), Vector3(3.0, 2.5, 3.0), 2.0, 5.0, 0.0006, Vector4(0.1, 0.1, 0.1, 0.0)));
	confetti.push_back(new GaussianParticleGenerator(Vector3(10.0, 5.0, -6.0), Vector3(0.0), Vector3(0.0), confettiShape, 5.0, 10.0, 0.001, 0.999,
		Vector4(0.3, 0.3, 1.0, 1.0), 1, 0.015, Vector3(1.1, 1.1, 1.1), Vector3(2.5, 3.0, 2.0), 2.0, 5.0, 0.0006, Vector4(0.1, 0.1, 0.1, 0.0)));

	for (auto c : confetti) {
		pS->addParticleGenerator(c);
		c->setGenerate(false);
	}
	pS->addForceGenerator(new GravityForceGenerator(Vector3(0.0, -9.4, 0.0)));
	ballSystem->addForceGenerator(new GravityForceGenerator(Vector3(0.0, -9.4, 0.0)));

	pS->addForceGenerator(new LocatedGravity(Vector3(0.0, 100.0, 0.0), Vector3(40.0, 0.3, 1.2), Vector3(0.0, -5.0, -1.2)));
	ballSystem->addForceGenerator(new LocatedGravity(Vector3(0.0, 100.0, 0.0), Vector3(40.0, 0.3, 1.2), Vector3(0.0, -5.0, -1.2)));

	explosion = new ExplosionGenerator(Vector3(28.0, 0.0, 0.0), 10.0, 50000.0, 0.5);
	pS->addForceGenerator(explosion);
	ballSystem->addForceGenerator(explosion);
	gun = new Gun();
	plane->release();
}

void
GameScene::update(double t) {
	pS->update(t);
	ballSystem->update(t);
	gun->integrate(t);
}

void
GameScene::keyPress(unsigned char key, const PxTransform& camera) {
	switch (toupper(key)) {
	case'P': {
		generatePins();
		explosion->setTimer(10.0);
		break;
	}
	case'L': {
		explosion->setTimer(0.0);
		break;
	}
	case ' ': {
		balls->setParticleSource(camera.p);
		balls->setVelocity(-camera.q.getBasisVector2().getNormalized() * balls->getVelocity().magnitude());
		ballSystem->generateParticle();
		break;
	}
	case'C': {
		for (auto c : confetti) c->setGenerate(!c->getGenerate());
		break;
	}
	default:
		break;
	}
}

Scene3::Scene3() :RI(std::vector<RenderItem*>(0)), pS(NULL) {}

Scene3::~Scene3() {
	for (auto ri : RI) {
		ri->shape->release();
		delete ri;
	}
	delete pS;
}

void
Scene3::initPhysics(bool interactive) {
	PxShape* shape = CreateShape(PxCapsuleGeometry(1.0, 10.0));
	PxShape* sphere = CreateShape(PxSphereGeometry(1.0));
	PxShape* box = CreateShape(PxBoxGeometry(1.0, 1.0, 1.0));

	RI.push_back(new RenderItem(shape, new PxTransform(Vector3(10.0, 0.0, 0.0), PxQuat(3.1416 / 2, Vector3(1.0, 0.0, 0.0))), Vector4(1.0, 0.0, 0.0, 1.0)));
	RI.push_back(new RenderItem(shape, new PxTransform(Vector3(0.0, 10.0, 0.0), PxQuat(3.1416 / 2, Vector3(0.0, 0.0, 1.0))), Vector4(0.0, 1.0, 0.0, 1.0)));
	RI.push_back(new RenderItem(shape, new PxTransform(Vector3(0.0, 0.0, 10.0), PxQuat(3.1416 / 2, Vector3(0.0, 1.0, 0.0))), Vector4(0.0, 0.0, 1.0, 1.0)));

	pS = new ParticleSystem();
	Particle* red = new Particle(Vector3(0.0), Vector3(0.0, 0.0, 0.0), Vector3(0.0), 1.0, 0.9, sphere, Vector4(1.0, 0.0, 0.0, 1.0));
	Particle* orange = new Particle(Vector3(0.0, 0.0, 0.5), Vector3(0.0, 0.0, 0.0), Vector3(0.0), 1.0, 0.9, sphere, Vector4(1.0, 0.5, 0.0, 1.0));
	Particle* yellow = new Particle(Vector3(0.0, 0.0, 1.0), Vector3(0.0, 0.0, 0.0), Vector3(0.0), 1.0, 0.9, sphere, Vector4(1.0, 1.0, 0.0, 1.0));
	Particle* green = new Particle(Vector3(0.0, 0.0, 1.5), Vector3(0.0, 0.0, 0.0), Vector3(0.0), 1.0, 0.9, sphere, Vector4(0.0, 1.0, 0.0, 1.0));
	Particle* blue = new Particle(Vector3(0.0, 0.0, 2.0), Vector3(0.0, 0.0, 0.0), Vector3(0.0), 1.0, 0.9, sphere, Vector4(0.0, 0.0, 1.0, 1.0));
	Particle* purple = new Particle(Vector3(0.0, 0.0, 2.5), Vector3(0.0, 0.0, 0.0), Vector3(0.0), 1.0, 0.9, sphere, Vector4(0.5, 0.0, 1.0, 1.0));


	pS->addParticle(red, Vector3(0.0, 0.0, 0.0), 100.0);
	pS->addParticle(orange, Vector3(0.0, 0.0, 0.2), 100.0);
	pS->addParticle(yellow, Vector3(0.0, 0.0, 0.4), 100.0);
	pS->addParticle(green, Vector3(0.0, 0.0, 0.6), 100.0);
	pS->addParticle(blue, Vector3(0.0, 0.0, 0.8), 100.0);
	pS->addParticle(purple, Vector3(0.0, 0.0, 1.0), 100.0);

	AnchoredSpringFG* anchoredSpring = new AnchoredSpringFG(5.0, 3.0, Vector3(0.0), box);
	TwoWaysSpringFG* spring = new TwoWaysSpringFG(5.0, 3.0);
	
	anchoredSpring->atachToRoot(red);
	spring->asignParticles(orange, red);
	spring->asignParticles(orange, yellow);
	spring->asignParticles(yellow, green);
	spring->asignParticles(green, blue);
	spring->asignParticles(blue, purple);

	pS->addForceGenerator(anchoredSpring);
	pS->addForceGenerator(spring);
	pS->addForceGenerator(new GravityForceGenerator(Vector3(0.0, -9.4, 0.0)));
}

void
Scene3::update(double t) {
	pS->update(t);
}

void
Scene3::keyPress(unsigned char key, const PxTransform& camera) {
	switch (toupper(key)) {

	default:
		break;
	}
}

Scene4::Scene4() :RI(std::vector<RenderItem*>(0)), pS(NULL) {}

Scene4::~Scene4() {
	for (auto ri : RI) {
		ri->shape->release();
		delete ri;
	}
	delete pS;
}

void
Scene4::initPhysics(bool interactive) {
	PxShape* shape = CreateShape(PxCapsuleGeometry(1.0, 10.0));
	PxShape* sphere = CreateShape(PxSphereGeometry(1.0));
	PxShape* box = CreateShape(PxBoxGeometry(15.0, 0.2, 15.0));

	RI.push_back(new RenderItem(shape, new PxTransform(Vector3(10.0, 0.0, 0.0), PxQuat(3.1416 / 2, Vector3(1.0, 0.0, 0.0))), Vector4(1.0, 0.0, 0.0, 1.0)));
	RI.push_back(new RenderItem(shape, new PxTransform(Vector3(0.0, 10.0, 0.0), PxQuat(3.1416 / 2, Vector3(0.0, 0.0, 1.0))), Vector4(0.0, 1.0, 0.0, 1.0)));
	RI.push_back(new RenderItem(shape, new PxTransform(Vector3(0.0, 0.0, 10.0), PxQuat(3.1416 / 2, Vector3(0.0, 1.0, 0.0))), Vector4(0.0, 0.0, 1.0, 1.0)));

	pS = new ParticleSystem();
	Particle* liquid = new Particle(Vector3(0.0), Vector3(0.0, 0.0, 0.0), Vector3(0.0), 1.0, 0.9, box, Vector4(0.0, 0.3, 1.0, 1.0));
	Particle* particle = new Particle(Vector3(-3.0, 0.0, 1.0), Vector3(0.0, 0.0, 0.0), Vector3(0.0), 1.0, 0.9, sphere, Vector4(1.0, 0.5, 0.0, 1.0));

	pS->addParticle(particle, Vector3(0.0, 0.0, 0.0), 100.0);
	
	pS->addForceGenerator(new GravityForceGenerator(Vector3(0.0, -9.4, 0.0)));
	pS->addForceGenerator(new FlotationFG(liquid, 5.0, 1.0));
}

void
Scene4::update(double t) {
	pS->update(t);
}

void
Scene4::keyPress(unsigned char key, const PxTransform& camera) {
	switch (toupper(key)) {

	default:
		break;
	}
}
