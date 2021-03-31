#ifndef _SMALLTEST
#define _SMALLTEST
#include "../allhead.h"
#include"tree.h"
#include "MySort.h"
#define max_(a, b) (a>b? a:b)
#define min_(a, b) (a>b? b:a)
#define min3(a, b, c)(min_(min_(a,b), min_(b,c)))
using namespace std;

/*给定一组序列，可能包含负数，求其中和最大的一段子序列*/
void MaxSubsequenceSum(){
    int a[] = {4, -3, 5, -2, -1, 2, 6, -2};   
    int sum=0, maxS=INT16_MIN;
    for(const auto& current:a){
        sum+=current;
        if(sum > maxS){
            maxS=sum;
        }else if (sum<0) sum=0; 
    }
    std::cout<<"Max Subsequence is "<<maxS<<std::endl;
}
/*求最小子序列和*/
void MinSubsequenceSum(){
    int a[] = {4, 2, 3, 4,0, -1};   
    long sum=0, minS=INT16_MAX;
    for(const auto& current:a){
       sum+=current;
       if(sum<minS){
           minS=sum;
       }else if(sum>=0)sum=0;
    }
    std::cout<<"Min Subsequence is "<<minS<<std::endl;
}
/*求最小正子序列和，即求最小的正数*/    

/*求最大子序列乘积*/
void MaxSubsequenceMul(){
    int a[] = {4, -3, 5, -2, -1, 2, 6, 2};   
    int n=sizeof(a)/sizeof(a[0]);
    int first=-1, last=-1, neg_num=0;
    int mul=1;
    int head=0, tail=n-1;
    while(head<=tail){
        if(a[head]<0){
            neg_num++;
            if(first<0)first=head;
        }
        if(a[tail]<0){
            neg_num++;
            if(last<0)last=tail;
        }
        head++;
        tail--;
    }
    
    if((neg_num&1)==0){
        for(auto& cur:a){
            mul*=cur;
        }
    }else{
        int mul_2=1, mul_3=1;
        for(int i=0;i<last;i++){
            mul_2*=a[i];
        }
        for(int i=first+1;i<n;i++){
            mul_3*=a[i];
        }
        mul = max_(mul_2, mul_3);
    }
    std::cout<<"Max Subsequence multpliation ="<<mul<<std::endl;
}

/*采用欧几里得算法计算最大公因数，复杂度O(log N)*/
void GCD(long m, long n){
    std::cout<<"gcd("<<m<<","<<n<<")=";
    while(n!=0){
        long rem = m%n;
        m = n;
        n = rem;
    }
    std::cout<<m<<std::endl;
}

/*递归计算x的任意次整数幂*/
long long MyPow(long x, int n){
    if(n==0) return 1;
    else if (n&1)    // n is old
    {
        return MyPow(x*x, n/2)*x;
    }else{
        return MyPow(x*x, n/2);
    }
}

/*Horner法则，计算多次项之和，Sum(a_i*x^i)*/
void PolySum(){
    int a[]={2, 1, 0, 8, 4};
    int x=3;
    std::ostringstream os;
    os<<"x="<<x<<" ";
    int n=sizeof(a)/sizeof(a[0]);
    long ploy=0;
    for(int i=n;i>=0;--i){
        if(a[i])
            {   
                if(a[i]>1)os<<a[i];
                if(i){
                    if(i>1)os<<"x^"<<i;
                    else os<<"x";
                    os<<"+";
                }
            }
        ploy+=x*ploy+a[i];  // 关键步骤
    }
    
    std::cout<<os.str()<<"="<<ploy<<std::endl;
  
}

