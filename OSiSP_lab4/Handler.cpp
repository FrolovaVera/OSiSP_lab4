#include "Handler.h"
#include <thread>
#include "ThreadPool.h"

std::vector<std::string>* MergeVectors(std::vector<std::string>* v1, std::vector<std::string>* v2);
void MergeTasks(ThreadPool* threadPool, std::vector<std::string>* out, int tasksCount);


void Handler::Sort(std::vector<std::string>* in, std::vector<std::string>* out, int threadsCount) {
	ThreadPool pool(threadsCount);

	if (!(in->size() && threadsCount)) {
		return;
	}

	int numWordsInTask = ceil((double)in->size() / threadsCount);
	int taskCount = ceil((double)in->size() / numWordsInTask);

	Task* newTask;
	for (int i = 0; i < taskCount;++i) {

		std::vector<std::string>* currStr = new std::vector<std::string>(in->begin()+i*numWordsInTask, in->size() < (i + 1) * numWordsInTask ? in->end() : in->begin() + (i + 1) * numWordsInTask);
		newTask = new Task(currStr);
		pool.AddTask(newTask);
	}
	std::thread outThread(MergeTasks, &pool, out, taskCount);
	outThread.join();
}

void MergeTasks(ThreadPool* threadPool, std::vector<std::string>* out, int tasksCount) {
	Task* task = ((Task*)threadPool->GetReadyTask());
	std::vector<std::string>* _vector = task->GetResult();

	std::vector<std::string>* result(_vector);
	for (int i = 1; i < tasksCount; i++)
	{
		task = ((Task*)threadPool->GetReadyTask());
		_vector = task->GetResult();

		result = MergeVectors(result, _vector);
	}
	*out = *result;
}

std::vector<std::string>* MergeVectors(std::vector<std::string>* v1, std::vector<std::string>* v2)
{
	int i = 0, j = 0;
	std::vector<std::string>* res = new std::vector<std::string>();
	while (i < v1->size() && j < v2->size()) {
		if (v1->at(i).compare(v2->at(j)) > 0) {
			res->push_back(v2->at(j));
			j++;
		}
		else {
			res->push_back(v1->at(i));
			i++;
		}
	}
	while (i < v1->size())
		res->push_back(v1->at(i++));
	while (j < v2->size())
		res->push_back(v2->at(j++));
	return res;
}