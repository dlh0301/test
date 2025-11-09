// huffman.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

template <typename E, typename Weight>
struct TreeNode {
    E data;
    Weight freq;
    TreeNode* left, * right;

    TreeNode(E data, Weight freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};

template <typename E, typename Weight>
struct Compare {
    bool operator()(TreeNode<E, Weight>* l, TreeNode<E, Weight>* r) {
        return l->freq > r->freq;
    }
};

// 根据给定的数组，生成哈夫曼编码树，返回根节点
template <typename E, typename Weight>
TreeNode<E, Weight>* generateHuffmanTree(std::vector<std::pair<E, Weight>>& freqVec, E invalid) {
    std::priority_queue<TreeNode<E, Weight>*, std::vector<TreeNode<E, Weight>*>, Compare<E, Weight>> pq;

    for (auto& pair : freqVec) {
        pq.push(new TreeNode<E, Weight>(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        TreeNode<E, Weight>* left = pq.top(); pq.pop();
        TreeNode<E, Weight>* right = pq.top(); pq.pop();

        TreeNode<E, Weight>* sum = new TreeNode<E, Weight>(invalid, left->freq + right->freq);
        sum->left = left;
        sum->right = right;

        pq.push(sum);
    }

    return pq.top();
}
// 根据哈夫曼编码树的根节点，得到每种叶子结点的具体编码
template <typename E>
void generateCode(TreeNode<E, int>* root, string code, map<E, string>& huffmanCode) {
    if (!root) return;

    if (root->left == nullptr && root->right == nullptr) {
        huffmanCode[root->data] = code;
    }

    generateCode(root->left, code + "0", huffmanCode);
    generateCode(root->right, code + "1", huffmanCode);
}

TreeNode<char, int>* GenHuffTreeByConfigFile(FILE* fp1, FILE* fp2) {
    std::map<char, std::string> huffmanCode;
    char c;
    std::string code;
    char buffer[256];

    // 从fp2读取字符和编码
    while (fscanf(fp2, "%c: ", &c) != EOF) {
        if (fgets(buffer, sizeof(buffer), fp2)) {
            std::string code(buffer);
            // 去除字符串末尾的换行符
            code.erase(std::remove(code.begin(), code.end(), '\n'), code.end());
            huffmanCode[c] = code;
    }

    // 重建哈夫曼树
    TreeNode<char, int>* root = nullptr;
    TreeNode<char, int>* current = nullptr;
    std::string path;

    // 从fp1读取树的结构
    while (fscanf(fp1, "%c", &c) != EOF) {
        if (c == '0') {
            if (!current) {
                current = new TreeNode<char, int>('0', 0);
                if (!root) root = current;
            }
            current = current->left;
        }
        else if (c == '1') {
            if (!current) {
                current = new TreeNode<char, int>('1', 0);
                if (!root) root = current;
            }
            current = current->right;
        }
        else if (c == '\n') { // 假设每行代表一个完整的路径
            current->data = path.back();
            current->freq = 1; // 假设重建的树中每个字符的频率为1
            current = root;
            path.clear();
        }
        else {
            path.push_back(c);
        }
    }

    return root;
}

    void storeHuffmanTree(TreeNode<char, int>*root, const std::string & treeFilePath, const std::string & codeFilePath) {
        std::ofstream treeFile(treeFilePath);
        std::ofstream codeFile(codeFilePath);

        if (!treeFile.is_open() || !codeFile.is_open()) {
            std::cerr << "无法打开文件来存储哈夫曼树和编码" << std::endl;
            return;
        }

        // 存储编码
        std::map<char, std::string> huffmanCode;
        generateCode(root, "", huffmanCode);

        for (const auto& pair : huffmanCode) {
            codeFile << pair.first << ": " << pair.second << std::endl;
        }

        // 存储树结构
        std::vector<TreeNode<char, int>*> stack;
        stack.push_back(root);
        while (!stack.empty()) {
            TreeNode<char, int>* node = stack.back();
            stack.pop_back();

            if (node->left) {
                treeFile << "0 ";
                stack.push_back(node->left);
            }
            if (node->right) {
                treeFile << "1 ";
                stack.push_back(node->right);
            }
            if (!node->left && !node->right) { // 叶子节点
                treeFile << node->data << std::endl;
            }
        }

        treeFile.close();
        codeFile.close();
    }

// 读取文本文件中一行数据
bool readLine(FILE* file, std::string& line) {
    line.clear();
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        line.append(buffer);
    }
    return line.length() > 0;
}

// 根据文件路径压缩文件
using namespace std;

// 前面定义的 TreeNode, generateHuffmanTree, generateCode 等结构和函数

// 比较器，用于优先队列
template <typename E, typename Weight>
struct Compare {
    bool operator()(TreeNode<E, Weight>* l, TreeNode<E, Weight>* r) {
        return l->freq > r->freq;
    }
};

bool compress(const char* filename) {
    map<char, int> freq;
    FILE* file = fopen(filename, "r");
    if (!file) {
        cerr << "无法打开文件: " << filename << endl;
        return false;
    }

    string line;
    while (readLine(file, line)) {
        for (char c : line) {
            freq[c]++;
        }
    }
    fclose(file);

    vector<pair<char, int>> freqVec(freq.begin(), freq.end());
    TreeNode<char, int>* root = generateHuffmanTree(freqVec, '\0');

    map<char, string> huffmanCode;
    generateCode(root, "", huffmanCode);

    storeHuffmanTree(root, "huffman_tree.txt", "huffman_codes.txt");

    file = fopen(filename, "r");
    ofstream outFile("compressed_" + string(filename), ios::binary);
    if (!file) {
        cerr << "无法打开文件: " << filename << endl;
        return false;
    }

    while (readLine(file, line)) {
        for (char c : line) {
            if (huffmanCode.find(c) != huffmanCode.end()) {
                outFile << huffmanCode[c];
            }
        }
    }
    fclose(file);
    outFile.close();

    ofstream treeFile("huffman_tree_" + string(filename));
    for (const auto& pair : huffmanCode) {
        treeFile << pair.first << ": " << pair.second << endl;
    }
    treeFile.close();

    return true;
}

TreeNode<char, int>* buildHuffmanTree(const std::map<char, std::string>& huffmanCode) {
    std::priority_queue<TreeNode<char, int>*, std::vector<TreeNode<char, int>*>, Compare<char, int>> pq;

    // 创建叶子节点
    for (const auto& pair : huffmanCode) {
        pq.push(new TreeNode<char, int>(pair.first, 1));
    }

    // 构建哈夫曼树
    while (pq.size() > 1) {
        TreeNode<char, int>* left = pq.top(); pq.pop();
        TreeNode<char, int>* right = pq.top(); pq.pop();

        TreeNode<char, int>* sum = new TreeNode<char, int>('\0', left->freq + right->freq);
        sum->left = left;
        sum->right = right;

        pq.push(sum);
    }

    return pq.top();
}

bool uncompress(const char* compressedFilename) {
    std::string configFilename = "huffman_tree_" + std::string(compressedFilename);
    std::map<char, std::string> huffmanCode;

    // 从配置文件读取哈夫曼编码
    std::ifstream configFile(configFilename);
    char c;
    std::string code;
    while (configFile >> c >> code) {
        huffmanCode[c] = code;
    }
    configFile.close();

    // 重建哈夫曼树
    TreeNode<char, int>* root = buildHuffmanTree(huffmanCode);

    // 读取压缩文件
    std::ifstream inFile(compressedFilename, std::ios::binary);
    std::string compressedData((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    inFile.close();

    // 解码
    std::string decoded;
    std::string currentCode;
    for (char bit : compressedData) {
        currentCode += bit;
        if (root->left && root->right) {
            if (bit == '0') root = root->left;
            else root = root->right;
        }
        else {
            decoded += root->data;
            currentCode.clear();
            root = buildHuffmanTree(huffmanCode); // 重置树为根节点
        }
    }

    // 写入解压后的文件
    std::ofstream outFile("decompressed_" + std::string(compressedFilename));
    outFile << decoded;
    outFile.close();

    // 清理内存
    deleteTree(root);

    return true;
}

void deleteTree(TreeNode<char, int>* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}


int main() {
    int choice;
    std::string filePath;

    while (true) {
        std::cout << "1. 压缩文件" << std::endl;
        std::cout << "2. 解压文件" << std::endl;
        std::cout << "3. 退出" << std::endl;
        std::cout << "请输入操作：";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "请输入目标文件路径：";
            std::cin.ignore(); // 忽略之前留在输入缓冲区的换行符
            std::getline(std::cin, filePath);
            if (compress(filePath.c_str())) {
                std::cout << "压缩完成" << std::endl;
            }
            else {
                std::cout << "压缩失败" << std::endl;
            }
            break;
        case 2:
            std::cout << "请输入已压缩文件路径：";
            std::cin.ignore(); // 忽略之前留在输入缓冲区的换行符
            std::getline(std::cin, filePath);
            if (uncompress(filePath.c_str())) {
                std::cout << "解压完成" << std::endl;
            }
            else {
                std::cout << "解压失败" << std::endl;
            }
            break;
        case 3:
            std::cout << "程序退出" << std::endl;
            return 0;
        default:
            std::cout << "无效的操作，请输入1、2或3." << std::endl;
        }

        std::cout << std::endl;
    }

    return 0;
}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
