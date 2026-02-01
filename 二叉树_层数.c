#include<stdio.h>
#include<stdlib.h>
#define MAX 1000

int idx=0;
char str[]="ABDH#K###E##CFI###G#J##";

typedef char ElemType;

typedef struct treeNode{
    ElemType val;
    struct treeNode* lchild;
    struct treeNode* rchild;
}treeNode;

typedef treeNode* Element;

typedef struct queue{
    Element* data;
    int front;
    int rear;
}queue;

int is_empty(queue* q){
    if(q->front==q->rear){
        return 1;
    }
    return 0;
}

void createTree(treeNode** T){
    ElemType ch;
    ch=*(str+idx++);
    if(ch=='#'){
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
    printf("%c ",T->val);
    preOrder(T->lchild);
    preOrder(T->rchild);
}

queue* initqueue(){
    queue* q=(queue*)malloc(sizeof(queue));
    q->data=(Element*)malloc(MAXSIZE*sizeof(Element));
    q->front=0;
    q->rear=q->front;
    return q;
}

int queue_full(queue* q){
    if(q->front>0){
        for(int i=q->front;i<=q->rear;i++){
            *(q->data+i-q->front)=*(q->data+i);
        }
        q->rear-=q->front;
        q->front=0;
        return 0;
    }else{
        return 1;
    }
    return 0;
}

void equeue(queue* q,Element e){
    if(q->rear>=MAXSIZE){
        if(queue_full(q)){
            return;
        }
    }
    *(q->data+q->rear++)=e;
}

void dequeue(queue* q,Element* e){
    if(is_empty(q)){
        return;
    }
    *e=*(q->data+q->front);
    q->front++;
}

int queuesize(queue* q){
    return q->rear-q->front;
}

int MaxDepth(treeNode* root){
    if(root==NULL){
        return 0;
    }
    int depth=0;
    queue* q=initqueue();
    equeue(q,root);
    while(!is_empty(q)){
        int count=queuesize(q);
        while(count>0){
            treeNode* cur;
            dequeue(q,&cur);
            if(cur->lchild!=NULL){
                equeue(q,cur->lchild);
            }
            if(cur->rchild!=NULL){
                equeue(q,cur->rchild);
            }
            count--;
        }
        depth++;
    }
    return depth;
}

int main(){
    treeNode* T;
    createTree(&T);
    preOrder(T);
    printf("\n");
    printf("%d",MaxDepth(T));
    return 0;
}