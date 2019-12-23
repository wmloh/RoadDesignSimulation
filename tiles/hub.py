from tiles.traversable import Traversable


class Hub(Traversable):
    __doc__ = '''
    Class that represents a destination of a Car
    '''

    def __init__(self, x, y, capacity):
        '''
        Constructor for a Hub

        :param x: Int - x-coordinate of the tile
        :param y: Int - y-coordinate of the tile
        :param capacity: Int - maximum number of cars the Home can support
        '''
        super(Hub, self).__init__(x, y, capacity)

    def to_vector(self):
        '''
        Returns a vector representation of this tile
        :return: list(Int) - vector of 5 dimensions
        '''
        return [0, self.capacity, 0, 0, 0]

    def __str__(self):
        return 'h'

    def traversable(self):
        '''
        Return whether cars can drive to this tile
        :return: Boolean
        '''
        return False
