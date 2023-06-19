#include"simulator.h"
#include<stdlib.h>

#include"General.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"
#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"

#include"ProgressionBar.h"
void FluidCube::FluidCubeCreate(int size, float diffusion, float viscosity, float dt)
{

    int N = size;
    state = simulationState::NORMAL_RUN;
    this->size = size;
    this->dt = dt;
    this->diff = diffusion;
    this->visc = viscosity;

    this->s = (float*)calloc(N * N * N, sizeof(float));
    this->density = (float*)calloc(N * N * N, sizeof(float));

    this->Vx = (float*)calloc(N * N * N, sizeof(float));
    this->Vy = (float*)calloc(N * N * N, sizeof(float));
    this->Vz = (float*)calloc(N * N * N, sizeof(float));

    this->Vx0 = (float*)calloc(N * N * N, sizeof(float));
    this->Vy0 = (float*)calloc(N * N * N, sizeof(float));
    this->Vz0 = (float*)calloc(N * N * N, sizeof(float));

    /// /////////////////////////////////////////////////////////////////7

    /*for (int a = 0; a < N * N * N; a++) {
        this->density[a] = 1;
    }*/

    ourShader = new Shader("resources/shaders/vert.txt", "resources/shaders/frag.txt");

    //////

    vertices = new float[20]{//40
         -1, 1, 0, 0, 1,  //0
             1, 1, 0, 1, 1,  //1
             -1, -1, 0, 0, 0, //2
             1, -1, 0, 1, 0, //3

             //-0.5, 0.5, -0.5, 1, 0, //4
             //0.5, 0.5, -0.5, 0, 0, //5
             //-0.5, -0.5, -0.5, 1, 1, //6
             //0.5, -0.5, -0.5, 0, 1//7
    };



    indices = new unsigned int[6]{ //36
        // front
        2,3,1,
        0,2,1,
        //back
        //6,4,5,
        //6,5,7,
        ////top
        //0,1,5,
        //0,5,4,
        ////bottom
        //6,7,3,
        //6,3,2,
        ////right
        //3,7,5,
        //3,5,1,
        ////left
        //6,2,0,
        //6,0,4
    };

    camera->Position = { 0,0,0 };



    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, /*sizeof(vertices)*/sizeof(float) * 40, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, /*sizeof(indices)*/sizeof(unsigned int) * 36, indices, GL_STATIC_DRAW);


    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    glBindVertexArray(0);



    glGenTextures(1, &ext);
    glBindTexture(GL_TEXTURE_3D, ext);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



    glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, N, N, N, 0, GL_RED, GL_FLOAT, density);
    //GL_TEXTURE_3D
    glGenerateMipmap(GL_TEXTURE_3D);
}
bool FluidCube::PreUpdate(float DT, int a) {
    dt = DT;



    ImGui::Begin("My name is window, ImGUI window");

    if (ImGui::Button("cacheate simulation")) {
        showcachOptionWindow = true;
    }
    if (showcachOptionWindow) {
        cachOptionWindow();
    }
    static ImVector<float> fpsLog;
    char title[25];
    fpsLog.push_back(1 / dt);
    sprintf_s(title, 25, "Framerate %.1f", fpsLog[fpsLog.size() - 1]);
    ImGui::PlotHistogram("##framerate", &fpsLog[0], fpsLog.size(), 0, title, 0.0f, 2000.0f, ImVec2(310, 100));

    ImGui::DragFloat("Smoke Diffusion", &diff,0.0001f,0,0,"%.4f");
    ImGui::DragFloat("Smoke Viscosity", &visc, 0.0001f, 0, 0, "%.4f");

    ImGui::End();
    return true;
}

