#include "pch.h"
#include "CTeam.h"
#include "CGameObject.h"

CTeam::CTeam()
{
	// Å¸¿ö 1°³
	imyobjnum = 1;
	iopnobjnum = 1;
}


CTeam::~CTeam()
{
	for (int i = 0; i < imyobjnum; i++) {
		CGameObject* delp = p_myobjlist;
		(p_myobjlist->next != nullptr) ? p_myobjlist = p_myobjlist->next : nullptr;
		delete delp;
	}
}

CGameObject* CTeam::GetMyObjList() const
{
	return p_myobjlist;
}

void CTeam::SetOpponentObj(CGameObject* objlist)
{
	p_opponentobjlist = objlist;
}

void CTeam::AddMyObjList(CGameObject* addobj)
{
	addobj->next = p_myobjlist;
	addobj->prev = p_myobjlist->prev;
	p_myobjlist->prev->next = addobj;
	p_myobjlist->prev = addobj;

	imyobjnum++;
}

void CTeam::DeleteInList(CGameObject* delobj)
{
	imyobjnum--;
	if (imyobjnum == 0) {
		p_myobjlist = nullptr;
		delete delobj;
		return;
	}

	delobj->prev->next = delobj->next;
	delobj->next->prev = delobj->prev;
	delete delobj;
}
