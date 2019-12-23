from tiles.traversable import Traversable


class Road(Traversable):
    __doc__ = '''
    Class that represents a road that allows cars to drive on and be contained in the road object
    '''

    def __init__(self, x, y, capacity):
        '''
        Constructor for a Road

        :param x: Int - x-coordinate of the tile
        :param y: Int - y-coordinate of the tile
        :param capacity: Int - maximum number of cars the Road can support
        '''
        super(Road, self).__init__(x, y, capacity)

    def to_vector(self):
        '''
        Returns a vector representation of this tile
        :return: list(Int) - vector of 5 dimensions
        '''
        return [0, 0, 0, self.capacity, 0]

    def __str__(self):
        if len(self.cars) == 0:
            return '+'
        else:
            return '@'

    def traversable(self):
        '''
        Return whether cars can drive to this tile
        :return: Boolean
        '''
        return True
