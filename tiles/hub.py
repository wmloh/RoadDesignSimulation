from tiles.traversable import Traversable


class Hub(Traversable):

    def __init__(self, x, y, capacity):
        super(Hub, self).__init__(x, y, capacity)

    def __str__(self):
        return 'h'

    def traversable(self):
        return False