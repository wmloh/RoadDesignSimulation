from utils.constants import STEPPED, KEYMAPPING


class Car:
    cur_id = 0
    all_cars = list()

    def __init__(self, curX, curY, desX, desY, hub, cur_road, id=None):
        self.curX = curX
        self.curY = curY
        self.desX = desX
        self.desY = desY
        self.route = None  # deque
        self.hub = hub
        self.cur_road = cur_road

        if id is None:
            self.id = Car.cur_id
            Car.cur_id += 1
        else:
            self.id = id

        Car.all_cars.append(self)

    def get_route(self, pathfinder):
        self.route = pathfinder.find_path(self.curX, self.curY, self.desX, self.desY, self)

        if len(self.route) == 0:
            raise RuntimeError(f'Ensure that car at {self.curX, self.curY} has access to roads')

        return True

    def get_dest(self):
        return (self.desX, self.desY)

    def move(self):
        if not self.route:
            raise RuntimeError(f'Route is empty but Car.move is called on {self.curX, self.curY}')

        direction = self.route[0]
        index = direction if direction <= 3 else direction + 1

        state = self.cur_road.send_car(index, self)
        if state == STEPPED:
            self.route.popleft()
            deltaX, deltaY = KEYMAPPING[direction]
            self.curX += deltaX
            self.curY += deltaY

        return state

    def reached(self):
        # TODO: Add completion action
        print(f'Car {self.id} has reached destination at {self.desX, self.desY}')

    def __str__(self):
        output = f'Coordinates: {self.curX, self.curY}\n' \
                 f'Destination: {self.desX, self.desY}\n' \
                 f'Path distance: {len(self.route)}'
        return output


