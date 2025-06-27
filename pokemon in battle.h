#include "pokemon functions.h"

using namespace std;

#ifndef POKEMON_IN_BATTLE_H
#define POKEMON_IN_BATTLE_H

enum BattleStatus {
    NONE,
    POISONED, // 中毒状态
    PARALYZED, // 麻痹状态
    ASLEEP, // 睡眠状态
    FROZEN, // 冻结状态
    BURNED // 烧伤状态
};

enum ItemType {
    NOITEM,
    DRINK
};

enum SpecialStatus {
    CONFUSED,
    PARASITED
};

class PokemonInBattle{
    private:
        float maxHp = -1; // 最大HP
        float currentHp = maxHp; // 当前HP
        float panelchange[5] = {1, 1, 1, 1, 1}; // 面板属性变化：物理攻击、物理防御、特殊攻击、特殊防御、速度
        ItemType item = NOITEM; // 使用的道具类型
        BattleStatus status = NONE; // 宝可梦在战斗中的状态
        vector<SpecialStatus> spcstatus = {}; // 特殊状态
        bool isalive = true; // 宝可梦是否存活
        bool isonstage = false; // 是否在场上
        ActualPokemon* actualpok = nullptr;
        int allpps[4] = {0, 0, 0, 0};
        int inbattlepps[4] = {0, 0, 0, 0}; // 每个技能的PP值，初始化为0

    public:
        PokemonInBattle(ActualPokemon* act, int hp = -1, BattleStatus st = NONE, ItemType item = NOITEM)  
        : actualpok(act), status(st), currentHp(hp), item(item), isalive(true), isonstage(false) {
            maxHp = actualpok->getActuaHpNew();
            if (hp < 0 || hp > maxHp) {
                if(hp != -1) cout << "New HP cannot be negative or more than max HP." << endl;
                currentHp = maxHp; // HP输入不符合要求，则设置为默认最大HP
            }
            for (int i = 0; i < 5; i++) {
                panelchange[i] = 1; // 初始化面板属性变化   
            }
            spcstatus.clear(); // 清空特殊状态
            vector<skillinfo*> allskills = allSkillsInPokemon->getAllSkills();
            for (int i = 0; i < 4; i++) {
                string skillnm = actualpok->getOneActualSkill(i);
                if(skillnm == ""){ continue; }
                auto it = find_if(allskills.begin(), allskills.end(), 
                              [&skillnm](skillinfo* s) { return s->name == skillnm;});
                if (it == allskills.end()) { continue; }
                allpps[i] = (*it)->allpp;
                inbattlepps[i] = (*it)->allpp; 
            }
            cout << "PokemonInBattle created with status: " << status << ", current HP: " << currentHp << ", item: " << item << endl;
        }

        int getAllPP(int index) const {
            if (index < 0 || index >= 4) {
                cout << "Index out of bounds." << endl;
                return -1;
            }
            return allpps[index];
        }
        int getInBattlePP(int index) const {
            if (index < 0 || index >= 4) {
                cout << "Index out of bounds." << endl;
                return -1;
            }
            return inbattlepps[index];
        }
        void setAllPP(int index, int pp) {
            if (index < 0 || index >= 4) {
                cout << "Index out of bounds." << endl;
                return;
            }
            allpps[index] = pp;
            inbattlepps[index] = pp;
            cout << "PP for skill " << index << " set to " << pp << endl;
        }
        void setInBattlePP(int index, int pp) {
            if (index < 0 || index >= 4) {
                cout << "Index out of bounds." << endl;
                return;
            }
            inbattlepps[index] = pp;
            cout << "In-battle PP for skill " << index << " set to " << pp << endl;
        }

        BattleStatus getStatus() const { return status; }
        float getCurrentHp() const { return currentHp; }
        float getMaxHp() const { return maxHp; }
        const float* getPanelChange() const { return panelchange; }
        ItemType getItem() const { return item; }
        bool isAlive() const { return isalive; }
        bool isOnStage() const { return isonstage; }
        vector<SpecialStatus> getSpecialStatus() const { return spcstatus; }

