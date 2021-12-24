#pragma once
#include "Platform/General/Resources/Resource.h"

namespace Me
{
    namespace Resources
    {
        class Script : public ResourceBase
        {
        public:
            Script();
            virtual ~Script();

            Script* OnCreate(const std::string& a_path) override;
        private:

        };
    }
}