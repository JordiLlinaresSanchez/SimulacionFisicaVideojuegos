#pragma once
#include <vector>

namespace physx {
	class PxTransform;
}
class Scene
{

public:
	Scene();
	~Scene();

	virtual void initPhysics(bool interactive) = 0;

	virtual void update(double t) = 0;

	virtual void keyPress(unsigned char key, const physx::PxTransform& camera) = 0;

};
