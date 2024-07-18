#ifndef _MYGRAPHIC_H_
#define _MYGRAPHIC_H_

#include <M5Core2.h>
#define LGFX_USE_V1

#define LGFX_M5STACK_CORE2 // M5Stack M5Stack Core2
#include <LovyanGFX.hpp>
#include <LGFX_AUTODETECT.hpp>

static LGFX lcd;                 // LGFXのインスタンスを作成。
static LGFX_Sprite sprite(&lcd); // スプライトを使う場合はLGFX_Spriteのインスタンスを作成。

typedef struct
{
    int x;
    int y;
    int32_t color;
}_Point;

typedef struct
{
    _Point pt0;
    _Point pt1;
    
    uint32_t color;
}_AxisPt;

typedef struct
{
    _Point Pt0;
    _Point Pt1;
    uint32_t color;
}_LinePt;

#endif