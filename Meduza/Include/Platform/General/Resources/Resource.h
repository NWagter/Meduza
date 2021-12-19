#pragma once
namespace Me
{
    namespace Resources
    {
        enum class ResourceType
        {
            Unkown = 0,
            Texture,
            Shader,
            Mesh,
            Script,
            Audio
        };

        class ResourceBase
        {
        public:
            virtual ~ResourceBase() = default;
            
            const Resource& GetID() const { return m_id; }
            const std::string& GetPath() const { return m_path; }
            const std::string& GetFileName() const { return m_fileName; }
            ResourceType GetType() const { return m_type; }

            virtual ResourceBase* OnCreate(const std::string& a_path) = 0;

        protected:
            ResourceBase() : m_type(ResourceType::Unkown) {}
            ResourceBase(ResourceType a_type) : 
                m_type(a_type)
            {}

            std::string m_path;
            std::string m_fileName;
            ResourceType m_type;
        private:
            void InitializeResource(Resource a_id, const std::string& a_path, const std::string& a_fileName)
            {
                m_id = a_id;
                m_path = a_path;
                m_fileName = a_fileName;
            }

            Resource m_id;
            friend class ResourceLibrary;
        };
    }
}