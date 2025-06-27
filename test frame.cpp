#include <iostream>
#include <vector>
#include <string>

#include <graphics.h>
#include <easyx.h>

#include "button.h"
#include "screen.h"
#include "all pokemons.h"

using namespace std;

int main(){
    //初始化图形窗口
    initgraph(1500, 800);
    //背景颜色
    setbkcolor(WHITE);
    //setbkcolor(RGB(a, b, c));

    cleardevice();

    vector<float> bottonarea = {0, 200, 600, 700};
    RectButton abbutton1(bottonarea,"Click Me");
    bottonarea = {0, 200, 700, 800};
    RectButton abbutton2(bottonarea, "you") ;
    bottonarea = {200, 400, 600, 700};
    RectButton abbutton3(bottonarea, "3") ;
    bottonarea = {200, 400, 700, 800};
    RectButton abbutton4(bottonarea, "4") ;
    abbutton1.show();
    abbutton2.show();
    abbutton3.show();
    abbutton4.show();

    vector<float> screenarea = {1000, 1500, 0, 800};
    Screen scr(screenarea);
    scr.showFrame();

    ExMessage mss;

    while(true){
        BeginBatchDraw();
        //cleardevice();
        if(peekmessage(&mss, EX_MOUSE)){
            //处理鼠标消息
            if(mss.message == WM_LBUTTONDOWN){
                //左键点击
                if(abbutton1.buttonLeftClick(mss.x, mss.y, mss.message)){
                    scr.newContent("Button1 clicked!");
                    
                }
                else if(abbutton2.buttonLeftClick(mss.x, mss.y, mss.message)){
                    scr.newContent("Button2 clicked!");
                    
                }
                else if(abbutton3.buttonLeftClick(mss.x, mss.y, mss.message)){
                    scr.newContent("Button3 clicked!");
                    
                }
                else if(abbutton4.buttonLeftClick(mss.x, mss.y, mss.message)){
                    scr.newContent("Button4 clicked!");
                    
                }
                else{
                    scr.newContent("Clicked outside the button.");
                }
            }
            else if(mss.message == WM_RBUTTONDOWN){
                //右键点击
                abbutton1.show();
                abbutton2.show();
                abbutton3.show();
                abbutton4.show();
            }
            /*
            else if(mss.message == WM_LBUTTONDBLCLK){
                break;
            }*/
            scr.showAllContents();
        }
        EndBatchDraw();
    }
    EndBatchDraw();

    closegraph();
    return 0;
}