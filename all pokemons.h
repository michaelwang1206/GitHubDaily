#include "player pockets.h"
#include <iostream>
#include <random>

using namespace std;

#ifndef ALL_POKEMONS_H
#define ALL_POKEMONS_H

const int maxpokemonnum = 6;
const int maxskillnum = 4;
struct playeraction{
    string action;
    int skillnum_or_pokemon_num;
};

const float effectiveness[4][4] = {
//  nor fire water grass
    {1,  1,    1,    1}, // Normal
    {1,  1,    2,   0.5}, // Fire
    {1, 0.5,   1,    2}, // Water
    {1,  2,   0.5,   1}  // Grass
};

skillinfo* createNewSkill(string input){
    string inputstring;
    int inputint;
    float inputfloat;
    skillinfo* newskill = new skillinfo;
    newskill->name = input;
    std::cout << "input type: ";
    std::getline(std::cin, inputstring);
    if(inputstring == "fire") newskill->type = FIRE;
    else if(inputstring == "water") newskill->type = WATER;
    else if(inputstring == "grass") newskill->type = GRASS;
    else if(inputstring == "normal") newskill->type = NORMAL;
    else{
        std::cout << "invalid type." << endl;
        delete newskill;
        return nullptr;
    }
    std::cout << "input category: ";
    std::getline(std::cin, inputstring);
    if(inputstring == "physical") newskill->category = PHYSICAL;
    else if(inputstring == "special") newskill->category = SPECIAL;
    else if(inputstring == "status") newskill->category = STATUS;
    else{
        std::cout << "invalid category." << endl;
        delete newskill;
        return nullptr;
    }
    std::cout << "input power: ";
    std::getline(std::cin, inputstring);
    inputint = std::stoi(inputstring);
    if(inputint < 0){
        std::cout << "invalid power." << endl;
        delete newskill;
        return nullptr;
    }
    newskill->power = inputint;
    std::cout << "input maxpp: ";
    std::getline(std::cin, inputstring);
    inputint = std::stoi(inputstring);
    if(inputint < 0){
        std::cout << "invalid maxpp." << endl;
        delete newskill;
        return nullptr;
    }
    newskill->allpp = inputint;
    std::cout << "input effect: ";
    std::getline(std::cin, inputstring);
    newskill->effect = inputstring;
    std::cout << "input effectprobability: ";
    std::getline(std::cin, inputstring);
    inputfloat = std::stof(inputstring);
    if(inputfloat < 0 || inputfloat > 1){
        std::cout << "invalid probability." << endl;
        delete newskill;
        return nullptr;
    }
    newskill->effectprobability = inputfloat;
    return newskill;
}

PokemonModel* createNewPokemonModel(){
    PokemonModel* newmodel = new PokemonModel;
    string inputstring;
    int inputint;
    float inputfloat;
    std::cout << "input name: ";
    std::getline(std::cin, inputstring);
    newmodel->setPokemonName(inputstring);
    std::cout << "input No: ";
    std::getline(std::cin, inputstring);
    inputint = std::stoi(inputstring);
    newmodel->setPokemonNo(inputint);
    std::cout << "input type: ";
    std::getline(std::cin, inputstring);
    if(inputstring == "fire") newmodel->resetType(FIRE);
    else if(inputstring == "water") newmodel->resetType(WATER);
    else if(inputstring == "grass") newmodel->resetType(GRASS);
    else if(inputstring == "normal") newmodel->resetType(NORMAL);
    else{
        std::cout << "invalid type." << endl;
        delete newmodel;
        return nullptr;
    }
    while(true){
        std::cout << "input modelskills, press enter to go to next step: " << endl;
        std::getline(std::cin, inputstring);
        if(inputstring == "") break;
        std::cout << "input skill name: ";
        std::getline(std::cin, inputstring);
        newmodel->addGroupSkills(inputstring);
    }
    while(true){
        std::cout << "input modelabilities, press enter to go to next step: " << endl;
        std::getline(std::cin, inputstring);
        if(inputstring == "") break;
        std::cout << "input ability name: ";
        std::getline(std::cin, inputstring);
        newmodel->addGroupAbilities(inputstring);
    }
    int panelnum = 0;
    while(panelnum < 6){
        std::cout << "input panel "<< panelnum << " :";
        std::getline(std::cin, inputstring);
        inputint = std::stoi(inputstring);
        if(inputint <= 0){
            std::cout << "invalid panel "<< panelnum << endl;
            continue;
        }
        newmodel->resetOneGroupPanel(inputint, panelnum);
        panelnum++;
    }
    return newmodel;                
}

