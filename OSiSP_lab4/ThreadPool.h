#pragma once
#include "QueueOfTasks.h"
#include <thread>
#include "Task.h"

class ThreadPool
{
public:
	ThreadPool(int threads);
	~ThreadPool();
	void AddTask(Task* task);
	Task* GetReadyTask();

private:
	std::vector<std::thread*> _threads;
	void ThreadFunc();
	QueueOfTasks _taskQueue;
	QueueOfTasks _readyTaskQueue;
};
