#include "raylib.h" 
#include "iostream"
#include "vector"
#include "math.h"
#include "chuongngai.h"
#include "random"
using namespace std;

float cao = 500;
float rong = 500;
float goftball_size = 10;
Vector2 goftball = {250,250};
Rectangle goftball_hitbox;
Vector2 mousepos;
float canhhuyen;
Vector2 luc;
Vector2 haicanh;
Vector2 velo;
bool keo = false;
float radien;
float deri;
Vector2 spin[maxlifes] = {-200,-200};

Rectangle blocks[maxchuongngai];
int blocks_size[maxchuongngai];
int blocks_spawn = 3;
int level = 0;

Vector2 rotationpoint1;
Vector2 rotationpoint2;
float rotationpoint1_size = 1;
float angle;
float xx;
float yy;
float thanhnangluong_color;
#define maxmap 8
Vector2 stuffperspace = {rong/8.f,cao/8.f};
Vector2 vello;

int layer = 0;
int ele = 0;
int xdot=2,ydot=0;
int blockloaded=0;
bool maploaded = false;
int luotchoi = 5;
bool luotchoiused;
bool blockgetback=true;
float logomove = 0.5;

string mainmap[maxmap];

string level_0[maxmap] = {
            "########",
            "    H   ",
            "        ",
            "    #   ",
            "        ",
            "        ",
            "    P   ",
            "        ",
};
string level_1[maxmap] = {
            "   #    ",
            "   #  H ",
            "   #    ",
            "   #    ",
            "   #    ",
            "###     ",
            "        ",
            " P #    ",
};
string level_2[maxmap] = {
            "########",
            "        ",
            " P      ",
            "####    ",
            "   #    ",
            "     ###",
            "        ",
            "   #   H",
};
string level_3[maxmap] = {
            "## H ###",
            "        ",
            "        ",
            "#####   ",
            "   #    ",
            " P #    ",
            "        ",
            "        ",
};
string level_4[maxmap] = {
            "########",
            "##### H ",
            "       #",
            "   #   #",
            "  ## #  ",
            "#       ",
            "        ",
            " P      ",
};
string level_5[maxmap] = {
            "########",
            "#    H  ",
            "  ##### ",
            "  #   # ",
            "  # P # ",
            "        ",
            "        ",
            "        ",
};
string level_6[maxmap] = {
            "## H ###",
            " ###    ",
            "      # ",
            "   #####",
            "   #    ",
            "     P  ",
            "###     ",
            "  #     ",
};
string level_7[maxmap] = {
            "########",
            "    H   ",
            "########",
            "        ",
            "        ",
            "    P   ",
            "        ",
            "        ",
};
string level_8[maxmap] = {
            "########",
            "    H   ",
            "########",
            "        ",
            "#####   ",
            "        ",
            " P      ",
            "        ",
};
string level_9[maxmap] = {
            "########",
            "    H    ",
            "########",
            "########",
            "        ",
            "########",
            " P      ",
            "        ",
};
string level_10[maxmap] = {
            "########",
            "########",
            "###H ###",
            "########",
            "########",
            "########",
            "###  P##",
            "########",
};
const char *mainjoke;
const char *jokes[4] = {"Tips: sibii","Tips: saptoidichr","Tips: ipcuamla:123.456.78","Tips: DANH GOFLT!!!!!"};
bool joke_randomed;
const char *button_text = "Choi";

Rectangle statboard = {75,75,350,350};
int total_shot;
int total_restart;
int time_finnished;

Rectangle golfhole = {-100,-100,25,25};
bool holed = false;
int holedtime;

bool gamestarted = false;
bool finished = false;
int lifecolor;
float spinspeed = 0.02;
float zoominvelo;
float zoomoutvelo;

Rectangle button = {190,300,125,70};
Rectangle logo = {120,30,200,150};


