#pragma once

void MenuV2::DrawVisualTab()
{
	vector<string> tabs;

	tabs.push_back(MENU_TRANSLATE("Visual", "Visual"));
	tabs.push_back(MENU_TRANSLATE("Cores", "Colors"));

	static int selectedTab = 0;

	ImGui::TabLabels(tabs, selectedTab, true);
	{
		switch (selectedTab)
		{
		case 0: DrawVisualVisualTab(); break;
		case 1: DrawVisualColorsTab(); break;
		}
	}	
}

void MenuV2::DrawVisualVisualTab()
{
	ImGui::Columns(3);

	ImGui::Checkbox(MENU_TRANSLATE("Ativar visuais", "Enable visuals"), &cfg.Visual.enabled);
	ImGui::Separator();

	if (cfg.Visual.enabled)
	{
		ImGui::Text(MENU_TRANSLATE(u8"Transparência", "Opacity"));
		ImGui::SliderInt(xorstr("##dummyvisuals0"), &cfg.Visual.espAlpha, 0, 200);

		ImGui::Checkbox(MENU_TRANSLATE("FOV do aimbot", "Aimbot FOV"), &cfg.Visual.drawFOV);

		if (cfg.Visual.drawFOV)
		{
			ImGui::SameLine();
			ImGui::Checkbox(MENU_TRANSLATE(u8"Dinâmico", "Dynamic"), &cfg.Visual.dinamicFOV);
		}

		ImGui::Text(MENU_TRANSLATE(u8"FOV da camera", "Camera FOV"));
		ImGui::SliderFloat(xorstr("##dummyvisuals1"), &cfg.Misc.fovChanger, 0.0f, 120.0f);
		ImGui::Checkbox(MENU_TRANSLATE("Travar FOV", "Lock FOV"), &cfg.Visual.lockFov);

		ImGui::Checkbox(MENU_TRANSLATE("Mira", "Crosshair"), &cfg.Visual.drawCrosshair);
		ImGui::Checkbox(MENU_TRANSLATE("Exibir aliados", "Show team"), &cfg.Visual.showTeam);
		ImGui::Checkbox(MENU_TRANSLATE("Exibir dormentes", "Show dormants"), &cfg.Visual.dormantEsp);
		ImGui::Checkbox(MENU_TRANSLATE("Exibir no jogador", "Show in local player"), &cfg.Visual.localPlayerVisuals);
		ImGui::Checkbox(MENU_TRANSLATE("Itens dropados", "Dropped items"), &cfg.Visual.drawItems);
		ImGui::Checkbox(MENU_TRANSLATE("Nome de itens dropados", "Dropped items names"), &cfg.Visual.drawItemsNames);
		if (cfg.Visual.drawItemsNames) {
			ImGui::Combo("##ItemNames", &cfg.Visual.drawWeaponIcons, "Icon\0Text\0");
		}
		ImGui::NextColumn();

		ImGui::Checkbox(MENU_TRANSLATE(u8"Traçado", "Tracers"), &cfg.Visual.drawTracers);
		ImGui::Checkbox(MENU_TRANSLATE("Nome", "Name"), &cfg.Visual.drawNames);
		ImGui::Checkbox(MENU_TRANSLATE("Arma", "Weapon"), &cfg.Visual.drawWeapons);
		ImGui::Checkbox(MENU_TRANSLATE(u8"Mira Spread", "Spread Crosshair"), &cfg.Visual.spreadCrosshair);
		ImGui::Checkbox(MENU_TRANSLATE(u8"Mostrar munição", "Bullets"), &cfg.Visual.drawAmmo);
		ImGui::Checkbox(MENU_TRANSLATE("Som do hitmarker", "Hitmarker Sound"), &cfg.Visual.hitmarkersound);
		ImGui::Checkbox(MENU_TRANSLATE("Exibir dano", "Show damage"), &cfg.Visual.damageESP);
		ImGui::Checkbox(MENU_TRANSLATE("Vida", "Health"), &cfg.Visual.drawHealth);
		ImGui::SameLine();
		ImGui::Checkbox(MENU_TRANSLATE(u8"Divisão", "Divisison"), &cfg.Visual.drawHealthDivision);
		//ImGui::Checkbox(MENU_TRANSLATE("Lagometer", "Lagometer"), &cfg.Visual.lagometer);
		//ImGui::Checkbox(MENU_TRANSLATE("Fill", "Fill"), &cfg.Visual.boxFill);
		ImGui::Checkbox(MENU_TRANSLATE("Caixa", "Box"), &cfg.Visual.drawBox);
		ImGui::Checkbox(MENU_TRANSLATE("Esqueleto", "Skeleton"), &cfg.Visual.drawBones);

		ImGui::Checkbox(MENU_TRANSLATE("Glow", "Glow"), &cfg.Visual.glow);
		ImGui::Checkbox(MENU_TRANSLATE("Chams", "Chams"), &cfg.Visual.chams);
		ImGui::Checkbox(MENU_TRANSLATE("Chams Ignore-Z", "Chams Ignore-Z"), &cfg.Visual.wallChams);
		ImGui::Checkbox(MENU_TRANSLATE(u8"Chams para mãos", "Hand chams"), &cfg.Visual.handChams);
		ImGui::Checkbox(MENU_TRANSLATE("Vidro", "Glass"), &cfg.Visual.glassHands);
		ImGui::SameLine();
		ImGui::Checkbox(MENU_TRANSLATE("Escuro", "Dark"), &cfg.Visual.darkHandChams);
		ImGui::Checkbox(MENU_TRANSLATE("Chams HvH", "Chams HvH"), &cfg.Visual.hvhChams);

		ImGui::NextColumn();

		ImGui::Text(MENU_TRANSLATE("Misc", "Misc"));
		ImGui::Checkbox(MENU_TRANSLATE("Noite", "Night mode"), &cfg.Visual.nightMode);
		ImGui::Checkbox(MENU_TRANSLATE(u8"Trajetória da granada", "Grenade trajectory"), &cfg.Visual.granadePrediction);
		ImGui::Checkbox(MENU_TRANSLATE("Destravar FPS", "Unlock FPS"), &cfg.Misc.unlockFps);
		ImGui::Checkbox(MENU_TRANSLATE("Remover scope", "Remove scope"), &cfg.Visual.noScope);
		ImGui::Checkbox(MENU_TRANSLATE("Remover pos processamento", "Remove postprocess"), &cfg.Visual.disablePostProcess);
		ImGui::Checkbox(MENU_TRANSLATE("Boost de FPS", "FPS boost"), &cfg.Visual.fpsBoost);

		ImGui::Checkbox(MENU_TRANSLATE("Debug autowall", "Debug autowall"), &cfg.Visual.debugAutowall);
		ImGui::Checkbox(MENU_TRANSLATE("Debug aimbot", "Debug aimbot"), &cfg.Visual.showAimPoint);
		ImGui::Checkbox(MENU_TRANSLATE("Debug multipoint", "Debug multipoint"), &cfg.Visual.debugMultipoint);

		//ImGui::Separator();
		//ImGui::Checkbox(xorstr("Screenshot Cleaner"), &cfg.Visual.screenshotCleaner);
	}
}

