#pragma once
#include "ECS/BaseSystem.h"

namespace Me
{
	struct TransformComponent;

	namespace Particle
	{
		struct ParticleComponent;

		class ParticleSystem : public BaseSystem<ParticleComponent, TransformComponent>
		{
		public:
			ParticleSystem();

		protected:
			void OnUpdate(float) override;
		};
	}
}