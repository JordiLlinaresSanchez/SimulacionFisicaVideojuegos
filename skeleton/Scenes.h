#include "Scene.h"


class RenderItem;
class Gun;
class ParticleSystem;
class ForceGenerator;
class Pin;

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
	ParticleSystem* pS;
	ForceGenerator* explosion;

	void generatePins();

public:
	GameScene();
	~GameScene();


	void initPhysics(bool interactive) override;

	void update(double t)override;

	void keyPress(unsigned char key, const physx::PxTransform& camera)override;

};