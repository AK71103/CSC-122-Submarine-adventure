//Submarine Adventure portfolio 1
//Alexander w Kazantzis
//9-23-26

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
//Grid Constants
const int GridSize = 10; //grid size 10x10
const char EmpCell = '.';
const char PlyrSub = 'S';
const char Unknwn = '?';

class SubCoord{
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

int TreaColl[5] = {0,0,0,0,0}; //Treasure Collected (Shells(s),Doubloons(D),Pearls(P),Gems(G),Treasure Chests(T))
int UnknwnInspt[3]= {0,0,0}; //Unknown Items Inspected (fish(f),clam(c),reef(r)))
const int TreaCnt = 9;
const int UnknwnCnt = 5;
Treasure treasures[TreaCnt];
Unknown unknowns[UnknwnCnt];

void displayGrid(const SubCoord& CurPos) { //function to display the grid
    bool foundTreasure = false;
    bool foundItem = false;
    for (int i = 0; i < GridSize; i++) {
        for (int j = 0; j < GridSize; j++) {

            if (i == CurPos.getY() && j == CurPos.getX()) {
                std::cout << PlyrSub << " ";
            }
            else {
                bool foundTreasure = false;
                bool foundItem = false;
                for (int k = 0; k < TreaCnt; k++) {
                    if (!treasures[k].Cllctd &&
                        treasures[k].x == j &&
                        treasures[k].y == i) {

                        std::cout << treasures[k].type << " ";
                        foundTreasure = true;
                        break;
                    }
                }

                if (!foundTreasure) {
                    std::cout << EmpCell << " ";
                }
            }
        }

        std::cout << std::endl;
    }
}
void DisplayCam(const SubCoord& CurPos) { // function to display 3x3 view
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
                for (int k = 0; k < TreaCnt; k++) { // Check for treasure
                    if (!treasures[k].Cllctd &&
                        treasures[k].x == x &&
                        treasures[k].y == y) {
                        std::cout << treasures[k].type << " ";
                        foundItem = true;
                        break;
                    }
                }
                if (!foundItem) { // Check for unknown item
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
                if (!foundItem) { // Empty cell
                    std::cout << EmpCell << " ";
                }
            }
            std::cout << std::endl;
        }
    }

void Inspect(const SubCoord& CurPos, int& SubOxy) {
    bool foundUnknown = false;

    for (int i = 0; i < UnknwnCnt; i++) {
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
            }

            break;
        }
    }
    if (!foundUnknown) {
        std::cout << "No unknown items nearby.\n";
    }
}
void moveControls( SubCoord& CurPos, int& SubOxy){//move controls (W,A,S,D,I)
    char move;
    
        std::cout << "Enter your move (W/A/S/D) or inspect (I): ";
        std::cin >> move;
        // input Validation Check
         if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Invalid input. Please enter W, A, S, or D or inspect(I).\n";
        return;
    }
    switch (move) {
        case 'W': 
        case 'w':
                 if (CurPos.getY() > 0) {
                CurPos.setY(CurPos.getY() - 1);
                SubOxy -= 5; //decrease oxygen by 5 
            }
            else {
                std::cout << "You have reached the surface!\n";
            }
            return;
        case 'A':
        case 'a':
           if (CurPos.getX() > 0) {
                CurPos.setX(CurPos.getX() - 1);
                SubOxy -= 5; //decrease oxygen by 5 
            }
            else {
                std::cout << "You can't move outside the grid!\n";
                
            }
            return;
        case 'S':
        case 's':
            if (CurPos.getY() < GridSize - 1) {
                CurPos.setY(CurPos.getY() + 1);
                SubOxy -= 5; //decrease oxygen by 5 
            }
            else {
                std::cout << "You can't move outside the grid!\n";
                
            }
            return;
        case 'D':
        case 'd':
            if (CurPos.getX() < GridSize - 1) {
                CurPos.setX(CurPos.getX() + 1);
                SubOxy -= 5; //decrease oxygen by 5 
            }
            else {
                std::cout << "You can't move outside the grid!\n";
                
            }
            return;
        case 'I':
        case 'i':
            Inspect(CurPos, SubOxy);
            return;
        default:
            std::cout << "Invalid move. Please enter W, A, S, D, or I." << std::endl;
            break;
    }
}


