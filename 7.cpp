#include <stdio.h>
#include <stdlib.h>

// 二叉树节点中数据元素的类型假设为char，可按需替换
typedef char TElemType;  

// 二叉树的二叉链表存储结构定义
typedef struct BiTNode { 
    TElemType data;
    struct BiTNode *lchild, *rchild; 
} BiTNode, *BiTree;

// 按照先序遍历序列创建二叉树（以#表示空节点）
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

// 先序遍历二叉树
void PreOrderTraverse(BiTree T) {
    if (T == NULL) {
        return;
    }
    printf("%c ", T->data);
    PreOrderTraverse(T->lchild);
    PreOrderTraverse(T->rchild);
}

// 中序遍历二叉树
void InOrderTraverse(BiTree T) {
    if (T == NULL) {
        return;
    }
    InOrderTraverse(T->lchild);
    printf("%c ", T->data);
    InOrderTraverse(T->rchild);
}

// 后序遍历二叉树
void PostOrderTraverse(BiTree T) {
    if (T == NULL) {
        return;
    }
    PostOrderTraverse(T->lchild);
    PostOrderTraverse(T->rchild);
    printf("%c ", T->data);
}

// 定义一个结构体用于辅助层次遍历（队列节点）
typedef struct LinkNode {
    BiTree data;
    struct LinkNode *next;
} LinkNode;

// 定义队列结构
typedef struct {
    LinkNode *front, *rear;
} LinkQueue;

// 初始化队列
void InitQueue(LinkQueue *Q) {
    Q->front = Q->rear = (LinkNode *)malloc(sizeof(LinkNode));
    Q->front->next = NULL;
}

// 判断队列是否为空
int IsEmpty(LinkQueue *Q) {
    return Q->front == Q->rear;
}

// 入队操作
void EnQueue(LinkQueue *Q, BiTree e) {
    LinkNode *s = (LinkNode *)malloc(sizeof(LinkNode));
    s->data = e;
    s->next = NULL;
    Q->rear->next = s;
    Q->rear = s;
}

// 出队操作
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

// 层次遍历二叉树
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
    printf("先序遍历结果: ");
    PreOrderTraverse(T);
    printf("\n");
    printf("中序遍历结果: ");
    InOrderTraverse(T);
    printf("\n");
    printf("后序遍历结果: ");
    PostOrderTraverse(T);
    printf("\n");
    printf("层次遍历结果: ");
    LevelOrderTraverse(T);
    printf("\n");
    return 0;
}
