#ifndef POKEMON_ACTUAL_H
#define POKEMON_ACTUAL_H

#include "pokemon model.h"

using namespace std;

enum CharacterType {
    HARDY, // 性格：Hardy
    BRAVE, // 性格：Brave
    TIMID, // 性格：Timid
};


// 实际宝可梦
class ActualPokemon {
    private:
        string actualname = ""; 
        int actualno = -1;
        CharacterType character = HARDY;
        float actualpanel[6] = {1,1,1,1,1,1};
        string actualskills[4] = {"","","",""};
        string actualability = "None";
        PokemonModel* model = nullptr;

    public:
        ActualPokemon() = default; // 默认构造函数
        ActualPokemon(PokemonModel* md, string nm, int nuum, CharacterType ch = HARDY, vector<string> skls = {}, string ability = "None"){        
            model = md;// 设置实际宝可梦
            actualname = nm; 
            actualno = nuum;
            character = ch;
            vector<string> tempskls = model->getAllSkills(); // 获取父类的所有技能
            vector<string> tempabilities =model->getAllAbilities(); // 获取父类的所有特性
            auto itability = find(tempabilities.begin(), tempabilities.end(), ability);
            if (itability != tempabilities.end()) {
                actualability = ability; // 设置实际特性
                cout << "Ability " << ability << " set successfully." << endl;
            }
            else {
                cout << "Ability " << ability << " is not valid." << endl;
            }
            for(int i = 0; i < 6; i++) {
                actualpanel[i] = 1; // 初始化实际面板属性
            }
            int inskill = 0, listskill = 0;
            while(listskill < skls.size() && inskill < 4) {
                auto it = find(tempskls.begin(),tempskls.end(), skls[listskill]);
                auto it2 = find(std::begin(actualskills), std::end(actualskills), skls[listskill]);
                if (it != tempskls.end() && it2 == std::end(actualskills)) {
                    actualskills[inskill] = skls[listskill];
                    inskill++;
                    cout << "Skill " << skls[listskill] << " added successfully." << endl;
                }
                else if (it2 != std::end(actualskills)) {
                    cout << "Skill " << skls[listskill] << " has already existed." << endl;
                }
                else {
                    cout << "Skill " << skls[listskill] << " is not valid." << endl;
                }
                listskill++;
            }
            for(int i = inskill; i < 4; i++) {
                actualskills[i] = "";
            }
            switch (character) {
            case HARDY:
            // 如果性格是Hardy，则所有属性不变
                break;
            case BRAVE:
            // 如果性格是Brave，则物理攻击增加，特防降低
                actualpanel[1] = 1.1; 
                actualpanel[4] = 0.9; 
                break;
            case TIMID:
            // 如果性格是Timid，则特防增加，物理攻击降低
                actualpanel[4] = 1.1; 
                actualpanel[1] = 0.9; 
                break;
            default:
                cout << "Unknown character type." << endl;
                character = HARDY; // 默认设置为Hardy
                break;
            }
        }

        PokemonModel* getPokemonModel() const {return model;}
        string getActualName() const { return actualname; }
        int getActualNo() const {return actualno;} 
        CharacterType getCharacter() const { return character; }
        float getActuaHp() const { return actualpanel[0]; }
        float getActualPhyatk() const { return actualpanel[1]; }
        float getActualPhydef() const { return actualpanel[2]; }
        float getActualSpcatk() const { return actualpanel[3]; }
        float getActualSpcdef() const { return actualpanel[4]; }
        float getActualSpeed() const { return actualpanel[5]; }        
        float* getActualPanel() {return actualpanel;}
        float getActuaHpNew() const { return actualpanel[0]*model->getOneGroupPanel(0); }
        float getActualPhyatkNew() const { return actualpanel[1]*model->getOneGroupPanel(1); }
        float getActualPhydefNew() const { return actualpanel[2]*model->getOneGroupPanel(2); }
        float getActualSpcatkNew() const { return actualpanel[3]*model->getOneGroupPanel(3); }
        float getActualSpcdefNew() const { return actualpanel[4]*model->getOneGroupPanel(4); }
        float getActualSpeedNew() const { return actualpanel[5]*model->getOneGroupPanel(5); }        
        void getActualPanelNew(float* acceptor) {
            for(int i = 0; i < 6; i++){
                acceptor[i] = actualpanel[i]*model->getOneGroupPanel(i);
            }
            return;}
        string getOneActualSkill(int index) const {
            if (index < 0 || index >= 4) {
                cout << "Index out of bounds." << endl;
                return "";
            }
            return actualskills[index];
        }
        const string* getActualSkills() const {return actualskills; }
        string getActualAbility() const { return actualability; }


