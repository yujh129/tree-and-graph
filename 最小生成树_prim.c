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

void creat_graph(Mat_Grph* G){
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

void prim(Mat_Grph* G){
    
    int i,j,k;
    int min=MAX;
    EdgeType weight[MAXSIZE];
    int vex_index[MAXSIZE];

    // 初始化：从顶点0开始构建最小生成树
    for(i=0;i<G->vertex_num;i++){
        weight[i]=G->arc[0][i];     // 初始化为从顶点0到各顶点的权重
        vex_index[i]=0;             // 记录与顶点i相连的顶点
    }
    weight[0]=0;                    // 顶点0以加入生成树

    //构建最小生成树，需要vertex_num-1条边
    for(i=1;i<G->vertex_num;i++){
        
        //初始化min和下标k，易忘&&注意
        min=MAX; 
        k=0;

        for(j=0;j<G->vertex_num;j++){
            if(weight[j]!=0&&weight[j]<min){
                min=weight[j];
                k=j;                //k记录最小权值边的终点
            }
        }

        //输出找到的边
        printf("%c-%c ",G->vertex[vex_index[k]],G->vertex[k]);
        weight[k]=0;                //将找到的k加入生成树

        //更新权重数组
        for(j=0;j<G->vertex_num;j++){
            if(weight[j]!=0&&weight[j]>G->arc[k][j]){
                weight[j]=G->arc[k][j];
                vex_index[j]=k;
            }
        }
    }

}

int main(){
    Mat_Grph G;
    creat_graph(&G);
    prim(&G);
    return 0;
}