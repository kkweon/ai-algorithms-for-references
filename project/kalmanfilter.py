"""Summary

Kalman Filter Class For a robot tracking

X = [[x],
     [y],
     [heading_angle],
     [turning_angle],
     [distance]]



"""

import argparse

import numpy as np

import matplotlib.pyplot as plt
from matrix import *


class KalmanFilter(object):
    def __init__(self, sigma, init_x, init_y):
        self.x = np.array([[init_x],  # x-coordinate
                           [init_y],  # y-coordinate
                           [0.0],  # heading_anlge
                           [0.0],  # turning_angle
                           [0.0]])  # distance

        # In Extended Kalman Filter
        # F = function of x
        self.f = None #KalmanFilter.get_transition_matrix(self.x)
        # covariance matrix
        self.p = np.array([[1000., 0., 0., 0., 0.],
                           [0., 1000., 0., 0., 0.],
                           [0., 0., 1000., 0., 0.],
                           [0., 0., 0., 1000., 0.],
                           [0., 0., 0., 0., 1000.]])

        # measurement uncertainty
        self.r = np.array([[sigma, 0.0],
                           [0.0, sigma]])

        # mapping: measurement -> state
        self.h = np.array([[1., 0., 0., 0., 0.],
                           [0., 1., 0., 0., 0.]])

        self.I = np.array([[1., 0., 0., 0., 0.],
                           [0., 1., 0., 0., 0.],
                           [0., 0., 1., 0., 0.],
                           [0., 0., 0., 1., 0.],
                           [0., 0., 0., 0., 1.]])

        self.predict()

    @staticmethod
    def get_transition_matrix(x):
        """
        x = f(x)
        f = df dx 

        fx = x + d * cos(h + r)
        fy = y + d * sin(h + r)
        fh = h + r
        fr = r
        fd = d
        """
        h = x[2][0]  # heading_angle
        r = x[3][0]  # rotaion_angle
        d = x[4][0]  # distance

        return np.array([[1., 0., -d * sin(h + r), -d * sin(h + r), cos(h + r)],
                         [0., 1., d * cos(h + r), d * cos(h + r), sin(h + r)],
                         [0., 0., 1., 1., 0.],
                         [0., 0., 0., 1., 0.],
                         [0., 0., 0., 0., 1.]])

    def predict(self):

        x = self.x[0][0]
        y = self.x[1][0]
        h = self.x[2][0]
        r = self.x[3][0]
        d = self.x[4][0]

        new_x = x + d * cos(h + r)
        new_y = y + d * sin(h + r)
        new_h = h + r
        new_r = r
        new_d = d

        new_x = np.array([[new_x],
                          [new_y],
                          [new_h],
                          [new_r],
                          [new_d]])
        self.f = KalmanFilter.get_transition_matrix(self.x)
        self.p = self.f.dot(self.p).dot(self.f.transpose())  # + self.q
        self.x = new_x

    def predict_next_point(self, measurement):
        self.update(measurement)
        self.predict()
        x = self.x[0][0]
        y = self.x[1][0]

        return [x, y]

    def update(self, measurement):
        x, y = measurement
        z = np.array([[x],
                      [y]])

        y = z - self.h.dot(self.x)
        S = self.r + self.h.dot(self.p).dot(self.h.transpose()) 
        K = self.p.dot(self.h.transpose()).dot(np.linalg.inv(S))


        self.x = self.x + K.dot(y)
        self.p = (self.I - K.dot(self.h)).dot(self.p)


def get_error(pointA, pointB):
    x, y = pointA
    a, b = pointB

    return sqrt((x-a)**2 + (y - b)**2)

if __name__ == '__main__':

    parser = argparse.ArgumentParser(description='part 1. noiseless prediction') 
    parser.add_argument('--visualize', action="store_true",
                        help='visualize the robot')

    parser.add_argument('--verbose', 
                        action="store_true",
                        help='verbose the prediction and the robot')

    parser.add_argument('--sigma', 
                        type=float,
                        default=1e-9,
                        help='Measurement Error')

    parser.add_argument('N', 
                        type=int,
                        help='N: how many measurements')
    args = parser.parse_args()
    verbose = args.verbose
    visualize = args.visualize

    print "Measurement Error"
    print args.sigma

    measurements = []
    radius = 1
    x = np.arange(radius, -radius, -0.1)
    y = np.sqrt(radius**2 - x**2) 
    measurements += [[x,y] for x, y in zip(x, y)]

    x = np.arange(-radius, radius, 0.1)
    y = -np.sqrt(radius**2 - x**2) 
    measurements += [[x,y] for x, y in zip(x, y)]
    measurements *= args.N

    result = []
    error_list = []

    k = KalmanFilter(args.sigma, measurements[0][0], measurements[0][1])
    for i in xrange(len(measurements) - 2):
        m = measurements[i+1]
        next = measurements[i+2]
        predict_point = k.predict_next_point(m)
        err = get_error(predict_point, next)
        if verbose:
            print "Predicted: {}".format(predict_point)
            print "Real: {}".format(next)
            print "Error: {}".format(err)
            print "============="
            print ""
        result.append(predict_point)
        error_list.append(err)


    if visualize:
        plt.scatter([x[0] for x in measurements], [x[1] for x in measurements], c="red", alpha=0.5, label="actual")
        plt.scatter([x[0] for x in result], [x[1] for x in result], c="blue", alpha=0.5, label="prediction")
        plt.legend()
        plt.grid('on')
        plt.show()

        plt.plot(error_list)
        plt.show()