/*厄拉多塞筛，计算小于N的素数*/
void Primer(int num){
    bool primer[num+1];
    int num_primer=0;
    std::cout<<"primer:"<<std::endl;
    for(int i=2;i<=sqrt(num);i++){
        if(!primer[i])
            {
                num_primer++;
                //std::cout<<i<<std::endl;
            }
        int j=1;    
        while(j*i<=num){
            if(!primer[j*i])
                primer[j*i]=true;
            j++;
        }
    }
    for(int i=sqrt(num)+1;i<=num;i++){
        if(!primer[i]){
            //std::cout<<i<<std::endl;
            num_primer++;
        }
    }
    std::cout<<"total number of primer is "<<num_primer<<" between 2~"<<num<<std::endl;
}

/*中缀表达式转后缀表达式*/
std::vector<std::string> infix2postfix(const std::string& str) {
	std::vector<std::string> result;
	std::stack<char> stack_;	//存储运算符和左括号
	std::map<char, int> priority;
	priority['('] = 10;
	priority['*'] = 9;
	priority['/'] = 9;
	priority['+'] = 8;
	priority['-'] = 8;
    
	char tmp = ' ', c;
	std::string tmp2="";
    if(str[0]=='-')
        result.push_back("0");
        
	for (int i = 0; i < str.size();i++) {
		c = str[i];
		if (c == '(')
			stack_.push(c);
		else if (c == '+' || c == '-' || c == '*' || c == '/') {
			if (tmp2 != "") {
				result.push_back(tmp2);
				tmp2 = "";
			}
			if (!stack_.empty()) {
				if (stack_.top()=='(' || priority[c] > priority[stack_.top()]) {
					stack_.push(c);
				}
				else {
					result.push_back(std::string(1, stack_.top()));
					stack_.pop();
					stack_.push(c);
				}
			}
			else {
				stack_.push(c);
			}
		}
		else if (c == ')') {
			result.push_back(tmp2);
			tmp2 = "";
			while (tmp != '(') {
				tmp = stack_.top();
				stack_.pop();
				if(tmp!='(')
					result.push_back(std::string(1, tmp));
			}
			tmp = ' ';
		}
		else {	//c是数字符或者小数点
			if (c != ' ' ) {	
					tmp2.push_back(c);
			}
			if (i == str.size()-1) {
				result.push_back(tmp2);
			}
		}
	}
	while (!stack_.empty()) {
		result.push_back(std::string(1, stack_.top()));
		stack_.pop();
	}
	return result;
}

/*后缀表达式(逆波兰记法)求解*/
double cal(double l, double r, std::string str){
	if (str == "+") {
		return l + r;
	}
	else if (str == "-") {
		return l - r;
	}
	else if (str == "*") {
		return l * r;
	}
	else {
		return l / r;
	}
}
double reversePolish(const std::string& str) {
	std::stack<double> stack_;
	std::vector<std::string> postfix = infix2postfix(str);
	double top=0, second=0;
	for (const auto &s : postfix) {
		if (s=="+" || s=="-" || s=="*" || s=="/") {	
			if (!stack_.empty()) {
				top = stack_.top();
				stack_.pop();
				second = stack_.top();
				stack_.pop();
				stack_.push(cal(second, top, s));
			}
		}
		else {
			stack_.push(atof(s.c_str()));
		}
	}
	return stack_.top();
}

/*Josephus问题:
    编号1~N，从1开报数，报数到M的数被删除，传递到其后一位重新从1报数，循环往复，直至全部被删除
*/
class Node{
public:
    Node(int init):data(init){}
    int data;
    Node* next=nullptr;
};
void Josephus(int M, int N){
    if(M==0){
        for(int i=1;i<=N;i++)std::cout<<i<<std::endl;
        return;
    }
    Node* p=new Node(1), *head=p;
    for(int i=2;i<=N;i++){
        Node* tmp = new Node(i);
        p->next = tmp;
        p=tmp;
    }
    p->next = head;
    int remain=N;
    
    Node* start=head;
    while(remain){
        int num=M-1;
        while(num--){
            head=head->next;
        }
        start=head;     //被删除节点的前一个节点
        head=head->next;    //被删除节点
        std::cout<<head->data<<std::endl;
        remain--;
        start->next=head->next;
        delete head;    //释放被删除节点
        head=start->next;
    }
    
}
//采用数组
void Josephus2(int M, int N){
    if(M==0){
        for(int i=1;i<=N;i++)std::cout<<i<<std::endl;
        return;
    }
    std::vector<bool> vec(N, false);
    int remain=N, start=0;
    while(true){
        int j=1;
        while(j<M){
            if(!vec[(++start)%N])j++;
        }
        start%=N;
        std::cout<<start+1<<std::endl;
        vec[start]=true;
        remain--;
        while(vec[(++start)%N]);
        start=start%N;
        if(remain==1){
            std::cout<<start+1<<std::endl;
            break;
        }
    }
}

