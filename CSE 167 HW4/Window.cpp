#include "Window.h"

// Window Properties
int Window::width;
int Window::height;
const char* Window::windowTitle = "GLFW Starter Project";
double Window::last_x;
double Window::last_y;
bool Window::leftPress;
bool Window::mode1;
bool Window::mode2;

// Objects to Render
Cube * Window::cube;
SkyBox * Window::box;
PointLight * Window::SphereLight;
PointCloud * Window :: lobby;
Geometry * Window :: robot1;
Geometry * Window :: robot2;
Geometry * Window :: robot3;
Geometry * Window :: robot4;
Geometry * Window :: robot5;

Particle * Window :: particle1;
Particle * Window :: particle2;
Particle * Window :: particle3;
Particle * Window :: particle4;

bool Window :: particle1On;
bool Window :: particle2On;
bool Window :: particle3On;
bool Window :: particle4On;

bool Window :: robotGone1;
bool Window :: robotGone2;
bool Window :: robotGone3;
bool Window :: robotGone4;

std::vector <Geometry *> Window :: List;

GLfloat Window :: appear1;
GLfloat Window :: appear2;
GLfloat Window :: appear3;
GLfloat Window :: appear4;

GLfloat Window :: run1;
GLfloat Window :: run2;
GLfloat Window :: run3;
GLfloat Window :: run4;

GLfloat Window :: runAgain1;
GLfloat Window :: runAgain2;
GLfloat Window :: runAgain3;
GLfloat Window :: runAgain4;

GLfloat Window :: leave1;
GLfloat Window :: leave2;
GLfloat Window :: leave3;
GLfloat Window :: leave4;

Transform * Window::ride;

glm::vec3 Window :: box1Center;
GLfloat Window :: box1Radius;
glm::vec3 Window :: box2Center;
GLfloat Window :: box2Radius;

glm::vec3 Window :: plane1N;
glm::vec3 Window :: plane1P;
glm::vec3 Window :: plane2N;
glm::vec3 Window :: plane2P;
glm::vec3 Window :: plane3N;
glm::vec3 Window :: plane3P;
glm::vec3 Window :: plane4N;
glm::vec3 Window :: plane4P;
glm::vec3 Window :: plane5N;
glm::vec3 Window :: plane5P;
glm::vec3 Window :: plane6N;
glm::vec3 Window :: plane6P;

GLfloat Window :: cur;
GLfloat Window :: cur2;
glm::vec3 Window :: gg (0, 0, 1);

Object* currObj;

// Camera Matrices 
// Projection matrix:
glm::mat4 Window::projection; 

// View Matrix:
glm::vec3 Window::eyePos (0, 0, 20);			// Camera position.
glm::vec3 Window::lookAtPoint(0, 0, 0);		// The point we are looking at.
glm::vec3 Window::upVector(0, 1, 0);		// The up direction of the camera.
glm::mat4 Window::view = glm::lookAt(Window::eyePos, Window::lookAtPoint, Window::upVector);

glm::vec3 Window::eyePosRecord = eyePos;
glm::vec3 Window::viewRecord = lookAtPoint;

// Shader Program ID
GLuint Window::shaderProgram;
GLuint Window::boxShader;
GLuint Window::sphereProgram;
GLuint Window::rideProgram;
GLuint Window::toonProgram;

bool Window::initializeProgram() {
    //glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    
	// Create a shader program with a vertex shader and a fragment shader.
    shaderProgram = LoadShaders("shaders/shader.vert", "shaders/shader.frag");
    boxShader = LoadShaders("shaders/boxShader.vert", "shaders/boxShader.frag");
    sphereProgram = LoadShaders("shaders/sphereShader.vert", "shaders/sphereShader.frag");
    rideProgram = LoadShaders("shaders/shader2.vert", "shaders/shader2.frag");
    toonProgram = LoadShaders("shaders/toonShader.vert", "shaders/toonShader.frag");
    
	// Check the shader program.
	if (!shaderProgram)
	{
		std::cerr << "Failed to initialize shader program" << std::endl;
		return false;
	}
    
    if (!boxShader)
    {
        std::cerr << "Failed to initialize boxShader program" << std::endl;
        return false;
    }
    
    if (!sphereProgram) {
        std::cerr << "Failed to initialize sphereProgram program" << std::endl;
        return false;
    }
    
    if (!rideProgram) {
        std::cerr << "Failed to initialize ride program" << std::endl;
        return false;
    }
    
    if (!toonProgram) {
        std::cerr << "Failed to initialize toon program" << std::endl;
        return false;
    }
    
	return true;
}

