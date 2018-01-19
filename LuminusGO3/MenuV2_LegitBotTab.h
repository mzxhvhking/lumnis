#pragma once

void MenuV2::DrawLegitBotTab()
{
	ImGui::Checkbox(MENU_TRANSLATE("Ativar LegitBot", "Enable LegitBot"), &cfg.LegitBot.enabled);

	if (cfg.LegitBot.enabled)
	{
		ImGui::Checkbox(MENU_TRANSLATE("AimBot", "AimBot"), &cfg.LegitBot.aimbot);

		if (cfg.LegitBot.aimbot)
		{
			ImGui::Text(MENU_TRANSLATE("Aimbot FOV", "Aimbot FOV"));
			ImGui::SliderFloat(xorstr("##dummylegitbot0"), &cfg.LegitBot.fov, 0, 35.0f, "%.1f");

			ImGui::Text(MENU_TRANSLATE("Rifle logsmooth", "Rifle logsmooth"));
			ImGui::SliderFloat(xorstr("##dummylegitbot1"), &cfg.LegitBot.smooth, 0, 1.0f, "%.1f");

			ImGui::Text(MENU_TRANSLATE("Aimbot delay [s]", "Aimbot delay [s]"));
			ImGui::SliderFloat(xorstr("##dummyaimbot2"), &cfg.LegitBot.delay, 0, 1.0f, "%.1f");

			ImGui::Checkbox(MENU_TRANSLATE("AimLock", "AimLock"), &cfg.LegitBot.aimLock);

			ImGui::Checkbox(MENU_TRANSLATE("Backtrack", "Backtrack"), &cfg.LegitBot.backtrack);
			ImGui::Checkbox(MENU_TRANSLATE("Fogo amigo", "Friendly fire"), &cfg.LegitBot.friendlyFire);
			ImGui::Checkbox(MENU_TRANSLATE("Silent", "Silent"), &cfg.LegitBot.silent);
		}

		ImGui::Separator();

		ImGui::Checkbox(MENU_TRANSLATE("TriggerBot", "TriggetBot"), &cfg.LegitBot.triggerBot);

		if (cfg.LegitBot.triggerBot)
		{
			ImGui::Text(MENU_TRANSLATE("Trigger delay [s]", "Trigger delay [s]"));
			ImGui::SliderFloat(xorstr("##dummyaimbot3"), &cfg.LegitBot.triggerDelay, 0, 0.3f);
		}
	}
}
