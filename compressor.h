#pragma once
#include "utils.h"
#include "fileHandler.h"

class compressor
{
private:
	WCHAR* dataBuffer;
	size_t bufLength;
public:
	compressor();
	void getBuffer(fileHandler *fHandler);
	void cHeapifier(size_t root);
	~compressor();
};