        int getPokemonNo() const { return actualpok->getPokemonNo(); }
        int getActualNo() const { return actualpok->getActualNo(); }
        string getPokemonName() const { return actualpok->getPokemonName(); }
        string getActualName() const { return actualpok->getActualName(); }
        const string* getActualSkills() const {return actualpok->getActualSkills(); }
        int* getInBattlePPs() {return inbattlepps;}
        string getOneActualSkill(int index) const {return actualpok->getOneActualSkill(index);}
        int getOneInBattlePP(int index) const {return inbattlepps[index];}
        PokemonModel* getPokemonModel() const { return actualpok->getPokemonModel(); }
        ActualPokemon* getActualPokemon() const { return actualpok; }
        CharacterType getCharacter() const { return actualpok->getCharacter(); }
        TYPE getActualType() const { return actualpok->getPokemonModel()->getType(); }

        void forcesetStatus(BattleStatus newStatus) { status = newStatus; }
        void setStatus(BattleStatus newStatus) {
            if (status == NONE) {
                status = newStatus;
                cout << "Status set to " << newStatus << endl;
            } else {
                cout << "Cannot change status from " << status << " to " << newStatus << endl;
            }
        }        
        void setCurrentHp(float hp) {
            if (hp <= 0) {
                cout << "Pokemon "<< actualpok->getActualName() <<" fainted." << endl;
                isalive = false;
                status = NONE; // 设置状态为NONE
                for (int i = 0; i < 5; ++i) {
                    panelchange[i] = 0;
                }// 重置面板属性变化
                spcstatus.clear(); // 清空特殊状态
                status = NONE;
                currentHp = 0;
            } 
            else if (hp > maxHp) {
                cout << "Over MaxHp."<< endl;
                currentHp = maxHp;
            }
            else {
                currentHp = hp;
            }
        }
        void setPanelChange(float newPanelChange[5]) {
            for (int i = 0; i < 5; i++) {
                panelchange[i] = newPanelChange[i];
                cout << "Panel change at index " << i << " set to " << newPanelChange[i] << endl;
            }
        }
        void setOnePanelChange(float newPanelChange, int index) {
            if (index < 0 || index >= 5) {
                cout << "Index out of bounds." << endl;
                return;
            }
            panelchange[index] = newPanelChange;
            cout << "Panel change at index " << index << " set to " << newPanelChange << endl;
        }
        void setItem(ItemType newItem) { item = newItem; }
        void setAlive(bool alive) { isalive = alive; }
        void setOnStage(bool onstage) { isonstage = onstage; }
        void addSpecialStatus(SpecialStatus status) {
            if (find(spcstatus.begin(), spcstatus.end(), status) == spcstatus.end()) {
                spcstatus.push_back(status);
                cout << "Special status " << status << " added." << endl;
            } else {
                cout << "Special status " << status << " already exists." << endl;
            }
        }
        void removeSpecialStatus(SpecialStatus status) {
            auto it = find(spcstatus.begin(), spcstatus.end(), status);
            if (it != spcstatus.end()) {
                spcstatus.erase(it);
                cout << "Special status " << status << " removed." << endl;
            } else {
                cout << "Special status " << status << " not found." << endl;
            }
        }
        void clearSpecialStatus() {
            spcstatus.clear();
            cout << "All special statuses cleared." << endl;
        }
        void reset() {
            status = NONE;
            currentHp = maxHp;
            fill(begin(panelchange), end(panelchange), 1);
            item = NOITEM;
            isalive = true;
            isonstage = false;
            spcstatus.clear();
            cout << "Pokemon "<< getActualName() <<" reset to initial state." << endl;
        }
        void leaveStage() {
            isonstage = false;
            for (int i = 0; i < 5; i++) {
                panelchange[i] = 1;
            } // 重置面板属性变化
            spcstatus.clear(); // 清空特殊状态
            cout << "Pokemon "<< getActualName() <<" left the stage." << endl;
        }
        void enterStage() {
            isonstage = true;
            cout << "Pokemon "<< getActualName() <<" entered the stage." << endl;
        }

        string useSkill(int index) {
            if (!isonstage) {
                cout << "Pokemon is not on stage." << endl;
                return "";
            }
            if (!isalive) {
                cout << "Pokemon is fainted." << endl;
                return "";
            }   
            if (index < 0 || index >= 4) {
                cout << "Index out of bounds." << endl;
                return "";
            }
            string skill = actualpok->getOneActualSkill(index);
            if (skill.empty()) {
                cout << "No skill at index " << index << "." << endl;
                return "";
            }
            cout << getActualName() <<"using skill: " << skill << endl;
            return skill;
        }
};

#endif // POKEMON_IN_BATTLE_H