#include "compressor.h"

compressor::compressor() {
	compressor::dataBuffer = 0;
}

void compressor::getBuffer(fileHandler *fHandler) {
	compressor::dataBuffer = fHandler->getBuffer();
}

void compressor::cHeapifier() {
	int bufLen = wcslen(L"A");
}

compressor::~compressor() {
	dataBuffer = 0;
}