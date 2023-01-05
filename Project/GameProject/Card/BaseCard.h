#pragma once
#include "../Base/Base.h"
#include <Gllibrary.h>
//カードを引いたときに呼ばれる
class BaseCard :public Base{
public:
	enum CardDesign{
		eNum_Heart,
		eNum_Diamond,
		eNum_Club,
		eNum_Spade,
	};
	//現在のゲーム設定
	enum GameMode{
		eState_Normal,
		eState_Random,
		eState_Debug,
		eState_Auto,
	};
	//リストナンバー
	//カードの数字。
	//0~12がハート
	//13~25がクラブ
	//26~38がダイヤ
	//39~51がスペード
	enum List{
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
	//現在の場面。ユーザーが操作する画面の移行に使われる
	enum GameScene{
	eScene_Play,//プレイ中
	eScene_AutoStay,//AUTOボタン表示中
	eScene_Auto,//自動
	eScene_Clear,//クリア画面
	};
	int CardNum[51];
	//現在のゲーム画面。プレイ中、AUTOボタンが表示されている、等
	//ユーザーが操作する画面の移行に使われる
	int GameScene = eScene_Play;
	//リストナンバー
	//bool InsideOrOutsideTheCard();これを実行したら更新される
	int ListNum;
	//リストのN番目
	int LaneNum;
	//今動いているカードのレーンを指定
	int MovingLane;
	//途中から動かせるレーンを指定
	int MiddleMovingLaneNum;
	//途中から動かせる先のリストを指定
	int MiddleMovingListNum;
	//動かせるカードの上にマウスがあるかどうか
	bool MouseOverCard;
	//reserveリストの上にマウスがあるかどうか
	bool MouseOverReserve;
	//resreveリストかWasteリストの上にマウスがあるかどうか
	bool MouseOverReserveAndWasteLists;
	//stockリストの上にマウスがあるかどうか
	bool MouseOverStockList;
	//途中から動かせる場合:true
	bool MiddleMovingCheck;
	//途中から動かせる場合、動かせる先のリストをいれる
	int MiddleMovingList[10];
	//途中から動かせる場合、ここにそのリストのN番目、を入れる
	int MiddleMovingLane[10];
	//途中から動かせる数を数えて、代入
	int MiddleMovingCount = 0;
	///場札の空白 20
	int Space = 20;
	//場札openの空白 50
	int OpenSpace = 50;
	//選択中のモード：0_normal;1_auto
	int SelectMode = 0;
	//カードが今動いているかどうか
	bool CardMoving;
	//今、途中からカードが動いているか否か
	bool MiddleCardMoving;
	//debugモードのstate
	int DebugMode_State;
	//マウスとカードの上端の距離
	int MouseDistance;
	//クリア画面表示までのカウントダウン
	int ClearCountDown;
	//すべてのカードのリスト
	std::list<int> AllCard_list = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51 };
	std::list<int> HeartCard_list = { 0,1,2,3,4,5,6,7,8,9,10,11,12 };//ハートカードリスト
	std::list<int> ClubCard_list = { 13,14,15,16,17,18,19,20,21,22,23,24,25 };//クラブカードリスト
	std::list<int> DiamondCard_list = { 26,27,28,29,30,31,32,33,34,35,36,37,38 };//ダイヤカードリスト
	std::list<int> SpadeCard_list = { 39,40,41,42,43,44,45,46,47,48,49,50,51 };//スペードカードリスト
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
	std::list<int> Moved_Log;//ログ
	std::list<int> Empty_list;//カード配置時、空白のリストを入れる
	std::list<int> Empty_list4Types;//カード配置時、空白のリストを入れる。４種類の模様カード。
	std::list<int> Temp_list;//temp。移動させるときに使う、仮のリスト
	CImage heart[14];//ハートの赤
	CImage diamond[14];//ダイヤの赤
	CImage club[14];//クローバーの黒
	CImage spade[14];//スペードの黒
	CImage BehindCard;//トランプの背面の画像
	CImage m_img;//選択中の画像。Temp
	CVector2D MousePos;
	CImage AutoButton;
	CImage ScreenDesign;
	CImage BackGround;
	CImage Clear_Excellent;
	CImage Clear_Star;
	CImage Clear_Score;
	CImage Clear_Cloud;
	CFont PushEnter_Text;
public:
	BaseCard(int GameMode);
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
	//途中から動いているカードの表示
	void MiddleCardMovingDraw();
	//マウスが動かせるカードの上にあるかないか。
	//ある場合,	MouseOverCard=trueにする、ListNumを更新する。
	void InsideOrOutsideTheCard();
	//StockListとWaseteListの双方向移動
	void BothStockAndWaste();
	// カードから一定範囲内で、一番近いカードに置けるかどうか試して
	//置ける場合はそのリストの１番最後に追加
	// 
	//openリストにカードが有るかどうか確かめる。もしなかったら追加
	void OpenListCheckAndAdd();
	//左クリックを離したとき、動いてるカードがどこかのreserveリストに置けるかチェック。置けたらリスト移動
	void CheckAddToReserveList();
	//左クリックを離したとき、動いてるカードがどこかのFoundationリストに置けるかチェック。置けたらリスト移動
	void CheckAddToFoundationList();
	//ListNumのリストの最後を削除
	void RemoveFromListend(int ListNum);
	//ListNumのリストの最後に追加
	void AddToListend(int ListNum,int AddNum);
	//因数のListNumのリストがemptyか否か
	bool EmptyOrNotTheList(int ListNum);
	//リストの最初を削除
	void DeleteListFront(int ListNum);
	//リストの要素数を戻り値とする
	int CheckListSize(int ListNum);
	//もしKのカードなら、移動可能
	void MoveIfK();
	//通常モード。小さい方から順に配置していくモード。クリアできる可能性が高い
	void NormalMode();
	//ランダムモード。完全ランダム配置。クリア可能か不明
	void RandomMode();
	//Autoモード
	void AutoMode();
	//ログを追加する
	void AddToMoved_Log(int BeforeList,int Beforeard,int afterList,int afterCard);
	//すべてのreserveリストが空白ならtrue;
	bool CheckReserveEmpty();
	//ループしてたらtrueを返す
	bool LoopOrNot();
	//すべてのリストを初期化してカードを再配置
	void ReStartGame(bool);
	//クリアかどうかの判定
	bool ClearOrNot();
	//ユーザー操作に対する処理。
	void UserOperation();
	//カード配置時、空きのあるリストを調べる
	void AddEmptyList();
	//４種類のカードリストで空きのあるリストを調べる
	void AddEmpty4CardList();
	//デバッグ用。カードリストの出力
	void AllCardNumOutPut_debug();
	//デバッグ用。オートと手動切替可能。
	void DebugMode();
	//途中からreserveリストへ移動できるかどうかの判定（判定とリストの数字を入れるのみ）
	void Middle_Judgement_CheckAddToReserveList(int MovingLane);
	//途中から動かせるかどうかの判定。
	//可能な場合MiddleMovingCheck = true;
	//現在作成中・・・
	void Middle_CheckAddToReserveList();
	//マウスの位置はリストのN番目
	int MousePositionIsNthInTheList(int ListNum);
	//途中から動かせるかどうかの判定と、どこから動かせるか。動かせる場合true
	bool CheckIfItCanBeMovedFromTheMiddle();
};