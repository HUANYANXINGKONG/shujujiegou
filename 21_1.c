//全排列的递归实现（教材21页题目二）
//此处全排列为数列的不同顺序所有组合方式
//选做内容：1）去掉重复的全排列递归实现 2）全排列的非递归实现
#include <stdio.h>

//交换两个字符
void swap(char *a,char *b)
{
    char temp= *a;
    *a=*b;
    *b=temp;
}
//打印排列
void print(char str[],int n)
{
    for (int i=0; i<n; i++) 
    {
        printf("%c",str[i]);
    }
    printf(" ");
}
//可能存在重复的递归算法
void digui(char* str,int start,int end)
{
    if(start==end)//当start=end时，表示一个排列完成
    {
        print(str,end+1);
        return;
    }
    for(int i=start;i<=end;i++)
    {
        swap(&str[start],&str[i]);
        digui(str,start+1,end);
        swap(&str[start],&str[i]);//回溯
    }
}
//去掉重复的全排列递归实现
void qcdigui(char* str,int start,int end)
{
    if(start==end)
    {
        print(str,end+1);
        return;
    }
    int used[256]={0};//使用数组记录已经交换过的字符
    for(int i=start;i<=end;i++)
    {
        if(used[(int)str[i]]==1)
        {
            continue;//如果该字符已经交换过，则跳过
        }
        used[(int)str[i]]=1;//标记该字符已经交换过
        swap(&str[start],&str[i]);
        qcdigui(str,start+1,end);
        swap(&str[start],&str[i]);//回溯
    }
}

// 反转字符串中从start到end的部分
void reverse(char str[], int start, int end) {
    while (start < end) {
        swap(&str[start], &str[end]);
        start++;
        end--;
    }
}
// 生成下一个排列
int nextPermutation(char str[], int len)
{
    int i, j;
    // 从右向左找到第一个str[i] < str[i+1]的位置
    for (i = len - 2; i >= 0; i--)
    {
        if (str[i] < str[i + 1])
        {
            break;
        }
    }
    // 如果找不到，说明已经是最后一个排列
    if (i < 0)
    {
        return 0;
    }
    // 从右向左找到第一个大于str[i]的元素str[j]
    for (j = len - 1; j > i; j--)
    {
        if (str[j] > str[i])
        {
            break;
        }
    }
    // 交换str[i]和str[j]
    swap(&str[i], &str[j]);
    // 反转从i+1到末尾的部分
    reverse(str, i + 1, len - 1);
    return 1;
}
//全排列的非递归实现
void feidigui(char* str,int len)
{
    // 先对字符串进行排序（使用冒泡排序）
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 0; j < len - i - 1; j++) 
        {
            if (str[j] > str[j + 1])
            {
                swap(&str[j], &str[j + 1]);
            }
        }
    }
    // 输出第一个排列
    print(str, len);
    // 不断生成下一个排列
    while (nextPermutation(str, len)) 
    {
        print(str, len);
    }
}
int main()
{
    char input[100];
    int len=0;
    int end;
    printf("请输入一个字符串,不多于100个字符\n");
    scanf("%s",input);
    while (input[len]!='\0') {len++;}//len为输入字符串的长度
    end=len-1;
    printf("可能存在重复的全排列结果如下:\n");
    digui(input,0,end);
    printf("\n去掉重复的全排列结果如下:\n");
    qcdigui(input,0,end);
    printf("\n非递归实现的全排列结果如下:\n");
    feidigui(input,len);
}
