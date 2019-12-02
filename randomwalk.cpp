#include <iostream> 
#include <vector>
#include <ctime> 
#include <cstdlib>
#include "sys/time.h"
#include <time.h>

const size_t MAX_WIDTH = 25; 
const size_t MAX_HEIGHT = 50;

const size_t MAX_LENGTH = 10; //specifies the maximum length of a tunnel
size_t MAX_TUNNELS = 200; // specifies the maximum number of total tunnels created

std::vector<std::vector<char> > level(MAX_WIDTH, std::vector<char> (MAX_HEIGHT, '*')); //This 2d vector represents our map/level
char boundary = '#'; //global character for outer boundary

void buildDungeon(); 
void printDungeon(); 
void generateDungeon(); 
void tunnelPath(int &x, int &y, int length, int direction);

int main() {
    buildDungeon(); 
    generateDungeon(); 
    printDungeon();     
}
void buildDungeon() { //this function creates the borders of the dungeon
    for(size_t i = 0; i < MAX_WIDTH; i++){
        for(size_t j = 0; j < MAX_HEIGHT; j++) {
            if(i == 0 || i == MAX_WIDTH-1) { //if i is at the left and right borders
                level[i][j] = boundary; 
            }
            if(j == 0 || j == MAX_HEIGHT-1) { //if i is at the top and bottom borders
                level[i][j] = boundary; 
            }
        }
    }
}
void printDungeon() { //this function prints the dungeon
    for(size_t i = 0; i < MAX_WIDTH; i++){
        for(size_t j = 0; j < MAX_HEIGHT; j++){
            char tile = level[i][j]; 
            std::cout << tile; 
        }
        std::cout << std::endl; 
    }
}

void generateDungeon() {
    timeval t1;
    gettimeofday(&t1, NULL); //gets time (microseconds) from epoch 
    srand(t1.tv_usec * t1.tv_sec); //seeds srand with time, but using microseconds from epoch

    int rand_x = rand() % (MAX_WIDTH / 2 ) + (MAX_WIDTH/4); //pick a random starting point from 25% - 50%
    int rand_y = rand() % (MAX_HEIGHT / 2) + (MAX_HEIGHT/4);  
    while(MAX_TUNNELS > 0 ) {
        int rand_length = (rand() % MAX_LENGTH) + 1; //get a random tunnel length
        int direction = (rand() % 4) + 1;            //get a random cardinal direction 
        tunnelPath(rand_x, rand_y, rand_length, direction);  
        MAX_TUNNELS--; 
    }
}

void tunnelPath(int &x, int &y, int length, int direction) {
    level[x][y] = '.';
    switch(direction)
    {
        case 1: // direction = right
            while(length != 0 && level[x][y + 1] != boundary) { 
                level[x][y + 1] = '.'; 
                y++; 
                length--; 
            }
            break;
        case 2: //direction = left 
            while(length != 0 && level[x][y - 1] != boundary) { 
                level[x][y - 1] = '.'; 
                y--; 
                length--; 
            }
            break;
        case 3: //direction = up 
            while(length != 0 && level[x - 1][y] != boundary) { 
                level[x - 1][y] = '.'; 
                x--; 
                length--; 
            }
            break;
        case 4: //direction = down
            while(length != 0 && level[x + 1][y] != boundary) { 
                level[x + 1][y] = '.'; 
                x++; 
                length--; 
            }
            break;
    }
}
