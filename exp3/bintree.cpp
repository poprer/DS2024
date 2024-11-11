#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>
#include <functional>

// Huffman树的节点结构
struct HuffmanNode {
    char ch;            // 如果是叶子节点，存储字符
    int freq;           // 频率
    HuffmanNode* left;  // 左子节点
    HuffmanNode* right; // 右子节点

    // 构造函数
    HuffmanNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}

    // 比较函数，用于优先队列
    bool operator>(const HuffmanNode& other) const {
        return freq > other.freq;
    }
};

// 构建Huffman树
HuffmanNode* buildHuffmanTree(const std::unordered_map<char, int>& freqMap) {
    // 使用优先队列（最小堆）来构建Huffman树
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, std::greater<HuffmanNode*>> minHeap;

    // 将所有字符节点加入优先队列
    for (const auto& pair : freqMap) {
        minHeap.push(new HuffmanNode(pair.first, pair.second));
    }

    // 合并节点直到只剩下一个根节点
    while (minHeap.size() > 1) {
        HuffmanNode* left = minHeap.top();
        minHeap.pop();
        HuffmanNode* right = minHeap.top();
        minHeap.pop();

        // 创建新的内部节点，频率为左右子节点频率之和
        HuffmanNode* newNode = new HuffmanNode('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        // 将新节点加入优先队列
        minHeap.push(newNode);
    }

    // 返回根节点
    return minHeap.top();
}

// 生成Huffman编码
void generateHuffmanCodes(HuffmanNode* root, const std::string& str, std::unordered_map<char, std::string>& huffmanCodes) {
    // 如果是叶子节点，存储编码
    if (!root->left && !root->right) {
        huffmanCodes[root->ch] = str;
    }
    else {
        // 递归遍历左子树和右子树
        generateHuffmanCodes(root->left, str + "0", huffmanCodes);
        generateHuffmanCodes(root->right, str + "1", huffmanCodes);
    }
}

// 打印Huffman编码
void printHuffmanCodes(const std::unordered_map<char, std::string>& huffmanCodes) {
    for (const auto& pair : huffmanCodes) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

// 释放Huffman树占用的内存
void freeHuffmanTree(HuffmanNode* root) {
    if (!root) return;
    freeHuffmanTree(root->left);
    freeHuffmanTree(root->right);
    delete root;
}

int main() {
    // 示例字符频率（你应该从输入中读取这些值）
    std::unordered_map<char, int> freqMap = {
        {'d', 4},
        {'r', 2},
        {'e', 3},
        {'a', 1},
        {'m', 2}
    };

    // 构建Huffman树
    HuffmanNode* root = buildHuffmanTree(freqMap);

    // 生成Huffman编码
    std::unordered_map<char, std::string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);

    // 打印Huffman编码
    printHuffmanCodes(huffmanCodes);

    // 释放Huffman树占用的内存
    freeHuffmanTree(root);

    return 0;
}