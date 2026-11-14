//Submarine Adventure portfolio 2
//Alexander w Kazantzis
//11-9-26

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>


//Grid Constants
const int GridSize = 10; //grid size 10x10
const char EmpCell = '.'; // Empty cells
const char PlyrSub = 'S'; //Submarine
const char Unknwn = '?'; //Unknown items
const char AirBble = '@'; // Air bubbles
const char DoorLvr = '/'; // Door lever
const char UnLckdDoor = 'O'; //Unlocked Door
const char LckdDoor = '#'; //Locked Door

class SubCoord{ //Coordinates of the submarine
private:    
    int CoordX; //0
    int CoordY; //1
    public:
    SubCoord(int x, int y) : CoordX(x), CoordY(y) {}
    int getX() const { return CoordX; }
    int getY() const { return CoordY; }
    void setX(int x) { CoordX = x; }
    void setY(int y) { CoordY = y; }

};

struct Treasure {//struct to hold treasure information
    int x;
    int y;
    char type; // s for Shells, D for Doubloons, P for Pearls, G for Gems, T for Treasure Chests
    bool Cllctd;//true if collected, false if not

};

struct Unknown{//struct to hold mystery item information
    int x;
    int y;
    char type; // ? for unknown item
    bool Inspctd;//true if inspected, false if not
};

struct Door { //struct to hold locked and Unlocked Door 
    int x;
    int y;
    char type;
    bool isLckd; // is door locked?
    bool Entered; // Have you gone through this door?
};

struct Lever{//struct to hold lever to open door
    int x;
    int y;
    char type;
    bool LvrUsd; //lever used
};

struct Pthway{//struct to hold pathway to subarea
    int x;
    int y;
    char type;
};

struct AirBubble{ //struct to hold Air bubbles that restore oxygen
    int x;
    int y;
    char type;
    bool Cllctd; // Bubble has been collected
};

int TreaColl[5] = {0,0,0,0,0}; //Treasure Collected (Shells(s),Doubloons(D),Pearls(P),Gems(G),Treasure Chests(T))
int UnknwnInspt[3]= {0,0,0}; //Unknown Items Inspected (fish(f),clam(c),reef(r)))
//Item constants
const int TreaCnt = 9; //treasures
const int UnknwnCnt = 5; //unknown
const int DoorCnt = 3; //Doors to subarea
const int LvrCnt = 1; //lever to open doors
const int BbleCnt = 7; //Air bubbles
//Item counts
Treasure treasures[TreaCnt];
Unknown unknowns[UnknwnCnt];
Door doors[DoorCnt];
Pthway pathways[DoorCnt];
Lever lever[LvrCnt];
AirBubble airbubbles[BbleCnt]; 

bool NoOvrLap(int x,int y,int Trea_Cnt,
              int Unknown_Cnt, int Door_Cnt,
              int Lever_Cnt, int Bubble_Cnt);

void displayGrid(const SubCoord& CurPos) { //Whole game map

    for (int i = 0; i < GridSize; i++) {
        for (int j = 0; j < GridSize; j++) {

            if (i == CurPos.getY() && j == CurPos.getX()) {
                std::cout << PlyrSub << " ";
                continue;
            }
            bool foundItem = false;
            for (int k = 0; k < TreaCnt; k++) {// Check treasures
                if (!treasures[k].Cllctd &&
                    treasures[k].x == j &&
                    treasures[k].y == i) {

                    std::cout << treasures[k].type << " ";
                    foundItem = true;
                    break;
                }
            }

            if (!foundItem) {// Check unknown items
                for (int k = 0; k < UnknwnCnt; k++) {
                    if (!unknowns[k].Inspctd &&
                        unknowns[k].x == j &&
                        unknowns[k].y == i) {

                        std::cout << unknowns[k].type << " ";
                        foundItem = true;
                        break;
                    }
                }
            }
            if (!foundItem) {
                for (int k = 0; k < BbleCnt; k++) {
                    if (!airbubbles[k].Cllctd &&
                        airbubbles[k].x == j &&
                        airbubbles[k].y == i) {

                        std::cout << AirBble << " ";
                        foundItem = true;
                        break;
                    }
                }
            }

            if (!foundItem) {
                for (int k = 0; k < DoorCnt; k++) {
                    if (doors[k].x == j && doors[k].y == i) {
                        std::cout << doors[k].type << " ";
                        foundItem = true;
                        break;
                    }
                }
            }

            if (!foundItem) {
                for (int k = 0; k < LvrCnt; k++) {
                    if (lever[k].x == j && lever[k].y == i) {
                        std::cout << lever[k].type << " ";
                        foundItem = true;
                        break;
                    }
                }
            }
            if (!foundItem) {
                std::cout << EmpCell << " ";
        } 
    }
}
std::cout << std::endl;
}

