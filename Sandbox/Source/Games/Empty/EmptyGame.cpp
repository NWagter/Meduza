#include "PCH.h"

#include "Games/Empty/EmptyGame.h"

#include "MeduzaIncluder.h"

#include "Components/RotateComponent.h"
#include "Systems/Rotator.h"

EmptyGame::EmptyGame()
{
   m_gameName = "Empty"; 

   new Rotator();
}

EmptyGame::~EmptyGame()
{

}

void EmptyGame::InitGame()
{
    auto eManager = Me::EntityManager::GetEntityManager();

    auto cC = new Me::CameraComponent();
    cC->m_cameraType = Me::CameraType::Perspective;
    cC->m_near = 0.1f;
    cC->m_far = 1000;
    cC->m_size = Me::Event::EventSystem::GetEventSystem()->ScreenSize();

    EntityID entCam = Me::EntityManager::CreateEntity();
    eManager->AddComponent<Me::CameraComponent>(entCam, cC);
    eManager->AddComponent<Me::TransformComponent>(entCam);

    float x = 100;
    float y = 75;
    float z = 50;

    for(int i = -x; i <= x; i += x)
    {
        for(int j = -y; j <= y; j += y)
        {
            for(int n = z; n <= (z * 10); n += z)
            {
                CreateCube(i,j,n, eManager);
            }
        }
    }
}

void EmptyGame::CreateCube(float a_x,float a_y,float a_z, Me::EntityManager* a_eManager)
{
    int i = rand() % 100;
    std::string textureFile = "Assets/Textures/Crate.png";
    Me::Primitives meshId = Me::Primitives::Cube;

    if(i < 50)
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

    tComp->m_position = Me::Math::Vec3(a_x,a_y,a_z);
    tComp->m_uniformScale = static_cast<float>(25);

    rotComp->m_rotateSpeed = 0.25f;

    rComp->m_mesh = mesh;
    rComp->m_shader = shader;
    rComp->m_colour = Me::Colours::WHITE;
    rComp->m_texture = texture;

    a_eManager->AddComponent<RotateComponent>(cube, rotComp);
    a_eManager->AddComponent<Me::RenderComponent>(cube, rComp);
    a_eManager->AddComponent<Me::TransformComponent>(cube, tComp);
}