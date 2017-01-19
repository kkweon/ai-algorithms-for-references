# ----------
# Background
# 
# A robotics company named Trax has created a line of small self-driving robots 
# designed to autonomously traverse desert environments in search of undiscovered
# water deposits.
#
# A Traxbot looks like a small tank. Each one is about half a meter long and drives
# on two continuous metal tracks. In order to maneuver itself, a Traxbot can do one
# of two things: it can drive in a straight line or it can turn. So to make a 
# right turn, A Traxbot will drive forward, stop, turn 90 degrees, then continue
# driving straight.
#
# This series of questions involves the recovery of a rogue Traxbot. This bot has 
# gotten lost somewhere in the desert and is now stuck driving in an almost-circle: it has
# been repeatedly driving forward by some step size, stopping, turning a certain 
# amount, and repeating this process... Luckily, the Traxbot is still sending all
# of its sensor data back to headquarters.
#
# In this project, we will start with a simple version of this problem and 
# gradually add complexity. By the end, you will have a fully articulated
# plan for recovering the lost Traxbot.
# 
# ----------
# Part One
#
# Let's start by thinking about circular motion (well, really it's polygon motion
# that is close to circular motion). Assume that Traxbot lives on 
# an (x, y) coordinate plane and (for now) is sending you PERFECTLY ACCURATE sensor 
# measurements. 
#
# With a few measurements you should be able to figure out the step size and the 
# turning angle that Traxbot is moving with.
# With these two pieces of information, you should be able to 
# write a function that can predict Traxbot's next location.
#
# You can use the robot class that is already written to make your life easier. 
# You should re-familiarize yourself with this class, since some of the details
# have changed. 
#
# ----------
# YOUR JOB
#
# Complete the estimate_next_pos function. You will probably want to use
# the OTHER variable to keep track of information about the runaway robot.
#
# ----------
# GRADING
# 
# We will make repeated calls to your estimate_next_pos function. After
# each call, we will compare your estimated position to the robot's true
# position. As soon as you are within 0.01 stepsizes of the true position,
# you will be marked correct and we will tell you how many steps it took
# before your function successfully located the target bot.

# These import steps give you access to libraries which you may (or may
# not) want to use.
from robot import *
from math import *
from matrix import *
import random
import numpy as np

# This is the function you have to write. The argument 'measurement' is a 
# single (x, y) point. This function will have to be called multiple
# times before you have enough information to accurately predict the
# next position. The OTHER variable that your function returns will be 
# passed back to your function the next time it is called. You can use
# this to keep track of important information over time.
# 

def gaussian(mu, sigma, x):
    return 1. / float(sigma) / sqrt(2.0 * pi) * exp(-0.5 * np.square(x - mu) / np.square(sigma) )


def resampling_wheel(particle, prob):
    """
    p3 = []

summation = sum(w)
beta = 0
index = random.randint(0, N-1)
for i in xrange(N):
    beta += random.uniform(0, 2*max(w))
    while w[index] < beta:
        beta = beta - w[index]
        index = ( index + 1 ) % N
    p3.append(p[index])
    """
    result = []
    N = len(particle)
    beta = 0
    index = random.randint(0, N-1)
    for i in xrange(N):
        beta += random.uniform(0, 2 * max(prob))
        while prob[index] < beta:
            beta = beta - prob[index]
            index = (index + 1) % N
        result.append(particle[index])
    return result

def measure_error(measurements, filter):
    prob = 1.0
    for i in xrange(len(measurements)):
        measure = measurements[i]
        if i == 0:
            dist_original = distance_between(measure, filter)
        else:
            dist_test = distance_between(measure, filter)
            prob *= gaussian(dist_original, 1, dist_test)
    return prob

def measure_error_over_particles(measurements, filters):
    prob_list = []
    for idx, particle in enumerate(filters):
        prob = measure_error(measurements, particle)
        prob_list.append(prob)

    return prob_list

def calculate_error(filter, measurements):
    err_list = []
    for i in xrange(len(measurements)):
        measure = measurements[i]
        if i == 0:
            dist_original = distance_between(measure, filter)
        else:
            dist_test = distance_between(measure, filter)
            err_list.append(abs(dist_original - dist_test))
    mse = np.mean(np.square(err_list))
    return mse

def calculate_error_over_particles(filters, measurements):
    mse_list = []
    for particle in filters:
        err = calculate_error(particle, measurements)
        mse_list.append(err)

    return mse_list

def estimate_next_pos(measurement, OTHER = None):
    """Estimate the next (x, y) position of the wandering Traxbot
    based on noisy (x, y) measurements."""

    # You must return xy_estimate (x, y), and OTHER (even if it is None) 
    # in this order for grading purposes.
    SIZE = 2000
    if OTHER is None:
        OTHER = {
            'data': [measurement],
            'filter': [],
            'filter_prob': [],
        }

        x_sets = np.random.uniform(low=-5.0, high=25.0, size=SIZE)
        y_sets = np.random.uniform(low=-5.0, high=25.0, size=SIZE)

        for i in xrange(len(x_sets)):
            particle_filter = [x_sets[i], y_sets[i]]
            OTHER['filter'].append(particle_filter)
            OTHER['filter_prob'].append(1.0)

        xy_estimate = measurement
    else:
        OTHER['data'].append(measurement)


        OTHER['filter_prob'] = measure_error_over_particles(OTHER['data'], OTHER['filter'])
        OTHER['filter_prob'] = np.array(OTHER['filter_prob']) / np.sum(OTHER['filter_prob'])
        OTHER['filter'] = resampling_wheel(OTHER['filter'], OTHER['filter_prob'])

        mse_list = measure_error_over_particles(OTHER['data'], OTHER['filter'])

        print "MSE: ", np.min(mse_list)
        xy_estimate = OTHER['filter'][np.argmin(mse_list)]

    return xy_estimate, OTHER 

