# -----------
# User Instructions
#
# Define a function smooth that takes a path as its input
# (with optional parameters for weight_data, weight_smooth,
# and tolerance) and returns a smooth path. The first and
# last points should remain unchanged.
#
# Smoothing should be implemented by iteratively updating
# each entry in newpath until some desired level of accuracy
# is reached. The update should be done according to the
# gradient descent equations given in the instructor's note
# below (the equations given in the video are not quite
# correct).
# -----------

from copy import deepcopy

import numpy as np

# Visualization
import matplotlib.pyplot as plt

# thank you to EnTerr for posting this on our discussion forum


def printpaths(path, newpath):
    for old, new in zip(path, newpath):
        print '[' + ', '.join('%.3f' % x for x in old) + \
            '] -> [' + ', '.join('%.3f' % x for x in new) + ']'

# Don't modify path inside your function.
path = [[0, 0],
        [0, 1],
        [0, 2],
        [1, 2],
        [2, 2],
        [3, 2],
        [4, 2],
        [4, 3],
        [4, 4]]


def smooth(path, weight_data=0.5, weight_smooth=0.1, tolerance=0.000001):

    # Make a deep copy of path into newpath
    newpath = deepcopy(path)

    #######################
    ### ENTER CODE HERE ###
    #######################
    change = True
    while change:
        change = False
        for i in xrange(len(path)):
            # i = 0, .. . len(path) - 1
            if i == 0 or i == len(path) - 1:
                continue
            else:
                x_real, y_real = path[i]
                x_previous, y_previous = newpath[i - 1]
                x_current, y_current = newpath[i]
                x_after, y_after = newpath[i + 1]

                x_new = x_current + weight_data * \
                    (x_real - x_current) + weight_smooth * \
                    (x_after + x_previous - 2.0 * x_current)
                y_new = y_current + weight_data * \
                    (y_real - y_current) + weight_smooth * \
                    (y_after + y_previous - 2.0 * y_current)

                if abs(x_new - x_current) >= tolerance and abs(y_new - y_current) >= tolerance:
                    change = True
                    newpath[i] = [x_new, y_new]
    return newpath  # Leave this line for the grader!

printpaths(path, smooth(path, weight_data=0.5))


plt.scatter(np.array(smooth(path))[:, 0],np.array(smooth(path))[:, 1], marker='o', c='blue', label="New Path")
plt.scatter(np.array(path)[:, 0], np.array(path)[:, 1], marker='^', c='red', label="original point")
plt.grid()
plt.legend()
plt.show()
