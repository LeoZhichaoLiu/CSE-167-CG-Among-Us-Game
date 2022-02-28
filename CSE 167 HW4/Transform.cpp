#include "Transform.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>

Transform::Transform (std::string name) {
    Name = name;
}

void Transform::addChild (Node * node) {
    List.push_back (node);
}

void Transform::draw (GLuint shader, glm::mat4 C) {
    
    C = C * M;
    
    for (int i = 0; i < List.size(); i++) {
        List[i]->draw (shader, C);
    }
}

void Transform::update () {
    for (int i = 0; i < List.size(); i++) {
        List[i] -> update();
    }
    
    if (Mode_1) {
       M = M  * glm::rotate(glm::radians(0.1f), glm::vec3(0.0f, 1.0f, 0.0f));
    }
    
    if (Mode_2 && Name == "Wheel Car") {
        M = M * glm::translate (glm::mat4(1.0), glm::vec3(0, -1.7, 0)) * glm::rotate(glm::radians(0.1f), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::translate (glm::mat4(1.0), glm::vec3(0, 1.7, 0));
    }
    
    
    if (Mode_3 && (Name == "F-L car"|| Name == "F-R car" || Name == "B-L car" || Name == "B-R car")) {
        M = M * glm::rotate(glm::radians(-0.3f), glm::vec3(0.0f, 0.0f, 1.0f));
    }
    
}

void Transform::setMode(bool mode_1, bool mode_2, bool mode_3) {
    Mode_1 = mode_1;
    Mode_2 = mode_2;
    Mode_3 = mode_3;
    for (int i = 0; i < List.size(); i++) {
        List[i]->setMode (Mode_1, Mode_2, Mode_3);
    }
}

void Transform::setMode1() {
    Mode_1 = false;
    for (int i = 0; i < List.size(); i++) {
        List[i]->setMode (Mode_1, Mode_2, Mode_3);
    }
}

void Transform::setMode2() {
    Mode_2 = false;
    for (int i = 0; i < List.size(); i++) {
        List[i]->setMode (Mode_1, Mode_2, Mode_3);
    }
}

void Transform::setMode3() {
    Mode_3 = false;
    for (int i = 0; i < List.size(); i++) {
        List[i]->setMode (Mode_1, Mode_2, Mode_3);
    }
}

void Transform::rotate(float degree, glm::vec3 axis) {
    M =  glm::rotate(glm::radians(degree), axis) * M;
}


