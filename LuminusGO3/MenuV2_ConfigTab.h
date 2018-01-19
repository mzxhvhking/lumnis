#pragma once

void MenuV2::DrawConfigTab()
{
	static char cfgsStr[4096];
	static int index;
	static bool safeDelete = false, safeSave = false;
	static char name[128];

	static std::vector<string> vecLanguages;
	static char strLanguages[20];

	if (vecLanguages.size() == 0)
	{
		vecLanguages.push_back(xorstr("PT-BR"));
		vecLanguages.push_back(xorstr("ENGLISH"));

		memset(strLanguages, 0, 20);
		VectorToArray(vecLanguages, strLanguages);
	}

	memset(cfgsStr, 0, 4096);
	VectorToArray(cfgMgr->files, cfgsStr);
	
	ImGui::Text(MENU_TRANSLATE("Linguagem", "Language"));
	ImGui::Combo(xorstr("##dummyconfigs0"), &cfg.language, strLanguages);

	ImGui::Separator();

	ImGui::Text("%s: %s [%s]", MENU_TRANSLATE(u8"Configuração atual", "Current configuration"), cfgMgr->actualConfig.c_str(), cfgMgr->GetConfigPath().c_str());

	if (ImGui::Combo(xorstr("##dummyconfigs1"), &index, cfgsStr))
	{
		cfgMgr->GetConfigFiles();
		strcpy_s(name, 128, cfgMgr->files[index].c_str());
	}

	ImGui::SameLine();

	if (ImGui::Button(MENU_TRANSLATE("Carregar", "Load")))
	{
		cfgMgr->ReadConfig(cfgMgr->files[index]);
		cfg.Rage.AntiAim.untrusted = false;
	}

	ImGui::Separator();

	ImGui::Checkbox(std::string(MENU_TRANSLATE("Deletar ", "Delete ") + cfgMgr->files[index] + "?").c_str(), &safeDelete);
	ImGui::SameLine();
	ImGui::Checkbox(std::string(MENU_TRANSLATE("Salvar ", "Save ") + cfgMgr->files[index] + "?").c_str(), &safeSave);

	if (safeSave)
	{
		ImGui::Text(MENU_TRANSLATE(u8"Salvar configuração atual", "Save current configuration"));
		ImGui::Separator();

		ImGui::Text(MENU_TRANSLATE("Nome: ", "Name: "));
		ImGui::InputText(xorstr("##dummyconfigs2"), name, 128);

		if (ImGui::Button(MENU_TRANSLATE("Salvar", "Save")))
		{
			std::string n = std::string(name);

			if (n.find(".json") == -1)
				n += ".json";

			cfgMgr->WriteConfig(n);
			cfgMgr->GetConfigFiles();
		}
	}

	if (safeDelete)
	{
		ImGui::Text(MENU_TRANSLATE(u8"DELETAR configuração atual", "DELETE current configuration"));
		ImGui::Separator();

		if (ImGui::Button(MENU_TRANSLATE("Deletar", "Delete")))
		{
			cfgMgr->RemoveConfig(cfgMgr->files[index]);
			cfgMgr->GetConfigFiles();
			safeDelete = false;
		}
	}
}
