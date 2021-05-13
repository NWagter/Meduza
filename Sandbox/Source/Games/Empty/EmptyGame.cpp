#include "PCH.h"

#include "Games/Empty/EmptyGame.h"

#include "MeduzaIncluder.h"

#include "Components/RotateComponent.h"
#include "Systems/Rotator.h"
#include "Systems/CameraControllerSystem.h"

EmptyGame::EmptyGame()
{
   m_gameName = "Empty"; 

   new Rotator();
   new CameraControllerSystem();
}

EmptyGame::~EmptyGame()
{

}

void EmptyGame::InitGame()
{
    Me::Resources::MeshLibrary::CreateMesh("Assets/Models/Duck.glb");
    Me::Resources::MeshLibrary::CreateMesh("Assets/Models/Suzanne/Suzanne.gltf");

    auto eManager = Me::EntityManager::GetEntityManager();

    auto cC = new Me::CameraComponent();
    cC->m_cameraType = Me::CameraType::Perspective;
    cC->m_near = 0.1f;
    cC->m_far = 1000;
    cC->m_size = Me::Event::EventSystem::GetEventSystem()->ScreenSize();

    EntityID entCam = Me::EntityManager::CreateEntity();
    eManager->AddComponent<Me::CameraComponent>(entCam, cC);
    eManager->AddComponent<Me::TransformComponent>(entCam);


    Me::Math::Vec3 spawnPointStart = Me::Math::Vec3(2,2,2);
    Me::Math::Vec3 spawnPointRot = Me::Math::Vec3(0,0,0);
    
    for(int i = -spawnPointStart.m_x; i <= spawnPointStart.m_x; i += spawnPointStart.m_x)
    {
        for(int j = -spawnPointStart.m_y; j <= spawnPointStart.m_y; j +=spawnPointStart.m_y)
        {
            for(int n = spawnPointStart.m_z; n <= (spawnPointStart.m_z * 10); n += spawnPointStart.m_z)
            {
                CreateObject(Me::Math::Vec3(i, j, n), spawnPointRot, eManager, false, true);
            }
        }
    }
}

void EmptyGame::UpdateGame(float)
{
    if(!m_spawnedDucks)
    {
        if(Me::Event::EventSystem::GetEventSystem()->KeyDown(Me::Event::KeyCode::Space))
        {
            auto eManager = Me::EntityManager::GetEntityManager();

            Me::Math::Vec3 position = Me::Math::Vec3(-10, 0, 25);
            Me::Math::Vec3 rotation = Me::Math::Vec3(0,0,0);   
            rotation.m_y = 180;

            Me::Mesh suzanne = Me::Resources::MeshLibrary::CreateMesh("Assets/Models/Suzanne/Suzanne.gltf");

            Me::Texture suzanneTexture = Me::Resources::TextureLibrary::GetTexture("Assets/Models/Suzanne/Suzanne_BaseColor.png");

            CreateObject(position, rotation, 5, eManager, suzanne, suzanneTexture, false); 
            
            position.m_x = 10;
            Me::Mesh duck = Me::Resources::MeshLibrary::CreateMesh("Assets/Models/Duck.glb");
            CreateObject(position, rotation, 0.05f, eManager, duck, 0, false);

            m_spawnedDucks = true;
        }
    }
}

void EmptyGame::CreateObject(Me::Math::Vec3 a_pos, Me::Math::Vec3 a_rot, Me::EntityManager* a_eManager, bool a_sphere, bool a_shouldRotate)
{
    int i = rand() % 100;
    std::string textureFile = "Assets/Textures/Crate.png";
    Me::Primitives meshId = Me::Primitives::Cube;

    if(i < 50 || a_sphere)
    {
        meshId = Me::Primitives::Sphere;
        textureFile = "Assets/Textures/Earth_TEXTURE_CM.png";
    }

    Me::Shader mesh = Me::Resources::MeshLibrary::GetMeshIndex(meshId);

    Me::Shader shader = Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/Lit_Shader.hlsl");
    Me::Texture texture = Me::Resources::TextureLibrary::CreateTexture(textureFile);

    EntityID cube = a_eManager->CreateEntity();

    Me::RenderComponent* rComp = new Me::RenderComponent();
    Me::TransformComponent* tComp = new Me::TransformComponent();
    RotateComponent* rotComp = new RotateComponent();
    
    tComp->SetPosition(a_pos);
    tComp->SetRotationDegree(a_rot);
    tComp->SetUniformScale(static_cast<float>(1));

    if(a_shouldRotate)
        rotComp->m_rotateSpeed = 0.25f;

    rComp->m_mesh = mesh;
    rComp->m_shader = shader;
    rComp->m_colour = Me::Colours::WHITE;
    rComp->m_texture = texture;

    a_eManager->AddComponent<RotateComponent>(cube, rotComp);
    a_eManager->AddComponent<Me::RenderComponent>(cube, rComp);
    a_eManager->AddComponent<Me::TransformComponent>(cube, tComp);
}
void EmptyGame::CreateObject(Me::Math::Vec3 a_positon, Me::Math::Vec3 a_rotation, float a_uniformScale, Me::EntityManager* a_eManager, Me::Mesh a_mesh, Me::Texture a_texture, bool a_shouldRotate)
{
    Me::Shader shader = Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/Lit_Shader.hlsl");

    if(a_texture == 0)
        shader = Me::Resources::ShaderLibrary::CreateShader("Assets/Shaders/LitColour_Shader.hlsl");

    EntityID cube = a_eManager->CreateEntity();

    Me::RenderComponent* rComp = new Me::RenderComponent();
    Me::TransformComponent* tComp = new Me::TransformComponent();
    RotateComponent* rotComp = new RotateComponent();

    tComp->SetPosition(a_positon);
    tComp->SetRotationDegree(a_rotation);
    tComp->SetUniformScale(a_uniformScale);

    if(a_shouldRotate)
        rotComp->m_rotateSpeed = 0.25f;

    rComp->m_mesh = a_mesh;
    rComp->m_shader = shader;
    rComp->m_colour = Me::Colours::WHITE;

    if(a_texture != 0)
        rComp->m_texture = a_texture;

    a_eManager->AddComponent<RotateComponent>(cube, rotComp);
    a_eManager->AddComponent<Me::RenderComponent>(cube, rComp);
    a_eManager->AddComponent<Me::TransformComponent>(cube, tComp);
}