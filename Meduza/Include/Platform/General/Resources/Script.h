#pragma once
#include "Platform/General/Resources/Resource.h"

namespace Me
{
    struct Value;

    namespace Resources
    {
        class Script : public ResourceBase
        {
        public:
            Script();
            virtual ~Script();

            Script* OnCreate(const std::string& a_path) override;
            void AddInputField(Value* a_input);

        protected:
            void OnInit() override;
        private:
            std::vector<Value*> m_inputFields;
        };
    }
}