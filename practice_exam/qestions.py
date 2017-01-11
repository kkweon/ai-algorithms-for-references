import numpy as np

def pprint(matrix):
    print "["
    for row in matrix:
        print " ", row
    print "]"

# Question 4
# World ["g", "g", "r", "g", "r"]
# 1. begin with the uniform distribution
# 2. Robot senses "red" 
# 3. Robot moves to right. But, the world is not cyclic, so if the robot hits the wall, it does not move
# 4. measurement error is 0.1 and move is exact
# Q. What is the probability it will sense "red" again.
print "Q4 Begins"
world = ['g', 'g', 'r', 'g', 'r']
p_red = 0.9
p_err = 0.1

grid = np.array([])
# Begins with the uniform distribution
for _ in world:
    grid = np.append(grid, 1./len(world))

# Robot senses "red"
for i in xrange(len(world)):
    color = world[i]
    p_prior = grid[i]

    grid[i] = p_prior * p_red if color == 'r' else p_prior * p_err


grid = grid / np.sum(grid)
print "after sense red", grid

# Move to right
new_grid = []
for idx in xrange(len(grid)):
    if idx == 0:
        p = 0.0
    #elif idx == len(grid) - 1:
    #    p = grid[-1]
    else:
        p = grid[idx - 1]
    new_grid.append(p)

new_grid[-1] += grid[-1]
new_grid = np.array(new_grid)
new_grid = new_grid / np.sum(new_grid)

print "after move to right", new_grid
print "p = ", new_grid[-1] + new_grid[-3]


# Q5. The robot location is characterized by a Gaussian,
# which has the value mu = 1 and sigma^2 = 1.
# Perform a measurement with a variance r^2 = 1 and the value of measurement is v = 3
# What are the values of the resulting mu and sigma^2 ?
print "\nQ5 Begins"
def get_mean_variance_after_measurement(old_mu_var, new_mu_var):
    """
    new_mean = (r_sq * mu + sigma_sq * v) / (r_sq + sigma_sq)
    new_sigma = 1 / (1 / r_sq + 1 / sigma_sq)
    
    Args:
        old_mu_var (list): [mu, sigma_sq]
        new_mu_var (list): [v, r_sq]
    
    Returns:
        list: new_mu, new_sigma_sq
    """
    mu, sigma_sq = old_mu_var
    v, r_sq = new_mu_var 

    new_mean = (r_sq * mu + sigma_sq * v) / (r_sq + sigma_sq)
    new_sigma_sq = 1. / (1. / r_sq + 1. / sigma_sq)

    return [new_mean, new_sigma_sq]

print get_mean_variance_after_measurement([1, 1], [3, 1])


# Q8
# | Green (p1) | Green      |   --> P(sense green) = 0.8  and P(sense yellow) = 0.2
# |------------|------------|
# | Yellow (p2)| Yellow (p3)|   --> P(sense green) = 0.3  and P(sense yellow) = 0.7
# 
# There are 3 particles (p1, p2, p3) and you observe yellow
# What is the normalized weight for each particle ?
print "\nQ8 Begins"
P = np.array([0.2, 0.7, 0.7])
print P/sum(P)


print "\nQ12 Begins"
# Q12: Warehouse
# -------------------
# Background Information
#
# In this problem, you will build a planner that helps a robot
# find the shortest way in a warehouse filled with boxes
# that he has to pick up and deliver to a drop zone.
# 
# For example:
#
# warehouse = [[ 1, 2, 3],
#              [ 0, 0, 0],
#              [ 0, 0, 0]]
# dropzone = [2,0] 
# todo = [2, 1]
# 
# The robot starts at the dropzone.
# The dropzone can be in any free corner of the warehouse map.
# todo is a list of boxes to be picked up and delivered to the dropzone.
#
# Robot can move diagonally, but the cost of a diagonal move is 1.5.
# The cost of moving one step horizontally or vertically is 1.
# So if the dropzone is at [2, 0], the cost to deliver box number 2
# would be 5.

