#include<stdio.h>
#include<stdlib.h>

typedef char VertexType;
typedef int EdgeType;

#define MAXSIZE 100
#define MAX 0x7fffffff

typedef struct{
    VertexType vertex[MAXSIZE];
    EdgeType arc[MAXSIZE][MAXSIZE];
    int vertex_num;
    int edge_num;
}Mat_Grph;

typedef struct{
    int begin;
    int end;
    int weight;
}Edge;

void creat_graph(Mat_Grph *G){
    G->edge_num=15;
    G->vertex_num=9;
    char ch='A';
    for(int i=0;i<9;i++){
        *(G->vertex+i)=ch++;
    }
    for(int i=0;i<G->vertex_num;i++){
        for(int j=0;j<G->vertex_num;j++){
            if(i==j){
                G->arc[i][j]=0;
            }else{
                G->arc[i][j]=MAX;
            }
        }
    }

    //A-B,A-F
    G->arc[0][1]=10;
    G->arc[0][5]=11;

    //B-C,B-I,B-G
    G->arc[1][2]=18;
    G->arc[1][8]=12;
    G->arc[1][6]=16;

    //C-I,C-D
    G->arc[2][8]=8;
    G->arc[2][3]=22;

    //D-I,D-G,D-H,D-E
    G->arc[3][4]=20;
    G->arc[3][7]=16;
    G->arc[3][8]=21;
    G->arc[3][6]=24;

    //E-H,E-F
    G->arc[4][5]=26;
    G->arc[4][7]=7;

    //F-G
    G->arc[5][6]=17;

    //G-H   
    G->arc[6][7]=19;

    for(int i=0;i<G->vertex_num;i++){
        for(int j=0;j<G->vertex_num;j++){
            G->arc[j][i]=G->arc[i][j];
        }
    }


}

int cmp(const void* a,const void* b){
    Edge* c=(Edge*)a;
    Edge* d=(Edge*)b;
    return (c->weight-d->weight);
}

int find(int* parent,int index){
    while(parent[index]>0){
        index=parent[index];
    }
    return index;
}

void kruskal(Mat_Grph G){
    Edge edge[MAXSIZE];
    int k=0;

    //遍历上半区域，存储于edge数组中
    for(int i=0;i<G.vertex_num;i++){
        for(int j=i+1;j<G.vertex_num;j++){
            if(G.arc[i][j]<MAX){
                edge[k].begin=i;
                edge[k].end=j;
                edge[k].weight=G.arc[i][j];
                k++;
            }
        }
    }

    qsort(edge,G.edge_num,sizeof(Edge),cmp);

    int parent[MAXSIZE];
    for(int i=0;i<G.vertex_num;i++){
        parent[i]=0;
    }

    int n,m;
    for(int i=0;i<G.edge_num;i++){
        n=find(parent,edge[i].begin);
        m=find(parent,edge[i].end);
        if(n!=m){
            parent[n]=m;
            printf("%c-%c %d\n",G.vertex[edge[i].begin],G.vertex[edge[i].end],edge[i].weight);
        }
    }
}

int main(){
    Mat_Grph G;
    creat_graph(&G);
    kruskal(G);
    return 0;
}