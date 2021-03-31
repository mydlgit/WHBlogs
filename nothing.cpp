#include "code/allhead.h"   // 包含全部头文件，以及using namespace std
#include "code/test.h"
#include "code/DataStruct/SmallTest.h"
#include "code/DataStruct/MySort.h"
#include "code/DataStruct/AVLTree.h"
#include "code/DataStruct/MyGraph.h"
#include "code/MyString.h"

class demo{
public:
    demo(){}
    virtual ~demo(){
        cout<<"demo dstor"<<endl;
    }
};
int main()
{   
    int n;
    cin>>n;
    int dp[n];
    for(int i=0;i<n;i++)cin>>dp[i]
    return 0;
}