void Josephus2_1(int M, int N){
    int a[N+1]; //存放指针，a[i]存放着下一个元素
    int b[N+1]; //出链顺序
    int i, j, k;
    for(int i=1;i<N;i++)a[i]=i+1;
    a[N]=1; //形成闭环

    k=1; j=N;
    for(i=1;i<=N;i++){
        while(k<M){
            j=a[j]; //移动指针
            k++;
        }
        b[i]=a[j];
        a[j] = a[a[j]];
        k=1;
        printf("%dout a[%d]=%d\n", b[i], j, a[j]);
    }
    for(int i=1;i<=N;i++)std::cout<<b[i]<<" ";
    std::cout<<std::endl;
}

//0,1,···,n-1这n个数字排成一个圆圈，
//从数字0开始，每次从这个圆圈里删除第M个数字（删除后从下一个数字开始计数）。求出这个圆圈里剩下的最后一个数字
void Josephus3(int M, int N){
    int f=0;
    for(int i=2;i<=N;i++)
        f = (f+M)%i;
    std::cout<<f<<std::endl; 
}

 //前序遍历
std::vector<int> preorderTraversal(TreeNode* root){
    if(!root)return {};
    std::vector<int> ans;
    std::stack<TreeNode*> st;
    while(root || !st.empty()){
        while(root){
            ans.push_back(root->val);
            st.push(root);
            root=root->left;
        }
        root = st.top()->right;
        st.pop();
    }
    return ans;
}
//中序遍历
std::vector<int> inorderTraversal(TreeNode* root){
    if(!root)return {};
    std::vector<int> ans;
    std::stack<TreeNode*> st;
    while(root || !st.empty()){
        while(root){
            st.push(root);
            root=root->left;
        }
        root=st.top();
        st.pop();
        ans.push_back(root->val);
        root=root->right;
    }
    return ans;
}
//后序遍历, 除去递归，提供了4种方法，前三种都需要O(N)的空间复杂度, morris只需O(1)空间复杂度
std::vector<int> postorderTraversal(TreeNode* root){
    if(!root)return {};
    std::vector<int> ans;
    std::stack<TreeNode*> st;
    st.push(root);
    TreeNode* cur;
    while(!st.empty()){
        cur=st.top();st.pop();
        if(cur){
            st.push(cur->left);
            st.push(cur->right);
            ans.push_back(cur->val); //访问顺序: 根、右、左，对结果逆序
        }
    }
    std::reverse(ans.begin(), ans.end());
    return ans;
}
std::vector<int> postorderTraversal2(TreeNode* root){
    if(!root)return {};
    std::vector<int> ans;
    std::stack<std::pair<TreeNode*, bool>> st;
    st.push(std::make_pair(root, false));
    std::pair<TreeNode*, bool>* cur; 
    while (!st.empty())
    {
        cur = &st.top();
        if(cur->second){//bool=true, 说明是子节点已经访问了
            ans.push_back(cur->first->val);
            st.pop();
        }else{ //bool=false, 说明当前节点的子节点尚未访问，将右孩子和左孩子先后入栈
            cur->second=true;
            if(cur->first->right) st.push(std::make_pair(cur->first->right, false));
            if(cur->first->left) st.push(std::make_pair(cur->first->left, false));
        }
    }
    return ans;
}
std::vector<int> postorderTraversal3(TreeNode* root){
    if(!root)return {};
    std::vector<int> ans;
    std::stack<TreeNode*> st;
    TreeNode* prev;
    while(root || !st.empty()){
        while(root){
            st.push(root);
            root=root->left;
        }
        root = st.top();
        if(!root->right || root->right==prev){
            ans.push_back(root->val);
            prev=root;
            st.pop();
            root=nullptr;
        }else
            root=root->right;
    }
    return ans;
}

