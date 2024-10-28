#include <iostream>  
#include <vector>  
#include <stack>  
#include <algorithm>  
  
using namespace std;  
  
// �������������ڼ����Ե�ǰ�߶�Ϊ��׼�����������  
int largestRectangleArea(vector<int>& heights) {  
    stack<int> stk; // ʹ��ջ���洢���ӵ�����  
    int maxArea = 0;  
    int n = heights.size();  
    vector<int> left(n, -1), right(n, n); // left[i]��ʾi��ߵ�һ����heights[i]С�����ӵ�������right[i]ͬ��  
  
    // ����ÿ��������ߵ�һ������С�����ӵ�����  
    for (int i = 0; i < n; ++i) {  
        while (!stk.empty() && heights[stk.top()] >= heights[i]) {  
            stk.pop();  
        }  
        if (!stk.empty()) {  
            left[i] = stk.top();  
        }  
        stk.push(i);  
    }  
  
    // ���ջ��������ÿ�������ұߵ�һ������С�����ӵ�����  
    while (!stk.empty()) {  
        stk.pop();  
    }  
    for (int i = n - 1; i >= 0; --i) {  
        while (!stk.empty() && heights[stk.top()] >= heights[i]) {  
            stk.pop();  
        }  
        if (!stk.empty()) {  
            right[i] = stk.top();  
        }  
        stk.push(i);  
    }  
  
    // �������������  
    for (int i = 0; i < n; ++i) {  
        maxArea = max(maxArea, (right[i] - left[i] - 1) * heights[i]);  
    }  
  
    return maxArea;  
}  
  
int main() {  
    // ʾ�����룬���Դ��ļ�����������Դ��ȡ  
    vector<int> heights = {2, 1, 5, 6, 2, 3};  
  
    // �������������  
    int maxArea = largestRectangleArea(heights);  
  
    // ������  
    cout << "The largest rectangle area is: " << maxArea << endl;  
  
    return 0;  
}
