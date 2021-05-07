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
            class ModelLoaderUtils
            {
                public:
                    static bool LoadModel(std::string a_path, std::vector<Vertex>& a_vertices, std::vector<uint16_t>& a_indices);

                private:
                    static bool LoadGLTFModelFromPath(std::string a_path, tinygltf::Model& a_model);
                    static bool LoadGLBModelFromPath(std::string a_path, tinygltf::Model& a_model);

                    template<typename T>
                    inline static const T* GetElementFromBuffer(const unsigned char* a_data, const std::size_t a_offset, const std::size_t a_index)
                    {
                        assert(a_data != nullptr);

                        return reinterpret_cast<const T*>(reinterpret_cast<std::size_t>(a_data) + a_offset + (a_index * sizeof(T)));
                    }
            };
        }
    }
}