ActualPokemon* createNewActualPokemon(){
    ActualPokemon* newact = new ActualPokemon;
    PokemonModel* usemodel;
    string inputstring;
    int inputint;
    std::cout << "choose to use model no or model name:" << endl;
    std::getline(std::cin, inputstring);
    if(inputstring == "name"){
        std::cout << "input pokemon model name:"<< endl;
        std::getline(std::cin, inputstring);
        usemodel = usePokemonModel(inputstring);
    }
    else if(inputstring == "No"){
        int inputint;
        std::cout << "input pokemon model no:"<< endl;
        std::getline(std::cin, inputstring);
        inputint = std::stoi(inputstring);
        usemodel = usePokemonModel(inputint);
    }
    if(usemodel == nullptr){
        cout << "no such model." << endl;
        delete newact;
        return nullptr;
    }
    newact->setPokemonModel(usemodel);
    std::cout << "input actual name:"<< endl;
    std::getline(std::cin, inputstring);
    newact->setActualName(inputstring);
    std::cout << "input actual No:" << endl;
    std::getline(std::cin, inputstring);
    inputint = std::stoi(inputstring);
    newact->setActualNo(inputint);
    std::cout << "input Character: " << endl;
    std::getline(std::cin, inputstring);
    switch (inputstring[0]) {
        case 'H':
        case 'h':
            newact->setCharacter(HARDY);
            break;
        case 'B':
        case 'b':
            newact->setCharacter(BRAVE);
            break;
        case 'T':
        case 't':
            newact->setCharacter(TIMID);
            break;
        default:
            cout << "invalid character." << endl;
            delete newact;
            return nullptr;
    }
    int skillnum = 0;
    while(true){
        if (skillnum >= 4) {
            std::cout << "You have added 4 skills, cannot add more." << endl;
            break;
        }
        std::cout << "input actualskills, press enter to go to next step: " << endl;
        std::getline(std::cin, inputstring);
        if(inputstring == "") break;
        std::cout << "input skill name: ";
        std::getline(std::cin, inputstring);
        int flg = newact->changeOneSkill(inputstring, skillnum);
        if(flg == 1) skillnum++;
        else if(flg == -1) continue;
    }
    
    //if(allAbilitiesInPokemon.checkexist(inputstring)){
    int abflg = -1;
    while(abflg < 0){
        std::cout << "input actualability, press enter to go to next step:: " << endl;
        std::getline(std::cin, inputstring);
        if(inputstring == "") break;
        abflg = newact->changeAbility(inputstring);
    }
    //}
    /*else{
        cout << "invalid ability." << endl;
        delete newact;
        return nullptr;
    }*/
    return newact;
}

