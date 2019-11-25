from utils.constants import BLOCKED, REACHED


class Timestep:
    __doc__ = '''
    Class that handles the sequential movement of every car active in the simulation
    '''

    def __init__(self, simulation):
        '''
        Constructor for Timestep

        :param simulation: Simulation - reference to simulation object
        '''
        self.simulation = simulation
        self.cars = list()

    def attach(self, car_reference):
        '''
        Appends a reference to the active car that has recently turned active.

        :param car_reference: Car - reference to the car
        :return: None
        '''
        self.cars.append(car_reference)

    def detach(self, car_reference):
        '''
        Removes a car from Timestep (turns it inactive)

        :param car_reference: Car - reference to the car to be removed
        :return: None
        '''
        self.cars.remove(car_reference)

    def notify_observer(self):
        '''
        Moves every car sequentially depending on the order it was attached.

        :return: None
        '''
        for car in self.cars:
            state = car.move()
            if state == BLOCKED:
                print('Traffic congestion')
            elif state == REACHED:
                self.detach(car)

    def get_size(self):
        '''
        Gets the number of active cars for convenience.

        :return: Int - number of active cars
        '''
        return len(self.cars)

    def __str__(self):
        car_list = list()
        for idx, car in enumerate(self.cars):
            car_list.append(f'[{idx}]\n{car[idx]}')
        return ''.join(car_list)
