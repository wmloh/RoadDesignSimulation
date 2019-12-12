from utils.constants import STEPPED, KEYMAPPING


class Car:
    __doc__ = '''
    An agent with the logic to navigate through the simulation to reach a destination 
    '''

    # ID to keep track of default naming of Cars
    cur_id = 0
    # stores references to all Cars in existence
    all_cars = list()

    def __init__(self, curX, curY, desX, desY, hub, cur_road, car_id=None):
        '''
        Constructor for a Car agent

        :param curX: Int - current x-coordinate of the car
        :param curY: Int - current y-coordinate of the car
        :param desX: Int - destination x-coordinate
        :param desY: Int - destination y-coordinate
        :param hub: Hub - reference to the destination hub
        :param cur_road: Home - home that contains the car initially (can be Traversable during the simulation)
        :param id: None/String/Int - a printable object used as identification of a car
                                     (None means a default id will be assigned)
        '''
        self.curX = curX
        self.curY = curY
        self.desX = desX
        self.desY = desY
        self.route = None  # contains a deque object when route is obtained
        self.hub = hub
        self.cur_road = cur_road

        if car_id is None:
            self.id = Car.cur_id
            Car.cur_id += 1
        else:
            self.id = car_id

        Car.all_cars.append(self)

    def get_route(self, pathfinder):
        '''
        Uses a PathFinder object to get the route.

        :param pathfinder: PathFinder - reference to a pathfinder object
        :return: Boolean - returns True if and only if there is a path to destination
        '''
        self.route = pathfinder.find_path(self.curX, self.curY, self.desX, self.desY, self)

        if not self.route:
            return False

        return True

    def get_dest(self):
        '''
        Returns a tuple representation of car coordinates for convenience.

        :return: tuple(Int, Int)
        '''
        return (self.desX, self.desY)

    def move(self):
        '''
        Moves the car by calling the Traversable.send_car method with the direction stored in
        the route container.

        :return: Int - state representation of result of the move
        '''
        if not self.route:
            raise RuntimeError(f'Route is empty but Car.move is called on {self.curX, self.curY}')

        direction = self.route[0]
        # calibrates the direction because the discrepancy between the neighbours and direction
        index = direction if direction <= 3 else direction + 1

        state = self.cur_road.send_car(index, self)
        if state == STEPPED:
            self.route.popleft()  # pop because the route has been executed

            # updates coordinates
            deltaX, deltaY = KEYMAPPING[direction]
            self.curX += deltaX
            self.curY += deltaY

        return state

    def reached(self):
        # TODO: Add completion action
        print(f'Car {self.id} has reached destination at {self.desX, self.desY}')

    def __str__(self):
        output = f'Car ({self.id})\n' \
                 f'Coordinates: {self.curX, self.curY}\n' \
                 f'Destination: {self.desX, self.desY}\n' \
                 f'Path distance: {len(self.route)}'
        return output

    @classmethod
    def delete_all(cls):
        '''
        Removes all car in the current simulation, including references of the car in Traversable tiles

        :return: None
        '''
        for car in cls.all_cars:
            car.cur_road.cars.clear()
            del car

        cls.all_cars.clear()
        cls.cur_id = 0
