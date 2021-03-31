#ifndef _MYSORT
#define _MYSORT
#include<vector>
#include<random>
#include<time.h>
#include<iostream>

// 选择排序，增序
void selection_sort(std::vector<int>& vec){
    for(int i=0;i<vec.size();i++){
        int minIndex=i;
        for(int j=i+1;j<vec.size();j++){  
            if(vec[j]<vec[minIndex])minIndex=j;
        }
        std::swap(vec[i], vec[minIndex]);
    }
}

//冒泡排序
void maopao_sort(std::vector<int>& vec){
    for(int i=0;i<vec.size()-1;i++){
        for(int j=0;j<vec.size()-1-i;j++){
            if(vec[j]>vec[j+1])
                std::swap(vec[j], vec[j+1]);
        }
    }
}

// 插入排序
void insertion_sort(std::vector<int>& vec){
    for(int i=1;i<vec.size();i++){
        int tmp=std::move(vec[i]);
        int j=i;
        for(;j>=1&&vec[j-1]>tmp;--j){
           vec[j]=std::move(vec[j-1]);  //采用这种方式避免中间过程的相互交换
        }
        vec[j]=std::move(tmp);
    }
}
//对指定范围内的元素进行插入排序
void inside_insertion_sort(std::vector<int>& vec, int left, int right){
    for(int i=left+1;i<right+1;i++){
        int tmp=std::move(vec[i]);
        int j=i;
        for(;j>=left+1&&vec[j-1]>tmp;--j){
           vec[j]=std::move(vec[j-1]);  //采用这种方式避免中间过程的相互交换
        }
        vec[j]=std::move(tmp);
    }
}

// 希尔排序
void shell_sort(std::vector<int>& vec){
    for(int gap=vec.size()/2; gap>0;gap/=2){
        for(int i=gap;i<vec.size();i++){
            // 下面和插入排序过程相同，只不过交换的元素间隔为gap
            int temp=std::move(vec[i]);
            int j=i;
            for(;j>=gap && temp<vec[j-gap];j-=gap){
                vec[j] = std::move(vec[j-gap]);
            }
            vec[j]=std::move(temp);
        }
    }
}

// 堆排序
# define leftchild(i) (2*i+1)   //i位置的节点左儿子下标，因为数组是从0开始存储的
template<typename comparable>   // i:下滤位置，n:堆的逻辑大小, 随着删除操作，逻辑大小与数组大小并不一致
void percDown(std::vector<comparable>& vec, int i, int n){
    int child;
    comparable tmp;
    for(tmp=std::move(vec[i]); leftchild(i)<n;i=child){
        child = leftchild(i);
        if(child!=n-1 && vec[child]<vec[child+1])//左孩子不是堆的最后一个节点，且右孩子大于左孩子
            child++;
        if(tmp<vec[child])
            vec[i]=std::move(vec[child]);  //空穴下滤， 两个孩子中较大的一个放入空穴原来的位置
        else 
            break;
    }
    vec[i]=std::move(tmp);    
}
void heap_sort(std::vector<int>& vec){
    //构建最大堆
    for(int i=vec.size()/2 - 1; i>=0; i--)// i<=len/2-1, 则其左孩子下标<=len-1, 等于说明i节点没有右孩子
        percDown(vec, i, vec.size());
    
    // 删除
    for(int j=vec.size()-1;j>0;--j){
        std::swap(vec[0], vec[j]);
        percDown(vec, 0, j);
    }
}


//归并排序
void merge(std::vector<int>& a, std::vector<int>& tmpArr, int leftPos, int rightPos, int rightEnd){
    int leftEnd = rightPos-1;
    int tmpPos=leftPos;
    int numElements = rightEnd-leftPos+1;

    while(leftPos<=leftEnd && rightPos<=rightEnd){
        if(a[leftPos]<=a[rightPos])
            tmpArr[tmpPos++]=std::move(a[leftPos++]);
        else
            tmpArr[tmpPos++] = std::move(a[rightPos++]);
    }

    while(leftPos<=leftEnd)
        tmpArr[tmpPos++]=std::move(a[leftPos++]);
    while(rightPos<=rightEnd)
        tmpArr[tmpPos++]=std::move(a[rightPos++]);
    
    //将排序后的临时数组复制回原数组
    for(int i=0;i<numElements;++i, --rightEnd){
        a[rightEnd] = std::move(tmpArr[rightEnd]);
    }
}
void mergeSort(std::vector<int>& a, std::vector<int>& tmpArr, int left, int right){
   if(left<right){
        int mid=(left+right)/2;
        mergeSort(a, tmpArr, left, mid);
        mergeSort(a, tmpArr, mid+1, right);
        merge(a, tmpArr, left, mid+1, right);
   }    
}

