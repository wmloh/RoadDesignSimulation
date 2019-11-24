from tiles.tile import Tile


class Obst(Tile):
    __doc__ = '''
    Class that represents an obstacle and does not allow interaction with cars
    '''

    def __init__(self, x, y):
        '''
        Constructor for an Obst

        :param x: Int - x-coordinate of the tile
        :param y: Int - y-coordinate of the tile
        '''
        super(Obst, self).__init__(x, y)

    def __str__(self):
        return '%'

    def traversable(self):
        '''
        Return whether cars can drive to this tile
        :return: Boolean
        '''
        return False
