//
//  Particle.hpp
//  CSE 167
//
//  Created by 刘智超 on 2020/12/6.
//
#ifndef Particle_hpp
#define Particle_hpp

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#include <string>
#endif

#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stdio.h>

using namespace std;

class Particle {

public:
    
    GLfloat pointSize;
    int particleSize = 0;
    int currSize = 0;
    bool Stop = false;
    
    float life;
    glm::vec3 position, vel;
    
    glm::mat4 model;
    glm::vec3 color;
    GLuint VAO, VBO;
    
    std::vector <int> indexes;
    std::vector <glm::vec3> velocity;
    
    Particle (glm::vec3 robotPos);
    ~Particle();
    
    void update (int Case, float deltaTime);
    void draw (GLuint shader);
    void move (glm::vec3 factor);
    
};


#endif /* Particle_hpp */