void initializeAllSkills(){
    string x;
    while(true){
        std::cout << "if you want to add new skills, input 'add';\n"
        << " want to delete skills, input 'delete';\n"
        << " want to change skills, input 'change';\n"
        << " want to check skills, input 'check'.\n"
        << "otherwise, input anything else." << endl;
        std::getline(std::cin, x);
        if (x != "add" && x != "delete" && x != "change" && x != "check"){
            std::cout << "continue" << endl;
            break;
        }
        else{
            if(x == "add"){
                string inputstring;
                std::cout << "input name: ";
                std::getline(std::cin, inputstring);
                if(allSkillsInPokemon->checkexist(inputstring)){
                    std::cout << inputstring << " has existed!" << endl;
                    continue;
                }
                else{
                    skillinfo* newsk = createNewSkill(inputstring);
                    if(newsk != nullptr) allSkillsInPokemon->addSkill(newsk);
                    else cout << "fail to create new skill." << endl;
                }
            }
            else if(x == "delete"){
                string inputstring;
                std::cout << "input skill name to delete:"<< endl;
                std::getline(std::cin, inputstring);
                allSkillsInPokemon->removeSkill(inputstring);
            }
            else if(x == "change"){
                string inputstring;
                std::cout << "input name: ";
                std::getline(std::cin, inputstring);
                if(!allSkillsInPokemon->checkexist(inputstring)){
                    std::cout << inputstring << " doesn't existed!" << endl;
                    continue;
                }
                else{
                    skillinfo* newsk = createNewSkill(inputstring);
                    if(newsk != nullptr) allSkillsInPokemon->changeSkill(newsk);
                    else cout << "fail to change skill." << endl;
                }
            }
            else if(x == "check"){
                string inputstring;
                std::cout << "input 'all' to check all skills, if not, input anything else:"<< endl;
                std::getline(std::cin, inputstring);
                if(inputstring == "all"){
                    allSkillsInPokemon->printAllSkills();
                }
                else{
                    std::cout << "input skill name to check:"<< endl;
                    std::getline(std::cin, inputstring);
                    allSkillsInPokemon->checkOneSkill(inputstring);
                }
            }
        }
    }
}

void initializePokemonModels(){
    string x;
    while(true){
        std::cout << "if you want to add new pokemon models, input 'add';\n"
        << "want to delete pokemon models, input 'delete';\n"
        << " want to change pokemon models, input 'change';\n"
        << " want to check pokemon models, input 'check'.\n"
        << "otherwise, input anything else." << endl;
        std::getline(std::cin, x);
        if (x != "add" && x != "delete" && x != "change" && x != "check"){
            std::cout << "continue" << endl;
            break;
        }
        else{
            if(x == "add"){
                PokemonModel* newmodel = createNewPokemonModel();
                if(newmodel != nullptr){
                    addPokemonModel(newmodel);
                }
                else cout << "fail to create pokemonmodel." << endl;
            }
            else if(x == "delete"){
                string inputstring;
                std::cout << "choose name or No." << endl;
                std::getline(std::cin, inputstring);
                if(inputstring == "name"){
                    std::cout << "input pokemon name to delete:"<< endl;
                    std::getline(std::cin, inputstring);
                    deletePokemonModel(inputstring);
                }
                else if(inputstring == "No"){
                    int inputint;
                    std::cout << "input pokemon no to delete:"<< endl;
                    std::getline(std::cin, inputstring);
                    inputint = std::stoi(inputstring);
                    deletePokemonModel(inputint);
                }
                else{
                    cout << "invalid index." << endl;
                    continue;
                }
            }
            else if(x == "change"){
                string inputstring;
                std::cout << "input new info:" << endl;
                PokemonModel* newmodel = createNewPokemonModel();
                if(newmodel == nullptr){
                    cout << "fail to create new model." << endl;
                    continue;
                }
                std::cout << "change with name or No:" << endl;
                std::getline(std::cin, inputstring);
                if(inputstring == "name"){
                    std::cout << "input pokemon name to change:"<< endl;
                    std::getline(std::cin, inputstring);
                    changePokemonModel(newmodel, inputstring);
                }
                else if(inputstring == "No"){
                    int inputint;
                    std::cout << "input pokemon no to change:"<< endl;
                    std::getline(std::cin, inputstring);
                    inputint = std::stoi(inputstring);
                    changePokemonModel(newmodel, inputint);
                }
                else{
                    cout << "invalid index." << endl;
                    continue;
                }
            }
            else if(x == "check"){
                string inputstring;
                std::cout << "input 'all' to check all pokemon models, if not, input anything else:"<< endl;
                std::getline(std::cin, inputstring);
                if(inputstring == "all"){
                    for(PokemonModel* md : allpokemonmodels){
                        md->showPokemonModel();
                    }
                }
                else{
                    std::cout << "choose name or No." << endl;
                    std::getline(std::cin, inputstring);
                    if(inputstring == "name"){
                        std::cout << "input pokemon name to check:"<< endl;
                        std::getline(std::cin, inputstring);
                        usePokemonModel(inputstring)->showPokemonModel();
                    }
                    else if(inputstring == "No"){
                        int inputint;
                        std::cout << "input pokemon no to check:"<< endl;
                        std::getline(std::cin, inputstring);
                        inputint = std::stoi(inputstring);
                        usePokemonModel(inputint)->showPokemonModel();
                    }
                    else{
                        cout << "invalid index." << endl;
                        continue;
                    }
                }
            }
        }
    }
}