bool FluidCube::Update(int a)
{
    
    if (state == simulationState::LOADING) {
        return true;
    }
    FluidCubeStep();
    return true;
}
bool FluidCube::PostUpdate(int a)
{
    if (state == simulationState::CACHING ) {
        saveCachedFile();
        
    }
    
    else if (state == simulationState::LOADING) {
        loadCachedFile();
    }
    glBindTexture(GL_TEXTURE_3D, ext);


    glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, size, size, size, 0, GL_RED, GL_FLOAT, density);
    glBindTexture(0, ext);
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, { 0,0,0 });

    transform = glm::scale(transform, glm::vec3{ 1,1,1 });
    ourShader->setMat4("transform", transform);
    ourShader->setMat4("projection", camera->GetProjection());
    ourShader->setMat4("view", camera->GetViewMatrix());
    ourShader->setVec3("camPos", camera->Position);
    ourShader->setVec3("X", camera->Right);
    ourShader->setVec3("Y", camera->Up);
    ourShader->setVec3("Z", camera->Front);
    glBindTexture(GL_TEXTURE_3D, ext);

    ourShader->use();
    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    return true;
}
void FluidCube::FluidCubeAddDensity(int x, int y, int z, float amount)
{
    if (state != simulationState::LOADING) 
    {
        int N = size;
        density[IX(x, y, z)] += amount;
    }
    
}

void FluidCube::FluidCubeAddVelocity(int x, int y, int z, float amountX, float amountY, float amountZ)
{
    int N = size;
    int index = IX(x, y, z);

    Vx[index] += amountX;
    Vy[index] += amountY;
    Vz[index] += amountZ;
}
void FluidCube::FluidCubeStep()
{
    int N = size;
    float visc = this->visc;
    float diff = this->diff;
    float dt = this->dt;
    float* Vx = this->Vx;
    float* Vy = this->Vy;
    float* Vz = this->Vz;
    float* Vx0 = this->Vx0;
    float* Vy0 = this->Vy0;
    float* Vz0 = this->Vz0;
    float* s = this->s;

    
    diffuse(1, Vx0, Vx, visc, dt, 1, N);
    diffuse(2, Vy0, Vy, visc, dt, 1, N);
    diffuse(3, Vz0, Vz, visc, dt, 1, N);

    project(Vx0, Vy0, Vz0, Vx, Vy, 1, N);

    advect(1, Vx, Vx0, Vx0, Vy0, Vz0, dt, N);
    advect(2, Vy, Vy0, Vx0, Vy0, Vz0, dt, N);
    advect(3, Vz, Vz0, Vx0, Vy0, Vz0, dt, N);

    project(Vx, Vy, Vz, Vx0, Vy0, 1, N);

    diffuse(0, s, density, diff, dt, 1, N);
    advect(0, density, s, Vx, Vy, Vz, dt, N);
}

