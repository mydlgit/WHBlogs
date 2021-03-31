#ifndef _AVLTREE
#define _AVLTREE
# include<queue>
# include<iostream>

#define max(a,b) (a>b?a:b)
static const int ALLOWED_IMBALANCE=1;

class AVLTree
{
public:
    AVLTree():root(nullptr){}
    ~AVLTree(){
        makeEmpty();
    }
    void makeEmpty(){makeEmpty(root);}
    void insert(const int& x){insert(x, root);}
    int findMin(){return findMin(root)->element;}
    int findMax(){return findMax(root)->element;}
    void remove(const int& x){remove(x, root);};
    void printLevel();
private:
    struct AVLNode
    {   
            int element;
            AVLNode* left;
            AVLNode* right;
            int _height;
            AVLNode(const int& ele, AVLNode* lt, AVLNode* rt, int h=0)
            : element(ele), left(lt), right(rt), _height(h){}
    };
    AVLNode* root;
    int height(AVLNode* t) const{return t==nullptr?-1:t->_height;}
    void insert(const int& x, AVLNode* &t);
    void balance(AVLNode* &t);
    void makeEmpty(AVLNode* p);
    AVLNode* findMin(AVLNode* p);
    AVLNode* findMax(AVLNode* p);
    void remove(const int& x, AVLNode* &t);

    void RightRotate(AVLNode* &t);
    void LeftRightRotate(AVLNode* &t);
    void LeftRotate(AVLNode* &t);
    void RightLeftRotate(AVLNode* &t);
};

void AVLTree::makeEmpty(AVLNode* p){
    if(!p){
        makeEmpty(p->left);
        makeEmpty(p->right);
        delete p;
        p=nullptr;
    }
}

void AVLTree::insert(const int& x, AVLNode* &t){
    if(t==nullptr)t=new AVLNode(x, nullptr, nullptr);
    else if(x<t->element) insert(x, t->left);
    else if(t->element < x) insert(x, t->right);
    balance(t); //t是插入的节点, 沿插入过程逆序，判断路径上的节点平衡是否被破坏
}

void AVLTree::balance(AVLNode* &t){
    if(!t)return;
    if(height(t->left) - height(t->right) > ALLOWED_IMBALANCE)
        if(height(t->left->left) >= height(t->left->right))
            RightRotate(t); //单旋，向右旋转
        else
            LeftRightRotate(t);
    else if(height(t->right) - height(t->left) > ALLOWED_IMBALANCE)
            if(height(t->right->right) >= height(t->right->left))
                LeftRotate(t);//单旋，向左旋转
            else
                RightLeftRotate(t);
    t->_height = max(height(t->left), height(t->right)) + 1;
}

AVLTree::AVLNode* AVLTree::findMin(AVLNode* p){
    if(!p)return nullptr;
    while(p->left){
        p=p->left;
    }
    return p;
}

AVLTree::AVLNode* AVLTree::findMax(AVLNode* p){
    if(!p)return nullptr;
    while(p->right){
        p=p->right;
    }
    return p;
}

//右旋
void AVLTree::RightRotate(AVLNode*& t){
    AVLNode* lchild=t->left;
    t->left=lchild->right;
    lchild->right = t;
    t->_height = 1+max(height(t->left), height(t->right));
    lchild->_height = 1+max(height(lchild->left), t->_height);
    t=lchild;//让原始t的父节点现在指向新的儿子节点
}
//左旋
void AVLTree::LeftRotate(AVLNode*& t){
    AVLNode* rchild=t->right;
    t->right=rchild->left;
    rchild->left=t;
    t->_height = 1 + max(height(t->left), height(t->right));
    rchild->_height = 1 + max(t->_height, height(rchild->right));
    t=rchild;
}
//双旋， 先对失衡节点的左子节点做左旋，再对失衡节点做右旋
void AVLTree::LeftRightRotate(AVLNode*& t){
    LeftRotate(t->left);
    RightRotate(t);
}
//双旋， 先对失衡节点的右子节点做右旋，再对失衡节点做左旋
void AVLTree::RightLeftRotate(AVLNode*& t){
    RightRotate(t->right);
    LeftRotate(t);
}

void AVLTree::remove(const int& x, AVLNode* &t){
    if(!t)return;
    if(t->element > x)
        remove(x, t->left);
    else if(t->element < x)
        remove(x, t->right);
    else if(t->right && t->left){
        t->element = findMin(t->right)->element;
        remove(t->element, t->right);
    }else{
        AVLNode* tmp=t;
        t = t->left?t->left:t->right;
        delete tmp;
    }
    balance(t);
}

//层序遍历
void AVLTree::printLevel(){
    if(!root)return;
    std::queue<AVLNode*> node_queue;
    node_queue.push(root);
    while(!node_queue.empty()){
        AVLNode* front = node_queue.front();
        node_queue.pop();
        std::cout<<front->element<<" ";
        if(front->left)node_queue.push(front->left);
        if(front->right)node_queue.push(front->right);
    }
    std::cout<<std::endl;
}
#endif

