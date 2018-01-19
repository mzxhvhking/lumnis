#pragma once

void MenuV2::DrawMiscTab()
{
	ImGui::Text(MENU_TRANSLATE("Cuidado", "Caution"));
	ImGui::Separator();

	//ImGui::Checkbox(xorstr("Bypass sv_cheats [Nao use cheats no console]"), &cfg.Misc.bypassSvCheats);
	ImGui::Checkbox(MENU_TRANSLATE("Untrusted", "Untrusted"), &cfg.Rage.AntiAim.untrusted);
	ImGui::Checkbox(MENU_TRANSLATE("Airstuck (Key: C)", "Airstuck (Key: C)"), &cfg.Misc.airStuck);

	if (!cfg.Rage.AntiAim.untrusted)
		cfg.Rage.teleportF9 = false;

	ImGui::Text(xorstr("Bunnyhop"));
	ImGui::Separator();

	ImGui::Checkbox(xorstr("Bunnyhop"), &cfg.Misc.bunnyhop);
	ImGui::SameLine();
	ImGui::Checkbox(xorstr("Spoof Autohop"), &cfg.Misc.spoofAutoBunnyhop);
	ImGui::SameLine();
	ImGui::Checkbox(MENU_TRANSLATE("Parar na parede", "Stop at wall"), &cfg.Misc.buunyhopStopAtWall);
	ImGui::SameLine();
	ImGui::Checkbox(xorstr("Auto strafe"), &cfg.Misc.autoStrafe);
	ImGui::SameLine();
	ImGui::Checkbox(xorstr("Bunny auto duck"), &cfg.Misc.bunnyAutoDuck);
	ImGui::Checkbox(MENU_TRANSLATE("aceitar partida Automaticamente", "Auto-Accept"), &cfg.Misc.autoaccept);


	if (cfg.Misc.autoStrafe)
	{
		ImGui::SameLine();
		ImGui::Checkbox(xorstr("Fast"), &cfg.Misc.fastAutoStrafe);
		ImGui::SliderFloat(xorstr("Retrack"), &cfg.Misc.retrackSpeed, 0.5f, 10.0f);
		ImGui::SliderFloat(xorstr("Divisor"), &cfg.Misc.speedDivisor, 0.5f, 10.0f);
		ImGui::Checkbox(xorstr("Box CStrafe"), &cfg.Misc.boxCircleStrafe);
	}

	ImGui::Text(xorstr("Clan tag"));
	ImGui::Separator();

	static vector<string> anims;
	static char animsStr[1024];

	if (anims.size() == 0)
	{
		anims.push_back(xorstr("None"));
		anims.push_back(xorstr("Matrix 0-1"));
		anims.push_back(xorstr("getze.us"));
		anims.push_back(xorstr("Lumin"));
		anims.push_back(xorstr("skeet.cc"));
		anims.push_back(xorstr("Valve"));
		anims.push_back(xorstr("Teste"));
		anims.push_back(xorstr("Luminus"));
		anims.push_back(xorstr("GB HvH"));
		anims.push_back(xorstr("GameSense"));

		VectorToArray(anims, animsStr);
	}

	ImGui::Text(MENU_TRANSLATE(u8"Animação", "Animation"));
	ImGui::Combo(xorstr("##dummymisc0"), &cfg.Misc.clanTagAnimation, animsStr);

	ImGui::Separator();

	ImGui::Checkbox(MENU_TRANSLATE("Travar os outros", "Auto block"), &cfg.Misc.autoBlock);

	ImGui::Separator();
		
	ImGui::Checkbox(MENU_TRANSLATE(u8"Ladrão de nomes", "Name stealer"), &cfg.Misc.nameStealer);

	ImGui::Separator();

	static char buf[512];
	static bool colorize;

	ImGui::InputText(xorstr("##dummymisc1"), buf, 512);

	bool changeName = ImGui::Button(MENU_TRANSLATE("Mudar nome", "Change name"));

	ImGui::SameLine();
	//ImGui::Checkbox(xorstr("Vermelho"), &colorize);

	bool changeTag = ImGui::Button(MENU_TRANSLATE("Mudar tag", "Change tag"));

	if (changeName || changeTag)
	{
		string buf2(buf);

		replace(buf2, string("\\n"), string("\n"));
		replace(buf2, string("\\r"), string("\r"));

		if (changeTag)
		{
			SetClanTag(buf2.c_str());
		}
		else if (changeName)
		{
			if (colorize)
			{				
				SetName((" \x01\x0B\x01""\x02""" + buf2 + "\x01").c_str());
			}
			else
			{
				SetName(buf2.c_str());
			}
		}
	}

	ImGui::Separator();

	ImGui::Text(xorstr("Overlay"));
	ImGui::Checkbox(MENU_TRANSLATE("Espectadores", "Spectators"), &cfg.Overlay.spectators);

	/*ImGui::Text(xorstr("Mudar Convar [untrusted]"));
	ImGui::Separator();

	if (cfg.Rage.AntiAim.untrusted)
	{
		static char buf[512];

		ImGui::InputText(xorstr("Convar: "), buf, 512);

		if (ImGui::Button(xorstr("Ativar")))
		{
			ConVar *convar = I::pCVar->FindVar(buf);

			if (convar)
			{
				convar->SetValue(1);
			}
		}
		if (ImGui::Button(xorstr("Desativar")))
		{
			ConVar *convar = I::pCVar->FindVar(buf);

			if (convar)
			{
				convar->SetValue(0);
			}
		}
	}*/
}