float pullback(Vector2 vec1,Vector2 vec2){
    float a = vec1.x - vec2.x;
    float b = vec1.y - vec2.y;
    float c = sqrt(pow(a,2)+pow(b,2));
    return c;
};
Vector2 nor(Vector2 vec,float pulbac){
    float a = vec.x/pulbac;
    float b = vec.y/pulbac;
    return {a,b};
}
Vector2 tru(Vector2 vec1,Vector2 vec2){
    float a = vec1.x - vec2.x;
    float b = vec1.y - vec2.y;
    return {a,b};
};
Vector2 cong(Vector2 vec1,Vector2 vec2){
    float a = vec1.x + vec2.x;
    float b = vec1.y + vec2.y;
    return {a,b};
};
Vector2 nhan(Vector2 vec1,float so){
    float a = vec1.x *so;
    float b = vec1.y *so;
    return {a,b};
};
Vector2 chia(Vector2 vec1,Vector2 vec2){
    float a = vec1.x *vec2.x;
    float b = vec1.y *vec2.y;
    return {a,b};
};
Vector2 nhanvec(Vector2 vec1,Vector2 vec2){
    float a = vec1.x *vec2.x;
    float b = vec1.y*vec2.y;
    return {a,b};
};
Vector2 circle(float posx,float posy,float radius,float deris){
    Vector2 ss = {radius*cos(deris)-radius*sin(deris)+posx,radius*sin(deris)+radius*cos(deris)+posy};
    return {ss.x,ss.y};
}
int randoms(int min,int max){
    std::random_device a;
    std::uniform_int_distribution<int> d(min,max);
    return d(a);
}

float goc = 1;


chuongngai chuongngaii[maxchuongngai];

