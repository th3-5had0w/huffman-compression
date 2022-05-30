#pragma once
#include "utils.h"
#include "fileHandler.h"

class compressor
{
private:
	char* dataBuffer;
	size_t bufLength;
public:
	compressor();
	void getBuffer(fileHandler *fHandler);
	void cHeapifier(size_t root);
	~compressor();
};