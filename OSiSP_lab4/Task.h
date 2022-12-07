#pragma once
#include <vector>
#include <string>
class Task
{
public:
	Task(std::vector<std::string>* words);
	void Execute();
	std::vector<std::string>* GetResult();

private:
	std::vector<std::string>* _words;
};