#ifndef PHYSICS_H
#define PHYSICS_H
#include"General.h"
#include<list>
# define M_PI           3.14159265358979323846
#define G 0.0000000006678
class particle;
class Force;
class Cube {
public:
    Cube();
    int CubeOption = 0;
    const char* CubeOptions[2];
    glm::vec3 update(particle* auxiliar, float dt);

    glm::vec3 position;
    glm::vec3 normals[6];
    
    glm::vec3 points[8];
};
enum class TypeOfForce
{
    NONE,
    WIND,
    GRAVITY
};

class Physics
{
public:
    void ColisionDetected(glm::vec3 colisionVector, particle* auxiliar, float dt);
    glm::vec3 UpdateVelocityVector(glm::vec3 aceleration, glm::vec3 initialVelocity, float dt);
    glm::vec3 UpdatePositionVector(glm::vec3 aceleration, glm::vec3 initialVelocity, glm::vec3 initialPosition, float dt);
    void CreateForce(TypeOfForce Type);
    void CreateWall();
    void Update(particle* auxiliar,float dt, std::list<particle*>::iterator iterator);
    void UpdateCollisons(particle* auxiliar, float dt);
    void PostUpdate();
    glm::vec3 SeflCollision1Update(float m1,float m2, glm::vec3 v1, glm::vec3 v2);
    glm::vec3 SeflCollision2Update(float m1, float m2, glm::vec3 v1, glm::vec3 v2);
    void SetParticlesInfo(std::list<particle*>* info) {
        allParticles = info;
    }
    std::list<Force*> ForceList;
    std::list<Cube*> CubesList;
    std::list<particle*>*allParticles;
    bool seflfCollision = false;
};

class Force
{
public:
    Force(TypeOfForce Type= TypeOfForce::NONE);

    TypeOfForce Type;
    glm::vec3 Position;
    Physics* GeneralPointer;
    void update(particle* auxiliar,float dt);
    
    //WIND CASE
    glm::vec3 Vector;
    float force = 1;

    //GRAVITY CASE
    float radious = 1;
    float OunMass = 10;
    float ParticleMass = 1;
    void SetGravityForce(particle* axuiliar,glm::vec3 distances);

};
#endif