void mergeSort2(std::vector<int>& nums, std::vector<int>& tmpArr, int left, int right){
    if(left>=right)return;
    int mid=(left+right)/2;
    mergeSort(nums, tmpArr, left, mid);
    mergeSort(nums, tmpArr, mid+1, right);

    for(int p=left;p<=right;p++){
        tmpArr[p]=nums[p];
    }
    int i=left, j=mid+1; //i,j分别是左右数组首元素的下标
    for(int k=left; k<=right;k++){
        // if(i==mid+1)//左侧数组已经添加完毕
        //     nums[k]=std::move(tmpArr[j++]);
        // else if(j==right+1 || tmpArr[i]<=tmpArr[j] )//右侧数组添加完毕或者左数组元素小于右数组元素
        //     nums[k]=std::move(tmpArr[i++]);
        // else{
        //     nums[k]=std::move(tmpArr[j++]);
        // }
        if(j==right+1 || tmpArr[i]<=tmpArr[j]) nums[k]=std::move(tmpArr[i++]);
        else nums[k]=std::move(tmpArr[j++]);    // i==mid+1 || tmpArr[j]<tmpArr[i]
    }
}
void merge_sort(std::vector<int>& a){
    std::vector<int> tmpArr(a.size());
    mergeSort2(a, tmpArr, 0, a.size()-1);
}

//快速排序 简易版
void simple_quick_sort(std::vector<int>& vec){
    if(vec.size()>1){
        std::vector<int> smaller, same, larger;
        auto pivot = vec[vec.size()/2];
        for(auto &v:vec){
            if(v<pivot)smaller.push_back(v);
            else if(v>pivot) larger.push_back(v);
            else same.push_back(v);
        }
        simple_quick_sort(smaller);
        simple_quick_sort(larger);
        std::move(begin(smaller), end(smaller), begin(vec));
        std::move(begin(same), end(same), begin(vec)+smaller.size());
        std::move(begin(larger), end(larger), end(vec)-larger.size());
    }
}
// 快速排序
void median3(std::vector<int>& a, int left, int right){
    /*三数中值分割：消除输入数据预先排序的坏情形*/
    int center = (left+right)/2;
    if(a[center]<a[left])
        std::swap(a[center], a[left]);
    if(a[right] < a[left])
        std::swap(a[right], a[left]);
    if(a[right]<a[center])
        std::swap(a[center], a[right]);

    //将pivot置于right-1处
    //对于不同的分割函数，pivot位置不同
    std::swap(a[center], a[right-1]);

}
//采用median3确定pivot
void _partition1(std::vector<int>& a, int left, int right){
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
        //i两侧的元素并非一定有序的，只是均小于等于或大于等于pivot
        //再将pivot从位置right-1换到i, 再对i两侧的元素做递归调用
        std::swap(a[i], a[right-1]);
        _partition1(a, left, i-1);
        _partition1(a, i+1, right);
    }else{  
        //数组元素小于5， 采用插入排序
        // inside_insertion_sort(a, left, right);

        //数组元素等于2，直接判断两者
        if(a[left]>a[right])
            std::swap(a[left], a[right]);
    }
}

//固定right位置上的元素为pivot
void _partition2(std::vector<int>& vec, int left, int right){
    if(left>=right)return;
    int pivot=vec[right];
    int i=left, j=right;
    while(i<j){
        while(i<j && vec[i]<=pivot)i++;
        while(i<j && vec[j]>=pivot)j--;
        if(i<j){
            swap(vec[i], vec[j]);
        }
    }
    swap(vec[i], vec[right]);
    _partition2(vec, left, i-1);
    _partition2(vec, i+1, right);
}
void quick_sort(std::vector<int>& vec){
    std::cout<<"median3:\n";
    _partition1(vec, 0, vec.size()-1);
    // std::cout<<"fix right:"
    // _partition2(vec, 0, vec.size()-1);
    
}

