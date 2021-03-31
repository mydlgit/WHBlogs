#ifndef _TEST
#define _TEST
#include "allhead.h"

class CTest {
 public:
  virtual void Test1(void)
	{
		cout<< "CTest Test1\n";
	}
	virtual void Test2(void)
	{
		cout<< "CTest Test2\n";
	}
};

typedef void(*fun)();
void testT(){
    CTest cc;
    typedef long long int64;    // 64位机上，指针大小是8个Byte
    int64* Vptr=(int64*)(&cc);  //虚指针值代表的是虚函数表入口地址
	int64* pVtbl = (int64*)*Vptr;	    //虚函数表是一个数组，数组元素是函数指针，pVtbl相当于数组元素首地址
	int64* pFirstVf = (int64*)(pVtbl[0]);		//pVtbl[0] 等价于 *(pVtbl)
    int64* pFirstVf2 = (int64*)*pVtbl;
	int64* pSecondVf = (int64*)(pVtbl[1]);      //pVtbl[1] 等价于 *(pVtbl+1)
    int64* pSecondVf2 = (int64*)*(pVtbl+1);
    
    fun pf;
    pf = (fun)pFirstVf;
    pf();   // CTest Test1
    pf = (fun)pFirstVf2;
    pf();   //CTest Test1
    pf = (fun)pSecondVf;
    pf(); //CTest Test2
    pf = (fun)pSecondVf2;
    pf();   //CTest Test2
}
#endif