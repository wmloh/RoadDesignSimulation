from utils.constants import BLOCKED, REACHED


class Timestep:

    def __init__(self, simulation):
        self.simulation = simulation
        self.cars = list()

    def attach(self, car_reference):
        self.cars.append(car_reference)

    def detach(self, car_reference):
        self.cars.remove(car_reference)

    def notify_observer(self):
        for car in self.cars:
            state = car.move()
            if state == BLOCKED:
                print('Traffic congestion')
            elif state == REACHED:
                self.detach(car)

    def get_size(self):
        return len(self.cars)

    def __str__(self):
        car_list = list()
        for idx, car in enumerate(self.cars):
            car_list.append(f'[{idx}]\n{car[idx]}')
        return ''.join(car_list)