void initializeActualPokemons(){
    string x;
    while(true){
        std::cout << "if you want to add new actual pokemons, input 'add';\n"
        << "want to delete actual pokemons, input 'delete';\n"
        << " want to change actual pokemons, input 'change';\n"
        << " want to check actual pokemons, input 'check'.\n"
        << "otherwise, input anything else." << endl;
        std::getline(std::cin, x);
        if (x != "add" && x != "delete" && x != "change" && x != "check"){
            std::cout << "continue" << endl;
            break;
        }
        else{
            if(x == "add"){
                ActualPokemon* newact = createNewActualPokemon();
                if(newact != nullptr){
                    addActualPokemon(newact);
                }
                else cout << "fail to create actualpokemon." << endl;
            }
            else if(x == "delete"){
                string inputstring;
                std::cout << "choose name or No." << endl;
                std::getline(std::cin, inputstring);
                if(inputstring == "name"){
                    std::cout << "input pokemon name to delete:"<< endl;
                    std::getline(std::cin, inputstring);
                    string inputstring2;
                    std::cout << "input actual name to delete:"<< endl;
                    std::getline(std::cin, inputstring2);
                    deleteActualPokemon(inputstring, inputstring2);
                }
                else if(inputstring == "No"){
                    int inputint;
                    std::cout << "input pokemon no to delete:"<< endl;
                    std::getline(std::cin, inputstring);
                    inputint = std::stoi(inputstring);
                    int inputint2;
                    std::cout << "input actual no to delete:"<< endl;
                    std::getline(std::cin, inputstring);
                    inputint2 = std::stoi(inputstring);
                    deleteActualPokemon(inputint, inputint2);
                }
                else{
                    cout << "invalid index." << endl;
                    continue;
                }
            }
            else if(x == "change"){
                string inputstring;
                std::cout << "input new info:" << endl;
                ActualPokemon* newact = createNewActualPokemon();
                if(newact == nullptr){
                    cout << "fail to create new model." << endl;
                    continue;
                }
                std::cout << "change with name or No:" << endl;
                std::getline(std::cin, inputstring);
                if(inputstring == "name"){
                    std::cout << "input pokemon name to change:"<< endl;
                    std::getline(std::cin, inputstring);
                    string inputstring2;
                    std::cout << "input actual name to change:"<< endl;
                    std::getline(std::cin, inputstring2);
                    changeActualPokemon(newact, inputstring, inputstring2);
                }
                else if(inputstring == "No"){
                    int inputint;
                    std::cout << "input pokemon no to change:"<< endl;
                    std::getline(std::cin, inputstring);
                    inputint = std::stoi(inputstring);
                    int inputint2;
                    std::cout << "input actual no to change:"<< endl;
                    std::getline(std::cin, inputstring);
                    inputint2 = std::stoi(inputstring);
                    changeActualPokemon(newact, inputint, inputint2);
                }
                else{
                    cout << "invalid index." << endl;
                    continue;
                }
            }
            else if(x == "check"){
                string inputstring;
                std::cout << "input 'all' to check all actual pokemons, if not, input anything else:"<< endl;
                std::getline(std::cin, inputstring);
                if(inputstring == "all"){
                    for(ActualPokemon* act : allactualpokemons){
                        act->showActualPokemon();
                    }
                }
                else{
                    std::cout << "choose name or No." << endl;
                    std::getline(std::cin, inputstring);
                    if(inputstring == "name"){
                        std::cout << "input pokemon name to check:"<< endl;
                        std::getline(std::cin, inputstring);
                        string inputstring2;
                        std::cout << "input actual name to check:"<< endl;
                        std::getline(std::cin, inputstring2);
                        useActualPokemon(inputstring, inputstring2)->showActualPokemon();
                    }
                    else if(inputstring == "No"){
                        int inputint;
                        std::cout << "input pokemon no to check:"<< endl;
                        std::getline(std::cin, inputstring);
                        inputint = std::stoi(inputstring);
                        int inputint2;
                        std::cout << "input actual no to check:"<< endl;
                        std::getline(std::cin, inputstring);
                        inputint2 = std::stoi(inputstring);
                        useActualPokemon(inputint, inputint2)->showActualPokemon();
                    }
                    else{
                        cout << "invalid index." << endl;
                        continue;
                    }
                }
            }
        }
    }
}

