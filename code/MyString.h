#ifndef _MYSTRING
#define _MYSTRING
#include<cstddef>
#include<cstring>
#include<iterator>
#include<time.h>
#include<stdio.h>
#include<iostream>
#include<typeinfo>


class MyString
{
public:
    static size_t DCtor;
    static size_t Ctor;
    static size_t CCtor;
    static size_t CAsign;
    static size_t MCtor;
    static size_t MAsign;
    static size_t Dtor;
    // 依次代表默认构造函数、直接构造函数、拷贝构造函数、拷贝赋值、移动构造函数、移动赋值、析构函数的累计调用次数
private:
   char* _data;
   size_t _len;

   void _init_data(const char* p){
       _data = new char[_len+1];
       memcpy(_data, p, _len);
       _data[_len] = '\0';
   }
public:
    // default constructor
    MyString():_data(nullptr), _len(0){++DCtor;}
    // constructor
    MyString(const char* p):_len(strlen(p)){++Ctor;_init_data(p);}
    // copy constructor
    MyString(const MyString& rhs):_len(rhs._len) {++CCtor;_init_data(rhs._data);}
    // copy assignment
    MyString& operator=(const MyString& rhs){
        ++CAsign;
        if(&rhs!=this){
            if(_data)delete[] _data;
            _len=rhs._len;
            _init_data(rhs._data);
        }
        return *this;
    }
    // move constructor
    MyString(MyString&& rhs)noexcept :_len(rhs._len), _data(rhs._data){
        ++MCtor;
        rhs._data=nullptr;
        rhs._len=0;
    }
    // move assignment
    MyString& operator = (MyString&& rhs) noexcept{
        ++MAsign;
        if(this!=&rhs){
            if(_data)delete[] _data;
            _data=rhs._data;
            _len = rhs._len;

            rhs._data=nullptr;
            rhs._len=0;
        }
        return *this;
    }
    // destructor
    ~MyString(){
        ++DCtor;
        if(_data)
            delete[] _data;
    }

    bool operator<(const MyString& rhs){
        size_t length = _len <= rhs._len ? _len:rhs._len;
        bool result = true;
        for(size_t i=0;i<length;i++){
            if(_data[i]>rhs._data[i])
                {
                    result=false;
                    break;
                }
        }
        if(!result && _len<rhs._len)result=true;
        return result;
    }
    bool operator== (const MyString& rhs){
        if(_len!=rhs._len) return false;
        for(size_t i=0;i<_len;i++){
            if(_data[i]!=rhs._data[i])
                return false;
        }
        return true;
    }
};
size_t MyString::Ctor=0;
size_t MyString::CCtor=0;
size_t MyString::CAsign=0;
size_t MyString::DCtor=0;
size_t MyString::Dtor=0;
size_t MyString::MCtor=0;
size_t MyString::MAsign=0;

class MyStrNoMove
{
public:
    static size_t DCtor;
    static size_t Ctor;
    static size_t CCtor;
    static size_t CAsign;
    static size_t MCtor;
    static size_t MAsign;
    static size_t Dtor;
    // 依次代表默认构造函数、拷贝构造函数、拷贝赋值、移动构造函数、移动赋值、析构函数的累计调用次数
private:
   char* _data;
   size_t _len;

   void _init_data(const char* p){
       _data = new char[_len+1];
       memcpy(_data, p, _len);
       _data[_len] = '\0';
   }
public:
    // default constructor
    MyStrNoMove():_data(nullptr), _len(0){++DCtor;}
    // constructor
    MyStrNoMove(const char* p):_len(strlen(p)){++Ctor;_init_data(p);}
    // copy constructor
    MyStrNoMove(const MyStrNoMove& rhs):_len(rhs._len) {++CCtor;_init_data(rhs._data);}
    // copy assignment
    MyStrNoMove& operator=(const MyStrNoMove& rhs){
        ++CAsign;
        if(&rhs!=this){
            if(_data)delete[] _data;
            _len=rhs._len;
            _init_data(rhs._data);
        }
        return *this;
    }

    // destructor
    ~MyStrNoMove(){
        ++DCtor;
        if(_data)
            delete[] _data;
    }

    bool operator<(const MyStrNoMove& rhs){
        size_t length = _len <= rhs._len ? _len:rhs._len;
        bool result = true;
        for(size_t i=0;i<length;i++){
            if(_data[i]>=rhs._data[i])
                {
                    result=false;
                    break;
                }
        }
        if(!result && length==rhs._len)result=true;
        return result;
    }
    bool operator== (const MyStrNoMove& rhs){
        if(_len!=rhs._len) return false;
        for(size_t i=0;i<_len;i++){
            if(_data[i]!=rhs._data[i])
                return false;
        }
        return true;
    }
};
size_t MyStrNoMove::Ctor=0;
size_t MyStrNoMove::CCtor=0;
size_t MyStrNoMove::CAsign=0;
size_t MyStrNoMove::DCtor=0;
size_t MyStrNoMove::Dtor=0;
size_t MyStrNoMove::MCtor=0;
size_t MyStrNoMove::MAsign=0;

template<typename T>
void output_static_data(const T& myStr){
    std::cout<<typeid(myStr).name()<<"--"<<std::endl;
    std::cout<<"CCtor="<<T::CCtor<<" "
            <<"MCtor="<<T::MCtor << " "
            <<"CAsign="<<T::CAsign << " "
            <<"MAsign="<<T::MAsign << " "
            <<"Dtor="<<T::Dtor << " "
            <<"Ctor="<<T::Ctor << " "
            <<"DCtor="<<T::DCtor<<std::endl;
}

template<typename M, typename NM>
void test_move(M c1, NM c2, long value=10000) {
    char buf[10];

    // 测试moveable
    std::cout << "test with moveable elements" << std::endl;
    typedef  typename std::iterator_traits<typename M::iterator>::value_type Vltype;
    
    clock_t start = clock();
    for (long i = 0;i < value;++i) {
        snprintf(buf, 10, "%d", rand());
        auto ite = c1.end();
        c1.insert(ite, Vltype(buf));
    }
    std::cout << "construction, mili-seconds:" << (clock() - start) << std::endl;
    std::cout << "size=" << c1.size() << std::endl;
    output_static_data(*(c1.begin()));
    std::cout << std::endl;
    // 测试Nomoveable
    std::cout << "test with non-moveable elements" << std::endl;
    typedef typename std::iterator_traits<typename NM::iterator>::value_type NVltype;
    start = clock();
    for (long i = 0;i < value;++i) {
        snprintf(buf, 10, "%d", rand());
        auto ite = c2.end();
        c2.insert(ite, NVltype(buf));
    }
    std::cout << "construction, mili-seconds:" << (clock() - start) << std::endl;
    std::cout << "size=" << c2.size() << std::endl;
    output_static_data(*(c2.begin()));
}

#endif

