#pragma once
#include "utils.h"

class fileHandler
{
private:
	HANDLE infHandler;
	HANDLE outfHandler;
	char* tmpBuf;
	char* outBuf;
	LARGE_INTEGER infSize;
public:
	fileHandler();
	void readFileData(WCHAR* inFilePath);
	void writeFileData(WCHAR* outFilePath);
	char* getOutpBuffer();
	char* getInpBuffer();
	~fileHandler();
};

