#include "all pokemons.h"

using namespace std;

int main() {
    //vector<string> skills = {"Flamethrower", "Water Gun", "Thunderbolt"};   
    //initializePokemonModels();initializeAllSkills();
    skillinfo* skill1 = new skillinfo {"Flamethrower", FIRE, SPECIAL, 60, 15, "Burns the target.", 0.1};
    skillinfo* skill2 = new skillinfo {"Water Gun", WATER, PHYSICAL, 40, 25, "Shoots a jet of water at the target.", 0.1};
    skillinfo* skill3 = new skillinfo {"Thunderbolt", NORMAL, SPECIAL, 60, 15, "Paralyzes the target.", 0.1};
    allSkillsInPokemon->addSkill(skill1); // 添加技能到全局技能库
    allSkillsInPokemon->addSkill(skill2);
    allSkillsInPokemon->addSkill(skill3);

    addPokemonModel(new PokemonModel(1,"wewe"));
    addPokemonModel(new PokemonModel(2,"youyou"));

    PokemonModel* pokemon1;
    PokemonModel* pokemon2;
    pokemon1 = usePokemonModel("wewe");
    pokemon2 = usePokemonModel(2);

pokemon1->addGroupSkills("Flamethrower");
    pokemon1->addGroupSkills("Water Gun");
    //pokemon1->addGroupSkills("Thunderbolt");
    //pokemon1->addGroupAbilities("None");
    float t[6] = {200,20,20,20,20,20};
    pokemon1->resetGroupPanel(t);

    vector<string> q = pokemon1->getAllSkills();
    for(int i = 0; i < q.size(); i++) {
        cout << q[i] << endl;
    }
    cout << endl;
    for(int i = 0; i < 6; i++) {
        cout << pokemon1->getOneGroupPanel(i) << endl;
    }
    q = pokemon1->getAllSkills();
    for(int i = 0; i < q.size(); i++) {
        cout << q[i] << endl;
    }


    pokemon2->addGroupSkills("Flamethrower");
    pokemon2->addGroupSkills("Water Gun");
    pokemon2->addGroupSkills("Thunderbolt");
    //pokemon1->addGroupAbilities("None");
    float t2[6] = {210,30,10,30,10,25};
    pokemon2->resetGroupPanel(t2);

    q = pokemon2->getAllSkills();
    for(int i = 0; i < q.size(); i++) {
        cout << q[i] << endl;
    }
    cout << endl;
    for(int i = 0; i < 6; i++) {
        cout << pokemon2->getOneGroupPanel(i) << endl;
    }

    pokemon2->removeGroupSkills("Water Gun");
    q = pokemon2->getAllSkills();
    for(int i = 0; i < q.size(); i++) {
        cout << q[i] << endl;
    }


    addActualPokemon(new ActualPokemon(pokemon1, "wewe1", 1));
    addActualPokemon(new ActualPokemon(pokemon1, "wewe2", 2));
    addActualPokemon(new ActualPokemon(pokemon2, "youyou1", 1));
    addActualPokemon(new ActualPokemon(pokemon2, "youyou2", 2));

    ActualPokemon* actpok11 = useActualPokemon("wewe","wewe1");
    ActualPokemon* actpok12 = useActualPokemon(1,2);
    ActualPokemon* actpok21 = useActualPokemon("youyou","youyou1");
    ActualPokemon* actpok22 = useActualPokemon(2,2);
    //ActualPokemon* erractpok11 = useActualPokemon("wew","wewe1");
    //ActualPokemon* erractpok12 = useActualPokemon(1,3);

    actpok11->setCharacter(TIMID);
    actpok11->changeOneSkill("Flamethrower",0);
    actpok11->changeOneSkill("Water Gun",1);
    actpok12->setCharacter(BRAVE);
    actpok12->changeOneSkill("Flamethrower",0);
    actpok12->changeOneSkill("Water Gun",2);

    actpok21->changeOneSkill("Flamethrower",0);
    actpok21->changeOneSkill("Thunderbolt",1);
    actpok22->setCharacter(BRAVE);
    actpok22->changeOneSkill("Flamethrower",0);
    actpok22->changeOneSkill("Thunderbolt",2);
    


    playerpocket* player1pocket = new playerpocket;
    playerpocket* player2pocket = new playerpocket;


    player1pocket->selectPokemon(actpok11);
    player1pocket->selectPokemon(actpok11);//wrong
    player1pocket->selectPokemon(actpok21);

    player2pocket->selectPokemon(actpok12);
    player2pocket->deletePokemon(0);
    player2pocket->selectPokemon(actpok11);
    player2pocket->changePokemon(0, actpok12);
    player2pocket->selectPokemon(actpok22);


    select(player1pocket);
    select(player2pocket);

    while(true){
        int flg = oneBattleRound(player1pocket, player2pocket);
        if (flg != 0) break;
    }
    
    player1pocket->clearpocket();
    player2pocket->clearpocket();
    clearPokemonModel();

}