void FluidCube::set_bnd(int b, float* x, int N)
{
    for (int j = 1; j < N - 1; j++) {
        for (int i = 1; i < N - 1; i++) {
            x[IX(i, j, 0)] = b == 3 ? -x[IX(i, j, 1)] : x[IX(i, j, 1)];
            x[IX(i, j, N - 1)] = b == 3 ? -x[IX(i, j, N - 2)] : x[IX(i, j, N - 2)];
        }
    }
    for (int k = 1; k < N - 1; k++) {
        for (int i = 1; i < N - 1; i++) {
            x[IX(i, 0, k)] = b == 2 ? -x[IX(i, 1, k)] : x[IX(i, 1, k)];
            x[IX(i, N - 1, k)] = b == 2 ? -x[IX(i, N - 2, k)] : x[IX(i, N - 2, k)];
        }
    }
    for (int k = 1; k < N - 1; k++) {
        for (int j = 1; j < N - 1; j++) {
            x[IX(0, j, k)] = b == 1 ? -x[IX(1, j, k)] : x[IX(1, j, k)];
            x[IX(N - 1, j, k)] = b == 1 ? -x[IX(N - 2, j, k)] : x[IX(N - 2, j, k)];
        }
    }

    x[IX(0, 0, 0)] = 0.33f * (x[IX(1, 0, 0)]
        + x[IX(0, 1, 0)]
        + x[IX(0, 0, 1)]);
    x[IX(0, N - 1, 0)] = 0.33f * (x[IX(1, N - 1, 0)]
        + x[IX(0, N - 2, 0)]
        + x[IX(0, N - 1, 1)]);
    x[IX(0, 0, N - 1)] = 0.33f * (x[IX(1, 0, N - 1)]
        + x[IX(0, 1, N - 1)]
        + x[IX(0, 0, N)]);
    x[IX(0, N - 1, N - 1)] = 0.33f * (x[IX(1, N - 1, N - 1)]
        + x[IX(0, N - 2, N - 1)]
        + x[IX(0, N - 1, N - 2)]);
    x[IX(N - 1, 0, 0)] = 0.33f * (x[IX(N - 2, 0, 0)]
        + x[IX(N - 1, 1, 0)]
        + x[IX(N - 1, 0, 1)]);
    x[IX(N - 1, N - 1, 0)] = 0.33f * (x[IX(N - 2, N - 1, 0)]
        + x[IX(N - 1, N - 2, 0)]
        + x[IX(N - 1, N - 1, 1)]);
    x[IX(N - 1, 0, N - 1)] = 0.33f * (x[IX(N - 2, 0, N - 1)]
        + x[IX(N - 1, 1, N - 1)]
        + x[IX(N - 1, 0, N - 2)]);
    x[IX(N - 1, N - 1, N - 1)] = 0.33f * (x[IX(N - 2, N - 1, N - 1)]
        + x[IX(N - 1, N - 2, N - 1)]
        + x[IX(N - 1, N - 1, N - 2)]);
}

void FluidCube::lin_solve(int b, float* x, float* x0, float a, float c, int iter, int N)
{
    float cRecip = 1.0 / c;
    for (int k = 0; k < iter; k++) {
        for (int m = 1; m < N - 1; m++) {
            for (int j = 1; j < N - 1; j++) {
                for (int i = 1; i < N - 1; i++) {
                    x[IX(i, j, m)] =
                        (x0[IX(i, j, m)]
                            + a * (x[IX(i + 1, j, m)]
                                + x[IX(i - 1, j, m)]
                                + x[IX(i, j + 1, m)]
                                + x[IX(i, j - 1, m)]
                                + x[IX(i, j, m + 1)]
                                + x[IX(i, j, m - 1)]
                                )) * cRecip;
                }
            }
        }

        set_bnd(b, x, N);
    }
}

void  FluidCube::diffuse(int b, float* x, float* x0, float diff, float dt, int iter, int N)
{
    float a = dt * diff * (N - 2) * (N - 2);
    lin_solve(b, x, x0, a, 1 + 6 * a, iter, N);
}

void FluidCube::project(float* velocX, float* velocY, float* velocZ, float* p, float* div, int iter, int N)
{
    for (int k = 1; k < N - 1; k++) {
        for (int j = 1; j < N - 1; j++) {
            for (int i = 1; i < N - 1; i++) {
                div[IX(i, j, k)] = -0.5f * (
                    velocX[IX(i + 1, j, k)]
                    - velocX[IX(i - 1, j, k)]
                    + velocY[IX(i, j + 1, k)]
                    - velocY[IX(i, j - 1, k)]
                    + velocZ[IX(i, j, k + 1)]
                    - velocZ[IX(i, j, k - 1)]
                    ) / N;
                p[IX(i, j, k)] = 0;
            }
        }
    }
    set_bnd(0, div, N);
    set_bnd(0, p, N);
    lin_solve(0, p, div, 1, 6, iter, N);

    for (int k = 1; k < N - 1; k++) {
        for (int j = 1; j < N - 1; j++) {
            for (int i = 1; i < N - 1; i++) {
                velocX[IX(i, j, k)] -= 0.5f * (p[IX(i + 1, j, k)]
                    - p[IX(i - 1, j, k)]) * N;
                velocY[IX(i, j, k)] -= 0.5f * (p[IX(i, j + 1, k)]
                    - p[IX(i, j - 1, k)]) * N;
                velocZ[IX(i, j, k)] -= 0.5f * (p[IX(i, j, k + 1)]
                    - p[IX(i, j, k - 1)]) * N;
            }
        }
    }
    set_bnd(1, velocX, N);
    set_bnd(2, velocY, N);
    set_bnd(3, velocZ, N);
}

