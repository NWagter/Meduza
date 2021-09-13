#pragma once

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

                static Serializer* GetInstance() { return ms_instance;}
            private:
                std::string m_activeScene;
                static Serializer* ms_instance;
        };
    }
}