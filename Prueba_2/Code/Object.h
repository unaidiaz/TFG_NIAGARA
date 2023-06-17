#ifndef OBJECT_H
#define OBJECT_H
#include"GeneralTextureAnimation.h"
#include"shader.h"
#include"Physics.h"
#include<list>
class object {

    unsigned int VBO, VAO, EBO;
    float* vertices;
    unsigned int* indices;
    Shader* ourShader;
    GeneralTextureAnimation* TextureAuxiliar;
    glm::mat4 transform = glm::mat4(1.0f);
    int indexSize;
public:
    ~object();
    Shader* getSahder() {
        return ourShader;
    }
    void setTextureClass(GeneralTextureAnimation* auxiliar);
    void createObject(std::list<float> Vertices, std::list<unsigned int> Indices, const char* VertexShaderSource, const char* FragmentShaderSource, const char* path);
    void Draw(int a);

private:
    void generateBuffers(const char* VertexShaderSource, const char* FragmentShaderSource, std::list<float> Vertices, std::list<unsigned int> Indices);
    void createShader(const char* VertexShaderSource, const char* FragmentShaderSource);
    void createTexture(const char* path, int textureIndex);

};

#endif
