#pragma once

#include "Math/MeduzaMath.h"

namespace meduza
{
	// Colum Matrix
	class Transform
	{
	public:
		Transform();
		Transform(math::Vec3, math::Vec3);
		~Transform() = default;

		// Get the Position of the transform Matrix
		math::Vec3 Position() const;
		math::Vec2 SetPosition(const math::Vec2&);
		math::Vec3 SetPosition(const math::Vec3&);

		// Get the Scale of the transform Matrix
		math::Vec3 Scale() const;
		// Get the Pixel Scale of the transform Matrix
		math::Vec3 GetPixelScale() const;
		math::Vec2 SetScale(const math::Vec2&);
		math::Vec3 SetScale(const math::Vec3&);


	private:

		// Set the Units Per Pixel 
		void SetUnitsPerPixel(const float);
		friend class Renderable2D;

		void Identity();
		float m_transform[16];
		float m_unitsPerPixel = 1;
	};
}