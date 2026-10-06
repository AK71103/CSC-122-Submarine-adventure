//Submarine Adventure portfolio 1
//Alexander w Kazantzis
//9-23-26

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

//Grid Constants
const int GridSize = 10;
const char EmpCell = '.';
const char PlyrSub = 'S';

class SubCoord{
private:    
    int CoordX; //0
    int CoordY; //1
    std::vector<char> GridCells; //game grid representation.
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
int TreaColl[5] = { 0,0,0,0,0 }; //Treasure Collected (Shells(s),Doubloons(D),Pearls(P),Gems(G),Treasure Chests(T))

const int TreaCnt = 9;
Treasure treasures[TreaCnt];

void displayGrid(const SubCoord& CurPos) { //function to display the grid
    for (int i = 0; i < GridSize; i++) {
        for (int j = 0; j < GridSize; j++) {

            if (i == CurPos.getY() && j == CurPos.getX()) {
                std::cout << PlyrSub << " ";
            }
            else {
                bool foundTreasure = false;

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

void moveControls(SubCoord& CurPos) {//move controls (W,A,S,D)
    std::cout << "Enter your move (W/A/S/D): ";
    char move;
    std::cin >> move;
    switch (move) {
        case 'W': 
        case 'w':
                 if (CurPos.getY() > 0) {
                CurPos.setY(CurPos.getY() - 1);
            }
            else {
                std::cout << "You have reached the surface!\n";
            }
            return;
        case 'A':
        case 'a':
           if (CurPos.getX() > 0) {
                CurPos.setX(CurPos.getX() - 1);
            }
            else {
                std::cout << "You can't move outside the grid!\n";
            }
            return;
        case 'S':
        case 's':
            if (CurPos.getY() < GridSize - 1) {
                CurPos.setY(CurPos.getY() + 1);
            }
            else {
                std::cout << "You can't move outside the grid!\n";
            }
            return;
        case 'D':
        case 'd':
            if (CurPos.getX() < GridSize - 1) {
                CurPos.setX(CurPos.getX() + 1);
            }
            else {
                std::cout << "You can't move outside the grid!\n";
            }
            return;
        default:
            std::cout << "Invalid move. Please enter W, A, S, or D." << std::endl;
            break;
    }
}

void spawnTrea() { // Function to randomly spawn treasure across the grid

    for (int i = 0; i < 9; i++) {
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
    spawnTrea(); // Spawn random treasure across the grid at the start of the game
    

    //initialized coordinates
    SubCoord CurPos(5, 1); // Starting position of the submarine (x:5,y:1)
    CllctTrea(CurPos);
    //initialize Stats
    std::cout << "Coordinates :" << " X: " << CurPos.getX() << " Y: " << CurPos.getY() << std::endl;
    int SubOxy = 100; // initialize oxygen level
  
    //display initial grid
    displayGrid(CurPos);
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
    moveControls(CurPos);
    //check for treasure collection
    CllctTrea(CurPos);
    SubOxy -= 5; //decrease oxygen by 5 for each move
    //update grid after move
    displayGrid(CurPos);
    //display stats
     std::cout << "Coordinates :" << " X: " << CurPos.getX() << " Y: " << CurPos.getY() << std::endl;
    std::cout << "Oxygen Level: " << SubOxy << std::endl;
    std::cout << "Treasure Collected: Shells: " << TreaColl[0] << ", Doubloons: " << TreaColl[1] << ", Pearls: " << TreaColl[2] << ", Gems: " << TreaColl[3] << ", Treasure Chests: " << TreaColl[4] << std::endl;

    //initialize end state of game
    if (CurPos.getY() <1) { 
            std::cout << "You have reached the surface!" << std::endl;
            std::cout << "You have collected the following treasures: Shells: " << TreaColl[0] << ", Doubloons: " << TreaColl[1] << ", Pearls: " << TreaColl[2] << ", Gems: " << TreaColl[3] << ", Treasure Chests: " << TreaColl[4] << std::endl;

        std::cout << "Do you want to Go down again? (y/n): "; //ask the user if they want to run the program again
        char choice;
        std::cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            std::cout<< "Back down to the depths!" << std::endl;
            main(); // Call main() again to run the program again
        }
        else {
            std::cout << "Thanks for playing!" << std::endl;
        }
        return 0;
    }
}
}
    }
}
}
