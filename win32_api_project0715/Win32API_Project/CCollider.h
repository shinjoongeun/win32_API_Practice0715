#pragma once
#include "CComponent.h"

class CCollider :
	public CComponent
{
public:
	Vec m_ColliderOffSet; // Object�� ���� ������� �Ÿ�
	Vec m_ColliderScale;

	Vec m_ColliderFinalPos; // �浹ü�� ���� ��ġ

public:
	void SetColliderScale(Vec _vScale) { m_ColliderScale = _vScale; };
	void SetColliderOffset(Vec _vOffset) { m_ColliderOffSet = _vOffset; };
public:
	virtual void ComponentTick() override;
	virtual void ComponentRender(HDC _dc) override;
public:
	CCollider();
	~CCollider();
};

