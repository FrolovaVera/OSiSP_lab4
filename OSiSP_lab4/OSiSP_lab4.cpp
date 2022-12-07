#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Handler.h"

int main()
{
    std::string path = "C:/Users/Vera/Desktop/3 курс/5 сем/осисп/OSiSP_lab4/file.txt", word;
    std::vector<std::string> words;
	std::vector<std::string> sortedWords;
	
	std::ifstream file(path);
	while (file >> word) {
		words.push_back(word);
	}

	Handler taskHandler;
	taskHandler.Sort(&words,&sortedWords,5);

	for (int i = 0; i < sortedWords.size(); i++) {
		std::cout << sortedWords[i] << std::endl;
	}

	return 0;

	
}

