#ifndef GENERALTEXTUREANIMATION_H
#define GENERALTEXTUREANIMATION_H

#include"LocalTextureAnimation.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include"General.h"
#define STB_IMAGE_IMPLEMENTATION

#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"

#include<string>

#include"DevIL/include/IL/il.h"
#include "DevIL/include/IL/ilu.h"
#include"DevIL/include/IL/ilut.h"
enum class TypeOfModify
{
    MIMPMAPS,
    ALIENIFY,
    BLURAVG,
    BLURGAUSSIAN,
    CONTRAST,
    EQUALIZE,
    GAMMACORRECT,
    NEGATIVE,
    NOISIFY,
    PIXELIZE,
    SHARPEN
};

class Texture {
public:
    int width, height,numberOfChanels;
    std::string path,name,format;
    GLuint textureMemLoc;

    float amountAvBlur=0;
    bool alienfy = false;
    float contrastAmount = 0;
    bool negativity = false;
    float gaussianBlur = 0;
    bool equalization = false;
    float noiseAmount = 0;
    float gammaCorrectionAmount = 0;
    float pixelationAmount;

};
class GeneralTextureAnimation
{
public:
    GeneralTextureAnimation();
    void useActualTexture(LocalTextureAnimation* local);
    void loadAnimation(std::string path);
    void IncreaseArray();
    GLuint getTextureFromArray(int a);
    void showImguiImagesAndInfo();
    void showIndividualImageInfo(int a);
    void TexturePartition(int textureID,int rows,int columns,int width,int height);
    Texture* textures;
    int actualNumberOfTextures;
    int actualNumberOfPlacesInTextures;
    int toIncreaseMemory;
    int sizeOfArray;
    int TextureRandomScope[2];
    //imgui
    bool showIndividualImage = false;
    int imageToshow;
    bool showImguiImages = false;
    //partition
    int partitionWith = 0;
    int partitionHeight = 0;
    bool showPartitionErrorImage = false;
    //animation
    float maxTimePerFrame;
    bool loop;

    //edit
    void ModifyTexture(TypeOfModify type, int image, float a=-1);
    
};
#endif