void DisplayCam(const SubCoord& CurPos) { //What the player sees
    int startX = std::max(0, CurPos.getX() - 1);
    int endX = std::min(GridSize - 1, CurPos.getX() + 1);
    int startY = std::max(0, CurPos.getY() - 1);
    int endY = std::min(GridSize - 1, CurPos.getY() + 1);

    for (int y = startY; y <= endY; y++) {
        for (int x = startX; x <= endX; x++) {

            if (x == CurPos.getX() && y == CurPos.getY()) {
                std::cout << PlyrSub << " ";
                continue;
            }

            bool foundItem = false;

            for (int k = 0; k < TreaCnt; k++) {
                if (!treasures[k].Cllctd &&
                    treasures[k].x == x &&
                    treasures[k].y == y) {

                    std::cout << treasures[k].type << " ";
                    foundItem = true;
                    break;
                }
            }

            if (!foundItem) {
                for (int k = 0; k < UnknwnCnt; k++) {
                    if (!unknowns[k].Inspctd &&
                        unknowns[k].x == x &&
                        unknowns[k].y == y) {

                        std::cout << Unknwn << " ";
                        foundItem = true;
                        break;
                    }
                }
            }

            if (!foundItem) {
                for (int k = 0; k < BbleCnt; k++) {
                    if (!airbubbles[k].Cllctd &&
                        airbubbles[k].x == x &&
                        airbubbles[k].y == y) {

                        std::cout << AirBble << " ";
                        foundItem = true;
                        break;
                    }
                }
            }

            if (!foundItem) {
                for (int k = 0; k < DoorCnt; k++) {
                    if (doors[k].x == x && doors[k].y == y) {
                        std::cout << doors[k].type << " ";
                        foundItem = true;
                        break;
                    }
                }
            }

            if (!foundItem) {
                for (int k = 0; k < LvrCnt; k++) {
                    if (lever[k].x == x && lever[k].y == y) {
                        std::cout << lever[k].type << " ";
                        foundItem = true;
                        break;
                    }
                }
            }

            if (!foundItem) {
                std::cout << EmpCell << " ";
            }
        }

        std::cout << std::endl;
    }
}

void UnlckDoors(){ //Unlocks the doors to the Sub areas
    for(int i =0; i<DoorCnt; i++) {
        doors[i].isLckd = false;
        doors[i].type = UnLckdDoor;
    }
}

void Inspect(const SubCoord& CurPos, int& SubOxy) {//Inspect items
    bool foundUnknown = false;
    bool foundBubble = false;
    bool foundLever = false;
    for (int i = 0; i < UnknwnCnt; i++) {//Check for Unknown.
        if (!unknowns[i].Inspctd &&
            std::abs(unknowns[i].x - CurPos.getX()) <= 1 &&
            std::abs(unknowns[i].y - CurPos.getY()) <= 1) {

            foundUnknown = true;
            unknowns[i].Inspctd = true;

            std::cout << "Unknown item inspected.\n";

            int result = rand() % 100;

            if (result < 50) {
                std::cout << "You found a fish! Nothing happens.\n";
                UnknwnInspt[0]++;
            }
            else if (result < 80) {
                std::cout << "You found a clam! Oxygen +20.\n";
                UnknwnInspt[1]++;
                SubOxy += 20;
                if (SubOxy > 100) {
                    SubOxy = 100;
                }
            }
            else {
                std::cout << "You found a reef! Oxygen -10.\n";
                UnknwnInspt[2]++;
                SubOxy -= 10;
                if(SubOxy<0){
                    SubOxy=0;
                }
            }

            break;
        }
            
        }
    if (!foundUnknown) {
            std::cout << "No unknown items nearby.\n";
        }
    for (int i = 0; i < LvrCnt; i++) { //Lever Check
            if (std::abs(lever[i].x - CurPos.getX()) <= 1 &&
                std::abs(lever[i].y - CurPos.getY()) <= 1 &&
                !lever[i].LvrUsd) {
                foundLever = true;
                lever[i].LvrUsd = true;

                std::cout << "Lever activated! Doors unlocked.\n";

                UnlckDoors();
            break;
            }
        }
        if (!foundLever) {
            std::cout << "No Levers nearby.\n";
        }
        for (int i = 0; i < BbleCnt; i++) {//Bubble Check
            if (std::abs(airbubbles[i].x - CurPos.getX()) <= 1 &&
                std::abs(airbubbles[i].y - CurPos.getY()) <= 1 &&
                !airbubbles[i].Cllctd) {
                foundBubble = true;
                airbubbles[i].Cllctd = true;

                std::cout << "Air bubble absorbed! Oxygen +30.\n";

                SubOxy += 30;

                if (SubOxy > 100)
                    SubOxy = 100;
            }
        }
        if (!foundBubble) {
            std::cout << "No Air bubbles nearby.\n";
        }
}

