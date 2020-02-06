#pragma once

class CommandList {
public:
	CommandList();

	virtual void Reset(int) = 0;
	virtual void Close() = 0;

	virtual void Draw(RenderItem*) = 0;

};