#include <iostream>

using namespace std;
const int MAX = 99;
char cha[MAX];
char hc[MAX - 1][MAX];
int s1, s2;                     //����ȫ�ֱ������Ա��ں���select�з�����������

typedef struct{                 //huffman���洢�ṹ
    int weight;                 //Ȩֵ
    int lchild;
    int rchild;
    int parent;
}huftree;

void select(huftree tree[],int k){
//��ѰparentΪ0��Ȩ��С�������ڵ�
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}