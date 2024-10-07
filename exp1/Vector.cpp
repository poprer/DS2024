#ifndef VECTOR_CPP
#define VECTOR_CPP
//#include "Vector.h"
#include <stdexcept> // std::out_of_range

// ���캯��
template <typename T>
Vector<T>::Vector(int c, int s, T v) : _size(s), _capacity(c) {
    if (c < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
    _elem = new T[_capacity];
    for (_size = 0; _size < s; _elem[_size++] = v);
}

// �������帴��
template <typename T>
Vector<T>::Vector(T const* A, Rank n) {
    copyFrom(A, 0, n);
}

// ���临��
template <typename T>
Vector<T>::Vector(T const* A, Rank lo, Rank hi) {
    copyFrom(A, lo, hi);
}

// �������帴��
template <typename T>
Vector<T>::Vector(Vector<T> const& V) {
    copyFrom(V._elem, 0, V._size);
}

// �������临��
template <typename T>
Vector<T>::Vector(Vector<T> const& V, Rank lo, Rank hi) {
    copyFrom(V._elem, lo, hi);
}

// ��������
template <typename T>
Vector<T>::~Vector() {
    delete[] _elem;
}

// ������������ A[lo, hi)
template <typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) {
    if (lo < 0 || hi > (int)sizeof(A)/sizeof(A[0]) || lo > hi)
        throw std::out_of_range("copyFrom: invalid lo or hi");
    _elem = new T[_capacity = 2*(hi - lo)];
    _size = 0;
    for (Rank i = lo; i < hi; ++i)
        _elem[_size++] = A[i];
}

// ����
template <typename T>
void Vector<T>::expand() {
    if (_size < _capacity) return; // ���пռ�
    _capacity = _capacity << 1; // �ӱ�
    T* oldElem = _elem;
    _elem = new T[_capacity];
    for (Rank i = 0; i < _size; ++i)
        _elem[i] = oldElem[i];
    delete[] oldElem;
}

// ѹ��
template <typename T>
void Vector<T>::shrink() {
    if (_capacity < DEFAULT_CAPACITY << 1) return; // ��������ѹ��
    if (_size << 2 > _capacity) return; // װ��������Ȼ�ϸ�
    _capacity = _capacity >> 1;
    T* oldElem = _elem;
    _elem = new T[_capacity];
    for (Rank i = 0; i < _size; ++i)
        _elem[i] = oldElem[i];
    delete[] oldElem;
}

// �ж������Ƿ�������
template <typename T>
int Vector<T>::disordered() const {
    int n = 0;
    for (Rank i = 1; i < _size; ++i)
        if (_elem[i-1] > _elem[i]) ++n;
    return n;
}

// ���������������
template <typename T>
Rank Vector<T>::find(T const& e) const {
    return find(e, 0, _size);
}

// ���������������
template <typename T>
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const {
    while ((lo < hi--) && (e != _elem[hi]));
    return hi;
}

// ���������������
template <typename T>
Rank Vector<T>::search(T const& e) const {
    return (_size > 0) ? search(e, 0, _size) : -1;
}

// ���������������
template <typename T>
Rank Vector<T>::search(T const& e, Rank lo, Rank hi) const {
    // ���ֲ���
    while (lo < hi) {
        Rank mi = (lo + hi) / 2;
        if (e < _elem[mi]) hi = mi;
        else lo = mi + 1;
    }
    return --lo;
}

// �����±������
template <typename T>
T& Vector<T>::operator[](Rank r) const {
    if (r < 0 || r >= _size)
        throw std::out_of_range("Vector index out of range");
    return _elem[r];
}

// ���ظ�ֵ������
template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const& V) {
    if (_elem) delete[] _elem;
    copyFrom(V._elem, 0, V._size);
    return *this;
}

// ɾ����Ϊ r ��Ԫ��
template <typename T>
T Vector<T>::remove(Rank r) {
    if (r < 0 || r >= _size)
        throw std::out_of_range("remove: invalid rank");
    T e = _elem[r];
    for (Rank i = r; i < _size - 1; ++i)
        _elem[i] = _elem[i + 1];
    --_size;
    shrink();
    return e;
}

// ɾ���������� [lo, hi) ֮�ڵ�Ԫ��
template <typename T>
int Vector<T>::remove(Rank lo, Rank hi) {
    if (lo < 0 || hi > _size || lo > hi)
        throw std::out_of_range("remove: invalid lo or hi");
    if (lo == hi) return 0;
    while (hi < _size)
        _elem[lo++] = _elem[hi++];
    int removed = hi - lo;
    _size = lo;
    shrink();
    return removed;
}

// ����Ԫ��
template <typename T>
Rank Vector<T>::insert(Rank r, T const& e) {
    if (r < 0 || r > _size)
        throw std::out_of_range("insert: invalid rank");
    expand();
    for (Rank i = _size; i > r; --i)
        _elem[i] = _elem[i - 1];
    _elem[r] = e;
    ++_size;
    return r;
}

