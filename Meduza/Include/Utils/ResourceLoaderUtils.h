#pragma once

namespace tinygltf
{
    class Model;
}

namespace Me
{
    namespace Utils
    {
        namespace Resources 
        {
            struct MeshPrimitives
            {
                std::string m_name;
                std::vector<Vertex> m_vertices;
                std::vector<uint16_t> m_indices;

                MeshPrimitives(std::string a_name)
                {
                    m_name = a_name;
                }
            };

            class ResourceLoaderUtils
            {
                public:
                    static bool LoadModel(std::string const& a_path, std::vector<MeshPrimitives>& a_meshes);

                    static unsigned char * LoadImage(std::string const& a_path, int* a_width, int* a_height, int* a_channels);
                    static void FreeImage(void* a_data);

                private:
                    static bool LoadGLTFModelFromPath(std::string const& a_path, tinygltf::Model& a_model);
                    static bool LoadGLBModelFromPath(std::string const& a_path, tinygltf::Model& a_model);

                    template<typename T>
                    inline static const T* GetElementFromBuffer(const unsigned char* a_data, std::size_t const a_offset, std::size_t const a_index)
                    {
                        assert(a_data != nullptr);

                        return reinterpret_cast<const T*>(reinterpret_cast<std::size_t>(a_data) + a_offset + (a_index * sizeof(T)));
                    }
            };
        }
    }
}