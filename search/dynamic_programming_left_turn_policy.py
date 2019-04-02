from pprint import pprint

# ----------
# User Instructions:
#
# Implement the function optimum_policy2D below.
#
# You are given a car in grid with initial state
# init. Your task is to compute and return the car's
# optimal path to the position specified in goal;
# the costs for each motion are as defined in cost.
#
# There are four motion directions: up, left, down, and right.
# Increasing the index in this array corresponds to making a
# a left turn, and decreasing the index corresponds to making a
# right turn.

forward = [[-1, 0], [0, -1], [1, 0], [0, 1]]  # go up  # go left  # go down  # go right
forward_name = ["up", "left", "down", "right"]

# action has 3 values: right turn, no turn, left turn
action = [-1, 0, 1]
action_name = ["R", "#", "L"]

# EXAMPLE INPUTS:
# grid format:
#     0 = navigable space
#     1 = unnavigable space
grid = [
    [1, 1, 1, 0, 0, 0],
    [1, 1, 1, 0, 1, 0],
    [0, 0, 0, 0, 0, 0],
    [1, 1, 1, 0, 1, 1],
    [1, 1, 1, 0, 1, 1],
]

init = [4, 3, 0]  # given in the form [row,col,direction]
# direction = 0: up
#             1: left
#             2: down
#             3: right

goal = [2, 0]  # given in the form [row,col]

cost = [2, 1, 20]  # cost has 3 values, corresponding to making
# a right turn, no turn, and a left turn


def is_valid(grid, location):
    """
    grid: m x n matrix
    location: [row, col, direction]
    """

    row, col, direction = location
    max_row, max_col = len(grid), len(grid[0])

    if (
        row < 0
        or col < 0
        or row > max_row - 1
        or col > max_col - 1
        or grid[row][col] != 0
    ):
        # out of grid
        return False
    return True


def optimum_policy2D(grid, init, goal, cost):
    """
    Params
    ======
    grid: 2-D list
    init: [row, col, direction] where
            direction {0: up, 1: left, 2: down, 3: right}
    goal: [row, col]
    cost: [right turn cost, no turn cost, left turn cost]

    Returns
    ======
    policy2D: 2-D List
    calling optimum_policy2D with the given parameters should return
    [[' ', ' ', ' ', 'R', '#', 'R'],
     [' ', ' ', ' ', '#', ' ', '#'],
     ['*', '#', '#', '#', '#', 'R'],
     [' ', ' ', ' ', '#', ' ', ' '],
     [' ', ' ', ' ', '#', ' ', ' ']]
    """
    policy2D = [[" " for col in xrange(len(grid[0]))] for row in xrange(len(grid))]

    c_row, c_col, c_orientation = init[0], init[1], init[2]
    value = [
        [[999 for col in xrange(len(grid[0]))] for row in xrange(len(grid))]
        for d in xrange(len(forward))
    ]
    policy = [
        [[" " for col in xrange(len(grid[0]))] for row in xrange(len(grid))]
        for d in xrange(len(forward))
    ]
    change = True
    while change:
        change = False

        for row in xrange(len(grid)):
            for col in xrange(len(grid[0])):
                for step in xrange(len(forward)):
                    if goal[0] == row and goal[1] == col:
                        if value[step][row][col] > 0:
                            value[step][row][col] = 0
                            policy[step][row][col] = "*"
                            change = True

                    elif grid[row][col] == 0:
                        for m_idx in xrange(len(action)):
                            # m_idx == 0, 1, 2
                            new_orientation = (step + action[m_idx]) % len(forward)
                            new_row = row + forward[new_orientation][0]
                            new_col = col + forward[new_orientation][1]
                            new_loc = [new_row, new_col, new_orientation]
                            if is_valid(grid, new_loc):
                                new_value = value[new_orientation][new_row][new_col]
                                new_value += cost[m_idx]

                                if new_value < value[step][row][col]:
                                    change = True
                                    value[step][row][col] = new_value
                                    policy[step][row][col] = action_name[m_idx]

    x, y, d = init
    policy2D[x][y] = policy[d][x][y]
    while policy[d][x][y] != "*":
        if policy[d][x][y] == "#":
            d2 = d
        elif policy[d][x][y] == "R":
            d2 = (d - 1) % 4
        elif policy[d][x][y] == "L":
            d2 = (d + 1) % 4
        x = x + forward[d2][0]
        y = y + forward[d2][1]
        d = d2
        policy2D[x][y] = policy[d][x][y]
    return policy2D


result = optimum_policy2D(grid, init, goal, cost)
pprint(result)
