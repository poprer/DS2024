#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <chrono>

// �����ඨ��
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

    // ���������Ȱ�ģ����ģ��ͬ��ʵ������
    bool operator<(const Complex& other) const {
        if (std::fabs(this->modulus() - other.modulus()) > 1e-9)
            return this->modulus() < other.modulus();
        return this->real < other.real;
    }

    // �������
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << "(" << c.real << " + " << c.imag << "i)";
        return os;
    }
};

// ð������
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

// �鲢����
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

// ������ң�����ģ�� [m1, m2) ������Ԫ��
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

    // ��������������������������ظ���
    std::vector<Complex> vec;
    int n = 20; // ���Ը�����Ҫ������С
    for(int i=0;i<n;i++){
        double r = (rand() % 100) / 10.0; // 0.0 �� 9.9
        double im = (rand() % 100) / 10.0;
        vec.emplace_back(r, im);
    }

    std::cout << "��ʼ��������:\n";
    for(const auto& c : vec) std::cout << c << " ";
    std::cout << "\n\n";

    // (1) �������ҡ����ҡ����롢ɾ����Ψһ��

    // ����
    std::random_shuffle(vec.begin(), vec.end());
    std::cout << "���Һ������:\n";
    for(const auto& c : vec) std::cout << c << " ";
    std::cout << "\n\n";

    // ����
    if(!vec.empty()){
        Complex target = vec[rand() % vec.size()]; // ���ѡһ�����ڵĸ���
        std::cout << "���Ҹ���: " << target << "\n";
        auto it = std::find(vec.begin(), vec.end(), target);
        if(it != vec.end()){
            std::cout << "�ҵ����� " << *it << " ��λ�� " << std::distance(vec.begin(), it) << "\n";
        }
        else{
            std::cout << "δ�ҵ����� " << target << "\n";
        }
    }
    std::cout << "\n";

    // ����
    Complex newComplex(5.5, 5.5);
    vec.push_back(newComplex);
    std::cout << "���� " << newComplex << " �������:\n";
    for(const auto& c : vec) std::cout << c << " ";
    std::cout << "\n\n";

    // ɾ��
    if(!vec.empty()){
        Complex toDelete = vec[rand() % vec.size()];
        std::cout << "ɾ������: " << toDelete << "\n";
        vec.erase(std::remove(vec.begin(), vec.end(), toDelete), vec.end());
        std::cout << "ɾ���������:\n";
        for(const auto& c : vec) std::cout << c << " ";
        std::cout << "\n\n";
    }

    // Ψһ��
    // ����������Ϊ std::unique ��Ҫ�����ظ�Ԫ��
    std::sort(vec.begin(), vec.end(), [](const Complex& a, const Complex& b) {
        if (a.real != b.real)
            return a.real < b.real;
        return a.imag < b.imag;
    });
    auto uniqueEnd = std::unique(vec.begin(), vec.end());
    vec.erase(uniqueEnd, vec.end());
    std::cout << "Ψһ���������:\n";
    for(const auto& c : vec) std::cout << c << " ";
    std::cout << "\n\n";

    // (2) ����Ч�ʱȽ�
    // ׼������˳��˳����������
    // ����ԭʼ��������
    std::vector<Complex> originalVec = vec;
    std::random_shuffle(originalVec.begin(), originalVec.end());

    // ˳����������ģ��ʵ������
    std::vector<Complex> sortedVec = originalVec;
    std::sort(sortedVec.begin(), sortedVec.end());

    // ��������
    std::vector<Complex> reverseVec = sortedVec;
    std::reverse(reverseVec.begin(), reverseVec.end());

    // ���������������㷨
    auto testSort = [&](std::vector<Complex> data, const std::string& order) {
        std::cout << "����˳��: " << order << "\n";

        // ð������
        std::vector<Complex> bubbleVec = data;
        auto start = std::chrono::high_resolution_clock::now();
        bubbleSort(bubbleVec);
        auto end = std::chrono::high_resolution_clock::now();
        auto bubbleTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        // ����Ƿ�������ȷ
        bool bubbleCorrect = std::is_sorted(bubbleVec.begin(), bubbleVec.end());

        // �鲢����
        std::vector<Complex> mergeVec = data;
        start = std::chrono::high_resolution_clock::now();
        mergeSort(mergeVec);
        end = std::chrono::high_resolution_clock::now();
        auto mergeTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        bool mergeCorrect = std::is_sorted(mergeVec.begin(), mergeVec.end());

        std::cout << "ð������ʱ��: " << bubbleTime << " ΢��"
                  << " ��ȷ��: " << (bubbleCorrect ? "��ȷ" : "����") << "\n";
        std::cout << "�鲢����ʱ��: " << mergeTime << " ΢��"
                  << " ��ȷ��: " << (mergeCorrect ? "��ȷ" : "����") << "\n\n";
    };

    // ����˳����������
    testSort(sortedVec, "˳��");
    testSort(originalVec, "����");
    testSort(reverseVec, "����");

    // (3) �������
    // ����ȷ������������
    std::sort(vec.begin(), vec.end());
    double m1 = 5.0, m2 = 10.0;
    std::vector<Complex> intervalVec = intervalSearch(vec, m1, m2);
    std::cout << "ģ�� [" << m1 << ", " << m2 << ") ��Ԫ��:\n";
    for(const auto& c : intervalVec) std::cout << c << " ";
    std::cout << "\n";

    return 0;
}
