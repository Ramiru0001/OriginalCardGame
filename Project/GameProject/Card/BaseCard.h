#pragma once
#include "../Base/Base.h"
#include <Gllibrary.h>
//カードの優先度
enum class SortCard
{
	GoddessCard, 
	CatCard,
	NormalCard,	//ノーマル
	Deveil,
};
class BaseCard :public Base{
public:
	static std::list<Base*> Card_list;
public:
	Task();
};