bool Window::initializeObjects()
{
    box = new SkyBox ();
    SphereLight = new PointLight ("OBJ/sphere.obj");
    lobby = new PointCloud ("OBJ/amongus_lobby.obj", 1);
    
    robot1 = new Geometry ("OBJ/amongus_astro_still.obj", "1yellow");
    robot1 -> move (glm::vec3(4, -8, -3));
    particle1 = new Particle (glm::vec3(4, -8, -3));
    particle1On = true;
    
    robot2 = new Geometry ("OBJ/amongus_astro_still.obj", "2blue");
    robot2 -> move (glm::vec3(-4, -2, -3));
    particle2 = new Particle (glm::vec3(-4, -2, -3));
    particle2On = true;
    
    robot3 = new Geometry ("OBJ/amongus_astro_still.obj", "3brown");
    robot3 -> move (glm::vec3(4, -6, -3));
    particle3 = new Particle (glm::vec3(4, -6, -3));
    particle3On = true;
    
    robot4 = new Geometry ("OBJ/amongus_astro_still.obj", "4orange");
    robot4 -> move (glm::vec3(1, -2, -3));
    particle4 = new Particle (glm::vec3(1, -2, -3));
    particle4On = true;
    
    robot5 = new Geometry ("OBJ/amongus_astro_still.obj", "5red");
    robot5 -> move (glm::vec3(-1, -4, -3));
    
    
    List.push_back (robot5);
    
    mode1 = true;
    mode2 = false;
    
    box1Center = glm::vec3 (-4.8, -3.8, -3);
    box1Radius = 1.1;

    box2Center = glm::vec3 (5.7, -2, -3);
    box2Radius = 1;
    
    plane1N = glm::vec3 (0, -1, 0); // Top
    plane1P = glm::vec3 (0, 0, 0);
    plane2N = glm::vec3 (0, 1, 0);  // Bottom
    plane2P = glm::vec3 (0, -8.6, 0);
    plane3N = glm::vec3 (1, 0, 0);  // Left
    plane3P = glm::vec3 (-8, 0, 0);
    plane4N = glm::vec3 (-1, 0, 0);  // Right
    plane4P = glm::vec3 (8.6, 0, 0);
    plane5N = glm::vec3 (1, 1, 0);   // Left-bottom
    plane5P = glm::vec3 (-7.8, -7.7, 0);
    plane6N = glm::vec3 (-1, 1, 0);   // Right-bottom
    plane6P = glm::vec3 (7.8, -7.7, 0);
    
    unsigned seed = time(0);
    srand(seed);
    
    cur = glfwGetTime();
    cur2 = glfwGetTime();
    
    appear1 = cur + float(rand() % 60)/10 + 3;
    run1 = appear1 + rand() % 3 + 1;
    leave1 = run1 + rand() % 8 + 30;
    
    appear2 = cur + float(rand() % 60)/10 + 3;
    run2 = appear2 + rand() % 3 + 1;
    leave2 = run2 + rand() % 8 + 30;
    
    appear3 = cur + float(rand() % 60)/10 + 3;
    run3 = appear3 + rand() % 3 + 1;
    leave3 = run3 + rand() % 8 + 30;
    
    appear4 = cur + float(rand() % 60)/10 + 3;
    run4 = appear4 + rand() % 3 + 1;
    leave4 = run3 + rand() % 8 + 30;
    
    robotGone1 = false;
    robotGone2 = false;
    robotGone3 = false;
    robotGone4 = false;
    
    /*
    float degree = 30.0;
    glm::mat4 model = glm::translate(glm::mat4(1.0f), eyePos) * glm::mat4(1);
    model = glm::rotate (glm::radians(degree), glm::vec3 (1, 0, 0)) * model;
    glm::vec4 pos = model * glm::vec4(0.0, 0.0, 0.0, 1.0);
    eyePos = glm::vec3(pos.x, pos.y, pos.z);
    view = glm::lookAt(Window::eyePos, Window::lookAtPoint, Window::upVector);
    */
    

	return true;
}