        string getPokemonName() const { return model->getPokemonName(); }
        int getPokemonNo() const {return model->getPokemonNo();}
        float getGroupHp() const { return model->getOneGroupPanel(0); }
        float getGroupPhyatk() const { return model->getOneGroupPanel(1); }
        float getGroupPhydef() const { return model->getOneGroupPanel(2); }
        float getGroupSpcatk() const { return model->getOneGroupPanel(3); }
        float getGroupSpcdef() const { return model->getOneGroupPanel(4); }
        float getGroupSpeed() const { return model->getOneGroupPanel(5); }
        float* getGroupPanel() { return model->getGroupPanel(); }
        vector<string> getAllSkills() const { return model->getAllSkills(); }
        vector<string> getAllAbilities() const { return model->getAllAbilities(); }
        TYPE getType() const { return model->getType(); }

        void setPokemonModel(PokemonModel* md){ 
            model = md;
            cout << "model reset successfully." << endl;
        }
        void setActualName(const string& name) { 
            actualname = name; 
            cout << "Actual Pokemon name set to " << actualname << endl;
        }
        void setActualNo(const int& no) { 
            actualno = no; 
            cout << "Actual Pokemon no set to " << actualno << endl;
        }
        void setCharacter(const CharacterType& newcharacter) { 
            character = newcharacter;
            for (int i = 0; i < 6; i++) actualpanel[i] = 1;
            switch (character) {
            case HARDY:
            // 如果性格是Hardy，则所有属性不变
                break;
            case BRAVE:
            // 如果性格是Brave，则物理攻击增加，特防降低
                actualpanel[1] = 1.1; 
                actualpanel[4] = 0.9; 
                break;
            case TIMID:
            // 如果性格是Timid，则特防增加，物理攻击降低
                actualpanel[4] = 1.1; 
                actualpanel[1] = 0.9; 
                break;
            default:
                cout << "Unknown character type." << endl;
                character = HARDY; // 默认设置为Hardy
                break;
            }
        }

        int changeOneSkill(string skill, int index) {
            if (index < 0 || index >= 4) {
                cout << "Index out of bounds." << endl;
                return -1;
            }
            vector<string> tempskls =model->getAllSkills();
            auto it = find(tempskls.begin(), tempskls.end(), skill);
            auto it2 = find(std::begin(actualskills), std::end(actualskills), skill);
            if (it != tempskls.end() && it2 == std::end(actualskills)) {
                actualskills[index] = skill;
                cout << "Skill " << skill << " added successfully." << endl;
                return 1;
            }
            else if (it2 != std::end(actualskills)) {
                cout << "Skill " << skill << " has already existed." << endl;
                return -1;
            }
            else {
                cout << "Skill " << skill << " is not valid." << endl;
                return -1;
            }
        }

        int changeAbility(string ability) {
            vector<string> tempabilities = model->getAllAbilities();
            auto it = find(tempabilities.begin(), tempabilities.end(), ability);
            if (it != tempabilities.end()) {
                actualability = ability; 
                cout << "Ability " << ability << " set successfully." << endl;
                return 1;
            }
            else {
                cout << "Ability " << ability << " is not valid." << endl;
                return -1;
            }
        }

        void showActualPokemon() const {
            cout << "Actual Name: " << actualname << endl;
            cout << "Actual No: " << actualno << endl;
            cout << "Character: ";
            switch (character) {
                case HARDY: cout << "Hardy"; break;
                case BRAVE: cout << "Brave"; break;
                case TIMID: cout << "Timid"; break;
                default: cout << "Unknown"; break;
            }
            cout << endl;
            cout << "Actual Panel: ";
            for (int i = 0; i < 6; i++) {
                cout << actualpanel[i] << " ";
            }
            cout << endl;
            cout << "Actual Skills: ";
            for (const auto& skill : actualskills) {
                if (!skill.empty()) {
                    cout << skill << " ";
                }
            }
            cout << endl;
            cout << "Actual Ability: " << actualability << endl;
        }

        ~ActualPokemon() = default;
};

vector<ActualPokemon*> allactualpokemons;

#endif // POKEMON_ACTUAL_H