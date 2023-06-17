#include"Physics.h"
//////////////////////
//FORCE
//////////////////////
#include"Particle.h"

Cube::Cube() {
    position = { 0,-4,0 };
    glm::vec3 auxiliar;
    auxiliar = { 1,1,1 };//0
    points[0]=auxiliar;
    auxiliar = { 1,-1,1 };//1
    points[1] = auxiliar;
    auxiliar = {-1,1,1 };//2
    points[2] = auxiliar;
    auxiliar = { -1,-1,1 };//3
    points[3] = auxiliar;
    auxiliar = { 1,1,-1 };
    points[4] = auxiliar;
    auxiliar = { 1,-1,-1 };
    points[5] = auxiliar;
    auxiliar = { -1,1,-1 };
    points[6] = auxiliar;
    auxiliar = { -1,-1,-1 };
    points[7] = auxiliar;

    //normals
    auxiliar = { 0,0,1 };
    normals[0]=auxiliar;
    auxiliar = { 0,0,-1 };
    normals[1] = auxiliar;
    auxiliar = { 0,1,0 };
    normals[2] = auxiliar;
    auxiliar = { 0,-1,0 };
    normals[3] = auxiliar;
    auxiliar = { 1,0,0 };
    normals[4] = auxiliar;
    auxiliar = { -1,0,0 };
    normals[5] = auxiliar;
    CubeOptions[0] = "Wall";
    CubeOptions[1] = "Elim";
}
glm::vec3 Cube::update(particle* auxiliar, float dt)
{
    glm::vec3 toReturn={0,0,0};
    glm::vec3 particlePosition = auxiliar->GetParticlePosition();
    float radius = auxiliar->GetParticleRadius();
    glm::vec3 frontalPoint;
    glm::vec3 auxiliarnormal;
    glm::vec3 auxiliarnormalOriginalPoint;

    frontalPoint = { particlePosition.x - (normals[0].x * radius),particlePosition.y - (normals[0].y * radius),particlePosition.z - (normals[0].z * radius) };

    auxiliarnormal = frontalPoint - (points[0]+position);
    auxiliarnormal=glm::normalize(auxiliarnormal);
    //
    auxiliarnormalOriginalPoint= particlePosition - (points[0] + position);
    auxiliarnormalOriginalPoint = glm::normalize(auxiliarnormalOriginalPoint);
    if (acos((auxiliarnormalOriginalPoint.x * normals[0].x) + (auxiliarnormalOriginalPoint.y * normals[0].y) + (auxiliarnormalOriginalPoint.z * normals[0].z)) < M_PI * 0.5) {
        toReturn = { normals[0] };
    }
    if (acos((auxiliarnormal.x * normals[0].x) + (auxiliarnormal.y * normals[0].y) + (auxiliarnormal.z * normals[0].z)) >= M_PI*0.5) {
        glm::vec3 BackPoint;
        BackPoint = { particlePosition.x - (normals[1].x * radius),particlePosition.y - (normals[1].y * radius),particlePosition.z - (normals[1].z * radius) };
        auxiliarnormal = BackPoint - (points[4] + position);
        auxiliarnormal = glm::normalize(auxiliarnormal);
        //
        auxiliarnormalOriginalPoint = particlePosition - (points[4] + position);
        auxiliarnormalOriginalPoint = glm::normalize(auxiliarnormalOriginalPoint);
        if (acos((auxiliarnormalOriginalPoint.x * normals[1].x) + (auxiliarnormalOriginalPoint.y * normals[1].y) + (auxiliarnormalOriginalPoint.z * normals[1].z)) < M_PI * 0.5) {
            toReturn = { normals[1] };
        }
        if (acos((auxiliarnormal.x * normals[1].x) + (auxiliarnormal.y * normals[1].y) + (auxiliarnormal.z * normals[1].z)) >= M_PI * 0.5) {
            glm::vec3 RightPoint;
            RightPoint = { particlePosition.x - (normals[4].x * radius),particlePosition.y - (normals[4].y * radius),particlePosition.z - (normals[4].z * radius) };
            auxiliarnormal = RightPoint - (points[0] + position);
            auxiliarnormal = glm::normalize(auxiliarnormal);
            //
            auxiliarnormalOriginalPoint = particlePosition - (points[0] + position);
            auxiliarnormalOriginalPoint = glm::normalize(auxiliarnormalOriginalPoint);
            if (acos((auxiliarnormalOriginalPoint.x * normals[4].x) + (auxiliarnormalOriginalPoint.y * normals[4].y) + (auxiliarnormalOriginalPoint.z * normals[4].z)) < M_PI * 0.5) {
                toReturn = { normals[4] };
            }
            if (acos((auxiliarnormal.x * normals[4].x) + (auxiliarnormal.y * normals[4].y) + (auxiliarnormal.z * normals[4].z)) >= M_PI * 0.5) {
                glm::vec3 LeftPoint;
                LeftPoint = { particlePosition.x - (normals[5].x * radius),particlePosition.y - (normals[5].y * radius),particlePosition.z - (normals[5].z * radius) };
                auxiliarnormal = LeftPoint - (points[2] + position);
                auxiliarnormal = glm::normalize(auxiliarnormal);
                //
                auxiliarnormalOriginalPoint = particlePosition - (points[2] + position);
                auxiliarnormalOriginalPoint = glm::normalize(auxiliarnormalOriginalPoint);
                if (acos((auxiliarnormalOriginalPoint.x * normals[5].x) + (auxiliarnormalOriginalPoint.y * normals[5].y) + (auxiliarnormalOriginalPoint.z * normals[5].z)) < M_PI * 0.5) {
                    toReturn = { normals[5] };
                }
                if (acos((auxiliarnormal.x * normals[5].x) + (auxiliarnormal.y * normals[5].y) + (auxiliarnormal.z * normals[5].z)) >= M_PI * 0.5) {
                    glm::vec3 TopPoint;
                    TopPoint = { particlePosition.x - (normals[2].x * radius),particlePosition.y - (normals[2].y * radius),particlePosition.z - (normals[2].z * radius) };
                    auxiliarnormal = TopPoint - (points[0] + position);
                    auxiliarnormal = glm::normalize(auxiliarnormal);
                    //
                    auxiliarnormalOriginalPoint = particlePosition - (points[0] + position);
                    auxiliarnormalOriginalPoint = glm::normalize(auxiliarnormalOriginalPoint);
                    if (acos((auxiliarnormalOriginalPoint.x * normals[2].x) + (auxiliarnormalOriginalPoint.y * normals[2].y) + (auxiliarnormalOriginalPoint.z * normals[2].z)) < M_PI * 0.5) {
                        toReturn = { normals[2] };
                    }
                    if (acos((auxiliarnormal.x * normals[2].x) + (auxiliarnormal.y * normals[2].y) + (auxiliarnormal.z * normals[2].z)) >= M_PI * 0.5) {
                        glm::vec3 DownPoint;
                        DownPoint = { particlePosition.x - (normals[3].x * radius),particlePosition.y - (normals[3].y * radius),particlePosition.z - (normals[3].z * radius) };
                        auxiliarnormal = DownPoint - (points[3] + position);
                        auxiliarnormal = glm::normalize(auxiliarnormal);
                        //
                        auxiliarnormalOriginalPoint = particlePosition - (points[3] + position);
                        auxiliarnormalOriginalPoint = glm::normalize(auxiliarnormalOriginalPoint);
                        if (acos((auxiliarnormalOriginalPoint.x * normals[3].x) + (auxiliarnormalOriginalPoint.y * normals[3].y) + (auxiliarnormalOriginalPoint.z * normals[3].z)) < M_PI * 0.5) {
                            toReturn = { normals[3] };
                        }
                        if (acos((auxiliarnormal.x * normals[3].x) + (auxiliarnormal.y * normals[3].y) + (auxiliarnormal.z * normals[3].z)) >= M_PI * 0.5) {
                            return normals[2];
                        
                        }
                       return {0,0,0};
                    }
                    return { 0,0,0 };
                }
                return { 0,0,0 };
            }
            return { 0,0,0 };        
        }
        return { 0,0,0 };
    }
    return { 0,0,0 };
}



