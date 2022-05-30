#pragma once
#include "utils.h"
#include "fileHandler.h"

struct charFreq {
	size_t chr = 0xdeadbeef;
	size_t freq = 0;
};

class minHeapNode {
public:
	size_t chr;
	size_t freq;
	minHeapNode* left, * right;
	minHeapNode();
	minHeapNode(size_t chr, size_t freq);
};
/*
struct MinHeapNode {

	// One of the input characters
	char data;

	// Frequency of the character
	unsigned freq;

	MinHeapNode* left, * right;

	MinHeapNode(char data, unsigned freq)
	{

		left = right = NULL;
		this->data = data;
		this->freq = freq;
	}
};
*/
class compressor
{
private:
	char* dataBuffer;
	size_t bufLength;
	minHeapNode** chrList = new minHeapNode * [256];
public:
	compressor();
	void getBuffer(fileHandler *fHandler);
	void calcCharFrequency();
	void huffmanBuild();
	void cHeapifier(size_t root);
	~compressor();
};

class decompressor : public compressor {
private:
public:
	decompressor();
	~decompressor();
};