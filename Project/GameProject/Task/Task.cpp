#include "Task.h"
#include "TaskManager.h"

// コンストラクタ
Task::Task(int prio)
	: m_priority(prio)
{
	// タスク管理クラスに自身を追加
	TaskManager::Instance()->AddTask(this);
}

// デストラクタ
Task::~Task()
{
	// タスク管理クラスから自身を取り除く
	TaskManager::Instance()->RemoveTask(this);
}

// 優先度を取得
int Task::GetPriority() const
{
	return m_priority;
}

// 優先度を設定
void Task::SetPriority(int prio)
{
	// 新しい優先度に変更してから、
	// タスクをリストから取り除き、再度リストに追加することで、
	// 新しい優先度の位置にタスクを配置
	m_priority = prio;
	TaskManager::Instance()->RemoveTask(this);
	TaskManager::Instance()->AddTask(this);
}

// タスクを削除
void Task::Delete()
{
	TaskManager::Instance()->DeleteTask(this);
}