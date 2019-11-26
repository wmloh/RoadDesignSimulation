from utils.constants import STEPPED, KEYMAPPING


class Car:
    __doc__ = '''
    An agent with the logic to navigate through the simulation to reach a destination 
    '''

    # ID to keep track of default naming of Cars
    cur_id = 0
    # stores references to all Cars in existence
    all_cars = list()

    def __init__(self, curX, curY, desX, desY, hub, cur_road, id=None):
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

        if id is None:
            self.id = Car.cur_id
            Car.cur_id += 1
        else:
            self.id = id

        Car.all_cars.append(self)

    def get_route(self, pathfinder):
        '''
        Uses a PathFinder object to get the route.

        Will raise a RuntimeError if no route can be found.

        :param pathfinder: PathFinder - reference to a pathfinder object
        :return: True
        '''
        self.route = pathfinder.find_path(self.curX, self.curY, self.desX, self.desY, self)

        if not self.route:
            # TODO: Consider changing to a boolean signal
            raise RuntimeError(f'Ensure that car at {self.curX, self.curY} has access to roads')

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

