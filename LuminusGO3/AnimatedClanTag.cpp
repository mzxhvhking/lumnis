#include "SDK.h"
#include "Global.h"
#include "Configs.h"
#include "AnimatedClanTag.h"

AnimatedClanTag *animatedClanTag = new AnimatedClanTag();

void AnimatedClanTag::Tick()
{
	char tag[64];
	int i = 0;
	float serverTime = (float)I::pEngineClient->GetServerTick() * (I::pGlobals->interval_per_tick * 2);

	std::vector<std::string> anim;

	switch (cfg.Misc.clanTagAnimation)
	{
	case 1:
		i = (int)(serverTime) % 2;

		if (i == 0 || i == 1)
		{
			for (i = 0; i < 4; i++)
				tag[i] = Math::Random('0', '1');

			tag[i] = '\0';

			SetClanTag(tag);
		}
		break;

	case 2:
		anim.push_back(xorstr("getze.us      "));
		anim.push_back(xorstr(" getze.us     "));
		anim.push_back(xorstr("  getze.us    "));
		anim.push_back(xorstr("   getze.us   "));
		anim.push_back(xorstr("    getze.us  "));
		anim.push_back(xorstr("     getze.us "));
		anim.push_back(xorstr("      getze.us"));
		anim.push_back(xorstr("     getze.us "));
		anim.push_back(xorstr("    getze.us  "));
		anim.push_back(xorstr("   getze.us   "));
		anim.push_back(xorstr("  getze.us    "));
		anim.push_back(xorstr(" getze.us     "));
		anim.push_back(xorstr("getze.us      "));

		break;

	case 3:
		anim.push_back(xorstr("Lumin\r"));
		anim.push_back(xorstr("L min\r"));
		anim.push_back(xorstr("Lu in\r"));
		anim.push_back(xorstr("Lum n\r"));
		anim.push_back(xorstr("Lumi \r"));
		anim.push_back(xorstr("Lumin\r"));
		anim.push_back(xorstr("Lum n\r"));
		anim.push_back(xorstr("Lu in\r"));
		anim.push_back(xorstr("L min\r"));
		anim.push_back(xorstr(" umin\r"));

		break;

	case 4:
		anim.push_back(xorstr("              "));
		anim.push_back(xorstr("c             "));
		anim.push_back(xorstr("cc            "));
		anim.push_back(xorstr(".cc           "));
		anim.push_back(xorstr("t.cc          "));
		anim.push_back(xorstr("et.cc         "));
		anim.push_back(xorstr("eet.cc        "));
		anim.push_back(xorstr("keet.cc       "));
		anim.push_back(xorstr("skeet.cc      "));
		anim.push_back(xorstr(" skeet.cc     "));
		anim.push_back(xorstr("  skeet.cc    "));
		anim.push_back(xorstr("   skeet.cc   "));
		anim.push_back(xorstr("    skeet.cc  "));
		anim.push_back(xorstr("     skeet.cc "));
		anim.push_back(xorstr("      skeet.cc"));
		anim.push_back(xorstr("       skeet.c"));
		anim.push_back(xorstr("        skeet."));
		anim.push_back(xorstr("         skeet"));
		anim.push_back(xorstr("          skee"));
		anim.push_back(xorstr("           ske"));
		anim.push_back(xorstr("            sk"));
		anim.push_back(xorstr("             s"));

		break;

	case 5:
		anim.push_back(xorstr("[VALVE]"));
		break;

	case 6:
		anim.push_back(xorstr("[testing]"));
		break;

	case 7:
		anim.push_back(xorstr("-  Luminus  +"));
		anim.push_back(xorstr("+  Luminus  -"));
		break;	

	case 8:
		/*anim.push_back(xorstr( "/  GB HvH  /" ));
		anim.push_back(xorstr( "- GB HvH   -" ));
		anim.push_back(xorstr("\\GB HvH    \\"));
		anim.push_back(xorstr( "| GB HvH   |" ));
		anim.push_back(xorstr( "-  GB HvH  -" ));
		anim.push_back(xorstr( "/   GB HvH /" ));
		anim.push_back(xorstr( "-    GB HvH-" ));
		anim.push_back(xorstr("\\   GB HvH \\"));
		anim.push_back(xorstr( "|  GB HvH   |" ));*/

		/*
		anim.push_back(xorstr( "/  GB HvH  /" ));
		anim.push_back(xorstr( "-  GB HvH  -" ));
		anim.push_back(xorstr("\\  GB HvH  \\"));
		anim.push_back(xorstr( "|  GB HvH  |" ));
		anim.push_back(xorstr( "-  GB HvH  -" ));
		anim.push_back(xorstr( "/  GB HvH  /" ));
		anim.push_back(xorstr( "-  GB HvH  -" ));
		anim.push_back(xorstr("\\  GB HvH  \\"));
		anim.push_back(xorstr( "|  GB HvH  |" ));*/

		anim.push_back(xorstr("Gira Brasil HvH"));
		anim.push_back(xorstr(" Gira Brasil Hv"));
		anim.push_back(xorstr("  Gira Brasil H"));
		anim.push_back(xorstr("   Gira Brasil "));
		anim.push_back(xorstr("    Gira Brasil"));
		anim.push_back(xorstr("     Gira Brasi"));
		anim.push_back(xorstr("      Gira Bras"));
		anim.push_back(xorstr("       Gira Bra"));
		anim.push_back(xorstr("        Gira Br"));
		anim.push_back(xorstr("         Gira B"));
		anim.push_back(xorstr("          Gira "));
		anim.push_back(xorstr("           Gira"));
		anim.push_back(xorstr("            Gir"));
		anim.push_back(xorstr("             Gi"));
		anim.push_back(xorstr("              G"));
		anim.push_back(xorstr("               "));
		anim.push_back(xorstr("H              "));
		anim.push_back(xorstr("vH             "));
		anim.push_back(xorstr("HvH            "));
		anim.push_back(xorstr(" HvH           "));
		anim.push_back(xorstr("l HvH          "));
		anim.push_back(xorstr("il HvH         "));
		anim.push_back(xorstr("sil HvH        "));
		anim.push_back(xorstr("asil HvH       "));
		anim.push_back(xorstr("rasil HvH      "));
		anim.push_back(xorstr("Brasil HvH     "));
		anim.push_back(xorstr(" Brasil HvH    "));
		anim.push_back(xorstr("a Brasil HvH   "));
		anim.push_back(xorstr("ra Brasil HvH  "));
		anim.push_back(xorstr("ira Brasil HvH "));
		anim.push_back(xorstr("Gira Brasil HvH"));
		break;

	case 9:
		anim.push_back(xorstr("gamesense    "));
		anim.push_back(xorstr(" gamesense   "));
		anim.push_back(xorstr("  gamesense  "));
		anim.push_back(xorstr("   gamesense "));
		anim.push_back(xorstr("    gamesense"));
		anim.push_back(xorstr("     gamesens"));
		anim.push_back(xorstr("      gamesen"));
		anim.push_back(xorstr("       gamese"));
		anim.push_back(xorstr("        games"));
		anim.push_back(xorstr("         game"));
		anim.push_back(xorstr("          gam"));
		anim.push_back(xorstr("           ga"));
		anim.push_back(xorstr("            g"));
		anim.push_back(xorstr("             "));
		anim.push_back(xorstr("e            "));
		anim.push_back(xorstr("se           "));
		anim.push_back(xorstr("nse          "));
		anim.push_back(xorstr("ense         "));
		anim.push_back(xorstr("sense        "));
		anim.push_back(xorstr("esense       "));
		anim.push_back(xorstr("mesense      "));
		anim.push_back(xorstr("amesense     "));
		anim.push_back(xorstr("gamesense    "));		
		break;
	}

	static bool reset = 0;

	if (cfg.Misc.clanTagAnimation != 0)
	{
		if (cfg.Misc.clanTagAnimation != 1)
		{
			i = (int)(serverTime) % (int)anim.size();
			SetClanTag(anim[i].c_str());
			reset = true;
		}
	}
	else
	{
		if (reset)
		{
			SetClanTag("");
			reset = false;
		}
	}
}