int main(){
    InitAudioDevice();
    InitWindow(rong,cao,"gop bon");
    SetTargetFPS(60);
    Texture2D background_tt = LoadTexture("access/background.png");
    Texture2D ball_tt = LoadTexture("access/ball.png");
    Texture2D block_tt = LoadTexture("access/block.png");
    Texture2D life_tt = LoadTexture("access/life.png");
    Texture2D hole_tt = LoadTexture("access/gofthole.png");
    Texture2D stat_tt = LoadTexture("access/statboard.png");
    Texture2D button_tt = LoadTexture("access/buton.png");
    Texture2D logo_tt = LoadTexture("access/logo.png");
    Sound bounce = LoadSound("access/bounce.mp3");
    Sound keoo = LoadSound("access/keoo.mp3");
    Sound vao = LoadSound("access/vao.mp3");

    Camera2D camera;
    camera.offset = (Vector2){rong/2.f,cao/2.f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    camera.target = (Vector2){rong/2.f,cao/2.f};

    //setblock
    
    
    while (!WindowShouldClose()){
        
        //setup
        mousepos = GetMousePosition();
        ClearBackground(WHITE);
        BeginDrawing();
        BeginMode2D(camera);
        DrawTexture(background_tt,0,0,WHITE);
        
        if(CheckCollisionPointRec(mousepos,button)){
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                gamestarted = true;
                button.x =-300;
                button.y = -300;
            }   
        }
        if(gamestarted){
            if(maploaded==false){
                zoominvelo+=0.01;
            if(camera.zoom<=10+0.1)camera.zoom+=zoominvelo;
                zoomoutvelo=0;
            }else {
                zoomoutvelo+=0.01;
            if(camera.zoom>1+0.1)camera.zoom-=zoomoutvelo;
                camera.target = (Vector2){rong/2,cao/2.f};
                zoominvelo=0;
            }

            if(blockgetback==true){
            for(int i=0;i<maxchuongngai;i++){
                blocks[i] = {-250,-250,stuffperspace.x,stuffperspace.y};
            }
            blockgetback = false;
            }
            if(IsKeyPressed(KEY_R)){
                maploaded = false;
                total_restart++;
            }
            //danh goft
            if((IsMouseButtonDown(MOUSE_BUTTON_LEFT))){
                if(CheckCollisionPointCircle(mousepos,goftball,goftball_size)){
                    if(velo.x<=0.1 &&velo.y<=0.1&&velo.x>=-0.1&&velo.y>=-0.1&&luotchoi>0){
                        keo = true;
                        luotchoiused = true;
                    }   
                }
            }else {
                keo = false;
                if(luotchoiused==true){
                    luotchoi--;
                    total_shot++;
                    PlaySound(keoo);
                    luotchoiused = false;
                }
            }
            canhhuyen = pullback(goftball,mousepos);
            if(keo){
                haicanh = tru(goftball,mousepos);
                luc = nor(haicanh,canhhuyen);
                if(canhhuyen<100) {
                    luc = nhan(luc,canhhuyen*0.1);
                    //thanh nang luong
                }
                else {
                    luc = nhan(luc,10);
                    DrawTriangle(rotationpoint1,mousepos,rotationpoint2,WHITE);
                }
                velo = luc;
            }else {
                goftball = cong(goftball,velo);
                velo = nhan(velo,0.98);
            }
            //maps va load
            for(int i=0;i<maxmap;i++){
                switch(level){
                    case 0:
                    mainmap[i] = level_0[i];
                    break;
                    case 1:
                    mainmap[i] = level_1[i];
                    break;
                    case 2:
                    mainmap[i] = level_2[i];
                    break;
                    case 3:
                    mainmap[i] = level_3[i];
                    break;
                    case 4:
                    mainmap[i] = level_4[i];
                    break;
                    case 5:
                    mainmap[i] = level_5[i];
                    break;
                    case 6:
                    mainmap[i] = level_6[i];
                    break;
                    case 7:
                    mainmap[i] = level_7[i];
                    break;
                    case 8:
                    mainmap[i] = level_8[i];
                    break;
                    case 9:
                    mainmap[i] = level_9[i];
                    break;
                    case 10:
                    mainmap[i] = level_10[i];
                    break;
                    case 11:
                    gamestarted = false;
                    finished = true;
                    goftball = {250,250};
                    button.x = 190;
                    button.y = 300;
                    break;
                }

            }

            if(maploaded==false&&blockgetback==false){
                if(mainmap[layer][ele] == ' '){
                    xdot+=stuffperspace.x;
                    ele++;
                }
                if(mainmap[layer][ele] == '#'){
                    blocks[blockloaded].x = xdot;
                    blocks[blockloaded].y = ydot;
                    xdot+=stuffperspace.x;
                    ele++;
                    blockloaded++;
                }
                if(mainmap[layer][ele] == 'P'){
                    goftball.x = xdot+goftball_size;
                    goftball.y = ydot+goftball_size;
                    xdot+=stuffperspace.x;
                    velo = {0,0};
                    if(luotchoi==0)total_restart++;
                    luotchoi=5;
                    ele++;
                }
                if(mainmap[layer][ele] == 'H'){
                    golfhole.x = xdot+golfhole.width;
                    golfhole.y = ydot+golfhole.height;
                    xdot+=stuffperspace.x;
                    ele++;
                }
                if(ele==8&&layer<8){
                    xdot=2;
                    ydot+=stuffperspace.x;
                    layer++;
                    ele=0;
                }
                if(layer==8&&ele==8){
                    layer = 0;
                    ele = 0;
                    xdot = 2;
                    ydot = 0;
                    maploaded = true;
                    blockloaded = 0;
                }
            }
            //colitions va blocks
            goftball_hitbox = {goftball.x-goftball_size,goftball.y-goftball_size,goftball_size*2,goftball_size*2};
            if(goftball.x+10>rong||goftball.x-10<0){
                velo.x *=-1;
                if(maploaded)PlaySound(bounce);
            }
            if(goftball.y+10>cao||goftball.y-10<0){
                velo.y *=-1;
                if(maploaded)PlaySound(bounce);
            }
            for(int i=0;i<maxchuongngai;i++){
                if(CheckCollisionRecs(goftball_hitbox,blocks[i])){
                    if(!(goftball_hitbox.x+goftball_size*2>blocks[i].x+blocks[i].width)) velo.x*=-1;
                    if(!(goftball_hitbox.y+goftball_size*2>blocks[i].y+blocks[i].height))velo.y *=-1;
                    if(!(goftball_hitbox.x<blocks[i].x)) velo.x*=-1;
                    if(!(goftball_hitbox.y<blocks[i].y))velo.y *=-1;
                    PlaySound(bounce);
                }
            }
            if(CheckCollisionRecs(goftball_hitbox,golfhole)&&holed==false){
                level++;
                holed = true;
                PlaySound(vao);
            }
            if(holed){
                goftball = {golfhole.x+goftball_size+5,golfhole.y+goftball_size+5};
                if(goftball_size>0)goftball_size-=0.5;
                if(goftball_size<=0){
                    goftball = {-100,-100};
                    goftball_size = 10;
                    blockgetback = true;
                    blockloaded = 0;
                    maploaded = false;
                    holed = false;
                }
            }
            if(luotchoi==0 &&velo.x<=0.1 &&velo.y<=0.1&&velo.x>=-0.1&&velo.y>=-0.1)maploaded = false;


            goc+=spinspeed;
            angle = atan2f(goftball.y-mousepos.y,goftball.x-mousepos.x);
            xx = (goftball_size-rotationpoint1_size)*sinf(angle);
            yy = -(goftball_size-rotationpoint1_size)*cosf(angle);
            rotationpoint1.x = goftball.x+xx;
            rotationpoint1.y = goftball.y+yy;
            rotationpoint2.x = goftball.x-xx;
            rotationpoint2.y = goftball.y-yy;
            //DrawCircle(goftball.x,goftball.y,goftball_size,RED);

            for(int i=0;i<maxchuongngai;i++){
                DrawTextureEx(block_tt,{blocks[i].x,blocks[i].y},0,blocks[i].width*0.002,WHITE);
                //DrawRectangleRec(blocks[i],RED);
            }
            for(int i=0;i<maxlifes;i++){
                //DrawCircleV(spin[i],4,CLITERAL(Color){0,0,0,(unsigned char)lifecolor});
                DrawTextureEx(life_tt,{spin[i].x-4,spin[i].y-4},0,0.5,CLITERAL(Color){255,255,255,(unsigned char)lifecolor});
            }
            if(keo)DrawTriangle(rotationpoint1,mousepos,rotationpoint2,CLITERAL(Color){ 255, 255, 255, (unsigned char)(255/100*canhhuyen)});
            if(lifecolor<255-4&&holed==false)lifecolor+=4;
            if(lifecolor>0+20&&holed==true)lifecolor-=20;
            switch(luotchoi){
                case 5:
                spinspeed = 0.012;
                spin[4] = circle(goftball.x,goftball.y,12,goc+4.8);
                spin[3] = circle(goftball.x,goftball.y,12,goc+3.6);
                spin[2] = circle(goftball.x,goftball.y,12,goc+2.4);
                spin[1] = circle(goftball.x,goftball.y,12,goc+1.2);
                spin[0] = circle(goftball.x,goftball.y,12,goc);
                break;
                case 4:
                spinspeed = 0.014;
                spin[4] = {-100,-100};
                spin[3] = circle(goftball.x,goftball.y,12,goc+4.5);
                spin[2] = circle(goftball.x,goftball.y,12,goc+3);
                spin[1] = circle(goftball.x,goftball.y,12,goc+1.5);
                spin[0] = circle(goftball.x,goftball.y,12,goc);
                break;
                case 3:
                spinspeed = 0.016;
                spin[3] = {-100,-100};
                spin[2] = circle(goftball.x,goftball.y,12,goc+4);
                spin[1] = circle(goftball.x,goftball.y,12,goc+2);
                spin[0] = circle(goftball.x,goftball.y,12,goc);
                break;
                case 2:
                spinspeed = 0.018;
                spin[2] = {-100,-100};
                spin[1] = circle(goftball.x,goftball.y,12,goc+3);
                spin[0] = circle(goftball.x,goftball.y,12,goc);
                break;
                case 1:
                spinspeed = 0.02;
                spin[1] = {-100,-100};
                spin[0] = circle(goftball.x,goftball.y,12,goc);
                break;
                case 0:
                spin[0] = {-100,-100};
                break;
            }
            DrawTextureV(hole_tt,{golfhole.x,golfhole.y},WHITE);
            //DrawRectangleRec(goftball_hitbox,RED);
        }else{
            lifecolor = 0;
            logo.y+=logomove;
            DrawTexture(button_tt,button.x,button.y,WHITE);
            DrawText(button_text,button.x+30,button.y+20,30,BLACK);
            //DrawRectangle(150,50,200,150,RED);
            if(!finished){
                DrawTextureEx(logo_tt,{logo.x,logo.y},0,1.3,WHITE);
                if(logo.y<20||logo.y>40) logomove*=-1;
            }
        }
        DrawTextureEx(ball_tt,{goftball.x-goftball_size,goftball.y-goftball_size},0,goftball_size*0.1,WHITE);
        //stats
        if(IsKeyDown(KEY_TAB)||finished==true){
            if(joke_randomed==false){
                mainjoke =jokes[randoms(0,4)];
                joke_randomed = true;
            }
            DrawTextureEx(stat_tt,{statboard.x,statboard.y},0,1,WHITE);
            if(!finished) DrawText(mainjoke,statboard.x+17,statboard.y+300,28,BLACK);
            DrawText(TextFormat("Tong so Gay: %i", total_shot),statboard.x+20,statboard.y+50,30,BLACK);
            DrawText(TextFormat("So lan thu lai: %i", total_restart),statboard.x+20,statboard.y+100,30,BLACK);
        }else joke_randomed = false;
        cout<<mainjoke<<"\n";
        EndMode2D();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}