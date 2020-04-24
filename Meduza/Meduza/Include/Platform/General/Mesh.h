#pragma once

#include "Util/MeduzaHelper.h"

namespace meduza
{
	namespace renderer
	{
		class Mesh
		{
		public:
			Mesh(unsigned int, std::vector<Vertex>, std::vector<int>);
			virtual ~Mesh() = default;

			virtual void GenerateBuffers() = 0;

		protected:
			unsigned int m_meshId;
			std::vector<Vertex> m_vertices;
			std::vector<int> m_indices;

			unsigned int m_vertexByteStride = 0;
			unsigned int m_vertexBufferByteSize = 0;
			unsigned int m_indexBufferByteSize = 0;
		};
	}
}