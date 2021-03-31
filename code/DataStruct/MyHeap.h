# ifndef _MYHEAP
# define _MYHEAP
#include<vector>

template<typename comparable>
class BinaryHeap{
private:
    int currentSize;    //当前数组元素个数，其也代表了新插入元素的第一个可用位置（从1开始）
    std::vector<comparable> array;
    void buildHeap();
    void percolateDown(int hole);
public:
    explicit BinaryHeap(int capacity=100);
    explicit BinaryHeap(const std::vector<comparable>& items);

    bool isEmpty() const{return currentSize==0;};
    const comparable findMin() const;

    void insert(const comparable& x);
    void insert(comparable& x){insert(static_cast<const>(x));};
    void deleteMin();
    void deleteMin(const comparable& minitem);
    void makeEmpty();
};

template<typename comparable>
BinaryHeap<comparable>::BinaryHeap(const std::vector<comparable>& items)
:array(items.size()+10), currentSize{int(items.size())}{
    for(int i=0;i<currentSize;++i){
        array[i+1]=items[i];
    }
    buildHeap();
}
template<typename comparable>
void BinaryHeap<comparable>::buildHeap(){
    for(int i=currentSize/2;i>0;i--){
        percolateDown(i);
    }
}

template<typename comparable>
void BinaryHeap<comparable>::insert(const comparable& x){
    if(currentSize==array.size()-1)array.resize(2*currentSize-1);
    int hole=++currentSize;
    comparable copy=x;
    array[0]=std::move(copy);  //暂时存放
    for(;x<array[hole/2]; hole/=2){     //最迟在hole=1时跳出，意味着X是最小的元素
        array[hole]=std::move(array[hole/2]);  
    }
    array[hole]=std::move(array[0]);
}

template<typename comparable>
void BinaryHeap<comparable>::deleteMin(const comparable& minitem){
    if(isEmpty())return;
    minitem = array[1];
    array[1]=std::move(array[currentSize--]);   //先让根节点存放末尾的元素，再执行下滤操作
    percolateDown(1);
}

template<typename comparable>
void BinaryHeap<comparable>::deleteMin(){
    if(isEmpty())return;
    array[1]=std::move(array[currentSize--]);   //先让根节点存放末尾的元素，再执行下滤操作
    percolateDown(1);
}

template<typename comparable>
void BinaryHeap<comparable>::percolateDown(int hole){
    int child;
    comparable tmp=std::move(array[hole]);
    for(;hole*2<currentSize;hole=child){
        child=hole*2;
        if(child!=currentSize && array[child+1]<array[child])++child;   //将空穴两个儿子较小者放入空穴
        if(array[child]<tmp)    //当前节点小于tmp，当前节点上移到空穴
            array[hole]=std::move(array[child]);
        else break; //直到当前节点大于tmp
    }
    array[hole] = std::move(tmp);
}
# endif