/*int i = (int)(serverTime) % 21;
/ *
|
/
-
|
/
-
* /
switch (i)
{
case 0:SetClanDGDruedTagName(" \\ "); break;
case 1:SetClanDGDruedTagName(" | "); break;
case 2: SetClanDGDruedTagName(" / "); break;
case 3: SetClanDGDruedTagName(" - "); break;
case 5: SetClanDGDruedTagName(" Z "); break;
case 6: SetClanDGDruedTagName(" Z\\ "); break;
case 7: SetClanDGDruedTagName(" Z| "); break;
case 8: SetClanDGDruedTagName(" Z/ "); break;
case 9: SetClanDGDruedTagName(" Z- "); break;
case 10: SetClanDGDruedTagName(" Ze "); break;
case 11: SetClanDGDruedTagName(" Ze\\ "); break;
case 12:SetClanDGDruedTagName(" Ze| "); break;
case 13:SetClanDGDruedTagName(" Ze/ "); break;
case 14:SetClanDGDruedTagName(" Ze- "); break;
case 15:SetClanDGDruedTagName(" Zeu "); break;
case 16:SetClanDGDruedTagName(" Zeu\\ "); break;
case 17:SetClanDGDruedTagName(" Zeu| "); break;
case 18:SetClanDGDruedTagName(" Zeu/ "); break;
case 19:SetClanDGDruedTagName(" Zeu- "); break;
case 20:SetClanDGDruedTagName(" Zeus "); break;
}
}
}
*/