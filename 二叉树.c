#include<stdio.h>
#include<stdlib.h>

typedef char ElemType;
typedef struct TreeNode{
    ElemType data;
    struct TreeNode* left;
    struct TreeNode* right;
}TreeNode;

typedef TreeNode* BiTree;

char str[]="ABD##EG##H##CF#I###";
int idx=0;

void createTree(BiTree* T){
    ElemType ch;
    ch=*(str+idx++);
    if(ch=='#'){
        *T=NULL;
    }
    else{
        *T=(BiTree)malloc(sizeof(TreeNode));
        (*T)->data=ch;
        creatTree(&(*T)->left);
        creatTree(&(*T)->right);
    }
}

void preOrder(BiTree T){
    if(T==NULL){
        return;
    }
    printf("%c ",T->data);
    preOrder(T->left);
    preOrder(T->right);
}

void inOrder(BiTree T){
    if(T==NULL){
        return;
    }
    inOrder(T->left);
    printf("%c ",T->data);
    inOrder(T->right);
}

void postOrder(BiTree T){
    if(T==NULL){
        return;
    }
    postOrder(T->left);
    postOrder(T->right);
    printf("%c ",T->data);
}

int main(){
    BiTree T;
    creatTree(&T);
    preOrder(T);
    printf("\n");
    inOrder(T);
    printf("\n");
    postOrder(T);
    return 0;
}