# A helper function you may find useful.
def distance_between(point1, point2):
    """Computes distance between point1 and point2. Points are (x, y) pairs."""
    x1, y1 = point1
    x2, y2 = point2
    return sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)

# This is here to give you a sense for how we will be running and grading
# your code. Note that the OTHER variable allows you to store any 
# information that you want. 
def demo_grading_visualize(estimate_next_pos_fcn, target_bot, OTHER = None):
    localized = False
    distance_tolerance = 0.01 * target_bot.distance
    ctr = 0
    # if you haven't localized the target bot, make a guess about the next
    # position, then we move the bot and compare your guess to the true
    # next position. When you are close enough, we stop checking.
    #For Visualization
    import turtle    #You need to run this locally to use the turtle module
    window = turtle.Screen()
    window.bgcolor('white')
    size_multiplier= 25.0  #change Size of animation
    broken_robot = turtle.Turtle()
    broken_robot.shape('turtle')
    broken_robot.color('green')
    broken_robot.resizemode('user')
    broken_robot.shapesize(0.1, 0.1, 0.1)
    measured_broken_robot = turtle.Turtle()
    measured_broken_robot.shape('circle')
    measured_broken_robot.color('red')
    measured_broken_robot.resizemode('user')
    measured_broken_robot.shapesize(0.1, 0.1, 0.1)
    prediction = turtle.Turtle()
    prediction.shape('arrow')
    prediction.color('blue')
    prediction.resizemode('user')
    prediction.shapesize(0.1, 0.1, 0.1)
    prediction.penup()
    broken_robot.penup()
    measured_broken_robot.penup()
    #End of Visualization
    while not localized and ctr <= 10:
        ctr += 1
        measurement = target_bot.sense()
        position_guess, OTHER = estimate_next_pos_fcn(measurement, OTHER)
        target_bot.move_in_circle()
        true_position = (target_bot.x, target_bot.y)
        error = distance_between(position_guess, true_position)
        if error <= distance_tolerance:
            print "You got it right! It took you ", ctr, " steps to localize."
            localized = True
        if ctr == 10:
            print "Sorry, it took you too many steps to localize the target."
        #More Visualization
        measured_broken_robot.setheading(target_bot.heading*180/pi)
        measured_broken_robot.goto(measurement[0]*size_multiplier, measurement[1]*size_multiplier-200)
        measured_broken_robot.stamp()
        broken_robot.setheading(target_bot.heading*180/pi)
        broken_robot.goto(target_bot.x*size_multiplier, target_bot.y*size_multiplier-200)
        broken_robot.stamp()
        prediction.setheading(target_bot.heading*180/pi)
        prediction.goto(position_guess[0]*size_multiplier, position_guess[1]*size_multiplier-200)
        prediction.stamp()
        #End of Visualization
    return localized

def demo_grading(estimate_next_pos_fcn, target_bot, OTHER = None, visualization=False):
    if visualization:
        demo_grading_visualize(estimate_next_pos_fcn, target_bot, OTHER)
    else:
        localized = False
        distance_tolerance = 0.01 * target_bot.distance
        ctr = 0
        # if you haven't localized the target bot, make a guess about the next
        # position, then we move the bot and compare your guess to the true
        # next position. When you are close enough, we stop checking.
        while not localized and ctr <= 10: 
            ctr += 1
            measurement = target_bot.sense()
            position_guess, OTHER = estimate_next_pos_fcn(measurement, OTHER)
            target_bot.move_in_circle()
            true_position = (target_bot.x, target_bot.y)
            error = distance_between(position_guess, true_position)
            if error <= distance_tolerance:
                print "You got it right! It took you ", ctr, " steps to localize."
                localized = True
            if ctr == 10:
                print "Sorry, it took you too many steps to localize the target."
        return localized

# This is a demo for what a strategy could look like. This one isn't very good.
def naive_next_pos(measurement, OTHER = None):
    """This strategy records the first reported position of the target and
    assumes that eventually the target bot will eventually return to that 
    position, so it always guesses that the first position will be the next."""
    if not OTHER: # this is the first measurement
        OTHER = measurement
    xy_estimate = OTHER 
    return xy_estimate, OTHER

# This is how we create a target bot. Check the robot.py file to understand
# How the robot class behaves.
test_target = robot(2.1, 4.3, 0.5, 2*pi / 34.0, 1.5)
test_target.set_noise(0.0, 0.0, 0.0)

print test_target
demo_grading(estimate_next_pos, test_target, visualization=True)
