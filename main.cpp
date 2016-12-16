#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <iostream>
typedef struct {
    char ch;
    unsigned int weight;
    unsigned int parent, lchild, rchild;
} HTNode, *HuffmanTree;             //动态分配数组存储哈夫曼树
typedef char **HuffmanCode;         //动态分配数组存储哈夫曼编码表
int wei[27] = {186, 64, 13, 22, 32, 103, 21, 15, 47, 57, 1, 5, 32, 20, 57, 63, 15, 1, 48, 51,
               80, 23, 8, 18, 1, 16, 1};  //186为空格的权值
int flag[54];
static int n, m;
HuffmanTree HT;
HuffmanCode HC;

void Select(HuffmanTree HT, int j, int &s1, int &s2) {
    //在1到j中选择双亲为0并且weight最小的两个叶子结点，其序号分别为s1，s2
    int mark = 0;
    for (int i = 1; i <= j; i++)         //for循环找到权值最小的节点
    {
        if (flag[i] == 0 && mark == 0)        //第一次 把第一个flag未改变的节点编号给s1
        {
            s1 = i;
            mark = 1;
        } else if (HT[i].weight < HT[s1].weight && flag[i] == 0) {
            s1 = i;                       //通过循环把最小权值节点给S1
        }
    }
    mark = 0;                   //mark 归零
    flag[s1] = 1;               //把s1节点的标记改为1
    for (int i = 1; i <= j; i++) {
        if (flag[i] == 0 && mark == 0) {
            s2 = i;
            mark = 1;
        } else if (HT[i].weight < HT[s2].weight && flag[i] == 0) {
            s2 = i;
        }
    }
    flag[s2] = 1;
}

void HuffmanCoding(HuffmanTree &HT, int w[], int s, char *ch)   //****M*****哈夫曼树初始化进行对字母编码
{
    n = s;
    int i, j, s1, s2, start;
    char *cd;
    unsigned int c, f;
    for (i = 0; i < s * 2; i++) {
        flag[i] = 0;                                        //每个对应节点标记为0 选择最小节点时 被选中标记为1
    }
    if (n <= 1) return;
    m = 2 * n - 1;                                          //n个叶子 2*n-1个节点
    HT = (HuffmanTree) malloc((m + 1) * sizeof(HTNode));    //0号单元未用
    for (i = 1; i <= n; i++)                                //哈夫曼树初始化
    {
        HT[i].weight = (unsigned int) w[i - 1];             //w[]对应的权值依次赋给HT每一个叶子节点
        HT[i].ch = ch[i - 1];                               //ch[]对应的字母依次赋给每一个叶子节点
        HT[i].parent = 0;
        HT[i].lchild = 0;
        HT[i].rchild = 0;
    }
    for (; i <= m; i++) {
            HT[i].weight = 0;
            HT[i].parent = 0;
            HT[i].lchild = 0;
            HT[i].rchild = 0;
            HT[i].ch = ' ';
    }
    printf("\n哈夫曼树的构造过程如下所示\n");
    for (i = n + 1; i <= m; i++)                 //构建哈夫曼树
    {
        Select(HT, i - 1, s1, s2);
        HT[s1].parent = (unsigned int) i;
        HT[s2].parent = (unsigned int) i;
        HT[i].lchild = (unsigned int) s1;
        HT[i].rchild = (unsigned int) s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
    printf("\n  结点 char  weight  parent  lchild  rchild");
    for (j = 1; j <= i - 1; j++)
        printf("\n%4d%6c%8d%8d%8d%8d", j, HT[j].ch, HT[j].weight, HT[j].parent, HT[j].lchild,
               HT[j].rchild);
//--- 从叶子到根逆向求每个字符的哈夫曼编码 ---
    HC = (HuffmanCode) malloc((n + 1) * sizeof(char *));
    cd = (char *) malloc(n * sizeof(char));
    cd[n - 1] = '\0';
    for (i = 1; i <= n; ++i) {
        start = n - 1;
        for (c = (unsigned int) i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
            if (HT[f].lchild == c)
                cd[--start] = '0';
            else
                cd[--start] = '1';
        HC[i] = (char *) malloc((n - start) * sizeof(char));
        strcpy(HC[i], &cd[start]);
    }
    printf("\n每个字母对应的哈夫曼编码:\n");
    for (int a = 1; a <= n; a++) {
        printf("%c:", HT[a].ch);
        printf("%s  ", HC[a]);
        if (a % 5 == 0)
            printf("\n");
    }
    printf("\n");
    free(cd);
}

void Initialization()             //******I用户自定义权值和字符*****
{
    int n, weight[50];
    char ch[50];
    printf("请输入权值个数>>:");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {

        printf("请输入第%d个字母及对应的权值:", i + 1);
        scanf("%s %d", &ch[i], &weight[i]);
    }
    HuffmanCoding(HT, weight, n, ch);

}

void Encoding()                   //*******E编码**********
{
    char str[50];
    int j;
    if (HT == NULL) {
        printf("请先进行初始化!\n");
        return;
    }
    printf("请输入要编码的文本(小写英文字母):\n");
    std::cin >> str;
    printf("编码结果如下:\n");
    int p = strlen(str);
    for (int i = 1; i <= p; i++) {
        for (j = 1; j <= n; j++) {
            if (str[i - 1] == HT[j].ch) {
                printf("%s", HC[j]);
                break;
            }
        }
    }
    printf("\n");
}

void Decoding()              //*******D译码**********
{
    int i = 1, j, key;
    char str[100];
    if (HT == NULL) {
        printf("请先进行初始化!\n");
        return;
    }

    printf("\n每个字母对应的哈夫曼编码:\n");
    for (int a = 1; a <= n; a++) {
        printf("%c:", HT[a].ch);
        printf("%s  ", HC[a]);
        if (a % 5 == 0)
            printf("\n");
    }

    printf("\n请输入哈夫曼编码:\n");
    scanf("%s", str);
    j = strlen(str);
    key = m;
    printf("哈夫曼编码译码如下:\n");
    while (i <= j) {
        while (HT[key].lchild != 0) {
            if (str[i - 1] == '0') {
                key = HT[key].lchild;
                i++;
                continue;
            }
            if (str[i - 1] == '1') {
                    key = HT[key].rchild;
                    i++;
                    continue;
            }

        }
        printf("%c", HT[key].ch);
        key = m;
    }

    printf("\n");
}

int main() {
    char num;
    char *str = (char *) " abcdefghijklmnopqrstuvwxyz";
    while (1) {
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("     ************** 赫夫曼编码/译码器 *************\n");
        printf("     *************M  使用默认初始化   *************\n");
        printf("     *************I 使用自定义初始化  *************\n");
        printf("     *************E       编码       *************\n");
        printf("     *************D       译码       *************\n");
        printf("     *************C       退出       *************\n");

        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("请输入您要操作的步骤:");
        std::cin >> num;
        switch (num) {
            case 'M':
                HuffmanCoding(HT, wei, 27, str);
                break;
            case 'I':
                Initialization();
                break;
            case 'E' :
                Encoding();
                break;
            case 'D' :
                Decoding();
                break;
            case 'C' :
                exit(0);
            default:break;
        }
    }
}