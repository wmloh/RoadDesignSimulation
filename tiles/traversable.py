from abc import abstractmethod
from tiles.tile import Tile
from collections import deque
from utils.constants import REACHED, BLOCKED, STEPPED


class Traversable(Tile):
    __doc__ = '''
    Abstract class for Tiles that can either contain cars or is a Tile that directly
    interacts with a car
    '''

    def __init__(self, x, y, capacity):
        '''
        Abstract constructor for a Traversable

        :param x: Int - x-coordinate of the tile
        :param y: Int - y-coordinate of the tile
        :param capacity: Int - maximum number of cars the tile can support
        '''
        super(Traversable, self).__init__(x, y)
        self.capacity = capacity
        self.cars = deque()

    def accept_car(self, car):
        '''
        Appends the car reference into the object.

        Note: Responsibility of checking for capacity is on the caller, not callee

        :param car: Car - reference to car to be added
        :return: None
        '''
        self.cars.append(car)

    def send_car(self, direction, car):
        '''
        Sends the car object to a neighbouring tile given the direction

        :param direction: Int - integer representation of direction defined by constants
        :param car: Car - reference to car to send
        :return: Int - integer representation of states defined by constants
        '''
        tile = self.neighbours[direction]

        curX, curY = tile.get_coord()
        desX, desY = car.get_dest()

        if curX == desX and curY == desY:
            # arrived at destination
            car.reached()
            car.cur_road = tile
            self.cars.remove(car)
            return REACHED

        if not isinstance(tile, Traversable):
            # most probably something wrong with the pathfinding algorithm
            raise ValueError(f'Invalid routing in Traversable.send_car; arrived at {type(tile)}')

        if len(tile.cars) < tile.capacity:
            self.cars.remove(car)
            car.cur_road = tile
            tile.accept_car(car)
            return STEPPED
        # implicit else condition
        return BLOCKED
