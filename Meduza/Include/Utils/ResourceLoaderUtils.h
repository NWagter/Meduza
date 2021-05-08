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
            class ResourceLoaderUtils
            {
                public:
                    static bool LoadModel(std::string, std::vector<Vertex>&, std::vector<uint16_t>&);

                    static unsigned char * LoadImage(std::string, int*, int*, int*);
                    static void FreeImage(void*);

                private:
                    static bool LoadGLTFModelFromPath(std::string, tinygltf::Model& );
                    static bool LoadGLBModelFromPath(std::string, tinygltf::Model& );

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