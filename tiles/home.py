from tiles.traversable import Traversable
from agents.car import Car


class Home(Traversable):

    def __init__(self, x, y, capacity):
        super(Home, self).__init__(x, y, capacity)

    def load_car(self, desX, desY, pathfinder, hub):
        car = Car(self.x, self.y, desX, desY, hub, self)
        car.get_route(pathfinder)
        self.cars.append(car)

    def __str__(self):
        if len(self.cars) == 0:
            return 'H'
        else:
            return '@'

    def traversable(self):
        return False
