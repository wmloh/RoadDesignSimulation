from abc import ABC, abstractmethod


class Tile(ABC):

    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.neighbours = list()

    def add_neighbours(self, tile):
        self.neighbours.append(tile)

    def get_coord(self):
        return (self.x, self.y)

    @abstractmethod
    def __str__(self):
        return ''

    @abstractmethod
    def traversable(self):
        return False