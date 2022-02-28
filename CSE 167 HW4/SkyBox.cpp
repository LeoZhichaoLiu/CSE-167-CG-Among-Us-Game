#include "SkyBox.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>

//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

SkyBox::SkyBox()
{
    faces = {
        "background/right.jpg",
        "background/left.jpg",
        "background/top.jpg",
        "background/bottom.jpg",
        "background/front.jpg",
        "background/back.jpg"
    };
    
    points = {
        // positions
        glm::vec3(-500.0f,  500.0f, -500.0f),
        glm::vec3(-500.0f, -500.0f, -500.0f),
        glm::vec3(500.0f, -500.0f, -500.0f),
        glm::vec3(500.0f, -500.0f, -500.0f),
        glm::vec3(500.0f,  500.0f, -500.0f),
        glm::vec3(-500.0f,  500.0f, -500.0f),

        glm::vec3(-500.0f, -500.0f,  500.0f),
        glm::vec3(-500.0f, -500.0f, -500.0f),
        glm::vec3(-500.0f,  500.0f, -500.0f),
        glm::vec3(-500.0f,  500.0f, -500.0f),
        glm::vec3(-500.0f,  500.0f,  500.0f),
        glm::vec3(-500.0f, -500.0f,  500.0f),

        glm::vec3(500.0f, -500.0f, -500.0f),
        glm::vec3(500.0f, -500.0f,  500.0f),
        glm::vec3(500.0f,  500.0f,  500.0f),
        glm::vec3(500.0f,  500.0f,  500.0f),
        glm::vec3(500.0f,  500.0f, -500.0f),
        glm::vec3(500.0f, -500.0f, -500.0f),

        glm::vec3(-500.0f, -500.0f,  500.0f),
        glm::vec3(-500.0f,  500.0f,  500.0f),
        glm::vec3(500.0f,  500.0f,  500.0f),
        glm::vec3(500.0f,  500.0f,  500.0f),
        glm::vec3(500.0f, -500.0f,  500.0f),
        glm::vec3(-500.0f, -500.0f,  500.0f),

        glm::vec3(-500.0f,  500.0f, -500.0f),
        glm::vec3(500.0f,  500.0f, -500.0f),
        glm::vec3(500.0f,  500.0f,  500.0f),
        glm::vec3(500.0f,  500.0f,  500.0f),
        glm::vec3(-500.0f,  500.0f,  500.0f),
        glm::vec3(-500.0f,  500.0f, -500.0f),

        glm::vec3(-500.0f, -500.0f, -500.0f),
        glm::vec3(-500.0f, -500.0f,  500.0f),
        glm::vec3(500.0f, -500.0f, -500.0f),
        glm::vec3(500.0f, -500.0f, -500.0f),
        glm::vec3(-500.0f, -500.0f,  500.0f),
        glm::vec3(500.0f, -500.0f,  500.0f)
    };
    
    
    // Set the model matrix to an identity matrix.
    model = glm::mat4(1);

    // Set the color.
    color = glm::vec3(1, 0, 0);

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
    
    // Unbind the VBO/VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    cubemapTexture = loadCubemap(faces);
    
}

SkyBox::~SkyBox()
{
    // Delete the VBO and the VAO.ssaz
    glDeleteBuffers(1, VBO);
    glDeleteVertexArrays(1, &VAO);
}

void SkyBox::draw(const glm::mat4& view, const glm::mat4& projection, GLuint shader)
{
    glDepthMask(GL_FALSE);
    
     // Actiavte the shader program
    glUseProgram(shader);
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);

    // Get the shader variable locations and send the uniform data to the shader
    glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, false,  glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, false, glm::value_ptr(projection));
    
    // ... set view and projection matrix
    glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthMask(GL_TRUE);
}

void SkyBox::update(){}

unsigned int SkyBox::loadCubemap(vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

void SkyBox::rotate(float degree, glm::vec3 axis) {
    model =  glm::rotate(glm::radians(degree), axis) * model;
}