void Window::cleanUp() {
    
    delete box;
    delete SphereLight;

	// Delete the shader program.
	glDeleteProgram(shaderProgram);
    glDeleteProgram(boxShader);
    glDeleteProgram(sphereProgram);
    glDeleteProgram(rideProgram);
    glDeleteProgram(toonProgram);
}

GLFWwindow* Window::createWindow(int width, int height)
{
	// Initialize GLFW.
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return NULL;
	}

	// 4x antialiasing.
	glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__ 
	// Apple implements its own version of OpenGL and requires special treatments
	// to make it uses modern OpenGL.

	// Ensure that minimum OpenGL version is 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Enable forward compatibility and allow a modern OpenGL context
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Create the GLFW window.
	GLFWwindow* window = glfwCreateWindow(width, height, windowTitle, NULL, NULL);

	// Check if the window could not be created.
	if (!window)
	{
		std::cerr << "Failed to open GLFW window." << std::endl;
		glfwTerminate();
		return NULL;
	}

	// Make the context of the window.
	glfwMakeContextCurrent(window);

#ifndef __APPLE__
	// On Windows and Linux, we need GLEW to provide modern OpenGL functionality.

	// Initialize GLEW.
	if (glewInit())
	{
		std::cerr << "Failed to initialize GLEW" << std::endl;
		return NULL;
	}
#endif

	// Set swap interval to 1.
	glfwSwapInterval(0);

	// Call the resize callback to make sure things get drawn immediately.
	Window::resizeCallback(window, width, height);

	return window;
}

void Window::resizeCallback(GLFWwindow* window, int width, int height)
{
#ifdef __APPLE__
	// In case your Mac has a retina display.
	glfwGetFramebufferSize(window, &width, &height); 
#endif
	Window::width = width;
	Window::height = height;
	// Set the viewport size.
	glViewport(0, 0, width, height);

	// Set the projection matrix.
	Window::projection = glm::perspective(glm::radians(60.0), 
								double(width) / (double)height, 1.0, 1000.0);
}

