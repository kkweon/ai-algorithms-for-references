from part2_adding_noise import *

def test_inner_product():
    vec1 = [1, 5]
    vec2 = [3, 4]

    assert inner_product(vec1, vec2) == 3 + 20

def test_get_length():
    vec1 = [3.5, 2.1]
    assert get_legnth(vec1) == sqrt(vec1[0]**2 + vec1[1]**2)


def test_get_angle_between():
    u = [2.,2.]
    v = [0.,3.]

    assert abs(get_angle_between(u, v) - pi/4) < 1e-7


def test_get_distance_list():
    history = [[1,0], [2,0], [3,0], [4,0], [5,0]]

    assert (get_distance_list(history)) == [1., 1., 1., 1.]


def test_mean():
    list = [1,2,3,4,5]
    assert mean(list) == 3.

def test_get_angle_list():
    history = [[1,0], [2,0]]

    assert get_angle_list(history) == [0.0]