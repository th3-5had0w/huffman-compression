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
	compressor::chrMapTable = 0;
	//plus one for pseudo eof
	for (size_t i = 0; i < 256+1; ++i) {
		compressor::chrList[i] = new minHeapNode();
	}
}

//get buffer pointer from filehandler
void compressor::getBuffer(fileHandler *fHandler) {
	compressor::dataBuffer = fHandler->getInpBuffer();
	compressor::bufLength = fHandler->inBufLen+1;
	compressor::dataBuffer[compressor::bufLength-1] = 0x100;
}

void compressor::calcCharFrequency() {
	for (size_t i = 0; i < compressor::bufLength; ++i) {
		if (compressor::chrList[compressor::dataBuffer[i]]->chr == 0xdeadbeef) {
			compressor::chrList[compressor::dataBuffer[i]]->chr = compressor::dataBuffer[i];
		}
		compressor::chrList[compressor::dataBuffer[i]]->freq++;
	}
}

void compressor::huffmanCodeGen(minHeapNode* root, std::string str) {
	if (!root) {
		return;
	}

	if (root->chr != 0xcafe) {
		chrMapTable->insert(std::pair<size_t, std::string>(root->chr, str));
	}

	compressor::huffmanCodeGen(root->left, str + "0");
	compressor::huffmanCodeGen(root->right, str + "1");
}

void compressor::huffmanBuild() {
	minHeapNode* left, * right, * top;
	compressor::chrMapTable = new std::map<size_t, std::string>;
	// prerequisite class for priority queue data structure
	class compare {
	public:
		bool operator()(minHeapNode* l, minHeapNode* r) {
			return (l->freq > r->freq);
		}
	};

	// put all chars appear in data string into priority based on their frequencies
	std::priority_queue<minHeapNode*, std::vector<minHeapNode*>, compare> minHeap;
	for (size_t i = 0; i < 256+1; ++i) { // plus one for pseudo eof
		if (compressor::chrList[i]->chr != 0xdeadbeef) {
			minHeap.push(compressor::chrList[i]);
		}
	}

	// take the 2 smallest frequency nodes to form a new subtree
	// repeat again and again until there's only one node left in the queue (root node)
	// idea: http://web.stanford.edu/class/archive/cs/cs106x/cs106x.1174/assnFiles/assign6/huffman-encoding-supplement.pdf
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
	compressor::huffmanCodeGen(minHeap.top(), "");
}

std::string compressor::createFromChrMapTable() {
	std::map <size_t, std::string>::iterator j;
	for (size_t i = 0; i < compressor::bufLength; ++i) {
		for (j = chrMapTable->begin(); j != chrMapTable->end(); ++j) {
			if (j->first == compressor::dataBuffer[i]) {
				compressor::bitstr += j->second;
				break;
			}
		}
	}

	//padding up to a number that is a multiple of 8 (1 * n bytes)
	while ((compressor::bitstr.size() & 0x7) != 0) {
		compressor::bitstr += "0";
	}
	std::cout << compressor::bitstr << std::endl;
	return compressor::bitstr;
}

//destructor
compressor::~compressor() {
	compressor::dataBuffer = 0;
	compressor::bufLength = 0;
}