#include "code/allhead.h"   // 包含全部头文件，以及using namespace std
#include "code/test.h"
#include "code/DataStruct/SmallTest.h"
#include "code/DataStruct/MySort.h"
#include "code/DataStruct/AVLTree.h"
#include "code/DataStruct/MyGraph.h"
#include "code/MyString.h"
struct ListNode{
    int val;
    ListNode* next;
    ListNode(): val(0), next(nullptr){}
    ListNode(int v): val(v), next(nullptr){}
    ListNode(int v, ListNode* n): val(v), next(n){}
};

class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        ListNode *dumpy = new ListNode(-1, head), *lastSorted=head, *cur = head->next;
        while(cur){
            if(lastSorted->val <= cur->val){
                lastSorted = lastSorted->next;
            }else{
                ListNode *prev=dumpy;
                while(prev->next->val <=cur->val){
                    prev=prev->next;
                }
                lastSorted->next = cur->next;
                cur->next = prev->next;
                prev->next = cur;
            }
            cur = lastSorted->next;
        }
        return dumpy->next;
    }
};
string myround(double a, int n){
    stringstream res;
	res<<setiosflags(ios::fixed);
    res << setprecision(n)<<a;
    return res.str();
}
int main()
{   
    cout<<myround(1.23333, 2);
    return 0;
}