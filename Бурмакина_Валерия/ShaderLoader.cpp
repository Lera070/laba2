#include "ShaderLoader.h"
#include <iostream>

using namespace std;


string Shader::loadShaderSource(const char* path) {
    fstream file(path);
    stringstream buffer;
    if (file) {
        buffer << file.rdbuf();
        file.close();
    }
    else {
        cerr << "Не удалось загрузить шейдерный файл: " << path << endl;
    }
    return buffer.str();
}


GLuint Shader::compileShader(GLenum type, const string& source) {
    GLuint shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
        cerr << "Ошибка компиляции шейдера: " << infoLog << endl;
    }

    return shader;
}


Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    string vertexCode = loadShaderSource(vertexPath);
    string fragmentCode = loadShaderSource(fragmentPath);

    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexCode);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentCode);

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    GLint success;
    GLchar infoLog[1024];
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 1024, nullptr, infoLog);
        cerr << "Ошибка линковки программы: " << infoLog << endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}


void Shader::use() {
    glUseProgram(ID);
}


GLint Shader::getUniformLocation(const string& name) {
    if (uniformCache.find(name) == uniformCache.end()) {
        uniformCache[name] = glGetUniformLocation(ID, name.c_str());
    }
    return uniformCache[name];
}


void Shader::setUniform(const string& name, float v1, float v2, float v3, float v4) {
    glUniform4f(getUniformLocation(name), v1, v2, v3, v4);
}

void Shader::setUniform(const string& name, int value) {
    glUniform1i(getUniformLocation(name), value);
}

void Shader::setUniform(const string& name, float value) {
    glUniform1f(getUniformLocation(name), value);
}