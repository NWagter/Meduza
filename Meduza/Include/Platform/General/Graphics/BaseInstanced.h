#pragma once

namespace Me
{
    namespace Renderer
    {
        constexpr unsigned int MAX_INSTANCES = 4096;

        class BaseInstanced
        {
        public:
            ~BaseInstanced() = default;

            virtual void ClearBuffer() = 0;

            virtual Mesh GetMesh() = 0;
            virtual Shader GetShader() = 0;
            virtual bool ReachedMaxSize() = 0;
            virtual bool Empty() = 0;
        };
    }
}