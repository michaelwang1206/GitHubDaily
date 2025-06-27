#include "pokemon actual.h"

using namespace std;

#ifndef POKEMON_FUNCTIONS_H
#define POKEMON_FUNCTIONS_H

void addPokemonModel(PokemonModel* md){
    for(int i = 0; i < allpokemonmodels.size(); i++){
        if(md->getPokemonNo() == allpokemonmodels[i]->getPokemonNo()){
            cout << "Pokemon No " << md->getPokemonNo() << " has existed in allmodels " << i << endl;
            return;
        }
        else if(md->getPokemonName() == allpokemonmodels[i]->getPokemonName()){
            cout << "Pokemon Name " << md->getPokemonName() << " has existed in allmodels " << i << endl;
            return;
        }
    }
    allpokemonmodels.push_back(md);
    cout << "Pokemon added to allmodels sucessfully." << endl;
}

void deletePokemonModel(int no){
    for(int i = 0; i < allpokemonmodels.size(); i++){
        if(no == allpokemonmodels[i]->getPokemonNo()){
            for(int j = allactualpokemons.size() - 1; j >= 0; j--){
                if(no == allactualpokemons[j]->getPokemonNo()){
                    delete allactualpokemons[j];
                    allactualpokemons.erase(allactualpokemons.begin() + j);
                    cout << "Pokemon No " << no << " deleted from allactuals "<< j << " successfully." << endl;
                }
            }
            delete allpokemonmodels[i];
            allpokemonmodels.erase(allpokemonmodels.begin() + i);
            cout << "Pokemon No " << no << " deleted from allmodels "<< i << " successfully." << endl;
            return;     
        }
    }
    cout <<"Cannot find Pokemon No "<< no << " in allmodels." << endl;
}

void deletePokemonModel(string nm){
    for(int i = 0; i < allpokemonmodels.size(); i++){
        if(nm == allpokemonmodels[i]->getPokemonName()){
            for(int j = allactualpokemons.size() - 1; j >= 0; j--){
                if(nm == allactualpokemons[j]->getPokemonName()){
                    delete allactualpokemons[j];
                    allactualpokemons.erase(allactualpokemons.begin() + j);
                    cout << "Pokemon Name " << nm << " deleted from allactuals "<< j << " successfully." << endl;
                }
            }
            delete allpokemonmodels[i];
            allpokemonmodels.erase(allpokemonmodels.begin() + i);
            cout << "Pokemon Name " << nm << " deleted from allmodels "<< i << " successfully." << endl;
            return;     
        }
    }
    cout <<"Cannot find Pokemon Name " << nm << " in allmodels." << endl;
}

void changePokemonModel(PokemonModel* md, int no){
    if(md->getPokemonNo() != no){
        cout << "invalid input."<< endl;
        return;
    }
    for(int i = 0; i < allpokemonmodels.size(); i++){
        if(md->getPokemonName() == allpokemonmodels[i]->getPokemonName() && no != allpokemonmodels[i]->getPokemonNo()){
        cout << "Pokemon Name " << md->getPokemonName() << " has existed in allmodels " << i << endl;
            return;
        }
    }
    for(int i = 0; i < allpokemonmodels.size(); i++){
        if(no == allpokemonmodels[i]->getPokemonNo()){
            for(int j = allactualpokemons.size() - 1; j >= 0; j--){
                if(no == allactualpokemons[j]->getPokemonNo()){
                    delete allactualpokemons[j];
                    allactualpokemons.erase(allactualpokemons.begin() + j);
                    cout << "Pokemon No " << no << " deleted from allactuals "<< j << " successfully." << endl;
                }
            }
            delete allpokemonmodels[i];
            allpokemonmodels[i] = md;
            cout << "Pokemon No " << no << " changed from allmodels "<< i << " successfully." << endl;
            return;     
        }
    }
    cout <<"Cannot find Pokemon No "<< no << " in allmodels." << endl;    
}

