#pragma once

class CComponent;
class CCollider;

class CObject
{
private:

	// �� ��ü�� ������Ʈ�� �迭�� ������ �ִ´�.
	CComponent* m_arrComponent[(UINT)COMPONENT_TYPE::END];

	Vec m_vPos;
	Vec m_vScale;

public:
	void SetPos(Vec _vPos)
	{
		m_vPos = _vPos;
	}
	void SetScale(Vec _vScale)
	{
		m_vScale = _vScale;
	}

	Vec GetPos()
	{
		return m_vPos;
	}
	Vec GetScale()
	{
		return m_vScale;
	} 

	CCollider* GetCollider() { return (CCollider*)m_arrComponent[(UINT)COMPONENT_TYPE::COLLIDER]; }
	//CAnimator* GetAnimator() { return (CCollider*)m_arrComponent[(UINT)COMPONENT_TYPE::ANIMATOR]; }
	//CGravity* GetGravity() { return (CCollider*)m_arrComponent[(UINT)COMPONENT_TYPE::GRAVITY]; }

	void AddComponent(CComponent* _pComponent);
	

	virtual void ObjTick();
	virtual void ObjRender(HDC _dc);

public:
	// ���� �����Լ��� ����ϴ� Tick() �� CObject ���� ����ؾ� �Կ� ���� ��ü�� �������� �Լ��� �ӽ÷� ����
	// ���� �����Լ��� ���� �ؾ� �ϴ� ���� -> CObject Ŭ�����δ� ��ü�� ���� �� ����.
	virtual CObject* Clone() = 0;

public:
	CObject();
	~CObject();
};