// 基数排序，num代表最多有几位，也可以通过查找数组中最大数来计算得到
void inside_radix_sort(std::vector<int>& vec, int num){
    std::vector<int>* buckets= new std::vector<int>[10];
    for(int i=0;i<num;i++){
        for(auto &v:vec){
            int j=i;
            auto copy=v;
            int tmp;
            while(j-->=0){
                tmp=copy%10;
                copy = (copy-tmp)/10;
            }
            tmp = tmp<0?-1*tmp:tmp; //第k位数
            buckets[tmp].push_back(v);
        }
        int k=0;
        for(int p=0;p<10;p++){
            for(auto& v:buckets[p]){
                vec[k++]=v;
            }
            buckets[p].clear();
        }
    }
    delete[] buckets;
}
void inside_radix_sort2(std::vector<int>& vec){
    std::vector<int> odd;   //奇数
    std::vector<int>  even; //偶数
    for(int i=0;i<32;i++){  //将整数看成32位的二进制
        for(auto &v:vec){
            if((v>>i & 1)==0)
                even.push_back(v);
            else
                odd.push_back(v);
        }
        int j=0;
        for(auto& v:even)
            vec[j++]=v;
        for(auto& v:odd)
            vec[j++]=v;
        even.clear();
        odd.clear();
    }
}
/*binary:true, 代表将每个整数看成32位的二进制位，这样就无需计算最大元素的位数了*/
void radix_sort(std::vector<int>& vec, bool binary=false){
    std::vector<int> negative, positive;
    int minNeg=0, maxPos=0;
    for(auto& v:vec){
        if(v<0){
            minNeg=v<minNeg?v:minNeg;
            negative.push_back(v);
        }else{
            maxPos=v>maxPos?v:maxPos;
            positive.push_back(v);
        }
    }
    int k=0;
    if(!binary){
        minNeg*=-1;
        int numNeg=0, numPos=0;
        while(minNeg){
            minNeg/=10;
            numNeg++;
        }
        while(maxPos){
            maxPos/=10;
            numPos++;
        }
        inside_radix_sort(negative, numNeg);
        inside_radix_sort(positive, numPos); 
        for(int i=negative.size()-1;  i>=0;i--){
            vec[k++]=negative[i];
        }
    }else{
        inside_radix_sort2(negative);
        inside_radix_sort2(positive);
        for(auto& v:negative)
            vec[k++]=v;
    }
    
    for(auto& v:positive)
        vec[k++]=v;
}

//计数基数排序
void inside_counting_radix_sort(std::vector<int>& vec, int num){
    for(int i=0;i<num;i++){
        int mod = 1, j=i;
        while(j-->0)mod*=10;
        // std::vector<int> count(10, 0), offset(10, 0);
        // for(int k=0;k<vec.size();k++){
        //     int tmp=(vec[k]/mod)%10;
        //     tmp = tmp>=0?tmp:-1*tmp;    //求第i位上数字为多少
        //     count[tmp]++;
        // }
        /*offset[k]存储位数为k的元素在新数组中的位置pos，每次安排桶中一个元素后，让pos值自增，
        这样桶中下一个元素的位置就会递增到下一位*/
        // for(int m=1;m<10;m++)
        //     offset[m]=offset[m-1]+count[m-1];
        
        // std::vector<int> copyVec=vec;
        // for(int n=0;n<copyVec.size();n++){
        //     int bit = (copyVec[n]/mod)%10;
        //     bit=bit<0?-1*bit:bit;
        //     vec[offset[bit]++]=copyVec[n];  //offset[bit]++ 表示桶中下一个元素的位置向后移动一位
        // }

        /*通过复用count来避免offset, count[k+1]表示位数为k的个数， 
        从小到大扫描，coutn[k]+=count[k-1]， 得到的count前10位正好就是之前的offset*/
        std::vector<int> count(11, 0);
        for(int k=0;k<vec.size();k++){
            int tmp=(vec[k]/mod)%10;
            tmp = tmp>=0?tmp:-1*tmp;    //求第i位上数字为多少
            count[tmp+1]++;
        }
        for(int m=1;m<11;m++)
            count[m]+=count[m-1];
        
        std::vector<int> copyVec=vec;
        for(int n=0;n<copyVec.size();n++){
            int bit = (copyVec[n]/mod)%10;
            bit=bit<0?-1*bit:bit;
            vec[count[bit]++]=copyVec[n];
        }
    }
}
void count_radix_sort(std::vector<int>& vec){
    std::vector<int> negative, positive;
    int minNeg=0, maxPos=0;
    for(auto& v:vec){
        if(v<0){
            minNeg=v<minNeg?v:minNeg;
            negative.push_back(v);
        }else{
            maxPos=v>maxPos?v:maxPos;
            positive.push_back(v);
        }
    }
    minNeg*=-1;
    int numNeg=0, numPos=0;
    while(minNeg){
        minNeg/=10;
        numNeg++;
    }
    while(maxPos){
        maxPos/=10;
        numPos++;
    }
    inside_counting_radix_sort(negative, numNeg);
    inside_counting_radix_sort(positive, numPos); 

    int k=0;
    for(int i=negative.size()-1;  i>=0;i--){
        vec[k++]=negative[i];
    }
    for(auto& v:positive)
        vec[k++]=v;
}

//排序算法测试程序
void testMySort(int num, void(*sort)(std::vector<int>&)){
    // std::uniform_int_distribution<int> u(INT32_MIN, INT32_MAX);
    std::uniform_int_distribution<int> u(-9999, 9999);
    std::default_random_engine e;
    // e.seed(clock());
    std::vector<int> vec(num);
    for(int i=0;i<num;i++)
        vec[i]=u(e);
    clock_t start=clock();
    sort(vec);
    long cost = clock()-start;
    std::cout<<"sorting cost time:"<<cost<<" ms"<<std::endl;
    if(num<=50){
        for(auto& v:vec){
            std::cout<<v<<" ";
        }
        std::cout<<std::endl;
    }
}
#endif