void FluidCube::advect(int b, float* d, float* d0, float* velocX, float* velocY, float* velocZ, float dt, int N)
{
    float i0, i1, j0, j1, k0, k1;

    float dtx = dt * (N - 2);
    float dty = dt * (N - 2);
    float dtz = dt * (N - 2);

    float s0, s1, t0, t1, u0, u1;
    float tmp1, tmp2, tmp3, x, y, z;

    float Nfloat = N;
    float ifloat, jfloat, kfloat;
    int i, j, k;

    for (k = 1, kfloat = 1; k < N - 1; k++, kfloat++) {
        for (j = 1, jfloat = 1; j < N - 1; j++, jfloat++) {
            for (i = 1, ifloat = 1; i < N - 1; i++, ifloat++) {
                tmp1 = dtx * velocX[IX(i, j, k)];
                tmp2 = dty * velocY[IX(i, j, k)];
                tmp3 = dtz * velocZ[IX(i, j, k)];
                x = ifloat - tmp1;
                y = jfloat - tmp2;
                z = kfloat - tmp3;

                if (x < 0.5f) x = 0.5f;
                if (x > Nfloat + 0.5f) x = Nfloat + 0.5f;
                i0 = floorf(x);
                i1 = i0 + 1.0f;
                if (y < 0.5f) y = 0.5f;
                if (y > Nfloat + 0.5f) y = Nfloat + 0.5f;
                j0 = floorf(y);
                j1 = j0 + 1.0f;
                if (z < 0.5f) z = 0.5f;
                if (z > Nfloat + 0.5f) z = Nfloat + 0.5f;
                k0 = floorf(z);
                k1 = k0 + 1.0f;

                s1 = x - i0;
                s0 = 1.0f - s1;
                t1 = y - j0;
                t0 = 1.0f - t1;
                u1 = z - k0;
                u0 = 1.0f - u1;

                int i0i = i0;
                int i1i = i1;
                int j0i = j0;
                int j1i = j1;
                int k0i = k0;
                int k1i = k1;

                d[IX(i, j, k)] =

                    s0 * (t0 * (u0 * d0[IX(i0i, j0i, k0i)]
                        + u1 * d0[IX(i0i, j0i, k1i)])
                        + (t1 * (u0 * d0[IX(i0i, j1i, k0i)]
                            + u1 * d0[IX(i0i, j1i, k1i)])))
                    + s1 * (t0 * (u0 * d0[IX(i1i, j0i, k0i)]
                        + u1 * d0[IX(i1i, j0i, k1i)])
                        + (t1 * (u0 * d0[IX(i1i, j1i, k0i)]
                            + u1 * d0[IX(i1i, j1i, k1i)])));
            }
        }
    }
    set_bnd(b, d, N);
}
void cacheate(FluidCube* toCach)
{
    int total = toCach->endFrameToCach - toCach->startFrameToCach;
    while (toCach->actualCachingFrame != total)
    {
        toCach->PreUpdate(toCach->realFramerate, INTERNAL_MODE);
        toCach->Update(INTERNAL_MODE);
        toCach->PostUpdate(INTERNAL_MODE);
    }
}
void load(FluidCube* toCach)
{
    int total = toCach->endFrameToCach - toCach->startFrameToCach;
    while (toCach->actualCachingFrame != total)
    {
        toCach->PreUpdate(toCach->realFramerate, INTERNAL_MODE);
        toCach->Update(INTERNAL_MODE);
        toCach->PostUpdate(INTERNAL_MODE);
    }
}
void FluidCube::progressionBar() {
    ImGui::Begin("Progression bar");
    if (state == simulationState::CACHING)
    {
        float value = 0;
        int total = endFrameToCach - startFrameToCach;
        const ImU32 co = ImGui::GetColorU32(ImGuiCol_ButtonHovered);
        const ImU32 bg = ImGui::GetColorU32(ImGuiCol_Button);
        ImGui::Text("saving all data");
        value = actualCachingFrame / total;
        ImGui::SameLine();
        ImGui::Spinner("##spinner", 15, 6, co);
        ImGui::Text("%f", value * 100);
        ImGui::BufferingBar("##buffer_bar", value, ImVec2(400, 6), bg, co);
    }
    else
    {
    }

    ImGui::End();
}
void FluidCube::cachOptionWindow() {
    ImGui::Begin("Simulation cache");
    ImGui::InputInt("Framerate:", &framerate);

    if (state == simulationState::NORMAL_RUN) {
        if (ImGui::Button("Save"))
        {
            if (state != simulationState::CACHING) {
                cachPath = FindSaveFilePath("*unai");
                state = simulationState::CACHING;
                realFramerate = 1 / framerate;
                bufferToStore = new float[size * size * size];
                //cacheate(this);
                //std::thread th3(cacheate, this);
                //th3.join();

            }
        }
        if (ImGui::Button("Load"))
        {
            if (state != simulationState::LOADING) {
                loadPath = FindSaveFilePath("");
                state = simulationState::LOADING;
                realFramerate = 1 / framerate;
                bufferToStore = new float[size * size * size];


            }
        }
    }
    else if (state == simulationState::LOADING) 
    {
        if (ImGui::Button("Exit Loading Mode"))
        {
            state = simulationState::NORMAL_RUN;
            for (int i = 0; i < size*size * size; i++)
            {
                density[i] = 0;
            }
            LoadedID = 0;
        }
    }
    else if (state == simulationState::CACHING)
    {
        ImGui::Text("saving path:");
        ImGui::SameLine();
        ImGui::Text(loadPath.c_str());
        ImGui::Text("frames cahed: %d", actualCachingFrame);
        if (ImGui::Button("Stop caching"))
        {
            actualCachingFrame = 0;
            state = simulationState::NORMAL_RUN;
        }
    }
    
    progressionBar();



    ImGui::End();
}
void FluidCube::saveCachedFile()
{

    std::ofstream archivo(cachPath + "_" + std::to_string(actualCachingFrame), std::ios::binary);

    size_t tamanoArray = size * size * size;
    archivo.write(reinterpret_cast<const char*>(&tamanoArray), sizeof(tamanoArray));


    archivo.write(reinterpret_cast<const char*>(&density[0]), tamanoArray * sizeof(float));

    archivo.close();

    actualCachingFrame++;
}
void FluidCube::loadCachedFile()
{
    size_t indiceGuionBajo = loadPath.find('_');
    std::string hh;
    if (indiceGuionBajo != std::string::npos) {
        hh=loadPath.substr(0, indiceGuionBajo);
        
        hh = hh + '_'+std::to_string(LoadedID);
    }

    std::ifstream archivo(hh, std::ios::binary);
    if (!archivo) {
        LoadedID = 0;
        return;
    }
    size_t tamanoArray;
    archivo.read(reinterpret_cast<char*>(&tamanoArray), sizeof(tamanoArray));



    archivo.read(reinterpret_cast<char*>(&density[0]), tamanoArray * sizeof(float));

    archivo.close();
    LoadedID++;

}
void bufferToString(const float* buffer, int bufferSize, char* outputString, int maxStringLength) {
    for (int i = 0; i < bufferSize; i++) {
        snprintf(outputString, maxStringLength, "%s%.2f ", outputString, buffer[i]);
    }
}