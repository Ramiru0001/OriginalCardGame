#pragma once
#include "../Base/Base.h"
#include <Gllibrary.h>
//カードの優先度
enum class ECardNum
{
};
//カードを引いたときに呼ばれる
class BaseCard :public Base{
public:
	//カードの数字。
	//0~12がハート
	//13~25がダイヤ
	//26~38がクラブ
	//39~51がスペード
	int CardNum[45];
	//カードリスト
	std::list<int> AllCard_list;//すべてのカードのリスト
	std::list<int> Remaining_list;//すべてのカードのリスト
	std::list<int> Stock_list;//開かれてない山札
	std::list<int> Waste_list;//開かれて左に移動した山札
	std::list<int> Reserve_list0;//場札。1番左
	std::list<int> Reserve_list1;//場札。左から2番目
	std::list<int> Reserve_list2;//場札。左から3番目
	std::list<int> Reserve_list3;//場札。左から4番目
	std::list<int> Reserve_list4;//場札。左から5番目
	std::list<int> Reserve_list5;//場札。左から6番目
	std::list<int> Reserve_list6;//場札。左から7番目,1番右
	std::list<int> Foundation_list;//左上の組札
	CImage heart[14];//赤
	CImage diamond[14];//赤
	CImage club[14];//黒
	CImage spade[14];//黒
	CImage BehindCard;//トランプの背面の画像
public:
	BaseCard();
	~BaseCard();
	//コピー、切り取り、サイズ指定、CardNum指定
	void ImageSet();
	void Update();
	void Draw();
	void CardListSet();
};