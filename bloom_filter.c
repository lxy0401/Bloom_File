#include "bloom_filter.h"
#include <stdlib.h>
#include "hash_func.h"
#include "bitmap.h"

#define BitmapMaxSize 10000

void BloomFilterInit(BloomFilter* bf)
{
    if(bf == NULL)
    {
        return ;
    }
    BitmapInit(&bf->bm,BitmapMaxSize);
    bf->bloom_hash[0] = SDBMHash;
    bf->bloom_hash[1] = BKDRHash;
    return ;
}


void BloomFilterDestroy(BloomFilter* bf)
{
    if(bf == NULL)
    {
        return ;
    }
    bf->bloom_hash[0] = NULL;
    bf->bloom_hash[1] = NULL;
    BitmapDestroy(&bf->bm);
    return ;
}

void BloomFilterInsert(BloomFilter* bf,const char* str)
{
    if(bf == NULL || str == NULL)
    {
        return ;
    }
    size_t i = 0;
    for(; i < BloomHashCount ; ++i)
    {
        uint64_t hash = bf->bloom_hash[i](str)% BitmapMaxSize;
        BitmapSet(&bf->bm,hash);
    }
    return ;
}


int BloomFilterIsExit(BloomFilter* bf,const char* str)
{
    if(bf == NULL || str == NULL)
    {
        return 0;
    }
    size_t i =0;
    for(;i < BloomHashCount;++i)
    {
        uint64_t hash = bf->bloom_hash[i](str)% BitmapMaxSize;
        int ret = BitmapTest(&bf->bm,hash);
        if(ret == 0)
        {
            return 0;
        }
    }
    return 1;
}


/************************
 *
 *
 *
 * 以下为测试代码
 *
 *
 ***************************/
#if 1
#include <stdio.h>
#define TEST_HEAD printf("\n===========%s================\n",__FUNCTION__);
void TestBloom()
{
    TEST_HEAD;
    BloomFilter bf;
    BloomFilterInit(&bf);
    BloomFilterInsert(&bf,"HeHe");
    BloomFilterInsert(&bf,"HaHa");
    int ret = BloomFilterIsExit(&bf,"HeHe");
    printf("ret expected 1,actual %d\n",ret);
}

int main()
{
    TestBloom();
    return 0;
}
#endif
