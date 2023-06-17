#include"GeneralTextureAnimation.h"


//#include "stb_image.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>



#define biteToKb 1024

std::string getFileNameFromPath(std::string path) {
    std::string toReturn;
    bool start = false;
    for (int a = path.length(); a != 0; a--)
    {
        if (start)
        {
            if (path[a] == '\\') {
                std::reverse(toReturn.begin(), toReturn.end());
                return toReturn;
            }
            toReturn += path[a];
        }
        else if (!start && path[a] == '.')
        {
            start = true;
        }
    }
    return "NoName";
}
std::string getFileFormatFromPath(std::string path) {
    std::string toReturn;
    bool start = false;
    for (int a = path.length(); a != 0; a--)
    {
        if (path[a] == '.') 
        {
            std::reverse(toReturn.begin(), toReturn.end());
            return toReturn;
        }
        else {
            toReturn += path[a];
        }
    }
    return "NoFormat";
}

//////////////////////////////////////////////////////////////////////////

GeneralTextureAnimation::GeneralTextureAnimation()
{
    maxTimePerFrame = 1;
    toIncreaseMemory = 5;
    actualNumberOfTextures = 0;
    actualNumberOfPlacesInTextures = 5;
    sizeOfArray = 5;
    loop = true;
    textures = new Texture[toIncreaseMemory];
    TextureRandomScope[0] = 0;
    TextureRandomScope[1] = 1;
}
GLuint GeneralTextureAnimation::getTextureFromArray(int a) {
    return textures[a].textureMemLoc;
}