# To pick up a box, the robot has to move into the same cell as the box.
# When the robot picks up a box, that cell becomes passable (marked 0)
# The robot can pick up only one box at a time and once picked up 
# it has to return the box to the dropzone by moving onto the dropzone cell.
# Once the robot has stepped on the dropzone, the box is taken away, 
# and it is free to continue with its todo list.
# Tasks must be executed in the order that they are given in the todo list.
# You may assume that in all warehouse maps, all boxes are
# reachable from beginning (the robot is not boxed in).

# -------------------
# User Instructions
#
# Design a planner (any kind you like, so long as it works!)
# in a function named plan() that takes as input three parameters: 
# warehouse, dropzone, and todo. See parameter info below.
#
# Your function should RETURN the final, accumulated cost to do
# all tasks in the todo list in the given order, which should
# match with our answer. You may include print statements to show 
# the optimum path, but that will have no effect on grading.
#
# Your solution must work for a variety of warehouse layouts and
# any length of todo list.
# 
# Add your code at line 76.
# 
# --------------------
# Parameter Info
#
# warehouse - a grid of values, where 0 means that the cell is passable,
# and a number 1 <= n <= 99 means that box n is located at that cell.
# dropzone - determines the robot's start location and the place to return boxes 
# todo - list of tasks, containing box numbers that have to be picked up
#
# --------------------
# Testing
#
# You may use our test function below, solution_check(),
# to test your code for a variety of input parameters. 

warehouse = [[ 1, 2, 3],
             [ 0, 0, 0],
             [ 0, 0, 0]]
dropzone = [2,0] 
todo = [2, 1]

# ------------------------------------------
# plan - Returns cost to take all boxes in the todo list to dropzone
#
# ----------------------------------------
# modify code below
# ----------------------------------------
# Helper Class

class Orientation:
    up = 1
    down = 2  
    left = 3
    right = 4
    upright = 5 
    upleft = 6
    downleft = 7
    downright = 8

delta = [
[-1,  0], #up
[ 1,  0], #down
[ 0, -1], #left
[ 0,  1], #right
[-1,  1], #upright
[-1, -1], #upleft
[ 1, -1], #downleft
[ 1,  1], #downright
]

delta_name = [
' ^',
' v',
' <',
' >',
'-^',
'^-',
'v-',
'-v',
]

class Robot:
    def __init__(self, row, col):
        self.row = row
        self.col = col

    def move(self, orientation, step=1):
        if orientation in [Orientation.up, Orientation.down, Orientation.left, Orientation.right]:
            print "cost of move is 1"
        elif orientation in [Orientation.upleft, Orientation.upright, Orientation.downleft, Orientation.downright]:
            print "cost of move is 1.5"

    def __repr__(self):
        return "Robot: [row={}, col={}]".format(self.row, self.col)

def goal_finder(grid, value):
    for row in xrange(len(grid)):
        for col in xrange(len(grid[0])):
            if grid[row][col] == value:
                return [row, col]

def is_in_grid(grid, pos, goal):
    row, col = pos

    if pos == goal:
        return True

    if 0 <= row < len(grid) and 0 <= col < len(grid[0]) and grid[row][col] == 0:
        return True
    return False


def calculate_cost(grid, init, goal, cost = 1.0, cost_diagonal = 1.5):
    value = [[999. for _ in row]for row in grid]
    policy = [[' ' for _ in row]for row in grid]

    change = True
    limit = 0
    step = 0
    while change and limit < 1000000:
        limit += 1
        change = False

        for row in xrange(len(value)):
            for col in xrange(len(value[0])):
                if [row, col] == goal:
                    if value[row][col] > 0:
                        value[row][col] = 0. 
                        policy[row][col] = '*'
                        change = True

                elif grid[row][col] == 0:
                    for action in xrange(len(delta)):
                        new_row = row + delta[action][0]
                        new_col = col + delta[action][1]

                        if is_in_grid(grid, [new_row, new_col], goal):
                            if action < 4:
                                # non-diagonal
                                new_value = value[new_row][new_col] + cost
                            else:
                                # diagonal
                                new_value = value[new_row][new_col] + cost_diagonal

                            if new_value < value[row][col]:
                                value[row][col] = new_value
                                change = True
                                policy[row][col] = delta_name[action]

    return value, policy

def get_cost(value, init_point):
    return value[init_point[0]][init_point[1]]