void changePokemonModel(PokemonModel* md, string nm){
    if(md->getPokemonName() != nm){
        cout << "invalid input."<< endl;
        return;
    }
    for(int i = 0; i < allpokemonmodels.size(); i++){
        if(md->getPokemonNo() == allpokemonmodels[i]->getPokemonNo() && nm != allpokemonmodels[i]->getPokemonName()){
        cout << "Pokemon No " << md->getPokemonNo() << " has existed in allmodels " << i << endl;
            return;
        }
    }
    for(int i = 0; i < allpokemonmodels.size(); i++){
        if(nm == allpokemonmodels[i]->getPokemonName()){
            for(int j = allactualpokemons.size() - 1; j >= 0; j--){
                if(nm == allactualpokemons[j]->getPokemonName()){
                    delete allactualpokemons[j];
                    allactualpokemons.erase(allactualpokemons.begin() + j);
                    cout << "Pokemon Name " << nm << " deleted from allactuals "<< j << " successfully." << endl;
                }
            }
            delete allpokemonmodels[i];
            allpokemonmodels[i] = md;
            cout << "Pokemon Name " << nm << " changed from allmodels "<< i << " successfully." << endl;
            return;     
        }
    }
    cout <<"Cannot find Pokemon Name " << nm << " in allmodels." << endl;
}

PokemonModel* usePokemonModel(int no) {
    for(int i = 0; i < allpokemonmodels.size(); i++){
        if(no == allpokemonmodels[i]->getPokemonNo()){
            return allpokemonmodels[i];     
        }
    }
    cout <<"Cannot find Pokemon No "<< no << " in allmodels." << endl;
    return nullptr;
}

PokemonModel* usePokemonModel(string nm) {
    for(int i = 0; i < allpokemonmodels.size(); i++){
        if(nm == allpokemonmodels[i]->getPokemonName()){
            return allpokemonmodels[i];     
        }
    }
    cout <<"Cannot find Pokemon Name "<< nm << " in allmodels." << endl;
    return nullptr;
}

void addActualPokemon(ActualPokemon* act){
    bool flg = false;
    for(int i = 0; i < allpokemonmodels.size(); i++){
        if(act->getPokemonName() == allpokemonmodels[i]->getPokemonName() && act->getPokemonNo() == allpokemonmodels[i]->getPokemonNo()){
            flg = true;
            break;
        }
    }
    if (!flg){
        cout << "invalid actual pokemon." << endl;
        return;
    }
    for(int i = 0; i < allactualpokemons.size(); i++){
        if(act->getPokemonNo() == allactualpokemons[i]->getPokemonNo() && act->getActualNo() == allactualpokemons[i]->getActualNo()){
            cout << "Pokemon No " << act->getPokemonNo() << " actual No " << act->getActualNo() << " has existed in allactuals " << i << endl;
            return;
        }
        else if(act->getPokemonName() == allactualpokemons[i]->getPokemonName() && act->getActualName() == allactualpokemons[i]->getActualName()){
            cout << "Pokemon Name " << act->getPokemonName() << " actual Name " << act->getActualName() << " has existed in allactuals " << i << endl;
            return;
        }
    }
    allactualpokemons.push_back(act);
    cout << "Pokemon added to allactuals sucessfully." << endl;
}

void deleteActualPokemon(int pkno, int actno){
    for(int i = 0; i < allactualpokemons.size(); i++){
        if(pkno == allactualpokemons[i]->getPokemonNo() && actno == allactualpokemons[i]->getActualNo()){
            delete allactualpokemons[i];
            allactualpokemons.erase(allactualpokemons.begin() + i);
            cout << "Pokemon No " << pkno << " actual No " << actno << " deleted from allactuals sucessfully." << endl;
            return;
        }
    }
    cout << "Pokemon No " << pkno << " actual No " << actno << " is not found in allactuals." << endl;
}

void deleteActualPokemon(string pknm, string actnm){
    for(int i = 0; i < allactualpokemons.size(); i++){
        if(pknm == allactualpokemons[i]->getPokemonName() && actnm == allactualpokemons[i]->getActualName()){
            delete allactualpokemons[i];
            allactualpokemons.erase(allactualpokemons.begin() + i);
            cout << "Pokemon Name " << pknm << " actual Name " << actnm << " deleted from allactuals sucessfully." << endl;
            return;
        }
    }
    cout << "Pokemon Name " << pknm << " actual Name " << actnm << " is not found in allactuals." << endl;
}

