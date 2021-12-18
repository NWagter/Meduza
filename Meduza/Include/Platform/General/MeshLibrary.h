#pragma once
namespace Me
{
    namespace Renderer
    {
        class RenderLayer;
    }

    namespace Utils
    {
        namespace Resources
        {
            struct MeshPrimitives;
        }
    }

    namespace Resources
    {
        class MeshBase;

        class MeshLibrary
        {
        public:
            static MeshLibrary* CreateMeshLibrary(Renderer::RenderLayer&);
            static void Destroy();

            static Mesh CreateMesh(std::string);
            static Mesh CreateMesh(std::string, Mesh, std::vector<Vertex>, std::vector<uint16_t>);
            static Mesh CreateMeshes(std::string, std::vector<Utils::Resources::MeshPrimitives>);
                    
            static Mesh GetMeshIndex(std::string);
            static Mesh GetMeshIndex(Primitives);
        
            static MeshBase* GetMesh(std::string);
            static MeshBase* GetMesh(Mesh);

            static bool UnLoadMesh(std::string);
            static bool UnLoadMesh(Mesh, bool = true);

        private:
            MeshLibrary(Renderer::RenderLayer&);
            ~MeshLibrary();

            void CreateQuad();
            void CreatePlane();
            void CreateCube();
            void CreateSphere();
            
            Renderer::RenderLayer* m_renderLayer;

            static MeshLibrary* ms_instance;
            std::unordered_map<Mesh, MeshBase*> m_meshes;
        };
    }
}