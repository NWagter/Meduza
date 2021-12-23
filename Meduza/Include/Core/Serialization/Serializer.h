#pragma once

using EntityID = uint64_t;

namespace Me
{
    struct TagComponent;

    namespace Serialization
    {
        class Serializer
        {
            public:
                Serializer(std::string a_file = "");
                static void DestroySerializer();

                bool SerializeScene();
                bool SerializeSceneAs(std::string a_file);
                bool DeserializeScene(std::string a_file = "", bool a_rememberScene = true, bool a_cleanup = true);

                bool SerializeEntity(std::string a_file, EntityID a_entityId);
                EntityID DeserializeEntity(std::string a_file);

                static Serializer* GetInstance() { return ms_instance;}
            private:
                ~Serializer();
                std::string m_activeScene;
                static Serializer* ms_instance;
        };
    }
}