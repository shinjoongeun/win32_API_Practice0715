#include "stdafx.h"
#include "CCollider.h"

void CCollider::ComponentTick()
{
}

void CCollider::ComponentRender(HDC _dc)
{
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
