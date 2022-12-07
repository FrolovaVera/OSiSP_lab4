#include "QueueOfTasks.h"
QueueOfTasks::QueueOfTasks() {
	_empty = true;
	_closed = false;
	InitializeCriticalSection(&criticalSection);
}
QueueOfTasks::~QueueOfTasks() {

	DeleteCriticalSection(&criticalSection);
}


Task* QueueOfTasks::Extract() {

	while (_empty == true && _closed == false) {}
	EnterCriticalSection(&criticalSection);

	if (_closed && !_tasks.size()) {
		LeaveCriticalSection(&criticalSection);
		return nullptr;
	}

	Task* task = _tasks.front(); //шзвлекаем первую задачу из очереди и выполн€ем ее
	_tasks.erase(_tasks.begin()); //удал€ем из очереди

	if (!_tasks.size()) {
		_empty = true;
	}
	LeaveCriticalSection(&criticalSection);

	return task;
}

void QueueOfTasks::Close() {
	_closed = true;
}

void QueueOfTasks::Add(Task* task) {//добавление задачи в очередь, которую обрабатывают потоки
	EnterCriticalSection(&criticalSection);//ќжидает владени€ указанным объектом критической секции.
	_tasks.push_back(task);

	_empty = false;
	LeaveCriticalSection(&criticalSection);

}