#include<stdio.h>
#include<stdlib.h>

typedef char VertexType;
typedef int EdgeType;

#define MAXSIZE 100

typedef struct{
    VertexType vertex[MAXSIZE];
    EdgeType arc[MAXSIZE][MAXSIZE];
    int vertex_num;
    int edge_num;
}Mat_Grph;

int visited[MAXSIZE];
EdgeType queue[MAXSIZE];
int front=0;
int rear=0;

void creat_graph(Mat_Grph* G){
    G->edge_num=15;
    G->vertex_num=9;
    char ch='A';
    for(int i=0;i<9;i++){
        *(G->vertex+i)=ch++;
    }
    for(int i=0;i<G->vertex_num;i++){
        for(int j=0;j<G->vertex_num;j++){
            G->arc[i][j]=0;
        }
    }

    //A-B,A-F
    G->arc[0][1]=1;
    G->arc[0][5]=1;

    //B-C,B-I,B-G
    G->arc[1][2]=1;
    G->arc[1][8]=1;
    G->arc[1][6]=1;

    //C-I,C-D
    G->arc[2][8]=1;
    G->arc[2][3]=1;

    //D-I,D-G,D-H,D-E
    G->arc[3][4]=1;
    G->arc[3][7]=1;
    G->arc[3][8]=1;
    G->arc[3][6]=1;

    //E-H,E-F
    G->arc[4][5]=1;
    G->arc[4][7]=1;

    //F-G
    G->arc[5][6]=1;

    //G-H   
    G->arc[6][7]=1;

    for(int i=0;i<G->vertex_num;i++){
        for(int j=0;j<G->vertex_num;j++){
            G->arc[j][i]=G->arc[i][j];
        }
    }


}

void dfs(Mat_Grph G,int i){
    visited[i]=1;
    printf("%c ",G.vertex[i]);

    for(int j=0;j<G.vertex_num;j++){
        if(G.arc[i][j]==1&&visited[j]==0){
            dfs(G,j);
        }
    }
}

void bfs(Mat_Grph G){
    int i=0;
    visited[0]=1;
    printf("%c ",G.vertex[i]);
    queue[rear++]=i;
    while(front!=rear){
        i=queue[front++];
        for(int j=0;j<G.vertex_num;j++){
            if(G.arc[i][j]==1&&visited[j]==0){
                visited[j]=1;
                printf("%c ",G.vertex[j]);
                queue[rear++]=j;
            }
        }
    }
}

int main(){
    Mat_Grph G;
    creat_graph(&G);
    for(int i=0;i<G.vertex_num;i++){
        visited[i]=0;
    }  
    dfs(G,0);
    printf("\n");
    for(int i=0;i<G.vertex_num;i++){
        visited[i]=0;
    }  
    bfs(G);
    return 0;
}