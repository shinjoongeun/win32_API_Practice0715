#include "stdafx.h"
#include "CObject.h"
#include "CComponent.h"

// ��ü�� ���Ӱ� ������Ʈ�� �����ϸ� ������ ��ü�� ������ �ִ� ������Ʈ �迭�� �ö��̴� ������Ʈ�� �ִ´�.
void CObject::AddComponent(CComponent* _pComponent)
{
	//m_arrComponent[(UINT)COMPONENT_TYPE::COLLIDER] = _pComponent;
	m_arrComponent[(UINT)_pComponent->GetComponentType()] = _pComponent;
}

void CObject::ObjTick()
{
	// CObject�� Tick �� ��ü�� ���� ��� Component�� Tick �� ȣ���Ѵ�.
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr == m_arrComponent[i])
		{
			// �ݺ������� continue �� �� ���� ������ ������ �����ϰ� ���ǹ��� �̾ �����Ѵ�.
			// break �� �ݺ����� �����Ѵ�.
			continue;
		}
		m_arrComponent[i]->ComponentTick();
	}
}

void CObject::ObjRender(HDC _dc)
{
	// ƽ�� ���������� �������� ������Ʈ�� �������� �� ������Ʈ�� Ŭ�������� �����ϰ� CObject Ŭ������ �� ������Ʈ����  render Ŭ������ ȣ���Ѵ�.
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if(nullptr == m_arrComponent[i])
		{
			continue;
		} 
		m_arrComponent[i]->ComponentRender(_dc);
	 }
}

CObject::CObject()
// ó���� ��ü�� ������ ������ ���� ��� ������Ʈ�� ��ü�� ���� �� �𸣱� ������ ��� ��Ҹ� nullptr�� �ʱ�ȭ �Ѵ�.
	: m_arrComponent{}
{
}

CObject::~CObject()
{
	// ��ü�� ������Ʈ�� �ּڰ��� ������ �ֱ� ������ ���� �����־�� �Ѵ�.
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		// ���� ������ ���� ���̱� ������ ��ũ��ȭ ���ش�.
		/*if (nullptr != m_arrComponent[i])
		{
			delete m_arrComponent[i];
		}*/
		SAFE_DELETE(m_arrComponent[i]);
	}

}