void select(playerpocket* plpc){
    string x;
    while(true){
        std::cout << " if you want to add pocket pokemon, input 'add pokemon';\n"
        << " want to delete pocket pokemon, input 'delete pokemon';\n"
        << " want to change pocket pokemon, input 'change pokemon';\n"
        << " want to set onstage pokemon, input 'set on stage';\n"
        << " want to delete onstage pokemon, input 'delete on stage';\n"
        << " want to change onstage pokemon, input 'change on stage';\n"
        << " want to check onstage pokemon, input 'check on stage';\n"
        << " want to check all pocket pokemons, input 'check all';\n"
        << " want to check one pocket pokemon, input 'check one'.\n"
        << " want to change item, input 'change item';\n"
        << " otherwise, input anything else." << endl;
        std::getline(std::cin, x);
        if (x != "add pokemon" &&  x != "delete pokemon" && x != "change pokemon" && x != "set on stage" && 
            x != "delete on stage" && x != "change on stage" && 
            x != "check on stage" && x != "check all" && x != "check one" && x != "change item"){
            std::cout << "continue" << endl;
            break;
        }
        else{
            string inputstring;
            if(x == "add pokemon"){
                if(plpc->getPocketSize() >= maxpokemonnum){
                    cout << "pocket is full." << endl;
                    continue;
                }
                cout << "choose to use pokemon name or No:" << endl;
                std::getline(std::cin, inputstring);
                if(inputstring == "name"){
                    string inputstring2;
                    std::cout << "input pokemon name to add:"<< endl;
                    std::getline(std::cin, inputstring);
                    cout << "input actual name to add:"<< endl;
                    std::getline(std::cin, inputstring2);
                    ActualPokemon* newpok = useActualPokemon(inputstring, inputstring2);
                    if(newpok == nullptr){
                        cout << "no such pokemon." << endl;
                        continue;
                    }
                    plpc->selectPokemon(newpok);
                }
                else if(inputstring == "No"){
                    int inputint;
                    int inputint2;
                    std::cout << "input pokemon No to add:"<< endl;
                    std::getline(std::cin, inputstring);
                    inputint = std::stoi(inputstring);
                    std::cout << "input actual No to add:"<< endl;
                    std::getline(std::cin, inputstring);
                    inputint2 = std::stoi(inputstring);
                    ActualPokemon* newpok = useActualPokemon(inputint, inputint2);
                    if(newpok == nullptr){
                        cout << "no such pokemon." << endl;
                        continue;
                    }
                    plpc->selectPokemon(newpok);
                }
                else{
                    cout << "invalid index." << endl;
                }
            }
            else if(x == "delete pokemon"){
                int index;
                std::cout << "input index of pokemon to delete:" << endl;
                std::getline(std::cin, inputstring);
                index = std::stoi(inputstring);
                plpc->deletePokemon(index);
            }
            else if(x == "change pokemon"){
                int index;
                std::cout << "input index of pokemon to change:" << endl;
                std::getline(std::cin, inputstring);
                index = std::stoi(inputstring);
                cout << "choose to use pokemon name or No:" << endl;
                std::getline(std::cin, inputstring);
                if(inputstring == "name"){
                    string inputstring2;
                    std::cout << "input pokemon name to add:"<< endl;
                    std::getline(std::cin, inputstring);
                    cout << "input actual name to add:"<< endl;
                    std::getline(std::cin, inputstring2);
                    ActualPokemon* newpok = useActualPokemon(inputstring, inputstring2);
                    if(newpok == nullptr){
                        cout << "no such pokemon." << endl;
                        continue;
                    }
                    plpc->changePokemon(index, newpok);
                }
                else if(inputstring == "No"){
                    int inputint;
                    int inputint2;
                    std::cout << "input pokemon No to add:"<< endl;
                    std::getline(std::cin, inputstring);
                    inputint = std::stoi(inputstring);
                    std::cout << "input actual No to add:"<< endl;
                    std::getline(std::cin, inputstring);
                    inputint2 = std::stoi(inputstring);
                    ActualPokemon* newpok = useActualPokemon(inputint, inputint2);
                    if(newpok == nullptr){
                        cout << "no such pokemon." << endl;
                        continue;
                    }
                    plpc->changePokemon(index, newpok);
                }
                else{
                    cout << "invalid index." << endl;
                    continue;
                }
            }
            else if(x == "set on stage"){
                int index;
                std::cout << "input index of pokemon to set on stage:" << endl;
                std::getline(std::cin, inputstring);
                index = std::stoi(inputstring);
                plpc->setOnStage(index);
            }
            else if(x == "delete on stage"){
                int index;
                std::cout << "input index of pokemon to delete on stage, or input -1 to clear on stage:" << endl;
                std::getline(std::cin, inputstring);
                index = std::stoi(inputstring);
                if (index == -1){
                    if(plpc->getOnStageNum() == -1){
                        cout << "No pokemon on stage." << endl;
                        continue;
                    }
                    plpc->deleteOnStage(plpc->getOnStageNum());
                }
                else if(index < 0 || index >= plpc->getPocketSize()){
                    cout << "Invalid index." << endl;
                    continue;
                }
                else{
                plpc->deleteOnStage(index);
                }
            }
            else if(x == "change on stage"){
                int index;
                std::cout << "input index of pokemon to change:" << endl;
                std::getline(std::cin, inputstring);
                index = std::stoi(inputstring);
                plpc->changeOnStage(index);
            }
            else if(x == "check on stage"){
                cout << "onstage pokemon no: "<< plpc->getOnStageNum() << endl;
                cout << "onstage pokemon name: "<< plpc->getOnStagePokemon()->getPokemonName() << endl;
            }
            else if(x == "check all"){
                for(int i = 0; i < plpc->getPocketSize(); i++){
                    cout <<"pokemon no: "<< plpc->getPocketPokemonNo(i) 
                    <<" name: "<< plpc->getPocketPokemonName(i) 
                    <<" actual no: "<< plpc->getPocketActualNo(i) 
                    <<" actual name: "<< plpc->getPocketActualName(i) 
                    <<" status: "<< plpc->getPocketStatus(i) 
                    <<" current hp: "<< plpc->getPocketCurrentHp(i) << endl;
                }
            }
            else if(x == "check one"){
                int index;
                std::cout << "input index of pokemon to check:" << endl;
                std::getline(std::cin, inputstring);
                index = std::stoi(inputstring);
                cout <<"pokemon no: "<< plpc->getPocketPokemonNo(index) 
                    <<" name: "<< plpc->getPocketPokemonName(index) 
                    <<" actual no: "<< plpc->getPocketActualNo(index) 
                    <<" actual name: "<< plpc->getPocketActualName(index) 
                    <<" status: "<< plpc->getPocketStatus(index) 
                    <<" current hp: "<< plpc->getPocketCurrentHp(index) << endl;
            }
            else if(x == "change item"){
                int index;
                std::cout << "input index of pokemon to change item:" << endl;
                std::getline(std::cin, inputstring);
                index = std::stoi(inputstring);
                ItemType newitem = plpc->getPocketItem(index);
                cout << "current item: " << newitem << endl;
                std::getline(std::cin, inputstring);
                string inputstring2;
                std::cout << "input item to change:"<< endl;
                std::getline(std::cin, inputstring);
                if (inputstring == "noitem"){
                    plpc->pocketChangeItem(index, NOITEM);
                }
                else if (inputstring == "drink"){
                    plpc->pocketChangeItem(index, DRINK);
                }
                else{
                    cout << "invalid item." << endl;
                    continue;
                }
            }
        }
    }
}