// Ĭ����ΪĩԪ�ز���
template <typename T>
Rank Vector<T>::insert(T const& e) {
    return insert(_size, e);
}

// ȥ��(��������)
template <typename T>
int Vector<T>::deduplicate() {
    int oldSize = _size;
    Rank i = 1;
    while (i < _size)
        (find(_elem[i], 0, i) < 0) ? ++i : remove(i);
    return oldSize - _size;
}

// ȥ��(��������)
template <typename T>
int Vector<T>::uniquify() {
    if (_size < 2) return 0;
    Rank i = 1, j = 1;
    while (++i < _size)
        if (_elem[i - 1] != _elem[i])
            _elem[j++] = _elem[i];
    int removed = _size - j;
    _size = j;
    shrink();
    return removed;
}

// ���������㷨
template <typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi) {
    while (!bubble(lo, hi--));
}

// ɨ�轻��
template <typename T>
bool Vector<T>::bubble(Rank lo, Rank hi) {
    bool sorted = true;
    while (++lo < hi)
        if (_elem[lo - 1] > _elem[lo]) {
            std::swap(_elem[lo - 1], _elem[lo]);
            sorted = false;
        }
    return sorted;
}

// ѡ�������㷨
template <typename T>
void Vector<T>::selectionSort(Rank lo, Rank hi) {
    for (Rank i = lo; i < hi - 1; ++i) {
        Rank maxRank = max(lo, hi);
        std::swap(_elem[maxRank], _elem[hi - 1]);
    }
}

// ѡȡ���Ԫ��
template <typename T>
Rank Vector<T>::max(Rank lo, Rank hi) {
    Rank maxRank = lo;
    for (Rank i = lo + 1; i < hi; ++i)
        if (_elem[i] > _elem[maxRank])
            maxRank = i;
    return maxRank;
}

// �鲢�����㷨
template <typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi) {
    if (hi - lo < 2) return;
    Rank mi = (lo + hi) / 2;
    mergeSort(lo, mi);
    mergeSort(mi, hi);
    merge(lo, mi, hi);
}

// �鲢�㷨
template <typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {
    T* A = _elem + lo;
    int lb = mi - lo;
    T* B = new T[lb];
    for (int i = 0; i < lb; ++i)
        B[i] = A[i];
    int lc = hi - mi;
    T* C = _elem + mi;
    int i = 0, j = 0, k = 0;
    while (j < lb && k < lc)
        A[i++] = (B[j] <= C[k]) ? B[j++] : C[k++];
    while (j < lb)
        A[i++] = B[j++];
    while (k < lc)
        A[i++] = C[k++];
    delete[] B;
}

// ���������㷨
template <typename T>
void Vector<T>::quickSort(Rank lo, Rank hi) {
    if (hi - lo < 2) return;
    Rank mi = partition(lo, hi);
    quickSort(lo, mi);
    quickSort(mi + 1, hi);
}

// ��㹹���㷨
template <typename T>
Rank Vector<T>::partition(Rank lo, Rank hi) {
    std::swap(_elem[lo], _elem[lo + std::rand() % (hi - lo)]);
    T pivot = _elem[lo];
    while (lo < hi) {
        while (lo < hi && _elem[--hi] >= pivot);
        if (lo < hi) _elem[lo] = _elem[hi];
        while (lo < hi && _elem[++lo] <= pivot);
        if (lo < hi) _elem[hi] = _elem[lo];
    }
    _elem[lo] = pivot;
    return lo;
}

// �������㷨
template <typename T>
void Vector<T>::heapSort(Rank lo, Rank hi) {
    // ������
    // ʡ��ʵ�֣���Ϊʾ��
}

// ����ӿ�
template <typename T>
void Vector<T>::sort(Rank lo, Rank hi) {
    // ѡ��һ�������㷨�������Կ�������Ϊ��
    quickSort(lo, hi);
}

// ��������
template <typename T>
void Vector<T>::sort() {
    sort(0, _size);
}

// ����
template <typename T>
void Vector<T>::unsort(Rank lo, Rank hi) {
    std::srand(unsigned(std::time(0)));
    for (Rank i = lo; i < hi; ++i)
        std::swap(_elem[i], _elem[lo + std::rand() % (hi - lo)]);
}

// ��������
template <typename T>
void Vector<T>::unsort() {
    unsort(0, _size);
}

// ����(ʹ�ú���ָ��)
template <typename T>
void Vector<T>::traverse(void (*visit)(T&)) {
    for (Rank i = 0; i < _size; ++i)
        visit(_elem[i]);
}

// ����(ʹ�ú�������)
template <typename T>
template <typename VST>
void Vector<T>::traverse(VST& visit) {
    for (Rank i = 0; i < _size; ++i)
        visit(_elem[i]);
}

#endif // VECTOR_CPP

