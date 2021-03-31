#ifndef _RBTREE
#define _RBTREE
#include<queue>
#include<iostream>

/*尚未实现*/
template<typename Comparable>
class RBTree{
private:
    struct RBNode
    {
        Comparable element;
        RBNode* left, right;
        int color;
        RBNode(const Comparable& rhs=Comparable{}, RBNode* lp=nullptr, RBNode* rp=nullptr, int c=BLACK)
        : element(rhs), left(lp), right(rp), color(c){}
    };
    RBNode* header;
    RBNode* nullNode;
    RBNode *current, *parent, *grand, *great;

    void reclaimMemory(RBNode* t);
    void printTree(RBNode* t) const;

    RBNode* clone(RBNode* t) const;

    void handleReorient(const Comparable& item);
    RBNode* rotate(const Comparable& item, RBNode* theParent);
    void RightRotate(RBNode* t);
    void LeftRotaet(RBNode* t);

public:
    explicit RBTree(const Comparable& negInf);
    RBTree(const RBTree& rhs);
    ~RBTree();

    const Comparable findMin() const;
    const Comparable findMax() const;
    bool contains(const Comparable& x) const;
    bool isEmpty();
    void printTree() const;

    void makeEmpty();
    void insert(const Comparable& x);
    void remove(const Comparable& x);

    enum {RED, BLACK};

    RBTree& operator=(cosnt RBTree& rhs);
};

template<typename Comparable>
RBTree<Comparable>::RBTree(const Comparable& negInf){
    nullNode = new RBNode;
    nullNode->left=nullNode->right=nullNode;
    header = new RBNode{negInf};
    header->left=header->right=nullNode;
}

template<typename Comparable>
RBTree<Comparable>::RBNode* RBTree<Comparable>::rotate(const Comparable& item, RBNode* theParent){

}
#endif