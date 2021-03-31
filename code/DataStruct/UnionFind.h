#ifndef _UNIONFIND
#define _UNIONFIND
#include<iostream>
# include<vector>
//不相交集类
class DisjSets{
private:
    std::vector<int> father; //存储每个节点的父节点，初始设为其自身
    std::vector<int> rank; //存储每个节点的估计高度，因为随着路径压缩，树的结构发生改变，高度会发生变化，初始值设为1
    int count;
public:
    explicit DisjSets(int numElements): father(numElements), rank(numElements, 1), count(numElements){
        for(int i=0;i<numElements;i++)father[i]=i;
    }
    int find(int x);
    void unionSets(int , int );  
    int getCount() const{return count;}
};

int DisjSets::find(int x){  //在查询时执行路径压缩，即让沿途的每个节点的父节点都为根节点
    return father[x]==x?x:(father[x]=find(father[x]));
}

void DisjSets::unionSets(int elem1, int elem2){
    int root1=find(elem1), root2=find(elem2);
    if(root1==root2){
        std::cout<<elem1<<" "<<elem2<<":"<<count<<std::endl;
        return;
    }
    count--;
    if(rank[root1] <= rank[root2])
        father[root1] = root2;  //让较深的树的根节点成为浅树的根的父节点
    else
        father[root2] = root1;
    //只有rank[root1]与rank[root2]相等树，合并才会增加根节点的高度，且此时是root1被合并到root2
    //因此只有rank[root2]++
    if(rank[root1]==rank[root2] && root1!=root2)
        rank[root2]++; 
}
#endif