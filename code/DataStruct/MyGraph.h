#ifndef _MYGRAPH
#define _MYGRAPH
#include <list>
#include "MyHeap.h"
#include<vector>
#include<iostream>
#include<string>
#include<queue>
#include<math.h>

struct Vertex{
    Vertex(std::string str): name(str){}
    std::list<std::pair<Vertex*, int>>  adj;    //邻接表
    bool known=false;
    int dist=INT32_MAX;
    Vertex* prev=nullptr;   //在dijkrstra和prim算法中有用
    std::string name;
};

void printPath(Vertex v){
    if(v.prev){
        printPath((*v.prev));
        std::cout<<" to ";
    }
    std::cout<<v.name;
}
void dijkrsta(std::vector<Vertex*>& vertexs, Vertex* start, Vertex* target){
    /*
        Vertex中的dist代表起始节点到该节点的距离，
        prev则是这条路径上的上一个节点
    */
    start->dist=0;
    bool visitedAll = true;
    while(true){
        //寻找未被标记过的距离start最近的节点
        int minDist = INT32_MAX, minIndex=0;
        for(int i=0;i<vertexs.size();i++){
            if(!vertexs[i]->known && vertexs[i]->dist<minDist){
                minDist=vertexs[i]->dist;
                minIndex=i;
                visitedAll=false;
            }
        }
        //全部标记过，跳出
        if(visitedAll) break;
        Vertex* front=vertexs[minIndex];
        front->known=true;
        for(auto& pp:front->adj){
            if(!pp.first->known){
                int neighbor_cost=pp.second;    //front到相邻节点的距离
                if(front->dist+neighbor_cost<pp.first->dist){   //pp.first->dist代表之前由start直接到pp的距离
                    //说明经由front到达pp距离更小
                    //更新start到pp所需的距离
                    pp.first->dist=front->dist+neighbor_cost;
                    pp.first->prev=front;
                }
            }
        }
        visitedAll=true;
    }
    printPath(*target);
}

void Prim(std::vector<Vertex*>& vertexs, Vertex* start){
    start->dist=0;
    bool visitedAll=false;
    /*
        此时Vertex中的dist代表由所有konwn=true的顶点到该节点的最小距离，
        具有最小距离的那个节点就是prev
    */
    while(true){
        //寻找未被标记过的距离start最近的节点
        int minDist = INT32_MAX, minIndex=0;
        for(int i=0;i<vertexs.size();i++){
            if(!vertexs[i]->known && vertexs[i]->dist<minDist){
                minDist=vertexs[i]->dist;
                minIndex=i;
                visitedAll=false;
            }
        }
        //全部标记过，跳出
        if(visitedAll) break;
        Vertex* front=vertexs[minIndex];
        front->known=true;
        for(auto& pp:front->adj){
            if(!pp.first->known){
                int neighbor_cost=pp.second;    
                if(neighbor_cost<pp.first->dist){   
                    pp.first->dist=front->dist+neighbor_cost;
                    pp.first->prev=front;
                }
            }
        }
        visitedAll=true;
    }
    std::cout<<"Minimum Spanning Tree:"<<std::endl;
    for(auto& v:vertexs){
        if(v->prev)
            std::cout<<"("<<v->prev->name<<","<<v->name<<")"<<std::endl;
    }
}

void testDijkstra(){
    Vertex v1("v1"), v2("v2"), v3("v3"), v4("v4"), v5("v5"), v6("v6"), v7("v7");
    v1.adj.push_back(std::make_pair(&v2, 2));
    v1.adj.push_back(std::make_pair(&v4, 1));

    v2.adj.push_back(std::make_pair(&v4, 3));
    v2.adj.push_back(std::make_pair(&v5, 10));

    v3.adj.push_back(std::make_pair(&v1, 4));
    v3.adj.push_back(std::make_pair(&v6, 5));

    v4.adj.push_back(std::make_pair(&v3, 2));
    v4.adj.push_back(std::make_pair(&v5, 2));
    v4.adj.push_back(std::make_pair(&v6, 8));
    v4.adj.push_back(std::make_pair(&v7, 4));

    v5.adj.push_back(std::make_pair(&v7, 6));
    v7.adj.push_back(std::make_pair(&v6, 1));

    std::vector<Vertex*> vertexs{&v1, &v2, &v3, &v4, &v5, &v6, &v7};
    dijkrsta(vertexs, &v1, &v6);
}

