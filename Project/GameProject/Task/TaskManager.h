#pragma once
#include <vector>
#include "Task.h"

// タスク管理クラス
class TaskManager
{
private:
	// TaskManagerのインスタンス
	static TaskManager* ms_instance;
	// 生成されたタスクのリスト
	std::vector<Task*> m_taskList;
	// リストに追加するタスクのリスト
	std::vector<Task*> m_addList;
	// リストから取り除くタスクのリスト
	std::vector<Task*> m_removeList;
	// リストから削除するタスクのリスト
	std::vector<Task*> m_deleteList;

	// 追加するタスクを反映
	void AddTaskList();
	// 取り除くタスクを反映
	void RemoveTaskList();
	// 削除するタスクを反映
	void DeleteTaskList();

public:
	// コンストラクタ
	TaskManager();
	// デストラクタ
	~TaskManager();

	// TaskManagerのインスタンスを取得
	static TaskManager* Instance();
	// TaskManagerのインスタンスを破棄
	static void ClearInstance();

	// タスクをリストに追加
	void AddTask(Task* task);
	// タスクをリストから取り除く
	void RemoveTask(Task* task);
	// タスクを削除してリストから取り除く
	void DeleteTask(Task* task);

	// 更新
	void Update();
	// 描画
	void Draw();
};
