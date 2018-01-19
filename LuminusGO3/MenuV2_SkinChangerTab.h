#pragma once

void MenuV2::DrawSkinChangerTab()
{
	ImGui::Text(xorstr("Skin Changer"));
	ImGui::Separator();

	static vector<string> skins;
	static char skinsStr[1024];

	if (skins.size() == 0)
	{
		skins.push_back(xorstr("Nenhum"));
		skins.push_back(xorstr("Karambit"));
		skins.push_back(xorstr("M9 Bayonet"));
		skins.push_back(xorstr("Butterfly"));

		VectorToArray(skins, skinsStr);
	}

	if (ImGui::Combo(xorstr("Faca"), &cfg.SkinChanger.knife, skinsStr))
		requestFullUpdate = true;
}
