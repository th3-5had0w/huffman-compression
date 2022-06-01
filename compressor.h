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

class compressor
{
private:
	short* dataBuffer;
	size_t bufLength;
	minHeapNode** chrList = new minHeapNode * [256+1]; // plus one for pseudo eof
	std::map<size_t, std::string>* chrMapTable;
	std::string bitstr = "";
	void huffmanCodeGen(minHeapNode* root, std::string str);
public:
	compressor();
	void getBuffer(fileHandler *fHandler);
	void calcCharFrequency();
	void huffmanBuild();
	std::string createFromChrMapTable();
	~compressor();
};

class decompressor : public compressor {
private:
public:
	decompressor();
	~decompressor();
};