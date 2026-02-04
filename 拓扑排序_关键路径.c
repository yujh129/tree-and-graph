#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 100
#define MAX 0x7fffffff

typedef struct {
    int vertex[MAXSIZE];
    int arc[MAXSIZE][MAXSIZE];
    int edge_num;
    int vertex_num;
}Mat_Graph;

//边结点
typedef struct EdgeNode{
    int edge_vex;
    int weight;
    struct EdgeNode* next;
}EdgeNode;

typedef struct VertexNode{
    int in;
    int data;
    EdgeNode* head;
}VertexNode;

typedef VertexNode Adj_List[MAXSIZE];//adj:adjacency

typedef struct{
    Adj_List adj_list;
    int vextex_num;
    int edge_num;
}Adj_Graph;

typedef Adj_Graph* Adj_List_graph;

void create_Graph(Mat_Graph* G){
    G->vertex_num=10;
    G->edge_num=13;

    for(int i=0;i<G->vertex_num;i++){
        G->vertex[i]=i;
    }

    for(int i=0;i<G->vertex_num;i++){
        for(int j=0;j<G->vertex_num;j++){
            G->arc[i][j]=(i==j)?0:MAX;
        }
    }

   G->arc[0][1]=3;
   G->arc[0][2]=4;
   G->arc[1][3]=5;
   G->arc[1][4]=6;
   G->arc[2][3]=8;
   G->arc[2][5]=7;
   G->arc[3][4]=3;
   G->arc[4][6]=9;
   G->arc[4][7]=4;
   G->arc[5][7]=6;
   G->arc[6][9]=2;
   G->arc[7][8]=5;
   G->arc[8][9]=3;

}

void create_adj_graph(Mat_Graph G,Adj_List_graph* ALG){
    EdgeNode* e;
    *ALG=(Adj_List_graph)malloc(sizeof(Adj_Graph));
    (*ALG)->vextex_num=G.vertex_num;
    (*ALG)->edge_num=G.edge_num;

    for(int i=0;i<G.vertex_num;i++){
        (*ALG)->adj_list[i].in=0;
        (*ALG)->adj_list[i].data=G.vertex[i];
        (*ALG)->adj_list[i].head=NULL;
    }

    for(int i=0;i<G.vertex_num;i++){
        for(int j=0;j<G.vertex_num;j++){
            if(G.arc[i][j]!=0&&G.arc[i][j]<MAX){
                e=(EdgeNode*)malloc(sizeof(EdgeNode));
                e->edge_vex=j;
                e->weight=G.arc[i][j];
                e->next=(*ALG)->adj_list[i].head;
                (*ALG)->adj_list[i].head=e;
                (*ALG)->adj_list[j].in++;
            }
        }
    }
}

// void topological_sort(Adj_List_graph ALG){
//     EdgeNode* e;
//     int top=-1;
//     int stack[MAXSIZE];
//     int curr,k;
//     for(int i=0;i<ALG->vextex_num;i++){
//         if(ALG->adj_list[i].in==0){
//             stack[++top]=i;
//         }
//     }

//     while(top!=-1){
//         curr=stack[top--];
//         printf("V%d->",ALG->adj_list[curr].data);
//         e=ALG->adj_list[curr].head;
//         while(e!=NULL){
//             k=e->edge_vex;
//             ALG->adj_list[k].in--;
//             if(ALG->adj_list[k].in==0){
//                 stack[++top]=k;
//             }
//             e=e->next;
//         }
//     }
//     printf("END\n");
// }

void critical_path(Adj_List_graph ALG){
    EdgeNode* e;
    int top=-1;
    int top2=-1;
    int stack[MAXSIZE],stack2[MAXSIZE];
    int etv[MAXSIZE];
    int ltv[MAXSIZE];
    int curr;
    int k;
    for(int i=0;i<ALG->vextex_num;i++){
        if(ALG->adj_list[i].in==0){
            stack[++top]=i;
        }
    }

    for(int i=0;i<ALG->vextex_num;i++){
        etv[i]=0;
    }

    while(top!=-1){
        curr=stack[top--];
        printf("V%d->",ALG->adj_list[curr].data);

        stack2[++top2]=curr;

        e=ALG->adj_list[curr].head;

        while(e!=NULL){
            k=e->edge_vex;
            ALG->adj_list[k].in--;
            if(ALG->adj_list[k].in==0){
                stack[++top]=k;
            }

            if(etv[curr]+e->weight>etv[k]){
                etv[k]=etv[curr]+e->weight;
            }
            e=e->next;
        }
    }
    printf("END\netv: ");
    for(int i=0;i<ALG->vextex_num;i++){
        printf("%d->",etv[i]);
    }
    printf("END\n");

    for(int i=0;i<ALG->vextex_num;i++){
        ltv[i]=etv[ALG->vextex_num-1];
    }

    while (top2!=-1)
    {
        curr=stack2[top2--];

        e=ALG->adj_list[curr].head;
        while(e!=NULL){
            k=e->edge_vex;

            if(ltv[k]-e->weight<ltv[curr]){
                ltv[curr]=ltv[k]-e->weight;
            }
            e=e->next;
        }
    }
    
    printf("ltv: ");
    for(int i=0;i<ALG->vextex_num;i++){
        printf("%d->",ltv[i]);
    }
    printf("END\n");

    for(int i=0;i<ALG->vextex_num;i++){
        if(etv[i]==ltv[i]){
            printf("V%d->",i);
        }
    }
    printf("END");
}
int main(int argc, char const *argv[])
{
    Mat_Graph G;
    Adj_List_graph ALG;
    create_Graph(&G);
    create_adj_graph(G,&ALG);
    // topological_sort(ALG);
    critical_path(ALG);
    
    return 0;
}