void Window::idleCallback()
{
	// Perform any necessary updates here
    
    if (!robotGone1) {
      particle1 -> update(1, appear1 - glfwGetTime());
        //cout << appear1 - glfwGetTime() << endl;
    } else {
      particle1 -> update(0, glfwGetTime() - leave1);
    }
    
    if (!robotGone2) {
      particle2 -> update(1, appear2 - glfwGetTime());
    } else {
      particle2 -> update(0, glfwGetTime() - leave2);
    }
    
    if (!robotGone3) {
      particle3 -> update(1, appear3 - glfwGetTime());
    } else {
      particle3 -> update(0, glfwGetTime() - leave3);
    }
    
    if (!robotGone4) {
      particle4 -> update(1, appear4 - glfwGetTime());
    } else {
      particle4 -> update(0, glfwGetTime() - leave4);
    }
    
    for (Geometry * robot : List) {
        
        //int randStop = rand() % 10;

        cur2 = glfwGetTime();
        
        if (run1 == 0 && leave1 != 0) {
            //cout << "Stop" << endl;
            if (robot1 -> still == false) {
                //cout << "Stop" << endl;
                if (rand() % 15000 == 0 ) {
                    robot1 -> still = true;
                    runAgain1 = glfwGetTime() + rand() % 3 + 1;
                }
            }
            
            if (robot1 -> still == true) {
                if (cur2 > runAgain1) {
                    cout << "Go" << endl;
                    robot1 -> still = false;
                }
            }
        }
        
        if (run2 == 0 && leave2 != 0) {
            if (robot2 -> still == false) {
                if (rand() % 15000 == 1) {
                    robot2 -> still = true;
                    runAgain2 = glfwGetTime() + rand() % 3 + 1;
                }
            }
            
            if (robot2 -> still == true) {
                if (cur2 > runAgain2) {
                    robot2 -> still = false;
                }
            }
        }
        
        if (run3 == 0 && leave3 != 0) {
            if (robot3 -> still == false) {
                if (rand() % 15000 == 2) {
                    robot3 -> still = true;
                    runAgain3 = glfwGetTime() + rand() % 3 + 1;
                }
            }
            if (robot3 -> still == true) {
                if (cur2 > runAgain3) {
                    robot3 -> still = false;
                }
            }
        }
        
        if (run4 == 0 && leave4 != 0) {
            if (robot4 -> still == false) {
                if (rand() % 15000 == 3) {
                    robot4 -> still = true;
                    runAgain4 = glfwGetTime() + rand() % 3 + 1;
                }
            }
            if (robot4 -> still == true) {
                if (cur2 > runAgain4) {
                    robot4 -> still = false;
                }
            }
        }
        
        
        if (robot != robot5 && robot -> still == false) {
            
        robot -> update ();
        if (playerCollision (robot)) {
            
            glm::vec3 topNearP = robot->center - robot->radius * plane1N;
            glm::vec3 bottomNearP = robot->center - robot->radius * plane2N;
            glm::vec3 leftNearP = robot->center - robot->radius * plane3N;
            glm::vec3 rightNearP = robot->center - robot->radius * plane4N;
            glm::vec3 leftDownNearP = robot->center - robot->radius * plane5N;
            glm::vec3 rightDownNearP = robot->center - robot->radius * plane6N;
        
            glm::vec3 originV = robot -> goVector;

            if (glm::length (robot->center - box1Center) <= robot->radius + box1Radius) {
                robot -> goVector = normalize (reflect (robot -> goVector,robot->center - box1Center));
            
            } else if (glm::length (robot->center - box2Center) <= robot->radius + box2Radius) {
                robot -> goVector = normalize (reflect (robot -> goVector,robot->center - box2Center));
                
            } else if (dot (topNearP - plane1P, plane1N) < 0) {
                robot -> goVector = normalize (reflect (robot -> goVector, plane1N));
            
            } else if (dot (bottomNearP - plane2P, plane2N) < 0) {
                robot -> goVector = normalize (reflect (robot -> goVector, plane2N));
            
            } else if (dot (leftNearP - plane3P, plane3N) < 0) {
                robot -> goVector = normalize (reflect (robot -> goVector, plane3N));
            
            } else if (dot (rightNearP - plane4P, plane4N) < 0) {
                robot -> goVector = normalize (reflect (robot -> goVector, plane4N));
            
            } else if (dot (leftDownNearP - plane5P, plane5N) < 0 ) {
                robot -> goVector = normalize (reflect (robot -> goVector, plane5N));
            
            } else if (dot (rightDownNearP - plane6P, plane6N) < 0) {
                robot -> goVector = normalize (reflect (robot -> goVector, plane6N));
            } else {
            
              for (Geometry * rob : List) {
                  if (rob != robot) {
                      if (glm::length (robot->center - rob->center) < robot->radius + rob->radius) {
                          robot -> goVector = normalize (reflect (robot -> goVector, robot->center - rob->center));;
                      }
                  }
              }
            }
            
            // Dealing with the changing of facing direction.
            glm::vec3 position = robot -> getPosition();
            robot -> move (-position);
            glm::vec3 curV = robot -> goVector;
            float angle;
            if (glm::cross (curV, originV) == glm::vec3 (0, 0, 0)) {
                angle = 180;
                robot -> rotate (angle, glm::vec3(0, 0, 1));
            } else {
                robot -> rotate (57.2958 * acos ((dot (curV, originV) / glm::length (curV) * glm::length(originV))),
                                -normalize(glm::cross (curV, originV)));
            }
            robot -> move (position);
        }
        }
    }
}