void changeActualPokemon (ActualPokemon* actpok, int pkno, int actno){
    if(actpok->getPokemonNo() != pkno || actpok->getActualNo() != actno){
        cout << "invalid input."<< endl;
        return;
    }
    for(int i = 0; i < allpokemonmodels.size(); i++){
        if((actpok->getPokemonName() == allactualpokemons[i]->getPokemonName() && actpok->getActualName() == allactualpokemons[i]->getActualName())
            && (pkno != allactualpokemons[i]->getPokemonNo() || actno != allactualpokemons[i]->getActualNo())){
        cout << "Pokemon Name " << actpok->getPokemonName()<<" actual name "<< actpok->getActualName() << " has existed in allmodels " << i << endl;
            return;
        }
    }
    for(int i = 0; i < allactualpokemons.size(); i++){
        if(pkno == allactualpokemons[i]->getPokemonNo() && actno == allactualpokemons[i]->getActualNo()){
            delete allactualpokemons[i];
            allactualpokemons[i] = actpok;
            cout << "Pokemon No " << pkno << " actual No " << actno << " changed from allactuals sucessfully." << endl;
            return;
        }
    }
    cout << "Pokemon No " << pkno << " actual No " << actno << " is not found in allactuals." << endl;
}

void changeActualPokemon (ActualPokemon* actpok, string pknm, string actnm){
    if(actpok->getPokemonName() != pknm || actpok->getActualName() != actnm){
        cout << "invalid input."<< endl;
        return;
    }
    for(int i = 0; i < allpokemonmodels.size(); i++){
        if((actpok->getPokemonNo() == allactualpokemons[i]->getPokemonNo() && actpok->getActualNo() == allactualpokemons[i]->getActualNo())
             && (pknm != allactualpokemons[i]->getPokemonName() || actnm != allactualpokemons[i]->getActualName())){
        cout << "Pokemon Name " << actpok->getPokemonNo()<<" actual name "<< actpok->getActualNo() << " has existed in allmodels " << i << endl;
            return;
        }
    }
    for(int i = 0; i < allactualpokemons.size(); i++){
        if(pknm == allactualpokemons[i]->getPokemonName() && actnm == allactualpokemons[i]->getActualName()){
            delete allactualpokemons[i];
            allactualpokemons[i] = actpok;
            cout << "Pokemon Name " << pknm << " actual Name " << actnm << " changed from allactuals sucessfully." << endl;
            return;
        }
    }
    cout << "Pokemon Name " << pknm << " actual Name " << actnm << " is not found in allactuals." << endl;
}

ActualPokemon* useActualPokemon(int pkno, int actno) {
    for(int i = 0; i < allactualpokemons.size(); i++){
        if(pkno == allactualpokemons[i]->getPokemonNo() && actno == allactualpokemons[i]->getActualNo()){
            return allactualpokemons[i];     
        }
    }
    cout << "Pokemon No " << pkno << " actual No " << actno << " is not found in allactuals." << endl;
    return nullptr;
}

ActualPokemon* useActualPokemon(string pknm, string actnm) {
    for(int i = 0; i < allactualpokemons.size(); i++){
        if(pknm == allactualpokemons[i]->getPokemonName() && actnm == allactualpokemons[i]->getActualName()){
            return allactualpokemons[i];     
        }
    }
    cout << "Pokemon Name " << pknm << " actual Name " << actnm << " is not found in allactuals." << endl;
    return nullptr;
}

void clearActualPokemon(){
    for (auto p : allactualpokemons) {
        delete p; // 释放每个指针指向的对象
    }
    allactualpokemons.clear(); // 清空容器
    cout << "All actual pokemons cleared." << endl;
}


void clearPokemonModel(){
    clearActualPokemon();
    for (auto p : allpokemonmodels) {
        delete p; // 释放每个指针指向的对象
    }
    allpokemonmodels.clear(); // 清空容器
    cout << "All pokemon models cleared." << endl;
}


#endif//POKEMON_FUNCTIONS_H