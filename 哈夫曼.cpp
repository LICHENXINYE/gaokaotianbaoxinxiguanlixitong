#include<stdio.h> // EOF(=^Z��F6),NULL
#include<stdlib.h> // srand( ) ,rand( ),exit(n)
#include<malloc.h> // malloc( ),alloc( ),realloc( )��
#include<limits.h> // INT_MAX��
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
}HTNode , *HuffmanTree; //��̬��������洢��������

void Select(HuffmanTree HT,int m,int &s1,int &s2){//����m�������ѡ����С��2��//�ѵ�һ�����б�Ǿ�ok 
 int i;//���±�Ϊ1��λ�ÿ�ʼ���� 
 //int min=HT[1].weight;����ֱ�Ӹ�ֵ�����������һ���Ǹ�1������С��ѡѡ�У���ô��2�λ��Ǳ�ѡ�� 
 int min1=1000; 
 int min2=1000;//�涨һ���ر����� 
 for(i=1;i<=m;i++){
  if(HT[i].parent==0&&min1>HT[i].weight){
   min1=HT[i].weight;
   s1=i;
  }
 }
 int temp=HT[s1].weight;//��ԭֵ�������������һ���ر��������Է����ظ�ѡ��
 HT[s1].weight =1000;
 for(i=1;i<=m;i++){//ע�����I!=*s1���min 
  if(i!=(s1)&&HT[i].parent==0)
   if(HT[i].weight<min2){
    min2=HT[i].weight;
    s2=i;
   }  
 } 
 HT[s1].weight=temp;//�ָ�ԭ����ֵ
}

void CreateHuffmanTree(HuffmanTree &HT,int n) //w���n��Ȩֵ�������������HT�������n���ַ��Ĺ���������HC
{
   if(n<=1) return ;
   int  m; m=2*n-1; 
   HT=new HTNode[m+1]; //0�ŵ�Ԫ����,������Ҫ��̬����m+1���ĵ�Ԫ
   if (!HT) exit (OVERFLOW);
   for(int i=1; i<=m;++i){HT[i].parent=0;HT[i].lchild=0;HT[i].rchild=0;}
   cout<<"������Ҷ�ӽ����ַ���"<<endl;
   for(int i=1;i<=n;++i) cin>>HT[i].data;
   cout<<"������Ҷ�ӽ���Ȩֵ��"<<endl;
   for(int i=1;i<=n;++i) cin>>HT[i].weight;//��n�ý�������������
/*-----��ʼ����������ʼ������������------*/
   for(int i=n+1; i<=m;++i) //����������
   {  
	   int s1,s2; 
	   Select(HT,i+1,s1,s2); //��HT[1..i-1]��ѡ��parentΪ0��weight��С�������������ŷֱ�Ϊs1��s2
	   HT[s1].parent= i ; HT[s2].parent =i;
	   HT[i].lchild=s1; HT[i].rchild=s2;
	   HT[i].weight= HT[s1].weight+ HT[s2].weight;
   }//for 
   cout <<"�±�"<<'\t'<<"data"<<'\t'<<"weight"<<'\t'<<"parent"<<'\t'<<"lchild"<<'\t'<<"rchild" << endl;
   for(int i=1;i<=2*n-1;i++)
   {
	   cout<<i<<'\t'<<HT[i].data<<'\t'<<HT[i].weight<<'\t'<<HT[i].parent<<'\t'<<HT[i].lchild<<'\t'<<HT[i].rchild<<endl;
   }
 }// HuffmanCoding

typedef    char  **HuffmanCode;   //��̬��������洢�����������

void CreatHuffmanCode(HuffmanTree HT,HuffmanCode &HC,int n) {
  HC=new char*[n+1];   //����n���ַ������ͷָ��
  char *cd=new char[n];
 //���������Ĺ����ռ�
cd[n-1]='\0'; //����Ľ�����־
for(int i=1;i<=n;i++)  //����ַ������������
{
	int start=n-1;   //���������λ��
for(int c=i, f=HT[i].parent;  f!=0;  c=f,f= HT[f].parent)
 //��Ҷ�������������
{ 
	if(HT[f].lchild==c) cd[--start]='0';
	else cd[--start]='1';
}
 HC[i]=new char[n-start];
 //Ϊ��i���ַ��������ռ�
strcpy(HC[i],  &cd[start]); //��cd���Ʊ��봮��HC[i]��
}
for (int i = 1; i <= n; i++) //��ӡ����������
	{
		cout<<"�ַ�"<< HT[i].data<<"�ı���Ϊ��"<<HC[i]<<endl;
	}
 delete cd; //�ͷŹ����ռ�
}// HuffmanCoding

//���������� 
void HuffmanDeCode(HuffmanTree HT,HuffmanCode &HC,int n)
{   // �Ӹ���Ҷ�ӱ�����㷨
    char encodedString[MAXQSIZE];
    cout << "������Ҫ����ı����ַ�����" << endl;
    cin >> encodedString;

    int len = strlen(encodedString);
    char decodedString[MAXQSIZE];
    int index = 0;
    int current = 2 * n - 1; // ���ڵ�

    for (int i = 0; i < len; i++) {
        if (encodedString[i] == '0') {
            current = HT[current].lchild;
        } else if (encodedString[i] == '1') {
            current = HT[current].rchild;
        }

        if (current > 0 && HT[current].lchild == 0 && HT[current].rchild == 0) {
            decodedString[index++] = HT[current].data;
            current = 2 * n - 1; // �ص����ڵ�
        }
    }
    decodedString[index] = '\0';
    cout << "�������ַ���: " << decodedString << endl;
}


void print(int n){
	char s[MAXQSIZE];
	cout << "�������ַ�����" << endl;
	cin>>s; int i,num[256]={0}; //ͳ�ƴ���ʱ�ı���
	// ͳ�Ƹ����ַ����ֵĴ���
    for(i=0;i<strlen(s);i++)
    {
        num[(int)s[i]]++;
      
    }
    
    for(i=0;i<256;i++)
    {
        if(num[i]!=0)
        {
			cout<<"�ַ�"<<(char)i<<"����"<<num[i]<<"��"<<endl;
        }
    }
}

int main(){
     int o; //����,���ڴ洢�û�ѡ��Ĳ���ѡ��
	 int n=0;//Ҷ���ĸ�����n���洢�ռ�
	 HuffmanTree HT; 
	 HuffmanCode HC;    //�����ռ�
	 cout<<endl;
	 while(1){
	    cout<<"------------------------"<<endl;
        cout<<"1����ʼ����������������"<<endl;
		cout<<"2������"<<endl;
	    cout<<"3������"<<endl;
		cout<<"4�����"<<endl;
		cout<<"5���˳�"<<endl;	
		cout<<"------------------------"<<endl;
		cout<<"������Ҫ���еĲ�����";
		cin>> o;
		switch(o){
		   case 1:
			   cout<<"������Ҷ�ӽ��ĸ�����";
	           cin>>n;
	           CreateHuffmanTree(HT,n);
			   break;
		   case 2:
			   cout<<"����Ľ��Ϊ��"<<endl;
			   CreatHuffmanCode(HT,HC,n);
			   cout<<endl;
			   break;
		   case 3:
			   cout<<"����Ľ��Ϊ��"<<endl;
			   HuffmanDeCode(HT,HC,n);
			   cout<<endl;
			   break;
		   case 4:
			   cout<<"����Ľ��Ϊ��"<<endl;
			   print(n);
			   cout<<endl;
			   break;
		   case 5:
			   return 0;
		   default:
			   cout<<"û�и�ѡ�"<<endl;
		}
	 }
     system("pause");
 }
