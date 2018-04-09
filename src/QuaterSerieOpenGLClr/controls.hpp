#ifndef CONTROLS_HPP
#define CONTROLS_HPP

void computeMatricesFromInputs();
void computeMatricesFromInputsQuater(int, int, int, int);
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();

#endif