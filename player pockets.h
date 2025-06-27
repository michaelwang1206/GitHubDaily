#include "pokemon in battle.h"
#include <random>

using namespace std;

#ifndef PLAYER_POCKETS_H
#define PLAYER_POCKETS_H


class playerpocket{
    private:
        vector<PokemonInBattle*> playerpocket = {};
        int onstagenum = -1;
        PokemonInBattle* onstagepokemon = nullptr;

    public:
        int getOnStageNum(){return onstagenum;}
        PokemonInBattle* getOnStagePokemon(){return onstagepokemon;}

        int getPocketSize(){
            return playerpocket.size();
        }

        void pocketPokemonNo(int index){
            cout <<"pokemonname: " << playerpocket[index]->getPokemonNo()<< endl;
        }
        int getPocketPokemonNo(int index){
            return playerpocket[index]->getPokemonNo();
        }

        void pocketPokemonName(int index){
            cout <<"pokemonname: " << playerpocket[index]->getPokemonName()<< endl;
        }
        string getPocketPokemonName(int index){
            return playerpocket[index]->getPokemonName();
        }

        void pocketActualNo(int index){
            cout <<"pokemonname: " << playerpocket[index]->getActualNo()<< endl;
        }
        int getPocketActualNo(int index){
            return playerpocket[index]->getActualNo();
        }

        void pocketActualName(int index){
            cout << "actualname: " <<playerpocket[index]->getActualName()<< endl;
        }
        string getPocketActualName(int index){
            return playerpocket[index]->getActualName();
        }

        void pocketStatus(int index){
            cout << "status: " << playerpocket[index]->getStatus() << endl;
        }
        BattleStatus getPocketStatus(int index){
            return playerpocket[index]->getStatus();
        }

        void pocketCurrentHp(int index){
            cout << "currenthp: " << playerpocket[index]->getCurrentHp() << endl;
        }
        float getPocketCurrentHp(int index){
            return playerpocket[index]->getCurrentHp();
        }

        void pocketMaxHp(int index){
            cout <<"maxhp: " <<playerpocket[index]->getMaxHp()<< endl;
        }
        float getPocketMaxHp(int index){
            return playerpocket[index]->getMaxHp();
        }

        void pocketPanelChange(int index){
            cout << "panelchange: ";
            for(int i = 0; i < 5; i++){
                cout <<playerpocket[index]->getPanelChange()[i]<< " ";
            }
            cout << endl;
        }
        const float* getPocketPanelChange(int index){
            return playerpocket[index]->getPanelChange();
        }

        void pocketItem(int index){
            cout << "item: " <<playerpocket[index]->getItem()<< endl;
        }
        ItemType getPocketItem(int index){
            return playerpocket[index]->getItem();
        }

        void pocketIsAlive(int index){
            cout << "alive: " <<playerpocket[index]->isAlive()<< endl;
        }
        bool getPocketIsAlive(int index){
            return playerpocket[index]->isAlive();
        }

        void pocketIsOnStage(int index){
            cout <<"onstage: " << playerpocket[index]->isOnStage() << endl;
        }
        bool getPocketIsOnStage(int index){
            return playerpocket[index]->isOnStage();
        }

        void pocketSpecialStatus(int index){
            cout << "spcstatus: ";
            for(int i = 0; i < playerpocket[index]->getSpecialStatus().size(); i++){
                cout<< " " <<playerpocket[index]->getSpecialStatus()[i];
            }
            cout << endl;
        }
        vector<SpecialStatus> getPocketSpecialStatus(int index){
            return playerpocket[index]->getSpecialStatus();
        }

        void pocketOneActualSkill(int index, int skillindex){
            cout<< "skill " << skillindex << ": " <<playerpocket[index]->getOneActualSkill(skillindex)<< endl;
        }
        string getPocketOneActualSkill(int index, int skillindex){
            return playerpocket[index]->getOneActualSkill(skillindex);
        }

        void pocketActualSkills(int index){
            cout << "skills of pokemon " << index <<endl;
            for(int i = 0; i < 4; i++){
            pocketOneActualSkill(index, i);
            }
        }
        const string* getPocketActualSkills(int index) const {
            return playerpocket[index]->getActualSkills();
        }

        void pocketDetail(int index){
            cout << "pokemon " << index << " info:" << endl;
            pocketPokemonName(index);
            pocketActualName(index);
            pocketMaxHp(index);
            pocketCurrentHp(index);
            pocketStatus(index);
            pocketSpecialStatus(index);
            pocketPanelChange(index);
            pocketItem(index);
            pocketIsAlive(index);
            pocketIsOnStage(index);
            pocketActualSkills(index);
        }

