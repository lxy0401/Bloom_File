#include "bitmap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

uint64_t GetSize(uint64_t capacity)
{
    uint64_t size = capacity/(sizeof(BitmapType)*8)+1;
    return size;
}

void BitmapInit(Bitmap* bm,uint64_t capacity)
{
    if(bm == NULL)
    {
        //非法输入
        return ;
    }
    bm->capacity = capacity;//capacity 表示该位图能表示的最大的数字
    uint64_t size = GetSize(capacity);//size表示申请内存时对应数组元素个数
    bm->data = (BitmapType*)malloc(sizeof(BitmapType)*size);
    memset(bm->data,0,sizeof(BitmapType)*size);
}

void BitmapDestroy(Bitmap* bm)
{
    if(bm == NULL)
    {
        return ;
    }
    bm->capacity = 0;
    free(bm->data);
    return ;
}

//测试某一位是否为1
//此处先实现Test是为了后续测试方便

void GetOffset(uint64_t index,uint64_t* n,uint64_t* offset)
{
    *n = index/(sizeof(BitmapType)*8);
    *offset = index%(sizeof(BitmapType)*8);
    return ;
}

int BitmapTest(Bitmap* bm,uint64_t index)
{
    if(bm == NULL || index >= bm->capacity)
    {
        return 0;
    }
    uint64_t n,offset;
    GetOffset(index,&n,&offset);
    uint64_t ret = bm->data[n]&(0x1ul << offset);
    return ret>0?1:0;
}

//将某一位设为1
void BitmapSet(Bitmap* bm,uint64_t index)
{
    if(bm == NULL)
    {
        return ;
    }
    uint64_t n,offset;
    GetOffset(index,&n,&offset);
    bm->data[n] |=(0x1ul << offset);
    return ;
}

//将某一位设为0
void BitmapUnset(Bitmap* bm,uint64_t index)
{
    if(bm == NULL || index >= bm->capacity)
    {
        return;
    }
    uint64_t n,offset;
    GetOffset(index,&n,& offset);
    bm->data[n]&=-(0x1ul << offset);
    return ;
}

//全部赋值为1
void BitmapFill(Bitmap* bm)
{
    if(bm == NULL)
    {
        return;
    }
    uint64_t size = GetSize(bm->capacity);
    memset(bm->data,0xff,sizeof(BitmapType)*size);
    return;
}

//全部赋值为0
void BitmapClear(Bitmap* bm)
{
    if(bm == NULL)
    {
        return ;
    }
    uint64_t size = GetSize(bm->capacity);
    memset(bm->data,0x0,sizeof(BitmapType)*size);
    return;
}

/************************
 *
 *
 *
 * 以下为测试代码
 *
 *
 ***************************/
#if 0
#include <stdio.h>
#define TEST_HEAD printf("\n===========%s================\n",__FUNCTION__);
void TestSet()
{
    TEST_HEAD;
    Bitmap bm;
    BitmapInit(&bm,100);
    BitmapSet(&bm,50);
    int ret = BitmapTest(&bm,50);
    printf("ret expected 1,actual %d\n",ret);
    ret = BitmapTest(&bm,20);
    printf("ret expected 0,actual %d\n",ret);
}

void TestUnset()
{
    TEST_HEAD;
    Bitmap bm;
    BitmapInit(&bm,100);
    BitmapUnset(&bm,50);
    int ret = BitmapTest(&bm,50);
    printf("ret expected 0,actual %d\n",ret);
    ret = BitmapTest(&bm,20);
    printf("ret expected 0,actual %d\n",ret);
}

void TestFill()
{
    TEST_HEAD;
    Bitmap bm;
    BitmapInit(&bm,100);
    BitmapFill(&bm);
    int ret = BitmapTest(&bm,50);
    printf("ret expected 1,actual %d\n",ret);
    ret = BitmapTest(&bm,0);
    printf("ret expected 1,actual %d\n",ret);
    ret = BitmapTest(&bm,99);
    printf("ret expected 1,actual %d\n",ret);
}

void TestClear()
{
    TEST_HEAD;
    Bitmap bm;
    BitmapInit(&bm,100);
    BitmapClear(&bm);
    int ret = BitmapTest(&bm,50);
    printf("ret expected 0,actual %d\n",ret);
    ret = BitmapTest(&bm,0);
    printf("ret expected 0,actual %d\n",ret);
    ret = BitmapTest(&bm,99);
    printf("ret expected 0,actual %d\n",ret);
}

int main()
{
    TestSet();
    TestUnset();
    TestFill();
    TestClear();
    return 0;
}

#endif
