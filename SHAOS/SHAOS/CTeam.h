#pragma once
#include "CUnit.h"
#include "CTower.h"

class CGameObject;
class CTeam
{
protected:
	CGameObject* p_myobj{ nullptr };
	CGameObject* p_opponentobj{ nullptr };

	INT imyobjnum;
	INT iopnobjnum;

	UINT iunitgentime;
public:
	CTeam();
	virtual ~CTeam();
	void UpdateOpponentObj(CGameObject&);
	void AddMyObjList(CGameObject*);
	void DeleteInList(CGameObject*);

};

