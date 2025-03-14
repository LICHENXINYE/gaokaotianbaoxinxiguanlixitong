#include <stdio.h>
#include <stdlib.h>

// �������ڵ�������Ԫ�ص����ͼ���Ϊchar���ɰ����滻
typedef char TElemType;  

// �������Ķ�������洢�ṹ����
typedef struct BiTNode { 
    TElemType data;
    struct BiTNode *lchild, *rchild; 
} BiTNode, *BiTree;

// ��������������д�������������#��ʾ�սڵ㣩
BiTree CreateBiTree() {
    char ch;
    scanf("%c", &ch);
    if (ch == '#') {
        return NULL;
    }
    BiTree T = (BiTree)malloc(sizeof(BiTNode));
    T->data = ch;
    T->lchild = CreateBiTree();
    T->rchild = CreateBiTree();
    return T;
}

// �������������
void PreOrderTraverse(BiTree T) {
    if (T == NULL) {
        return;
    }
    printf("%c ", T->data);
    PreOrderTraverse(T->lchild);
    PreOrderTraverse(T->rchild);
}

// �������������
void InOrderTraverse(BiTree T) {
    if (T == NULL) {
        return;
    }
    InOrderTraverse(T->lchild);
    printf("%c ", T->data);
    InOrderTraverse(T->rchild);
}

// �������������
void PostOrderTraverse(BiTree T) {
    if (T == NULL) {
        return;
    }
    PostOrderTraverse(T->lchild);
    PostOrderTraverse(T->rchild);
    printf("%c ", T->data);
}

// ����һ���ṹ�����ڸ�����α��������нڵ㣩
typedef struct LinkNode {
    BiTree data;
    struct LinkNode *next;
} LinkNode;

// ������нṹ
typedef struct {
    LinkNode *front, *rear;
} LinkQueue;

// ��ʼ������
void InitQueue(LinkQueue *Q) {
    Q->front = Q->rear = (LinkNode *)malloc(sizeof(LinkNode));
    Q->front->next = NULL;
}

// �ж϶����Ƿ�Ϊ��
int IsEmpty(LinkQueue *Q) {
    return Q->front == Q->rear;
}

// ��Ӳ���
void EnQueue(LinkQueue *Q, BiTree e) {
    LinkNode *s = (LinkNode *)malloc(sizeof(LinkNode));
    s->data = e;
    s->next = NULL;
    Q->rear->next = s;
    Q->rear = s;
}

// ���Ӳ���
BiTree DeQueue(LinkQueue *Q) {
    if (IsEmpty(Q)) {
        return NULL;
    }
    LinkNode *p = Q->front->next;
    BiTree e = p->data;
    Q->front->next = p->next;
    if (Q->rear == p) {
        Q->rear = Q->front;
    }
    free(p);
    return e;
}

// ��α���������
void LevelOrderTraverse(BiTree T) {
    LinkQueue Q;
    InitQueue(&Q);
    if (T!= NULL) {
        EnQueue(&Q, T);
    }
    while (!IsEmpty(&Q)) {
        BiTree p = DeQueue(&Q);
        printf("%c ", p->data);
        if (p->lchild!= NULL) {
            EnQueue(&Q, p->lchild);
        }
        if (p->rchild!= NULL) {
            EnQueue(&Q, p->rchild);
        }
    }
}

int main() {
    BiTree T = CreateBiTree();
    printf("����������: ");
    PreOrderTraverse(T);
    printf("\n");
    printf("����������: ");
    InOrderTraverse(T);
    printf("\n");
    printf("����������: ");
    PostOrderTraverse(T);
    printf("\n");
    printf("��α������: ");
    LevelOrderTraverse(T);
    printf("\n");
    return 0;
}