//morros前序遍历
std::vector<int> preorderTraversal2(TreeNode* root){
    if(!root)return {};
    std::vector<int> ans;
    TreeNode* cur=root, *next=nullptr;
    while (cur)
    {
        next=cur->left;
        if(next){
            while(next->right && next->right!=cur)
                next=next->right;
            if(!next->right){
                next->right=cur;
                ans.push_back(cur->val);
                cur=cur->left;
            }else{
                next->right=nullptr;
                cur=cur->right;
            }
        }else
            {
                ans.push_back(cur->val);
                cur=cur->right;
            }
    }
    return ans;
            }
    //moris中序遍历
std::vector<int> inorderTranversal2(TreeNode* root){
    if(!root)return {};
    std::vector<int> ans;
    TreeNode *cur=root, *next=nullptr;
    while(cur){
        next=cur->left;
        if(next){
            while (next->right && next->right!=cur)
                next=next->right;
            if(!next->right){
                next->right=cur;
                cur=cur->left;
            }else{
                next->right=nullptr;
                ans.push_back(cur->val);
                cur=cur->right;
            }
        }else{
            ans.push_back(cur->val);
            cur=cur->right;
        }    
    }
    return ans;
}
//morris后序遍历
void addPath(std::vector<int> &vec, TreeNode *node) {
    int count = 0;
    while (node != nullptr) {
        ++count;
        vec.emplace_back(node->val);
        node = node->right;
    }
    reverse(vec.end() - count, vec.end());
}
std::vector<int> postorderTraversal4(TreeNode* root){
    if(!root)return {};
    std::vector<int> ans;
    TreeNode *cur=root, *next=nullptr;
    while(cur){
        next=cur->left;
        if(next){
            while (next->right && next->right!=cur)
                next=next->right;
            if(!next->right){
                next->right=cur;
                cur=cur->left;
            }else{
                next->right=nullptr;
                addPath(ans, cur->left);
                cur=cur->right;
            }
        }else
            cur=cur->right;
    }
    addPath(ans, root);
    return ans;
}

//层序遍历
std::vector<int> LayerTraversal(TreeNode* root){
    if(!root)return {};
    std::vector<int> ans;
    std::queue<TreeNode*> qu;
    qu.push(root);
    while(!qu.empty()){
        root=qu.front(); qu.pop();
        ans.push_back(root->val);
        if(root->left)qu.push(root->left);
        if(root->right)qu.push(root->right);
    }
    return ans;
}
//第二种形式的层序遍历，只是返回形式不同
std::vector<std::vector<int>> MulLayerTraversal(TreeNode* root){
    if(!root)return {};
    std::vector<std::vector<int>> ans;
    std::queue<TreeNode*> qu;
    qu.push(root);
    while(!qu.empty()){
        int len=qu.size();
        std::vector<int> tmp(len);
        for(int i=0;i<len;i++){
            root=qu.front(); qu.pop();
            tmp[i]=root->val;
            if(root->left)qu.push(root->left);
            if(root->right)qu.push(root->right);
        }
        ans.push_back(tmp);
    }
    return ans;
}

void testTree(){
    BinarySearchTree BSTree;
    BSTree.insert(10);
    BSTree.insert(9);
    BSTree.insert(11);
    BSTree.insert(13);
    BSTree.insert(8);
    std::vector<int> ans=inorderTranversal2(BSTree.getRoot());
    // 前序: 10,9,8,11,13
    // 中序：8,9,10,11,13
    // 后序：8,9,13,11,10;
    for(auto& v: ans){
        std::cout<<v<<" ";
    }
    std::cout<<std::endl;
}


