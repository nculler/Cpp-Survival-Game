#include <iostream>
#include <sstream>
#include <time.h>

using namespace std;

class Player {
    public:
    Player(int x, int y){
        health = MAX_HEALTH;
        hunger = MAX_HUNGER;
        thirst = MAX_THIRST;
        
        this->x = x;
        this->y = y;
        this->score = 0;
    }
    
    int getScore() const {
        cout << "Your score is: ";
        return score;
    }
    
    void takeDamage(int val){
        this->health -= val;
        if(this->health < 0) this->health = 0;
    }
    
    void takeTurn(){
        this->thirst--;
        this->hunger--;
        
        if(this->thirst <= 0){
            this->health--;
            this->thirst = 0;
        }
        
        if(this->hunger <= 0){
            this->health--;
            this->hunger = 0;
        }
        
        this->score++;
    }
    
    string getStats() const {
        stringstream ss;
        ss  << "============\n"
            //<< "Health: " << this->health << "\n"
            << "\033[1;31m Health: \033[0m" << this->health <<"\n"
            //<< "Hunger: " << this->hunger << "\n" 
            << "\033[1;32m Hunger: \033[0m" << this->hunger <<"\n"
            //<< "Thirst: " << this->thirst << "\n"
            << "\033[1;34m Thirst: \033[0m" << this->thirst <<"\n"
            << "============\n";
        return ss.str();
    }
    
    bool isAlive() const {
        return this->health > 0;
    }
    
    void increaseThirst(int val){
        this->thirst = this->thirst + val;
        if(this->thirst > MAX_THIRST) this->thirst = MAX_THIRST;
    }
    
    void increaseHunger(int val){
        this->hunger += val;
        if(this->hunger > MAX_HUNGER) this->hunger = MAX_HUNGER;
    }
    
    void increaseHealth(int val){
        this->health += val;
        if(this->health > MAX_HEALTH) this->health = MAX_HEALTH;
    }
    
    int x, y;
    private:
    int health, hunger, thirst, score;
    const int MAX_HEALTH = 5;
    const int MAX_HUNGER = 10;
    const int MAX_THIRST = 10;
};

class Land {
    public:
    virtual string getDescription() = 0;
    virtual string visit(Player& player) = 0;
};

// TODO: Define at least 3 more types of derivded land types
// TODO: Add some unique effect to each new type

class Forest : public Land {
    public:
    string getDescription(){
        return "a red wood forest";
    }
    
    string visit(Player& player){
        int randomNum = rand() % 100;
        
        if(randomNum > 1){
            player.increaseHunger(1);
            return "You find some wild corn and eat it";
        } else {
            player.takeDamage(1000);
            return "You died to a falling tree";
        }
    }
};

class Lake : public Land {
    public:
    string getDescription(){
            return "a clear sparkling lake.";
    }
    
    string visit(Player& player){
        int randomNum = rand() % 100;
        if (randomNum > 49) {
            player.increaseThirst(-2);
            return "You drank dirty water";
        }
        else {
            player.increaseThirst(2);
            return "You visit the lake and drink its clean water";
        }
        
    }
};

class Mountain : public Land {
    public:
    string getDescription(){
        return "a tall, snow capped mountain";
    }
    
    string visit(Player& player){
        int randomNum = rand() % 100;
            if (randomNum > 1){
            player.increaseThirst(2);
            return "You find a stream and drink from it.";
            }
            
            else {
                player.takeDamage(1000);
                return "You fell off the mountain and died";
            }
    }
};

class Village : public Land {
    public:
    string getDescription(){
        return "a bustling village with a slight scent of pie";
    }
    
    string visit(Player& player){
        int randomNum = rand() % 100;
        if (randomNum > 74){
            player.increaseHunger(2);
            return "A nice grandma gives you some pie";
        }
        
        else {
            player.takeDamage(1);
            return "A grandma scolds you for stealing her pie";
        }
    }
};

class Dungeon : public Land {
    public:
    string getDescription(){
        return "an underground dungeon";
    }
    
    string visit(Player& player){
        int randomNum = rand() % 100;
        if (randomNum > 59){
            player.takeDamage(3);
            return "You flee from the dragon";
        }
        else {
            player.increaseHealth(2);
            player.increaseHunger(5);
            player.increaseThirst(5);
            return "You slay the dragon and take its loot";
        }
    }
};

class Beach : public Land {
    public:
    string getDescription(){
        return "a soft sanded beach";
    }
    
    string visit(Player& player){
        player.increaseThirst(1);
        player.increaseHunger(1);
        return "You rest after a long days journey";
    }
};

