#include "forceGenerator.h"

ForceGenerator::ForceGenerator(Vector3 force) : _magnitude(force), _elapsedTime(0.0), canAply(true){}