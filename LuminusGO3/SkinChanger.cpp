#include "SDK.h"
#include "Global.h"
#include "Configs.h"
#include "SkinChanger.h"

#define SEQUENCE_DEFAULT_DRAW 0
#define SEQUENCE_DEFAULT_IDLE1 1
#define SEQUENCE_DEFAULT_IDLE2 2
#define SEQUENCE_DEFAULT_LIGHT_MISS1 3
#define SEQUENCE_DEFAULT_LIGHT_MISS2 4
#define SEQUENCE_DEFAULT_HEAVY_MISS1 9
#define SEQUENCE_DEFAULT_HEAVY_HIT1 10
#define SEQUENCE_DEFAULT_HEAVY_BACKSTAB 11
#define SEQUENCE_DEFAULT_LOOKAT01 12

#define SEQUENCE_BUTTERFLY_DRAW 0
#define SEQUENCE_BUTTERFLY_DRAW2 1
#define SEQUENCE_BUTTERFLY_LOOKAT01 13
#define SEQUENCE_BUTTERFLY_LOOKAT03 15

#define SEQUENCE_FALCHION_IDLE1 1
#define SEQUENCE_FALCHION_HEAVY_MISS1 8
#define SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP 9
#define SEQUENCE_FALCHION_LOOKAT01 12
#define SEQUENCE_FALCHION_LOOKAT02 13

#define SEQUENCE_DAGGERS_IDLE1 1
#define SEQUENCE_DAGGERS_LIGHT_MISS1 2
#define SEQUENCE_DAGGERS_LIGHT_MISS5 6
#define SEQUENCE_DAGGERS_HEAVY_MISS2 11
#define SEQUENCE_DAGGERS_HEAVY_MISS1 12

#define SEQUENCE_BOWIE_IDLE1 1

// Store the original proxy functions.
RecvVarProxyFn oSequenceProxyFn = NULL;

bool requestFullUpdate = false;

class SkinChangerInfo
{
public:
	char model[128];
	int fallbackPaintKit;
	int itemDefinitionIndex;

	SkinChangerInfo(char *model_, int fallbackPaintKit_, int itemDefinitionIndex_)
	{
		strcpy(model, model_);
		fallbackPaintKit = fallbackPaintKit_;
		itemDefinitionIndex = itemDefinitionIndex_;
	}
};

//RecvVarProxyFn oRecvnModelIndex = NULL;

