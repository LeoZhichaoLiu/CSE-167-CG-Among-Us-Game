#include "PointCloud.h"

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

PointCloud::PointCloud(std::string objFilename, GLfloat pointSize) 
	: pointSize(pointSize)
{
    
    std::vector< glm::vec3 > faceV, faceT, faceN;
    std::vector< glm::vec3 > temp_vertex;
    std::vector< glm::vec3 > temp_normals;
    std::vector< glm::vec2 > temp_texture;
    
    std: ifstream objFile(objFilename); // The obj file we are reading.
    
    int time = 0;
    
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
                
            } else if (label == "vt") {
                
                glm::vec2 texture2;
                ss >> texture2.x >> texture2.y;
                
                temp_texture.push_back (texture2);
                
                /*
                if (time == 0) {
                    cout << texture2.x << " " << texture2.y  << endl;
                }
                time = 1;
                */

                
            } else if (label == "vn") {
                       
                glm::vec3 normal2;
                ss >> normal2.x >> normal2.y >> normal2.z;
                
                temp_normals.push_back(normal2);
                
                
            } else if (label == "f") {
                
                glm::ivec3 face1;
                glm::ivec3 face2;
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
                
                face2.x = stoi (a.substr(afirst+1, asecond)) - 1;
                face2.y = stoi (b.substr(bfirst+1, bsecond)) - 1;
                face2.z = stoi (c.substr(cfirst+1, csecond)) - 1;
                
                face3.x = stoi (a.substr(asecond+1)) - 1;
                face3.y = stoi (b.substr(bsecond+1)) - 1;
                face3.z = stoi (c.substr(csecond+1)) - 1;
                
                faceV.push_back(face1);
                faceT.push_back (face2);
                faceN.push_back(face3);
                
                /*
                if (time == 0) {
                    cout << face1.x << " " << face1.y << " " << face1.z << " " << face2.x << " " << face2.y << " " << face2.z << endl;
                }
                time = 1;
                */
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
        
        texture.push_back (temp_texture[faceT[i].x]);
        texture.push_back (temp_texture[faceT[i].y]);
        texture.push_back (temp_texture[faceT[i].z]);
        
        normal.push_back (temp_normals[faceN[i].x]);
        normal.push_back (temp_normals[faceN[i].y]);
        normal.push_back (temp_normals[faceN[i].z]);
        face.push_back (glm::vec3 (3*(i+1)-3, 3*(i+1)-2, 3 * (i+1) - 1));
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
    
    for (int i = 0; i < points.size(); i++) {
        points[i].x -= (xMin + xMax) / 2;
        points[i].y -= (yMin + yMax) / 2;
        points[i].z -= (zMin + zMax) / 2;
    }
    
    GLfloat longest = -INFINITY;
    
    for (glm::vec3 element : points) {
        GLfloat dis = sqrt(element.x * element.x + element.y * element.y + element.z * element.z);
        if (dis > longest) {
            longest = dis;
        }
    }
    
    GLfloat factor = 13 / longest;
    
    for (int i = 0; i < points.size(); i++) {
        points[i].x *= factor;
        points[i].y *= factor;
        points[i].z *= factor;
    }
    
    material = new Material ();
    
            
    if (objFilename == "OBJ/amongus_lobby.obj") {
        material -> ambient = glm::vec3 (0.215, 0.4745, 0.215);
        material -> diffuse = glm::vec3 (0.07568, 0.71424, 0.07568);
        material -> specular = glm::vec3 (0.533, 0.727811, 0.633);
        material -> shininess = 0.2;
    }
    
	// Set the model matrix to an identity matrix. 
	model = glm::mat4(1);
    model = model * glm::rotate(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	// Set the color. 
	color = glm::vec3(1, 0, 0);

	// Generate a Vertex Array (VAO) and Vertex Buffer Object (VBO)
	glGenVertexArrays(1, &VAO);
	glGenBuffers(3, &VBO[0]);
    glGenBuffers(1, &EBO);
      
	// Bind VAO
	glBindVertexArray(VAO);

	// Bind VBO to the bound VAO, and store the point data
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * points.size(), points.data(), GL_STATIC_DRAW);
	// Enable Vertex Attribute 0 to pass point data through to the shader
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    
    // Bind VBO to the bound VAO, and store the normal data.
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normal.size(), normal.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    
    // Bind VBO to the bound VAO, and store the texture data.
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * texture.size(), texture.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
    
    
    // Generate EBO, bind the EBO to the bound VAO, and send the index data (three points with their normals and texture coordinate).
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(glm::ivec3) * face.size(), face.data(), GL_STATIC_DRAW);
    
	// Unbind the VBO/VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
    
    stbi_set_flip_vertically_on_load(true);
    lobbyTexture = loadLobby ("background/amongus_lobby.png");//("background/back.jpg");//("background/amongus_lobby.png");
}

PointCloud::~PointCloud() 
{
	// Delete the VBO and the VAO.ssaz
	glDeleteBuffers(1, VBO);
    glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
}

void PointCloud::draw(const glm::mat4& view, const glm::mat4& projection, GLuint shader)
{
	// Actiavte the shader program 
	glUseProgram(shader);

	// Get the shader variable locations and send the uniform data to the shader 
	glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, false, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, false, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniform3fv(glGetUniformLocation(shader, "color"), 1, glm::value_ptr(color));

    glUniform3fv(glGetUniformLocation(shader, "ambient"), 1, glm::value_ptr(material->ambient));
    glUniform3fv(glGetUniformLocation(shader, "diffuse"), 1, glm::value_ptr(material->diffuse));
    glUniform3fv(glGetUniformLocation(shader, "specular"), 1, glm::value_ptr(material->specular));
    glUniform1f(glGetUniformLocation(shader, "shininess"), material->shininess);
    
	// Bind the VAO
	glBindVertexArray(VAO);
    glBindTexture(GL_TEXTURE_2D, lobbyTexture);
    
	// Set point size
	glPointSize(pointSize);

	// Draw the points
    glDrawElements(GL_TRIANGLES, 3*face.size(), GL_UNSIGNED_INT, 0);
    
	// Unbind the VAO and shader program
	glBindVertexArray(0);
	glUseProgram(0);
}

unsigned int PointCloud::loadLobby(string lobby)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    
    unsigned char *data = stbi_load(lobby.c_str(), &width, &height, &nrChannels, 0);
    
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
    } else {
        std::cout << "Cubemap tex failed to load at path: " << lobby << std::endl;
    }
    stbi_image_free(data);

    return textureID;
}


void PointCloud::update(){ }

void PointCloud::updatePointSize(GLfloat size) 
{
    pointSize = pointSize * size;
    glPointSize(pointSize);
}

void PointCloud::spin(float deg)
{
	// Update the model matrix by multiplying a rotation matrix
	model = model * glm::rotate(glm::radians(deg), glm::vec3(0.0f, 1.0f, 0.0f));
}

void PointCloud::rotate(float degree, glm::vec3 axis) {
    model =  glm::rotate(glm::radians(degree), axis) * model;
}

void PointCloud::scale (double factor) {
    model = glm::scale(glm::vec3(factor, factor, factor)) * model;
}