float calculateDamage(PokemonInBattle* attacker, PokemonInBattle* defender, skillinfo* skill){
    float damage = 0;
    float effectfactor = effectiveness[skill->type][defender->getActualType()];
    float sametypebonus = 1;
    if (attacker->getActualType() == skill->type) {
        sametypebonus = 1.5;
    }
    if (skill->category == PHYSICAL){
        damage = max(
        attacker->getActualPokemon()->getActualPhyatkNew()
        * attacker->getPanelChange()[0]
        * skill->power * 0.1 * 0.05, 
        attacker->getActualPokemon()->getActualPhyatkNew()
        * attacker->getPanelChange()[0]
        * skill->power * 0.1 
        - defender->getActualPokemon()->getActualPhydefNew() 
        * defender->getPanelChange()[1]) 
        * effectfactor * sametypebonus;
    }
    else{
        damage = max(
        attacker->getActualPokemon()->getActualSpcatkNew()
        * attacker->getPanelChange()[2]
        * skill->power * 0.1 * 0.05, 
        attacker->getActualPokemon()->getActualSpcatkNew()
        * attacker->getPanelChange()[2]
        * skill->power * 0.1 
        - defender->getActualPokemon()->getActualSpcdefNew() 
        * defender->getPanelChange()[3]) 
        * effectfactor * sametypebonus;
    }
    return damage;
}

