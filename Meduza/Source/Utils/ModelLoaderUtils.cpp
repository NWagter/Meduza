#include "MePCH.h"
#include "Utils/ModelLoaderUtils.h"

#include "Platform/General/FileSystem/FileSystem.h"


#include "tiny_gltf.h"

bool Me::Utils::Resources::ModelLoaderUtils::LoadModel(std::string a_path, std::vector<Vertex>& a_vertices, std::vector<uint16_t>& a_indices)
{
	tinygltf::Model model;
	std::string ext = Files::FileSystem::GetFileExtention(a_path);

	if(ext == "glb")
	{
		//Load Mesh
		if(!LoadGLBModelFromPath(a_path, model))
		{
			return false;
		}
	}
	else if(ext == "gltf")
	{
		//Load Mesh
		if(!LoadGLTFModelFromPath(a_path, model))
		{
			return false;
		}
	}

    std::vector<Vertex> vertices;
	std::vector<uint16_t> indices;

	for(auto primitive : model.meshes[0].primitives)
	{
		auto attr = primitive.attributes;
        auto attribIter = attr.find("NORMAL");

        if (attribIter != attr.end())
        {
			auto& bufferView = model.bufferViews[model.accessors[attribIter->second].bufferView];
			auto count = model.accessors[attribIter->second].count;
			auto accessorByteOffset = model.accessors[attribIter->second].byteOffset;

			vertices.reserve(count);
			auto& buffer = model.buffers[bufferView.buffer];
			auto start = bufferView.byteOffset;

			for(std::size_t i = 0; i < count; i++)
			{
				Math::Vec3 normals = *(GetElementFromBuffer<Math::Vec3>(&buffer.data[accessorByteOffset], start, i));

				if(vertices.size() <= i)
				{
					Vertex v;
					v.m_normals = normals;
					vertices.push_back(v);
				}
				else
				{
					vertices.at(i).m_normals = normals;
				}
			}
		}
	        
		attribIter = attr.find("POSITION");
        if (attribIter != attr.end())
        {
			auto& bufferView = model.bufferViews[model.accessors[attribIter->second].bufferView];
			auto count = model.accessors[attribIter->second].count;
			auto accessorByteOffset = model.accessors[attribIter->second].byteOffset;

			vertices.reserve(count);
			auto& buffer = model.buffers[bufferView.buffer];
			auto start = bufferView.byteOffset;

			for(std::size_t i = 0; i < count; i++)
			{
				Math::Vec3 vertPos = *(GetElementFromBuffer<Math::Vec3>(&buffer.data[accessorByteOffset], start, i));

				if(vertices.size() <= i)
				{
					Vertex v;
					v.m_vertexPos = vertPos;
					vertices.push_back(v);
				}
				else
				{
					vertices.at(i).m_vertexPos = vertPos;
				}
			}
		}
		
		attribIter = attr.find("TEXCOORD_0");
        if (attribIter != attr.end())
        {
			auto& bufferView = model.bufferViews[model.accessors[attribIter->second].bufferView];
			auto count = model.accessors[attribIter->second].count;
			auto accessorByteOffset = model.accessors[attribIter->second].byteOffset;

			vertices.reserve(count);
			auto& buffer = model.buffers[bufferView.buffer];
			auto start = bufferView.byteOffset;

			for(std::size_t i = 0; i < count; ++i)
			{
				Math::Vec2 textCoord = *(GetElementFromBuffer<Math::Vec2>(&buffer.data[accessorByteOffset], start, i));

				if(vertices.size() <= i)
				{
					Vertex v;
					v.m_uvCoord = textCoord;
					vertices.push_back(v);
				}
				else
				{
					vertices.at(i).m_uvCoord = textCoord;
				}
			}
		}
	

		int accesorIndex = primitive.indices;
		if(accesorIndex != -1)
		{
			auto& bufferView = model.bufferViews[model.accessors[accesorIndex].bufferView];
			auto count = model.accessors[accesorIndex].count;
			auto accessorByteOffset = model.accessors[accesorIndex].byteOffset;

			indices.reserve(count);

			auto& buffer = model.buffers[bufferView.buffer];
			auto start = bufferView.byteOffset;
			auto compType = model.accessors[accesorIndex].componentType;

			for(std::size_t i = 0; i < count; ++i)
			{
				uint16_t indice = 0;

				if(compType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT)
				{
					indice = static_cast<uint16_t>(*GetElementFromBuffer<unsigned short>(&buffer.data[accessorByteOffset], start, i));
				}
				else if(compType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT)
				{
					indice = (*GetElementFromBuffer<uint16_t>(&buffer.data[accessorByteOffset], start, i));

				}
				else if(compType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE)
				{
					indice = static_cast<uint16_t>(*GetElementFromBuffer<unsigned char>(&buffer.data[accessorByteOffset], start, i));
					
				}

				indices.push_back(indice);
			}
		}
	}


    a_vertices = vertices;
    a_indices = indices;
    
    return true;
}

bool Me::Utils::Resources::ModelLoaderUtils::LoadGLTFModelFromPath(std::string a_path, tinygltf::Model& a_model)
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
bool Me::Utils::Resources::ModelLoaderUtils::LoadGLBModelFromPath(std::string a_path, tinygltf::Model& a_model)
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