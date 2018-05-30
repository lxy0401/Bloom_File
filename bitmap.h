#pragma once
#include <stdint.h>
typedef uint64_t BitmapType;

typedef struct Bitmap
{
    BitmapType* data;//64位无符号整形占8个字节
    uint64_t capacity;//位图最多能容纳多少位
}Bitmap;

//初始化
void BitmapInit(Bitmap* bm,uint64_t capacity);

//销毁
void BitmapDestroy(Bitmap* bm);

//测试某一位是否为1
int BitmapTest(Bitmap* bm,uint64_t index);

//将某一位设为1
void BitmapSet(Bitmap* bm,uint64_t index);

//将某一位设为0
void BitmapUnset(Bitmap* bm,uint64_t index);

//全部赋值为1
void BitmapFill(Bitmap* bm);

//全部赋值为0
void BitmapClear(Bitmap* bm);
