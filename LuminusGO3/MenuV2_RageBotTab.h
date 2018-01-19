#pragma once

#include "AntiAimV2.h"

void MenuV2::DrawRagebotTab()
{
	static vector<string> rageTabs;

	if (rageTabs.size() == 0)
	{
		rageTabs.push_back(xorstr("Aimbot"));
		rageTabs.push_back(xorstr("Anti Aim"));
		rageTabs.push_back(xorstr("Auto Fire"));
		rageTabs.push_back(xorstr("Resolver"));
		rageTabs.push_back(xorstr("Fake Lag"));
		rageTabs.push_back(xorstr("Advanced"));
	}

	static int selectedTabRage = 0;

	ImGui::TabLabels(rageTabs, selectedTabRage, true);
	{
		switch (selectedTabRage)
		{
		case 0: DrawAimbotTab(); break;
		case 1: DrawAntiAimTab(); break;
		case 2: DrawAutoFireTab(); break;
		case 3: DrawResolverTab(); break;
		case 4: DrawFakeLagTab(); break;
		case 5: DrawAdvancedRageBotTab(); break;
		}
	}
}

void MenuV2::DrawAntiAimTab()
{
	ImGui::Checkbox(MENU_TRANSLATE("Ativar anti-aim", "Enable anti-aim"), &cfg.Rage.AntiAim.enabled);

	ImGui::Separator();

	if (cfg.Rage.AntiAim.enabled)
	{
		ImGui::Columns(3);

		static vector<string> antiAims;
		static char antiAimsStr[1024];

		if (antiAims.size() == 0)
		{
			antiAims.push_back(xorstr("None"));
			antiAims.push_back(xorstr("Legit"));
			antiAims.push_back(xorstr("Backward"));
			antiAims.push_back(xorstr("Spin"));
			antiAims.push_back(xorstr("LBY Inverse"));
			antiAims.push_back(xorstr("Auto"));
			antiAims.push_back(xorstr("Backward at targets"));
			antiAims.push_back(xorstr("LBY Spin"));
			antiAims.push_back(xorstr("Invade AA"));
			antiAims.push_back(xorstr("Synchronize AA"));

			VectorToArray(antiAims, antiAimsStr);
		}

		static vector<string> antiAimsLBY;
		static char antiAimsLBYStr[1024];

		if (antiAimsLBY.size() == 0)
		{
			antiAimsLBY.push_back(xorstr("None"));
			antiAimsLBY.push_back(xorstr("Inverse"));
			antiAimsLBY.push_back(xorstr("Auto Out"));
			antiAimsLBY.push_back(xorstr("Auto In"));
			antiAimsLBY.push_back(xorstr("Air"));
			antiAimsLBY.push_back(xorstr("Custom"));
			antiAimsLBY.push_back(xorstr("Air Inverse"));

			VectorToArray(antiAimsLBY, antiAimsLBYStr);
		}

		static vector<string> antiAimsPitch;
		static char antiAimsPitchStr[1024];

		if (antiAimsPitch.size() == 0)
		{
			antiAimsPitch.push_back(xorstr("None"));
			antiAimsPitch.push_back(xorstr("Legit"));
			antiAimsPitch.push_back(xorstr("Down"));
			antiAimsPitch.push_back(xorstr("Up"));
			antiAimsPitch.push_back(xorstr("Fake Down [UT]"));
			antiAimsPitch.push_back(xorstr("Fake Up [UT]"));
			antiAimsPitch.push_back(xorstr("Fake Zero [UT]"));
			antiAimsPitch.push_back(xorstr("Fake Up Cycle [UT]"));
			antiAimsPitch.push_back(xorstr("Custom"));

			VectorToArray(antiAimsPitch, antiAimsPitchStr);
		}

		ImGui::Combo(xorstr("Pitch"), &cfg.Rage.AntiAim.pitchStyle, antiAimsPitchStr);

		if (cfg.Rage.AntiAim.pitchStyle == AntiAimV2::X_CUSTOM)
		{
			ImGui::Text(MENU_TRANSLATE("Pitch personalizado", "Custom pitch"));
			ImGui::InputFloat(xorstr("##aadummycustompitch"), &cfg.Rage.AntiAim.customPitch);
		}

		ImGui::Combo(MENU_TRANSLATE("Real parado", "Real standing"), &cfg.Rage.AntiAim.realStyle, antiAimsStr);
		ImGui::Combo(MENU_TRANSLATE("Real movimentando", "Real moving"), &cfg.Rage.AntiAim.movingRealStyle, antiAimsStr);
		ImGui::Combo(MENU_TRANSLATE("Real agaixando", "Real ducking"), &cfg.Rage.AntiAim.duckingRealStyle, antiAimsStr);
		ImGui::Combo(MENU_TRANSLATE("Anti resolver", "Anti resolver"), &cfg.Rage.AntiAim.lowerBodyStyle, antiAimsLBYStr);
		ImGui::Combo(xorstr("Fake"), &cfg.Rage.AntiAim.fakeStyle, antiAimsStr);

		if (cfg.Rage.AntiAim.lowerBodyStyle == AntiAimV2::LBY_CUSTOM)
		{
			ImGui::Text(xorstr("Anti Resolver Offset"));
			ImGui::SliderFloat(xorstr("##aadummyfakelbyoffset"), &cfg.Rage.AntiAim.fakelLbyOffset, -180.0f, 180.0f);
		}

		ImGui::Text(xorstr("Real Offset"));
		ImGui::SliderFloat(xorstr("##aadummyrealoffset"), &cfg.Rage.AntiAim.realYawOffset, -180.0f, 180.0f);
		ImGui::Text(xorstr("Fake Offset"));
		ImGui::SliderFloat(xorstr("##aadummyfakeoffset"), &cfg.Rage.AntiAim.fakeYawOffset, -180.0f, 180.0f);

		ImGui::Text(MENU_TRANSLATE("Real LJitter parado", "Real LJitter standing"));
		ImGui::SliderFloat(xorstr("##aadummyjitter"), &cfg.Rage.AntiAim.lbyJitter, 0.0f, 90.0f);
		ImGui::Text(MENU_TRANSLATE("Real LJitter movimentando", "Real LJitter moving"));
		ImGui::SliderFloat(xorstr("##aadummyjittermoving"), &cfg.Rage.AntiAim.lbyJitterMoving, 0.0f, 90.0f);
		ImGui::SameLine();
		ImGui::Checkbox(MENU_TRANSLATE("Devagar", "Slow"), &cfg.Rage.AntiAim.lbyJitterOnlySlow);
		ImGui::Text(MENU_TRANSLATE("Slow motion", "Slow motion"));
		ImGui::SliderInt(xorstr("##aadummyslowmotionticks"), &cfg.Rage.AntiAim.slowMotionTicks, 0, 15);

		ImGui::NextColumn();

		ImGui::Checkbox(xorstr("Static base"), &cfg.Rage.AntiAim.staticAA);
		ImGui::Checkbox(xorstr("Lowerbody base"), &cfg.Rage.AntiAim.lowerBody);
		ImGui::Checkbox(MENU_TRANSLATE("Virar para alvos", "At targets"), &cfg.Rage.AntiAim.atTargets);

		ImGui::Checkbox(xorstr("Real TJitter"), &cfg.Rage.AntiAim.realJitter);
		ImGui::Checkbox(xorstr("Fake TJitter"), &cfg.Rage.AntiAim.fakeJitter);

		ImGui::NextColumn();

		ImGui::Checkbox(MENU_TRANSLATE("Destivar na faca", "Disable with knife"), &cfg.Rage.AntiAim.removeOnKnife);

		ImGui::Checkbox(MENU_TRANSLATE("Mostrar AA real", "Show real AA"), &cfg.Rage.AntiAim.viewAntiAim);
		ImGui::Checkbox(MENU_TRANSLATE("Mostrar AA fake", "Show fake AA"), &cfg.Rage.AntiAim.viewAntiAimFake);
		ImGui::Checkbox(MENU_TRANSLATE("Mostrar LBY [Ghost]", "Show LBY [Ghost]"), &cfg.Rage.AntiAim.viewLowerBodyYawTarget);

		ImGui::Checkbox(MENU_TRANSLATE("Terceira pessoa [Bind: MOUSE3]", "Third person [Bind: MOUSE3]"), &cfg.Misc.thirdPerson);
	}
}

