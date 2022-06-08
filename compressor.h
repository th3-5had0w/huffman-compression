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
	minHeapNode** chrList; // plus one for pseudo eof
	std::map<size_t, std::string>* chrMapTable;
	std::string bitstr;

	// prerequisite class for priority queue data structure's comparison
	class compare {
	public:
		bool operator()(minHeapNode* l, minHeapNode* r) {
			return (l->freq > r->freq);
		}
	};

	std::priority_queue<minHeapNode*, std::vector<minHeapNode*>, compare> minHeap; // every single char appeared in data string goes into priority queue based on their frequencies
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