print "\nTest"
grid = [
[0, 0, 0, 0],
[0, 1, 1, 0],
[0, 1, 1, 0],
[0, 0, 0, 0]
]
init = [3, 0]
goal = [0, 3]
value, policy = calculate_cost(grid, init, goal)
print "Cost Test: "
pprint(value)
pprint(policy)
print "Total Cost: ", get_cost(value, init)
print "Test Ends\n\n"

def plan(warehouse, dropzone, todo):
    # cost is 1 or 1.5 if diagonal move
    cost = 0
    row, col = dropzone
    robot = [row, col] #Robot(row, col)
    warehouse[row][col] = 0.0
    for box in todo:
        goal = goal_finder(warehouse, box) 
        value, policy = calculate_cost(warehouse, robot, goal)
        path_to_box = get_cost(value, robot)
        warehouse[goal[0]][goal[1]] = 0
        robot = goal
        goal = dropzone
        value, policy = calculate_cost(warehouse, robot, goal)
        path_to_dropzone = get_cost(value, robot)
        robot = dropzone

        cost += path_to_box + path_to_dropzone

    return cost
print "Warehouse Map"
pprint(warehouse)

print "Dropzone"
print (dropzone)

print "Todo"
print(todo)

cost = plan(warehouse, dropzone, todo)    
print "Cost=", cost
################# TESTING ##################
       
# ------------------------------------------
# solution check - Checks your plan function using
# data from list called test[]. Uncomment the call
# to solution_check to test your code.
#
def solution_check(test, epsilon = 0.00001):
    answer_list = []
    
    import time
    start = time.clock()
    correct_answers = 0
    for i in range(len(test[0])):
        user_cost = plan(test[0][i], test[1][i], test[2][i])
        true_cost = test[3][i]
        if abs(user_cost - true_cost) < epsilon:
            print "\nTest case", i+1, "passed!"
            answer_list.append(1)
            correct_answers += 1
            #print "#############################################"
        else:
            print "\nTest case ", i+1, "unsuccessful. Your answer ", user_cost, "was not within ", epsilon, "of ", true_cost 
            answer_list.append(0)
    runtime =  time.clock() - start
    if runtime > 1:
        print "Your code is too slow, try to optimize it! Running time was: ", runtime
        return False
    if correct_answers == len(answer_list):
        print "\nYou passed all test cases!"
        return True
    else:
        print "\nYou passed", correct_answers, "of", len(answer_list), "test cases. Try to get them all!"
        return False
#Testing environment
# Test Case 1 
warehouse1 = [[ 1, 2, 3],
             [ 0, 0, 0],
             [ 0, 0, 0]]
dropzone1 = [2,0] 
todo1 = [2, 1]
true_cost1 = 9
# Test Case 2
warehouse2 = [[   1, 2, 3, 4],
              [   0, 0, 0, 0],
              [   5, 6, 7, 0],
              [ 'x', 0, 0, 8]] 
dropzone2 = [3,0] 
todo2 = [2, 5, 1]
true_cost2 = 21

# Test Case 3
warehouse3 = [[   1, 2,  3,  4, 5, 6,  7],
              [   0, 0,  0,  0, 0, 0,  0],
              [   8, 9, 10, 11, 0, 0,  0],
              [ 'x', 0,  0,  0, 0, 0, 12]] 
dropzone3 = [3,0] 
todo3 = [5, 10]
true_cost3 = 18

# Test Case 4
warehouse4 = [[ 1, 17, 5, 18,  9, 19,  13],
              [ 2,  0, 6,  0, 10,  0,  14],
              [ 3,  0, 7,  0, 11,  0,  15],
              [ 4,  0, 8,  0, 12,  0,  16],
              [ 0,  0, 0,  0,  0,  0, 'x']] 
dropzone4 = [4,6]
todo4 = [13, 11, 6, 17]
true_cost4 = 41

testing_suite = [[warehouse1, warehouse2, warehouse3, warehouse4],
                 [dropzone1, dropzone2, dropzone3, dropzone4],
                 [todo1, todo2, todo3, todo4],
                 [true_cost1, true_cost2, true_cost3, true_cost4]]


solution_check(testing_suite) #UNCOMMENT THIS LINE TO TEST YOUR CODE