void moveControls(SubCoord& CurPos, int& SubOxy) {
    char move;

    int NewX = CurPos.getX();
    int NewY = CurPos.getY();

    std::cout << "Enter your move (W/A/S/D) or inspect (I): ";
    std::cin >> move;

    switch (move) {
        case 'W':
        case 'w':
            NewY--;
            break;

        case 'A':
        case 'a':
            NewX--;
            break;

        case 'S':
        case 's':
            NewY++;
            break;

        case 'D':
        case 'd':
            NewX++;
            break;

        case 'I':
        case 'i':
            Inspect(CurPos, SubOxy);
            SubOxy -= 5;
            if (SubOxy<0){
                SubOxy=0;
            }
            return;

        default:
            std::cout << "Invalid move. Please enter W, A, S, D, or I.\n";
            return;
    }

    // Check grid boundaries
    if (NewX < 0 || NewX >= GridSize || NewY < 0 || NewY >= GridSize) {
    
        if (NewY < 0 && CurPos.getY() == 0) {
            std::cout << "You are already at the surface!\n";
        }
        else {
            std::cout << "You can't move outside the grid!\n";
        }
    return;
    }
    

    // Check locked doors
    for (int i = 0; i < DoorCnt; i++) {
        if (doors[i].x == NewX &&
            doors[i].y == NewY &&
            doors[i].isLckd) {

            std::cout << "This door is locked!\n";
            return;
        }
    }

    // Move submarine
    CurPos.setX(NewX);
    CurPos.setY(NewY);

    SubOxy -= 5;
    if (SubOxy<0){
        SubOxy=0;
    }
}

void spawnTrea(){ // Function to randomly spawn treasure across the grid
    int x,y;

    for (int i = 0; i < TreaCnt; i++) {
        do {
            x = rand() % GridSize;
            y = rand() % GridSize;
        } while (!NoOvrLap(x, y,i,0,0,0,0));

        treasures[i].x = x;
        treasures[i].y = y;

        treasures[i].Cllctd = false;

        int TreaType = rand() % 5; //randomizes treasure type 

        
        switch (TreaType) {
    case 0:
        treasures[i].type = 's';
        break;
    case 1:
        treasures[i].type = 'D';
        break;
    case 2:
        treasures[i].type = 'P';
        break;
    case 3:
        treasures[i].type = 'G';
        break;
    case 4:
        treasures[i].type = 'T';
        break;
}
    }
}

void spawnUnknwn(){ // Function to randomly spawn unknown items across the grid
   int x, y;

    for (int i = 0; i < UnknwnCnt; i++) {
        do {
            x = rand() % GridSize;
            y = rand() % GridSize;
        } while (!NoOvrLap(x, y, TreaCnt, i, 0, 0, 0));

        unknowns[i].x = x;
        unknowns[i].y = y;
        unknowns[i].type = '?';
        unknowns[i].Inspctd = false;
    }
}

