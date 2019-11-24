from tiles.tile import Tile


class Empty(Tile):
    __doc__ = '''
    Class that acts as a placeholder for potential construction of roads
    '''

    def __init__(self, x, y):
        '''
        Constructor for an Empty object

        :param x: Int - x-coordinate of the tile
        :param y: Int - y-coordinate of the tile
        '''
        super(Empty, self).__init__(x, y)

    def __str__(self):
        return ' '

    def traversable(self):
        '''
        Return whether cars can drive to this tile
        :return: Boolean
        '''
        return False
