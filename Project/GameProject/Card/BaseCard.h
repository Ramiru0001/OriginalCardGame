#pragma once
#include "../Base/Base.h"
#include <Gllibrary.h>
//カードを引いたときに呼ばれる
class BaseCard :public Base{
public:
	//リストナンバー
	enum {
		eNum_stock,
		eNum_Waste,
		eNum_Reserve0,
		eNum_Reserve1,
		eNum_Reserve2,
		eNum_Reserve3,
		eNum_Reserve4,
		eNum_Reserve5,
		eNum_Reserve6,
		eNum_ReserveOpen0,
		eNum_ReserveOpen1,
		eNum_ReserveOpen2,
		eNum_ReserveOpen3,
		eNum_ReserveOpen4,
		eNum_ReserveOpen5,
		eNum_ReserveOpen6,
		eNum_Foundation0,
		eNum_Foundation1,
		eNum_Foundation2,
		eNum_Foundation3,
	};
	//カードの数字。
	//0~12がハート
	//13~25がダイヤ
	//26~38がクラブ
	//39~51がスペード
	int CardNum[51];

	//リストナンバー
	//bool InsideOrOutsideTheCard();これを実行したら更新される
	int ListNum;
	//今動いているカードのレーンを指定
	int MovingLane;
	//動かせるカードの上にマウスがあるかどうか
	bool MouseOverCard;
	//場札の空白
	int Space = 20;
	//カードが今動いているかどうか
	bool CardMoving;
	//すべてのカードのリスト
	std::list<int> AllCard_list = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51 };
	//余ってるカードのリスト
	std::list<int> Remaining_list = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51 };
	std::list<int> Stock_list;//開かれてない山札
	std::list<int> Waste_list;//開かれて左に移動した山札
	std::list<int> Reserve_list0;//場札。1番左
	std::list<int> Reserve_list1;//場札。左から2番目
	std::list<int> Reserve_list2;//場札。左から3番目
	std::list<int> Reserve_list3;//場札。左から4番目
	std::list<int> Reserve_list4;//場札。左から5番目
	std::list<int> Reserve_list5;//場札。左から6番目
	std::list<int> Reserve_list6;//場札。左から7番目,1番右
	std::list<int> Reserve_listOpen0;//開かれた場札。1番左
	std::list<int> Reserve_listOpen1;//開かれた場札。左から2番目
	std::list<int> Reserve_listOpen2;//開かれた場札。左から3番目
	std::list<int> Reserve_listOpen3;//開かれた場札。左から4番目
	std::list<int> Reserve_listOpen4;//開かれた場札。左から5番目
	std::list<int> Reserve_listOpen5;//開かれた場札。左から6番目
	std::list<int> Reserve_listOpen6;//開かれた場札。左から7番目,1番右
	std::list<int> Foundation_list0;//左上の組札。1番左
	std::list<int> Foundation_list1;//左上の組札。左から2番め
	std::list<int> Foundation_list2;//左上の組札。左から3番目
	std::list<int> Foundation_list3;//左上の組札。左から4番目
	CImage heart[14];//ハートの赤
	CImage diamond[14];//ダイヤの赤
	CImage club[14];//クローバーの黒
	CImage spade[14];//スペードの黒
	CImage BehindCard;//トランプの背面の画像
	CImage m_img;//選択中の画像。Temp
	CVector2D MousePos;
public:
	BaseCard();
	~BaseCard();
	//コピー、切り取り、サイズ指定、CardNum指定。初期設定
	void ImageSet();
	void Update();
	void Draw();
	//カードをリストにセットする。振り分ける。初期設定
	void CardListSet();
	//呼ばれたら、その引数のカードをm_imgに指定
	void CardNumToImage(int ThatCardNumber);
	//リストを読み込み、画像を指定、配置。
	void LoadTheListAndDraw();
	//動いているカードの表示
	void MovingCardDraw();
	//マウスが動かせるカードの上にあるかないか。
	//ある場合,	MouseOverCard=trueにする、ListNumを更新する。
	void InsideOrOutsideTheCard();
	//StockListとWaseteListの双方向移動
	void BothStockAndWaste();
	// カードから一定範囲内で、一番近いカードに置けるかどうか試して
	//置ける場合はそのリストの１番最後に追加
	//void
};