from tiles.traversable import Traversable


class Road(Traversable):

    def __init__(self, x, y, capacity):
        super(Road, self).__init__(x, y, capacity)

    def __str__(self):
        if len(self.cars) == 0:
            return '+'
        else:
            return '@'

    def traversable(self):
        return True