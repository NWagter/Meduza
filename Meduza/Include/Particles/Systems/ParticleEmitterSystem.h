#pragma once
#include "ECS/BaseSystem.h"

namespace Me
{
	struct TransformComponent;

	namespace Particle
	{
		struct ParticleSystemComponent;

		class ParticleEmitterSystem : public BaseSystem<ParticleSystemComponent, TransformComponent>
		{
		public:
			ParticleEmitterSystem();

		protected:
			void OnUpdate(float a_dt) override;

			Shader m_defaultShader;
			Mesh m_defaultMesh;
		};
	}
}