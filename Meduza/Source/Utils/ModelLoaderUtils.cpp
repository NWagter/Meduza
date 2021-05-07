#include "MePCH.h"
#include "Utils/ModelLoaderUtils.h"

#include "tiny_gltf.h"

bool Me::Utils::Resources::LoadGLTFModelFromPath(std::string a_path, tinygltf::Model& a_model)
{
    tinygltf::TinyGLTF loader;
    std::string err;
    std::string warn;

    bool res = loader.LoadASCIIFromFile(&a_model, &err, &warn, a_path);

    if (!warn.empty())
    {
        ME_CORE_LOG("Warning loading %s : %s ", a_path.c_str(), warn.c_str());
        return false;
    }

    if (!err.empty())
    {
        ME_CORE_LOG("Error loading %s : %s ", a_path.c_str(), err.c_str());
        return false;
    }

    if(!res)
    {
        ME_CORE_LOG("Failed to load : %s", a_path.c_str());
        return false;
    }
    
    return true;
}
bool Me::Utils::Resources::LoadGLBModelFromPath(std::string a_path, tinygltf::Model& a_model)
{
    tinygltf::TinyGLTF loader;
    tinygltf::Model model;
    std::string err;
    std::string warn;

    bool res = loader.LoadBinaryFromFile(&a_model, &err, &warn, a_path);

    if (!warn.empty())
    {
        ME_CORE_LOG("Warning loading %s : %s ", a_path.c_str(), warn.c_str());
        return false;
    }

    if (!err.empty())
    {
        ME_CORE_LOG("Error loading %s : %s ", a_path.c_str(), err.c_str());
        return false;
    }

    if(!res)
    {
        ME_CORE_LOG("Failed to load : %s", a_path.c_str());
        return false;
    }

    return true;
}