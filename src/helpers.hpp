#ifndef HELPERS_HPP
#define HELPERS_HPP

#include "core.hpp"

GLenum glCheckError_(const char *file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__) 

void printVec3(glm::vec3 v);

#endif