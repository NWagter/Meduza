#include "MePCH.h"
#include "Utils/ResourceLoaderUtils.h"

#include "Platform/General/FileSystem/FileSystem.h"
#include "Platform/General/ResourceLibrary.h"
#include "Platform/General/Resources/TextureBase.h"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define TINYGLTF_NOEXCEPTION
#define JSON_NOEXCEPTION

#include "tiny_gltf.h"

bool Me::Utils::Resources::ResourceLoaderUtils::LoadModel(std::string const& a_path, std::vector<MeshPrimitives>& a_meshes)
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

	std::vector<MeshPrimitives> meshes;

	//Load Mesh
	for (size_t i = 0; i < model.meshes.size(); i++)
	{
		MeshPrimitives mesh = MeshPrimitives(model.meshes[i].name);
		for (auto primitive : model.meshes[i].primitives)
		{

			auto attr = primitive.attributes;
			auto extras = model.meshes[i].extras;

			auto attribIter = attr.find("NORMAL");

			if (attribIter != attr.end())
			{
				auto& bufferView = model.bufferViews[model.accessors[attribIter->second].bufferView];
				auto count = model.accessors[attribIter->second].count;
				auto accessorByteOffset = model.accessors[attribIter->second].byteOffset;

				mesh.m_vertices.reserve(count);
				auto& buffer = model.buffers[bufferView.buffer];
				auto start = bufferView.byteOffset;

				for (std::size_t i = 0; i < count; i++)
				{
					Math::Vec3 normals = *(GetElementFromBuffer<Math::Vec3>(&buffer.data[accessorByteOffset], start, i));

					if (mesh.m_vertices.size() <= i)
					{
						Vertex v;
						v.m_normals = normals;
						mesh.m_vertices.push_back(v);
					}
					else
					{
						mesh.m_vertices.at(i).m_normals = normals;
					}
				}
			}

			attribIter = attr.find("POSITION");
			if (attribIter != attr.end())
			{
				auto& bufferView = model.bufferViews[model.accessors[attribIter->second].bufferView];
				auto count = model.accessors[attribIter->second].count;
				auto accessorByteOffset = model.accessors[attribIter->second].byteOffset;

				mesh.m_vertices.reserve(count);
				auto& buffer = model.buffers[bufferView.buffer];
				auto start = bufferView.byteOffset;

				for (std::size_t i = 0; i < count; i++)
				{
					Math::Vec3 vertPos = *(GetElementFromBuffer<Math::Vec3>(&buffer.data[accessorByteOffset], start, i));

					if (mesh.m_vertices.size() <= i)
					{
						Vertex v;
						v.m_vertexPos = vertPos;
						mesh.m_vertices.push_back(v);
					}
					else
					{
						mesh.m_vertices.at(i).m_vertexPos = vertPos;
					}
				}
			}

			attribIter = attr.find("TEXCOORD_0");
			if (attribIter != attr.end())
			{
				auto& bufferView = model.bufferViews[model.accessors[attribIter->second].bufferView];
				auto count = model.accessors[attribIter->second].count;
				auto accessorByteOffset = model.accessors[attribIter->second].byteOffset;

				mesh.m_vertices.reserve(count);
				auto& buffer = model.buffers[bufferView.buffer];
				auto start = bufferView.byteOffset;

				for (std::size_t i = 0; i < count; i++)
				{
					Math::Vec2 textCoord = *(GetElementFromBuffer<Math::Vec2>(&buffer.data[accessorByteOffset], start, i));

					if (mesh.m_vertices.size() <= i)
					{
						Vertex v;
						v.m_uvCoord = textCoord;
						mesh.m_vertices.push_back(v);
					}
					else
					{
						mesh.m_vertices.at(i).m_uvCoord = textCoord;
					}
				}
			}

			int accesorIndex = primitive.indices;
			if (accesorIndex != -1)
			{
				auto& bufferView = model.bufferViews[model.accessors[accesorIndex].bufferView];
				auto count = model.accessors[accesorIndex].count;
				auto accessorByteOffset = model.accessors[accesorIndex].byteOffset;

				mesh.m_indices.reserve(count);

				auto& buffer = model.buffers[bufferView.buffer];
				auto start = bufferView.byteOffset;
				auto compType = model.accessors[accesorIndex].componentType;

				for (std::size_t i = 0; i < count; ++i)
				{
					uint16_t indice = 0;

					if (compType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT)
					{
						indice = static_cast<uint16_t>(*GetElementFromBuffer<unsigned short>(&buffer.data[accessorByteOffset], start, i));
					}
					else if (compType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT)
					{
						indice = (*GetElementFromBuffer<uint16_t>(&buffer.data[accessorByteOffset], start, i));

					}
					else if (compType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE)
					{
						indice = static_cast<uint16_t>(*GetElementFromBuffer<unsigned char>(&buffer.data[accessorByteOffset], start, i));

					}

					mesh.m_indices.push_back(indice);
				}
			}
		}

		meshes.push_back(mesh);
	}

	a_meshes = meshes;

    if (model.textures.size() > 0)
	{
		// fixme: Use material's baseColor
		tinygltf::Texture &tex = model.textures[0];

		if (tex.source > -1) 
		{
			for(size_t i = 0; i < model.textures.size();i++)
			{
				tinygltf::Texture &tex = model.textures[i];
				tinygltf::Image &image = model.images[tex.source];


				if(image.uri != "")
				{
					std::string directory;
					const size_t last_slash_idx = a_path.rfind('/');
					if (std::string::npos != last_slash_idx)
					{
						directory = a_path.substr(0, last_slash_idx);
					}

					Me::Resources::ResourceLibrary::GetInstance()->LoadResource<Me::Resources::TextureBase>(directory + "/" + image.uri);
				}
				else
				{
					auto texture = Me::Resources::TextureBase().Create(image.image, image.width, image.height);
					Me::Resources::ResourceLibrary::GetInstance()->AddResource<Me::Resources::TextureBase>(texture, a_path, Me::Files::FileSystem::GetFileName(a_path));
				}
			}
		}
	}
	
    return true;
}

unsigned char * Me::Utils::Resources::ResourceLoaderUtils::LoadImage(std::string const& a_path, int *a_width, int *a_height, int *a_channels)
{
    const char* file = a_path.c_str();
	return stbi_load(file, a_width, a_height, a_channels, STBI_rgb_alpha);
}

void Me::Utils::Resources::ResourceLoaderUtils::FreeImage(void* a_data)
{
	stbi_image_free(a_data);
}

bool Me::Utils::Resources::ResourceLoaderUtils::LoadGLTFModelFromPath(std::string const& a_path, tinygltf::Model& a_model)
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
bool Me::Utils::Resources::ResourceLoaderUtils::LoadGLBModelFromPath(std::string const& a_path, tinygltf::Model& a_model)
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