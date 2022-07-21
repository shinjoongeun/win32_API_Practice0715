#pragma once
class CComponent
{
private:

	// AddComponent �� ���ؼ� ������Ʈ�� ������ ��
	// �� ������Ʈ�� �ڽ��� ��� ������Ʈ ���� ������� ������ ���ؼ� ������Ʈ Ÿ���� ����� �����Ѵ�.
	// �̶� ����� ������ �ɹ� ����� �ʱ�ȭ �� �ϸ� ���̻� ������ ������ �������� �ʱ�ȭ�θ� (����x) ���� �ִ� ���� �����ϴ�.
	const COMPONENT_TYPE m_eType;

public:
	virtual void ComponentTick() = 0;

	// �浹������ ���� ������ �� ��찡 �����Ƿ�.
	virtual void ComponentRender(HDC _dc);

	COMPONENT_TYPE GetComponentType() { return m_eType; };

public:
	// �����ڴ� ����ڰ� ������ ��� �⺻�����ڰ� �������� �ʴ´�.
	// new CComponent �� ������Ʈ�� ������ �� �� ������Ʈ�� ������ ���ڷ� �־ ��� ������ �ʱ�ȭ �ϰ� �����μ�
	// �� ������Ʈ�� ���� ������ �ǰ� �Ѵ�.
	CComponent(COMPONENT_TYPE _eType)
		: m_eType(_eType)
	{};
	~CComponent(){};
};

