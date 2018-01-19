#pragma once

#include "FrameStageNotify.h"

//void RecvProxy_ModelIndex(CRecvProxyData *pData, void *pStruct, void *pOut);
void SkinChanger(ClientFrameStage_t Stage);

//extern RecvVarProxyFn oRecvnModelIndex;

extern bool requestFullUpdate;

extern RecvVarProxyFn oSequenceProxyFn;
void RecvProxy_SetViewModelSequence(const CRecvProxyData *pDataConst, void *pStruct, void *pOut);

