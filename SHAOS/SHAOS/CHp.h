#pragma once
class CHp
{
	const INT imaxHp;
	INT ihp;
	BOOL IsZero;
public:
	CHp(INT initHp) ;
	~CHp();

	INT GetHp() const;
	void SetHp(INT sethp);
	void AddHp(INT addhp);
	BOOL SubHp(INT subhp);
};

