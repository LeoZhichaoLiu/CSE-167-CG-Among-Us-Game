#ifndef _SPHERE_H_
#define _SPHERE_H_

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//#include "./components/geometries/Geometry.h"

class Sphere{
	public:
		//GLuint shader;

		GLuint vao = 0, vbo = 0, vbo_n = 0, ebo = 0;
		glm::vec3 _minVal, _maxVal, _center;
        glm::mat4 model;
    
		int stackCount;
		int sectorCount;
		int numsToDraw;
		Sphere();
        void draw (const glm::mat4& projection, const glm::mat4& view, const glm::vec3& eye, GLuint shader);
        void scale (double factor);
        void changeStack (double factor);
        void move (glm::vec3 factor);
};

#endif
