from tiles.tile import Tile


class Empty(Tile):

    def __init__(self, x, y):
        super(Empty, self).__init__(x, y)

    def __str__(self):
        return ' '

    def traversable(self):
        return False