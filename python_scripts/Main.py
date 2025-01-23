import API
import sys
from collections import deque

# Wall north 1
# Wall east 2
# Wall south 4
# Wall west 8

# Remember along a row what we have is the vertical wall
# Along a colomn what we have is the horizontal wall
# Along a row we have the y coordinate, along a column we have the x coordinate
maze = [[float('inf') for _ in range(16)] for _ in range(16)]

walls = [[12, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9],
         [4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
         [4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
         [4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
         [4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
         [4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
         [4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
         [4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
         [4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
         [4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
         [4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
         [4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
         [4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
         [4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
         [4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
         [6, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3]]

directions = [
    (0, 1),  # North
    (1, 0),  # East
    (0, -1), # South
    (-1, 0)  # West
]

wall_bits = [1, 2, 4, 8]  # Corresponding to North, East, South, West


def floodfill():
    global maze, walls, directions, wall_bits
    maze = [[float('inf') for _ in range(16)] for _ in range(16)]
    queue = deque()  # Use deque for efficient pop from the left
    # Define goals and set their distances to 0
    goals = [(7, 7), (7, 8), (8, 7), (8, 8)]
    for goal in goals:
        queue.append(goal)
        maze[goal[0]][goal[1]] = 0

    while queue:
        x, y = queue.popleft()  # Efficient pop from left
        current_distance = maze[x][y]
        for d, (dx, dy) in enumerate(directions):
            nx, ny = x + dx, y + dy
            # Check bounds and walls
            if 0 <= nx < 16 and 0 <= ny < 16 and (walls[x][y] & wall_bits[d] == 0):
                if maze[nx][ny] > current_distance + 1:
                    maze[nx][ny] = current_distance + 1
                    queue.append((nx, ny))  # Only append if distance is updated
            

def log(string):
    sys.stderr.write("{}\n".format(string))
    sys.stderr.flush()

def updateMazeDistances():
    global maze
    for i in range(len(maze)):
        for j in range (len(maze[0])):
            API.setText(i, j, maze[i][j])


def getWalls(wallVal):
    wallDirs = []
    if wallVal & wall_bits[3]: wallDirs.append("w")
    if wallVal & wall_bits[2]: wallDirs.append("s")
    if wallVal & wall_bits[1]: wallDirs.append("e")
    if wallVal & wall_bits[0]: wallDirs.append("n")
    return wallDirs


def updateMazeWalls():
    global walls
    for i in range(len(walls)):
        for j in range(len(walls[0])):
            for dir in getWalls(walls[i][j]):
                API.setWall(i, j, dir)

def updateDistances(x, y):
    global walls, maze, directions, wall_bits
    stack = [(x, y)]  # Use a stack instead of a queue

    while stack:
        currentPos = stack.pop()  # Pop from the top of the stack
        cx, cy = currentPos
        currentDistance = maze[cx][cy]
        minDistance = float('inf')

        neighbors = []
        for d, (dx, dy) in enumerate(directions):
            nx, ny = cx + dx, cy + dy

            # Check bounds and walls
            if 0 <= nx < 16 and 0 <= ny < 16 and (walls[cx][cy] & wall_bits[d] == 0):
                minDistance = min(minDistance, maze[nx][ny])
                neighbors.append((nx, ny))

        # Update the distance if needed and process neighbors
        if currentDistance != minDistance + 1:
            maze[cx][cy] = minDistance + 1
            for neighbor in neighbors:
                stack.append(neighbor)  # Push neighbor onto the stack


def main():
    global walls, directions, maze

    # Initialization
    API.setColor(0, 0, "G")
    API.setText(0, 0, "START") 
    updateMazeWalls()
    floodfill()
    updateMazeDistances()


    # Starting point
    currentPos = (0, 0)
    visited = set()
    backtrackStack = []

    orient = 0  # 0: North, 1: East, 2: South, 3: West

    # Directions and corresponding wall checks
    # (dx, dy, wall_bit(direction))
    direction_mapping = {
        0: {"front": (0, 1, 1), "left": (-1, 0, 8), "right": (1, 0, 2)},  # Facing North
        1: {"front": (1, 0, 2), "left": (0, 1, 1), "right": (0, -1, 4)},  # Facing East
        2: {"front": (0, -1, 4), "left": (1, 0, 2), "right": (-1, 0, 8)}, # Facing South
        3: {"front": (-1, 0, 8), "left": (0, -1, 4), "right": (0, 1, 1)}  # Facing West
    }

    while len(visited) < 256:
        visited.add(currentPos)
        x, y = currentPos
        print(f"Mouse currently at {currentPos}, with orientation: {orient}")
        # Scan for walls and make record of walls
        print(f"Wall value before: {walls[x][y]}")
        if API.wallFront():
            walls[x][y] |= direction_mapping[orient]["front"][2]
        if API.wallLeft():
            walls[x][y] |= direction_mapping[orient]["left"][2]
        if API.wallRight():
            walls[x][y] |= direction_mapping[orient]["right"][2]
        
        print(f"Wall value after: {walls[x][y]}")

        updateMazeWalls()

        # Calculate new distances using floodfill
        # updateDistances(x, y)
        floodfill()

        updateMazeDistances()

        neighbors = []
        for d, (dx, dy) in  enumerate(directions):
            nx, ny = x + dx, y + dy
            if 0 <= nx < 16 and 0 <= ny < 16: # Inside the grid
                if walls[x][y] & wall_bits[d] == 0 and (nx, ny) not in visited: # No wall in this direction
                    # We will store coordinate, the distance to goal and the direction
                    neighbors.append((nx, ny, maze[nx][ny], d))

        neighbors.sort(key=lambda n: n[2])  # Sort by distance ( 3rd element in tuple )
        if neighbors:
            nextX, nextY, _, direction = neighbors[0]
            # Add current position to backtrack stack
            if (nextX, nextY) not in visited:
                backtrackStack.append((x, y))  # Push current position

            turn = (direction - orient) % 4

            # Execute the turn based on the relative direction
            if turn == 1:  # Turn right
                API.turnRight()
                print("Turned right")
            elif turn == 2:  # Turn around
                API.turnRight()
                API.turnRight()
                print("Turned around")
            elif turn == 3:  # Turn left
                API.turnLeft()
                print("Turned left")
            # No turn needed if turn == 0

            # Move forward
            API.moveForward()
            print("Moved forward")

            # Update the orientation and position
            orient = direction  # Update the orientation to the new direction
            currentPos = (nextX, nextY)  # Update the current position
            print(f"Moved to position {currentPos}, now facing {orient}")

        else:
            # Have to backtrack to last junction with unexplored paths
            print("Starting to backtrack")
            # Turn 180 degrees and move forward once
            API.turnLeft()
            API.turnLeft()
            API.moveForward()
            """ match orient:
                case 0: orient = 2
                case 1: orient = 3
                case 2: orient = 0
                case 3: orient = 1 """
                
            orient = (orient + 2) % 4

            print("Done turning back")

            while backtrackStack:
                bx, by = backtrackStack[-1]  # Peek at the top of the stack
                print(f"Currently in ({bx} , {by}) with orientation: {orient}")
                unvisitedNeighbors = False
                for d, (dx, dy) in  enumerate(directions):
                    nx, ny = bx + dx, by + dy
                    if 0 <= nx < 16 and 0 <= ny < 16: # Inside the grid
                        if walls[bx][by] & wall_bits[d] == 0 and (nx, ny) not in visited: # No wall in this direction
                            unvisitedNeighbors = True
                            
                if unvisitedNeighbors: 
                    print("There are unvisited neighbors")
                    currentPos = (bx, by)
                    break

                # If no unvisited neighbors, backtrack
                backtrackStack.pop()  # Remove current cell from the stack

                if backtrackStack:
                    # Move to previous cell, by changing the orientation as necessary
                    px, py = backtrackStack[-1]  # Peek at the next cell to backtrack to
                    print(f"Now going to move to cell ({px}, {py})")
                    #Directions:
                    #0: North, 1: East, 2: South, 3: West

                    if px == bx and py == by:
                        continue
                
                    direction_map = {
                        (0, 1): 0,   # North
                        (0, -1): 2,  # South
                        (1, 0): 1,   # East
                        (-1, 0): 3   # West
                    }
         
                    direction = direction_map[(px - bx, py - by)]
     
                    print(f"The direction to move is {direction}")


                    turn = (direction - orient) % 4
                    # Execute the turn based on the relative direction
                    if turn == 1:  # Turn right
                        API.turnRight()
                        print("Turned right")
                    elif turn == 2:  # Turn around
                        API.turnRight()
                        API.turnRight()
                        print("Turned around")
                    elif turn == 3:  # Turn left
                        API.turnLeft()
                        print("Turned left")
                    # No turn needed if turn == 0

                    # Move forward
                    API.moveForward()
                    print("Moved forward")

                    # Update the orientation and position
                    orient = direction  # Update the orientation to the new direction
                    currentPos = (px, py)  # Update the current position
            print(f"Finished backtracking at ({currentPos})")
    floodfill()
    updateMazeDistances()

      
if __name__ == "__main__":
    main()