void SpawnDoor(){ //function to spawn Locked doors and opened pathways
    int x, y;

    for (int i = 0; i < DoorCnt; i++) {
        do {
            x = rand() % GridSize;
            y = rand() % GridSize;
        } while (!NoOvrLap(x, y, TreaCnt,
                           UnknwnCnt, i, 0, 0));

        doors[i].x = x;
        doors[i].y = y;
        doors[i].type = LckdDoor;
        doors[i].isLckd = true;
        doors[i].Entered = false;
    }
}

void SpawnPthway(){
    for (int i = 0; i < DoorCnt; i++) {
        pathways[i].x = doors[i].x;
        pathways[i].y = doors[i].y;
        pathways[i].type = LckdDoor;

    }
}

void SpawnLvr(){//function to spawn a Lever to unlock the doors
    int x, y;

    for (int i = 0; i < LvrCnt; i++) {
        do {
            x = rand() % GridSize;
            y = rand() % GridSize;
        } while (!NoOvrLap(x, y, TreaCnt,
                           UnknwnCnt, DoorCnt, i, 0));

        lever[i].x = x;
        lever[i].y = y;
        lever[i].type = DoorLvr;
        lever[i].LvrUsd = false;
    }
}

void SpawnAirBble(){//Function to spawn Air bubbles
   int x, y;

    for (int i = 0; i < BbleCnt; i++) {
        do {
            x = rand() % GridSize;
            y = rand() % GridSize;
        } while (!NoOvrLap(x, y, TreaCnt,
                           UnknwnCnt, DoorCnt,
                           LvrCnt, i));

        airbubbles[i].x = x;
        airbubbles[i].y = y;
        airbubbles[i].type = AirBble;
        airbubbles[i].Cllctd = false;
    }
}

void CllctTrea(const SubCoord& CurPos) { // Function to check if the player has collected any treasure
    for (int i = 0; i < TreaCnt; i++) {
        if (!treasures[i].Cllctd && treasures[i].x == CurPos.getX() && treasures[i].y == CurPos.getY()) {
            treasures[i].Cllctd = true; // Mark as collected
        switch (treasures[i].type) {
            case 's':
                TreaColl[0]++;
                
                std::cout << "You collected a Shell!\n";
                break;

            case 'D':
                TreaColl[1]++;
                std::cout << "You collected Doubloons!\n";
                break;

            case 'P':
                TreaColl[2]++;
                std::cout << "You collected a Pearl!\n";
                break;

            case 'G':
                TreaColl[3]++;
                std::cout << "You collected a Gem!\n";
                break;

            case 'T':
                TreaColl[4]++;
                std::cout << "You collected a Treasure Chest!\n";
                break;
        }
        }
    }
}

bool NoOvrLap(int x, int y,int Trea_Cnt,int Unknown_Cnt,int Door_Cnt,int Lever_Cnt, int Bubble_Cnt) {//preventing Overlapping Items
    if (x == 5 && y == 1) {
    return false;
    }

    for (int i = 0; i < Trea_Cnt; i++) {
        if (treasures[i].x == x &&
            treasures[i].y == y) {
            return false;
        }
    }
    
    for (int i = 0; i < Unknown_Cnt; i++) {
        if (unknowns[i].x == x &&
            unknowns[i].y == y) {
            return false;
        }
    }

    for (int i = 0; i < Door_Cnt; i++) {
        if (doors[i].x == x &&
            doors[i].y == y) {
            return false;
        }
    }
    for (int i = 0; i < Lever_Cnt; i++) {
        if (lever[i].x == x &&
            lever[i].y == y) {
            return false;
        }
    }
    for (int i = 0; i < Bubble_Cnt; i++) {
        if (airbubbles[i].x == x &&
            airbubbles[i].y == y) {
            return false;
        }
    }
    return true;
}

class SubArea{ //abstract class for the subareas
    protected:
    int SubAreaX;
    int SubAreaY;
    int SubADoor;
    int SubATreaCnt;
    public:
    SubArea(int x, int y)
        : SubAreaX(x), SubAreaY(y),
          SubADoor(0), SubATreaCnt(0) {}

    virtual void Enter() = 0;
    virtual void Subgrid() = 0;
    virtual void SpawnSubArea() = 0;
    int getSubAreaX() const {
        return SubAreaX;
    }

    int getSubAreaY() const {
        return SubAreaY;
    }
    

