#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <sstream>

using namespace std;

#ifndef ALL_SKILLS_H
#define ALL_SKILLS_H

enum SkillCategory {
    PHYSICAL, // 物理技能
    SPECIAL, // 特殊技能
    STATUS // 变化技能
};

enum TYPE {
    NORMAL, 
    FIRE,  
    WATER,
    GRASS, 
};

struct skillinfo {
    string name; // 技能名称
    TYPE type; // 技能类型
    SkillCategory category; // 技能类别（物理、特殊、变化）
    //int priority = 0; // 技能优先级，默认为0
    float power; // 技能威力
    //int accuracy; // 技能命中率
    int allpp; // 技能PP值
    string effect; // 技能效果描述
    float effectprobability; // 技能效果概率
};

class AllSkills {
    private:
        vector<skillinfo*> allskills; // 存储所有技能信息

    public:
        AllSkills(vector<skillinfo*> otherskills = {}) {
            // 初始化技能列表
            allskills = {};
            if(otherskills.size() > 0) {
                for(const auto& skill : otherskills) {
                    // 检查技能是否已存在
                    auto it = find_if(allskills.begin(), allskills.end(), 
                                      [&skill](skillinfo* s) { return s->name == skill->name; });
                    if (it == allskills.end()) {
                        allskills.push_back(skill); // 添加新技能
                    }
                    else {
                        cout << "Skill " << skill->name << " already exists." << endl; // 技能已存在
                    }
                }
            }
        }

        vector<skillinfo*> getAllSkills() const { return allskills; }

        bool checkexist(const string& skillname){
            auto it = find_if(allskills.begin(), allskills.end(), 
                              [&skillname](skillinfo* s) { return s->name == skillname; });
            if (it == allskills.end()) return false;
            return true;
        }

        skillinfo* getOneSkill(const string& skillname) {
            auto it = find_if(allskills.begin(), allskills.end(), 
                              [&skillname](skillinfo* s) { return s->name == skillname; });
            if (it != allskills.end()) {
                return *it; // 返回找到的技能
            }
            cout << "Skill " << skillname << " does not exist." << endl;
            return nullptr; // 技能不存在
        }

        void addSkill(skillinfo* newskill) {
            // 检查技能是否已存在
            auto it = find_if(allskills.begin(), allskills.end(), 
                              [&newskill](skillinfo* s) { return s->name == newskill->name; });
            if (it == allskills.end()) {
                allskills.push_back(newskill); // 添加新技能
                cout << "Skill " << newskill->name << " added successfully." << endl;
            }
            else {
                cout << "Skill " << newskill->name << " already exists." << endl; // 技能已存在
            }
        }
        void removeSkill(const string& skillname) {
            auto it = find_if(allskills.begin(), allskills.end(), 
                              [&skillname](skillinfo* s) { return s->name == skillname; });
            if (it != allskills.end()) {
                delete *it;
                allskills.erase(it); // 删除技能
                cout << "Skill " << skillname << " removed successfully." << endl;
            }
            else {
                cout << "Skill " << skillname << " does not exist." << endl; // 技能不存在
            }
        }
        void printAllSkills() const {
            cout << "All Skills:" << endl;
            for (const auto& skill : allskills) {
                cout << "Name: " << skill->name << "\n"
                     << ", Type: " << skill->type << "\n" 
                     << ", Category: " << skill->category << "\n"
                     << ", Power: " << skill->power << "\n" 
                     << ", PP: " << skill->allpp << "\n" 
                     << ", Effect: " << skill->effect << "\n"
                     << ", Effect Probability: " << skill->effectprobability << endl;
            }
        }

        void changeSkill(skillinfo* newskill) {
            auto it = find_if(allskills.begin(), allskills.end(), 
                              [&newskill](skillinfo* s) { return s->name == newskill->name; });
            if (it != allskills.end()) {
                delete *it;
                *it = newskill; // 修改技能
                cout << "Skill " << newskill->name << " changed successfully." << endl;
            }
            else {
                cout << "Skill " << newskill->name << " does not exist." << endl; // 技能不存在
            }
        }

        void checkOneSkill(const string& sknm){
            auto skill = find_if(allskills.begin(), allskills.end(), 
                              [&sknm](const skillinfo* s) { return s->name == sknm; });
            if (skill != allskills.end()) {
                    cout << "Name: " << (*skill)->name << "\n"
                     << ", Type: " << (*skill)->type << "\n" 
                     << ", Category: " << (*skill)->category << "\n"
                     << ", Power: " << (*skill)->power << "\n" 
                     << ", PP: " << (*skill)->allpp << "\n" 
                     << ", Effect: " << (*skill)->effect << "\n"
                     << ", Effect Probability: " << (*skill)->effectprobability << endl;
            }  
            else cout << "no skill calls " << sknm << endl;         
        }

        ~AllSkills(){
            for(int i = 0; i < allskills.size(); i++){
                delete allskills[i];
            }
            allskills.clear(); 
        }
};


AllSkills* allSkillsInPokemon = new AllSkills; // 全局技能
void clearAllSkills() {
    delete allSkillsInPokemon; // 释放全局技能对象
    allSkillsInPokemon = new AllSkills; // 重新创建一个新的空技能对象
}

#endif // ALL_SKILLS_H