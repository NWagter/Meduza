#pragma once
class PSO;
class CommandList {
public:
	CommandList();

	virtual void Reset(int, PSO*) = 0;
	virtual void Close() = 0;

	//virtual void Draw(RenderItem*) = 0;

};