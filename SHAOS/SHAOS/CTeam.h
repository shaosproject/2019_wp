#pragma once
class CGameObject;
class CTower;
class CUnit;

class CTeam
{
protected:
	CGameObject* p_myobj{ nullptr };
	CGameObject* p_opponentobj{ nullptr };

	INT imyobjnum;
	INT iopnobjnum;
public:
	CTeam();
	virtual ~CTeam();
	void UpdateOpponentObj(CGameObject&);
	void AddMyObjList(CGameObject*);
	void DeleteInList(CGameObject*);

};

