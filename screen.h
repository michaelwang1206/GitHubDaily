#include <iostream>
#include <string>
#include <vector>
#include <graphics.h>
#include <easyx.h>
using namespace std;

#ifndef SCREEN_H
#define SCREEN_H

class Text{
    private:
        string textcontent, style = "微软雅黑";
        bool ishide = true;
        int textcolor[3]; //文字颜色
        int textsize;
        float itswidth = 0/*左*/,itsheight = 0;/*上*/
    public:
        Text(string txtcont, int txtsz = 20, vector<int> txtcl = {0,0,0}, string st = "微软雅黑"){
            textcontent = txtcont;
            textsize = txtsz;
            for(int i = 0; i < 3; i++){
                textcolor[i] = txtcl[i];
            }
            style = st;
            ishide = true;
        }
        float showText(float width,float height){//以左下角为输入标准
            settextstyle(textsize, 0, style.c_str());
            settextcolor(RGB(textcolor[0], textcolor[1], textcolor[2]));
            setbkmode(TRANSPARENT);
            itswidth = width;
            itsheight = height - textheight(textcontent.c_str());
            outtextxy(itswidth, itsheight, textcontent.c_str());
            ishide = false;
            return textheight(textcontent.c_str());
        }

        void hideText(vector<int> bkcolor){
            setfillcolor(RGB(bkcolor[0], bkcolor[1], bkcolor[2]));
            solidrectangle(itswidth, itsheight, itswidth + textwidth(textcontent.c_str()), itsheight + textheight(textcontent.c_str()));//左上右下
            ishide = true;
        }

        bool isHide(){
            return ishide;
        }

        ~Text() = default;
};


class Screen{
    private:
        vector<Text*> contents = {};
        float area[4] = {0,0,0,0};//左右上下
        bool ishide = true;
        int textcolor[3];
        int fillcolor[3]; //填充颜色
        string style;
        int textsize;
    
    public:
        Screen(vector<float> inarea, int textsz = 10, vector<int> fillcl = {200,200,200}, vector<int> txtcl = {0,0,0}, string style = "微软雅黑")
        : textsize(textsz), style(style), ishide(true){
            for(int i = 0; i < 4; i++) area[i] = inarea[i];
            for(int i = 0; i < 3; i++){
                fillcolor[i] = fillcl[i];
                textcolor[i] = txtcl[i];
            }
        }

        vector<Text*> getContents(){return contents;}
        float* getArea(){return area;}
        Text* getOneContent(int index){
            if(index < 0 || index >= contents.size()) return nullptr;
            return contents[index];
        }
        float getOneArea(int index){
            if(index < 0 || index >= 4) return -1;
            return area[index];
        }

        void addContent(Text* newcont){contents.push_back(newcont);}
        void newContent(string cont){
            vector<int> temp(textcolor, textcolor + 3); 
            contents.push_back(new Text(cont, textsize, temp, style));
        }
        void deleteOneContent(){
            if(!contents.empty()) {
                delete contents[0];
                contents.erase(contents.begin());
            }
        }

        void newArea(vector<float> inarea){for(int i = 0; i < 4; i++) area[i] = inarea[i];}
        void newStyle(string s){style = s;}
        void newFillColor(vector<int> fillcl = {200,200,200}){for(int i = 0; i < 3; i++) fillcolor[i] = fillcl[i];}
        void newTextColor(vector<int> txtcl = {0,0,0}){for(int i = 0; i < 3; i++) textcolor[i] = txtcl[i];}
        void showFrame(){
            setfillcolor(RGB(fillcolor[0], fillcolor[1], fillcolor[2]));
            solidrectangle(area[0], area[2], area[1], area[3]);//左上右下
            ishide = false;
        }
        void hideFrame(vector<int> bkcolor){
            setfillcolor(RGB(bkcolor[0], bkcolor[1], bkcolor[2]));
            solidrectangle(area[0], area[2], area[1], area[3]);//左上右下
            ishide = true;
        }

        void showAllContents(){
            if (!ishide){
                vector<int> temp(fillcolor, fillcolor + 3);
                for(int i = contents.size() - 1; i >= 0; i--){
                    if(!contents[i]->isHide()) contents[i]->hideText(temp);
                }
                float pointerleft = area[0] + 2;
                float pointerbottom = area[3]; 
                float onelineheight;
                vector<int> toDelete;
                for(int i = contents.size() - 1; i >= 0; i--){
                    if(pointerbottom > 0){
                        onelineheight = contents[i]->showText(pointerleft, pointerbottom);
                        pointerbottom -= onelineheight;
                    }
                    else{
                        toDelete.push_back(i);
                    }
                }
                for (auto it = toDelete.rbegin(); it != toDelete.rend(); ++it) {
                    delete contents[*it];
                    contents[*it] = nullptr;
                    contents.erase(contents.begin() + *it);
                }
            }
        }

        ~Screen(){
            for(auto& cont : contents){
                delete cont;
            }
            contents.clear();
        }
};

vector<float> screenarea = {1000, 1500, 0, 800};
Screen scr(screenarea);

#endif //SCREEN_H