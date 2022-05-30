#include "compressor.h"

minHeapNode::minHeapNode() {
	minHeapNode::chr = 0xdeadbeef;
	minHeapNode::freq = 0;
	left = right = NULL;
}

minHeapNode::minHeapNode(size_t chr, size_t freq) {
	minHeapNode::chr = chr;
	minHeapNode::freq = freq;
	left = right = NULL;
}

//constructor
compressor::compressor() {
	compressor::dataBuffer = 0;
	compressor::bufLength = 0;
	for (size_t i = 0; i < 256; ++i) {
		compressor::chrList[i] = new minHeapNode();
	}
}

//get buffer pointer from filehandler
void compressor::getBuffer(fileHandler *fHandler) {
	compressor::dataBuffer = fHandler->getInpBuffer();
	compressor::bufLength = fHandler->inBufLen;
}

void compressor::calcCharFrequency() {
	for (size_t i = 0; i < compressor::bufLength; ++i) {
		if (compressor::chrList[compressor::dataBuffer[i]]->chr == 0xdeadbeef) {
			compressor::chrList[compressor::dataBuffer[i]]->chr = compressor::dataBuffer[i];
		}
		compressor::chrList[compressor::dataBuffer[i]]->freq++;
	}
}

void compressor::huffmanBuild() {
	minHeapNode* left, * right, * top;

	class compare {
	public:
		bool operator()(minHeapNode* l, minHeapNode* r) {
			return (l->freq > r->freq);
		}
	};

	std::priority_queue<minHeapNode*, std::vector<minHeapNode*>, compare> minHeap;
	for (size_t i = 0; i < 256; ++i) {
		if (compressor::chrList[i]->chr != 0xdeadbeef) {
			minHeap.push(compressor::chrList[i]);
		}
	}

	while (minHeap.size() != 1) {
		left = minHeap.top();
		minHeap.pop();
		right = minHeap.top();
		minHeap.pop();

		top = new minHeapNode(0xcafe, left->freq + right->freq);
		top->left = left;
		top->right = right;
		minHeap.push(top);
	}

}

/*
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
*/
//destructor
compressor::~compressor() {
	compressor::dataBuffer = 0;
	compressor::bufLength = 0;
}