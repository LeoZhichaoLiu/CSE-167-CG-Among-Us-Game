//
//  Material.hpp
//  CSE 167
//
//
#ifndef Material_hpp
#define Material_hpp

#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>
#include "PointCloud.h"
#include <stdio.h>

class Material {
    
public:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    float shininess;

    Material();
};

#endif /* Material_hpp */
