import numpy as np

import matplotlib.pyplot as plt


class KalmanFilter(object):
    def __init__(self, sigma):
        """
        Kalman Filter Constructor
        
        Algorithms:
            X: state matrix [[ x ],
                             [ y ],
                             [ x_velocity ],
                             [ y_velocity ],
                             [ x_acceleration ],
                             [ y_acceleration ]]

            << State Transition >>
                x <- x + x_velocity
                y <- y + y_velocity
                x_velocity <- x_velocity + x_acceleration
                y_velocity <- y_velocity + y_acceleration
                x_acceleration <- x_acceleration
                y_acceleration <- y_acceleration
                
        Args:
            sigma (float): measurement uncertainty
        """
        self.x = np.array([[0. for i in xrange(6)]]).reshape(-1, 1)
        self.f = np.array([[1, 0, 1, 0, 0, 0],
                           [0, 1, 0, 1, 0, 0],
                           [0, 0, 1, 0, 1, 0],
                           [0, 0, 0, 1, 0, 1],
                           [0, 0, 0, 0, 1, 0],
                           [0, 0, 0, 0, 0, 1]])
        self.p = np.diag([999. for i in xrange(6)])
        self.h = np.array([[1., 0., 0., 0., 0., 0.],
                           [0., 1., 0., 0., 0., 0.]])
        self.r = np.array([[sigma, 0.],
                           [0., sigma]])
        self.i = np.identity(6)
        self.predict()

    def predict(self):
        """
        Prediction Step in Kalman Filter
        
        Algorithms:
            x = f*x
            p = f*p*f^T
        """
        self.x = self.f.dot(self.x)
        self.p = self.f.dot(self.p).dot(self.f.transpose())

    def update(self, measurement):
        """
        Update Step in Kalman Filter.
        
        Algorithms:
            Z = measurement matrix (2x1)
            y = z - h * x (error between sensor measurement and predicted value)
            s = h * p * h^T + r
            k = p * h^T * s^-1 (kalman gain)

            x = x_real = x + k * y
            p = p_real = (I - k * h)*p       
                
        Args:
            measurement (list): [x, y] coordinates
        """

        z = np.array(measurement).reshape(-1, 1)
        y = z - self.h.dot(self.x)
        s = self.h.dot(self.p).dot(self.h.transpose()) + self.r
        k = self.p.dot(self.h.transpose()).dot(np.linalg.inv(s))

        self.x = self.x + k.dot(y)
        self.p = (self.i - k.dot(self.h)).dot(self.p)

    def predict_point(self, measurement):
        """
        One Step Wrapper for Kalman Filter
        sense() -> predict() next point
        
        Args:
            measurement (list): [x, y] coordinates
        """
        self.update(measurement)
        self.predict()
        return self.get_point()


    def get_point(self):
        """
        Return:
            [x, y]: coordinate from the state vector X
        """
        return self.x[0:2, :].flatten()


def get_dist(pointA, pointB):
    """
    Returns
        float: distance between two points (to calculate distance between real and predicted positions)
    """
    a, b = pointA
    c, d = pointB

    return np.sqrt((a-c)**2 + (b - d)**2)


if __name__ == '__main__':
    filter = KalmanFilter(1e-10)

    
    # create sensor data
    measurements = []
    result = []
    err_list = []

    # x^2 + y^2 = r^2
    # N: how many round of circle
    # N = 10 -> sensor data of 10 circles 
    step_size = 0.5 
    radius = 10
    N = 100

    # sin graph
    # x = np.arange(-radius, radius*N, step_size)
    # y = np.sin(x) + np.random.randn(len(x)) * 0.1
    # measurements += [[x,y] for x, y in zip(x, y)]

    # circle
    # upper half
    x = np.arange(-radius, radius, step_size)
    y = np.sqrt(radius**2 - x**2) + np.random.randn(len(x)) # add noise
    measurements += [[x,y] for x, y in zip(x, y)]
    # circle lower half
    x = np.arange(radius, -radius, -step_size)
    y = -np.sqrt(radius**2 - x**2) + np.random.randn(len(x)) # add noise
    measurements += [[x,y] for x, y in zip(x, y)]
    # how many circle
    measurements *= N

    for i in xrange(len(measurements)):
        m = measurements[i]
        pred = filter.predict_point(m)
        err = get_dist(m, pred)
        print "error: {}".format(err)
        err_list.append(err)
        result.append(pred)

    plt.figure("Kalman Filter Visualization")
    plt.subplot(211)
    plt.scatter([x[0] for x in measurements], [x[1] for x in measurements], c='red', label='Real Position', alpha=0.3, s = 2)
    plt.scatter([x[0] for x in result], [x[1] for x in result], c='blue', label='Predicted Position', alpha=0.3, s = 2, marker='x')
    plt.legend()
    plt.grid('on')
    plt.title("Circular Motion Robot and Kalman Filter Prediction")
    plt.xlabel("X-axis")
    plt.ylabel("Y-axis")


    plt.subplot(212)
    plt.plot(err_list, lw=0.1)
    plt.grid('on')
    plt.title("Error MSE(True Position - Predicted Position)")
    plt.xlabel("Iteration")

    plt.tight_layout()
    plt.show()
