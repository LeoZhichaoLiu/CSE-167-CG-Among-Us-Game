//
//  Light.cpp
//  CSE 167
//
//
#include "PointLight.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>

PointLight::PointLight (std::string objFilename) {
    
    
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
           if (label == "v") {
               
              glm::vec3 point;
              ss >> point.x >> point.y >> point.z;

              // Process the point. For example, you can save it to a.
              points.push_back(point);
          } else if (label == "vn") {
            
              glm::vec3 normal2;
              ss >> normal2.x >> normal2.y >> normal2.z;
            
              normal.push_back(normal2);
            
          } else if (label == "f") {
            
            glm::ivec3 face1;
            string a;
            string b;
            string c;
            
            ss >> a >> b >> c;
            
            face1.x = stoi (a.substr(0, a.find("\\"))) - 1;
            face1.y = stoi (b.substr(0, b.find("\\"))) - 1;
            face1.z = stoi (c.substr(0, c.find("\\"))) - 1;
            
            face.push_back(face1);
          }
       }
      cout << "Success!";
    } else {
        
      std::cerr << "Can't open the file " << objFilename << std::endl;
    }
    
   objFile.close();

   for (int i = 0; i < points.size(); i++) {
      points[i].x *= 0.1;
      points[i].y *= 0.1;
      points[i].z *= 0.1;
   }
    
   for (int i = 0; i < normal.size(); i++) {
       float factor = sqrt(normal[i].x * normal[i].x + normal[i].y * normal[i].y + normal[i].z * normal[i].z);
       normal[i].x = (normal[i].x / factor + 1) / 2;
       normal[i].y = (normal[i].y / factor + 1) / 2;
       normal[i].z = (normal[i].z / factor + 1) / 2;
    }
    
    material = new Material ();
    material -> ambient = glm::vec3 (1, 1, 1);
    material -> diffuse = glm::vec3 (0, 0, 0);
    material -> specular = glm::vec3 (0, 0, 0);
    material -> shininess = 0.8;
  
    model = glm::mat4(1);
    color = glm::vec3(0.4, 0.3, 0.12);
    pointSize = 1;
    position = glm::vec3(0, 2, 7);
    model = glm::translate(glm::mat4(1.0f), position) * model;
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(2, &VBO[0]);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * points.size(), points.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normal.size(), normal.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(glm::ivec3) * face.size(), face.data(), GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

PointLight::~PointLight()
{
    // Delete the VBO and the VAO.ssaz
    glDeleteBuffers(2, VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
}

void PointLight::draw(const glm::mat4& view, const glm::mat4& projection, GLuint shader, GLuint shader2) {
    
    // Actiavte the shader program
    glUseProgram(shader);
    
    glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, false, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, false, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
    
    // Update the information for light sphere (to other 3D model).
    glUniform3fv(glGetUniformLocation(shader, "light_color"), 1, glm::value_ptr(color));
    glUniform3fv(glGetUniformLocation(shader, "color"), 1, glm::value_ptr(color));
    glUniform3fv(glGetUniformLocation(shader, "LightPos"), 1, glm::value_ptr(position));
    
    // Update the material of the light sphere
    glUniform3fv(glGetUniformLocation(shader, "ambient"), 1, glm::value_ptr(material->ambient));
    glUniform3fv(glGetUniformLocation(shader, "diffuse"), 1, glm::value_ptr(material->diffuse));
    glUniform3fv(glGetUniformLocation(shader, "specular"), 1, glm::value_ptr(material->specular));
    glUniform1f(glGetUniformLocation(shader, "shininess"), material->shininess);
    
    glUseProgram (shader2);
    glUniformMatrix4fv(glGetUniformLocation(shader2, "view"), 1, false, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader2, "projection"), 1, false, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(shader2, "model"), 1, GL_FALSE, glm::value_ptr(model));
    
    // Update the information for light sphere (to other 3D model).
    glUniform3fv(glGetUniformLocation(shader2, "light_color"), 1, glm::value_ptr(color));
    glUniform3fv(glGetUniformLocation(shader2, "color"), 1, glm::value_ptr(color));
    glUniform3fv(glGetUniformLocation(shader2, "LightPos"), 1, glm::value_ptr(position));
    
    // Update the material of the light sphere
    glUniform3fv(glGetUniformLocation(shader2, "ambient"), 1, glm::value_ptr(material->ambient));
    glUniform3fv(glGetUniformLocation(shader2, "diffuse"), 1, glm::value_ptr(material->diffuse));
    glUniform3fv(glGetUniformLocation(shader2, "specular"), 1, glm::value_ptr(material->specular));
    glUniform1f(glGetUniformLocation(shader2, "shininess"), material->shininess);
    
    
    // Bind the VAO
    glBindVertexArray(VAO);

    // Set point size
    glPointSize(pointSize);

    // Draw the points
    glDrawArrays(GL_POINTS, 0, points.size());
    glDrawElements(GL_TRIANGLES, 3*face.size(), GL_UNSIGNED_INT, 0);
    
    // Unbind the VAO and shader program
    glBindVertexArray(0);
    glUseProgram(0);
}

void PointLight::update() {}

void PointLight::rotate(float degree, glm::vec3 axis) {
    model =  glm::rotate(glm::radians(degree), axis) * model;
    glm::vec4 pos = model * glm::vec4(0.0, 0.0, 0.0, 1.0);
    position = glm::vec3(pos.x, pos.y, pos.z);
}

void PointLight::move(double yoffset) {
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, yoffset)) * model;
    glm::vec4 pos = model * glm::vec4(0.0, 0.0, 0.0, 1.0);
    position = glm::vec3(pos.x, pos.y, pos.z);
    cout << pos.x << " " << pos.y << " " << pos.z << endl;
}

