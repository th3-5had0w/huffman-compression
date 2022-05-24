#pragma once
#include "utils.h"
#include "fileHandler.h"

class compressor
{
private:
	WCHAR* dataBuffer;
public:
	compressor();
	void getBuffer(fileHandler *fHandler);
	void cHeapifier();
	~compressor();
};