/*寻找n个点中距离最近的两个点*/
struct point{
    point():x(INT32_MAX), y(INT32_MAX){}
    point(int a, int b): x(a), y(b){}
    int x, y;
};
double CmpDistance(point& p1, point& p2){
    return (p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y);
}
double inside_findClosed(std::vector<point>::iterator orderXBegin, //在区域内
                        std::vector<point>::iterator orderXEnd,    //不在区域内
    std::vector<point>& orderY){
        // 小于两个点，直接计算距离返回
        if(orderXEnd - orderXBegin == 1){return INT32_MAX;}
        else if(orderXEnd - orderXBegin == 2){
            return CmpDistance(*orderXBegin, *(orderXEnd-1));
        }else{
            //先找出x轴中分线mid
            int midLen=(orderXEnd - orderXBegin)/2;
            float mid = (*(orderXBegin+midLen)).x;
            std::vector<point> left(midLen+1), right(midLen+1); //预先分配大小，避免超出容量重新分配
            //然后根据mid, 对按纵坐标排序的orderY进行筛选
            int i=0, j=0;
            for(auto& p:orderY){
                if(p.x<mid)
                    left[i++] = p;
                else
                    right[j++] = p;
            }
            //递归求解左右两侧中的最近点的距离
            double minDistLeft = inside_findClosed(orderXBegin, orderXBegin+midLen, left);
            double minDistRight = inside_findClosed(orderXBegin+midLen, orderXEnd, right);
            double delta = minDistLeft>minDistRight?minDistRight:minDistLeft;

            //找出那些在距中分线不超过delta的点
            std::vector<point> strip;
            for(auto& p:orderY){
                if(std::abs(p.x-mid)<=delta)
                    strip.push_back(p);
            }
            int size=strip.size();  //strip中的点是按纵轴排序的
            for(int i=0;i<size;i++)
                for(int j=i+1;j<size;j++){
                    //如果两个点在纵轴上超过delta，则直接跳出，其后的点必然也超出delta
                    if(std::abs(strip[i].y - strip[j].y) > delta)break;   
                    else{
                        double dist=CmpDistance(strip[i], strip[j]);
                        if(dist<delta)
                            delta=dist;
                            
                    }
                }
            return std::sqrt(delta);
        }
}

void findClosedPoints(std::vector<point>& points){
    if(points.size()<=2) 
    {
        std::cout<<"number of point is less than 3"<<std::endl;
        return;
    }
    std::vector<point> orderX=points;
    auto cmpX=[](point p1, point p2) -> bool {return p1.x<p2.x;};
    std::sort(orderX.begin(), orderX.end(), cmpX);

    std::vector<point> orderY=points;
    auto cmpY=[](point p1, point p2) -> bool {return p1.y<p2.y;};
    std::sort(orderY.begin(), orderY.end(), cmpY);

    double minDistance=inside_findClosed(orderX.begin(), orderX.end(), orderY);
    std::cout<<"distance = "<<minDistance<<std::endl;
}


/*快速选择法，在N个元素中找到第k个最小的元素*/
int quickFind(std::vector<int>& a, int left, int right){
    if(left+2<=right){
        median3(a, left, right);
        const int pivot= a[right-1];    //经过三数中值分割后，选择倒数第二个数为pivot
        //开始分割
        int i=left, j=right-1;
        for(;;){
            while(a[++i]<pivot);
            while(a[--j]>pivot);
            if(i<j){
                std::swap(a[i], a[j]);  //此时i依旧在j左侧，a[i]>=pivot, a[j]<=pivot, 交换两者
            }else break;    // i已经移动到j右侧，跳出循环
        }
    
        //此时 pos<i的元素均小于等于pivot, pos>j的元素均大于等于pivot，
        //再将pivot从位置right-1换到i,
        std::swap(a[i], a[right-1]);
        return i;
    }else{
        if(a[left]>a[right]){
            std::swap(a[left], a[right]);
        }
        return left;
    }
}
void quick_find(std::vector<int>& vec, int k){
    if(k>0 && vec.size() < k)return;
    k = vec.size()-k+1;
    int left=0, right=vec.size()-1;
    while(true){
        int position=quickFind(vec, left, right);
        if(position<k-1)left=position+1;
        else if(position>k-1)right=position-1;
        else{
            std::cout<<"the kth minimum number is "<<" "<<vec[position]<<", k="<<k<<std::endl;
            return;
        }
    }
}


