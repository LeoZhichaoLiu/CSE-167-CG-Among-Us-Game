#ifndef Node_hpp
#define Node_hpp

#include <stdio.h>

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
//#include "Transform.hpp"
//#include "Geometry.hpp"

class Node {
    
  public:
    
    virtual void draw(GLuint shader, glm::mat4 C)=0;
    virtual void update()=0;
    virtual void setMode(bool mode_1, bool mode_2, bool mode_3)=0;
};

#endif /* Node_hpp */