void spawnTrea(){ // Function to randomly spawn treasure across the grid

    for (int i = 0; i < TreaCnt; i++) {
        treasures[i].x = rand() % GridSize;
        treasures[i].y = rand() % GridSize;
        int TreaType = rand() % 5; // Randomly select treasure type (0-4)
        treasures[i].Cllctd = false; // Initialize as not collected
        
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
    for (int i = 0; i < UnknwnCnt; i++) {
        unknowns[i].x = rand() % GridSize;
        unknowns[i].y = rand() % GridSize;
        unknowns[i].type = '?'; // Unknown item type
        unknowns[i].Inspctd = false; // Initialize as not inspected
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
int main() {
    std::cout << "Welcome to Deep Dive!" << std::endl;
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
    int TotEarn = 0; // Total earnings across all runs    
    bool PlyAgain = true;
    while (PlyAgain) {
        for (int i = 0; i < 5; i++) { //reset treasure
            TreaColl[i] = 0;
        }
        for (int i = 0; i < 3; i++) {
            UnknwnInspt[i] = 0;
        }
        
        spawnTrea(); // Spawn random treasure across the grid at the start of the game
        spawnUnknwn(); // Spawn random unknown items across the grid at the start of the game
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
        CllctTrea(CurPos); //check for treasure collection
        
        DisplayCam(CurPos); //update camera after move
        }
        //display stats
        std::cout << "Coordinates :" << " X: " << CurPos.getX() << " Y: " << CurPos.getY() << std::endl;
        std::cout << "Oxygen Level: " << SubOxy << std::endl;
        std::cout << "Treasure Collected: Shells: " << TreaColl[0] << ", Doubloons: " << TreaColl[1] << ", Pearls: " << TreaColl[2] << ", Gems: " << TreaColl[3] << ", Treasure Chests: " << TreaColl[4] << std::endl;

        //initialize end state of game
        if (CurPos.getY() ==0) { 
                std::cout << "You have reached the surface!" << std::endl;
                std::cout << "You have collected the following treasures: Shells: " << TreaColl[0] << ", Doubloons: " << TreaColl[1] << ", Pearls: " << TreaColl[2] << ", Gems: " << TreaColl[3] << ", Treasure Chests: " << TreaColl[4] << std::endl;
                RunEarn = (TreaColl[0] * 5) + (TreaColl[1] * 10) + (TreaColl[2] * 20) + (TreaColl[3] * 50) + (TreaColl[4] * 100); //calculate earnings for this run
                TotEarn += RunEarn; //Add this run's earnings to the total earnings
                std::cout << "You have earned: " << RunEarn << " gold coins this run!" << std::endl;

                std::cout << "Do you want to Go down again? (y/n): "; //ask the user if they want to run the program again
                char choice;
                std::cin >> choice;
                while(PlyAgain == true){
                if (choice == 'y' || choice == 'Y') {
                    std::cout<< "Back down to the depths!" << std::endl;
                    break;
                }
                else if (choice == 'n' || choice == 'N'){
                    std::cout << "Thanks for playing!" << std::endl;
                    std::cout << "Total Earnings: " << TotEarn << std::endl;
                    PlyAgain = false;
                    break;
                }
                
                else{
                    std::cout<< "Invalid input, please Enter Y or N!\n";
                    std::cin >> choice;
                }
        
        }
        }
        else if (SubOxy <= 0) {
                std::cout << "You ran out of oxygen, returning to the surface!" << std::endl;
                std::cout << "You have collected the following treasures: Shells: " << TreaColl[0] << ", Doubloons: " << TreaColl[1] << ", Pearls: " << TreaColl[2] << ", Gems: " << TreaColl[3] << ", Treasure Chests: " << TreaColl[4] << std::endl;
                        RunEarn = 0; //no earnings if the player runs out of oxygen
                        std::cout << "You have earned: " << RunEarn << " gold coins this run!" << std::endl;

                        std::cout << "Do you want to Go down again? (y/n): "; //ask the user if they want to run the program again
                        char choice;
                        std::cin >> choice;
                        while(PlyAgain == true){
                        if (choice == 'y' || choice == 'Y') {
                            std::cout<< "Back down to the depths!" << std::endl;
                            break;
                        }
                        else if (choice == 'n' || choice == 'N'){
                            std::cout << "Thanks for playing!" << std::endl;
                            std::cout << "Total Earnings: " << TotEarn << std::endl;
                            PlyAgain = false;
                            break;
                        }
                        
                        else {
                            std::cout << "Invalid input, please enter Y or N: ";
                            std::cin >> choice;
                        }


                        }
                    }
    }
    }
    

