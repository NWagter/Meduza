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

                bool SerializeScene(std::string);
                bool DeserializeScene(std::string);

                static Serializer* GetInstance() { return ms_instance;}
            private:
                static Serializer* ms_instance;
        };
    }
}