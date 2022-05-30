#pragma once
#include "utils.h"

class fileHandler
{
private:
	HANDLE infHandler;
	HANDLE outfHandler;
	WCHAR* tmpBuf;
	WCHAR* outBuf;
	LARGE_INTEGER infSize;
public:
	fileHandler();
	void readFileData(WCHAR* inFilePath);
	void writeFileData(WCHAR* outFilePath);
	WCHAR* getOutpBuffer();
	WCHAR* getInpBuffer();
	~fileHandler();
};

