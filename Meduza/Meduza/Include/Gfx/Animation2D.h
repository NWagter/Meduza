#pragma once

#include "Animation.h"

#include "Math/MeduzaMath.h"

namespace meduza
{
	class Renderable2D;

	class Texture;

	struct Frame
	{
		unsigned int m_frame;
		math::Vec4 m_frameRect;
	};

	namespace gfx
	{
		class Animation2D : public Animation
		{
		public:
			Animation2D(std::string, float, Texture&);
			Animation2D(std::string, float, std::string);
			~Animation2D() override;

			void AddFrame(math::Vec4);
			void UpdateFrame(Renderable2D&);

			// Inherited via Animation
			virtual void OnStart() override;
			virtual void OnEnd() override;

		private:
			unsigned int m_frameCount = 0;
			std::vector<Frame> m_frames;

			Texture* m_texture;
			std::string m_textureName;

			unsigned int m_currentFrame = 0;

		};
	}
}