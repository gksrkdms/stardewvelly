#pragma once
#include "singletonBase.h"
#include <vector>
#include <string>

class DataManager : public singletonBase<DataManager>
{
	public:
		//std::vector<string> txtLoad

	public:
		HRESULT init();
		void release();

		// ���̺� 
		void txtSave(const char* saveFileName, std::vector<std::string> vecStr);
		char* vectorArrayCombine(std::vector<std::string> vecArray);

		// �ε�
		std::vector<std::string> txtLoad(const char* loadFileName);
		std::vector<std::string> charArraySeparation(char charArray[]);



public:
	DataManager();
	~DataManager();
};

