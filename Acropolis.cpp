#include "stdafx.h"
#include "Acropolis.h"
#include "ServiceManager.h"
#include "DirectX.h"
#include "TexturedGameObject.h"

Acropolis::Acropolis(D3DXVECTOR3 scale, D3DXVECTOR3 position, D3DXVECTOR3 view, TexturedGameObject* gameObject) : GameObject(scale, position, view),
gameObject_(gameObject)
{
}

void Acropolis::renderCustom(double lagTime)
{
	DirectX& directX = getServiceManager().getDirectX();
	DWORD oldRenderState;
	directX.getRenderState(D3DRS_CULLMODE, oldRenderState);
	directX.setRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	gameObject_->renderCustom(lagTime);
	directX.setRenderState(D3DRS_CULLMODE, oldRenderState);
}

void Acropolis::updateCustom()
{
}
