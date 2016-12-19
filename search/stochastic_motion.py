# --------------
# USER INSTRUCTIONS
#
# Write a function called stochastic_value that
# returns two grids. The first grid, value, should
# contain the computed value of each cell as shown
# in the video. The second grid, policy, should
# contain the optimum policy for each cell.
#
# --------------
# GRADING NOTES
#
# We will be calling your stochastic_value function
# with several different grids and different values
# of success_prob, collision_cost, and cost_step.
# In order to be marked correct, your function must
# RETURN (it does not have to print) two grids,
# value and policy.
#
# When grading your value grid, we will compare the
# value of each cell with the true value according
# to this model. If your answer for each cell
# is sufficiently close to the correct answer
# (within 0.001), you will be marked as correct.

delta = [[-1, 0],  # go up
         [0, -1],  # go left
         [1, 0],  # go down
         [0, 1]]  # go right

delta_name = ['^', '<', 'v', '>']  # Use these when creating your policy grid.

# ---------------------------------------------
#  Modify the function stochastic_value below
# ---------------------------------------------


def is_valid(grid, location):
    row, col = location

    if row < 0 or col < 0 or row > len(grid) - 1 or col > len(grid[0]) - 1 or grid[row][col] != 0:
        return False
    return True


def stochastic_value(grid, goal, cost_step, collision_cost, success_prob):
    # Probability(stepping left) = prob(stepping right) = failure_prob
    failure_prob = (1.0 - success_prob) / 2.0
    value = [[collision_cost for col in range(
        len(grid[0]))] for row in range(len(grid))]
    policy = [[' ' for col in range(len(grid[0]))] for row in range(len(grid))]

    change = True
    while change:
        change = False
        for row in xrange(len(grid)):
            for col in xrange(len(grid[0])):
                if [row, col] == goal and value[row][col] > 0:
                    change = True
                    value[row][col] = 0
                    policy[row][col] = "*"
                elif grid[row][col] == 0:
                    for idx, move in enumerate(delta):
                        # move up [-1, 0]
                        # move left [0, -1]
                        # move down [1, 0]
                        # move right [0, 1]
                        new_row, new_col = row + move[0], col + move[1]
                        err1_move = delta[(idx + 1) % len(delta)]
                        err2_move = delta[(idx - 1) % len(delta)]

                        err1_row, err1_col = row + \
                            err1_move[0], col + err1_move[1]
                        err2_row, err2_col = row + \
                            err2_move[0], col + err2_move[1]

                        if is_valid(grid, [new_row, new_col]):
                            new_value = success_prob * \
                                value[new_row][new_col] + cost_step
                            if is_valid(grid, [err1_row, err1_col]):
                                new_value += failure_prob * value[err1_row][err1_col]
                            else:
                                new_value += failure_prob * collision_cost

                            if is_valid(grid, [err2_row, err2_col]):
                                new_value += failure_prob * value[err2_row][err2_col]
                            else:
                                new_value += failure_prob * collision_cost


                            if new_value < value[row][col]:
                                change = True
                                value[row][col] = new_value
                                policy[row][col] = delta_name[idx]

    return value, policy

# ---------------------------------------------
#  Use the code below to test your solution
# ---------------------------------------------

grid = [[0, 0, 0, 0],
        [0, 0, 0, 0],
        [0, 0, 0, 0],
        [0, 1, 1, 0]]
goal = [0, len(grid[0]) - 1]  # Goal is in top right corner
cost_step = 1
collision_cost = 100
success_prob = 0.5



value, policy = stochastic_value(
    grid, goal, cost_step, collision_cost, success_prob)

print "Value"
for row in value:
    print row
print "Policy"
for row in policy:
    print row

# Expected outputs:
#
# [57.9029, 40.2784, 26.0665,  0.0000]
# [47.0547, 36.5722, 29.9937, 27.2698]
# [53.1715, 42.0228, 37.7755, 45.0916]
# [77.5858, 100.00, 100.00, 73.5458]
#
# ['>', 'v', 'v', '*']
# ['>', '>', '^', '<']
# ['>', '^', '^', '<']
# ['^', ' ', ' ', '^']
