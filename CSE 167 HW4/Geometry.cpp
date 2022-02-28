#include "Geometry.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>

Geometry::Geometry (std::string obj, std::string name) {
    
    Geometry::init (obj);
    
    material = new Material ();
    
    if (name == "1yellow") {
        material -> ambient = glm::vec3 (0.964, 0.964, 0.342);
        material -> diffuse = glm::vec3 (0.964, 0.964, 0.342);
        material -> specular = glm::vec3 (0.964, 0.964, 0.342);
        material -> shininess = 0.6;
            
    } else if (name == "2blue") {
            
        material -> ambient = glm::vec3 (0.074, 0.1803, 0.8196);
        material -> diffuse = glm::vec3 (0.074, 0.1803, 0.8196);
        material -> specular = glm::vec3 (0.074, 0.1803, 0.8196);
        material -> shininess = 0.6;
            
    } else if (name == "3brown") {
            
        material -> ambient = glm::vec3 (0.443, 0.2862, 0.11372);
        material -> diffuse = glm::vec3 (0.443, 0.2862, 0.1137);
        material -> specular = glm::vec3 (0.443, 0.2862, 0.1137);
        material -> shininess = 0.4;
        
    } else if (name == "4orange") {
        
        material -> ambient = glm::vec3 (0.945, 0.4902, 0.047);
        material -> diffuse = glm::vec3 (0.945, 0.4902, 0.047);
        material -> specular = glm::vec3 (0.945, 0.4902, 0.047);
        material -> shininess = 0.4;
        
    } else if (name == "5red") {
        material -> ambient = glm::vec3 (0.7725, 0.0705, 0.0666);
        material -> diffuse = glm::vec3 (0.7725, 0.0705, 0.0666);
        material -> specular = glm::vec3 (0.7725, 0.0705, 0.0666);
        material -> shininess = 0.4;
        
    }
    
    startDirection = 4 * rand ();

    model = glm::mat4(1);
    model = model * glm::rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    
    // Generate a Vertex Array (VAO) and Vertex Buffer Object (VBO)
    glGenVertexArrays(1, &VAO);
    glGenBuffers(2, &VBO[0]);
    glGenBuffers(1, &EBO);
          
    // Bind VAO
    glBindVertexArray(VAO);
    
    // Bind VBO to the bound VAO, and store the point data
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * points.size(), points.data(), GL_STATIC_DRAW);
    // Enable Vertex Attribute 0 to pass point data through to the shader
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
        
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normal.size(), normal.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
        
    // Generate EBO, bind the EBO to the bound VAO, and send the index data
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(glm::ivec3) * face.size(), face.data(), GL_STATIC_DRAW);
        
    // Unbind the VBO/VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Geometry::~Geometry () {
    glDeleteBuffers(1, VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
}


void Geometry::draw(GLuint shader, glm::mat4 C) {
    
    newModel = C * model;
    
    glUseProgram(shader);
    
    glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(newModel));
    glUniform3fv(glGetUniformLocation(shader, "ambient"), 1, glm::value_ptr(material->ambient));
    glUniform3fv(glGetUniformLocation(shader, "diffuse"), 1, glm::value_ptr(material->diffuse));
    glUniform3fv(glGetUniformLocation(shader, "specular"), 1, glm::value_ptr(material->specular));
    glUniform1f(glGetUniformLocation(shader, "shininess"), material->shininess);
    
    glBindVertexArray(VAO);
        
    glDrawElements(GL_TRIANGLES, 3*face.size(), GL_UNSIGNED_INT, 0);
        
    glBindVertexArray(0);
    glUseProgram(0);
}


void Geometry::update() {
    /*
    pos = newModel * glm::vec4(0.0, 0.0, 0.0, 1.0);
    glm::vec3 position = glm::vec3(pos.x, pos.y, pos.z);
    
    if (passEye) {
      *(newEye) = position;
      *(newView) = glm::lookAt(*(newEye), *(newLook), glm::vec3 (0, 1, 0));
    }
    */
    
    this -> move (0.01f * goVector);
    
}

void Geometry::setEye (glm::vec3 * eye, glm::vec3 * Look, glm::mat4 * view) {

    newEye = eye;
    newLook = Look;
    newView = view;
    passEye = true;
}

void Geometry::setFalse () {
    passEye = false;
}

void Geometry::rotate(float degree, glm::vec3 axis) {
    model =  glm::rotate(glm::radians(degree), axis) * model;
}

