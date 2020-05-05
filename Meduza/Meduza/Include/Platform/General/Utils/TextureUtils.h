#pragma once

#include "Math/MeduzaMath.h"

namespace meduza
{
	namespace utils
	{
		class TextureUtils
		{
		public:
			static math::Vec4 GetTextureCoords(math::Vec4 a_rect, math::Vec2 a_size, float a_pixelOffset = 0)
			{
                math::Vec4 returnValue = a_rect;

                if (a_rect.m_x != 0 || a_rect.m_z != 1)
                {
                    returnValue.m_x = (1 / a_size.m_x) * (a_rect.m_x + a_pixelOffset);
                    returnValue.m_z = (1 / a_size.m_x) * (a_rect.m_z - a_pixelOffset);
                }
                if (a_rect.m_y != 0 || a_rect.m_w != 1)
                {
                    returnValue.m_y = (1 / a_size.m_y) * (a_rect.m_y + a_pixelOffset);
                    returnValue.m_w = (1 / a_size.m_y) * (a_rect.m_w - a_pixelOffset);
                }
                
                return returnValue;
			}
		};
	}
}