void MenuV2::DrawAutoFireTab()
{
	ImGui::Checkbox(MENU_TRANSLATE("Atirar automaticamente", "Auto fire"), &cfg.Rage.AutoFire.enabled);

	//if (cfg.Rage.AutoFire.enabled)
	{
		ImGui::Columns(3);

		/*vector<string> hitscanTypes;
		char hitscanTypesStr[1024];
		memset(hitscanTypesStr, 0, 1024);

		hitscanTypes.push_back(MENU_TRANSLATE("Desativado", "Off"));
		hitscanTypes.push_back(MENU_TRANSLATE(u8"Padrão", "Default"));
		hitscanTypes.push_back(MENU_TRANSLATE("Maior dano", "High damage"));
		hitscanTypes.push_back(MENU_TRANSLATE("Priorizar caminho livre", "Priorize free path"));
		VectorToArray(hitscanTypes, hitscanTypesStr);*/

		ImGui::Checkbox(xorstr("Auto wall"), &cfg.Rage.AutoWall.enabled);

		ImGui::Text(MENU_TRANSLATE(u8"Dano minímo", "Min damage"));
		ImGui::SliderFloat(xorstr("##dummyragebot0"), &cfg.Rage.AutoWall.minDamage, 1.0f, 120.f, "%.0f");

		ImGui::Text(MENU_TRANSLATE("Hitchance", "Hitchance"));
		ImGui::SliderFloat(xorstr("##dummyautofire0"), &cfg.Rage.AutoFire.hitchance, 0.0f, 100.0f, "%.0f");

		//ImGui::SliderInt(xorstr("Hitchance max seed"), &cfg.Rage.AutoFire.hitchanceMaxSeed, 0, 256);
		cfg.Rage.AutoFire.hitchanceMaxSeed = 256;

		ImGui::SliderInt("Body-Aim After X Shots", &cfg.Rage.AutoFire.BaimAfterShots, 0, 10);

		/*ImGui::Checkbox(xorstr("Spread Limit"), &cfg.Rage.AutoFire.useMaxSpread);
		if (cfg.Rage.AutoFire.useMaxSpread)
		{
		//ImGui::SameLine();
		ImGui::SliderFloat(xorstr("spred max"), &cfg.Rage.AutoFire.maxSpread, 0.0f, 100.0f);
		}*/

		/*ImGui::Checkbox(MENU_TRANSLATE(u8"Velocidade máxima", "Max speed"), &cfg.Rage.AutoFire.useMaxSpeed);
		if (cfg.Rage.AutoFire.useMaxSpeed)
		{
		//ImGui::SameLine();
		ImGui::SliderFloat(xorstr("vel max"), &cfg.Rage.AutoFire.maxSpeed, 0.0f, 200.0f);
		}*/

		ImGui::NextColumn();

		//ImGui::Text(MENU_TRANSLATE("Hitscan", "Hitscan"));
		//ImGui::Combo(xorstr("##dummyaimbot2"), &cfg.Rage.AutoFire.hitscan, hitscanTypesStr);

		ImGui::Checkbox(MENU_TRANSLATE(u8"Adaptar ao FPS", "FPS adaptive"), &cfg.Rage.AutoWall.fast);
		ImGui::Checkbox(MENU_TRANSLATE(u8"Ignorar cabeça", "Ignore head"), &cfg.Rage.ignoreHead);
		//ImGui::SameLine();
		ImGui::Checkbox(MENU_TRANSLATE(u8"Ignorar braços e pernas", "Ignore arms & legs"), &cfg.Rage.ignoreArm);
		ImGui::Checkbox(MENU_TRANSLATE("Apenas HS", "HS only"), &cfg.Rage.AutoFire.onlyHS);
		ImGui::Checkbox(MENU_TRANSLATE("Apenas HS se resolvido", "HS only if resolved"), &cfg.Rage.AutoFire.onlyHsIfResolved);

		//ImGui::SameLine();
		ImGui::Checkbox(MENU_TRANSLATE("Apenas HS se movimentando", "HS only at moving targets"), &cfg.Rage.AutoFire.onlyHsMoving);
		ImGui::Checkbox(xorstr("Smart Aim"), &cfg.Rage.AutoFire.smartAim);
		//ImGui::SameLine();
		ImGui::Checkbox(MENU_TRANSLATE("Preferir baim", "Prefer baim"), &cfg.Rage.AutoFire.preferBody);
		ImGui::Checkbox(MENU_TRANSLATE("Baim caso baixa hitchance", "Baim on low hitchance"), &cfg.Rage.AutoFire.baimOnLowHitchance);
		ImGui::Checkbox(MENU_TRANSLATE("Preferir baim", "Auto Baim"), &cfg.Rage.AutoFire.AutoBaim);

		static vector<string> multibox;
		static char multiboxStr[1024];

		if (multibox.size() == 0)
		{
			multibox.push_back(xorstr("None"));
			multibox.push_back(xorstr("Head - Neck"));
			multibox.push_back(xorstr("Head - Chest"));
			multibox.push_back(xorstr("Head - Neck - Chest"));

			VectorToArray(multibox, multiboxStr);
		}

		ImGui::Combo(xorstr("Multibox"), &cfg.Rage.AutoFire.multiBox, multiboxStr);

		ImGui::NextColumn();

		ImGui::Checkbox(MENU_TRANSLATE(u8"Boost de acurácia", "Accuracy boost"), &cfg.Rage.AutoFire.accuracyBoost);
		ImGui::Checkbox(MENU_TRANSLATE("Atrasar tiro", "Delay shoot"), &cfg.Rage.AutoFire.delayShoot);
		ImGui::Checkbox(xorstr("pSilent"), &cfg.Rage.pSilent);
		ImGui::Checkbox(xorstr("Anti pSilent"), &cfg.Rage.AutoFire.antiSilent);

		if (cfg.Rage.AutoFire.antiSilent)
			cfg.Rage.pSilent = false;

		ImGui::Checkbox(xorstr("Auto Revolver"), &cfg.Rage.AutoFire.autoRevolver);
		ImGui::Checkbox(MENU_TRANSLATE("Compensar recuo", "No recoil"), &cfg.Rage.noRecoil);
		//ImGui::Checkbox(xorstr("Apenas no chao"), &cfg.Rage.AutoFire.inGround);
		cfg.Rage.AutoFire.inGround = false;
		ImGui::Checkbox(xorstr("Auto scope"), &cfg.Rage.AutoFire.autoScope);
		ImGui::Checkbox(MENU_TRANSLATE("Parar automaticamente", "Auto stop"), &cfg.Rage.AutoFire.autoStop);
		ImGui::Checkbox(MENU_TRANSLATE("Parar Crouch", "Auto Crouch"), &cfg.Rage.AutoFire.autocrouch);
	}
}

