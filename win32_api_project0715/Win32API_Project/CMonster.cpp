#include "stdafx.h"
#include "CMonster.h"

#include "CResMgr.h"
#include "CImage.h"
#include "CCollider.h"

CMonster::CMonster()
	: m_MonsterImage(nullptr)
{
	AddComponent(new CCollider);

	GetCollider()->SetColliderOffset(Vec(0.f, -35.f));
	GetCollider()->SetColliderScale(Vec(320.f, 130.f));


	m_MonsterImage = CResMgr::GetInst()->LoadImg(L"Monster", L"image\\Monster.bmp");
}

CMonster::~CMonster()
{
}

void CMonster::ObjTick()
{
	CObject::ObjTick();
}

void CMonster::ObjRender(HDC _dc)
{
	Vec vPos = GetPos();

	TransparentBlt(_dc, (int)vPos.x - m_MonsterImage->GetWidth() / 2
		, (int)vPos.y - m_MonsterImage->GetHeight() / 2
		, m_MonsterImage->GetWidth(), m_MonsterImage->GetHeight()
		, m_MonsterImage->GetImageDC(), 0, 0, m_MonsterImage->GetWidth(), m_MonsterImage->GetHeight(), RGB(255, 0, 255));

	CObject::ObjRender(_dc);
}