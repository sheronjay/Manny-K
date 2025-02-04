#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <array>
#include <vector>
#include <algorithm>
#include "checkMaze.h"
#include "motorcontrol.h"
#include "turning.h"
#include <map>

using namespace std;

// Constants
const int MAZE_SIZE = 16;

// Global variables (since we're using functional approach)
pair<int, int> currentPos = {0, 0};
set<pair<int, int>> visited;
stack<pair<int, int>> backtrackStack;
int orient = 0; // 0: North, 1: East, 2: South, 3: West

// Arrays for maze state
unsigned char maze[MAZE_SIZE][MAZE_SIZE];
unsigned char walls[MAZE_SIZE][MAZE_SIZE] = {
    {12, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9},  //represents 1st column from bottom up
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {6, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3}
};

// Movement and direction constants
constexpr int directions[4][2] = {
    {0, 1},   // North
    {1, 0},   // East
    {0, -1},  // South
    {-1, 0}   // West
};

constexpr unsigned char wall_bits[4] = {1, 2, 4, 8}; // N, E, S, W

constexpr int direction_map[4][3][3] = {
    {{0, 1, 1}, {-1, 0, 8}, {1, 0, 2}},   // Facing North
    {{1, 0, 2}, {0, 1, 1}, {0, -1, 4}},   // Facing East
    {{0, -1, 4}, {1, 0, 2}, {-1, 0, 8}},  // Facing South
    {{-1, 0, 8}, {0, -1, 4}, {0, 1, 1}}   // Facing West
};

// Helper functions
void initializeMazeArray() {
    for (int i = 0; i < MAZE_SIZE; ++i) {
        fill(maze[i], maze[i] + MAZE_SIZE, 255);  // Using 255 as "infinity"
    }
}

bool isValidPosition(int x, int y) {
    return x >= 0 && x < MAZE_SIZE && y >= 0 && y < MAZE_SIZE;
}

void floodfill() {
    initializeMazeArray();
    queue<pair<int, int>> queue;

    // Define goals
    const array<pair<int, int>, 4> goals = {{
        {7, 7}, {7, 8}, {8, 7}, {8, 8}
    }};

    // Initialize goals
    for (const auto& goal : goals) {
        queue.push(goal);
        maze[goal.first][goal.second] = 0;
    }

    // BFS
    while (!queue.empty()) {
        auto [x, y] = queue.front();
        queue.pop();

        unsigned char current_distance = maze[x][y];

        for (int d = 0; d < 4; ++d) {
            int nx = x + directions[d][0];
            int ny = y + directions[d][1];

            if (isValidPosition(nx, ny) &&
                !(walls[x][y] & wall_bits[d]) && 
                maze[nx][ny] > current_distance + 1) {
                maze[nx][ny] = current_distance + 1;
                queue.push({nx, ny});
            }
        }
    }
}

void updateWalls() {
    int x = currentPos.first;
    int y = currentPos.second;

    if (wallLeft()) {
        walls[x][y] |= direction_map[orient][1][2];
    }
    if (wallFront()) {
        walls[x][y] |= direction_map[orient][0][2];
    }
    if (wallRight()) {
        walls[x][y] |= direction_map[orient][2][2];
    }
}

void algorithmSetup() {
    currentPos = {0, 0};
    orient = 0;
}

void moveToNextCell(const tuple<int, int, int>& next) {
    auto [nextX, nextY, direction] = next;
    
    if (visited.find({nextX, nextY}) == visited.end()) {
        backtrackStack.push(currentPos);
    }

    // +4 to make turn positive always
    int turn = (direction - orient + 4) % 4;

    if (turn == 1) {
        turnRight();
    } else if (turn == 2) {
        turnRight();
        turnRight();
    } else if (turn == 3) {
        turnLeft();
    }

    moveForward();
    orient = direction;
    currentPos = {nextX, nextY};
}

void algorithmLoop() {
    visited.insert(currentPos);
    updateWalls();
    floodfill();

    // Generate neighbors
    vector<tuple<int, int, int>> neighbors;
    tuple<int, int, int> nearestNeighbor = {-1, -1, -1};
    unsigned char minDistance = 255;  // Initialize to max value

    for (int d = 0; d < 4; ++d) {
        int nx = currentPos.first + directions[d][0];
        int ny = currentPos.second + directions[d][1];

        if (isValidPosition(nx, ny) &&
            !(walls[currentPos.first][currentPos.second] & wall_bits[d]) &&
            visited.find({nx, ny}) == visited.end()) {
            
            // Add neighbors
            neighbors.emplace_back(nx, ny, d);
            
            // Check if this neighbor has a shorter path to goal
            if (maze[nx][ny] < minDistance) {
                minDistance = maze[nx][ny];
                nearestNeighbor = {nx, ny, d};
            }
        }
    }

    if (get<0>(nearestNeighbor) != -1) {  // If we found a valid neighbor
        moveToNextCell(nearestNeighbor);
    } 
    
    else if (!backtrackStack.empty()) {
        // Backtracking
        turnLeft();
        turnLeft();
        moveForward();
        orient = (orient + 2) % 4;

        while (!backtrackStack.empty()) {
            auto [bx, by] = backtrackStack.top();
            bool hasUnvisitedNeighbors = false;

            // Check for unvisited neighbors
            for (int d = 0; d < 4; ++d) {
                int nx = bx + directions[d][0];
                int ny = by + directions[d][1];

                if (isValidPosition(nx, ny) &&
                    !(walls[bx][by] & wall_bits[d]) &&
                    visited.find({nx, ny}) == visited.end()) {
                    hasUnvisitedNeighbors = true;
                }
            }

            if (hasUnvisitedNeighbors) {
                currentPos = {bx, by};
                break;
            }

            backtrackStack.pop();

            if (!backtrackStack.empty()) {
                // Move to previous cell, by changing orientation
                auto [px, py] = backtrackStack.top();
                int dx = px - currentPos.first;
                int dy = py - currentPos.second;

                if (px == bx && py == by) {
                    continue;
                }

                map<pair<int, int>, int> directionMap = {
                    {{0, 1}, 0}, {{1, 0}, 1}, {{0, -1}, 2}, {{-1, 0}, 3}
                };

                int direction = directionMap[{dx, dy}];
                int turn = (direction - orient + 4) % 4;

                if (turn == 1) {
                    turnRight();
                } else if (turn == 2) {
                    turnRight();
                    turnRight();
                } else if (turn == 3) {
                    turnLeft();
                }

                moveForward();

                orient = direction;
                currentPos = {px, py};
            }
        }
    }
}