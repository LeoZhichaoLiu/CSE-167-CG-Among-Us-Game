#ifndef Geometry_hpp
#define Geometry_hpp

#include <stdio.h>
#include "Node.hpp"
#include "Transform.hpp"
#include "Material.hpp"
#include "PointLight.hpp"
//#include "Window.h"

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <vector>
#include <list>

using namespace std;

class Geometry : public Node {
    
  protected:
    std::vector<glm::vec3> points;
    std::vector<glm::vec3> normal;
    std::vector<glm::ivec3> face;

    GLuint VAO, VBO[2];
    GLuint EBO;
    
    glm::vec3 color;
    
  public:
    Geometry (std::string obj, std::string name);
    ~Geometry ();
    
    glm::mat4 model;
    glm::mat4 newModel;
    glm::vec4 pos;
    glm::vec3 * newEye;
    glm::vec3 * newLook;
    glm::mat4 * newView;
    bool passEye = false;
    GLfloat radius;
    glm::vec3 position;
    glm::vec3 center;
    float direction = 0;
    float startDirection;
    glm::vec3 goVector;
    
    bool still = true;
    
    
    struct Material {
        public :
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        float shininess;
    };
    
    Material * material;
    
    void init (std::string objFilename);
    void draw(GLuint shader, glm::mat4 C);
    void update();
    void rotate(float degree, glm::vec3 axis);
    void setMode(bool mode_1, bool mode_2, bool mode_3);
    void setEye (glm::vec3 * eye, glm::vec3 * Look, glm::mat4 * view);
    void setFalse ();
    void move (glm::vec3 factor);
    glm::vec3 getPosition ();
};

#endif /* Geometry_hpp */