void SkinChanger(ClientFrameStage_t Stage)
{
	CBaseEntity *pLocal = G::pLocal;

	static std::vector<SkinChangerInfo> knifeModelReplace;
	
	if (knifeModelReplace.size() == 0)
	{
		knifeModelReplace.push_back(SkinChangerInfo(xorstr("models/weapons/v_knife_karam.mdl"), 38, WEAPON_KNIFE_KARAMBIT));
		knifeModelReplace.push_back(SkinChangerInfo(xorstr("models/weapons/v_knife_m9_bay.mdl"), 421, WEAPON_KNIFE_M9_BAYONET));
		knifeModelReplace.push_back(SkinChangerInfo(xorstr("models/weapons/v_knife_butterfly.mdl"), 12, WEAPON_KNIFE_BUTTERFLY));
	}

	if (Stage == FRAME_NET_UPDATE_POSTDATAUPDATE_START)
	{
		if (!requestFullUpdate && cfg.SkinChanger.knife != 0)
		{
			UINT* hWeapons = pLocal->GetWeapons();

			if (hWeapons)
			{
				int nLocalPlayerID = I::pEngineClient->GetLocalPlayer();

				player_info_t LocalPlayerInfo;
				I::pEngineClient->GetPlayerInfo(nLocalPlayerID, &LocalPlayerInfo);

				static int default_t = I::pModelInfo->GetModelIndex(xorstr("models/weapons/v_knife_default_t.mdl"));
				static int default_ct = I::pModelInfo->GetModelIndex(xorstr("models/weapons/v_knife_default_ct.mdl"));

				int replace = I::pModelInfo->GetModelIndex(knifeModelReplace[cfg.SkinChanger.knife - 1].model);

				// Loop through weapons and run our skin function on them.
				for (int nIndex = 0; hWeapons[nIndex]; nIndex++)
				{
					CBaseAttributableItem* pWeapon = (CBaseAttributableItem*)I::pClientEntityList->GetClientEntityFromHandle(hWeapons[nIndex]);

					if (!pWeapon)
						continue;

					// Compare original owner XUIDs.
					if (LocalPlayerInfo.m_nXuidLow != *pWeapon->GetOriginalOwnerXuidLow())
						continue;

					if (LocalPlayerInfo.m_nXuidHigh != *pWeapon->GetOriginalOwnerXuidHigh())
						continue;

					if (pWeapon->GetClientClass()->m_ClassID == 93) // knives
					{
						*pWeapon->GetFallbackPaintKit() = knifeModelReplace[cfg.SkinChanger.knife - 1].fallbackPaintKit;
						*pWeapon->GetItemDefinitionIndex() = knifeModelReplace[cfg.SkinChanger.knife - 1].itemDefinitionIndex;

						*pWeapon->GetItemIDHigh() = -1;
						*pWeapon->GetFallbackWear() = 0.0001f;
						*pWeapon->GetEntityQuality() = 3;
						/**pWeapon->GetViewModelIndex() = replace;
						*pWeapon->GetWorldModelIndex() = replace + 1;*/

						pWeapon->SetModelIndex(replace);

						// Fix up the account ID so StatTrak will display correctly.
						*pWeapon->GetAccountID() = LocalPlayerInfo.m_nXuidLow;

						CBaseViewModel *pViewModel = (CBaseViewModel*)I::pClientEntityList->GetClientEntityFromHandle(pLocal->GetViewModel());
						CBaseAttributableItem *pViewModelWeapon = (CBaseAttributableItem*)I::pClientEntityList->GetClientEntityFromHandle(pViewModel->GetWeapon());
						CBaseAttributableItem *pWorldModel = (CBaseAttributableItem*)I::pClientEntityList->GetClientEntityFromHandle(pWeapon->GetWorldModel());

						if (pWorldModel)
						{
							pWorldModel->SetModelIndex(replace + 1);
						}

						if (pLocal->GetViewModel() != -1)
						{
							if (pViewModelWeapon == pWeapon)
							{
								pViewModel->SetModelIndex(replace);
							}
						}
					}
					else
					{
						if (*pWeapon->GetItemDefinitionIndex() == WEAPON_SCAR20)
						{
							*pWeapon->GetFallbackPaintKit() = 597;							
						}
						else if (*pWeapon->GetItemDefinitionIndex() == WEAPON_G3SG1)
						{
							*pWeapon->GetFallbackPaintKit() = 465;
						}
						else if (*pWeapon->GetItemDefinitionIndex() == WEAPON_AK47)
						{
							*pWeapon->GetFallbackPaintKit() = 639;
						}
						else if (*pWeapon->GetItemDefinitionIndex() == WEAPON_AWP)
						{
							*pWeapon->GetFallbackPaintKit() = 344;
						}
						/*else if (*pWeapon->GetItemDefinitionIndex() == WEAPON_DEAGLE)
						{
							*pWeapon->GetFallbackPaintKit() = 232;
						}*/
						else if (*pWeapon->GetItemDefinitionIndex() == WEAPON_REVOLVER)
						{
							*pWeapon->GetFallbackPaintKit() = 595;
						}

						*pWeapon->GetItemIDHigh() = -1;
						*pWeapon->GetFallbackWear() = 0.0001f;
						*pWeapon->GetEntityQuality() = 3;
						*pWeapon->GetAccountID() = LocalPlayerInfo.m_nXuidLow;						
					}
				}
			}
		}

		if (requestFullUpdate)
		{
			static ConCommand * cl_fullupdate = NULL;

			if (!cl_fullupdate)
				cl_fullupdate = I::pCVar->FindCommand(xorstr("cl_fullupdate"));

			if (cl_fullupdate)
			{
				//cl_fullupdate->m_nFlags &= ~FCVAR_CHEAT;
				//I::pEngineClient->ClientCmd_Unrestricted(xorstr("cl_fullupdate"));
				//cl_fullupdate->m_nFlags |= FCVAR_CHEAT;
				cl_fullupdate->m_fnCommandCallbackV1();
			}

			requestFullUpdate = false;
		}
	}
}

/*
void RecvProxy_ModelIndex(CRecvProxyData *pData, void *pStruct, void *pOut)
{
	if (G::exit)
	{
		oRecvnModelIndex(pData, pStruct, pOut);
		return;
	}

	static int default_t = I::pModelInfo->GetModelIndex("models/weapons/v_knife_default_t.mdl");
	static int default_ct = I::pModelInfo->GetModelIndex("models/weapons/v_knife_default_ct.mdl");

	static int iKarambit = I::pModelInfo->GetModelIndex("models/weapons/v_knife_karam.mdl");

	CBaseEntity *pLocal = G::pLocal;

	if (pLocal)
	{
		if (pLocal->GetLifeState() == LIFE_ALIVE && (pData->m_Value.m_Int == default_t || pData->m_Value.m_Int == default_ct))
		{
			pData->m_Value.m_Int = iKarambit;
		}
	}

	oRecvnModelIndex(pData, pStruct, pOut);
}
*/

