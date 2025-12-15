#include "twoWaysSpringFG.h"

TwoWaysSpringFG::TwoWaysSpringFG(double k, double restingLength):SpringForceGenerator(k, restingLength){}

void 
TwoWaysSpringFG::asignParticles(Particle* part, Particle* root) {
	SpringForceGenerator::asignParticles(part, root);
	SpringForceGenerator::asignParticles(root, part);
}