#pragma once
#include<iostream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include"shader.h"
#include"Camera.h"
#include<thread>
#define IX(x, y, z) ((x) + (y) * N + (z) * N * N)
#define INTERNAL_MODE 0
#define EXTERNAL_MODE 1

enum class simulationState {
    NORMAL_RUN,
    PAUSE,
    STOP,
    CACHING,
    LOADING
};
class FluidCube {
public:
    bool PreUpdate(float dt,int a);
    bool Update(int a);
    void FluidCubeCreate(int size, float diffusion, float viscosity, float dt);
    void FluidCubeAddDensity(int x, int y, int z, float amount);
    void FluidCubeAddVelocity(int x, int y, int z, float amountX, float amountY, float amountZ);
    bool PostUpdate(int a);
    void SetDt(float newDt) { dt = newDt; }
    void setCamera(Camera* cam) {
        camera = cam;
    }
private:
    void FluidCubeStep();
    static void set_bnd(int b, float* x, int N);
    static void lin_solve(int b, float* x, float* x0, float a, float c, int iter, int N);
    static void  diffuse(int b, float* x, float* x0, float diff, float dt, int iter, int N);
    static void project(float* velocX, float* velocY, float* velocZ, float* p, float* div, int iter, int N);
    static void advect(int b, float* d, float* d0, float* velocX, float* velocY, float* velocZ, float dt, int N);

    unsigned int ext;
    simulationState state;
    int size;
    float dt;
    float diff;
    float visc;

    float* s;
    float* density;

    float* Vx;
    float* Vy;
    float* Vz;

    float* Vx0;
    float* Vy0;
    float* Vz0;

    unsigned int col;
    unsigned int VBO, VAO, EBO;
    unsigned int texture;
    float* vertices;
    unsigned int* indices;

    unsigned int buffer;
    glm::mat4* modelMatrices;
    glm::vec4* color;
    /// 
    /// CACHEATE PROCCES
    /// 
public:
    void cachOptionWindow();
    bool showcachOptionWindow = false;
    int framerate = 24;
    float realFramerate;
    std::string cachPath;
    std::string loadPath;
    void saveCachedFile();
    void loadCachedFile();
    int actualCachingFrame = 0;
    float* bufferToStore;
    int startFrameToCach = 0;
    int endFrameToCach = 100;
    void progressionBar();
    int LoadedID = 0;
    /// 
    /// 
    /// 
public:
    Shader* ourShader;
    Camera* camera;
};
void cacheate(FluidCube* toCach);

