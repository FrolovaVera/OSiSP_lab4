#include "Task.h"
#include <algorithm>

Task::Task(std::vector<std::string>* words) : _words(words)
{
}

void Task::Execute() {
	std::sort(_words->begin(), _words->end());
}
std::vector<std::string>* Task::GetResult() {
	return _words;
}