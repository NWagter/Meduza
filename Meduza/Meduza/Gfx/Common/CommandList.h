#pragma once


class CommandList {
public:
	CommandList();

	virtual void Close() = 0;

	virtual void Draw(uint32_t vertexCount, uint32_t instanceCount, uint32_t startVertex, uint32_t startInstance) = 0;
	virtual void DrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t startIndex, int32_t baseVertex, uint32_t startInstance) = 0;

};