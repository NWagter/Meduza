#pragma once
namespace cr {

	static const int    gs_numBuffers = 3;

	struct Vertex {

		Vertex(float a_x, float a_y, float a_z) {
			m_pos.x = a_x;
			m_pos.y = a_y;
			m_pos.z = a_z;
		}

		Vertex(glm::vec3 a_vec) {
			m_pos = a_vec;
		}

		glm::vec3 m_pos;
	};

	struct MeshBuffer {

		std::vector<Vertex> m_vertices;
		std::vector<std::uint16_t> m_indices;
	};

	enum class DrawType {

		Triangle = 0,
		Quad
	};

	struct Drawable {

		DrawType a_drawtype = DrawType::Quad;
		glm::vec3 m_position;
		glm::vec3 m_size = {1,1,1};
		float m_zRotation = 0;
		glm::vec4 m_colour = {1,0,1,1};
	};

	class Mesh {
	public:
		Mesh(MeshBuffer a_meshBuffer) { m_meshBuffer = a_meshBuffer; }
		virtual ~Mesh() {}
		inline unsigned int GetIndexCount() { return static_cast<unsigned int>(m_meshBuffer.m_indices.size()); }
	protected:

		MeshBuffer m_meshBuffer;

		unsigned int m_vertexByteStride = 0;
		unsigned int m_vertexBufferByteSize = 0;
		unsigned int m_indexBufferByteSize = 0;
	};
}