class School : public Land {
    public:
    string getDescription(){
        return "a school classroomm with a familiar face";
    }
    
    string visit(Player& player){
        int randomNum = rand() % 100;
        if (randomNum > 9) {
            player.increaseThirst(2);
            return "A familiar professor hands you a Monster engergy drink";
        }
        else {
            player.takeDamage(1000);
            return "You were caught cheating and suffered the consequences";
        }
    }
};

class End : public Land {
    public:
    string getDescription(){
        return "a light at the end of your journey";
    }
    
    string visit(Player& player){
        player.takeDamage(1000);
        return "You completed your journey and can now rest";
    }
};

const int MAP_SIZE = 10;
Land* map[MAP_SIZE][MAP_SIZE];

void populateMap(){
    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            // TODO: Modify this code to add your new land types
            int randomNum = rand() % 8;
            switch(randomNum){
                case 0: // Forest
                    map[i][j] = new Forest;
                    break;
                case 1: // Lake
                    map[i][j] = new Lake;
                    break;
                case 2: // Mountian
                    map[i][j] = new Mountain;
                    break;
                case 3: // Village
                    map[i][j] = new Village;
                    break;
                case 4: // Dungeon
                    map[i][j] = new Dungeon;
                    break;
                case 5: // Beach
                    map[i][j] = new Beach;
                    break;
                case 6: // School
                    map[i][j] = new School;
                    break;
                case 7: // End
                    map[i][j] = new End;
                    break;
                default:
                    cout << "Invalid land type selected" << endl;
                    break;
            }
        }
    }
}

int main(){
    srand(time(0));
    
    populateMap();
    
    Player player(MAP_SIZE/2, MAP_SIZE/2);
    //Player player(0, 0);
    
    cout << "You wake up and find yourself lost in the middle of a strange wilderness." << endl;
    
    // TODO: Handle boundary conditions (e.g., if index out of bounds north, you index the south-most location)
    
    while(player.isAlive()){
        if(player.y==0){
            cout << "To the north you see " << map[player.x][player.y + 9]->getDescription() << endl;
        }
        
        else {
            cout << "To the north you see " << map[player.x][player.y - 1]->getDescription() << endl;
        }
        
        if(player.x==9){
            cout << "To the east you see " << map[player.x - 9][player.y]->getDescription() << endl;
        }
        
        else{
            cout << "To the east you see " << map[player.x + 1][player.y]->getDescription() << endl;
        }
        
        if(player.y==9){
            cout << "To the south you see " << map[player.x][player.y - 9]->getDescription() << endl;
        }
        
        else{
            cout << "To the south you see " << map[player.x][player.y + 1]->getDescription() << endl;
        }
        
        if(player.x==0){
            cout << "To the west you see " << map[player.x + 9][player.y]->getDescription() << endl;
        }
        
        else{
            cout << "To the west you see " << map[player.x - 1][player.y]->getDescription() << endl; 
        }
        
        /*cout << "To the north you see " << map[player.x][player.y - 1]->getDescription() << endl;
        cout << "To the east you see " << map[player.x + 1][player.y]->getDescription() << endl;
        cout << "To the south you see " << map[player.x][player.y + 1]->getDescription() << endl;
        cout << "To the west you see " << map[player.x - 1][player.y]->getDescription() << endl;
        */
        cout << "Which way will you go? Enter N, E, S, or W:" << endl;
        //cout << player.x << "," << player.y << endl;
        char userInput;
        cin >> userInput;
        
        if(userInput == 'N' || userInput == 'E' || userInput == 'S' || userInput == 'W'){
        
            switch(userInput){
                case 'N':
                    if(player.y==0){
                        player.y = player.y + 9;
                    }
                    else {
                        player.y = player.y - 1;
                    }
                    break;
                case 'E':
                    if(player.x==9){
                        player.x = player.x - 9;
                    }
                    else {
                        player.x = player.x + 1;
                    }
                    break;
                case 'S':
                    if(player.y==9){
                        player.y = player.y - 9;
                    }
                    else {
                        player.y = player.y + 1;
                    }
                    break;
                case 'W':
                    if(player.x==0){
                        player.x = player.x + 9;
                    }
                    else {
                        player.x = player.x - 1;
                    }
                    break;
                default:
                    break;
            }
        
        
    
        cout << map[player.x][player.y]->visit(player) << endl;
        
        cout << player.getStats() << endl;
        player.takeTurn();
        
        }
        
        else{
            cout << "Invalid Input" << endl;
            
        }
    }
    
    cout << "You died." << endl;
    cout << player.getScore() << endl;
    
    return 0;
}