Force::Force(TypeOfForce newType) {
    Type = newType;
    Position = { 0,2,0 };
    Vector = { 0,0,-1 };
    force = 1;
}
void Force::update(particle* auxiliar,float dt)
{
    glm::vec3 temporalPosition;
    float realDistance;
    glm::vec3 Distances;
    switch (Type)
    {
    case TypeOfForce::NONE:
        break;
    case TypeOfForce::GRAVITY:

        /// AABB?????
        temporalPosition = auxiliar->GetParticlePosition();
        
        Distances.x = (temporalPosition.x - Position.x);
        Distances.y = (temporalPosition.y - Position.y);
        Distances.z = (temporalPosition.z - Position.z);
        realDistance = sqrt((Distances.x * Distances.x) + (Distances.y * Distances.y) + (Distances.z * Distances.z));

        if (realDistance < radious)
        {
            SetGravityForce(auxiliar, Distances);
        }

        break;
    case TypeOfForce::WIND:
        break;
    default:
        break;
    }
}
void Force::SetGravityForce( particle* axuiliar, glm::vec3 distances) {


    glm::vec3 newAceleration;
    long float top=(/*G*/0.1 * OunMass * ParticleMass);
    
    newAceleration.x = top / distances.x;
    newAceleration.y = top / distances.y;
    newAceleration.z = top / distances.z;
    if (distances.x == 0) {
        newAceleration.x = 0;
    }
    if (distances.y == 0) {
        newAceleration.y = 0;
    }
    if (distances.z == 0) {
        newAceleration.z = 0;
    }
    axuiliar->SetParticleAceleration(newAceleration);
}
//////////////////////
//PHISICS
//////////////////////
glm::vec3 Physics::UpdateVelocityVector(glm::vec3 aceleration, glm::vec3 initialVelocity, float dt)
{
    return { initialVelocity.x + (aceleration.x * dt),initialVelocity.y + (aceleration.y * dt),initialVelocity.z + (aceleration.z * dt) };
}
glm::vec3 Physics::UpdatePositionVector(glm::vec3 aceleration, glm::vec3 initialVelocity, glm::vec3 initialPosition, float dt)
{
    return{ (float)(initialPosition.x + (initialVelocity.x * dt) + (0.5 * aceleration.x * dt * dt)),(float)(initialPosition.y + (initialVelocity.y * dt) + (0.5 * aceleration.y * dt * dt)),(float)(initialPosition.z + (initialVelocity.z * dt) + (0.5 * aceleration.z * dt * dt)) };
}

