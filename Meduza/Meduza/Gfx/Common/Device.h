#pragma once
class Device {
public :
	virtual void InitDevice() = 0;
	virtual void DestroyDevice() = 0;
};