#ifndef PARTICLE_H
#define PARTICLE_H
#include"Physics.h"
#include"LocalTextureAnimation.h"
class particle {

    float angleToRotate;
    glm::vec3 axisToRotate;
    
    bool isActive;

    //textures
    LocalTextureAnimation textures;

    //Physics
    glm::vec3 initialVelocity;
    glm::vec3 velocity;
    glm::vec3 aceleration;
    glm::vec3 initialposition;
    glm::vec3 position;
    glm::vec3 allAngleRotation;
    glm::vec4 color;

    float mass;
    float collisionRadius;
    //vel
    
private:
    float scale;
    float maxLifeTime;
    float currentLifeTime = 0;
public:
    particle();
    ~particle();
    glm::vec3 frontVector = { 0,0,-1 };
    void PreUpdate(float dt);
    
    inline bool getIsActive() {
        return isActive;
    }
    inline void setIsActive(bool newState) {
        isActive = newState;
    }

    inline void setParticleMaxLifeTime(float newMaxLifeTime)
    {
        maxLifeTime = newMaxLifeTime;
    }
    inline void setParticleActualLifeTime(float newActualLifeTime)
    {
        currentLifeTime = newActualLifeTime;
    }
    inline void addParticleActualLifeTime(float newActualLifeTime)
    {
        currentLifeTime += newActualLifeTime;
    }
    inline float GetParticleMaxLifeTime()
    {
        return maxLifeTime;
    }
    inline float GetParticleActualLifeTime()
    {
        return currentLifeTime;
    }
    //general sters
    inline void SetParticleAlpha(float NewAlpha)
    {
        color[3] = NewAlpha;
    }
    inline void SetParticleColor(float* NewColor)
    {
        color[0] = NewColor[0];
        color[1] = NewColor[1];
        color[2] = NewColor[2];
    }

    //general geters

    inline LocalTextureAnimation* GetParticleTexture()
    {
        return &textures;
    }
    inline glm::vec3 GetParticleColor()
    {
        return color;
    }
    inline float GetParticleAlpha()
    {
        return color[3];
    }
    inline glm::vec4 GetParticleColorWithAlpha()
    {
        return color;
    }
    //Physics geters
    inline float GetParticleMass()
    {
        return mass;
    }
    inline float GetParticleRadius()
    {
        return collisionRadius;
    }
    inline glm::vec3 GetParticlePosition()
    {
        return position;
    }
    inline glm::vec3 GetParticleInitialPosition()
    {
        return initialposition;
    }
    inline glm::vec3 GetParticleInitialVelocity()
    {
        return initialVelocity;
    }
    inline glm::vec3 GetParticleVelocity()
    {
        return velocity;
    }
    inline glm::vec3 GetParticleAceleration()
    {
        return aceleration;
    }
    inline float GetParticleRotationAngle()
    {
        return angleToRotate;
    }
    inline glm::vec3 GetParticleRotationAxis()
    {
        return axisToRotate;
    }
    inline glm::vec3 GetAllParticleRotation()
    {
        return allAngleRotation;
    }
    inline glm::vec3 GetParticleFrontVector()
    {
        return frontVector;
    }
    inline float GetParticleScale()
    {
        return scale;
    }
    //Physics seteres
    inline void SetParticleMass(float newMass)
    {
        mass = newMass;
    }
    inline void SetParticleRadius(float newRad)
    {
        collisionRadius = newRad;
    }
    inline void SetParticlePosition(glm::vec3 newPosition)
    {
        position = newPosition;
    }
    inline void SetParticleInitialPosition(glm::vec3 newInitialPosition)
    {
        initialposition = newInitialPosition;
    }
    inline void SetParticleInitialVelocity(glm::vec3 newInitialVelocity)
    {
        initialVelocity = newInitialVelocity;
    }
    inline void SetParticleVelocity(glm::vec3 newVelocity)
    {
        velocity = newVelocity;
    }
    inline void SetParticleAceleration(glm::vec3 newAceleration)
    {
        aceleration = newAceleration;
    }
    inline void SetParticleAngleRotation(float newRotation)
    {
        angleToRotate = newRotation;
    }
    inline void SetParticleAxisRotation(glm::vec3 newRotationAngle)
    {
        axisToRotate = newRotationAngle;
    }
    inline void SetParticleAllRotation(glm::vec3 newAllRotation)
    {
        allAngleRotation = newAllRotation;
    }
    inline void SetParticleFrontVector(glm::vec3 newFrontVector)
    {
        frontVector = newFrontVector;
    }
    inline void SetParticleScale(float newScale)
    {
        scale = newScale;
    }
};
#endif
