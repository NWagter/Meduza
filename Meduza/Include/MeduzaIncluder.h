#pragma once

#include "Core/Core.h"
#include "Math/Math.h"
#include "Core/MeduzaCore.h"

#include "Core/Application.h"

#include "Utils/MeduzaUtils.h"


///--------- ECS --------
#include "ECS/EntityTypes.h"
#include "ECS/EntityManager.h"
#include "ECS/BaseComponent.h"
#include "ECS/BaseSystem.h"
///--------- Serializer --------
#include "Core/Serialization/Serializer.h"
///--- Base Components --
#include "Core/Components/TransformComponent.h"
#include "Core/Components/RenderComponent.h"
#include "Core/Components/CameraComponent.h"
///------ Physics -------
#include "Physics/Physics.h"
#include "Physics/Components/PhysicsComponent.h"
///------ Library -------
#include "Platform/General/ResourceLibrary.h"
//------ Events ---------
#include "Platform/General/Events/EventSystem.h"
#include "Platform/General/Events/Events.h"
///--- Base Resources --
#include "Platform/General/Resources/MeshBase.h"
#include "Platform/General/Resources/ShaderBase.h"
#include "Platform/General/Resources/TextureBase.h"