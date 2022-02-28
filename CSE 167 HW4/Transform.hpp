#ifndef Transform_hpp
#define Transform_hpp

#include <stdio.h>
#include "Node.hpp"

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

class Transform : public Node {
     
  public:
    Transform (std::string name);
    ~Transform ();
    
    bool Mode_1 = true;
    bool Mode_2 = true;
    bool Mode_3 = true;
    int time = 0;
    int direction = 1;
    
    glm::mat4 M;
    std::vector <Node *> List;
    std::string Name;
    
    void draw(GLuint shader, glm::mat4 C);
    void update();
    void addChild (Node * node);
    void rotate (float degree, glm::vec3 axis);
    void setMode (bool mode_1, bool mode_2, bool mode_3);
    void setMode1 ();
    void setMode2 ();
    void setMode3 ();
};


#endif /* Transform_hpp */
