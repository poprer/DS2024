#include <iostream>  
#include <vector>  
#include <stack>  
#include <algorithm>  
  
using namespace std;  
  
// 辅助函数，用于计算以当前高度为基准的最大矩形面积  
int largestRectangleArea(vector<int>& heights) {  
    stack<int> stk; // 使用栈来存储柱子的索引  
    int maxArea = 0;  
    int n = heights.size();  
    vector<int> left(n, -1), right(n, n); // left[i]表示i左边第一个比heights[i]小的柱子的索引，right[i]同理  
  
    // 计算每个柱子左边第一个比它小的柱子的索引  
    for (int i = 0; i < n; ++i) {  
        while (!stk.empty() && heights[stk.top()] >= heights[i]) {  
            stk.pop();  
        }  
        if (!stk.empty()) {  
            left[i] = stk.top();  
        }  
        stk.push(i);  
    }  
  
    // 清空栈，并计算每个柱子右边第一个比它小的柱子的索引  
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
  
    // 计算最大矩形面积  
    for (int i = 0; i < n; ++i) {  
        maxArea = max(maxArea, (right[i] - left[i] - 1) * heights[i]);  
    }  
  
    return maxArea;  
}  
  
int main() {  
    // 示例输入，可以从文件或其他输入源获取  
    vector<int> heights = {2, 1, 5, 6, 2, 3};  
  
    // 计算最大矩形面积  
    int maxArea = largestRectangleArea(heights);  
  
    // 输出结果  
    cout << "The largest rectangle area is: " << maxArea << endl;  
  
    return 0;  
}
