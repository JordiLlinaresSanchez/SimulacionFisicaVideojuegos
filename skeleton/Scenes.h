#include "Scene.h"


class RenderItem;
class Gun;
class ParticleSystem;
class ParticleGenerator;
class ForceGenerator;
class Pin;
class SpecialParticleSystem;
class FloatationFG;
class SolidSystem;
class RigidPin;
class BowlingBallSystem;
class SolidGenerator;
namespace physx{
	class PxPhysics;
	class PxScene;
}

class Scene0 : public Scene {

private:
	std::vector<RenderItem*> RI;
	Gun* gun;

public:
	Scene0();
	~Scene0();

	void initPhysics(bool interactive) override;

	void update(double t)override;

	void keyPress(unsigned char key, const physx::PxTransform& camera)override;

};

class Scene1 : public Scene {

private:
	std::vector<RenderItem*> RI;
	ParticleSystem* pS;
	ForceGenerator* explosion;

public:
	Scene1();
	~Scene1();

	void initPhysics(bool interactive) override;

	void update(double t)override;

	void keyPress(unsigned char key, const physx::PxTransform& camera)override;

};

class Scene2 : public Scene {

private:
	std::vector<RenderItem*> RI;
	ParticleSystem* pS;

public:
	Scene2();
	~Scene2();

	void initPhysics(bool interactive) override;

	void update(double t)override;

	void keyPress(unsigned char key, const physx::PxTransform& camera)override;

};

class GameScene : public Scene {

private:
	std::vector<RenderItem*> RI;
	std::vector<Pin*> pins;
	std::vector<ParticleGenerator*> confetti;
	ParticleSystem* pS;
	SpecialParticleSystem* ballSystem;
	ForceGenerator* explosion;
	ParticleGenerator* balls;
	Gun* gun;
	

	void generatePins();

public:
	GameScene();
	~GameScene();


	void initPhysics(bool interactive) override;

	void update(double t)override;

	void keyPress(unsigned char key, const physx::PxTransform& camera)override;

};

class Scene3 : public Scene {

private:
	std::vector<RenderItem*> RI;
	ParticleSystem* pS;

public:
	Scene3();
	~Scene3();

	void initPhysics(bool interactive) override;

	void update(double t)override;

	void keyPress(unsigned char key, const physx::PxTransform& camera)override;

};

class Scene4 : public Scene {

private:
	std::vector<RenderItem*> RI;
	ParticleSystem* pS;
	FloatationFG* floatationFG;

public:
	Scene4();
	~Scene4();

	void initPhysics(bool interactive) override;

	void update(double t)override;

	void keyPress(unsigned char key, const physx::PxTransform& camera)override;

};

class Scene5 : public Scene {

private:
	std::vector<RenderItem*> RI;
	SolidSystem* sS;
	physx::PxPhysics* gPhysics = NULL;
	physx::PxScene* gScene = NULL;
public:
	Scene5(physx::PxPhysics* physics, physx::PxScene* scene);
	~Scene5();

	void initPhysics(bool interactive) override;

	void update(double t)override;

	void keyPress(unsigned char key, const physx::PxTransform& camera)override;

};

class GameScene2 : public Scene {

private:
	std::vector<RenderItem*> RI;
	//std::vector<RigidPin*> pins;
	std::vector<ParticleGenerator*> confetti;
	ParticleSystem* pS;
	SolidSystem* sS;
	BowlingBallSystem* ballSystem;
	SolidGenerator* balls;
	ForceGenerator* explosion;
	physx::PxScene* gScene;


	void generatePins();
	void generateConfetti();

public:
	GameScene2(physx::PxScene* scene);
	~GameScene2();

	void initPhysics(bool interactive) override;

	void update(double t)override;

	void keyPress(unsigned char key, const physx::PxTransform& camera)override;

};