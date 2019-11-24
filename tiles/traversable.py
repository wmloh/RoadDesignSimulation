from abc import abstractmethod
from tiles.tile import Tile
from collections import deque
from utils.constants import REACHED, BLOCKED, STEPPED


class Traversable(Tile):

    def __init__(self, x, y, capacity):
        super(Traversable, self).__init__(x, y)
        self.capacity = capacity
        self.cars = deque()

    def accept_car(self, car):
        self.cars.append(car)

    def send_car(self, direction, car):
        tile = self.neighbours[direction]

        curX, curY = tile.get_coord()
        desX, desY = car.get_dest()

        if curX == desX and curY == desY:
            car.reached()
            self.cars.popleft()
            return REACHED

        if not isinstance(tile, Traversable):
            raise ValueError(f'Invalid routing in Traversable.send_car; arrived at {type(tile)}')

        if len(tile.cars) < tile.capacity:
            moved_car = self.cars.popleft()
            moved_car.cur_road = tile
            tile.accept_car(moved_car)
            return STEPPED
        return BLOCKED

    @abstractmethod
    def __str__(self):
        return ''

    @abstractmethod
    def traversable(self):
        return False