//一个长度为n+1的数组中，元素范围为1~n, 存在至少一个重复元素，找出重复元素，要求不改变原始数组
// time: O(Nlog N), sapce:O(1)
int countRange(std::vector<int>& nums, int start, int end){
    int count=0;
    for(auto&v:nums){
        if(v>=start && v<=end){
            count++;
        }
    }
    return count;
}
int findRepeatNumber(std::vector<int>& nums) {
    int start=1, length=nums.size(), end=length-1;
    while(end>=start){
        int mid=(end-start)/2 + start;
        int count = countRange(nums, start, mid);
        if(end==start){
            if(count>1)return start;
            else break;
        }
        if(count>(mid-start+1))
            end=mid;
        else
            start=mid+1;
    }
    return -1;
}

/*
输入数字 n，按顺序打印出从 1 到最大的 n 位十进制数。比如输入 3，则打印出 1、2、3 一直到最大的 3 位数 999;
这里对n没有限制，因此要考虑不是正数，以及能表示的数超出int、long long
*/
void IncreaseNum(std::string num){
    int len=num.size();
    while(num[0] != '0'){
        std::cout<<num<<std::endl;
        int tmp=0;
        while(++tmp<10){
            num[len-1]++;
            std::cout<<num<<std::endl;
        }
        num[len-1]='0';
        for(int i=len-2;i>=0;i--){
            if(num[i]!='9'){
                num[i]++;
                break;
            }else num[i]='0';
        }
    }
}
void printN(int n){
    if(n<=0)return;
    for(int i=1;i<=n;i++){
        if(i==1){
            for(int j=1;j<=9;j++)std::cout<<j<<std::endl;
        }else
            IncreaseNum("1"+std::string(i-1,'0'));
    }
}

// 回溯不适合n太大，否则递归产生的函数栈太深
void backtrack(std::string num, int index){
    if(index==num.size()){
        size_t pos = num.find_first_not_of('0');
        if(pos<num.size()){
            std::string sub = num.substr(pos, num.size()-pos);
            std::cout<<sub<<std::endl;
        }
        return;
    }
    for(int i=0;i<=9;i++){
        num[index+1]='0'+i; //做出选择，并加入路径中
        backtrack(num, index+1);    //进入到下一层回溯
    }
}
void printN2(int n){
    if(n<=0)return;
    backtrack(std::string(n+1, '0'), 0);
}

//二分查找, vec递增，
int binarySerach(std::vector<int> &vec, int target){
     if(vec.size()==0 || target<vec[0] || target>vec[vec.size()-1])return -1;

    int left=0, right=vec.size()-1;
    while(left<=right){
        int mid=left+(right-left)/2;
        if(target==vec[mid])return mid;
        else if(vec[mid] < target) left=mid+1;
        else if(vec[mid] > target) right=mid-1;
    }
    return -1;
}
// 二分查找，寻找左侧边界, 即最左边的target
int binarySearchLSide(std::vector<int>& vec, int target){
    if(vec.size()==0 || target<vec[0] || target>vec[vec.size()-1])return -1;

    int left=0, right=vec.size()-1;
    while(left<=right){
        int mid=left+(right-left)/2;
        if(target==vec[mid])right=mid-1; //收缩右侧边界，锁定左侧
        else if(vec[mid] < target) left=mid+1;
        else if(vec[mid] > target) right=mid-1;
    }
    if(left>=vec.size() || vec[left]!=target) return -1;
    return left;
}

