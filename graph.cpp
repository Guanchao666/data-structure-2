#include<iostream>
#include<vector>
#include<queue>
using namespace std;
#define MAXVEX 100                  // 最大顶点数
#define INFINITY 65535              // 无穷大

/*  ------------- 图的存储结构 start ---------------*/

/*  图的邻接矩阵存储结构（数组），C   */
typedef struct{
    char vertexes[MAXVEX];          // 顶点表
    int arcs[MAXVEX][MAXVEX];       // 弧的邻接矩阵
    int vertexes_num, edges_num;    // 顶点数和边数
}MGraph;


/*  图的邻接表存储结构   */
// 边的表结点
typedef struct EdgeNode{
    int adjvex;                     // 邻接点域，存储邻接点对应的下标
    int weight;                     // 边的权值，备用
    EdgeNode *next;                 // 链域，指向下一个邻接点
}EdgeNode;

// 顶点的表结点
typedef struct{
    char data;                      // 顶点信息
    EdgeNode *first_edge;           // 边表的头指针
}VertexNode, AdjList;

// 图的邻接表
typedef struct{
    AdjList adj_list[MAXVEX];
    int vertexes_num, edges_num;    // 顶点数和边数
}GraphAdjList;

/*  ------------- 图的存储结构 end ---------------*/


/*  ------------- 图的遍历 start ---------------*/

bool visited[MAXVEX];                // 访问标志数组

// 邻接矩阵的深度优先遍历递归算法
void DFS(MGraph G, int i){
    visited[i] = true;
    cout << G.vertexes[i] << " ";               // 打印顶点信息，作为访问
    for(int j = 0; j < G.vertexes_num; j++){
        if(G.arcs[i][j] == 1 && !visited[j]){
            DFS(G, j);                          // 对访问的邻接顶点递归调用
        }
    }
}
void DFSTraverse(MGraph G){
    for(int i = 0; i < G.vertexes_num; i++){
        visited[i] = false;                     // 初始化访问标志数组
    }
    for(int i = 0; i < G.vertexes_num; i++){
        if(!visited[i]){                        // 对未访问过的顶点调用DFS
            DFS(G, i);
        }
    }
}

// 邻接表的深度优先遍历递归算法
void DFS2(GraphAdjList GL, int i){
    EdgeNode *p;
    visited[i] = true;
    cout << GL.adj_list[i].data << " ";
    p = GL.adj_list[i].first_edge;
    while(p){
        if(!visited[p->adjvex]){
            DFS2(GL, p->adjvex);
        }
        p = p->next;
    }
}
void DFSTraverse2(GraphAdjList GL){
    for(int i = 0; i < GL.vertexes_num; i++){
        visited[i] = false;                      // 初始化访问标志数组
    }
    for(int i = 0; i < GL.vertexes_num; i++){
        if(!visited[i]){
            DFS2(GL, i);                          // 对未访问过的顶点调用DFS
        }
    }
}


// 邻接矩阵的广度优先遍历算法
void BFSTraverse(MGraph G){
    queue<int> que;
    for(int i = 0; i < G.vertexes_num; i++){
        visited[i] = false;
    }

    for(int i = 0; i < G.vertexes_num; i++){                    // 遍历每一个顶点
        if(!visited[i]){                                        // 若未访问过就处理
            visited[i] = true;
            cout << G.vertexes[i] << " ";
            que.push(i);                                        // 将当前结点放入队列
            while(!que.empty()){                                // 当队列不为空时
                int k = que.front();
                que.pop();
                for(int j = 0; j < G.vertexes_num; j++){
                    if(G.arcs[k][j] == 1 && !visited[k]){    // 判断其他顶点若与当前顶点存在边且未访问过
                        visited[j] = true;
                        cout << G.vertexes[j] << " ";
                        que.push(j);
                    }
                }
            }
        }
    }
}

// 邻接表的广度优先遍历算法
void BFSTraverse2(GraphAdjList GL){
    EdgeNode *p;
    queue<int> que;
    for(int i = 0; i < GL.vertexes_num; i++){
        visited[i] = false;
    }
    for(int i = 0; i < GL.vertexes_num; i++){
        if(!visited[i]){
            visited[i] = true;
            cout << GL.adj_list[i].data << " ";
            que.push(i);
            while(!que.empty()){
                int k = que.front();
                que.pop();
                p = GL.adj_list[k].first_edge;                 // 找到当前顶点边表链表头指针
                while(p){
                    if(!visited[p->adjvex]){
                        visited[p->adjvex] = true;
                        cout << GL.adj_list[p->adjvex].data << " ";
                        que.push(p->adjvex);                    // 将此顶点如队列
                    }
                    p = p ->next;
                }

            }

        }
    }
}

/*  ------------- 图的遍历 end ---------------*/




int main(){
    return 0;
}
