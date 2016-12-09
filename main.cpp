#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
    char ch;
    unsigned int weight;
    unsigned int parent, lchild, rchild;
} HTNode, *HuffmanTree;
typedef char **HuffmanCode;
int wei[27] = {186, 64, 13, 22, 32, 103, 21, 15, 47, 57, 1, 5, 32, 20, 57, 63, 15, 1, 48, 51,
               80, 23, 8, 18, 1, 16, 1};  //186Ϊ�ո��Ȩֵ
int flag[54];
static int n, m;
HuffmanTree HT;
HuffmanCode HC;

void Select(HuffmanTree HT, int j, int &s1, int &s2) {
    //��1��j��ѡ��˫��Ϊ0����weight��С������Ҷ�ӽ�㣬����ŷֱ�Ϊs1��s2
    int i, mark = 0;
    for (i = 1; i <= j; i++)         //forѭ���ҵ�Ȩֵ��С�Ľڵ�
    {
        if (flag[i] == 0 && mark == 0)        //��һ�� �ѵ�һ��flagδ�ı�Ľڵ��Ÿ�s1
        {
            s1 = i;
            mark = 1;
        } else if (HT[i].weight < HT[s1].weight && flag[i] == 0) {
            s1 = i;                       //ͨ��ѭ������СȨֵ�ڵ��S1
        }
    }
    mark = 0;                   //mark ����
    flag[s1] = 1;               //��s1�ڵ�ı�Ǹ�Ϊ1
    for (i = 1; i <= j; i++) {
        if (flag[i] == 0 && mark == 0) {
            s2 = i;
            mark = 1;
        } else if (HT[i].weight < HT[s2].weight && flag[i] == 0) {
            s2 = i;
        }
    }
    flag[s2] = 1;
}

void HuffmanCoding(HuffmanTree &HT, int w[], int s, char *ch)   //****1*****��������ʼ�����ж���ĸ����
{
    n = s;
    int i, j, s1, s2, start;
    char *cd;
    unsigned int c, f;
    for (i = 0; i < s * 2; i++) {
        flag[i] = 0;          //ÿ����Ӧ�ڵ���Ϊ0 ѡ����С�ڵ�ʱ ��ѡ�б��Ϊ1
    }
    if (n <= 1) return;
    m = 2 * n - 1;                             //n����Ҷ 2*n-1���ڵ�
    HT = (HuffmanTree) malloc((m + 1) * sizeof(HTNode));//0�ŵ�Ԫδ��
    for (i = 1; i <= n; i++)        //����������ʼ��
    {
        HT[i].weight = w[i - 1];                         //w[]��Ӧ��Ȩֵ���θ���HTÿһ��Ҷ�ӽڵ�
        HT[i].ch = ch[i - 1];       //ch[]��Ӧ����ĸ���θ��� ûһ��Ҷ�ӽڵ�
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
    printf("\n���������Ĺ������������ʾ��\n");
    for (i = n + 1; i <= m; i++)                 //������������
    {

        Select(HT, i - 1, s1, s2);
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
    printf("\n  ��� char  weight  parent  lchild  rchild");
    for (j = 1; j <= i - 1; j++)

        printf("\n%4d%6c%8d%8d%8d%8d", j, HT[j].ch, HT[j].weight, HT[j].parent, HT[j].lchild,
               HT[j].rchild);
//--- ��Ҷ�ӵ���������ÿ���ַ��Ĺ��������� ---
    HC = (HuffmanCode) malloc((n + 1) * sizeof(char *));
    cd = (char *) malloc(n * sizeof(char));
    cd[n - 1] = '\0';
    for (i = 1; i <= n; ++i) {
        start = n - 1;
        for (c = (unsigned int) i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
            if (HT[f].lchild == c) cd[--start] = '0';
            else cd[--start] = '1';
        HC[i] = (char *) malloc((n - start) * sizeof(char));
        strcpy(HC[i], &cd[start]);
    }
    printf("\nÿ����ĸ��Ӧ�Ĺ���������:\n");
    for (int a = 1; a <= n; a++) {
        printf("%c:", HT[a].ch);
        printf("%s  ", HC[a]);
        if (a % 5 == 0)
            printf("\n");
    }
    printf("\n");
    free(cd);
}

void Customize()             //******2�û��Զ���Ȩֵ���ַ�*****
{
    int n, weight[50];
    char ch[50];
    printf("������Ȩֵ����>1:");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {

        printf("�������%d����ĸ����Ӧ��Ȩֵ:", i + 1);
        scanf("%s %d", &ch[i], &weight[i]);
    }
    HuffmanCoding(HT, weight, n, ch);

}

void TexttoCode()                   //*******3����**********
{
    char str[50];
    int j;
    if (HT == NULL) {
        printf("���Ƚ��г�ʼ��!\n");
        return;
    }
    printf("������Ҫ������ı�(СдӢ����ĸ):\n");
    gets(str);
    printf("����������:\n");
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

void CodetoText()              //*******4����**********
{
    int i = 1, j, key;
    char str[100];
    if (HT == NULL) {
        printf("���Ƚ��г�ʼ��!\n");
        return;
    }

    printf("\nÿ����ĸ��Ӧ�Ĺ���������:\n");
    for (int a = 1; a <= n; a++) {
        printf("%c:", HT[a].ch);
        printf("%s  ", HC[a]);
        if (a % 5 == 0)
            printf("\n");
    }

    printf("\n���������������:\n");
    scanf("%s", str);
    j = strlen(str);
    key = m;
    printf("������������������:\n");
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
    int num;
    char *str = (char *) " abcdefghijklmnopqrstuvwxyz";  //
    while (1) {

        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("     *************�շ�������/������  *************\n");
        printf("     *************1 ʹ��Ĭ�ϳ�ʼ��   *************\n");
        printf("     *************2 ʹ���Զ����ʼ�� *************\n");
        printf("     *************3       ����       *************\n");
        printf("     *************4       ����       *************\n");
        printf("     *************5       �˳�       *************\n");

        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("��������Ҫ�����Ĳ���:");
        scanf("%d", &num);
        getchar();
        switch (num) {
            case 1 :
                HuffmanCoding(HT, wei, 27, str);
                break;
            case 2:
                Customize();
                break;
            case 3 :
                TexttoCode();
                break;
            case 4 :
                CodetoText();
                break;
            case 5 :
                exit(0);
            default:break;
        }
    }
    return 0;
}