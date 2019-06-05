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
