#pragma once
#include "CUnit.h"
#include "CTower.h"

class CGameObject;
class CTeam
{
protected:
	// ���� �׻� Ÿ���� ����Ų��
	CGameObject* p_myobjlist{ nullptr };
	CGameObject* p_opponentobjlist{ nullptr };


	INT imyobjnum;
	INT iopnobjnum;

	UINT iunitgentime;

public:
	CTeam();
	virtual ~CTeam();


	CGameObject* GetMyObjList() const;
	virtual void SetOpponentObj(CGameObject*) = 0;


	void AddMyObjList(CGameObject*);
	void DeleteInList(CGameObject*);
};

