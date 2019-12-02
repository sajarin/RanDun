#include <iostream>
#include <vector>
#include <ctime> 
#include <cstdlib>
#include "sys/time.h"
#include <time.h>

struct cell {
    int value = 8; 
    bool transform = false;     
};

const int MAX_WIDTH = 25; 
const int MAX_HEIGHT = 50; 
void buildDungeon(std::vector<std::vector<cell> > &level); 

void printDungeon(std::vector<std::vector<cell>> &level);
void generateDungeon(int generation, std::vector<std::vector<cell>> &level); 

int main() {
    
    int generation = 2;
    std::vector<std::vector<cell> > level(MAX_WIDTH, std::vector<cell> (MAX_HEIGHT));

    timeval t1; 
    gettimeofday(&t1, NULL); 
    srand(t1.tv_usec * t1.tv_sec); 

    buildDungeon(level); 
    generateDungeon(generation, level); 
    printDungeon(level);     
}

void assignRandom(int i, int j, std::vector<std::vector<cell>> &level) {
    int assignment = (rand() % 2) + 1; //1 or 0
    if(assignment == 2) {
        level[i][j].value = 1;  
    }
    else {
        level[i][j].value = 0; 
    }
}

void buildDungeon(std::vector<std::vector<cell>> &level) {
    for(size_t i = 0; i < level.size(); i++) {
        for(size_t j = 0; j < level[i].size(); j++) {
            assignRandom(i, j, level); 
        }        
    }    
}

void printDungeon(std::vector<std::vector<cell>> &level) {
    for(size_t i = 0; i < level.size(); i++) {
        for(size_t j = 0; j < level[i].size(); j++) {
            if(level[i][j].value == 0){
                std::cout << '#'; 
            }
            else{
                std::cout << '.';
            }
        }
        std::cout << std::endl; 
    }        
}
int checkAdjacent(int x, int y, std::vector<std::vector<cell>> &level) {
    int wallCounter = 0; 
    static int checks[8][2] = {{-1,0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}};
    for(int i = 0; i < 8; ++i) {
        int ti = x + checks[i][0]; 
        int tj = y + checks[i][1]; 
        if (ti < 0 || ti >= MAX_WIDTH || tj < 0 || tj >= MAX_HEIGHT) {
          continue;
        }
        if(level[ti][tj].value == 1){
            wallCounter++; 
        }
    }
    return wallCounter;    

}
void evolveDungeon(std::vector<std::vector<cell>> &level) {
    for(int i = 0; i < MAX_WIDTH; i++) {
        for(int j = 0; j < MAX_HEIGHT; j++) {
            if(level[i][j].transform == true) {
                if(level[i][j].value == 0)
                    level[i][j].value = 1; 
            }
        }
    }
}
void generateDungeon(int generation, std::vector<std::vector<cell>> &level) {
    while(generation > 0) {
        for(size_t i = 0; i < level.size(); i++) {
            for(size_t j = 0; j < level[i].size(); j++) {
                int numAdjacent = checkAdjacent(i, j, level);

                if(numAdjacent > 4) {
                    level[i][j].transform = true; 
                }            
            }
        }
    evolveDungeon(level); 
    generation--; 
    } 
}
