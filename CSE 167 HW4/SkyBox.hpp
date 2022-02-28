#ifndef SkyBox_hpp
#define SkyBox_hpp

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <vector>

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class SkyBox{
private:
    std::vector<glm::vec3> points;
    std::vector<glm::vec3> normal;
    std::vector<glm::ivec3> face;
    std::vector<std::string> faces;
    unsigned int cubemapTexture;
    
    GLuint VAO, VBO[2];
    GLuint EBO;
    glm::mat4 model;
    glm::vec3 color;
    
public:
    
    SkyBox();
    ~SkyBox();
    
    unsigned int loadCubemap(vector<std::string> faces);
    void draw(const glm::mat4& view, const glm::mat4& projection, GLuint shader);
    void update();
    void rotate(float degree, glm::vec3 axis);
    
};

#endif /* SkyBox_hpp */
