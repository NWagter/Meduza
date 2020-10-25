#pragma once
namespace Me
{
    namespace Renderer
    {
        class RenderLayer;
    }

    namespace Resources
    {
        class MeshBase;

        class MeshLibrary
        {
        public:
            static MeshLibrary* CreateMeshLibrary(Renderer::RenderLayer&);
            static void Destroy();

            static MeshBase* CreateMesh(std::string);
            static MeshBase* CreateMesh(unsigned int, std::vector<Vertex>, std::vector<uint16_t>);
            
            static MeshBase* GetMesh(std::string);
            static MeshBase* GetMesh(unsigned int);

            static bool UnLoadMesh(std::string);
            static bool UnLoadMesh(unsigned int, bool = true);

        private:
            MeshLibrary(Renderer::RenderLayer&);
            ~MeshLibrary();
            
            Renderer::RenderLayer* m_renderLayer;

            static MeshLibrary* ms_instance;
            std::unordered_map<unsigned int, MeshBase*> m_meshes;
        };
    }
}