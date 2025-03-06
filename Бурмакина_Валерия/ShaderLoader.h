#pragma once
#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

using namespace std;

class Shader {
public:
    GLuint ID; 

    Shader(const char* vertexPath, const char* fragmentPath);
    void use();

    
    void setUniform(const string& name, float v1, float v2, float v3, float v4);
    void setUniform(const string& name, int value);
    void setUniform(const string& name, float value);

private:
    unordered_map<string, GLint> uniformCache;
    GLint getUniformLocation(const string& name);
    string loadShaderSource(const char* path);
    GLuint compileShader(GLenum type, const string& source);
};

#endif
