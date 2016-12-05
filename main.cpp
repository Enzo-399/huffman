#include <iostream>

using namespace std;
const int MAX = 99;
char cha[MAX];
char hc[MAX - 1][MAX];
int s1, s2;                     //设置全局变量，以便在函数select中返回两个变量

typedef struct{                 //huffman树存储结构
    int weight;                 //权值
    int lchild;
    int rchild;
    int parent;
}huftree;

void select(huftree tree[],int k){
//找寻parent为0，权最小的两个节点
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}