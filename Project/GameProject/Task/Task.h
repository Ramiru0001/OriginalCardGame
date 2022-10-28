#pragma once
#include <GLLibrary.h>

// タスクの優先度
enum class ETaskPrio
{
	eDefault,	// デフォルト
	eShell,		// 砲弾
	eTank,		// 戦車

	Num
};

// タスククラス
class Task
{
protected:
	int m_priority;	// 優先度

public:
	// コンストラクタ
	Task(int prio = (int)ETaskPrio::eDefault);
	// デストラクタ
	// （継承先でもデストラクタを使用するためvirtual化）
	virtual ~Task();

	// 優先度を取得
	int GetPriority() const;
	// 優先度を設定
	void SetPriority(int prio);

	// タスクを削除
	void Delete();

	// 更新（実処理は継承先で実装）
	virtual void Update(float deltaTime) = 0;
	// 描画（実処理は継承先で実装）
	virtual void Draw() = 0;
};