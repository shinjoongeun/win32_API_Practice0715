#include "stdafx.h"
#include "CCollider.h"
#include "CObject.h" // Object�� Pos �� Scale�� �˱� ���� ����
#include "CEngine.h"

void CCollider::ComponentTick()
{
	CObject* pOwnerObject = GetOwnerObject();

	// �浹ü�� ���� ��ġ�� ��ü�� ��ġ + ��ü�� �浹ü ������ �Ÿ��� ����.
	m_ColliderFinalPos = pOwnerObject->GetPos() + m_ColliderOffSet;
}

void CCollider::ComponentRender(HDC _dc)
{
	m_ColliderFinalPos;
	// �浹ü ������ �ʷ� �׵θ��� ǥ��
	tSelectPen ColliderPen(_dc, PEN_COLOR::GREEN);
	tSelectBrush ColliderBrush(_dc, BRUSH_COLOR::HOLLOW);

	Rectangle(_dc, (int)(m_ColliderFinalPos.x - m_ColliderScale.x / 2.f)
		, (int)(m_ColliderFinalPos.y - m_ColliderScale.y / 2.f)
		, (int)(m_ColliderFinalPos.x + m_ColliderScale.x / 2.f)
		, (int)(m_ColliderFinalPos.y + m_ColliderScale.y / 2.f));
}

CCollider::CCollider()
// CCollider �� �����ڴ� �θ� Ŭ���� CComponent�� �����ڸ� ȣ���Ѵ�.
// �̶� CComponent�� �⺻������ ���� ���ڸ� ������ ������ ���� ���� �ϹǷ� �� ���ڸ� ������ �����ڸ� ��ӹ޴´ٰ� ǥ���Ѵ�.
// ���� �ڵ�� CCollider Ŭ������ �����ڰ� �θ� ũ������ CComponent Ŭ������ �����ڸ� ��� �޾Ҵٴ� ���̴�.
	: CComponent(COMPONENT_TYPE::COLLIDER)
{
}

CCollider::~CCollider()
{
}
