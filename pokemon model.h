#include <algorithm>
#include <typeinfo>
#include <map>
#include <functional>

#include "all skills.h"

using namespace std;
#ifndef POKEMON_MODEL_H
#define POKEMON_MODEL_H

class PokemonModel{
    private:
        string pokemonname = "";
        int pokemonno = -1;
        TYPE type = NORMAL; // 类型
        vector<string> allskills = {}; // 技能列表
        vector<string> allabilities = {"None"}; // 特性列表
        float panel[6] = {100,10,10,10,10,10}; // 面板属性：hp, phsatk, phydef, spcatk, spcdef, speed

    public:
        PokemonModel() = default; // 默认构造函数
        PokemonModel(int no, string name, TYPE tp = NORMAL, vector<float> pl = {100,10,10,10,10,10}, vector<string> allsk = {}, vector<string> allab = {"None"}){
            if(pl.size() != 6){
                cout << "invalid panel." << endl;
            }
            else{
                for(int i = 0; i < 6; i++){panel[i] = pl[i];}
            }
            pokemonname = name;
            pokemonno = no;
            type = tp;

            for (int j = 0; j < allsk.size(); j++){
                bool sklflg = false;
                for (int i = 0; i < allSkillsInPokemon->getAllSkills().size(); i++) {
                    if (allSkillsInPokemon->getAllSkills()[i]->name == allsk[j]) {
                        sklflg = true; // 如果技能已存在在全局技能库中，设置flg为true
                        break;
                    }
                }
                if (!sklflg) {
                    cout << "Skill is invalid." << endl; // 如果技能不存在在全局技能库中，直接返回
                    continue;
                }

                auto it = find(allskills.begin(), allskills.end(), allsk[j]);
                if (it != allskills.end()) {
                    cout << "Skill has existed." << endl;
                }
                else {
                    allskills.push_back(allsk[j]);
                cout << "Skill " << allsk[j] << " added successfully." << endl;
                }
            }

            for (int i = 0; i < allab.size(); i++){
                auto it = find(allabilities.begin(), allabilities.end(), allab[i]);
                if (it != allabilities.end()) {
                    cout << "Ability " << allab[i] << " has existed." << endl;
                }
                else {
                    allabilities.push_back(allab[i]);
                    cout << "Ability "<< allab[i] <<" added successfully." << endl;
                }
            }
        }


        string getPokemonName() {
            return pokemonname;
        }
        int getPokemonNo() {
            return pokemonno;
        }
        vector<string> getAllSkills() {
            return allskills;
        }
        vector<string> getAllAbilities() {
            return allabilities;
        }
        float* getGroupPanel() {
            return panel;
        }
        float getOneGroupPanel(int index) {
            if (index < 0 || index >= 6) {
                cout << "Index out of bounds." << endl;
                return -1; // 或者抛出异常
            }
            return panel[index];
        }
        TYPE getType() {
            return type;
        }


        void setPokemonName(const string& name) {
            pokemonname = name;
        }
        void setPokemonNo(const int& num) {
            pokemonno = num;
        }
        void addGroupSkills(const string& skill) {
            bool flg = false;
            for (int i = 0; i < allSkillsInPokemon->getAllSkills().size(); i++) {
                if (allSkillsInPokemon->getAllSkills()[i]->name == skill) {
                    flg = true; // 如果技能已存在在全局技能库中，设置flg为true
                    break;
                }
            }
            if (!flg) {
                cout << "Skill is invalid." << endl;
                return; // 如果技能不存在在全局技能库中，直接返回
            }

            auto it = find(allskills.begin(), allskills.end(), skill);
            if (it != allskills.end()) {
                cout << "Skill has existed." << endl;
            }
            else {
                allskills.push_back(skill);
                cout << "Skill added successfully." << endl;
            }
        }
        void addGroupAbilities(const string& ability) {
            auto it = find(allabilities.begin(), allabilities.end(), ability);
            if (it != allabilities.end()) {
                cout << "Ability has existed." << endl;
            }
            else {
                allabilities.push_back(ability);
                cout << "Ability added successfully." << endl;
            }
        }
        void removeGroupSkills(const string& skill) {
            auto it = find(allskills.begin(), allskills.end(), skill);
            if (it != allskills.end()) {
                allskills.erase(it);
                cout << "Skill removed successfully." << endl;
            }
            else {
                cout << "Skill not found." << endl;
            }
        }
        void removeGroupAbilities(const string& ability) {
            auto it = find(allabilities.begin(), allabilities.end(), ability);
            if (it != allabilities.end()) {
                allabilities.erase(it);
                cout << "Ability removed successfully." << endl;
            }
            else {
                cout << "Ability not found." << endl;
            }
        }
        void resetGroupPanel(const float newPanel[6]) {
            for (int i = 0; i < 6; i++) {
                panel[i] = newPanel[i];
                cout << "Panel "<< i <<" updated successfully." << endl;
            }
        }
        void resetOneGroupPanel(const float newPanel, int index) {
            if (index < 0 || index >= 6) {
                cout << "Index out of bounds." << endl;
                return;
            }
            panel[index] = newPanel;
            cout << "Panel attribute at index " << index << " updated successfully." << endl;
        }
        void resetType(const TYPE& newType) {
            type = newType;
        }

        void showPokemonModel(){
            cout << "Pokemon Name: " << pokemonname << endl;
            cout << "Pokemon No: " << pokemonno << endl;
            cout << "Type: ";
            switch (type) {
                case NORMAL: cout << "Normal"; break;
                case FIRE: cout << "Fire"; break;
                case WATER: cout << "Water"; break;
                case GRASS: cout << "Grass"; break;
                default: cout << "Unknown"; break;
            }
            cout << endl;
            cout << "Skills: ";
            for (const auto& skill : allskills) {
                cout << skill << " ";
            }
            cout << endl;
            cout << "Abilities: ";
            for (const auto& ability : allabilities) {
                cout << ability << " ";
            }
            cout << endl;
            cout << "Panel Attributes: ";
            for (int i = 0; i < 6; i++) {
                cout << panel[i] << " ";
            }
            cout << endl;
        }

        ~PokemonModel() = default;
};

vector<PokemonModel*> allpokemonmodels;

#endif // POKEMON_MODEL_H