// 二分查找，寻找右侧边界，即最右边的target
int binarySearchRSide(std::vector<int>& vec, int target){
    if(vec.size()==0 || target<vec[0] || target>vec[vec.size()-1])return -1;

    int left=0, right=vec.size()-1;
    while(left<=right){ //结束循环条件 right=left-1
        int mid=left+(right-left)/2;
        if(target==vec[mid])left=mid+1; //收缩左侧边界，锁定右侧
        else if(vec[mid] < target) left=mid+1;
        else if(vec[mid] > target) right=mid-1;
    }
    if(right<0 || vec[right]!=target) return -1;
    else return right;
}

//斜着打印方阵
void printMatrix(std::vector<std::vector<int> >& vec){ 
    int m=vec.size();
    for(int k=0;k<m;k++){
        for(int i=0;i<m-k;i++){
            int j=k+i;
            std::cout<<vec[i][j]<<" ";
        }
    }
}

//最长递增子序列，返回长度最长的递增子序列中，字典序最小的
std::vector<int> LongestSubseq(std::vector<int>& arr){
    int N=arr.size();
    int dp[N];  //dp[i]代表以arr[i]结尾的递增子序列长度
    std::vector<int> top;    //top.size()代表最长递增子序列长度
    for(int i=0;i<N;i++){
        int poker=arr[i];
        int left=0, right=top.size();
        while(left<right){  //寻找左侧边界
            int mid=(left+right)/2;
            if(top[mid] < poker)left=mid+1;
            else right=mid;
        }
        if(left==top.size()){
            top.emplace_back(poker);
            dp[i]=top.size();
        }else{
            top[left]=poker;
            dp[i]=left+1;
        }
    }
    for(int i=N-1, j=top.size();j>0;i--){
        // dp[i]==j, 说明arr[i]属于该递增子序列
        // 不同位置的i，可能dp[i]相同，但由于需要最小的字典序，因此后面位置的字符更符合条件，其小于前面的字符
        if(dp[i]==j)top[--j]=arr[i];
    }
    return top;
}

//LRU算法
struct DNode{
    int key, val;
    DNode* next, *prev;
    DNode(int k, int v):key(k), val(v), next(nullptr), prev(nullptr){}
};
class DoubleList{   //靠近链表尾部的数据表示最近使用的
private:
    DNode* head, *tail;
    int _size;
public:
    DoubleList():_size(0){
        head = new DNode(0, 0);
        tail = new DNode(0, 0);
        head->next=tail;
        tail->prev=head;
    }
    void addLast(DNode* x){
        x->prev=tail->prev;
        x->next=tail;
        tail->prev->next = x;
        tail->prev=x;
        _size++;
    }
    void remove(DNode* x, bool reuse){   //要求x一定在链表中
        x->prev->next=x->next;
        x->next->prev = x->prev;
        _size--;
        if(!reuse)  //因为x节点可能是被永久删除，也有可能是被移到链表尾
            delete x;
    }
    int removeFirst(){
        if(head->next == tail)return 0;
        int key=head->next->key;
        remove(head->next, false);
        return key;
    }
    int size() const{return _size;}
};

class LRUCache{
private:
    unordered_map<int, DNode*> umap;
    DoubleList cache;
    int cap;    //最大容量
    
    //将某个key提升为最近使用的
    void makeRecently(int key){
        DNode* x=umap[key];
        cache.remove(x, true);
        cache.addLast(x);
    }
    //添加最近使用的
    void addRecently(int key, int val){
        DNode *x=new DNode(key, val);
        cache.addLast(x);
        umap[key] = x;
    }
    //删除某个key
    void deleteKey(int key){
        if(umap.count(key)==0)return;

        DNode *x=umap[key];
        cache.remove(x, false);
        umap.erase(key);
    }
    //删除最久未使用的
    void removeLeastRecently(){
        umap.erase(cache.removeFirst());
    }
public:
    LRUCache(int capacity): cap(capacity){}
    int get(int key){
        if(umap.count(key)==0) return -1;
        makeRecently(key);  //将该数据提升为最近使用
        return umap[key]->val;
    }
    void put(int key, int val){
        if(umap.count(key)){
            // deleteKey(key);
            // addRecently(key, val);
            umap[key]->val = val;
            makeRecently(key);
            return;
        }
        if(cache.size() == cap)
            removeLeastRecently();
        addRecently(key, val);
    }
};


