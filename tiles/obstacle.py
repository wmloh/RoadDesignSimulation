from tiles.tile import Tile


class Obst(Tile):

    def __init__(self, x, y):
        super(Obst, self).__init__(x, y)

    def __str__(self):
        return '%'

    def traversable(self):
        return False
