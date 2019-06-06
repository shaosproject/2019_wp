#include "pch.h"
#include "CTeam.h"
#include "CGameObject.h"

CTeam::CTeam()
{
	imyobjnum = 0;
	iopnobjnum = 0;
}


CTeam::~CTeam()
{
	for (int i = 0; i < imyobjnum; i++) {
		CGameObject* delp = p_myobj;
		(p_myobj->next != nullptr) ? p_myobj = p_myobj->next : nullptr;
		delete delp;
	}
}

CGameObject* CTeam::GetMyObjList() const
{
	return p_myobj;
}

void CTeam::SetOpponentObj(CGameObject* objlist)
{
	p_opponentobj = objlist;
}

void CTeam::AddMyObjList(CGameObject* addobj)
{
	imyobjnum++;
	if (!p_myobj) {
		p_myobj = addobj;
		return;
	}

	addobj->next = p_myobj;
	p_myobj->prev = addobj;
	p_myobj = addobj;
}

void CTeam::DeleteInList(CGameObject* delobj)
{
	imyobjnum--;
	if (imyobjnum == 0) {
		p_myobj = nullptr;
		delete delobj;
		return;
	}
	if (delobj == p_myobj) {
		p_myobj->next->prev = nullptr;
		delobj->next = p_myobj;
		delete delobj;
		return;
	}
	delobj->prev->next = delobj->next;
	delobj->next->prev = delobj->prev;
	delete delobj;
}
