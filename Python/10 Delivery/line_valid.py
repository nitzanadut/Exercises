def fdirection(a, b):
    "1 - Up/Down, 0 - Left/Right"
    return b[0] != a[0]

def get_neighbors(lines, current):
    "Returns a node's neighbors"
    neighbors = []

    if current[0] != 0:                 neighbors.append((current[0] - 1, current[1]))
    if current[0] != len(lines) - 1:    neighbors.append((current[0] + 1, current[1]))
    if current[1] != 0:                 neighbors.append((current[0], current[1] - 1))
    if current[1] != len(lines[0]) - 1: neighbors.append((current[0], current[1] + 1))

    return neighbors

def check_floating(lines, visited):
    "Checks if we have a 'floating' node, meaning not in one path with the others"
    for i, line in enumerate(lines):
        for j, c in enumerate(line):
            if c == ' ': continue
            if (i, j) not in visited: return True
    return False

def check_path(current, end, lines, last=(-1,-1)):
    "Checks if a given path is valid"
    direction = -1
    visited = []

    while current != end:
        neighbors = get_neighbors(lines, current)
        current_value = lines[current[0]][current[1]]
        
        potential_next = []
        # Finding the neighbors fitting to be the next step
        for neighbor in neighbors:
            # Neighbor is not an empty space, not in the visited nodes and the direction is valid
            if lines[neighbor[0]][neighbor[1]] != ' ' and not neighbor in visited and (
                direction == -1 or (current_value == '+' and fdirection(current, neighbor) != direction) or (
                                    current_value != '+' and fdirection(current, neighbor) == direction)):
                potential_next.append(neighbor)

        # Checking if the neighbor's value doesn't match the direction
        to_remove = []
        for pot_next in potential_next:
            if (fdirection(current, pot_next) == 1 and lines[pot_next[0]][pot_next[1]] == '-') or (fdirection(current, pot_next) == 0 and lines[pot_next[0]][pot_next[1]] == '|'):
                to_remove.append(pot_next)

        for item in to_remove: potential_next.remove(item)

        # Intersection with more than one valid option
        if len(potential_next) != 1:
            return False

        next_ = potential_next[0]
        direction = fdirection(current, next_)
        
        # Validate intersection
        if last != (-1, -1) and current_value == '+':
            if fdirection(current, last) == fdirection(current, next_):
                    return False
        elif last != (-1, -1) and current_value != 'X' and lines[last[0]][last[1]] != 'X' and lines[last[0]][last[1]] != '+' and (fdirection(last, current) != fdirection(current, next_) or current_value != lines[last[0]][last[1]]):
                return False
        
        # Updating visited and last
        visited.append(current)
        last = current
        
        # Change current
        current = next_

    visited.append(end)
    if check_floating(lines, visited):
        return False

    # Passed all requirements, valid path
    return True

def line_valid(lines):
    "Recieves a grid the returns whether the given grid is solvable"
    
    # Doesn't have start and end
    if sum([sum([c == 'X' for c in line]) for line in lines]) != 2:
        return False
    
    # Mapping out start and end
    start = end = '-1'
    for i, line in enumerate(lines):
        for j, n in enumerate(line):
            if n == 'X':
                if start == '-1': start = (i, j)
                else: end = (i, j)
    
    # The path is valid from the start OR from the end
    return check_path(start, end, lines) or check_path(end, start, lines)


#Examples: 
grid = ["           ",
        "X---------X",
        "           ",
        "           "]
print(line_valid(grid))  # ---> True


grid = ["     ",
        "  X  ",
        "  |  ",
        "  |  ",
        "  X  "]
print(line_valid(grid))  # ---> True


# Note: this grid is only valid when starting on the right-hand X, but still considered valid
grid = ["                      ",
        "   +-------+          ",
        "   |      +++---+     ",
        "X--+      +-+   X     "]
print(line_valid(grid))  # ---> True


grid = [" X  ",
        " |  ",
        " +  ",
        " X  "]
print(line_valid(grid))  # ---> False


grid = ["              ",
        "   +------    ",
        "   |          ",
        "X--+      X   ",
        "              "]
print(line_valid(grid))  # ---> False


grid = ["      +------+",
        "      |      |",
        "X-----+------+",
        "      |       ",
        "      X       "]
print(line_valid(grid))  # ---> False

grid = ["X-----|-------X"]
print(line_valid(grid))

grid = ['X+', 'X+']
print(line_valid(grid))

grid = ['X-----X', '       ', '- -    ']
print(line_valid(grid))

grid = ['+-----+',
        '|+---+|',
        '||+-+||',
        '|||X+||',
        'X|+--+|',
        ' +----+']

print(line_valid(grid))