playeraction oneStep(playerpocket* plpc1, int playernum){
    playeraction action1;
    string inputbattle1;
    while(true){
        cout << "Player "<< playernum <<" action, input change or skill."<< endl;
        getline(cin, inputbattle1);
        if(inputbattle1 != "change" && inputbattle1 != "skill"){
                cout << "invalid action." << endl;
                continue;
            }
        if(inputbattle1 == "change"){
            cout << "input change num." << endl;
            string inputstring;
            int index;
            getline(cin, inputstring);
            index = stoi(inputstring);
            if(index < 0 || index >= plpc1->getPocketSize()){
                cout << "invalid index." << endl;
                continue;
            }
            if(index == plpc1->getOnStageNum()){
                cout << "already on stage." << endl;
                continue;
            }
            if(plpc1->getPocketIsAlive(index) == false){
                cout << "pokemon is not alive." << endl;
                continue;
            }
            action1.action = "change";
            action1.skillnum_or_pokemon_num = index;
            return action1;
        }
        if(inputbattle1 == "skill"){
            cout << "input skill num." << endl;
            string inputstring;
            int index;
            getline(cin, inputstring);
            index = stoi(inputstring);
            if(index < 0 || index >= maxskillnum || plpc1->getOnStagePokemon()->getOneActualSkill(index) == ""){
                cout << "invalid index or no such skill." << endl;
                continue;
            }
            int pp = plpc1->getOnStagePokemon()->getInBattlePP(index);
            if(pp <= 0){
                cout << "no PP." << endl;
                continue;
            }
            action1.action = "skill";
            action1.skillnum_or_pokemon_num = index;
            plpc1->getOnStagePokemon()->setInBattlePP(index, pp - 1);
            return action1;
        }
    }
}

