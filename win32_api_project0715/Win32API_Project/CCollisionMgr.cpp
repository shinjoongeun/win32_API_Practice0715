#include "stdafx.h"
#include "CCollisionMgr.h"
#include "CScene.h"
#include "CSceneMgr.h"
#include "CObject.h"
#include "CCollider.h"

CCollisionMgr::CCollisionMgr()
	: m_matrix{}
{
}

CCollisionMgr::~CCollisionMgr()
{
}


void CCollisionMgr::CollisionMgrTick()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	for (UINT iRow = 0; iRow < MAX_LAYER; ++iRow)
	{
		// m_matrix�� 2���� ������ ����̱� ������ iCol�� �������� iRow �� ���������ν� �� ���캸�ƾ� �� ��츦 ������ ���δ�.
		for (UINT iCol = iRow; iCol < MAX_LAYER; ++iCol)
		{
			if (m_matrix[iRow] & (1 << iCol))
			{
				CollisionBtwLayer(pCurScene, (LAYER_TYPE)iRow, (LAYER_TYPE)iCol);
			}
		}
	}
}

void CCollisionMgr::CollisionBtwLayer(CScene* _pCurScene, LAYER_TYPE _layer1, LAYER_TYPE _layer2)
{
	const vector<CObject*>& vecObj1 = _pCurScene->GetObjects(_layer1);
	const vector<CObject*>& vecObj2 = _pCurScene->GetObjects(_layer2);

	for (size_t i = 0; i < vecObj1.size(); ++i)
	{
		// vecObj1�� �浹ü�� ���� ���
		if (nullptr == vecObj1[i]->GetCollider())
		{
			continue;
		}
		for (size_t j = 0; j < vecObj2.size(); ++j)
		{
			// �� ��ü�� �����ϰų� vecObj2�� �浹ü�� ���°��
			if (vecObj1[i] == vecObj2[j] || nullptr == vecObj2[j]->GetCollider()) // �ڱ� �ڽŰ� �浹�ϴ� ������ ���Ǵ� ���
			{
				continue;
			}

			// �� ��ü�� �����ϸ� ���� ��� �浹ü�� �ִ°��
			// �� �浹ü�� ID Ȯ��
			COLLIDER_ID id;
			id.FIRST_ID = vecObj1[i]->GetCollider()->GetID();
			id.SECOND_ID = vecObj2[j]->GetCollider()->GetID();
			// COLLIDER_ID�� union ���� �ϳ��� ����� �޸� �������� �̷�����ִ�. 
			// FIRST_ID �� 8����Ʈ �� ID �� ����  4����Ʈ�� , SECOND_ID�� ���� 4����Ʈ�� �����ϰ� �ֵ�.
			// ���� �̶� ID�� �޸� ������ ������ �� ���α׷� ���� ������ Ű���� �ȴ�.
			id.ID;

			// ���� �浹 ������ �˻��Ѵ�.
			// map �� bool �� �浹�� ���� �� �ǹ��Ѵ�.
			map<LONGLONG,bool>::iterator CollisionInfoIter = m_mapColInfo.find(id.ID);
			// �浹 ������ �ƿ� ���� ��� ����� �ش�.
			if (CollisionInfoIter == m_mapColInfo.end())
			{
				m_mapColInfo.insert(make_pair(id.ID, false));
				// �߰� ���ص� �ٽ� �˻��Ͽ� CollisionInfoIter�� ���� �Ѵ�.
				CollisionInfoIter = m_mapColInfo.find(id.ID);
			}

			if (IsCollision(vecObj1[i]->GetCollider(), vecObj2[j]->GetCollider()))
			{
				// ���� �����ӿ� �浹�� ���۵Ǵ� ���
				if (false == CollisionInfoIter->second)
				{
					vecObj1[i]->GetCollider()->CollisionBeginOverlap(vecObj2[j]->GetCollider());
					vecObj2[j]->GetCollider()->CollisionBeginOverlap(vecObj1[i]->GetCollider());
					CollisionInfoIter->second = true;
				}
				else
				{
					// ������ �浹�ϰ� ���翡�� �浹�ϰ� �ִ� ���
					vecObj1[i]->GetCollider()->CollisionOverlap(vecObj2[j]->GetCollider());
					vecObj2[j]->GetCollider()->CollisionOverlap(vecObj1[i]->GetCollider());
				}
			}
			else 
			{
				// �浹�� �� ����ƴ� ����
				if (CollisionInfoIter->second)
				{
					vecObj1[i]->GetCollider()->CollisionEndOverlap(vecObj2[j]->GetCollider());
					vecObj2[j]->GetCollider()->CollisionEndOverlap(vecObj1[i]->GetCollider());
					CollisionInfoIter->second = false;
				}
			}
		}
	}
}

bool CCollisionMgr::IsCollision(CCollider* _collider1, CCollider* _collider2)
{
	Vec _collider1Pos = _collider1->GetColliderFinalPos();
	Vec _collider1Scale = _collider1->GetColliderScale();

	Vec _collider2Pos = _collider2->GetColliderFinalPos();
	Vec _collider2Scale = _collider2->GetColliderScale();

	// �� �浹ü�� ���� ���� �Ÿ���, �� �浹ü�� ���� ���� �� ���� ���ݳ����� ���� ���Ͽ�
	// ����(x,y) ���� ��ġ�� �κ��� ���ÿ� �����ϴ��� üũ�Ѵ�.
	if (fabs(_collider1Pos.x - _collider2Pos.x) < (_collider1Scale.x / 2.f + _collider2Scale.x / 2.f)
		&& fabs(_collider1Pos.y - _collider2Pos.y) < (_collider1Scale.y / 2.f + _collider2Scale.y / 2.f))
	{
		return true;
	}
	
	return false;
}

void CCollisionMgr::CollisionLayerCheck(LAYER_TYPE _Layer1, LAYER_TYPE _Layer2)
{
	// �� ���� ���ڸ� ��( �迭�� �ε���)���� , �� ū ���ڸ� ��(��Ʈ ��ġ) ��
	UINT iRow = 0;
	UINT iCol = 0;

	// ��Ʈ������ �ݸ� ����ϱ� ���� iRow 
	if ((UINT)_Layer1 < UINT(_Layer2))
	{
		iRow = (UINT)_Layer1;
		iCol = (UINT)_Layer2;
	}
	else
	{
		iRow = (UINT)_Layer2;
		iCol = (UINT)_Layer1;
	}

	// �浹�� �Ͼ �� ���̾��� LAYER_TYPE �� ���� ���̾��� UINT ���� iRow ū ���� iCol�̶�� �Ҷ�.
	// m_matrix[iRow] �� (1 << iCol �� ���� ���� UINT ���� ���̾� ��Ʈ �κ�)�� ��Ʈ���� ������ üũ�Ѵ�.
	m_matrix[iRow] |= (1 << iCol);
}

void CCollisionMgr::CollisionLayerRelease(LAYER_TYPE _Layer1, LAYER_TYPE _Layer2)
{
	UINT iRow = 0;
	UINT iCol = 0;

	if ((UINT)_Layer1 < UINT(_Layer2))
	{
		iRow = (UINT)_Layer1;
		iCol = (UINT)_Layer2;
	}
	else
	{
		iRow = (UINT)_Layer2;
		iCol = (UINT)_Layer1;
	}

	m_matrix[iRow] &= ~(1 << iCol);
}

