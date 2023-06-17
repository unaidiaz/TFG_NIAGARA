#include"LocalTextureAnimation.h"
#include"GeneralTextureAnimation.h"

LocalTextureAnimation::LocalTextureAnimation() {
    actualTexture = -1;
    actualTextureTime = 0;
}
LocalTextureAnimation::~LocalTextureAnimation() {

}
int LocalTextureAnimation::getActualtexture() {
    return actualTexture;
}
void LocalTextureAnimation::Update(float dt)
{
    actualTextureTime += dt;

    if (actualTextureTime >= generalReference->maxTimePerFrame)
    {
        actualTextureTime = 0;
        actualTexture++;
        if (actualTexture == generalReference->actualNumberOfTextures) 
        {
            if (generalReference->loop) 
            {
                actualTexture = 0;
            }
        }
    }
}
void LocalTextureAnimation::resetTextureAnimation() {
    actualTexture = 0;
    actualTextureTime = 0;
    //TODO
}
void LocalTextureAnimation::SetActualTextureID(int NewID) {
    actualTexture = NewID;
}
void  LocalTextureAnimation::setGenearlReference(GeneralTextureAnimation* auxiiliar) 
{
    generalReference = auxiiliar;
}