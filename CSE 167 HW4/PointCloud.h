#ifndef _POINT_CLOUD_H_
#define _POINT_CLOUD_H_

#include "Object.h"

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <string>

//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"

using namespace std;

class PointCloud : public Object
{
private:
	std::vector<glm::vec3> points;
    std::vector<glm::vec3> normal;
    std::vector<glm::ivec3> face;
    std::vector<glm::vec2> texture;
    
    unsigned int lobbyTexture;

	GLuint VAO, VBO[3];
    GLuint EBO;
	GLfloat pointSize;

public:
    
	PointCloud(std::string objFilename, GLfloat pointSize);
	~PointCloud();
    
    struct Material {
        public :
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        float shininess;
    };
    
    Material * material;
	
	void draw(const glm::mat4& view, const glm::mat4& projection, GLuint shader);
	void update();

	void updatePointSize(GLfloat size);
	void spin(float deg);
    void rotate(float degree, glm::vec3 axis);
    void scale (double factor);
    unsigned int loadLobby (string face);
};

#endif