void GeneralTextureAnimation::IncreaseArray()
{
    sizeOfArray += toIncreaseMemory;
    Texture* auxiiarList = new Texture[sizeOfArray];
    actualNumberOfPlacesInTextures = toIncreaseMemory;
    for (int a = 0; a < actualNumberOfTextures; a++) {
        auxiiarList[a] = textures[a];
    }
    delete[] textures;
    textures = auxiiarList;
}
void GeneralTextureAnimation::useActualTexture(LocalTextureAnimation* local)
{

    //glBindTexture(GL_TEXTURE_2D, textures[local->getActualtexture()]);
}
void GeneralTextureAnimation::loadAnimation(std::string path)
{
    ilInit();
    iluInit();
    ILboolean success = ilutRenderer(ILUT_OPENGL);
    if (actualNumberOfPlacesInTextures == 0)
    {
        IncreaseArray();
    }
    // path = "resources/textures/q.PNG";
    glGenTextures(1, &textures[actualNumberOfTextures].textureMemLoc);
    glBindTexture(GL_TEXTURE_2D, textures[actualNumberOfTextures].textureMemLoc);
    ilGenImages(1, &textures[actualNumberOfTextures].textureMemLoc);
    ilBindImage(textures[actualNumberOfTextures].textureMemLoc);
    std::wstring widestr = std::wstring(path.begin(), path.end());
    const wchar_t* widecstr = widestr.c_str();
    success = ilLoadImage((const ILstring)widecstr);
    ILenum o = ilGetError();
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    int width, height, nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    //unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);





    if (success)
    {
        width = ilGetInteger(IL_IMAGE_WIDTH);
        height = ilGetInteger(IL_IMAGE_HEIGHT);
        ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);


        textures[actualNumberOfTextures].name = getFileNameFromPath(path);
        textures[actualNumberOfTextures].height = height;
        textures[actualNumberOfTextures].width = width;
        textures[actualNumberOfTextures].numberOfChanels = 3;
        textures[actualNumberOfTextures].path = path;
        textures[actualNumberOfTextures].format = getFileFormatFromPath(path);
        ILubyte* data = ilGetData();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        //GL_TEXTURE_3D
        glGenerateMipmap(GL_TEXTURE_2D);
        actualNumberOfTextures++;
        actualNumberOfPlacesInTextures--;

        //
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }


    ilBindImage(0);
    ilDeleteImages(1, &textures[actualNumberOfTextures].textureMemLoc);
}
void GeneralTextureAnimation::showImguiImagesAndInfo() {
    ImGui::Begin("All Textures", &showIndividualImage);
    ImVec2 e = { 100,100 };
    for (int a=0; a < actualNumberOfTextures; a++) {
        ImGui::PushID(a);
        ImGui::Text("Texture ID: %d", a);
        ImGui::SameLine();
        ImGui::Image((void*)(intptr_t)textures[a].textureMemLoc, e);
        ImGui::SameLine();
        
        
        if (ImGui::Button("Sow Invividual Texture ")) {
            imageToshow = a;
            showIndividualImage = true;
        }
        ImGui::PopID();
    }
    if (showIndividualImage) {
        showIndividualImageInfo(imageToshow);
    }

    ImGui::End();
}
void GeneralTextureAnimation::showIndividualImageInfo(int a)
{
    ImVec2 realBounds = { (float)textures[a].width,(float)textures[a].height };
    ImGui::Begin(textures[a].name.c_str(), &showIndividualImage);

    ImGui::Image((void*)(intptr_t)textures[a].textureMemLoc, realBounds);
    auto rectmin = ImGui::GetItemRectMin();
    auto rectmax = ImGui::GetItemRectMax();
    ImDrawList* list = ImGui::GetForegroundDrawList();
    list->AddRect(rectmin, rectmax, IM_COL32(255, 255, 0, 255));

    ImGui::Text("Texture ID: %d", a);
    ImGui::Text("Texture Path: ");
    ImGui::SameLine();
    ImGui::Text( textures[a].path.c_str());
    ImGui::Text("Texture Name: ");
    ImGui::SameLine();
    ImGui::Text(textures[a].name.c_str());
    ImGui::Text("File Format: ");
    ImGui::SameLine();
    ImGui::Text(textures[a].format.c_str());
    ImGui::Text("Texture Width: %d", textures[a].width);
    ImGui::Text("Texture Height: %d", textures[a].height);
    ImGui::Text("Texture Number of Chanels: %d", textures[a].numberOfChanels);
    ImGui::Text("Texture Total Size: %d Kb", (textures[a].numberOfChanels* textures[a].height*textures[a].width)/ biteToKb);
    
    
    //FIlters
    
    if (ImGui::Checkbox("Alienfy", &textures[a].alienfy))
    {
        ModifyTexture(TypeOfModify::ALIENIFY, a);
    }

    //if (ImGui::DragFloat("Amount of Contrast:", &textures[a].contrastAmount, 0.1f, -2, 2));
    //{
    //    ModifyTexture(TypeOfModify::CONTRAST, a, textures[a].contrastAmount);//
    //}

    if (ImGui::Checkbox("Negativity", &textures[a].negativity))
    {
        ModifyTexture(TypeOfModify::NEGATIVE, a);
    }

    ///*ImGui::Text("Sharpering Factor:");
    //if (ImGui::DragFloat("  ", &sharpenFactor, 0.1f, 0, 2.5));
    //{
    //    res->metaData.sharpenFactor = sharpenFactor;
    //}*/
    //ImGui::Text("Amount of Gaussian Blur:");
    if (ImGui::DragFloat("Amount of Gaussian Blur:", &textures[a].gaussianBlur, 0.1f, 0, 10));
    {
        ModifyTexture(TypeOfModify::BLURGAUSSIAN, a, textures[a].gaussianBlur);//
    }
    //if (ImGui::Checkbox("Equalization", &textures[a].equalization))
    //{
    //    ModifyTexture(TypeOfModify::EQUALIZE, a);
    //}
    //ImGui::Text("Amount of Noise:");
    //if (ImGui::DragFloat("     ", &textures[a].noiseAmount, 0.1f, 0, 1));
    //{
    //    ModifyTexture(TypeOfModify::NOISIFY, a, textures[a].noiseAmount);//
    //}
    //ImGui::Text("Amount of Average Blur:");
    //if (ImGui::DragFloat("       ", &textures[a].amountAvBlur, 0.1f, 1, 10));
    //{
    //    ModifyTexture(TypeOfModify::BLURAVG, a, textures[a].amountAvBlur);
    //}
    //ImGui::Text("Amount of Gamma Correction:");
    //if (ImGui::DragFloat("        ", &textures[a].gammaCorrectionAmount, 0.1f, 0, 2));
    //{
    //    ModifyTexture(TypeOfModify::GAMMACORRECT, a, textures[a].gammaCorrectionAmount);//
    //}
    //ImGui::Text("Amount of Pixelization:");
    //if (ImGui::DragFloat("", &textures[a].pixelationAmount, 0.1f, 1, 10));
    //{
    //    ModifyTexture(TypeOfModify::PIXELIZE, a, textures[a].pixelationAmount);
    //}
   
    /*ImGui::Text("Sharpering Iterations:");
    if (ImGui::DragFloat("   ", &sharpenIters, 0.1f, 0, 5));
    {
        res->metaData.sharpenIters = sharpenIters;
    }*/
    
    

    ImGui::InputInt("lines in With", &partitionWith);
    ImGui::InputInt("lines in Height", &partitionHeight);
    if (ImGui::Button("Subdivide Image")) 
    {
        if (textures[a].width%(partitionWith+1) == 0) 
        {
            TexturePartition(a, partitionWith, partitionHeight, textures[a].width, textures[a].height);
        }
        else 
        {
            showPartitionErrorImage = true;
        }
        
    }
    if (showPartitionErrorImage)
    {
        ImGui::Begin("ERROR", &showPartitionErrorImage);
        ImGui::Text("ERROR ");



        ImGui::End();
    }

    /* 
    if (resource->metaData.gausianBlurring)
        iluBlurGaussian(resource->metaData.amountGausianBlur);
    if (resource->metaData.contrast)
        iluContrast(resource->metaData.amountContrast);
    if (resource->metaData.equalization)
        iluEqualize();
    if (resource->metaData.gammaCorrection)
        iluGammaCorrect(resource->metaData.amountGammaCorrection);
    if (resource->metaData.negativity)
        iluNegative();
    if (resource->metaData.noise)
        iluNoisify(resource->metaData.amountNoise);
    if (resource->metaData.pixelization)
        iluPixelize(resource->metaData.amountPixelation);
    if (resource->metaData.sharpering)
        iluSharpen(resource->metaData.sharpenFactor, resource->metaData.sharpenIters);*/
    

    ImGui::End();
}
void GeneralTextureAnimation::TexturePartition(int textureID, int rows, int columns, int width, int height)
{
    long long unsigned int buffer = textures[textureID].width * textures[textureID].height * 4;
    GLubyte* pixel = new GLubyte[buffer];
    glBindTexture(GL_TEXTURE_2D, textures[textureID].textureMemLoc);
    glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
    ILubyte* data;
    int widthPerFragment = (width / (columns + 1));
    int heightPerFragment = (height / (rows + 1));
    data = new GLubyte[widthPerFragment * heightPerFragment * GL_RGBA];
    
    int sum = widthPerFragment * heightPerFragment * 4;
    for (int b = 0; b < rows+1; b++) 
    {
        for (int a = 0; a < columns+1; a++) 
        {

            if (actualNumberOfPlacesInTextures == 0)
            {
                IncreaseArray();
            }
            glGenTextures(1, &textures[actualNumberOfTextures].textureMemLoc);
            glBindTexture(GL_TEXTURE_2D, textures[actualNumberOfTextures].textureMemLoc);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);	// set texture wrapping to GL_REPEAT (default wrapping method)
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
            // set texture filtering parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            
            int first = 0;
            int counter = 0;
            int i = ((widthPerFragment*4) * a) + ((width *4)* (heightPerFragment*b));
            while (true)           
            {
                
                data[first] = pixel[i];
                first++;
                counter++;
                i++;
                if (counter == widthPerFragment * 4) {
                    counter = 0;
                    i += ((widthPerFragment*4)* columns);
                }
                if (first == sum) {
                    break;
                }
            }
            textures[actualNumberOfTextures].name = textures[textureID].name+std::to_string(a)+"X"+ std::to_string(b);
            textures[actualNumberOfTextures].height = heightPerFragment;
            textures[actualNumberOfTextures].width = widthPerFragment;
            textures[actualNumberOfTextures].numberOfChanels = 3;
            textures[actualNumberOfTextures].path = "-";
            textures[actualNumberOfTextures].format = "-";

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthPerFragment, heightPerFragment, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
            actualNumberOfTextures++;
            actualNumberOfPlacesInTextures--;
        }
    }



    delete[] data;
    delete[] pixel;
}
void GeneralTextureAnimation::ModifyTexture(TypeOfModify type,  int image,float a)
{
    //int amount=textures[image].height* textures[image].width * 4;
    //GLubyte* pixel = new GLubyte[amount];

    glBindTexture(GL_TEXTURE_2D, textures[image].textureMemLoc);
    ILubyte* data;
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textures[image].width, textures[image].height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textures[image].original);
    //data = new GLubyte[textures[image].height * textures[image].width * GL_RGBA];
    ilBindImage(textures[image].textureMemLoc);
    switch (type)
    {
    case TypeOfModify::MIMPMAPS:
        iluBuildMipmaps();
        break;
    case TypeOfModify::ALIENIFY:
        iluAlienify();
        break;
    case TypeOfModify::BLURAVG:
        iluBlurAvg(a);
        break;
    case TypeOfModify::BLURGAUSSIAN:
        iluBlurGaussian(a);
        break;
    case TypeOfModify::CONTRAST:
        iluContrast(a);
        break;
    case TypeOfModify::EQUALIZE:
        iluEqualize();
        break;
    case TypeOfModify::GAMMACORRECT:
        iluGammaCorrect(a);
        break;
    case TypeOfModify::NEGATIVE:
        iluNegative();
        break;
    case TypeOfModify::NOISIFY:
        iluNoisify(a);
        break;
    case TypeOfModify::PIXELIZE:
        iluPixelize(a);
        break;
    case TypeOfModify::SHARPEN:
        //iluSharpen(resource->metaData.sharpenFactor, resource->metaData.sharpenIters);
        break;
    default:
        break;
    }
    data = ilGetData();
    ////glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textures[image].width, textures[image].height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    ilBindImage(0);
    glBindTexture(GL_TEXTURE_2D, 0);


}