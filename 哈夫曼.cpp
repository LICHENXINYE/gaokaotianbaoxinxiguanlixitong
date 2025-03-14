#include<stdio.h> // EOF(=^Z或F6),NULL
#include<stdlib.h> // srand( ) ,rand( ),exit(n)
#include<malloc.h> // malloc( ),alloc( ),realloc( )等
#include<limits.h> // INT_MAX等
#include<string.h>
#include<ctype.h>
#include<math.h> // floor(),ceil( ),abs( )
#include<iostream> // cout,cin
using namespace std;
#include<time.h> // clock( )
#define    TRUE          1
#define     FALSE        0 
#define     OK              1
#define     ERROR      0
#define     INFEASIBLE     -1
typedef      int       Status;
#define MAXQSIZE 100

typedef struct {
  unsigned int weight;
  unsigned char data;
  unsigned int parent, lchild, rchild;
}HTNode , *HuffmanTree; //动态分配数组存储哈夫曼树

void Select(HuffmanTree HT,int m,int &s1,int &s2){//从这m个数里边选择最小的2个//把第一个进行标记就ok 
 int i;//从下标为1的位置开始计数 
 //int min=HT[1].weight;这里直接赋值不合理，假如第一次那个1就是最小被选选中，那么第2次还是被选中 
 int min1=1000; 
 int min2=1000;//规定一个特别大的数 
 for(i=1;i<=m;i++){
  if(HT[i].parent==0&&min1>HT[i].weight){
   min1=HT[i].weight;
   s1=i;
  }
 }
 int temp=HT[s1].weight;//将原值存放起来，赋予一个特别大的数，以防被重复选择
 HT[s1].weight =1000;
 for(i=1;i<=m;i++){//注意这个I!=*s1标记min 
  if(i!=(s1)&&HT[i].parent==0)
   if(HT[i].weight<min2){
    min2=HT[i].weight;
    s2=i;
   }  
 } 
 HT[s1].weight=temp;//恢复原来的值
}

void CreateHuffmanTree(HuffmanTree &HT,int n) //w存放n个权值，构造哈夫曼树HT，并求出n个字符的哈夫曼编码HC
{
   if(n<=1) return ;
   int  m; m=2*n-1; 
   HT=new HTNode[m+1]; //0号单元不用,所以需要动态分配m+1个的单元
   if (!HT) exit (OVERFLOW);
   for(int i=1; i<=m;++i){HT[i].parent=0;HT[i].lchild=0;HT[i].rchild=0;}
   cout<<"请输入叶子结点的字符："<<endl;
   for(int i=1;i<=n;++i) cin>>HT[i].data;
   cout<<"请输入叶子结点的权值："<<endl;
   for(int i=1;i<=n;++i) cin>>HT[i].weight;//建n棵仅含根结点二叉树
/*-----初始化结束，开始创建哈夫曼树------*/
   for(int i=n+1; i<=m;++i) //建哈夫曼树
   {  
	   int s1,s2; 
	   Select(HT,i+1,s1,s2); //在HT[1..i-1]中选择parent为0且weight最小的两个结点其序号分别为s1和s2
	   HT[s1].parent= i ; HT[s2].parent =i;
	   HT[i].lchild=s1; HT[i].rchild=s2;
	   HT[i].weight= HT[s1].weight+ HT[s2].weight;
   }//for 
   cout <<"下标"<<'\t'<<"data"<<'\t'<<"weight"<<'\t'<<"parent"<<'\t'<<"lchild"<<'\t'<<"rchild" << endl;
   for(int i=1;i<=2*n-1;i++)
   {
	   cout<<i<<'\t'<<HT[i].data<<'\t'<<HT[i].weight<<'\t'<<HT[i].parent<<'\t'<<HT[i].lchild<<'\t'<<HT[i].rchild<<endl;
   }
 }// HuffmanCoding

typedef    char  **HuffmanCode;   //动态分配数组存储哈夫曼编码表

