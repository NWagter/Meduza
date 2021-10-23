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
                Serializer(std::string = "");
                ~Serializer();

                bool SerializeScene();
                bool SerializeSceneAs(std::string);
                bool DeserializeScene(std::string = "");

                bool SerializeEntity(std::string, EntityID);
                EntityID DeserializeEntity(std::string);

                static Serializer* GetInstance() { return ms_instance;}
            private:
                std::string m_activeScene;
                static Serializer* ms_instance;
        };
    }
}