        void pocketChangeCurrentHp(int index, float newhp){
            playerpocket[index]->setCurrentHp(newhp);
        }
        void pocketChangeStatus(int index, BattleStatus newst){
            playerpocket[index]->setStatus(newst);
        }
        void pocketForceChangeStatus(int index, BattleStatus newst = NONE){
            playerpocket[index]->forcesetStatus(newst);
        }
        void pocketAddSpecialStatus(int index, SpecialStatus newss){
            playerpocket[index]->addSpecialStatus(newss);
        }
        void pocketRemoveSpecialStatus(int index, SpecialStatus newss){
            playerpocket[index]->removeSpecialStatus(newss);
        }
        void pocketChangePanel(int index, float newpanel[5]){
            playerpocket[index]->setPanelChange(newpanel);
        }
        void pocketChangeOnePanel(int index, int panelindex, float newpanel){
            playerpocket[index]->setOnePanelChange(newpanel, panelindex);
        }
        void pocketChangeItem(int index, ItemType item){
            playerpocket[index]->setItem(item);
        }
        void pocketChangeAlive(int index, bool alive){
            playerpocket[index]->setAlive(alive);
        }

        void selectPokemon(ActualPokemon* p){
            for(int i = 0; i < playerpocket.size(); i++){
                if(playerpocket[i]->getActualPokemon() == p){
                    cout << "Pokemon already exists in the pocket." << endl;
                    return;
                }
            }
            PokemonInBattle* inbattleM = new PokemonInBattle(p);
            playerpocket.push_back(inbattleM);
            cout << "Battle pokemon added to "<< playerpocket.size() - 1 <<"." << endl;
        }

        void deletePokemon(int index){
            if(index >= playerpocket.size() || index < 0){ cout << "Invalid index."; return;}
            else{
                delete playerpocket[index];
                playerpocket.erase(playerpocket.begin() + index);
                cout << "Battle pokemon "<< index <<" deleted." << endl;
            }
        }

        void changePokemon(int index, ActualPokemon* p){
            if(index >= playerpocket.size() || index < 0){ cout << "Invalid index."; return;}
            for(int i = 0; i < playerpocket.size(); i++){
                if(playerpocket[i]->getActualPokemon() == p){
                    cout << "Pokemon already exists in the pocket." << endl;
                    return;
                }
            }
            delete playerpocket[index];
            playerpocket[index] = new PokemonInBattle(p);
            cout << "Battle pokemon "<< index <<" changed." << endl;
        }

        void setOnStage(int index){
            if(index >= playerpocket.size() || index < 0){ cout << "Invalid index."; return;}
            int tochangeindex = -1;
            for(int i = 0; i < playerpocket.size(); i++){
                if (playerpocket[i]->isOnStage()){
                    tochangeindex = i;
                    break;
                }
            }
            if (tochangeindex != -1) {
                cout <<"Pokemon " << tochangeindex << " has been chosen."<< endl;
                return;// 找到了至少一个 isOnStage 为 true 的宝可梦
            } 
            if (!playerpocket[index]->isAlive()){
                cout<<"Pokemon " << tochangeindex << " is fainted."<< endl;
                return;
            }
            playerpocket[index]->enterStage();
            onstagenum = index;
            onstagepokemon = playerpocket[index];
            cout << "Pokemon " << index << " is chosen." << endl;
        }

        int changeOnStage(int index){
            if(index >= playerpocket.size() || index < 0){ cout << "Invalid index." << endl; return -1;}
            int tochangeindex = -1, num = 0; 
            for(int i = 0; i < playerpocket.size(); i++){
                if (playerpocket[i]->isOnStage()){
                    tochangeindex = i;
                    num += 1;
                }
                if (num > 1) break;
            }
            if(num > 1){
                cout << "Error:More than 1 pokemon have been chosen." << endl;
                return -2;
            }
            if (num == 0) {
                cout <<"No pokemon is on stage,set "<< index <<" on stage."<< endl;
                playerpocket[index]->enterStage();
                onstagenum = index;
                onstagepokemon = playerpocket[index];
                return index;
            }
            if (!playerpocket[index]->isAlive()){
                cout<<"Pokemon " << tochangeindex << " is fainted."<< endl;
                return -1;
            } 
            playerpocket[tochangeindex]->leaveStage();
            playerpocket[index]->enterStage();
            onstagenum = index;
            onstagepokemon = playerpocket[index];
            cout << "Chosen pokemon changed from " << tochangeindex << " to " << index << endl;
            return index;
        }

        void deleteOnStage(int index){
            if(index >= playerpocket.size() || index < 0){ cout << "Invalid index."; return;}
            if(!playerpocket[index]->isOnStage()){
                cout << "Pokemon "<< index <<" is not on stage." << endl;
                return;
            }
            playerpocket[index]->leaveStage();
            onstagenum = -1;
            onstagepokemon = nullptr;
            cout << "Chosen pokemon left stage. " << endl;
        }

        void clearpocket(){
            for (auto p : playerpocket) {
                delete p; // 释放每个指针指向的对象
            }
            playerpocket.clear(); // 清空容器
            onstagenum = -1;
            onstagepokemon = nullptr;
            cout << "Pocket cleared." << endl;
        }

        string pocketUseSkill(int skillindex){
            if(onstagenum < 0 || onstagenum >= playerpocket.size()){
                cout << "No pokemon on stage." << endl;
                return "";
            }
            return playerpocket[onstagenum]->useSkill(skillindex);
        }

        int pocketAliveNum(){
            int num = 0;
            for(int i = 0; i < playerpocket.size(); i++){
                if(playerpocket[i]->isAlive()) num++;
            }
            return num;
        }

};

#endif //  PLAYER_POCKETS_H