void MenuV2::DrawVisualColorsTab()
{
	{
		float col[3] = { min(255.f, cfg.Visual.colorGlow.r() / 255.f),  min(255.f, cfg.Visual.colorGlow.g() / 255.f),  min(255.f, cfg.Visual.colorGlow.b() / 255.f) };

		if (ImGui::ColorEdit3(MENU_TRANSLATE("Glow", "Glow"), col))
			cfg.Visual.colorGlow = Color((BYTE)(col[0] * 255), (BYTE)(col[1] * 255), (BYTE)(col[2] * 255), 255);
	}

	{
		float col[3] = { min(255.f, cfg.Visual.colorChamsVisible.r() / 255.f),  min(255.f, cfg.Visual.colorChamsVisible.g() / 255.f),  min(255.f, cfg.Visual.colorChamsVisible.b() / 255.f) };

		if (ImGui::ColorEdit3(MENU_TRANSLATE(u8"Chams visível", "Chams visible"), col))
			cfg.Visual.colorChamsVisible = Color((BYTE)(col[0] * 255), (BYTE)(col[1] * 255), (BYTE)(col[2] * 255), 255);
	}

	{
		float col[3] = { min(255.f, cfg.Visual.colorChamsHidden.r() / 255.f),  min(255.f, cfg.Visual.colorChamsHidden.g() / 255.f),  min(255.f, cfg.Visual.colorChamsHidden.b() / 255.f) };

		if (ImGui::ColorEdit3(MENU_TRANSLATE(u8"Chams escondido", "Chams hidden"), col))
			cfg.Visual.colorChamsHidden = Color((BYTE)(col[0] * 255), (BYTE)(col[1] * 255), (BYTE)(col[2] * 255), 255);
	}
}