void Window::displayCallback(GLFWwindow* window)
{	
	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glUseProgram(boxShader);
    //glUseProgram(sphereProgram);
    glUseProgram(rideProgram);
    
    SphereLight->draw(view, projection, rideProgram, toonProgram);
    
    box->draw(view, projection, boxShader);
    lobby -> draw (view, projection, rideProgram);
    
    glUseProgram(toonProgram);
    
    glUniformMatrix4fv(glGetUniformLocation(toonProgram, "view"), 1, false, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(toonProgram, "projection"), 1, false, glm::value_ptr(projection));
    glUniform3fv(glGetUniformLocation(toonProgram, "view2"), 1, glm::value_ptr(eyePos));
    
    glUseProgram(shaderProgram);
    
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, false, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, false, glm::value_ptr(projection));
    
    //cout << cur2 << " " << endl;
    
    if (cur2 > (appear1 - 3)) {
        if (particle1On) {
            
            if (robotGone1 && !particle1 -> Stop) {
               particle1 -> move (robot1->getPosition() - glm::vec3(4, -8, -3));
            }
            particle1 -> draw (shaderProgram);
            
            if (cur2 > leave1 + 3) {
                particle1On = false;
            }
        }
    
    if (cur2 > appear1 && !robotGone1) {
        
        if (cur2 > leave1) {
            List.erase(std::find(List.begin(), List.end(), robot1));
            robot1 -> still = true;
            particle1On = true;
            robotGone1 = true;
            
        } else {
            robot1->draw (toonProgram, glm::mat4(1.0f));
            particle1On = false;
        }
        
        if (appear1 != 0) {
            List.push_back (robot1);
            robot1 -> still = true;
            appear1 = 0;
        }
        
        if (run1 != 0 && cur2 > run1 ) {
            setDirection (robot1);
            robot1 -> still = false;
            run1 = 0;
        }
    }
    }
    
    
    if (cur2 > (appear2 - 3) ) {
        if (particle2On) {
            
            if (robotGone2 && !particle2 -> Stop) {
               particle2 -> move (robot2->getPosition() - glm::vec3(-4, -2, -3));
            }
            particle2 -> draw (shaderProgram);
            
            if (cur2 > leave2 + 3) {
                particle2On = false;
            }
        }
        
    if (cur2 > appear2 && !robotGone2) {
        
        if (cur2 > leave2) {
            List.erase(std::find(List.begin(), List.end(), robot2));
            robot2 -> still = true;
            particle2On = true;
            robotGone2 = true;
            
        } else {
            robot2->draw (toonProgram, glm::mat4(1.0f));
            particle2On = false;
        }
        
        if (appear2 != 0) {
            List.push_back (robot2);
            robot2 -> still = true;
            appear2 = 0;
        }
        
        if (run2 != 0 && cur2 > run2) {
            setDirection (robot2);
            robot2 -> still = false;
            run2 = 0;
        }
    }
    }
    
    
    if (cur2 > (appear3 - 3)) {
        if (particle3On) {
            
            if (robotGone3 && !particle3 -> Stop) {
               particle3 -> move (robot3->getPosition() - glm::vec3(4, -6, -3));
            }
            particle3 -> draw (shaderProgram);
            
            if (cur2 > leave3 + 3) {
                particle3On = false;
            }
        }
    
    if (cur2 > appear3 && !robotGone3) {
        
        if (cur2 > leave3) {
            List.erase(std::find(List.begin(), List.end(), robot3));
            robot3 -> still = true;
            particle3On = true;
            robotGone3 = true;
            
        } else {
            robot3->draw (toonProgram, glm::mat4(1.0f));
            particle3On = false;
        }
        
        if (appear3 != 0) {
            List.push_back (robot3);
            robot3 -> still = true;
            appear3 = 0;
        }
        
        if (run3 != 0 && cur2 > run3) {
            setDirection (robot3);
            robot3 -> still = false;
            run3 = 0;
        }
    }
    }
    
    if (cur2 > (appear4 - 3)) {
        if (particle4On) {
            
            if (robotGone4 && !particle4 -> Stop) {
               particle4 -> move (robot4->getPosition() - glm::vec3(1, -2, -3));
            }
            particle4 -> draw (shaderProgram);
            
            if (cur2 > leave4 + 3) {
                particle4On = false;
            }
        }
    
    if (cur2 > appear4 && !robotGone4) {
        
        if (cur2 > leave4) {
            List.erase(std::find(List.begin(), List.end(), robot4));
            robot4 -> still = true;
            particle4On = true;
            robotGone4 = true;
            
        } else {
            robot4->draw (toonProgram, glm::mat4(1.0f));
            particle4On = false;
        }
        
        if (appear4 != 0) {
            List.push_back (robot4);
            robot4 -> still = true;
            appear4 = 0;
        }
        
        if (run4 != 0 && cur2 > run4) {
            setDirection (robot4);
            robot4 -> still = false;
            run4 = 0;
        }
    }
    }
    
    robot5->draw (toonProgram, glm::mat4(1.0f));

	// Gets events, including input such as keyboard and mouse or window resizing
	glfwPollEvents();

	// Swap buffers.
	glfwSwapBuffers(window);
}


void Window::mouse_botton_callback (GLFWwindow* window, int button, int action, int mods) {
     
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
       leftPress = true;
    } else {
       leftPress = false;
    }
}

