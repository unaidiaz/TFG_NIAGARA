#include"Emitter.h"
#include "General.h"


#include <commdlg.h>
#include <Windows.h> 
#include<string>
#include"ImguiCurve.h"
#include"grand.h"
#include"Imgui/ImGuizmo.h"
#include"Imgui/ImSequencer.h"
#define RANDOMMODE 1


float Emitter::GetZeroOneConvertion(float actualValue, float maxValue)
{
    return actualValue / maxValue;
}






//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




Emitter::Emitter() {
    prevTimeValue = 0;
    faceToCamera = false;
    auxiliarRotationAngle = 0;
    auxiliarRotationAxis = { 1,0,0 };
    ParticlesColorAndAlpha[0] = 1;
    ParticlesColorAndAlpha[1] = 1;
    ParticlesColorAndAlpha[2] = 1;
    ParticlesColorAndAlpha[3] = 1;
    generalState = emitterState::PLAY;

    //transform efects

    transformEfects[0] = "None";
    transformEfects[1] = "Vortex";
    //IMGUI
    //LifeTime
    LifeTimeItems[0] = "Set Life Time";
    LifeTimeItems[RANDOMMODE] = "Random Life Time";
    // velocity
    velocityItems[0] = "Set Velocity";
    velocityItems[RANDOMMODE] = "Random Velocity";
    //position
    positionItems[0] = "Set Position";
    positionItems[RANDOMMODE] = "Random Position";
    //Texture
    textureItems[0] = "Create Animation";
    textureItems[RANDOMMODE] = "Random Texture";
    textureItems[2] = "Set Fixed Texture";
    //spawn form
    spawnForms[0] = "CUSTOM";
    spawnForms[1] = "CONE";
    spawnForms[2] = "SPHERE";
    //particle partition
    PartitionMode[0] = "No partition";
    PartitionMode[1] = "particle Partition";
    randomPartitionMode[0] = "Fixed Number of partitions";
    randomPartitionMode[1] = "Random scope of partitions";
    //scale
    scaleItems[0] = "Scale During Time";
    scaleItems[RANDOMMODE] = "Random Sacle";
    scaleItems[2] = "Set Scale";

    graphicScalePoints[0] = { 0,0 };
    graphicScalePoints[1] = { 0.25,0.25 };
    graphicScalePoints[2] = { 0.75,0.75 };
    graphicScalePoints[3] = { 1,1 };

    //alpha
    alphaModified = false;
    alphaItems[0] = "Alpha During Time";
    alphaItems[1] = "Random Alpha";
    alphaItems[2] = "Set Alpha";

    //color
    colorItems[0] = "Set Color";
    colorItems[1] = "Random Color";
    colorItems[2] = "Color During Time";

    graphicAlphaPoints[0] = { 0,0 };
    graphicAlphaPoints[1] = { 0.25,0.25 };
    graphicAlphaPoints[2] = { 0.75,0.75 };
    graphicAlphaPoints[3] = { 1,1 };
    //pyhsics
    massMode[0] = "Set fixed mass";
    massMode[1] = "Random mass";


    radiusMode[0] = "Set fixed Radio";
    radiusMode[1] = "Random Radio";
    //TO CHANGE
    spawnFrec = 10;

    position = { 0,0,0 };
    maxParticles = lastMaxParticles = 200;
    maxParticleLifeTime = 5;
    spawnPosition = { 0,0,0 };
    spawnAceleration = { 0,0,0 };
    spawnVelocity = { 0,1,0 };

    textureAnimation = new GeneralTextureAnimation();
    
    physicsModule = new Physics();
    physicsModule->SetParticlesInfo(&activeParticles);
    for (int a = 0; a < maxParticles; a++) {


        addParticle();
    }
    textureAnimation->loadAnimation("resources\\textures\\image.jpg");
    //Cube*o =new Cube();
    //physicsModule->CubesList.push_back(o);
    auxiliarTimefrecuency = 1 / spawnFrec;
    //////////////////////////////////////////////////////////////////////////////////////

    //ourShader = new Shader("resources/shaders/instancedVertexShader.txt", "resources/shaders/instancedFragmentShader.txt");

    ////////

    //vertices = new float[40]{//40
    //    -0.5, 0.5, 0.5, 0, 1,  //0
    //        0.5, 0.5, 0.5, 1, 1,  //1
    //        -0.5, -0.5, 0.5, 0, 0, //2
    //        0.5, -0.5, 0.5, 1, 0, //3

    //        -0.5, 0.5, -0.5, 1, 0, //4
    //        0.5, 0.5, -0.5, 0, 0, //5
    //        -0.5, -0.5, -0.5, 1, 1, //6
    //        0.5, -0.5, -0.5, 0, 1//7
    //};



    //indices = new unsigned int[36]{ //36
    //    // front
    //    2,3,1,
    //    0,2,1,
    //    //back
    //    6,4,5,
    //    6,5,7,
    //    //top
    //    0,1,5,
    //    0,5,4,
    //    //bottom
    //    6,7,3,
    //    6,3,2,
    //    //right
    //    3,7,5,
    //    3,5,1,
    //    //left
    //    6,2,0,
    //    6,0,4
    //};

    //glGenBuffers(1, &VBO);
    //glGenBuffers(1, &EBO);
    //glGenVertexArrays(1, &VAO);
    //// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    //glBindVertexArray(VAO);

    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, /*sizeof(vertices)*/sizeof(float) * 40, vertices, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, /*sizeof(indices)*/sizeof(unsigned int) * 36, indices, GL_STATIC_DRAW);










    //modelMatrices = new glm::mat4[cant];

    //int acumulationX = 0;
    //int acumulationY = 0;
    //int acumulationZ = 0;
    //int aux = cbrt(cant);
    //for (unsigned int i = 0; i < cant; i++)
    //{
    //    glm::mat4 model = glm::mat4(1.0f);
    //    // 1. translation: displace along circle with 'radius' in range [-offset, offset]

    //    float offsetX = acumulationX * 7;
    //    float offsetY = acumulationY * 7;
    //    float offsetZ = acumulationZ * 7;

    //    model = glm::translate(model, glm::vec3(offsetX, offsetY, offsetZ));

    //    acumulationX++;
    //    if (aux == acumulationX) {
    //        acumulationX = 0;
    //        acumulationZ++;
    //    }
    //    if (acumulationZ == aux)
    //    {
    //        acumulationZ = 0;
    //        acumulationY++;
    //    }
    //    modelMatrices[i] = model;
    //}

    //glEnableVertexAttribArray(0);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

    //glEnableVertexAttribArray(1);
    //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));


    //glBindVertexArray(0);
    //////////////////////////////////////////


    //color = new glm::vec4[cant];

    //for (int q = 0; q < cant; q++) {

    //    color[q].r = 1;
    //    color[q].g = 1;
    //    color[q].b = 1;
    //    color[q].a = 1;
    //}


    //glGenBuffers(1, &col);
    //glBindBuffer(GL_ARRAY_BUFFER, col);
    //glBufferData(GL_ARRAY_BUFFER, cant * sizeof(glm::vec4), &color[0], GL_STATIC_DRAW);

    //glBindVertexArray(VAO);
    //glEnableVertexAttribArray(2);
    //glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);
    //glVertexAttribDivisor(2, 1);





    //glBindVertexArray(0);

    //glGenBuffers(1, &buffer);
    //glBindBuffer(GL_ARRAY_BUFFER, buffer);
    //glBufferData(GL_ARRAY_BUFFER, cant * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);
    //glBindVertexArray(VAO);



    //glEnableVertexAttribArray(3);
    //glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
    //glEnableVertexAttribArray(4);
    //glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
    //glEnableVertexAttribArray(5);
    //glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
    //glEnableVertexAttribArray(6);
    //glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));


    //glVertexAttribDivisor(3, 1);
    //glVertexAttribDivisor(4, 1);
    //glVertexAttribDivisor(5, 1);
    //glVertexAttribDivisor(6, 1);





    //glGenTextures(1, &texture);
    //glBindTexture(GL_TEXTURE_2D, texture);


    //// set the texture wrapping parameters
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);	// set texture wrapping to GL_REPEAT (default wrapping method)
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    //// set texture filtering parameters
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    //int width, height, nrChannels;
    //// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    ////unsigned char* data = stbi_load("resources/textures/image.jpg", &width, &height, &nrChannels, 0);
    ///*if (data)
    //{
    //    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    //    glGenerateMipmap(GL_TEXTURE_2D);
    //}
    //else
    //{
    //    std::cout << "Failed to load texture" << std::endl;
    //}*/
    ////stbi_image_free(data);



}
Emitter::~Emitter() 
{
    activeParticles.clear();
    for (std::list<particle*>::iterator it = allParticles.begin(); it != allParticles.end(); it++)
    {
        particle* toDelete= it._Ptr->_Myval;

        delete toDelete;
    }
    delete textureAnimation;
    allParticles.clear();
    delete physicsModule;
    delete geometry;
    for (std::list<Emitter*>::iterator it = SecondEmitters.begin(); it != SecondEmitters.end(); it++) {
        delete it._Ptr->_Myval;
    }
}
void Emitter::setGeneralRotationaxis(glm::vec3 axis, float newAngle)
{
    for (std::list<particle*>::iterator it = activeParticles.begin(); it != activeParticles.end(); it++)
    {
        it._Ptr->_Myval->SetParticleAxisRotation(axis);
        it._Ptr->_Myval->SetParticleAngleRotation(newAngle);
    }
}
void Emitter::ResetSimulation() 
{
    for (std::list<particle*>::iterator it = activeParticles.begin(); it != activeParticles.end(); it++)
    {
        it._Ptr->_Myval->setIsActive(false);
    }
    generalState = emitterState::PLAY;
    emitteractuallifetime = 0;
}
void Emitter::OnEditor(float dt) {

    ImGui::Begin(emmitterName.c_str(), &showEdit);

    //static ImGuizmo::OPERATION mCurrentGizmoOperation(ImGuizmo::ROTATE);
    //mCurrentGizmoOperation = ImGuizmo::TRANSLATE;
    //ImGuiIO& io = ImGui::GetIO();
    //ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);
    ////ImGuizmo::Manipulate(camera->GetViewMatrix(), camera.mProjection.m16, mCurrentGizmoOperation, mCurrentGizmoMode, matrix.m16, NULL, useSnap ? &snap.x : NULL);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //APPLICATION
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (ImGui::CollapsingHeader("Application"))
    {
        if (ImGui::Button("back"))
        {
            exit = true;
        }
        static ImVector<float> fpsLog;
        char title[25];
        fpsLog.push_back(1 / dt);
        sprintf_s(title, 25, "Framerate %.1f", fpsLog[fpsLog.size() - 1]);
        ImGui::PlotHistogram("##framerate", &fpsLog[0], fpsLog.size(), 0, title, 0.0f, 2000.0f, ImVec2(310, 100));
        ImGui::Checkbox("Instacing", &instancing);
    }
    
    
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //EMITTER
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (ImGui::CollapsingHeader("Emitter"))
    {
        
        if (ImGui::CollapsingHeader("Emitter General Configuration"))
        {
            if(ImGui::Button("Start")) {
                generalState = emitterState::PLAY;
            }
            ImGui::SameLine();
            if (ImGui::Button("Stop")) {
                generalState = emitterState::STOP;
            }
            ImGui::SameLine();
            if (ImGui::Button("Reset")) {
                ResetSimulation();
            }
            ImGui::Text("active particles: %d", activeParticles.size());
            ImGui::Separator();
            ImGui::Checkbox("Loop", &loop);
            if (!loop) 
            {
                ImGui::DragFloat("emitter Max Lifetime", &emitterMaxLifetime);
            }
            ImGui::Separator();
            if (ImGui::SliderFloat("Spawn Frecuence", &spawnFrec, 0, 20)) {
                auxiliarTimefrecuency = 1 / spawnFrec;
            }
            ImGui::Separator();
            ImGui::Checkbox("faced to camera", &faceToCamera);
            if (ImGui::InputInt("max particles", &maxParticles))
            {
                if (maxParticles >= lastMaxParticles) {
                    for (int a = 0; a < maxParticles - lastMaxParticles; a++) {


                        addParticle();
                    }
                    lastMaxParticles = maxParticles;
                }
                else
                {
                    /*for (int a = 0; a < lastMaxParticles - maxParticles; a++) {


                        addParticle();
                    }*/
                }
            }
            ImGui::Separator();
            ImGui::Combo("Life Time Modify type", &LifeTimeItem, LifeTimeItems, IM_ARRAYSIZE(LifeTimeItems));
            switch (LifeTimeItem)
            {
            case 0:
                ImGui::SliderFloat("Life Time", &maxParticleLifeTime, 0, 100);
                break;
            case RANDOMMODE:
                ImGui::InputFloat2("Random Life Time scope", lifeRandomScope);
                break;
            case 2:

                break;
            default:
                break;
            }
            ImGui::Separator();
            //spawn
            if (ImGui::Combo("Spawn Mode", &actualForm, spawnForms, IM_ARRAYSIZE(spawnForms))) {
                switch (actualForm)
                {
                case (int)spawnForms::CUSTOM:

                    break;
                case (int)spawnForms::CONE:
                    velocityItem = RANDOMMODE;
                    XVelocityRandomScope[0] = -1;
                    XVelocityRandomScope[1] = 1;
                    YVelocityRandomScope[0] = 0.5;
                    YVelocityRandomScope[1] = 1.5;
                    ZVelocityRandomScope[0] = -1;
                    ZVelocityRandomScope[1] = 1;
                    break;
                case (int)spawnForms::SPHERE:
                    velocityItem = RANDOMMODE;
                    XVelocityRandomScope[0] = -1;
                    XVelocityRandomScope[1] = 1;
                    YVelocityRandomScope[0] = -1;
                    YVelocityRandomScope[1] = 1;
                    ZVelocityRandomScope[0] = -1;
                    ZVelocityRandomScope[1] = 1;
                    break;
                default:
                    break;
                }
            }
            ImGui::Separator();
            // particle partition
            ImGui::Combo("Particle Partition", &actualPartition, PartitionMode, IM_ARRAYSIZE(PartitionMode));
            
            switch (actualPartition)
            {
            case 0:
                showPartitionWindow = false;
                break;
            case 1:
                showPartitionWindow = true;
                partitionWindow();
            }
            

            
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //TRANFORM
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (ImGui::CollapsingHeader("Tranform"))
        {
            ImGui::Combo("Position Modify type", &positionItem, positionItems, IM_ARRAYSIZE(positionItems));
            switch (positionItem)
            {
            case 0:
                ImGui::DragFloat3("particles Spawn Position", &position.x, 0.1f);
                break;
            case RANDOMMODE:
                ImGui::InputFloat2("Random Position X scope", XPositionRandomScope);
                ImGui::InputFloat2("Random Position Y scope", YPositionRandomScope);
                ImGui::InputFloat2("Random Position Z scope", ZPositionRandomScope);
                break;
            case 2:

                break;
            default:
                break;
            }
            ImGui::Separator();
            ImGui::Combo("Velocity Modify type", &velocityItem, velocityItems, IM_ARRAYSIZE(velocityItems));
            switch (velocityItem)
            {
            case 0:
                ImGui::DragFloat3("particles Spawn Velocity", &spawnVelocity.x, 0.1f);
                break;
            case RANDOMMODE:
                ImGui::InputFloat2("Random Velocity X scope", XVelocityRandomScope);
                ImGui::InputFloat2("Random Velocity Y scope", YVelocityRandomScope);
                ImGui::InputFloat2("Random Velocity Z scope", ZVelocityRandomScope);
                break;
            case 2:

                break;
            default:
                break;
            }         
            ImGui::Separator();
            ImGui::Text("particles aceleration");
            ImGui::DragFloat3("particles Spawn Aceleration", &spawnAceleration.x, 0.1f);
            if (!faceToCamera)
            {
                ImGui::Text("Rotation:");

                ImGui::DragFloat("Rotation X", &AllAxisRotationVelocitys.x, 0.1f);

                ImGui::DragFloat("Rotation Y", &AllAxisRotationVelocitys.y, 0.1f);

                ImGui::DragFloat("Rotation Z", &AllAxisRotationVelocitys.z, 0.1f);

            }
            else
            {

            }
            ImGui::Separator();
            ImGui::Combo("Particle mass", &actualMassMode, massMode, IM_ARRAYSIZE(massMode));
            switch (actualMassMode)
            {
            case 0:
                ImGui::DragFloat("Mass", &fixedMass, 0.1f);
                break;
            case RANDOMMODE:
                ImGui::InputFloat2("Random Mass Scope", massRandomScope);
                break;
            }
            ImGui::Combo("Particle collision Radius", &actualRadiusMode, radiusMode, IM_ARRAYSIZE(radiusMode));
            switch (actualRadiusMode)
            {
            case 0:
                ImGui::DragFloat("Radius", &fixedRadius, 0.1f);
                break;
            case RANDOMMODE:
                ImGui::InputFloat2("Random Mass Scope", radiusRandomScope);
                break;
            }

            ImGui::Separator();
            //transform efects
            ImGui::Combo("Transform efects", &transformEfect, transformEfects, IM_ARRAYSIZE(transformEfects));

            switch (transformEfect)
            {
            case 0:

                break;
            case 1:
                ImGui::Checkbox("Vortex in X axis", &Xvortex);
                if (Xvortex) {
                    Yvortex = false;
                    Zvortex = false;
                    ImGui::SliderFloat("XVortexVelocity", &XVortexVelocity, 0, 100);
                    ImGui::SliderFloat("XVortexRadius", &XVortexRadius, 0, 500);
                }
                ImGui::Checkbox("Vortex in Y axis", &Yvortex);
                if (Yvortex) {
                    Xvortex = false;
                    Zvortex = false;
                    ImGui::SliderFloat("YVortexVelocity", &YVortexVelocity, 0, 100);
                    ImGui::SliderFloat("YVortexRadius", &YVortexRadius, 0, 500);
                }
                ImGui::Checkbox("Vortex in Z axis", &Zvortex);
                if (Zvortex) {
                    Yvortex = false;
                    Xvortex = false;
                    ImGui::SliderFloat("ZVortexVelocity", &ZVortexVelocity, 0, 100);
                    ImGui::SliderFloat("ZVortexRadius", &ZVortexRadius, 0, 500);
                }



                break;
            }
            ImGui::Separator();
            ImGui::Text("Particles Scale:");
            ImGui::Combo("Scale Modify type", &Scaleitem, scaleItems, IM_ARRAYSIZE(scaleItems));
            switch (Scaleitem)
            {
            case 0:
                ImGui::InputFloat("Max Scale", &maxScale);
                
                ImGui::Curve("Scale", graphicSize, MaxGraphicPoints, graphicScalePoints);
                break;
            case RANDOMMODE:
                ImGui::InputFloat2("Random Scale scope", scaleRandomScope);
                break;
            case 2:
                ImGui::DragFloat("Set Scale", &spawnScale, 0.05);
                break;
            default:
                break;
            }
           
            
            

        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //TEXTURES
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (ImGui::CollapsingHeader("Textures"))
        {
            if (ImGui::Button("Load Texture"))
            {
                textureAnimation->loadAnimation(FindLoadFilePath(""));
            }
            if (ImGui::Button("Sow all textures and info")) {
                textureAnimation->showImguiImages = !textureAnimation->showImguiImages;
            }
            if (textureAnimation->showImguiImages) 
            {
                textureAnimation->showImguiImagesAndInfo();
            }
            ImGui::Separator();
            ImGui::Text("Particles Texture:");
            ImGui::Combo("Texture Modify type", &Textureitem, textureItems, IM_ARRAYSIZE(textureItems));
            switch (Textureitem)
            {
            case 0:
                
                ImGui::InputFloat("Max Time Per Frame", &textureAnimation->maxTimePerFrame);
                break;
            case RANDOMMODE:
                if (ImGui::InputInt2("Random ID Scope", textureAnimation->TextureRandomScope))
                {
                    if (textureAnimation->TextureRandomScope[0] == textureAnimation->TextureRandomScope[1]) {
                        textureAnimation->TextureRandomScope[1]++;
                    }
                }
                                         
                break;
            case 2:

                ImGui::InputInt("Texture ID", &fixedIDToSet);
                break;
            default:
                break;
            }
                
            /*ImGui::Text("Particles Apha");
            ImGui::Bezier("Linearr", &alphaDuringTime);*/
            ImGui::Separator();
            ImGui::Text("Particles Apha");
            
            
            ImGui::Combo("Alpha Modify type", &Alphaitem, alphaItems, IM_ARRAYSIZE(alphaItems));
            switch (Alphaitem)
            {
            case 0:
                ImGui::Curve("Alpha", graphicSize, MaxGraphicPoints, graphicAlphaPoints);
                
                break;
            case 1:

                break;
            case 2:
                ImGui::DragFloat("Set Alpha", &ParticlesColorAndAlpha[3],0.1,0,1);
                break;
            default:
                break;
            }
            ImGui::Separator();
            ImGui::Text("Particles Color");


            ImGui::Combo("Color Modify type", &Coloritem, colorItems, IM_ARRAYSIZE(colorItems));
            switch (Coloritem)
            {
            case 0:
                ImGui::ColorPicker3("color", ParticlesColorAndAlpha);

                break;
            case 1:

                break;
            case 2:
                gradient_widget.widget("My Gradient");
                
                break;
            default:
                break;
            }
    
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //Physics
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (ImGui::CollapsingHeader("Physics"))
        {
            ImGui::Checkbox("particles self collision", &physicsModule->seflfCollision);
            ImGui::Separator();
            if (ImGui::Button("create force")) {
                physicsModule->CreateForce(TypeOfForce::GRAVITY);
            }
            int a = 1;
            std::string positionName = "Force Position ";
            std::string radiusName = "Force Radius ";
            std::string ForceName = "Force ";
            for (std::list<Force*>::iterator it = physicsModule->ForceList.begin(); it != physicsModule->ForceList.end(); it++,a++)
            {
                positionName = positionName + std::to_string(a);
                radiusName = radiusName + std::to_string(a);
                ForceName= ForceName + std::to_string(a);

                ImGui::DragFloat3(positionName.c_str(), &it._Ptr->_Myval->Position.x, 0.1f);
                ImGui::InputFloat(radiusName.c_str(), &it._Ptr->_Myval->radious);
                ImGui::InputFloat(ForceName.c_str(), &it._Ptr->_Myval->OunMass);

                ForceName= "Force ";
                positionName = "Force Position ";
                radiusName = "Force Radius ";
            }
            ImGui::Separator();
            if (ImGui::Button("create Wall")) {
                physicsModule->CreateWall();
            }
            a = 1;
            for (std::list<Cube*>::iterator it = physicsModule->CubesList.begin(); it != physicsModule->CubesList.end(); it++, a++)
            {
                
                positionName = "Cube Position ";
                positionName = positionName + std::to_string(a);
                ImGui::DragFloat3(positionName.c_str(), &it._Ptr->_Myval->position.x, 0.1f);

                positionName = "Cube Mode ";
                positionName = positionName + std::to_string(a);
                ImGui::Combo(positionName.c_str(), &it._Ptr->_Myval->CubeOption, it._Ptr->_Myval->CubeOptions, IM_ARRAYSIZE(it._Ptr->_Myval->CubeOptions));
                ImGui::Separator();
            }
        }
    }

    ImGui::End();
}
void Emitter::partitionWindow() 
{
    ImGui::Begin("partition particles", &showPartitionWindow);

    if (ImGui::Button("Create Emitter")) {
        Emitter* newEmitter;
        newEmitter = new Emitter();
        SecondEmitters.push_back(newEmitter);
        newEmitter->isSecondary = true;
       
        newEmitter->emmitterName = "emitter" + std::to_string(SecondEmitters.size());

        std::list<unsigned int> indices;
        std::list<float> vertices;

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

        indices.push_back(2);
        indices.push_back(3);
        indices.push_back(1);
        indices.push_back(0);
        indices.push_back(2);
        indices.push_back(1);


        newEmitter->LoadGeometry(vertices, indices, "resources/shaders/vertexShader.txt", "resources/shaders/fragmentShader.txt", "resources/textures/image.jpg");
        newEmitter->SetCamera(camera);
    }
    bool Delete = false;
    std::list<Emitter*>::iterator toDelete;
    for (std::list<Emitter*>::iterator it = SecondEmitters.begin(); it != SecondEmitters.end(); it++) {

        ImGui::Text(it._Ptr->_Myval->emmitterName.c_str());
        ImGui::SameLine();
        if(ImGui::Button("Edit")) {
            it._Ptr->_Myval->showEdit = true;
        }

        ImGui::SameLine();
        if (ImGui::Button("Delete")) {
            toDelete = it; 
            Delete = true;
        }
        if (it._Ptr->_Myval->showEdit) 
        {
            ImGui::SliderFloat("Explision time", &exlosionTime, 0, 1);
        }
        ImGui::Separator();
    }
    if (Delete) {
        Emitter* Del = toDelete._Ptr->_Myval;
        SecondEmitters.erase(toDelete);
        delete Del;
    }
    ImGui::Separator();
    ImGui::InputFloat("probability Of partition of particle", &probabilityofPartition);
    ImGui::Combo("Number of partitions Mode", &actualRandomPartition, randomPartitionMode, IM_ARRAYSIZE(randomPartitionMode));
    
    switch (actualRandomPartition)
    {
    case 0:
        ImGui::InputInt("Number of partitions", &fixedNmOfPartitions);
        break;
    case 1:
        ImGui::InputInt2("Random Spawn Number Range", NmOfPartitionsRandomScope);
        break;
    default:
        break;
    }

    
    ImGui::End();
}
particle* Emitter::activeNewParticle() {
    for (std::list<particle*>::iterator it = allParticles.begin(); it != allParticles.end(); it++)
    {
        if (!it._Ptr->_Myval->getIsActive())
        {
            it._Ptr->_Myval->setIsActive(true);
            activeParticles.push_back(it._Ptr->_Myval);
            return it._Ptr->_Myval;
        }
    }
}
void Emitter::LoadGeometry(std::list<float> Vertices, std::list<unsigned int> Indices, const char* VertexShaderSource, const char* FragmentShaderSource, const char* path) {
    geometry = new object();
    geometry->setTextureClass(textureAnimation);
    geometry->createObject(Vertices, Indices, VertexShaderSource, FragmentShaderSource, path);
}
void Emitter::initNewParticle(int cant) {
    particle* auxiliar;
    acumulationTime = 0;
    grand r;
    for (int i = 0; i < cant; i++)
    {


        auxiliar = activeNewParticle();
        //Life Time
        if (LifeTimeItem == RANDOMMODE) {
            maxParticleLifeTime = lifeRandomScope[0] + r.d(lifeRandomScope[1] - lifeRandomScope[0]);
        }
        //Position
        if (positionItem == RANDOMMODE) {
            spawnPosition.x = XPositionRandomScope[0] + r.d(XPositionRandomScope[1] - XPositionRandomScope[0]);
            spawnPosition.y = YPositionRandomScope[0] + r.d(YPositionRandomScope[1] - YPositionRandomScope[0]);
            spawnPosition.z = ZPositionRandomScope[0] + r.d(ZPositionRandomScope[1] - ZPositionRandomScope[0]);
        }
        //Velocity
        if (velocityItem == RANDOMMODE) {
            spawnVelocity.x = XVelocityRandomScope[0] + r.d(XVelocityRandomScope[1] - XVelocityRandomScope[0]);
            spawnVelocity.y = YVelocityRandomScope[0] + r.d(YVelocityRandomScope[1] - YVelocityRandomScope[0]);
            spawnVelocity.z = ZVelocityRandomScope[0] + r.d(ZVelocityRandomScope[1] - ZVelocityRandomScope[0]);
        }
        //scale
        if (Scaleitem == RANDOMMODE) {
            spawnScale = scaleRandomScope[0] + r.d(scaleRandomScope[1] - scaleRandomScope[0]);
        }
        //Aceleration
        if (isAcelerationXrandom) {
            spawnAceleration.x = rand();
        }
        if (isAcelerationYrandom) {
            spawnAceleration.y = rand();
        }
        if (isAcelerationZrandom) {
            spawnAceleration.z = rand();
        }
        //physics
        if (actualMassMode == RANDOMMODE) {
            fixedMass= massRandomScope[0] + r.d(massRandomScope[1] - massRandomScope[0]);
        }
        if (actualRadiusMode == RANDOMMODE) {
            fixedRadius = radiusRandomScope[0] + r.d(radiusRandomScope[1] - radiusRandomScope[0]);
        }


        //animation Texture
        auxiliar->GetParticleTexture()->resetTextureAnimation();
        if (Textureitem == RANDOMMODE)
        {
            fixedIDToSet = (rand() % (textureAnimation->TextureRandomScope[1] - textureAnimation->TextureRandomScope[0])) + textureAnimation->TextureRandomScope[0];
        }

        auxiliar->GetParticleTexture()->SetActualTextureID(fixedIDToSet);
        //color
        if (Coloritem == 1) {
            float Color[3] = { r.d(1), r.d(1), r.d(1) };
            auxiliar->SetParticleColor(Color);
        }
        

        //Position
        auxiliar->SetParticleInitialPosition(spawnPosition + position);
        auxiliar->SetParticlePosition(spawnPosition + position);

        //Rotation
        auxiliar->SetParticleAngleRotation(auxiliarRotationAngle);
        auxiliar->SetParticleAxisRotation(auxiliarRotationAxis);
        auxiliar->SetParticleFrontVector({ 0,0,1 });

        //velocity
        auxiliar->SetParticleInitialVelocity(spawnVelocity);
        auxiliar->SetParticleVelocity(spawnVelocity);

        //aceleration
        auxiliar->SetParticleAceleration(spawnAceleration);
        //scale
        auxiliar->SetParticleScale(spawnScale);
        //lifeTime
        auxiliar->setParticleMaxLifeTime(maxParticleLifeTime);
        auxiliar->setParticleActualLifeTime(0);
        //Physics
        auxiliar->SetParticleMass(fixedMass);
        auxiliar->SetParticleRadius(fixedRadius);
        //color and alpha
        //auxiliar->SetParticleColorWithAlpha(ParticlesColorAndAlpha);

        //particle partition
    }
}
void Emitter::PreUpdate(float dt)
{
    
    OnEditor(dt);
    
    // set new particles active
    if (generalState != emitterState::STOP) {
        if (actualPartition != 0) {
            for (std::list<Emitter*>::iterator it = SecondEmitters.begin(); it != SecondEmitters.end(); it++)
            {
                if (it._Ptr->_Myval->showEdit) 
                {
                    it._Ptr->_Myval->PreUpdate(dt);
                }
                
            }
        }
        acumulationTime += dt;
       
        if (!loop) {

            emitteractuallifetime += dt;
            if (emitteractuallifetime >= emitterMaxLifetime) {
                generalState = emitterState::STOP;
            }
        }

        if ((acumulationTime >= auxiliarTimefrecuency)&&isSecondary == false)
        {          
            initNewParticle(1);
        }

    }


    //Remove no active particles
    std::list<particle*>::iterator it = activeParticles.begin();
    std::list<particle*> toelim;
    while (it != activeParticles.end())
    {
        if (!it._Ptr->_Myval->getIsActive()) {
            toelim.push_back(it._Ptr->_Myval);
        }
        it++;
    }
    it = toelim.begin();
    while (it != toelim.end())
    {
        activeParticles.remove(it._Ptr->_Myval);
        it++;
    }
    toelim.clear();


    /*for (std::list<particle*>::iterator it = activeParticles.begin(); it != activeParticles.end(); it++)
    {
        it._Ptr->_Myval->PreUpdate(dt);
    }*/
}
void Emitter::particleSpawn(particle* auxiliar)
{
    grand r;
    switch (actualRandomPartition)
    {
    case 0:
        for (std::list<Emitter*>::iterator it = SecondEmitters.begin(); it != SecondEmitters.end(); it++)
        {
            it._Ptr->_Myval->position = auxiliar->GetParticlePosition();
            it._Ptr->_Myval->initNewParticle(fixedNmOfPartitions);
        }
        break;
    case 1:
        
        for (std::list<Emitter*>::iterator it = SecondEmitters.begin(); it != SecondEmitters.end(); it++)
        {
            it._Ptr->_Myval->position = auxiliar->GetParticlePosition();
            it._Ptr->_Myval->initNewParticle(NmOfPartitionsRandomScope[0] + r.d(NmOfPartitionsRandomScope[1] - NmOfPartitionsRandomScope[0]));
        }
        break;

    default:
        break;
    }
}
void Emitter::SetCamera(Camera* camera) {
    this->camera = camera;
}
void Emitter::UpdateScale(particle* auxiliar)
{
    switch (Scaleitem)
    {
    case 0:
        auxiliar->SetParticleScale(ImGui::CurveValue(GetZeroOneConvertion(auxiliar->GetParticleActualLifeTime(), auxiliar->GetParticleMaxLifeTime()), MaxGraphicPoints, graphicScalePoints)*maxScale);
        break;
    case 1:

        break;
    case 2:

        break;
    default:
        break;
    }
    
}
void Emitter::UpdateRotation(particle* auxiliar, float dt) {
    if (faceToCamera)
    {
        glm::vec3 vector = camera->Position - auxiliar->GetParticlePosition();

        if (vector != auxiliar->frontVector)
        {
            float fristMod = glm::length(vector);
            float secondMod = glm::length(auxiliar->frontVector);

            auxiliar->SetParticleAngleRotation(acos(((vector.x * auxiliar->frontVector.x) + (vector.y * auxiliar->frontVector.y) + (vector.z * auxiliar->frontVector.z)) / (fristMod * secondMod)));
            if (fristMod == 0 || secondMod == 0) {
                auxiliar->SetParticleAngleRotation(0);
            }
            auxiliar->SetParticleAxisRotation(glm::cross(auxiliar->frontVector, vector));
        }

    }
    else {

        auxiliar->SetParticleAllRotation(auxiliar->GetAllParticleRotation() + (AllAxisRotationVelocitys * dt));
    }
}
void Emitter::UpdatePhysics(particle* auxiliar, float dt) 
{
    if (transformEfect != 1)
    {
        //auxiliar->SetParticleVelocity(physicsModule->UpdateVelocityVector(auxiliar->GetParticleAceleration(), auxiliar->GetParticleInitialVelocity(), auxiliar->GetParticleActualLifeTime()));
        auxiliar->SetParticleVelocity({ auxiliar->GetParticleVelocity().x + (auxiliar->GetParticleAceleration().x * dt),auxiliar->GetParticleVelocity().y + (auxiliar->GetParticleAceleration().y * dt),auxiliar->GetParticleVelocity().z + (auxiliar->GetParticleAceleration().z * dt) });
    }
   
   /* auxiliar->hidedvelocity=(physicsModule->UpdateVelocityVector(auxiliar->GetParticleAceleration(), auxiliar->GetParticleInitialVelocity(), dt));*/
    auxiliar->SetParticlePosition({ auxiliar->GetParticlePosition().x+(auxiliar->GetParticleVelocity().x* dt) + (0.5 * (auxiliar->GetParticleAceleration().x * dt * auxiliar->GetParticleActualLifeTime())) ,auxiliar->GetParticlePosition().y + (auxiliar->GetParticleVelocity().y * dt) + (0.5 * (auxiliar->GetParticleAceleration().y * auxiliar->GetParticleActualLifeTime() * dt)) ,auxiliar->GetParticlePosition().z + (auxiliar->GetParticleVelocity().z * dt) + (0.5 * auxiliar->GetParticleAceleration().z * auxiliar->GetParticleActualLifeTime() * dt)});
    //auxiliar->SetParticlePosition(physicsModule->UpdatePositionVector(auxiliar->GetParticleAceleration(), auxiliar->GetParticleInitialVelocity(), auxiliar->GetParticleInitialPosition(), auxiliar->GetParticleActualLifeTime()));
}
void Emitter::UpdateAlphaAndColor(particle* auxiliar) 
{
    float alpha = 1;
    switch (Alphaitem)
    {
    case 0:     
        alpha=ImGui::CurveValue(GetZeroOneConvertion(auxiliar->GetParticleActualLifeTime(), auxiliar->GetParticleMaxLifeTime()), MaxGraphicPoints, graphicAlphaPoints);
        break;
    case 1:

        break;
    case 2:
        alpha = ParticlesColorAndAlpha[3];
        break;
    default:
        break;
    }
    auxiliar->SetParticleAlpha(alpha);
    //COLOR
    ImGG::ColorRGBA color;
    switch (Coloritem)
    {
    case 0:
        auxiliar->SetParticleColor(ParticlesColorAndAlpha);
        
        break;
    case 1:

        break;
    case 2:

        color = gradient_widget.gradient().at({ GetZeroOneConvertion(auxiliar->GetParticleActualLifeTime(), auxiliar->GetParticleMaxLifeTime()), ImGG::WrapMode::Clamp });
        ParticlesColorAndAlpha[0] = color.x;
        ParticlesColorAndAlpha[1] = color.y;
        ParticlesColorAndAlpha[2] = color.z;
        auxiliar->SetParticleColor(ParticlesColorAndAlpha);
        break;
    default:
        break;
    }
}
void Emitter::UpdateTextures(particle* auxiliar, float dt) 
{
    switch (Textureitem)
    {
    case 0:
        auxiliar->GetParticleTexture()->Update(dt);
            break;
    case 1:
        
        break;
    case 2:
        break;
    default:
        break;
    }
    

}
void Emitter::UpdateSecondariEmitters(int time, particle* auxiliar) {
    if (actualPartition != 0) {
        switch (time)
        {
        case 0:
            prevExlosionTime = GetZeroOneConvertion(auxiliar->GetParticleActualLifeTime(), auxiliar->GetParticleMaxLifeTime());
            break;
        case 1:
            if ((exlosionTime > prevExlosionTime) && (exlosionTime <= GetZeroOneConvertion(auxiliar->GetParticleActualLifeTime(), auxiliar->GetParticleMaxLifeTime()))) {
                grand r;

                if (r.b(probabilityofPartition)) {
                    particleSpawn(auxiliar);
                }

            }
            break;
        default:
            break;
        }
    }
}
void Emitter::UpdateTransformEfects(particle* auxiliar, float dt) {
    switch (transformEfect)
    {
    case 0:
        break;
    case 1:
        UpdateVortex(auxiliar, dt);

        break;
    default:
        break;
    }
}
void Emitter::UpdateVortex(particle* auxiliar, float dt)
{   
    glm::vec3 newVelocity;
    glm::vec3 oldVelocity;
    //oldVelocity = auxiliar->GetParticleVelocity();
    oldVelocity = physicsModule->UpdateVelocityVector(auxiliar->GetParticleAceleration(), spawnVelocity, auxiliar->GetParticleActualLifeTime());
    if (Zvortex) {
        actualSinVaule = auxiliar->GetParticleActualLifeTime() / ZVortexRadius;
        newVelocity.x = (glm::sin((actualSinVaule * 180) / M_PI) * ZVortexVelocity) + oldVelocity.x;
        newVelocity.y = (glm::cos((actualSinVaule * 180) / M_PI) * ZVortexVelocity) + oldVelocity.y;
        newVelocity.z = oldVelocity.z;
    }
    if (Xvortex) {
        actualSinVaule = (auxiliar->GetParticleActualLifeTime() / XVortexRadius);
        newVelocity.z = (glm::sin((actualSinVaule * 180) / M_PI) * XVortexVelocity) + oldVelocity.z;
        newVelocity.y = (glm::cos((actualSinVaule * 180) / M_PI) * XVortexVelocity) + oldVelocity.y;
        newVelocity.x = oldVelocity.x;
    }
    if (Yvortex) {
        actualSinVaule = (auxiliar->GetParticleActualLifeTime() / YVortexRadius);
        newVelocity.z = (glm::sin((actualSinVaule * 180) / M_PI) * YVortexVelocity) + oldVelocity.z;
        newVelocity.x = (glm::cos((actualSinVaule * 180) / M_PI) * YVortexVelocity) + oldVelocity.x;
        newVelocity.y = oldVelocity.y;
    }
    auxiliar->SetParticleVelocity(newVelocity);
    
    
}
void Emitter::Update(float dt)
{
    if (actualPartition != 0) {
        for (std::list<Emitter*>::iterator it = SecondEmitters.begin(); it != SecondEmitters.end(); it++)
        {
            it._Ptr->_Myval->Update(dt);
        }
    }
    for (std::list<particle*>::iterator it = activeParticles.begin(); it != activeParticles.end(); it++)
    {
        UpdateSecondariEmitters(0, it._Ptr->_Myval);
        it._Ptr->_Myval->addParticleActualLifeTime(dt);
        UpdateSecondariEmitters(1, it._Ptr->_Myval);
        if (it._Ptr->_Myval->GetParticleMaxLifeTime() > it._Ptr->_Myval->GetParticleActualLifeTime())
        {
            
            physicsModule->Update(it._Ptr->_Myval,dt, it);
            UpdateRotation(it._Ptr->_Myval, dt);
            
            

            UpdatePhysics(it._Ptr->_Myval, dt);
            UpdateTransformEfects(it._Ptr->_Myval, dt);
           
            
            UpdateScale(it._Ptr->_Myval);
            UpdateAlphaAndColor(it._Ptr->_Myval);

            UpdateTextures(it._Ptr->_Myval,dt);
            
        }
        else
        {
           
                
 
            it._Ptr->_Myval->setIsActive(false);
        }
    }
}
void Emitter::instancedRender() {
    ourShader->setMat4("projection", camera->GetProjection());
    ourShader->setMat4("view", camera->GetViewMatrix());
    glm::vec2 res = { WIDTH,HEIGHT };
    ourShader->setVec2("resolution", res);
    glBindTexture(GL_TEXTURE_2D, texture);

    ourShader->use();
    glBindVertexArray(VAO);

    glVertexAttribDivisor(2, 1);

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, col);
    glBufferData(GL_ARRAY_BUFFER, cant * sizeof(glm::vec4), &color[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);

    glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, cant);

    glDisableVertexAttribArray(2);

    glBindVertexArray(0);
}
void Emitter::PostUpdate(float dt) {
    if (instancing) {

       // instancedRender();
    }
    else {


        if (actualPartition != 0) {
            for (std::list<Emitter*>::iterator it = SecondEmitters.begin(); it != SecondEmitters.end(); it++)
            {
                it._Ptr->_Myval->PostUpdate(dt);
            }
        }
        for (std::list<particle*>::iterator it = activeParticles.begin(); it != activeParticles.end(); it++)
        {
            Draw(it._Ptr->_Myval);
        }
        physicsModule->PostUpdate();
    }
}
void Emitter::Draw(particle* auxiliar)
{
    glm::mat4 transform = glm::mat4(1.0f);
    glm::vec3 auxPosition(auxiliar->GetParticlePosition().x, auxiliar->GetParticlePosition().y, auxiliar->GetParticlePosition().z);

    transform = glm::translate(transform, auxPosition);
    if (faceToCamera)
    {
        transform = glm::rotate(transform, auxiliar->GetParticleRotationAngle(), auxiliar->GetParticleRotationAxis());
    }
    else
    {
        transform = glm::rotate(transform, auxiliar->GetAllParticleRotation().x, glm::vec3{ 1,0,0 });
        transform = glm::rotate(transform, auxiliar->GetAllParticleRotation().y, glm::vec3{ 0,1,0 });
        transform = glm::rotate(transform, auxiliar->GetAllParticleRotation().z, glm::vec3{ 0,0,1 });
    }
    float sca = auxiliar->GetParticleScale();
    transform = glm::scale(transform, glm::vec3{ sca,sca,sca });
    geometry->getSahder()->setMat4("transform", transform);
    geometry->getSahder()->setMat4("projection", camera->GetProjection());
    geometry->getSahder()->setMat4("view", camera->GetViewMatrix());
    geometry->getSahder()->setVec4("Color", auxiliar->GetParticleColorWithAlpha());
    geometry->getSahder()->setBool("isFaced", faceToCamera);
    geometry->Draw(auxiliar->GetParticleTexture()->getActualtexture());
}
void Emitter::addParticle()
{
    particle* auxiliar = new particle();
    auxiliar->GetParticleTexture()->setGenearlReference(textureAnimation);


    allParticles.push_back(auxiliar);
    auxiliar->setIsActive(false);
}
void Emitter::substractParticle(int number)
{
    for (int a = 0; a < number; a++) {

    }
}
