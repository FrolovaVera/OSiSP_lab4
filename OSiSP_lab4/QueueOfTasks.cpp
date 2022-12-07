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

	Task* task = _tasks.front(); //��������� ������ ������ �� ������� � ��������� ��
	_tasks.erase(_tasks.begin()); //������� �� �������

	if (!_tasks.size()) {
		_empty = true;
	}
	LeaveCriticalSection(&criticalSection);

	return task;
}

void QueueOfTasks::Close() {
	_closed = true;
}

void QueueOfTasks::Add(Task* task) {//���������� ������ � �������, ������� ������������ ������
	EnterCriticalSection(&criticalSection);//������� �������� ��������� �������� ����������� ������.
	_tasks.push_back(task);

	_empty = false;
	LeaveCriticalSection(&criticalSection);

}