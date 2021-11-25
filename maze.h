//
// Created by mikeb on 11/22/2021.
//

#ifndef PROJ4_MAZE_H
#define PROJ4_MAZE_H
#include <list>
#include <random>
#include <set>
#include <stack>
#include <vector>

int getRandInt(int leftLim, int rightLim) {
    std::random_device seed;
    std::mt19937 randomGenerator{seed()};
    std::uniform_int_distribution<int> distribution{leftLim, static_cast<int>(rightLim)};
    return distribution(randomGenerator);
}

class Maze {

    const int mazeSize;
    const int numOfRooms = mazeSize * mazeSize;

    std::set<int> visitedRooms;
    std::stack<int> workToDo;

    std::list<std::pair<int,int>> edgeList;
    //std::list<int> *edgeList = new std::list<int>[numOfRooms];


    void breakRandomWall(int &currentRoom) {
        int randInt;
        std::shared_ptr<int> selectedRoom = nullptr;

        while (selectedRoom == nullptr) {
            randInt = getRandInt(0, 3);
            if (randInt == 0)
                selectedRoom = getNorthRoomate(currentRoom);
            else if (randInt == 1)
                selectedRoom = getSouthRoomate(currentRoom);
            else if (randInt == 2)
                selectedRoom = getWestRoomate(currentRoom);
            else if (randInt == 3)
                selectedRoom = getEastRoomate(currentRoom);
        }

        auto *edge = new std::pair<int, int>(currentRoom, *selectedRoom);
        edgeList.push_back(*edge);
        //edgeList[currentRoom].push_back(*selectedRoom);
        edge = nullptr;
    }

    void addRoomatesToStack(int &currentRoom) {
        auto nRoom = getNorthRoomate(currentRoom);
        auto sRoom = getSouthRoomate(currentRoom);
        auto wRoom = getWestRoomate(currentRoom);
        auto eRoom = getEastRoomate(currentRoom);

        if (nRoom != nullptr)
            pushRoomToStack(*nRoom);
        if (sRoom != nullptr)
            pushRoomToStack(*sRoom);
        if (wRoom != nullptr)
            pushRoomToStack(*wRoom);
        if (eRoom != nullptr)
            pushRoomToStack(*eRoom);
    }

    void pushRoomToStack(int roomNum) {
        if (visitedRooms.find(roomNum) == visitedRooms.end()) {
            workToDo.push(roomNum);
        }
    }

    std::shared_ptr<int> getNorthRoomate(int &currentRoom) {
        int nRoom = currentRoom + mazeSize;
        if (nRoom < numOfRooms - 1)
            return std::make_shared<int>(nRoom);
        else
            return nullptr;
    }

    std::shared_ptr<int> getSouthRoomate(int &currentRoom) {
        int sRoom = currentRoom - mazeSize;
        if (sRoom >= 0)
            return std::make_shared<int>(sRoom);
        else
            return nullptr;
    }

    std::shared_ptr<int> getWestRoomate(int &currentRoom) {
        if (currentRoom % mazeSize == 0) {
            return nullptr;
        } else
            return std::make_shared<int>(currentRoom - 1);
    }

    std::shared_ptr<int> getEastRoomate(int &currentRoom) {
        if ((currentRoom + 1) % mazeSize == 0)
            return nullptr;
        else
            return std::make_shared<int>(currentRoom + 1);
    }
    int getRowNum(int roomNum){
        if(roomNum == 0)
            return 0;
        else
            return roomNum / mazeSize;
    }

    int getColNum(int roomNum){
        int colNum;
        colNum = (roomNum % mazeSize);
        if(colNum == mazeSize) colNum = 0;

        return colNum;
    }

    int getLiteralRowNum(int r){
        int litRowNum = (mazeSize + mazeSize/2 + 1) - r*2;
        return litRowNum;
    }

    int getLiteralColNum(int c){
        int litColNum = c + mazeSize - (mazeSize- c - 1);
        return litColNum;
    }
public:

    void generateMaze() {
        workToDo.push(0);
        while (!workToDo.empty()) {
            int currentRoom = workToDo.top();
            workToDo.pop();
            if (visitedRooms.find(currentRoom) == visitedRooms.end()) {
                addRoomatesToStack(currentRoom);
                breakRandomWall(currentRoom);
                visitedRooms.insert(currentRoom);
            }
        }
    }

    void printAllEdges() {

        std::cout << "edge list " << std::endl;
        for (std::pair<int,int> room: edgeList) {
            std::cout << room.first << " " << room.second << std::endl;
        }
        std::cout << std::endl;

    }

    void printMaze() {

        //TODO create 2d array using vectors or array library i guess
        int gridSize = (mazeSize << 1) + 1;
        //char *mazeArray = new char[mazeSize];

        std::vector<std::vector<char>> mazeArray(gridSize, std::vector<char> (gridSize));

        int roomCounter = gridSize;
        for (int row = 0; row < gridSize; row++) {
            bool isRowOdd = row % 2;
            for (int col = 0; col < gridSize; col++) {
                if (!isRowOdd)
                    mazeArray[row][col] = 'x';
                else {
                    if (col % 2) {
                        mazeArray[row][col] = '0'; //+ roomCounter;
                        if (roomCounter % mazeSize == 0)
                            roomCounter -= mazeSize * 2 - 1;
                        else
                            roomCounter++;

                    } else
                        mazeArray[row][col] = 'x';
                }

            }
        }

        for(std::pair<int,int> edge : edgeList){
            int r = getRowNum(edge.first);
            int c = getColNum(edge.first);

            r = getLiteralRowNum(r);
            c = getLiteralColNum(c);

            //TODO: need to create holes in the walls
            if(edge.second == edge.first+1);

        }

        int roomNum = 11;

        int r = getRowNum(roomNum);
        int c = getColNum(roomNum);

        r = getLiteralRowNum(r);
        c = getLiteralColNum(c);

        mazeArray[r][c] = '#';




        for (int row = 0; row < gridSize; row++) {
            for (int col = 0; col < gridSize; col++) {
                std::cout << mazeArray[row][col];
            }
            std::cout << std::endl;
        }

    }

    explicit Maze(int size) : mazeSize(size) {};
};

#endif //PROJ4_MAZE_H