void Window::Cursor_pos_callback (GLFWwindow* window, double xpos, double ypos) {
      

    if (leftPress) {
          
          // Translate points to 3D vectors, and calculate their direction (as vector).
          glm::vec3 last_position = TwoDto3D (last_x, last_y);
          glm::vec3 new_position = TwoDto3D (xpos, ypos);
        
          glm::vec3 direction = new_position - last_position;
        
          // Get the velocity of last to new.
          float velocity = glm::length (direction);
          
          // If velocity is bigger than a small velue.
          if (velocity > 0.0001) {
              // Get the angle and axis to know how our object should rotate.
              float degree = velocity * 100;
              glm::vec3 axis = glm::cross(last_position, new_position);
              
              if (mode1) {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), eyePos) * glm::mat4(1);
                model =  glm::rotate(glm::radians(-degree), axis) * model;
                glm::vec4 pos = model * glm::vec4(0.0, 0.0, 0.0, 1.0);
                eyePos = glm::vec3(pos.x, pos.y, pos.z);
                view = glm::lookAt(Window::eyePos, Window::lookAtPoint, Window::upVector);
              } else if (mode2) {
                SphereLight->rotate(degree, axis);
              }
          }
    }
    
    // Set last_x and last_y to record current position.
    last_x = xpos;
    last_y = ypos;
}

void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    //SphereLight -> move (0.2 * yoffset);
    glm::mat4 model = glm::translate(glm::mat4(1.0f), eyePos) * glm::mat4(1);
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, yoffset)) * model;
    glm::vec4 pos = model * glm::vec4(0.0, 0.0, 0.0, 1.0);
    eyePos = glm::vec3(pos.x, pos.y, pos.z);
    view = glm::lookAt(Window::eyePos, Window::lookAtPoint, Window::upVector);
}

