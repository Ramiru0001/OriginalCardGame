#pragma once
#include "../Base/Base.h"
#include <Gllibrary.h>
//�J�[�h�̗D��x
enum class SortCard
{
	GoddessCard, 
	CatCard,
	NormalCard,	//�m�[�}��
	Deveil,
};
class BaseCard :public Base{
public:
	static std::list<Base*> Card_list;
public:
	Task();
};