void CreatHuffmanCode(HuffmanTree HT,HuffmanCode &HC,int n) {
  HC=new char*[n+1];   //分配n个字符编码的头指针
  char *cd=new char[n];
 //分配求编码的工作空间
cd[n-1]='\0'; //编码的结束标志
for(int i=1;i<=n;i++)  //逐个字符求哈夫曼编码
{
	int start=n-1;   //编码结束符位置
for(int c=i, f=HT[i].parent;  f!=0;  c=f,f= HT[f].parent)
 //从叶到根逆向求编码
{ 
	if(HT[f].lchild==c) cd[--start]='0';
	else cd[--start]='1';
}
 HC[i]=new char[n-start];
 //为第i个字符编码分配空间
strcpy(HC[i],  &cd[start]); //从cd复制编码串到HC[i]中
}
for (int i = 1; i <= n; i++) //打印哈夫曼编码
	{
		cout<<"字符"<< HT[i].data<<"的编码为："<<HC[i]<<endl;
	}
 delete cd; //释放工作空间
}// HuffmanCoding

//哈夫曼译码 
void HuffmanDeCode(HuffmanTree HT,HuffmanCode &HC,int n)
{   // 从根到叶子编码的算法
    char encodedString[MAXQSIZE];
    cout << "请输入要解码的编码字符串：" << endl;
    cin >> encodedString;

    int len = strlen(encodedString);
    char decodedString[MAXQSIZE];
    int index = 0;
    int current = 2 * n - 1; // 根节点

    for (int i = 0; i < len; i++) {
        if (encodedString[i] == '0') {
            current = HT[current].lchild;
        } else if (encodedString[i] == '1') {
            current = HT[current].rchild;
        }

        if (current > 0 && HT[current].lchild == 0 && HT[current].rchild == 0) {
            decodedString[index++] = HT[current].data;
            current = 2 * n - 1; // 回到根节点
        }
    }
    decodedString[index] = '\0';
    cout << "解码后的字符串: " << decodedString << endl;
}


void print(int n){
	char s[MAXQSIZE];
	cout << "请输入字符串：" << endl;
	cin>>s; int i,num[256]={0}; //统计次数时的变量
	// 统计各个字符出现的次数
    for(i=0;i<strlen(s);i++)
    {
        num[(int)s[i]]++;
      
    }
    
    for(i=0;i<256;i++)
    {
        if(num[i]!=0)
        {
			cout<<"字符"<<(char)i<<"出现"<<num[i]<<"次"<<endl;
        }
    }
}

int main(){
     int o; //操作,用于存储用户选择的操作选项
	 int n=0;//叶结点的个数，n个存储空间
	 HuffmanTree HT; 
	 HuffmanCode HC;    //编码表空间
	 cout<<endl;
	 while(1){
	    cout<<"------------------------"<<endl;
        cout<<"1、初始化并创建哈夫曼树"<<endl;
		cout<<"2、编码"<<endl;
	    cout<<"3、译码"<<endl;
		cout<<"4、输出"<<endl;
		cout<<"5、退出"<<endl;	
		cout<<"------------------------"<<endl;
		cout<<"输入您要进行的操作：";
		cin>> o;
		switch(o){
		   case 1:
			   cout<<"请输入叶子结点的个数：";
	           cin>>n;
	           CreateHuffmanTree(HT,n);
			   break;
		   case 2:
			   cout<<"编码的结果为："<<endl;
			   CreatHuffmanCode(HT,HC,n);
			   cout<<endl;
			   break;
		   case 3:
			   cout<<"译码的结果为："<<endl;
			   HuffmanDeCode(HT,HC,n);
			   cout<<endl;
			   break;
		   case 4:
			   cout<<"输出的结果为："<<endl;
			   print(n);
			   cout<<endl;
			   break;
		   case 5:
			   return 0;
		   default:
			   cout<<"没有该选项！"<<endl;
		}
	 }
     system("pause");
 }
