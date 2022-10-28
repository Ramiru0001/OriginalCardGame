#include "TaskManager.h"

// TaskManagerのインスタンスを定義
TaskManager* TaskManager::ms_instance = nullptr;

// コンストラクタ
TaskManager::TaskManager()
{
}

// デストラクタ
TaskManager::~TaskManager()
{
	// タスクリストに登録されているタスクを全て削除
	for (int i = 0; i < m_taskList.size(); i++)
	{
		Task* task = m_taskList[i];
		delete task;
	}
	m_taskList.clear();
}

// TaskManagerのインスタンスを取得
TaskManager* TaskManager::Instance()
{
	// インスタンスが生成されていなければ生成
	if (ms_instance == nullptr)
	{
		ms_instance = new TaskManager();
	}
	return ms_instance;
}

// TaskManagerのインスタンスを破棄
void TaskManager::ClearInstance()
{
	if (ms_instance == nullptr) return;
	delete ms_instance;
	ms_instance = nullptr;
}

// タスクをリストに追加
void TaskManager::AddTask(Task* task)
{
	m_addList.push_back(task);
}

// 追加するタスクを反映
void TaskManager::AddTaskList()
{
	for (int i = 0; i < m_addList.size(); i++)
	{
		// 追加するタスク
		Task* addTask = m_addList[i];
		bool isAdd = false;

		// 追加するタスクの優先度をみてリストに追加
		auto begin = m_taskList.begin();
		auto end = m_taskList.end();
		for (auto it = begin; it != end; ++it)
		{
			// 追加するタスクの優先度の方が小さい場合は
			// そこにタスクを追加
			if (addTask->GetPriority() < (*it)->GetPriority())
			{
				m_taskList.insert(it, addTask);
				isAdd = true;
				break;
			}
		}
		if (!isAdd)
		{
			// ここに来た場合は優先度が一番高いので
			// リストの最後に追加
			m_taskList.push_back(addTask);
		}
	}
	m_addList.clear();
}

// タスクをリストから外す
void TaskManager::RemoveTask(Task* task)
{
	m_removeList.push_back(task);
}

// 取り除くタスクを反映
void TaskManager::RemoveTaskList()
{
	for (int i = 0; i < m_removeList.size(); i++)
	{
		Task* removeTask = m_removeList[i];

		// リスト内から取り除くタスクを検索
		auto begin = m_taskList.begin();
		auto end = m_taskList.end();
		auto find = std::find(begin, end, removeTask);
		// 見つからなければ次へ
		if (find == m_taskList.end()) continue;

		// 見つかればリストから取り除く
		m_taskList.erase(find);
	}
	m_removeList.clear();
}

// タスクを削除してリストから取り除く
void TaskManager::DeleteTask(Task* task)
{
	m_deleteList.push_back(task);

	// 削除リストに追加されたタスクは
	// 追加タスクのリストから取り除く
	{
		auto begin = m_addList.begin();
		auto end = m_addList.end();
		auto find = std::find(begin, end, task);
		if (find != end) m_addList.erase(find);
	}
	// 取り除くリストからも取り除く
	{
		auto begin = m_removeList.begin();
		auto end = m_removeList.end();
		auto find = std::find(begin, end, task);
		if (find != end) m_removeList.erase(find);
	}
}

// 削除するタスクを反映
void TaskManager::DeleteTaskList()
{
	for (int i = 0; i < m_deleteList.size(); i++)
	{
		Task* deleteTask = m_deleteList[i];

		// リスト内から削除するタスクを検索
		auto begin = m_taskList.begin();
		auto end = m_taskList.end();
		auto find = std::find(begin, end, deleteTask);
		// 見つかればリストから取り除く
		if (find != m_taskList.end())
		{
			m_taskList.erase(find);
		}

		// タスクを削除
		delete deleteTask;
	}
	m_deleteList.clear();
}

// 更新
void TaskManager::Update()
{
	// 削除するリストに
	// 登録されているタスクを削除
	DeleteTaskList();
	// 取り除くリストに
	// 登録されているタスクをリストから取り除く
	RemoveTaskList();
	// 追加リストに
	// 登録されているタスクをリストに追加
	AddTaskList();

	// リストに登録されている全てのタスクを更新
	for (int i = 0; i < m_taskList.size(); i++)
	{
		m_taskList[i]->Update(CFPS::GetDeltaTime());
	}
}

// 描画
void TaskManager::Draw()
{
	// リストに登録されている全てのタスクを描画
	for (int i = 0; i < m_taskList.size(); i++)
	{
		m_taskList[i]->Draw();
	}
}