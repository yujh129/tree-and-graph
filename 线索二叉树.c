#include<stdio.h>
#include<stdlib.h>

typedef char ElemType;
typedef struct ThreadNode{
    ElemType data;
    struct ThreadNode* left;
    struct ThreadNode* right;
    //ltag==0:left has leftTree
    //latg==1:left hasn`t lefttree
    int ltag;
    int rtag;
}ThreadNode;

typedef ThreadNode* ThreadTree;

//类preOrder创建二叉树
char str[]="ABDH##I##EJ###CF##G##";
int idx=0;

ThreadTree prev=NULL;

//用前序的方式创建一棵二叉树
void createTree(ThreadTree* T){
    ElemType ch;
    ch=str[idx++];
    if(ch=='#'){
        *T=NULL;
    }
    else{
        *T=(ThreadTree)malloc(sizeof(ThreadNode));
        (*T)->data=ch;
        (*T)->ltag=0;
        (*T)->rtag=0;
        createTree(&(*T)->left);
        if((*T)->left==NULL){
            (*T)->ltag=1;
        }

        createTree(&(*T)->right);
        if((*T)->right==NULL){
            (*T)->rtag=1;
        }

    }   
}

//将树线索化
void in_threading(ThreadTree T){
    if(T!=NULL){
        in_threading(T->left);
        if(T->left==NULL){
            T->left=prev;
            T->ltag=1;
        }
        if(prev->right==NULL){
            prev->rtag=1;
            prev->right=T;
        }
        prev=T;
        in_threading(T->right);
    }
}


//中序遍历的方式线索化二叉树
void inOrderThreading(ThreadTree* head,ThreadTree T){
    *head=(ThreadTree)malloc(sizeof(ThreadNode));
    (*head)->ltag=0;
    (*head)->rtag=1;
    (*head)->right=(*head);

    if(T==NULL){
        (*head)->left=(*head);
    }
    else{
        (*head)->left=T;
        prev=(*head);

        in_threading(T);

        prev->right=(*head);
        prev->rtag=1;

        (*head)->right=prev;
    }
}


//中序遍历输出一棵线索二叉树
void inOrder(ThreadTree T){
    ThreadTree cur;
    cur=T->left;

    while(cur!=T){
        while(cur->ltag==0){
            cur=cur->left;
        }

        printf("%c ",cur->data);

        while(cur->rtag==1&&cur->right!=T){
            cur=cur->right;
            printf("%c ",cur->data);
        }
        cur=cur->right;
    }
}

int main(){
    ThreadTree in_head;
    ThreadTree in_T;
    createTree(&in_T);
    inOrderThreading(&in_head,in_T);
    inOrder(in_head);
    return 0;
}