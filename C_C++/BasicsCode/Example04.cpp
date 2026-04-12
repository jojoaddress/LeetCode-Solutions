#include <iostream>
#include <math.h>
using namespace std;

struct st
{
    int data;
    struct st *next;
} a[3]={5,&a[1],7,&a[2],9,NULL}, *p = a;
int main()
{
    p++->data;
    p->data++;
    (*p).data++;
    ++p->data;
    return 0;
}
/**
 * p++->data;：这行代码实际上没有改变 data 的值，因为它只是获取了 data 的值然后丢弃了。但是，由于 p++ 的副作用，p 现在指向数组 a 的第二个元素。
 * p->data++;：这行代码将 p 指向的结构体的 data 成员的值增加了 1。
 * (*p).data++;：这行代码也将 p 指向的结构体的 data 成员的值增加了 1。
 * ++p->data;：这行代码将 p 指向的结构体的 data 成员的值再次增加了 1。
*/