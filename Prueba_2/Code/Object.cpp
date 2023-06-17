#include"Object.h"

void object::createTexture(const char* path, int textureIndex)
{
    //TODO
    //glGenTextures(1, &texture[textureIndex]);
    //glBindTexture(GL_TEXTURE_2D, texture[textureIndex]);


    //// set the texture wrapping parameters
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);	// set texture wrapping to GL_REPEAT (default wrapping method)
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    //// set texture filtering parameters
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    //int width, height, nrChannels;
    //// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    //unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
    //if (data)
    //{
    //    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    //    glGenerateMipmap(GL_TEXTURE_2D);
    //}
    //else
    //{
    //    std::cout << "Failed to load texture" << std::endl;
    //}
    //stbi_image_free(data);
}
object::~object() {
    delete ourShader;
    delete vertices;
    delete indices;
}
void object::Draw(int a)
{
    
    glBindTexture(GL_TEXTURE_2D, TextureAuxiliar->getTextureFromArray(a));

    ourShader->use();
    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);

}
void object::setTextureClass(GeneralTextureAnimation* auxiliar) {
    TextureAuxiliar = auxiliar;
}
void object::createObject(std::list<float> Vertices, std::list<unsigned int> Indices, const char* VertexShaderSource, const char* FragmentShaderSource, const char* path)
{
    createShader(VertexShaderSource, FragmentShaderSource);
    generateBuffers(VertexShaderSource, FragmentShaderSource, Vertices, Indices);

    //TODO
    if (path != "-") {
        createTexture("resources/textures/image.jpg", 0);
        //createTexture("resources/textures/image1.jpg", 1);
    }
}
void object::createShader(const char* VertexShaderSource, const char* FragmentShaderSource)
{
    ourShader = new Shader(VertexShaderSource, FragmentShaderSource/*,"resources/shaders/geometryShader.txt"*/);

}
void object::generateBuffers(const char* VertexShaderSource, const char* FragmentShaderSource, std::list<float> Vertices, std::list<unsigned int> Indices) {

    std::list<float>::iterator it;
    it = Vertices.begin();
    vertices = new float[Vertices.size()];
    for (int a = 0; a < Vertices.size(); a++) {
        vertices[a] = it._Ptr->_Myval;
        it++;
    }
    std::list<unsigned int>::iterator itI;
    itI = Indices.begin();
    indices = new unsigned int[Indices.size()];
    for (int b = 0; b < Indices.size(); b++) {
        indices[b] = itI._Ptr->_Myval;
        itI++;
    }
    indexSize = Indices.size();


    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    int a = sizeof(vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * Vertices.size(), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * Indices.size(), indices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    Vertices.clear();
    Indices.clear();
}