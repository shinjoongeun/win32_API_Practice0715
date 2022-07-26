#pragma

class CObject;

class CScene
{
private:
	//vector<CObject*> m_vecObject;
	vector<CObject*> m_arrLayer[MAX_LAYER]; // ���� ���� ���� �ϳ��� ������ ��Ұ� ���ϳ��� ������ ����

public:
	void AddObject(CObject* _pObject, LAYER_TYPE _eLayer) // m_arrLayer �� ��� ���̾� ��� �κп� ��� ������Ʈ�� ���� ������ 
	{
		m_arrLayer[(UINT)_eLayer].push_back(_pObject);
	}
public:
	virtual void SceneInit() = 0;
	virtual void SceneTick();
	virtual void SceneRender(HDC _dc);

public:
	CScene();
	~CScene();
};