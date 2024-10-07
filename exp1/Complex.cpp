#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <chrono>

// 复数类定义
class Complex {
public:
    double real;
    double imag;

    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    double modulus() const {
        return std::sqrt(real * real + imag * imag);
    }

    bool operator==(const Complex& other) const {
        return (real == other.real) && (imag == other.imag);
    }

    // 用于排序：先按模排序，模相同则按实部排序
    bool operator<(const Complex& other) const {
        if (std::fabs(this->modulus() - other.modulus()) > 1e-9)
            return this->modulus() < other.modulus();
        return this->real < other.real;
    }

    // 输出复数
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << "(" << c.real << " + " << c.imag << "i)";
        return os;
    }
};

// 冒泡排序
void bubbleSort(std::vector<Complex>& vec) {
    size_t n = vec.size();
    bool swapped;
    for (size_t i = 0; i < n -1; ++i) {
        swapped = false;
        for (size_t j = 0; j < n - i -1; ++j) {
            if (vec[j] > vec[j+1]) {
                std::swap(vec[j], vec[j+1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

// 归并排序
void merge(std::vector<Complex>& vec, int left, int mid, int right) {
    int n1 = mid - left +1;
    int n2 = right - mid;
    std::vector<Complex> L(n1);
    std::vector<Complex> R(n2);
    for(int i=0;i<n1;i++) L[i] = vec[left + i];
    for(int i=0;i<n2;i++) R[i] = vec[mid +1 +i];
    int i=0, j=0, k=left;
    while(i < n1 && j < n2){
        if(L[i] < R[j]){
            vec[k++] = L[i++];
        }
        else{
            vec[k++] = R[j++];
        }
    }
    while(i < n1) vec[k++] = L[i++];
    while(j < n2) vec[k++] = R[j++];
}

void mergeSortHelper(std::vector<Complex>& vec, int left, int right){
    if(left < right){
        int mid = left + (right - left)/2;
        mergeSortHelper(vec, left, mid);
        mergeSortHelper(vec, mid+1, right);
        merge(vec, left, mid, right);
    }
}

void mergeSort(std::vector<Complex>& vec){
    if(vec.empty()) return;
    mergeSortHelper(vec, 0, vec.size()-1);
}

// 区间查找：返回模在 [m1, m2) 的所有元素
std::vector<Complex> intervalSearch(const std::vector<Complex>& vec, double m1, double m2){
    std::vector<Complex> result;
    for(const auto& c : vec){
        double mod = c.modulus();
        if(mod >= m1 && mod < m2){
            result.push_back(c);
        }
    }
    return result;
}

int main(){
    srand(time(0));

    // 生成随机复数向量（无序，允许重复）
    std::vector<Complex> vec;
    int n = 20; // 可以根据需要调整大小
    for(int i=0;i<n;i++){
        double r = (rand() % 100) / 10.0; // 0.0 到 9.9
        double im = (rand() % 100) / 10.0;
        vec.emplace_back(r, im);
    }

    std::cout << "初始复数向量:\n";
    for(const auto& c : vec) std::cout << c << " ";
    std::cout << "\n\n";

    // (1) 测试置乱、查找、插入、删除和唯一化

    // 置乱
    std::random_shuffle(vec.begin(), vec.end());
    std::cout << "置乱后的向量:\n";
    for(const auto& c : vec) std::cout << c << " ";
    std::cout << "\n\n";

    // 查找
    if(!vec.empty()){
        Complex target = vec[rand() % vec.size()]; // 随机选一个存在的复数
        std::cout << "查找复数: " << target << "\n";
        auto it = std::find(vec.begin(), vec.end(), target);
        if(it != vec.end()){
            std::cout << "找到复数 " << *it << " 在位置 " << std::distance(vec.begin(), it) << "\n";
        }
        else{
            std::cout << "未找到复数 " << target << "\n";
        }
    }
    std::cout << "\n";

    // 插入
    Complex newComplex(5.5, 5.5);
    vec.push_back(newComplex);
    std::cout << "插入 " << newComplex << " 后的向量:\n";
    for(const auto& c : vec) std::cout << c << " ";
    std::cout << "\n\n";

    // 删除
    if(!vec.empty()){
        Complex toDelete = vec[rand() % vec.size()];
        std::cout << "删除复数: " << toDelete << "\n";
        vec.erase(std::remove(vec.begin(), vec.end(), toDelete), vec.end());
        std::cout << "删除后的向量:\n";
        for(const auto& c : vec) std::cout << c << " ";
        std::cout << "\n\n";
    }

    // 唯一化
    // 首先排序，因为 std::unique 需要相邻重复元素
    std::sort(vec.begin(), vec.end(), [](const Complex& a, const Complex& b) {
        if (a.real != b.real)
            return a.real < b.real;
        return a.imag < b.imag;
    });
    auto uniqueEnd = std::unique(vec.begin(), vec.end());
    vec.erase(uniqueEnd, vec.end());
    std::cout << "唯一化后的向量:\n";
    for(const auto& c : vec) std::cout << c << " ";
    std::cout << "\n\n";

    // (2) 排序及效率比较
    // 准备三种顺序：顺序、乱序、逆序
    // 生成原始乱序向量
    std::vector<Complex> originalVec = vec;
    std::random_shuffle(originalVec.begin(), originalVec.end());

    // 顺序向量（按模和实部排序）
    std::vector<Complex> sortedVec = originalVec;
    std::sort(sortedVec.begin(), sortedVec.end());

    // 逆序向量
    std::vector<Complex> reverseVec = sortedVec;
    std::reverse(reverseVec.begin(), reverseVec.end());

    // 函数来测试排序算法
    auto testSort = [&](std::vector<Complex> data, const std::string& order) {
        std::cout << "排序顺序: " << order << "\n";

        // 冒泡排序
        std::vector<Complex> bubbleVec = data;
        auto start = std::chrono::high_resolution_clock::now();
        bubbleSort(bubbleVec);
        auto end = std::chrono::high_resolution_clock::now();
        auto bubbleTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        // 检查是否排序正确
        bool bubbleCorrect = std::is_sorted(bubbleVec.begin(), bubbleVec.end());

        // 归并排序
        std::vector<Complex> mergeVec = data;
        start = std::chrono::high_resolution_clock::now();
        mergeSort(mergeVec);
        end = std::chrono::high_resolution_clock::now();
        auto mergeTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        bool mergeCorrect = std::is_sorted(mergeVec.begin(), mergeVec.end());

        std::cout << "冒泡排序时间: " << bubbleTime << " 微秒"
                  << " 正确性: " << (bubbleCorrect ? "正确" : "错误") << "\n";
        std::cout << "归并排序时间: " << mergeTime << " 微秒"
                  << " 正确性: " << (mergeCorrect ? "正确" : "错误") << "\n\n";
    };

    // 测试顺序、乱序、逆序
    testSort(sortedVec, "顺序");
    testSort(originalVec, "乱序");
    testSort(reverseVec, "逆序");

    // (3) 区间查找
    // 首先确保向量已排序
    std::sort(vec.begin(), vec.end());
    double m1 = 5.0, m2 = 10.0;
    std::vector<Complex> intervalVec = intervalSearch(vec, m1, m2);
    std::cout << "模在 [" << m1 << ", " << m2 << ") 的元素:\n";
    for(const auto& c : intervalVec) std::cout << c << " ";
    std::cout << "\n";

    return 0;
}