void MenuV2::DrawAdvancedRageBotTab()
{
	ImGui::Text(MENU_TRANSLATE("PS-point scale, MP-multi point, D-desativar", "PS-point scale, MP-multi point, D-disable"));

	ImGui::Columns(4);

	for (int i = 0; i < HITBOX_COUNT; i++)
	{
		int hitbox = i;

		ImGui::Text(GetHitboxName(hitbox).c_str());
		ImGui::NextColumn();

		ImGui::Text(MENU_TRANSLATE("PS", "PS"));
		ImGui::SameLine();
		ImGui::SliderFloat(string(string(xorstr("##dummyragebotadvancedscale")) + GetHitboxName(hitbox)).c_str(), &cfg.Rage.Hitscan.scale[hitbox], 0.0f, 1.0f, "%.1f");
		ImGui::NextColumn();

		ImGui::Text(MENU_TRANSLATE("MP", "MP"));
		ImGui::SameLine();
		ImGui::SliderInt(string(string(xorstr("##dummyragebotadvancedpoints")) + GetHitboxName(hitbox)).c_str(), &cfg.Rage.Hitscan.points[hitbox], 0, 8);
		ImGui::NextColumn();

		/*ImGui::Text(MENU_TRANSLATE("I", "I"));
		ImGui::SameLine();
		ImGui::SliderInt(string(string(xorstr("##dummyragebotadvancedpriority")) + GetHitboxName(hitbox)).c_str(), &cfg.Rage.Hitscan.priority[hitbox], 0, HITBOX_COUNT - 1);
		ImGui::NextColumn();*/

		ImGui::Text(MENU_TRANSLATE("D", "D"));
		ImGui::SameLine();
		ImGui::Checkbox(string(string(xorstr("##dummyragebotadvancedignore")) + GetHitboxName(hitbox)).c_str(), (bool*)&cfg.Rage.Hitscan.ignore[hitbox]);
		ImGui::NextColumn();
	}

	ImGui::NextColumn();

	if (ImGui::Button(xorstr("Reset PS")))
	{
		for (int i = 0; i < HITBOX_COUNT; i++)
		{
			cfg.Rage.Hitscan.scale[i] = 0.5f;
		}
	}

	ImGui::NextColumn();

	if (ImGui::Button(xorstr("Min MP")))
	{
		for (int i = 0; i < HITBOX_COUNT; i++)
			cfg.Rage.Hitscan.points[i] = 0;
	}

	if (ImGui::Button(xorstr("Medium MP")))
	{
		for (int i = 0; i < HITBOX_COUNT; i++)
			cfg.Rage.Hitscan.points[i] = 3;
	}

	if (ImGui::Button(xorstr("Max MP")))
	{
		for (int i = 0; i < HITBOX_COUNT; i++)
			cfg.Rage.Hitscan.points[i] = 8;
	}

	ImGui::NextColumn();

	/*if (ImGui::Button(xorstr("Reset I")))
	{
	for (int i = 0; i < HITBOX_COUNT; i++)
	cfg.Rage.Hitscan.priority[i] = i;
	}

	ImGui::NextColumn();*/

	if (ImGui::Button(xorstr("Reset D")))
	{
		for (int i = 0; i < HITBOX_COUNT; i++)
			cfg.Rage.Hitscan.ignore[i] = 0;
	}
}