    virtual ~SubArea() = default;
};

class Cave : public SubArea { // cave subarea
    private:
    char    grid[8][7];
    public:
    Cave() :  SubArea(7,8)  {

    for (int y = 0; y < SubAreaY; y++) {
            for (int x = 0; x < SubAreaX; x++) {
                grid[y][x] = EmpCell;
            }
        }
    }
    void Enter() override {
        std::cout << "You entered the Cave!\n";
    }  
    void Subgrid() override{ //grid for Subarea
        for (int y = 0; y < SubAreaY; y++) {
            for (int x = 0; x < SubAreaX; x++) {
                std::cout << grid[y][x] << " ";
            }
            std::cout << '\n';
        }
    }
    void SpawnSubArea() override {
    for (int y = 0; y < SubAreaY; y++) {
        for (int x = 0; x < SubAreaX; x++) {
            grid[y][x] = EmpCell;
            }
        }
    }
};

class Ruins : public SubArea { // cave subarea
    private:
    char grid[9][8];
    public:
    Ruins() :  SubArea(8,9) {

    for (int y = 0; y < SubAreaY; y++) {
        for (int x = 0; x < SubAreaX; x++) {
            grid[y][x] = EmpCell;
        }
    }
}
    void Enter() override {
        std::cout << "You entered the Ruins!\n";
    }

   void Subgrid() override { //grid for Subarea
    for (int y = 0; y < SubAreaY; y++) {
        for (int x = 0; x < SubAreaX; x++) {
            std::cout << grid[y][x] << " ";
        }
        std::cout << '\n';
    }
    }
    void SpawnSubArea() override {
        for (int y = 0; y < SubAreaY; y++) {
            for (int x = 0; x < SubAreaX; x++) {
                grid[y][x] = EmpCell;
                }
            }
        }
};

class Shipwreck : public SubArea { // cave subarea
    private:
    char grid[5][8];
    public:
    Shipwreck() :  SubArea(8,5) {
        for (int y = 0; y < SubAreaY; y++) {
            for (int x = 0; x < SubAreaX; x++) {
                grid[y][x] = EmpCell;
            }
        }
    }
    void Enter() override {
        std::cout << "You entered the Shipwreck!\n";
    }
    void Subgrid() override { //grid for Subarea
    for (int y = 0; y < SubAreaY; y++) {
        for (int x = 0; x < SubAreaX; x++) {
            std::cout << grid[y][x] << " ";
        }
        std::cout << '\n';
    }
    }
    void SpawnSubArea() override {
        for (int y = 0; y < SubAreaY; y++) {
            for (int x = 0; x < SubAreaX; x++) {
                grid[y][x] = EmpCell;
                }
            }
        }
};

//SubArea objects
Cave cave;
Ruins ruins;
Shipwreck shipwreck;

void EnterSubArea(const SubCoord& CurPos){//function to access Subareas
     for (int i = 0; i < DoorCnt; i++) {

        if (doors[i].x == CurPos.getX() &&
            doors[i].y == CurPos.getY() &&
            !doors[i].isLckd && !doors[i].Entered) {

            doors[i].Entered = true;

            if (doors[i].y >= 8) {
                ruins.Enter();
                ruins.Subgrid();
            }
            else if (doors[i].x <= 5) {
                cave.Enter();
                cave.Subgrid();
            }
            else {
                shipwreck.Enter();
                shipwreck.Subgrid();
            }

            return;
        }
    
    }
}

