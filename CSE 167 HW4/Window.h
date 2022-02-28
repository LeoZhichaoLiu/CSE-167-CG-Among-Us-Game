#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "main.h"
#include "shader.h"
#include "Object.h"
#include "Cube.h"
#include "PointCloud.h"
#include "SkyBox.hpp"
#include "Sphere.h"
#include "Node.hpp"
#include "Geometry.hpp"
#include "Transform.hpp"
#include "Material.hpp"
#include "PointLight.hpp"
#include "Particle.hpp"

//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"

class Window
{
public:

	// Window Properties
	static int width;
	static int height;
	static const char* windowTitle;
    static double last_x;
    static double last_y;
    static bool leftPress;
    static bool mode1;
    static bool mode2;
    
    static glm::vec3 gg;
    
    static vector<std::string> faces;
    
	// Objects to Render
	static Cube* cube;
    static SkyBox * box;
    static Transform * ride;
    static PointLight * SphereLight;
    static PointCloud * lobby;
    static Geometry * robot1;
    static Geometry * robot2;
    static Geometry * robot3;
    static Geometry * robot4;
    static Geometry * robot5;
    
    static Particle * particle1;
    static Particle * particle2;
    static Particle * particle3;
    static Particle * particle4;
    
    static bool particle1On;
    static bool particle2On;
    static bool particle3On;
    static bool particle4On;
    
    static bool robotGone1;
    static bool robotGone2;
    static bool robotGone3;
    static bool robotGone4;
    
    static std::vector <Geometry *> List;
    
    static GLfloat appear1;
    static GLfloat appear2;
    static GLfloat appear3;
    static GLfloat appear4;
    
    static GLfloat run1;
    static GLfloat run2;
    static GLfloat run3;
    static GLfloat run4;
    
    static GLfloat runAgain1;
    static GLfloat runAgain2;
    static GLfloat runAgain3;
    static GLfloat runAgain4;
    
    static GLfloat leave1;
    static GLfloat leave2;
    static GLfloat leave3;
    static GLfloat leave4;
    
    static glm::vec3 box1Center;
    static GLfloat box1Radius;
    static glm::vec3 box2Center;
    static GLfloat box2Radius;
    
    static glm::vec3 plane1N;
    static glm::vec3 plane1P;
    static glm::vec3 plane2N;
    static glm::vec3 plane2P;
    static glm::vec3 plane3N;
    static glm::vec3 plane3P;
    static glm::vec3 plane4N;
    static glm::vec3 plane4P;
    static glm::vec3 plane5N;
    static glm::vec3 plane5P;
    static glm::vec3 plane6N;
    static glm::vec3 plane6P;
    
    static GLfloat cur;
    static GLfloat cur2;

	// Camera Matrices
	static glm::mat4 projection;
	static glm::mat4 view;
	static glm::vec3 eyePos, lookAtPoint, upVector, eyePosRecord, viewRecord;

	// Shader Program ID
	static GLuint shaderProgram;
    static GLuint boxShader;
    static GLuint sphereProgram;
    static GLuint rideProgram;
    static GLuint toonProgram;
    
	// Constructors and Destructors
	static bool initializeProgram();
	static bool initializeObjects();
	static void cleanUp();

	// Window functions
	static GLFWwindow* createWindow(int width, int height);
	static void resizeCallback(GLFWwindow* window, int width, int height);

	// Draw and Update functions
	static void idleCallback();
	static void displayCallback(GLFWwindow*);
    
    // Helper function to change 2d to 3d.
    static glm::vec3 TwoDto3D(double x, double y);

	// Callbacks
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouse_botton_callback (GLFWwindow* window, int button, int action, int mods);
    static void Cursor_pos_callback (GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double xOff, double yOff);
    static bool playerCollision (Geometry * robot);
    static void setDirection (Geometry * robot);
};

#endif
