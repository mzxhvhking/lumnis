#pragma once

void MenuV2::DrawAimbotTab()
{
	ImGui::Checkbox(MENU_TRANSLATE("Ativar aimbot", "Enable aimbot"), &cfg.Aimbot.enabled);

	if (cfg.Aimbot.enabled)
	{
		const char *opt_MultiHitboxes[14] = { "Head", "Pelvis", "Upper Chest", "Chest", "Neck", "Left Forearm", "Right Forearm", "Hands", "Left Thigh", "Right Thigh", "Left Calf", "Right Calf", "Left Foot", "Right Foot" };
		const char *opt_AimHitboxSpot[] = { "Head", "Neck", "Body", "Pelvis" };
		ImGui::Checkbox(MENU_TRANSLATE("Apenas yaw", "Only yaw"), &cfg.Aimbot.onlyX);
		ImGui::Text("Hitscan");
		ImGui::Separator();
		ImGui::Columns(1, NULL, true);
		{
			ImGui::Checkbox("Prioritize Selected Hitbox", &cfg.Rage.AutoFire.prioritize);
			ImGui::Checkbox(MENU_TRANSLATE("Multi point", "Multi point"), &cfg.Rage.AutoFire.multiPoint);
			if (cfg.Rage.AutoFire.multiPoint)
			{
				ImGui::Text(MENU_TRANSLATE("Point scale", "Point scale"));
				ImGui::SliderFloat(xorstr("##dummyaimbot3"), &cfg.Rage.AutoFire.pointScale, 0.1f, 1.0f, "%.1f");
			}
		}
		ImGui::Columns(1);
		ImGui::Separator();
		for (int i = 0; i < ARRAYSIZE(opt_MultiHitboxes); ++i)
		{
			ImGui::Selectable(opt_MultiHitboxes[i], &cfg.Rage.AutoFire.rage_multiHitboxes[i]);
		}
		ImGui::Columns(1);
		ImGui::Separator();
		vector<string> aimbotSpots;

		char aimbotSpotsStr[1024];

		memset(aimbotSpotsStr, 0, 1024);

		aimbotSpots.push_back(MENU_TRANSLATE("Barriga", "Pelvis"));
		aimbotSpots.push_back(MENU_TRANSLATE("Peito", "Body"));
		aimbotSpots.push_back(MENU_TRANSLATE(u8"Pescoço", "Neck"));
		aimbotSpots.push_back(MENU_TRANSLATE(u8"Cabeça", "Head"));
		VectorToArray(aimbotSpots, aimbotSpotsStr);

		ImGui::Text(MENU_TRANSLATE(u8"Posição", "Select Hitbox"));
		ImGui::Combo(xorstr("Posicao"), &cfg.Aimbot.position, opt_AimHitboxSpot, 4);

		ImGui::Text(MENU_TRANSLATE("Aimbot FOV", "Aimbot FOV"));
		ImGui::SliderFloat(xorstr("##dummyaimbot1"), &cfg.Aimbot.fov, 0, 180.0f, "%.1f");

		if (cfg.Aimbot.fov < 0.0f)
			cfg.Aimbot.fov = 0.0f;
		if (cfg.Aimbot.fov > 180.0f)
			cfg.Aimbot.fov = 180.0f;

		ImGui::Text(MENU_TRANSLATE("Tempo de espera", "Delay"));
		ImGui::SliderInt(xorstr("##dummyaimbot5"), &cfg.Aimbot.recoverTime, 0, 1000);
		ImGui::Separator();

		ImGui::Checkbox(MENU_TRANSLATE("Usar suavidade [BETA]", "Use smooth [BETA]"), &cfg.Aimbot.Smooth.enabled);
		if (cfg.Aimbot.Smooth.enabled)
		{
			ImGui::Text(MENU_TRANSLATE("Suavidade", "Smooth"));
			ImGui::SliderFloat(xorstr("##dummyaimbot4"), &cfg.Aimbot.Smooth.ammount, 1.0f, 6.0f);
		}

		if (cfg.Aimbot.silent)
			cfg.Aimbot.Smooth.enabled = false;

		if (cfg.Aimbot.Aimstep.enabled)
			cfg.Aimbot.onlyX = false;

		ImGui::Checkbox(MENU_TRANSLATE("Usar aimstep", "Use aimstep"), &cfg.Aimbot.Aimstep.enabled);
		if (cfg.Aimbot.Aimstep.enabled)
		{
			ImGui::Text(MENU_TRANSLATE("Graus/tick", "Degree/tick"));
			ImGui::SliderFloat(xorstr("##dummyaimbot6"), &cfg.Aimbot.Aimstep.ammount, 0.5f, 30.0f, "%.0f");
		}

		ImGui::Separator();

		ImGui::Checkbox(MENU_TRANSLATE("Silent", "Silent"), &cfg.Aimbot.silent);
		ImGui::Separator();

		ImGui::Checkbox(MENU_TRANSLATE(u8"Aliados são alvos", "Friendly fire"), &cfg.Aimbot.friendlyFire);
	}
}