bool PlayAgain() {
    char choice;

    std::cout << "Do you want to go down again? (y/n): ";
    std::cin >> choice;

    while (choice != 'y' && choice != 'Y' &&
           choice != 'n' && choice != 'N') {

        std::cout << "Invalid input. Please enter Y or N: ";
        std::cin >> choice;
    }

    if (choice == 'y' || choice == 'Y') {
        std::cout << "Back down to the depths!\n";
        return true;
    }

    std::cout << "Thanks for playing!\n";
    return false;
}
int main() {
    std::cout << "Welcome to Deep Dive!" << std::endl;
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
    int TotEarn = 0; // Total earnings across all runs    
    bool PlyAgain = true;
    while (PlyAgain) {
        for (int i = 0; i < 5; i++) { //reset treasure
            TreaColl[i] = 0;
        }
        for (int i = 0; i < 3; i++) {//Reset Unknowns
            UnknwnInspt[i] = 0;
        }
        for (int i = 0; i < DoorCnt; i++){//Reset doors
            doors[i].Entered = false;
            doors[i].isLckd = true;
            doors[i].type = LckdDoor;
        }
        for (int i = 0; i < LvrCnt; i++){//Reset Lever
            lever[i].LvrUsd = false;
        }
        for (int i = 0; i < BbleCnt; i++){//Reset Airbubbles
            airbubbles[i].Cllctd = false;
        }
        spawnTrea(); // Spawn random treasure across the grid at the start of the game
        spawnUnknwn(); // Spawn random unknown items across the grid at the start of the game
        SpawnDoor(); // Spawn 3 random doors across the grid
        SpawnPthway();// replaces doors with pathways
        SpawnLvr();// Spawns a Lever at a random point on the grid
        SpawnAirBble();// Spawns Air bubbles randomly across the grid
        //intiailized New Run stats
        int RunEarn = 0; //earnings made this run
       
        //initialized coordinates
        SubCoord CurPos(5, 1); // Starting position of the submarine (x:5,y:1)
        CllctTrea(CurPos);
        //initialize Stats
        std::cout << "Coordinates :" << " X: " << CurPos.getX() << " Y: " << CurPos.getY() << std::endl;
        int SubOxy = 100; // initialize oxygen level
  
        //display initial grid
        DisplayCam(CurPos);
        //display stats
        std::cout << "Coordinates :" << " X: " << CurPos.getX() << " Y: " << CurPos.getY() << std::endl;
        std::cout << "Oxygen Level: " << SubOxy << std::endl;
        std::cout << "Treasure Collected: Shells: " << TreaColl[0] << ", Doubloons: " << TreaColl[1] << ", Pearls: " << TreaColl[2] << ", Gems: " << TreaColl[3] << ", Treasure Chests: " << TreaColl[4] << std::endl;
    
        //game loop
        while (SubOxy > 0) {
        //display stats
        std::cout << "Coordinates :" << " X: " << CurPos.getX() << " Y: " << CurPos.getY() << std::endl;
        std::cout << "Oxygen Level: " << SubOxy << std::endl;
        std::cout << "Treasure Collected: Shells: " << TreaColl[0] << ", Doubloons: " << TreaColl[1] << ", Pearls: " << TreaColl[2] << ", Gems: " << TreaColl[3] << ", Treasure Chests: " << TreaColl[4] << std::endl;
    
        //move controls
        moveControls(CurPos,SubOxy);
        
        if (CurPos.getY() == 0) { // Check whether the player reached the surface
            break;
        }

        if (SubOxy <= 0) {  // Check oxygen
            break;
        }
        CllctTrea(CurPos); //check for treasure collection
        
        DisplayCam(CurPos); //update camera after move
        
        EnterSubArea(CurPos);// Enter SubArea
        }

        //display stats
        std::cout << "Coordinates :" << " X: " << CurPos.getX() << " Y: " << CurPos.getY() << std::endl;
        std::cout << "Oxygen Level: " << SubOxy << std::endl;
        std::cout << "Treasure Collected: Shells: " << TreaColl[0] << ", Doubloons: " << TreaColl[1] << ", Pearls: " << TreaColl[2] << ", Gems: " << TreaColl[3] << ", Treasure Chests: " << TreaColl[4] << std::endl;

        //initialize end state of game
        if (CurPos.getY() == 0) {
            std::cout << "You have reached the surface!\n";

            RunEarn = (TreaColl[0] * 5) +
                    (TreaColl[1] * 10) +
                    (TreaColl[2] * 20) +
                    (TreaColl[3] * 50) +
                    (TreaColl[4] * 100);

            TotEarn += RunEarn;

            std::cout << "You have earned: " << RunEarn
                    << " gold coins this run!\n";

            PlyAgain = PlayAgain();
        }
        else if (SubOxy <= 0) {
            std::cout << "You ran out of oxygen, returning to the surface!\n";

            RunEarn = 0;

            std::cout << "You have earned: " << RunEarn
                    << " gold coins this run!\n";

            PlyAgain = PlayAgain();
        }
    }
}
