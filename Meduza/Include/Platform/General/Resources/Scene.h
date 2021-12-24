#pragma once
#include "Platform/General/Resources/Resource.h"

namespace Me
{
    namespace Resources
    {
        class Scene : public ResourceBase
        {
        public:
            Scene();
            virtual ~Scene();

            Scene* OnCreate(const std::string& a_path) override;
        private:

        };
    }
}