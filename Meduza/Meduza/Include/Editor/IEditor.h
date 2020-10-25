#pragma once

namespace meduza
{
	namespace editor
	{
		class IEditor
		{
		public:

			virtual ~IEditor() {};

			virtual void Update(const float) = 0;
		};
	}
}