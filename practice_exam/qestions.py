import numpy as np

# Question 4
# World ["g", "g", "r", "g", "r"]
# 1. begin with the uniform distribution
# 2. Robot senses "red" 
# 3. Robot moves to right. But, the world is not cyclic, so if the robot hits the wall, it does not move
# 4. measurement error is 0.1 and move is exact
# Q. What is the probability it will sense "red" again.

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