// Function to fix sequences for certain models.
void RecvProxy_SetViewModelSequence(const CRecvProxyData *pDataConst, void *pStruct, void *pOut)
{
	// Make the incoming data editable.
	CRecvProxyData* pData = const_cast<CRecvProxyData*>(pDataConst);

	// Confirm that we are replacing our view model and not someone elses.
	CBaseViewModel* pViewModel = (CBaseViewModel*)pStruct;

	if (pViewModel) {
		CBaseEntity* pOwner = I::pClientEntityList->GetClientEntityFromHandle(pViewModel->GetOwner());
		
		// Compare the owner entity of this view model to the local player entity.
		if (pOwner && pOwner == G::pLocal) {
			// Get the filename of the current view model.
			const model_t* pModel = I::pModelInfo->GetModel(pViewModel->GetModelIndex());
			const char* szModel = I::pModelInfo->GetModelName(pModel);
			
			// Store the current sequence.
			int m_nSequence = pData->m_Value.m_Int;

			if (!strcmp(szModel, xorstr("models/weapons/v_knife_butterfly.mdl"))) {
				// Fix animations for the Butterfly Knife.
				switch (m_nSequence) {
				case SEQUENCE_DEFAULT_DRAW:
					m_nSequence = Math::Random(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2); break;
				case SEQUENCE_DEFAULT_LOOKAT01:
					m_nSequence = Math::Random(SEQUENCE_BUTTERFLY_LOOKAT01, SEQUENCE_BUTTERFLY_LOOKAT03); break;
				default:
					m_nSequence++;
				}
			}
			else if (!strcmp(szModel, xorstr("models/weapons/v_knife_falchion_advanced.mdl"))) {
				// Fix animations for the Falchion Knife.
				switch (m_nSequence) {
				case SEQUENCE_DEFAULT_IDLE2:
					m_nSequence = SEQUENCE_FALCHION_IDLE1; break;
				case SEQUENCE_DEFAULT_HEAVY_MISS1:
					m_nSequence = Math::Random(SEQUENCE_FALCHION_HEAVY_MISS1, SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP); break;
				case SEQUENCE_DEFAULT_LOOKAT01:
					m_nSequence = Math::Random(SEQUENCE_FALCHION_LOOKAT01, SEQUENCE_FALCHION_LOOKAT02); break;
				case SEQUENCE_DEFAULT_DRAW:
				case SEQUENCE_DEFAULT_IDLE1:
					break;
				default:
					m_nSequence--;
				}
			}
			else if (!strcmp(szModel, xorstr("models/weapons/v_knife_push.mdl"))) {
				// Fix animations for the Shadow Daggers.
				switch (m_nSequence) {
				case SEQUENCE_DEFAULT_IDLE2:
					m_nSequence = SEQUENCE_DAGGERS_IDLE1; break;
				case SEQUENCE_DEFAULT_LIGHT_MISS1:
				case SEQUENCE_DEFAULT_LIGHT_MISS2:
					m_nSequence = Math::Random(SEQUENCE_DAGGERS_LIGHT_MISS1, SEQUENCE_DAGGERS_LIGHT_MISS5); break;
				case SEQUENCE_DEFAULT_HEAVY_MISS1:
					m_nSequence = Math::Random(SEQUENCE_DAGGERS_HEAVY_MISS2, SEQUENCE_DAGGERS_HEAVY_MISS1); break;
				case SEQUENCE_DEFAULT_HEAVY_HIT1:
				case SEQUENCE_DEFAULT_HEAVY_BACKSTAB:
				case SEQUENCE_DEFAULT_LOOKAT01:
					m_nSequence += 3; break;
				case SEQUENCE_DEFAULT_DRAW:
				case SEQUENCE_DEFAULT_IDLE1:
					break;
				default:
					m_nSequence += 2;
				}
			}
			else if (!strcmp(szModel, xorstr("models/weapons/v_knife_survival_bowie.mdl"))) {
				// Fix animations for the Bowie Knife.
				switch (m_nSequence) {
				case SEQUENCE_DEFAULT_DRAW:
				case SEQUENCE_DEFAULT_IDLE1:
					break;
				case SEQUENCE_DEFAULT_IDLE2:
					m_nSequence = SEQUENCE_BOWIE_IDLE1; break;
				default:
					m_nSequence--;
				}
			}

			// Set the fixed sequence.
			pData->m_Value.m_Int = m_nSequence;
		}
	}

	// Call original function with the modified data.
	oSequenceProxyFn(pData, pStruct, pOut);
}
