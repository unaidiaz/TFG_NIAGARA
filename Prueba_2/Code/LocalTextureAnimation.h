#ifndef LOCALTEXTUREANIMATION_H
#define LOCALTEXTUREANIMATION_H
class GeneralTextureAnimation;
class LocalTextureAnimation {
public:
    LocalTextureAnimation();
    ~LocalTextureAnimation();
    int getActualtexture();
    void Update(float dt);

    void resetTextureAnimation();
    void SetActualTextureID(int NewID);
    void setGenearlReference(GeneralTextureAnimation* auxiiliar);
private:
    GeneralTextureAnimation* generalReference;
    int actualTexture;
    //animation
    float actualTextureTime;
};
#endif
