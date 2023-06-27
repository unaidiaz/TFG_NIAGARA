#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"
#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"
#include"Imgui/ImGuizmo.h"



#include"General.h"
#include"Object.h"
#include"Emitter.h"

#include"Camera.h"
#include "shader.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <list>
#include<vector>
#include"simulator.h"


float DT = 0;
float actualValue = 0;
float lastValue = 0;
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));
float lastX = (float)WIDTH / 2.0;
float lastY = (float)HEIGHT / 2.0;
bool firstMouse = true;
bool simple = false;
bool realist = false;

std::list<unsigned int> indices;
std::list<float> vertices;
Emitter* auxiliar;
FluidCube* cube;


GLFWwindow* window;





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////














void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xoffset = 0;
    float yoffset = 0;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {


        float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);

        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        xoffset = xpos - lastX;
        yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

        lastX = xpos;
        lastY = ypos;
    }
    camera.ProcessMouseMovement(xoffset, yoffset);
}
void processInput(GLFWwindow* window)
{
    /*for (int a = 0; a < GLFW_KEY_LAST; a++)
    {
        if (glfwGetKey(window, a) == GLFW_PRESS)
            cambio = true;
    }*/
    if (realist) {
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            cube->FluidCubeAddDensity(5, 3, 2, 10000);
            cube->FluidCubeAddDensity(6, 3, 2, 10000);
            cube->FluidCubeAddDensity(5, 4, 2, 10000);
            cube->FluidCubeAddDensity(5, 3, 3, 10000);
        }
        if (cube) {
            cube->FluidCubeAddVelocity(2, 2, 2, 500, 500, 500);
        }

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            camera.ProcessKeyboard(BACKWARD, DT);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            camera.ProcessKeyboard(FORWARD, DT);

        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {

            camera.ProcessKeyboard(RIGHT, DT);
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            camera.ProcessKeyboard(LEFT, DT);
        }
    }
    else if(simple)
    {
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            camera.ProcessKeyboard(BACKWARD, DT);
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            camera.ProcessKeyboard(FORWARD, DT);

        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {

            camera.ProcessKeyboard(RIGHT, DT);
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            camera.ProcessKeyboard(LEFT, DT);
        }
    }
   
    

    
}
void loadRealistic() {
    realist = true;
    cube = new FluidCube();
    cube->setCamera(&camera);
    cube->FluidCubeCreate(40, 0.00001, 0.5, DT);//40, 0.00001, 0.5,

}
void loadSimple() {
    simple = true;
    vertices.push_back(-0.5);
    vertices.push_back(0.5);
    vertices.push_back(0);
    vertices.push_back(0);
    vertices.push_back(1);

    vertices.push_back(0.5);
    vertices.push_back(0.5);
    vertices.push_back(0);
    vertices.push_back(1);
    vertices.push_back(1);

    vertices.push_back(-0.5);
    vertices.push_back(-0.5);
    vertices.push_back(0);
    vertices.push_back(0);
    vertices.push_back(0);

    vertices.push_back(0.5);
    vertices.push_back(-0.5);
    vertices.push_back(0);
    vertices.push_back(1);
    vertices.push_back(0);

    /*vertices.push_back(-0.5);
    vertices.push_back(0.5);
    vertices.push_back(-0.5);
    vertices.push_back(0);
    vertices.push_back(1);
    vertices.push_back(0.5);
    vertices.push_back(0.5);
    vertices.push_back(-0.5);
    vertices.push_back(1);

    vertices.push_back(1);
    vertices.push_back(-0.5);
    vertices.push_back(-0.5);
    vertices.push_back(-0.5);
    vertices.push_back(0);
    vertices.push_back(0);
    vertices.push_back(0.5);
    vertices.push_back(-0.5);
    vertices.push_back(-0.5);
    vertices.push_back(1);
    vertices.push_back(0);*/


    indices.push_back(2);
    indices.push_back(3);
    indices.push_back(1);
    indices.push_back(0);
    indices.push_back(2);
    indices.push_back(1);
    /*indices.push_back(6);
    indices.push_back(4);
    indices.push_back(5);
    indices.push_back(6);
    indices.push_back(5);
    indices.push_back(7);
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(5);

    indices.push_back(0);
    indices.push_back(5);
    indices.push_back(4);

    indices.push_back(6);
    indices.push_back(7);
    indices.push_back(3);

    indices.push_back(6);
    indices.push_back(3);
    indices.push_back(2);



    indices.push_back(3);
    indices.push_back(7);
    indices.push_back(5);

    indices.push_back(3);
    indices.push_back(5);
    indices.push_back(1);

    indices.push_back(6);
    indices.push_back(2);
    indices.push_back(0);

    indices.push_back(6);
    indices.push_back(0);
    indices.push_back(4);*/

    auxiliar = new Emitter();
    auxiliar->LoadGeometry(vertices, indices, "resources/shaders/vertexShader.txt", "resources/shaders/fragmentShader.txt", "resources/textures/image.jpg");
    auxiliar->SetCamera(&camera);
    camera.Position = { 0 ,0,7.3 };
}
void chooseParticle()
{
    if (!realist && !simple) {
        ImGui::Begin("Choose the sistem");

        if (ImGui::Button("Realist Particle system"))
        {
            loadRealistic();
        }
        else if (ImGui::Button("Normal Particle system")) {
            loadSimple();
        }
        ImGui::End();
    }
}
int main() {


    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "TFG_NIAGARA", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, WIDTH, HEIGHT);
    glEnable(GL_DEPTH_TEST);
    glfwSetCursorPosCallback(window, mouse_callback);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");


    /// //////////////////////////////////////////////////////// //////////////////////////////////////////////////////// /////////////////////////////////////////////////////


    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    // make sure to initialize matrix to identity matrix first
    /// //////////////////////////////////////////////////////// //////////////////////////////////////////////////////// /////////////////////////////////////////////////////
    while (!glfwWindowShouldClose(window))
    {
        actualValue = glfwGetTime();
        DT = actualValue - lastValue;
        lastValue = actualValue;
        glClearColor(0, 0, 0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGuizmo::BeginFrame();
        processInput(window);
        chooseParticle();
        if (simple) {
            auxiliar->PreUpdate(DT);
            auxiliar->Update(DT);
            auxiliar->PostUpdate(DT);
            if (auxiliar->exit) {
                simple = false;
                delete auxiliar;
            }
        }
        else if (realist) {
            
            cube->PreUpdate(DT, EXTERNAL_MODE);
            cube->Update(EXTERNAL_MODE);
            cube->PostUpdate(EXTERNAL_MODE);
            if (cube->exit) {
                realist = false;
                delete cube;
            }
        }


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    /*glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);*/
    //glDeleteProgram(our.ID);

    glfwTerminate();
    return 0;
}