#pragma once
#include "bitmap.h"

//此处定义了布隆过滤器的hash函数
//把字符串转成下标


typedef uint64_t (*BloomHash)(const char*);
//此处定义了布隆过滤器的Hash函数，把字符串转为下标

#define BloomHashCount 2

typedef struct BloomFilter
{
    Bitmap bm;
    BloomHash bloom_hash[10000];
}BloomFilter;

void BloomFilterInit(BloomFilter* bf);

void BloomFilterDestroy(BloomFilter* bf);

void BloomFilterInsert(BloomFilter* bf,const char* str);

int BloomFilterIsExit(BloomFilter* bf,const char* str);