void MenuV2::DrawResolverTab()
{
	ImGui::Text(xorstr("Resolver"));
	ImGui::Checkbox(xorstr("Anti anti-aim"), &cfg.Rage.Resolver.enabled);

	if (cfg.Rage.Resolver.enabled)
	{
		ImGui::SliderInt(xorstr("Reset time [ms]"), &cfg.Rage.Resolver.resetTime, 500, 5000);
		ImGui::Checkbox(xorstr("Force to LBY"), &cfg.Rage.Resolver.lispCorrect);
		ImGui::SameLine();
		ImGui::Checkbox(xorstr("Delta fix"), &cfg.Rage.Resolver.deltaCorrect);
		ImGui::Checkbox(xorstr("Bruteforce yaw"), &cfg.Rage.Resolver.forceYaw);
		ImGui::SameLine();
		ImGui::Checkbox(xorstr("Bruteforce pitch"), &cfg.Rage.Resolver.fixPitch);
		ImGui::SliderInt(xorstr("Tiros ate bruteforce"), &cfg.Rage.Resolver.minBruteforceBullets, 0, 5);
		ImGui::Checkbox(xorstr("Resolve legits"), &cfg.Rage.Resolver.resolveLegits);
		cfg.Rage.Resolver.minBruteforceBullets = 0;
		ImGui::SliderInt(xorstr("Bruteforce After X Shots"), &cfg.Rage.Resolver.BruteForceShots, 0, 20);
		ImGui::Checkbox(MENU_TRANSLATE("Modo nospread", "Nospread mode"), &cfg.Rage.Resolver.noSpreadMode);
		ImGui::Checkbox(xorstr("Force jitter"), &cfg.Rage.Resolver.forceJitter);
		ImGui::Checkbox(xorstr("No interpolation"), &cfg.Rage.Resolver.noInterpolation);
		ImGui::Separator();
		ImGui::Text(xorstr("Backtrack"));

		ImGui::Checkbox(MENU_TRANSLATE("Mover no tempo", "Backtrack"), &cfg.Rage.Resolver.backTrack);
		if (cfg.Rage.Resolver.backTrack)
		{
			const char *opt_LagCompType[] = { "Only best records", "Best and newest", "All records (fps warning)", "Only on shot(debug)", "Oldest(debug)" };
			ImGui::Checkbox(MENU_TRANSLATE("Exibir cache", "Show cache"), &cfg.Rage.Resolver.drawRecord);
			ImGui::Combo("Type##Rage", &cfg.Rage.Resolver.backtrackingtype, opt_LagCompType, 5);
			//ImGui::SliderInt(xorstr("Min Offset"), &cfg.Rage.Resolver.backTrackMinOffset, 0, Backtrack::pRecordManager->GetMaxRecords());
			//ImGui::SliderInt(xorstr("Offset"), &cfg.Rage.Resolver.backTrackOffset, 0, Backtrack::pRecordManager->GetMaxRecords());

			/*if (TICKS_TO_TIME(cfg.Rage.Resolver.backTrackMinOffset) > 0.2f && cfg.Rage.AntiAim.untrusted)
			ImGui::Checkbox(xorstr("Ping exploit"), &cfg.Rage.Resolver.pingExploit);
			else
			cfg.Rage.Resolver.pingExploit = false;*/

			if (cfg.Rage.Resolver.backTrackOffset < cfg.Rage.Resolver.backTrackMinOffset)
				cfg.Rage.Resolver.backTrackOffset = cfg.Rage.Resolver.backTrackMinOffset;
		}
		else
		{
			cfg.Rage.Resolver.drawRecord = false;
		}

		ImGui::Separator();
		ImGui::Checkbox(MENU_TRANSLATE("Atirar quando resolvido", "Fire only resolved"), &cfg.Rage.Resolver.fireOnlyResolved);
		ImGui::Checkbox(MENU_TRANSLATE("Baim unresolved", "Baim unresolved"), &cfg.Rage.Resolver.baimUnresolved);
		ImGui::SameLine();
		ImGui::Checkbox(xorstr("Inverse unresolved"), &cfg.Rage.Resolver.inverseUnresolved);

		ImGui::Separator();
		ImGui::Text(xorstr("Prediction"));
		ImGui::Checkbox(MENU_TRANSLATE("Extrapolar", "Extrapolate"), &cfg.Rage.Resolver.extrapolate);
	}

	ImGui::Separator();

	ImGui::Checkbox(xorstr("Local player prediction"), &cfg.Rage.Resolver.prediction);
}

