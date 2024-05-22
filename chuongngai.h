#pragma once
#include "raylib.h"
#include "iostream"
using namespace std;
const int maxchuongngai = 64;
const int maxlifes = 5;

class chuongngai{
    public:
    float scale;
    Vector2 block_vec;
    chuongngai();
    void loadtexture();
    void block(int x, int y,int rong,float rotate,bool textureloaded);
    void triang();
    bool textureloaded = true;    
};