void Geometry::init (std::string objFilename) {
    
    std::vector< glm::vec3 > faceV, faceN;
    std::vector< glm::vec3 > temp_vertex;
    std::vector< glm::vec3 > temp_normals;
        
    std: ifstream objFile(objFilename); // The obj file we are reading.
        
    // Check whether the file can be opened.
    if (objFile.is_open())
    {
        std::string line; // A line in the file.
    
        // Read lines from the file.
        while (std::getline(objFile, line))
        {
            // Turn the line into a string stream for processing.
            std::stringstream ss;
            ss << line;
                
            // Read the first word of the line.
            std::string label;
            ss >> label;
    
            // If the line is about vertex (starting with a "v").
            if (label == "v")
            {
                // Read the later three float numbers and use them as the
                // coordinates.
                glm::vec3 point;
                ss >> point.x >> point.y >> point.z;
    
                // Process the point. For example, you can save it to a.
                temp_vertex.push_back(point);
                    
            } else if (label == "vn") {
                    
                glm::vec3 normal2;
                ss >> normal2.x >> normal2.y >> normal2.z;
                    
                temp_normals.push_back(normal2);
        
            } else if (label == "f") {
                    
                glm::ivec3 face1;
                glm::ivec3 face3;
                string a;
                string b;
                string c;
                    
                ss >> a >> b >> c;
                    
                size_t afirst = a.find("/");
                size_t asecond = a.find("/", afirst+1);
                    
                size_t bfirst = b.find("/");
                size_t bsecond = b.find("/", bfirst+1);
                
                size_t cfirst = c.find("/");
                size_t csecond = c.find("/", cfirst+1);
                    
                face1.x = stoi (a.substr(0, afirst)) - 1;
                face1.y = stoi (b.substr(0, bfirst)) - 1;
                face1.z = stoi (c.substr(0, cfirst)) - 1;
                    
                face3.x = stoi (a.substr(asecond+1)) - 1;
                face3.y = stoi (b.substr(bsecond+1)) - 1;
                face3.z = stoi (c.substr(csecond+1)) - 1;
                    
                faceV.push_back(face1);
                faceN.push_back(face3);
                    
            }
                
        }
    }
    else
    {
        std::cerr << "Can't open the file " << objFilename << std::endl;
    }
    objFile.close();
        
    
    for (unsigned int i = 0; i < faceV.size(); i++ ) {
        points.push_back (temp_vertex[faceV[i].x]);
        points.push_back (temp_vertex[faceV[i].y]);
        points.push_back (temp_vertex[faceV[i].z]);
        normal.push_back (temp_normals[faceN[i].x]);
        normal.push_back (temp_normals[faceN[i].y]);
        normal.push_back (temp_normals[faceN[i].z]);
        face.push_back (glm::vec3 (3*(i+1)-3, 3*(i+1)-2, 3 * (i+1) - 1));
    }
    
    for (int i = 0; i < points.size(); i++) {
        points[i].x *= 0.6;
        points[i].y *= 0.6;
        points[i].z *= 0.6;
    }
    
    GLfloat xMin = INFINITY;
    GLfloat xMax = -INFINITY;
    GLfloat yMin = INFINITY;
    GLfloat yMax = -INFINITY;
    GLfloat zMin = INFINITY;
    GLfloat zMax = -INFINITY;
    
    
    for (glm::vec3 element : points) {
        if (element.x < xMin) {
            xMin = element.x;
        }
        if (element.x > xMax) {
            xMax = element.x;
        }
        if (element.y < yMin) {
            yMin = element.y;
        }
        if (element.y > yMax) {
            yMax = element.y;
        }
        if (element.z < zMin) {
            zMin = element.z;
        }
        if (element.z > zMax) {
            zMax = element.z;
        }
    }
    
    GLfloat radius1 = max (abs(xMax), abs(xMin));
    GLfloat radius2 = max (abs(yMax), abs(yMin));
    GLfloat radius3 = max (abs(zMax), abs(zMin));
    GLfloat radius4 = max (radius1, radius2);
    //radius = max (radius3, radius4);
    radius = 0.6;
    position = glm::vec3 (0, 0, 0);
    center = position;
    
}

void Geometry::setMode (bool mode_1, bool mode_2, bool mode_3){}

void Geometry::move (glm::vec3 factor) {
    model = glm::translate(glm::mat4(1.0f), factor) * model;
    glm::vec4 pos = model * glm::vec4(0.0, 0.0, 0.0, 1.0);
    position = glm::vec3(pos.x, pos.y, pos.z);
    center = position;
}

glm::vec3 Geometry::getPosition () {
    return position;
}




