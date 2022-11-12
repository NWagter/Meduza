#pragma once
namespace Me
{
    namespace Resources
    {
        enum class ResourceType : uint8_t
        {
            Audio,
            Mesh,
            Prefab,
            Scene,
            Script,
            Shader,
            Texture,

            LAST,
            Unknown
        };
        static const char* gs_resourceTypes[] =
        { "Audio", "Mesh", "Prefab", "Scene", "Script", "Shader", "Texture"};

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
            ResourceBase() : m_type(ResourceType::Unknown) {}
            ResourceBase(ResourceType a_type) : 
                m_type(a_type)
            {}

            virtual void OnInit() {}
            virtual void OnLoad() {}

            std::string m_path;
            std::string m_fileName;
            ResourceType m_type;
        private:

            virtual void InitializeResource(Resource a_id, const std::string& a_path, const std::string& a_fileName)
            {
                m_id = a_id;
                m_path = a_path;
                m_fileName = a_fileName;

                OnInit();
            }

            Resource m_id;
            friend class ResourceLibrary;
        };
    }
}