void Physics::CreateForce(TypeOfForce Type)
{
    Force* newForce = new Force(Type);
    newForce->GeneralPointer = this;
    ForceList.push_back(newForce);
}
void Physics::Update(particle* auxiliar,float dt, std::list<particle*>::iterator iterator)
{
    for (std::list<Force*>::iterator it = ForceList.begin(); it != ForceList.end(); it++)
    {
        it._Ptr->_Myval->update(auxiliar,dt);

    }
    for (std::list<Cube*>::iterator it = CubesList.begin(); it != CubesList.end(); it++)
    {
        glm::vec3 o = it._Ptr->_Myval->update(auxiliar, dt);
        
        if (o!= glm::vec3{0,0,0}) {
            switch (it._Ptr->_Myval->CubeOption)
            {
            case 0:
                ColisionDetected(o, auxiliar, dt);
                break;
            case 1:
                auxiliar->setIsActive(false);
                break;
            default:
                break;
            }
            
        }
        
    }
    if (seflfCollision) {
        for (std::list<particle*>::iterator it = iterator; it != allParticles->end(); it++)
        {
            if (it != iterator) {
                glm::vec3 auxiliarPosition = it._Ptr->_Myval->GetParticlePosition() - iterator._Ptr->_Myval->GetParticlePosition();
                if (glm::length(auxiliarPosition) < it._Ptr->_Myval->GetParticleRadius()+ iterator._Ptr->_Myval->GetParticleRadius()) {
                    iterator._Ptr->_Myval->SetParticleVelocity(SeflCollision1Update(it._Ptr->_Myval->GetParticleMass(), iterator._Ptr->_Myval->GetParticleMass(), it._Ptr->_Myval->GetParticleVelocity(), iterator._Ptr->_Myval->GetParticleVelocity()));
                    it._Ptr->_Myval->SetParticleVelocity(SeflCollision2Update(it._Ptr->_Myval->GetParticleMass(), iterator._Ptr->_Myval->GetParticleMass(), it._Ptr->_Myval->GetParticleVelocity(), iterator._Ptr->_Myval->GetParticleVelocity()));
                }
            }

        }
    }
}
void Physics::ColisionDetected(glm::vec3 colisionVector,particle* auxiliar,float dt) {

    glm::vec3 j = {(auxiliar->GetParticleVelocity().x * colisionVector.x),(auxiliar->GetParticleVelocity().y * (-colisionVector.y)),(auxiliar->GetParticleVelocity().z * colisionVector.z)};
    auxiliar->SetParticleVelocity(j);
    //auxiliar->SetParticlePosition({ auxiliar->GetParticlePosition().x + (auxiliar->GetParticleVelocity().x * dt)  ,auxiliar->GetParticlePosition().y + (auxiliar->GetParticleVelocity().y * dt)  ,auxiliar->GetParticlePosition().z + (auxiliar->GetParticleVelocity().z * dt) });
}
void Physics::UpdateCollisons(particle* auxiliar, float dt) {
    
}
void Physics::PostUpdate()
{
    
}
void Physics::CreateWall() {
    Cube* auxiliar = new Cube();
    CubesList.push_back(auxiliar);
}
glm::vec3 Physics::SeflCollision1Update(float m1, float m2, glm::vec3 v1, glm::vec3 v2) {
    return ((((2 * m1) / (m1 + m2)) * v1) - (((m1 - m2) / (m1 + m2)) * v2));
}
glm::vec3 Physics::SeflCollision2Update(float m1, float m2, glm::vec3 v1, glm::vec3 v2) {
    return ((((m1 - m2) / (m1 + m2)) * v1) + (((2 * m2) / (m1 + m2)) * v2));
}