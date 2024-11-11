#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>
#include <functional>

// Huffman���Ľڵ�ṹ
struct HuffmanNode {
    char ch;            // �����Ҷ�ӽڵ㣬�洢�ַ�
    int freq;           // Ƶ��
    HuffmanNode* left;  // ���ӽڵ�
    HuffmanNode* right; // ���ӽڵ�

    // ���캯��
    HuffmanNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}

    // �ȽϺ������������ȶ���
    bool operator>(const HuffmanNode& other) const {
        return freq > other.freq;
    }
};

// ����Huffman��
HuffmanNode* buildHuffmanTree(const std::unordered_map<char, int>& freqMap) {
    // ʹ�����ȶ��У���С�ѣ�������Huffman��
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, std::greater<HuffmanNode*>> minHeap;

    // �������ַ��ڵ�������ȶ���
    for (const auto& pair : freqMap) {
        minHeap.push(new HuffmanNode(pair.first, pair.second));
    }

    // �ϲ��ڵ�ֱ��ֻʣ��һ�����ڵ�
    while (minHeap.size() > 1) {
        HuffmanNode* left = minHeap.top();
        minHeap.pop();
        HuffmanNode* right = minHeap.top();
        minHeap.pop();

        // �����µ��ڲ��ڵ㣬Ƶ��Ϊ�����ӽڵ�Ƶ��֮��
        HuffmanNode* newNode = new HuffmanNode('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        // ���½ڵ�������ȶ���
        minHeap.push(newNode);
    }

    // ���ظ��ڵ�
    return minHeap.top();
}

// ����Huffman����
void generateHuffmanCodes(HuffmanNode* root, const std::string& str, std::unordered_map<char, std::string>& huffmanCodes) {
    // �����Ҷ�ӽڵ㣬�洢����
    if (!root->left && !root->right) {
        huffmanCodes[root->ch] = str;
    }
    else {
        // �ݹ������������������
        generateHuffmanCodes(root->left, str + "0", huffmanCodes);
        generateHuffmanCodes(root->right, str + "1", huffmanCodes);
    }
}

// ��ӡHuffman����
void printHuffmanCodes(const std::unordered_map<char, std::string>& huffmanCodes) {
    for (const auto& pair : huffmanCodes) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

// �ͷ�Huffman��ռ�õ��ڴ�
void freeHuffmanTree(HuffmanNode* root) {
    if (!root) return;
    freeHuffmanTree(root->left);
    freeHuffmanTree(root->right);
    delete root;
}

int main() {
    // ʾ���ַ�Ƶ�ʣ���Ӧ�ô������ж�ȡ��Щֵ��
    std::unordered_map<char, int> freqMap = {
        {'d', 4},
        {'r', 2},
        {'e', 3},
        {'a', 1},
        {'m', 2}
    };

    // ����Huffman��
    HuffmanNode* root = buildHuffmanTree(freqMap);

    // ����Huffman����
    std::unordered_map<char, std::string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);

    // ��ӡHuffman����
    printHuffmanCodes(huffmanCodes);

    // �ͷ�Huffman��ռ�õ��ڴ�
    freeHuffmanTree(root);

    return 0;
}