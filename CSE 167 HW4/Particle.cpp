//
//  Particle.cpp
//  CSE 167
//
//  Created by 刘智超 on 2020/12/6.
//

#include "Particle.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>

Particle :: Particle (glm::vec3 robotPos) {
    
    pointSize = 2;
    particleSize = 100;
            
    for (int i = 0; i < particleSize; i++) {
        float degree = rand () % 360;
        float axis = float (rand () % 10) / 10;
        float xValue = axis * cos (degree);
        float yValue = axis * sin (degree);
        float zValue = float (rand () % 30) / 10;
        
        velocity.push_back (glm::vec3 (xValue, yValue, zValue));
        indexes.push_back (i);
    }
    
    /*
    for (glm::vec3 ref : velocity) {
        std::cout << ref.x << " " << ref.y << " " << ref.z << std::endl;
    } */
    
    model = glm::mat4(1);
    model = glm::translate (glm::mat4(1.0), robotPos) * model;
    
    color = glm::vec3(1, 1, 1);
    
    // Generate a vertex array (VAO) and a vertex buffer objects (VBO).
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    // Bind VAO
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * velocity.size(), velocity.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    
    /*
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(int) * indexes.size(), indexes.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(int), 0);
    */
     
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    // Unbind from the VBO and VAO.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
}

Particle :: ~Particle () {
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void Particle :: update (int Case, float time) {
    
    float degree ;
    
    if (Case == 1) {
        degree = 0.1f;
        pointSize = 2;
        pointSize = pointSize * (3 - time);
        cout << time << endl;
        glPointSize (pointSize);
    } else {
        degree = -0.1f;
        pointSize = 2;
        pointSize = pointSize * (3 - time);
        glPointSize (pointSize);
    }
    
    glm::vec4 pos = model * glm::vec4(0.0, 0.0, 0.0, 1.0);
    position = glm::vec3(pos.x, pos.y, pos.z);
    model = glm::translate(glm::mat4(1.0), -position) * model;
    model = model * glm::rotate(glm::radians(degree), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(glm::mat4(1.0f), position) * model;
    
    
    /*for (glm::vec3 ref : velocity) {
        ref = time/2 * ref;
    }*/
}

void Particle :: draw (GLuint shader) {
    
    glUseProgram(shader);
    
    glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniform3fv(glGetUniformLocation(shader, "color"), 1, glm::value_ptr(color));
    
    // Bind VAO
    glBindVertexArray(VAO);
    // Set the point size
    glPointSize(pointSize);
    
    // Draw the points
    glDrawArrays(GL_POINTS, 0, velocity.size());
    
    // Unbind the VAO and shader program
    glBindVertexArray(0);
    glUseProgram(0);
}

void Particle::move (glm::vec3 factor) {
    model = glm::translate(glm::mat4(1.0f), factor) * model;
    glm::vec4 pos = model * glm::vec4(0.0, 0.0, 0.0, 1.0);
    position = glm::vec3(pos.x, pos.y, pos.z);
    Stop = true;
}
