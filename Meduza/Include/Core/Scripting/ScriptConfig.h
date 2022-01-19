#pragma once

namespace Me
{
	namespace Resources
	{
		class Script;
	}

	namespace Scripting
	{
		struct Value;
		enum class ValueType;
		struct ScriptConfigData;

		class ScriptConfig
		{
		public:
			~ScriptConfig();
			static ScriptConfig* CreateScriptConfig();
			static ScriptConfig* GetScriptConfig() { return ms_instance; }

			bool InitializeScriptConfig(std::string const& a_path, std::string const& a_projectName);
			bool LoadScriptConfig(std::string const& a_path, std::string const& a_projectName, std::string const& a_assetPath);

			void AddScript(Resources::Script& a_script);
			void AddValue(Resource const a_resource);
			Value* ChangeType(ScriptConfigData* a_dataSet, int a_index, ValueType a_newType);

			void OnChange(Resource const a_resource);

			std::unordered_map<Resource, ScriptConfigData*> GetConfigData() const
			{
				return m_config;
			}
		private:
			ScriptConfig();

			void SerializeScriptData();
			void Clear();

			std::unordered_map<Resource, ScriptConfigData*> m_config;

			std::string m_projectName;
			std::string m_scriptPath;
			static ScriptConfig* ms_instance;
		};
	}
}