// The function to translate 2D point into 3D vector.
glm::vec3 Window::TwoDto3D(double x, double y) {
    
    glm::vec3 vector;
    float d;
    vector.x = (2.0 * x - width) / width;
    vector.y = (height - 2.0 *y) / height;
    vector.z = 0.0;
    d = glm::length(vector);
    d = (d < 1.0) ? d : 1.0;
    vector.z = sqrtf (1.001 - d*d);
    
    // Calculate the normal factor to make v as normal vector.
    float norFactor = sqrtf (vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
    vector.x = vector.x / norFactor;
    vector.y = vector.y / norFactor;
    vector.z = vector.z / norFactor;
    
    return vector;
}

bool Window::playerCollision (Geometry * robot) {
    
    glm::vec3 topNearP = robot->center - robot->radius * plane1N;
    glm::vec3 bottomNearP = robot->center - robot->radius * plane2N;
    glm::vec3 leftNearP = robot->center - robot->radius * plane3N;
    glm::vec3 rightNearP = robot->center - robot->radius * plane4N;
    glm::vec3 leftDownNearP = robot->center - robot->radius * plane5N;
    glm::vec3 rightDownNearP = robot->center - robot->radius * plane6N;
    
    // If robot entert either two boxes, we should return true for collision.
    if (glm::length (robot->center - box1Center) < robot->radius + box1Radius ||
        glm::length (robot->center - box2Center) < robot->radius + box2Radius) {
        
        return true;
    }
    
    if (dot (topNearP - plane1P, plane1N) < 0  || dot (bottomNearP - plane2P, plane2N) < 0 ||
        dot (leftNearP - plane3P, plane3N) < 0 || dot (rightNearP - plane4P, plane4N) < 0 ||
        dot (leftDownNearP - plane5P, plane5N) < 0 || dot (rightDownNearP - plane6P, plane6N) < 0 ) {
        
        return true;
    }
    
    for (Geometry * rob : List) {
        if (rob != robot) {
            if (glm::length (robot->center - rob->center) < robot->radius + rob->radius) {
                return true;
            }
        }
    }
    
    return false;
}

void Window :: setDirection (Geometry * robot) {
    
    int direction = rand() % 4;
    //cout << "Direction " << direction << endl;
    
    if (direction == 0) {
        
        // Go right
        robot -> goVector = glm::vec3 (1, 0, 0);
        glm::vec3 position = robot -> getPosition();
        robot -> move (-position);
        robot -> rotate (90, glm::vec3 (0, 0, 1));
        robot -> move (position);
    
    } else if (direction == 1) {
        robot -> goVector = glm::vec3 (-1, 0, 0);
        glm::vec3 position = robot -> getPosition();
        robot -> move (-position);
        robot -> rotate (-90, glm::vec3 (0, 0, 1));
        robot -> move (position);
    
    } else if (direction == 2) {
        // Go up
        robot -> goVector = glm::vec3 (0, 1, 0);
        glm::vec3 position = robot -> getPosition();
        robot -> move (-position);
        robot -> rotate (180, glm::vec3 (0, 0, 1));
        robot -> move (position);
    
    } else {
        robot -> goVector = glm::vec3 (0, -1, 0);
    }
}


void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	// Check for a key press.
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			// Close the window. This causes the program to also terminate.
			glfwSetWindowShouldClose(window, GL_TRUE);				
			break;
        
        case GLFW_KEY_W: {
            glm::vec3 position = robot5 -> getPosition();
            robot5 -> move (-position);
            int direction5 = robot5->direction;
            robot5 -> rotate ((180 - direction5), glm::vec3 (0, 0, 1));
            robot5 -> move (position);
            robot5 -> direction = 180;
            
            robot5 -> move (glm::vec3(0, 0.5, 0));
            
            if (playerCollision (robot5)) {
               robot5 -> move (glm::vec3(0, -0.5, 0));
            }
            
            break;
        }
        
        case GLFW_KEY_S: {
            glm::vec3 position = robot5 -> getPosition();
            robot5 -> move (-position);
            int direction5 = robot5->direction;
            robot5 -> rotate ((0 - robot5->direction), glm::vec3 (0, 0, 1));
            robot5 -> move (position);
            robot5 -> direction = 0;
            
            robot5 -> move (glm::vec3(0, -0.5, 0));
            
            if (playerCollision (robot5)) {
                robot5 -> move (glm::vec3(0, 0.5, 0));
            }
            
            break;
        }
                
        case GLFW_KEY_A: {
            glm::vec3 position = robot5 -> getPosition();
            robot5 -> move (-position);
            int direction5 = robot5->direction;
            robot5 -> rotate ((-90 - robot5->direction), glm::vec3 (0, 0, 1));
            robot5 -> move (position);
            robot5 -> direction = -90;
            
            robot5 -> move (glm::vec3(-0.5, 0, 0));
            
            if (playerCollision (robot5)) {
                robot5 -> move (glm::vec3(0.5, 0, 0));
            }
            
            break;
        }
                
        case GLFW_KEY_D: {
           glm::vec3 position = robot5 -> getPosition();
           robot5 -> move (-position);
           int direction5 = robot5->direction;
           robot5 -> rotate ((90 - robot5->direction), glm::vec3 (0, 0, 1));
           robot5 -> move (position);
           robot5 -> direction = 90;
            
           robot5 -> move (glm::vec3(0.5, 0, 0));
            
           if (playerCollision (robot5)) {
               robot5 -> move (glm::vec3(-0.5, 0, 0));
           }
            
           break;
        }
                
        /*
        // Go front
        case GLFW_KEY_I: {
            
            glm::mat4 model = glm::translate(glm::mat4(1.0f), eyePos) * glm::mat4(1);
            model = glm::translate(glm::mat4(1.0), normalize (lookAtPoint - eyePos) ) * model;
            glm::vec4 pos = model * glm::vec4(0.0, 0.0, 0.0, 1.0);
            
            glm::mat4 model2 = glm::translate(glm::mat4(1.0f), lookAtPoint) * glm::mat4(1);
            model2 = glm::translate(glm::mat4(1.0), normalize (lookAtPoint - eyePos)) * model2;
            glm::vec4 pos2 = model2 * glm::vec4(0.0, 0.0, 0.0, 1.0);
            
            eyePos = glm::vec3(pos.x, pos.y, pos.z);
            eyePosRecord = eyePos;
            
            lookAtPoint = glm::vec3(pos2.x, pos2.y, pos2.z);
            viewRecord = lookAtPoint;
            
            view = glm::lookAt(Window::eyePos, Window::lookAtPoint, Window::upVector);
            
            
            break;
        }
                
        // Go back
        case GLFW_KEY_K: {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), eyePos) * glm::mat4(1);
            model = glm::translate(glm::mat4(1.0), normalize (eyePos - lookAtPoint)) * model;
            glm::vec4 pos = model * glm::vec4(0.0, 0.0, 0.0, 1.0);
            
            glm::mat4 model2 = glm::translate(glm::mat4(1.0f), lookAtPoint) * glm::mat4(1);
            model2 = glm::translate(glm::mat4(1.0), normalize (eyePos - lookAtPoint) ) * model2;
            glm::vec4 pos2 = model2 * glm::vec4(0.0, 0.0, 0.0, 1.0);
            
            eyePos = glm::vec3(pos.x, pos.y, pos.z);
            eyePosRecord = eyePos;
            
            lookAtPoint = glm::vec3(pos2.x, pos2.y, pos2.z);
            viewRecord = lookAtPoint;
            
            view = glm::lookAt(Window::eyePos, Window::lookAtPoint, Window::upVector);
            break;
        }
        
        // Go up
        case GLFW_KEY_U: {
            eyePos = eyePos + glm::vec3(0, 3, 0);
            eyePosRecord = eyePos;
                
            glm::mat4 model2 = glm::translate(glm::mat4(1.0f), lookAtPoint) * glm::mat4(1);
            model2 = glm::translate(glm::mat4(1.0), glm::vec3(0, 3, 0)) * model2;
            glm::vec4 pos2 = model2 * glm::vec4(0.0, 0.0, 0.0, 1.0);
                
            viewRecord = lookAtPoint;
            lookAtPoint = glm::vec3(pos2.x, pos2.y, pos2.z);
                                    
            view = glm::lookAt(Window::eyePos, Window::lookAtPoint, Window::upVector);
            break;
        }
       
        // Go down
        case GLFW_KEY_P: {
            eyePos = eyePos + glm::vec3(0, -3, 0);
            eyePosRecord = eyePos;
            
            glm::mat4 model2 = glm::translate(glm::mat4(1.0f), lookAtPoint) * glm::mat4(1);
            model2 = glm::translate(glm::mat4(1.0), glm::vec3(0, -3, 0)) * model2;
            glm::vec4 pos2 = model2 * glm::vec4(0.0, 0.0, 0.0, 1.0);
                
            viewRecord = lookAtPoint;
            lookAtPoint = glm::vec3(pos2.x, pos2.y, pos2.z);
                                    
            view = glm::lookAt(Window::eyePos, Window::lookAtPoint, Window::upVector);
            break;
        }
        
        // Turn left with view point (Camera doesn't move)
        case GLFW_KEY_J: {
            glm::mat4 model2 = glm::translate(glm::mat4(1.0f), lookAtPoint) * glm::mat4(1);
            model2 = glm::translate(glm::mat4(1.0), -eyePos) * model2;
            model2 = glm::rotate(glm::radians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * model2;
            model2 = glm::translate(glm::mat4(1.0), eyePos) * model2;
            glm::vec4 pos2 = model2 * glm::vec4(0.0, 0.0, 0.0, 1.0);
            lookAtPoint = glm::vec3(pos2.x, pos2.y, pos2.z);
            viewRecord = lookAtPoint;
            view = glm::lookAt(Window::eyePos, Window::lookAtPoint, Window::upVector);
            break;
        }
        
        // Turn right with view point (Camera doesn't move)
        case GLFW_KEY_L: {
            glm::mat4 model2 = glm::translate(glm::mat4(1.0f), lookAtPoint) * glm::mat4(1);
            model2 = glm::translate(glm::mat4(1.0), -eyePos) * model2;
            model2 = glm::rotate(glm::radians(-20.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * model2;
            model2 = glm::translate(glm::mat4(1.0), eyePos) * model2;
            glm::vec4 pos2 = model2 * glm::vec4(0.0, 0.0, 0.0, 1.0);
            lookAtPoint = glm::vec3(pos2.x, pos2.y, pos2.z);
            viewRecord = lookAtPoint;
            view = glm::lookAt(Window::eyePos, Window::lookAtPoint, Window::upVector);
            break;
        }
        
        // Stop the first level
        case GLFW_KEY_1:
            mode1 = true;
            mode2 = false;
            break;
        
        // Stop the second level
        case GLFW_KEY_2:
            mode2 = true;
            mode1 = false;
            break;
        
        // Stop the thrid level
        case GLFW_KEY_3:
            
            break;
        */
                
        // activate all level
        case GLFW_KEY_4:
            
            break;
        
        // Turn to car's view
        case GLFW_KEY_5: {
            
            break;
        }
        
        // Turn to camera view.
        case GLFW_KEY_6:
            
            break;
                
		default:
			break;
		}
	}
}
