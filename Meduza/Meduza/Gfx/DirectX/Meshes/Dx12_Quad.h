#pragma once

#include "Dx12_Mesh.h"

class Dx12_Quad : public Dx12_Mesh {

public:
	Dx12_Quad(MeshType, const Dx12_Device&, Dx12_CommandList*);
};