#include "compressor.h"

compressor::compressor() {
	compressor::dataBuffer = 0;
	compressor::bufLength = 0;
}

void compressor::getBuffer(fileHandler *fHandler) {
	compressor::dataBuffer = fHandler->getInpBuffer();
	compressor::bufLength = strlen(compressor::dataBuffer);
}

void compressor::cHeapifier(size_t root = 0) {
	size_t bufLen = compressor::bufLength;
	size_t largest = root;
	size_t i = bufLen / 2 - 1;
	size_t leftNode = root * 2 + 1;
	size_t rightNode = root * 2 + 2;
	if (leftNode < bufLen) {
		if (compressor::dataBuffer[leftNode] > largest) {
			std::swap(compressor::dataBuffer[largest], compressor::dataBuffer[leftNode]);
			largest = leftNode;
		}
		cHeapifier(leftNode);
	}
	if (rightNode < bufLen) {
		if (compressor::dataBuffer[rightNode] > largest) {
			std::swap(compressor::dataBuffer[largest], compressor::dataBuffer[rightNode]);
			largest = rightNode;
		}
		cHeapifier(rightNode);
	}
}

compressor::~compressor() {
	dataBuffer = 0;
	bufLength = 0;
}