// LFU算法
struct DNode2{
    int key;
    DNode2 *next, *prev;
    DNode2(int k):key(k){}
};
class linkHash{
private:
    unordered_map<int, DNode2*> umap;
    DNode2 *head, *tail;
    int _size=0;
public:
    linkHash(){
        head = new DNode2(-1); tail=new DNode2(-1);
        head->next = tail; tail->prev=head;
    }
    ~linkHash(){
        while(head){
            DNode2 *tmp=head->next;
            delete head;
            head=tmp;    
        }
    }

    void push_back(int key){//从尾部插入最新访问的
        DNode2* x = new DNode2(key);
        umap[key]=x;
        x->prev = tail->prev;
        x->next = tail;
        tail->prev->next=x;
        tail->prev=x;
        _size++;
    }
    void remove(int key){
        DNode2 *x=umap[key];
        umap.erase(key);
        x->prev->next = x->next;
        x->next->prev = x->prev;
        delete x;
        _size--;
    }
    int removeFront(){//返回被删除节点的key
        DNode2 *x=head->next;
        int key = x->key;
        remove(key);
        return key;
    }
    int size()const {return _size;}
};
class LFUCache {
public:
    LFUCache(int capacity): cap(capacity) {}
    
    int get(int key) {
        if(key2VF.count(key)==0)return -1;
        increaseFre(key);
        return key2VF[key].first;
    }
    
    void put(int key, int value) {
        if(cap==0)return;
        if(key2VF.count(key)!=0){
            key2VF[key].first=value;
        }else{
            if(key2VF.size()==cap)
                deleteLeastFreqKey();
            key2VF[key] = make_pair(value, 0);
            minFreq = 1;    //插入新节点后
        }
        increaseFre(key);
    }

private:
    unordered_map<int, linkHash*> freq2key;  // frequency -> list of key order by time
    unordered_map<int, pair<int, int>> key2VF;  // key-> val+fre
    int cap=10; //默认值
    int minFreq;

    void increaseFre(int key){
        int oldFreq = key2VF[key].second++;
        int newFreq = key2VF[key].second;
  
        if(oldFreq!=0){
            freq2key[oldFreq]->remove(key);
            if(freq2key[oldFreq]->size()==0)
            {
                freq2key.erase(oldFreq);
                if(oldFreq==minFreq)minFreq++;
            }
        }

        if(freq2key.count(newFreq)==0)
            freq2key[newFreq] = new linkHash();
        freq2key[newFreq]->push_back(key);
    }
    void deleteLeastFreqKey(){
       linkHash* x = freq2key[minFreq];
       int key = x->removeFront();
       if(x->size()==0) freq2key.erase(minFreq);
       key2VF.erase(key);
    }
};

// KMP算法
void getNext(std::vector<int>& next, string& p){
    next[0] = -1;
    int j=0, k=-1;
    while(j<p.size()-1){
        if(k==-1 || p[j]==p[k]){
            j++;
            k++;
            next[j] = k;
        }else 
            k = next[k];
    }
}
int KMP(string& s, string& p){
    if(p.size() == 0 || s.size()<p.size())return -1;
    vector<int> next(p.size());
    getNext(next, p);
    int i=0, j=-1;
    int sLen = s.size(), pLen = p.size();
    while(i<sLen && j<pLen){
        if(j==-1 || s[i]==p[j]){
            i++;
            j++;
        }else j=next[j];
    }
    if(j==pLen)return i-j;
    else return -1;
}
#endif