void MenuV2::DrawFakeLagTab()
{
	ImGui::Text(xorstr("Fake lag"));
	ImGui::Checkbox(xorstr("FakeLag"), &cfg.Rage.FakeLag.enabled);

	if (cfg.Rage.FakeLag.enabled)
	{
		ImGui::Checkbox(MENU_TRANSLATE("Adaptativo", "Adaptive"), &cfg.Rage.FakeLag.adaptive);

		if (cfg.Rage.FakeLag.adaptive)
		{
			ImGui::SliderInt(xorstr("Min"), &cfg.Rage.FakeLag.min, 1, 14);
			ImGui::SliderInt(xorstr("Max"), &cfg.Rage.FakeLag.max, 1, 14);
			ImGui::Checkbox(xorstr("Random"), &cfg.Rage.FakeLag.random);

			if (cfg.Rage.FakeLag.min > cfg.Rage.FakeLag.max)
				cfg.Rage.FakeLag.max = cfg.Rage.FakeLag.min;

			if (cfg.Rage.FakeLag.max < cfg.Rage.FakeLag.min)
				cfg.Rage.FakeLag.min = cfg.Rage.FakeLag.max;

			cfg.Rage.FakeLag.air = 0;
		}
		else
		{
			ImGui::SliderInt(xorstr("Ticks"), &cfg.Rage.FakeLag.min, 1, 14);
			ImGui::SliderInt(MENU_TRANSLATE("No ar", "On air"), &cfg.Rage.FakeLag.air, 0, 14);

			cfg.Rage.FakeLag.max = cfg.Rage.FakeLag.min;
		}

		ImGui::SliderInt(xorstr("Edge"), &cfg.Rage.FakeLag.edge, 0, 14);
	}
}

