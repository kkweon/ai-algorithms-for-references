from pprint import pprint

# ----------
# User Instructions:
#
# Create a function compute_value which returns
# a grid of values. The value of a cell is the minimum
# number of moves required to get from the cell to the goal.
#
# If a cell is a wall or it is impossible to reach the goal from a cell,
# assign that cell a value of 99.
# ----------
import sys

grid = [
    [0, 1, 0, 0, 0, 0],
    [0, 1, 0, 0, 0, 0],
    [0, 1, 0, 0, 0, 0],
    [0, 1, 0, 0, 0, 0],
    [0, 0, 0, 0, 1, 0],
]
goal = [len(grid) - 1, len(grid[0]) - 1]
cost = 1  # the cost associated with moving from a cell to an adjacent one
OBSTACLE = 99
delta = [[-1, 0], [0, -1], [1, 0], [0, 1]]  # go up  # go left  # go down  # go right

delta_name = ["^", "<", "v", ">"]


def get_nearby_position(grid, location, delta, history):
    result = set()
    for row, col in delta:
        row_new, col_new = location[0] + row, location[1] + col
        new_loc = (row_new, col_new)

        if is_valid(grid, new_loc) and new_loc not in history:
            result.add(new_loc)
            history.add(new_loc)
    return result


def is_valid(grid, loc):
    """Check if loc is out of grid
    grid: m x n
    loc: [x, y]
    """
    max_row, max_col = len(grid), len(grid[0])
    row, col = loc
    if row < 0 or col < 0 or row > max_row - 1 or col > max_col - 1:
        return False
    return True


def hit_obstacle(grid, loc):
    """
    Check if obstacle at loc
    grid: m x n
    loc: [x, y]
    """
    row, col = loc
    return grid[row][col] == 1


def compute_value(grid, goal, cost):
    """
    Params
    ======
    grid (n x m) matrix : world
    goal ([x, y])       : final destination
    cost (int)          : cost of one step 
    """
    row, col = goal
    value = [
        [99 for col in xrange(len(grid[0]))] for row in xrange(len(grid))
    ]  # create a copy of the grid
    value[row][col] = 0
    history = set()
    history.add((row, col))
    children = get_nearby_position(grid, goal, delta, history)
    step = 0
    while len(children) > 0:
        tmp_nearby_set = set()
        for child in children:
            if hit_obstacle(grid, child):
                # value[child[0]][child[1]] = OBSTACLE
                continue
            else:
                value[child[0]][child[1]] = step + cost
                grand_children = get_nearby_position(grid, child, delta, history)
                for gc in grand_children:
                    tmp_nearby_set.add(gc)

        step += 1
        children = tmp_nearby_set

    return value


result = compute_value(grid, goal, cost)
pprint(result)