void testPrim(){
    Vertex v1("v1"), v2("v2"), v3("v3"), v4("v4"), v5("v5"), v6("v6"), v7("v7");
    v1.adj.push_back(std::make_pair(&v2, 2));
    v1.adj.push_back(std::make_pair(&v4, 1));
    v1.adj.push_back(std::make_pair(&v3, 4));

    v2.adj.push_back(std::make_pair(&v1, 2));
    v2.adj.push_back(std::make_pair(&v4, 3));
    v2.adj.push_back(std::make_pair(&v5, 10));

    v3.adj.push_back(std::make_pair(&v1, 4));
    v3.adj.push_back(std::make_pair(&v6, 5));
    v3.adj.push_back(std::make_pair(&v4, 2));

    v4.adj.push_back(std::make_pair(&v1, 1));
    v4.adj.push_back(std::make_pair(&v2, 3));
    v4.adj.push_back(std::make_pair(&v3, 2));
    v4.adj.push_back(std::make_pair(&v5, 2));
    v4.adj.push_back(std::make_pair(&v6, 8));
    v4.adj.push_back(std::make_pair(&v7, 4));

    v5.adj.push_back(std::make_pair(&v2, 10));
    v5.adj.push_back(std::make_pair(&v4, 2));
    v5.adj.push_back(std::make_pair(&v7, 6));

    v6.adj.push_back(std::make_pair(&v4, 8));
    v6.adj.push_back(std::make_pair(&v3, 5));
    v6.adj.push_back(std::make_pair(&v7, 1));

    v7.adj.push_back(std::make_pair(&v6, 1));
    v7.adj.push_back(std::make_pair(&v4, 4));
    v7.adj.push_back(std::make_pair(&v5, 6));

    std::vector<Vertex*> vertexs{&v1, &v2, &v3, &v4, &v5, &v6, &v7};
    Prim(vertexs, &v1);
}

void floyd(std::vector<std::vector<std::pair<int, int>> >&adjacents){
    //adjacents存储所有节点的相邻节点，若没有，则adjacent[i]={};
    //pair<相邻节点，边的权值>
    int numVertexs = adjacents.size();
    std::vector<std::vector<int> > edges(numVertexs, std::vector<int>(numVertexs, INT32_MAX/2));
    for(int i=0;i<numVertexs;i++){
        edges[i][i] = 0;
        for(auto& p:adjacents[i]){
            edges[i][p.first] = p.second;
        }
    }
    for(int k=0;k<numVertexs;k++){
        for(int i=0;i<numVertexs;i++){
            for(int j=0;j<numVertexs;j++){
                edges[i][j] = std::min(edges[i][j], edges[i][k]+edges[k][j]);
            }
        }
    }
    int i=1;
}

void testFloyd(){
    std::vector<std::vector<std::pair<int, int>> > adjacets{
        std::vector<std::pair<int, int>>{std::make_pair(1, 10), std::make_pair(2, 7)},
        std::vector<std::pair<int, int>>{std::make_pair(0, 10), std::make_pair(2, 2), std::make_pair(3, 1)},
        std::vector<std::pair<int, int>>{std::make_pair(0, 7), std::make_pair(1, 2), std::make_pair(3, 5)},
        std::vector<std::pair<int, int>>{std::make_pair(1, 1), std::make_pair(2, 5)}
    };
    floyd(adjacets);
}

void dfs(Vertex& ver){
    std::cout<<ver.name<<" ";
    ver.known=true;
    for(std::pair<Vertex*, int>& p:ver.adj){
        Vertex& v= *(p.first);
        if(!v.known)
            dfs(v);
    }
}
void bfs(Vertex* ver){
    std::queue<Vertex*> q;
    ver->known=true;
    q.push(ver);
    while(!q.empty()){
        Vertex* head=q.front();
        std::cout<<head->name<<" ";
        q.pop();
        for(auto& p: head->adj){
            if(!p.first->known){
                p.first->known=true;
                q.push(p.first);
            }            
        }
    }
}
void testDFS(){
    Vertex v1("v1"), v2("v2"), v3("v3"), v4("v4"), v5("v5"), v6("v6"), v7("v7");
    v1.adj.push_back(std::make_pair(&v2, 2));
    v1.adj.push_back(std::make_pair(&v4, 1));
    v1.adj.push_back(std::make_pair(&v3, 4));

    v2.adj.push_back(std::make_pair(&v1, 2));
    v2.adj.push_back(std::make_pair(&v4, 3));
    v2.adj.push_back(std::make_pair(&v5, 10));

    v3.adj.push_back(std::make_pair(&v1, 4));
    v3.adj.push_back(std::make_pair(&v6, 5));
    v3.adj.push_back(std::make_pair(&v4, 2));

    v4.adj.push_back(std::make_pair(&v1, 1));
    v4.adj.push_back(std::make_pair(&v2, 3));
    v4.adj.push_back(std::make_pair(&v3, 2));
    v4.adj.push_back(std::make_pair(&v5, 2));
    v4.adj.push_back(std::make_pair(&v6, 8));
    v4.adj.push_back(std::make_pair(&v7, 4));

    v5.adj.push_back(std::make_pair(&v2, 10));
    v5.adj.push_back(std::make_pair(&v4, 2));
    v5.adj.push_back(std::make_pair(&v7, 6));

    v6.adj.push_back(std::make_pair(&v4, 8));
    v6.adj.push_back(std::make_pair(&v3, 5));
    v6.adj.push_back(std::make_pair(&v7, 1));

    v7.adj.push_back(std::make_pair(&v6, 1));
    v7.adj.push_back(std::make_pair(&v4, 4));
    v7.adj.push_back(std::make_pair(&v5, 6));

    // dfs(v1);
    bfs(&v1);
}
#endif
