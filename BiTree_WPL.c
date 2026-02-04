#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 1000

int idx=0;
int whight[]={100,42,15,-1,-1,27,-1,-1,58,28,13,5,-1,-1,8,-1,-1,15,-1,-1,30,-1,-1};

typedef int ElemType;

typedef struct treeNode{
    ElemType val;
    struct treeNode* lchild;
    struct treeNode* rchild;
}treeNode;

void createTree(treeNode** T){
    ElemType ch;
    ch=*(whight+idx++);
    if(ch==-1){
        *T=NULL;
    }
    else{
        *T=(treeNode*)malloc(sizeof(treeNode));
        (*T)->val=ch;
        createTree(&(*T)->lchild);
        createTree(&(*T)->rchild);
    }
}

void preOrder(treeNode* T){
    if(T==NULL){
        return;
    }
    printf("%d ",T->val);
    preOrder(T->lchild);
    preOrder(T->rchild);
}

int wpl(treeNode* T){
    if(T==NULL){
        return 0;
    }
    treeNode* queue[MAXSIZE];
    int front=0;
    int rear=0;

    int wpl=0;
    int depth=0;
    queue[rear++]=T;
    while(rear!=front){
        int count=rear-front;
        while(count>0){
            treeNode* cur=queue[front++];
            if(cur->lchild==NULL&&cur->rchild==NULL){
                wpl+=depth*cur->val;
            }
            if(cur->lchild!=NULL){
                queue[rear++]=cur->lchild;
            }
            if(cur->rchild!=NULL){
                queue[rear++]=cur->rchild;
            }
            count--;
        }
        depth++;
    }
    return wpl;
}

int main(){
    treeNode* T;
    createTree(&T);
    preOrder(T);
    printf("\n");
    printf("%d",wpl(T));
    return 0;

}
