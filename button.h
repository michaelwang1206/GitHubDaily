#include <iostream>
#include <string>
#include <vector>
#include <graphics.h>
#include <easyx.h>
using namespace std;

#ifndef BUTTON_H
#define BUTTON_H
class RectButton{
    private:        
        string style;
        string text;
        bool ishide;
        int fillcolor[3]; //填充颜色
        int textcolor[3]; //文字颜色
        float area[4];//左右上下
        float midwidth, midheight;
        float midtextw, midtexth;
        int textsize;

    public:
        RectButton(vector<float> inarea, string txt = "", int textsz = 20, string s = "微软雅黑", 
                   vector<int> fillcl = {200,200,200}, vector<int> txtcl = {0,0,0}) 
            : style(s), text(txt), textsize(textsz), ishide(true) {
                for(int i = 0; i < 4; i++) area[i] = inarea[i];
                for(int i = 0; i < 3; i++){
                    fillcolor[i] = fillcl[i];
                    textcolor[i] = txtcl[i];
                }
                midwidth = (area[0] + area[1])/2;
                midheight = (area[2] + area[3])/2;
                midtextw = midwidth - textwidth(text.c_str()) / 2;
                midtexth = midheight - textheight(text.c_str()) / 2;
        }
        
        void newText(string txt){
            //设置按钮文字
            text = txt;
            midtextw = midwidth - textwidth(text.c_str()) / 2;
            midtexth = midheight - textheight(text.c_str()) / 2;
        }
        void newStyle(string s){style = s;}
        void newFillColor(vector<int> fillcl = {200,200,200}){for(int i = 0; i < 3; i++) fillcolor[i] = fillcl[i];}
        void newTextColor(vector<int> txtcl = {0,0,0}){for(int i = 0; i < 3; i++) textcolor[i] = txtcl[i];}

        void newSpace(vector<float> inarea){
            //设置按钮矩形区域
            for(int i = 0; i < 4; i++) area[i] = inarea[i];
            midwidth = (area[0] + area[1])/2;
            midheight = (area[2] + area[3])/2;
            midtextw = midwidth - textwidth(text.c_str()) / 2;
            midtexth = midheight - textheight(text.c_str()) / 2;
        }
        
        void draw(){
            //绘制按钮
            setfillcolor(RGB(fillcolor[0], fillcolor[1], fillcolor[2]));
            fillrectangle(area[0], area[2], area[1], area[3]);//左上右下
            settextstyle(textsize, 0, style.c_str());
            settextcolor(RGB(textcolor[0], textcolor[1], textcolor[2]));
            setbkmode(TRANSPARENT);
            outtextxy(midtextw, midtexth, text.c_str());
        }

        void show(){
            //显示按钮
            ishide = false;
            draw();
        }

        void erase(int x = 255, int y = 255, int z = 255){
            //擦除按钮
            setfillcolor(RGB(x, y, z));
            fillrectangle(area[0], area[2], area[1], area[3]);
        }

        void hide(int x = 255, int y = 255, int z = 255){
            //隐藏按钮
            ishide = true;
            erase(x, y, z);
        }

        bool inRect(int x, int y){return (x >= area[0] && x <= area[1] && y >= area[2] && y <= area[3]);}//判断点(x, y)是否在矩形内

        bool buttonLeftClick(int x, int y, int msg){return (!ishide && inRect(x, y) && msg == WM_LBUTTONDOWN);}//判断按钮是否被左键点击

        bool buttonRightClick(int x, int y, int msg){return (!ishide && inRect(x, y) && msg == WM_RBUTTONDOWN);}//判断按钮是否被右键点击
        
        ~RectButton() = default;
};

#endif // BUTTON_H
