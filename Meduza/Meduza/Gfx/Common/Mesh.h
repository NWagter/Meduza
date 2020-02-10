#pragma once

class Mesh {
public:
	Mesh(MeshType);

	MeshType m_meshId;

	unsigned int m_vertexByteStride = 0;
	unsigned int m_vertexBufferByteSize = 0;
	unsigned int m_indexBufferByteSize = 0;
};