#include "MePCH.h"
#include "Core/Scripting/API/Lua_SceneManager.h"

#include "Core/Serialization/Serializer.h"

void Me::Scripting::Lua_API::Lua_SceneManager::RegisterSceneManagerFunctions(lua_State* a_luaState)
{
	lua_register(a_luaState, "_LoadScene", lua_LoadScene);
	lua_register(a_luaState, "_LoadCleanScene", lua_LoadCleanScene);
}

bool Me::Scripting::Lua_API::Lua_SceneManager::LoadScene(lua_State* a_luaState, std::string& a_scene)
{
	if (lua_gettop(a_luaState) != 1) return false;

	a_scene = "Assets/Scenes/";
	a_scene.append(lua_tostring(a_luaState, 1));
	a_scene.append(".scene");
	
	return true;
}


int Me::Scripting::Lua_API::Lua_SceneManager::lua_LoadScene(lua_State* a_luaState)
{
	std::string scene;
	if (!LoadScene(a_luaState, scene)) return -1;

	Serialization::Serializer::GetInstance()->DeserializeScene(scene, false, false);

	return 1;
}

int Me::Scripting::Lua_API::Lua_SceneManager::lua_LoadCleanScene(lua_State* a_luaState)
{
	std::string scene;
	if (!LoadScene(a_luaState, scene)) return -1;

	Serialization::Serializer::GetInstance()->DeserializeScene(scene, false, true);

	return 1;
}
