#ifndef _TREE
#define _TREE
#include<iostream>
struct TreeNode {
	TreeNode* left, *right;
    int val;
	TreeNode():val(0), left(nullptr), right(nullptr){}
    TreeNode(int a):val(a), left(nullptr), right(nullptr){}
    TreeNode(int a, TreeNode* le, TreeNode* ri):val(a), left(le), right(ri){}
};

class BinarySearchTree {
public:
	BinarySearchTree() :root(nullptr){};
	BinarySearchTree(const BinarySearchTree& rhs) { root = clone(rhs.root); };
	~BinarySearchTree() { makeEmpty(); };

	const int& findMin() const;
	const int& findMax() const;
	bool contains(const int& val) const { return contains(val, root); };
	bool isEmpty() const { return root == nullptr; };
	void printTree(std::ostream &os = std::cout) const;

	void makeEmpty() { makeEmpty(root); };
	void insert(const int& x) { insert(x, root); };
	void remove(const int& x) { remove(x, root); };

	BinarySearchTree& operator=(const BinarySearchTree & rhs);

	TreeNode* getRoot(){return root;}
private:
	TreeNode* root;
	void insert(const int& x, TreeNode* &t);
	void remove(const int& x, TreeNode*& t);
	TreeNode* findMin(TreeNode* t)const;
	TreeNode* findMax(TreeNode* t)const;
	bool contains(const int& x, TreeNode* t) const;
	void makeEmpty(TreeNode* &t);
	void printTree(TreeNode* t, std::ostream &os)const;
	TreeNode* clone(TreeNode* t)const;
};

// public
const int& BinarySearchTree::findMin() const {
	return findMin(root)->val;
}

const int& BinarySearchTree::findMax() const {
	return findMax(root)->val;
}

// private
bool BinarySearchTree::contains(const int& val, TreeNode* t) const {
	if (t == nullptr)
		return false;
	else if (val == t->val) {
		return true;
	}
	else if (val > t->val) {
		return contains(val, t->right);
	}
	else {
		return contains(val, t->left);
	}
}

TreeNode* BinarySearchTree::findMin(TreeNode* t) const{
	if (t == nullptr)
		return nullptr;
	else if (t->left != nullptr)
		return findMin(t->left);
	else
		return t;
}

TreeNode* BinarySearchTree::findMax(TreeNode* t)const {
	if (t == nullptr)
		return nullptr;
	while (t->right != nullptr) {
		t = t->right;
	}
	return t;
}

void BinarySearchTree::insert(const int& x, TreeNode*& t) {
	if (t == nullptr) {
		t = new TreeNode(x, nullptr, nullptr);
	}
	else if (x < t->val) {
		insert(x, t->left);
	}
	else if (x > t->val) {
		insert(x, t->right);
	}
}

void BinarySearchTree::remove(const int& x, TreeNode*& t) {
	if (t == nullptr)
		return;
	else if (x < t->val) {
		remove(x, t->left);
	}
	else if (x > t->val) {
		remove(x, t->right);
	}
	else {
		if (t->left != nullptr && t->right != nullptr) {
			t->val = findMin(t->right)->val;	//找到被删节点右子树的最小节点，更新当前节点的值
			remove(t->val, t->right);	//因为右子树的最小节点最多只有右孩子，适用于下面的情况
		}
		else {
			TreeNode* oldNode = t;	// t现在是其父节点的左节点或右节点的指针的引用
			t = (t->left != nullptr) ? t->left : t->right;
			delete oldNode;
		}
	}
}

// 清空一棵树，后序遍历
void BinarySearchTree::makeEmpty(TreeNode* &t) {
	if (t != nullptr) {
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
		t = nullptr;
	}
}
TreeNode* BinarySearchTree::clone(TreeNode* t)const{
	if (t == nullptr)
		return nullptr;
	else {
		return new TreeNode(t->val, clone(t->left), clone(t->right));
	}
}

#endif