#pragma once
#include "Platform/General/Resources/Resource.h"

namespace Me
{
    namespace Scripting
    {
        struct Value;
    }

    namespace Resources
    {
        class Script : public ResourceBase
        {
        public:
            Script();
            virtual ~Script();

            Script* OnCreate(const std::string& a_path) override;
            void AddInputField(Scripting::Value* a_input);

        protected:
            void OnInit() override;
        private:
            std::vector<Scripting::Value*> m_inputFields;
        };
    }
}