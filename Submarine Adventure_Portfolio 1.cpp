//Submarine Adventure portfolio 1
//Alexander w Kazantzis
//9-23-26

#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <cmath>
#include <stdexcept>

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
//function to display the grid
void displayGrid(const SubCoord& CurPos) {
    for (int i = 0; i < GridSize; i++) {
        for (int j = 0; j < GridSize; j++) {
            if (i == CurPos.getY() && j == CurPos.getX()) {
                std::cout << PlyrSub << " ";
            } else {
                std::cout << EmpCell << " ";
            }
        }
        std::cout << std::endl;
    }
}

//move controls (W,A,S,D)
void moveControls(SubCoord& CurPos) {
    enum Coord {CoordX, CoordY};
    std::cout << "Enter your move (W/A/S/D): ";
    char move;
    std::cin >> move;
    switch (move) {
        case 'W': 
        case 'w':
            CurPos.setY(CurPos.getY() - 1); // Move up
            break;
        case 'A':
        case 'a':
            CurPos.setX(CurPos.getX() - 1); // Move left
            break;
        case 'S':
        case 's':
            CurPos.setY(CurPos.getY() + 1); // Move down
            break;
        case 'D':
        case 'd':
            CurPos.setX(CurPos.getX() + 1); // Move right
            break;
        default:
            std::cout << "Invalid move. Please enter W, A, S, or D." << std::endl;
            moveControls(CurPos); // Prompt again for valid input
            break;
    }
}
const int TreaColl[5] = { 0,0,0,0,0 }; //Treasure Collected (Shells(s),Doubloons(D),Pearls(P),Gems(G),Treasure Chests(T))

int main() {
    
    std::cout << "Welcome to Deep Dive!" << std::endl;
    //initialized coordinates
    SubCoord CurPos(5, 2); // Starting position of the submarine (x:5,y:2)
    
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
    std::cout<< "Enter your move (W/A/S/D): ";
    moveControls(CurPos);
    SubOxy -= 5; //decrease oxygen by 5 for each move
    //update grid after move
    displayGrid(CurPos);
    //display stats
     std::cout << "Coordinates :" << " X: " << CurPos.getX() << " Y: " << CurPos.getY() << std::endl;
    std::cout << "Oxygen Level: " << SubOxy << std::endl;
    std::cout << "Treasure Collected: Shells: " << TreaColl[0] << ", Doubloons: " << TreaColl[1] << ", Pearls: " << TreaColl[2] << ", Gems: " << TreaColl[3] << ", Treasure Chests: " << TreaColl[4] << std::endl;

    //initialize end state of game
    if (CurPos.getY() <1) { 
        bool SubSurface = true;
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