int implement(playeraction plact1, playerpocket* plpc1, playerpocket* plpc2,int index1,int index2){
    if(plact1.action == "change"){
        plpc1->changeOnStage(plact1.skillnum_or_pokemon_num);
        cout << "Player "<< index1 <<" changed pokemon to " << plpc1->getOnStageNum() << endl;
        return 0;
    }
    else if(plact1.action == "skill"){
        float dm = calculateDamage(plpc1->getOnStagePokemon(), plpc2->getOnStagePokemon(), 
        allSkillsInPokemon->getOneSkill(plpc1->getOnStagePokemon()->getOneActualSkill(plact1.skillnum_or_pokemon_num)));
        cout << "Player "<< index1 <<" used skill " << plpc1->getOnStagePokemon()->getOneActualSkill(plact1.skillnum_or_pokemon_num) << endl;
        cout << "Player "<< index1 <<" dealt " << dm << " damage to Player "<<index2<<"." << endl;
        plpc2->getOnStagePokemon()->setCurrentHp(plpc2->getOnStagePokemon()->getCurrentHp() - dm);
        cout << "Player "<< index2 <<" currentHp = "<<plpc2->getOnStagePokemon()->getCurrentHp()<<endl;
        return 1;
    }
    return -1;
}

int oneBattleRound(playerpocket* plpc1, playerpocket* plpc2){
        if(plpc1->pocketAliveNum() <= 0 ){
            cout << "Player 2 wins."<< endl;
            return 2;
        }
        if(plpc2->pocketAliveNum() <= 0 ){
            cout << "Player 1 wins."<< endl;
            return 1;
        }
        while(((plpc1->getOnStageNum() == -1 || plpc2->getOnStageNum() == -1 )
            ||(!(plpc1->getOnStagePokemon()->isAlive() && plpc2->getOnStagePokemon()->isAlive()))) 
            && plpc1->pocketAliveNum() > 0 && plpc2->pocketAliveNum() > 0){
            if(plpc1->getOnStageNum() == -1 ||(!(plpc1->getOnStagePokemon()->isAlive()))){
                string inputstring;
                int index;
                cout << "Player 1 has no living pokemon on stage, please select one." << endl;
                getline(cin, inputstring);
                index = stoi(inputstring);
                plpc1->changeOnStage(index);
            }
            if(plpc2->getOnStageNum() == -1||(!(plpc2->getOnStagePokemon()->isAlive()))){
                string inputstring;
                int index;
                cout << "Player 2 has no living pokemon on stage, please select one." << endl;
                getline(cin, inputstring);
                index = stoi(inputstring);
                plpc2->changeOnStage(index);
            }

        }
        float spd1 = plpc1->getOnStagePokemon()->getActualPokemon()->getActualSpeedNew() * plpc1->getOnStagePokemon()->getPanelChange()[4];
        float spd2 = plpc2->getOnStagePokemon()->getActualPokemon()->getActualSpeedNew() * plpc2->getOnStagePokemon()->getPanelChange()[4];
        playeraction action1 = oneStep(plpc1, 1);
        playeraction action2 = oneStep(plpc2, 2);

        if(action1.action == "change") spd1 += 1000;
        if(action2.action == "change") spd2 += 1000;

        static std::mt19937 rng(std::random_device{}());
        std::uniform_real_distribution<float> dist(-0.5f, 0.5f);
        if(fabs(spd1 - spd2) < 1e-6) spd1 += dist(rng);
        if(spd1 >= spd2){
            implement(action1, plpc1, plpc2,1,2);
            if(!(plpc1->getOnStagePokemon()->isAlive() && plpc2->getOnStagePokemon()->isAlive())) return 0;
            implement(action2, plpc2, plpc1,2,1);
            return 0;
        }
        else{
            implement(action2, plpc2, plpc1,2,1);
            if(!(plpc1->getOnStagePokemon()->isAlive() && plpc2->getOnStagePokemon()->isAlive())) return 0;
            implement(action1, plpc1, plpc2,1,2);
            return 0;
        }
}

#endif//ALL_POKEMONS_H