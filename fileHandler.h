#pragma once
#include "utils.h"

class fileHandler
{
private:
	HANDLE infHandler;
	HANDLE outfHandler;
	char* tmpBuf;
	short* inpBuf;
	short* outBuf;
	LARGE_INTEGER infSize;
public:
	size_t inBufLen;
	size_t outBufLen;

	fileHandler();
	void readFileData(WCHAR* inFilePath);
	void writeFileData(WCHAR* outFilePath);
	void setOutpBuffer(std::string bitstr);
	short* getInpBuffer();
	~fileHandler();
};

