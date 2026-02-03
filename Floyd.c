#include<stdio.h>

typedef int VertexType;
typedef int EdgeType;

#define MAXSIZE 100
#define MAXEDGE 200
#define MAX 0x10000

typedef struct {
    VertexType vertex[MAXSIZE];
    EdgeType arc[MAXSIZE][MAXSIZE];
    int edge_num;
    int vertex_num;
}Mat_graph;

void create_graph(Mat_graph* G){
    G->edge_num=16;
    G->vertex_num=9;

    for(int i=0;i<G->vertex_num;i++){
        G->vertex[i]=i;
    }

    for(int i=0;i<G->vertex_num;i++){
        for(int j=0;j<G->vertex_num;j++){
            G->arc[i][j]=(i==j)?0:MAX;
        }
    }

    G->arc[0][1]=1;
    G->arc[0][2]=5;

    G->arc[1][2]=3;
    G->arc[1][3]=7;
    G->arc[1][4]=5;

    G->arc[2][4]=1;
    G->arc[2][5]=7;

    G->arc[3][4]=2;
    G->arc[3][6]=3;

    G->arc[4][5]=3;
    G->arc[4][6]=6;
    G->arc[4][7]=9;

    G->arc[5][7]=5;

    G->arc[6][7]=2;
    G->arc[6][8]=7;

    G->arc[7][8]=4;

    for(int i=0;i<G->vertex_num;i++){
        for(int j=0;j<G->vertex_num;j++){
            G->arc[j][i]=G->arc[i][j];
        }
    }
}

void floyd(Mat_graph G){
    int distance[MAXSIZE][MAXSIZE];
    int path[MAXSIZE][MAXSIZE];

    for(int i=0;i<G.vertex_num;i++){
        for(int j=0;j<G.vertex_num;j++){
            distance[i][j]=G.arc[i][j];
            path[i][j]=j;
        }
    }

    //i:mid j:begin k:end
    for(int i=0;i<G.vertex_num;i++){
        for(int j=0;j<G.vertex_num;j++){
            for(int k=0;k<G.vertex_num;k++){
                if(distance[j][k]>distance[j][i]+distance[i][k]){
                    distance[j][k]=distance[j][i]+distance[i][k];
                    path[j][k]=path[j][i];
                }
            }
        }
    }

    int k;
    for(int i=0;i<G.vertex_num;i++){
        for(int j=i+1;j<G.vertex_num;j++){
            printf("V%d->V%d:weight:%d ",i,j,distance[i][j]);
            k=path[i][j];
            printf("Path:V%d",i);
            while(k!=j){
                printf("->V%d",k);
                k=path[k][j];
            }
            printf("->V%d\n",j);
        }
        printf("\n");
    }
}

int main(int argc, char const *argv[])
{
    Mat_graph G;
    create_graph(&G);
    floyd(G);
    return 0;
}
