from abc import ABC, abstractmethod


class Tile(ABC):
    __doc__ = '''
    Abstract class for a generic Tile that provides some methods and enforces implementation
    of certain methods
    '''

    def __init__(self, x, y):
        '''
        Abstract constructor for a Tile

        :param x: Int - x-coordinate of the tile
        :param y: Int - y-coordinate of the tile
        '''
        self.x = x
        self.y = y
        self.neighbours = list()

    def add_neighbours(self, tile):
        '''
        Appends neighbours into the Tile

        :param tile: Tile - reference to a neighbouring tile
        :return: None
        '''
        self.neighbours.append(tile)

    def get_coord(self):
        '''
        Returns the coordinates

        :return: tuple - x,y-coordinates of the Tile
        '''
        return (self.x, self.y)

    @abstractmethod
    def __str__(self):
        return ''

    @abstractmethod
    def traversable(self):
        '''
        Return whether cars can drive to this tile
        :return: Boolean
        '''
        return False