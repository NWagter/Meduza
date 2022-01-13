#pragma once

#include "Platform/General/FileSystem/FileSystem.h"

namespace Me
{
    namespace Resources
    {
		class ResourceBase;

        class ResourceLibrary
        {
        public:
            static ResourceLibrary* CreateResourceLibrary();
			static ResourceLibrary* GetInstance();
            static void Destroy();

            template<typename T, typename = typename std::enable_if<std::is_base_of<ResourceBase, T>::value, T>::type, typename ... Args>
            T* LoadResource(std::string const& a_path, Args... a_args);


			template<typename T, typename = typename std::enable_if<std::is_base_of<ResourceBase, T>::value, T>::type, typename ... Args>
			T* AddResource(T* a_resource, std::string const& a_path, std::string const& a_name);

			template<typename T>
			T* GetResource(Resource const a_resourceId);

			std::unordered_map<Resource, ResourceBase*> const& GetResources() const { return m_resources; }

			void Cleanup(bool a_baseLoad);
        private:
			ResourceLibrary();
			~ResourceLibrary() = default;

			void BaseLoad();
			//Base Geometry
			void CreateQuad();
			void CreatePlane();
			void CreateCube();
			void CreateSphere();

			static ResourceLibrary* ms_instance;
            std::unordered_map<Resource, ResourceBase*> m_resources;
        };

		template <typename T, typename, class... Args>
		T* ResourceLibrary::LoadResource(std::string const& a_path, Args... a_args)
		{
			std::string fileName = Files::FileSystem::GetFileName(a_path);			
			Resource id = Utils::Utilities::GetHashedID(fileName);

			//Check if resource is already loaded in.
			T* resource = GetResource<T>(id);
			if (resource != nullptr)
			{
				return resource;
			}

			resource = T(a_args...).OnCreate(a_path);

			if (GetResource<T>(id) != nullptr)
			{
				return resource;
			}

			resource->InitializeResource(id, a_path, fileName);
			m_resources.insert(std::make_pair(id, resource));

			return resource;
		}

		template <typename T, typename, class... Args>
		T* ResourceLibrary::AddResource(T* a_resource, std::string const& a_path, std::string const& a_name)
		{
			Resource id = Utils::Utilities::GetHashedID(a_name);

			T* resource = GetResource<T>(id);
			if (resource != nullptr)
			{
				delete a_resource;
				return resource;
			}

			a_resource->InitializeResource(id, a_path, a_name);
			m_resources.insert(std::make_pair(id, a_resource));

			return a_resource;
		}

		template <typename T>
		T* ResourceLibrary::GetResource(Resource const a_resourceId)
		{
			const auto it = m_resources.find(a_resourceId);
			if (it != m_resources.end())
			{
				return dynamic_cast<T*>(it->second);
			}

			return nullptr;
		}
    }
}