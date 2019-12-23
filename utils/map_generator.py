from tiles.empty import Empty
from tiles.home import Home
from tiles.hub import Hub
from tiles.obstacle import Obst
from tiles.road import Road
import pandas as pd
import numpy as np


def generate_map(map_fp, profile_fp, order_fp, waiting, sample=False):
    '''
    Generates a 2D-array object of tiles from reading the text files specified.

    :param map_fp: String - path to text file containing map layout
    :param profile_fp: String - path to text file containing details of each Tile (capacity)
    :param order_fp: String/None - path to text file containing car origin and destination (None if sample=True)
    :param waiting: Waiting - reference to waiting object
    :param sample: Boolean - enable random sampling (as opposed to loading order_fp)
    :return: np.ndarray - 2D array of tiles for the simulation
    '''
    # forms the ground
    ground = _to_tiles(map_fp, profile_fp)

    if sample:
        sampling_func = _to_order_by_sampling(ground, waiting)

        return np.array(ground), sampling_func
    else:
        # sets the car creation order
        _to_order_from_file(order_fp, ground, waiting)

        return np.array(ground)


def _attach_neighbours(ground, lenX, lenY):
    '''
    Assigns directly adjacent neighbours to each tile.

    :param ground: np.ndarray - 2D array of tiles
    :param lenX: Int - number of columns in map
    :param lenY: Int - number of rows in map
    :return: None
    '''
    x = 0
    y = 0

    for row in ground:
        for tile in row:
            # iterates through all 9 positions around and including itself
            for i in range(x - 1, x + 2):
                for j in range(y - 1, y + 2):
                    if 0 <= i < lenX and 0 <= j < lenY and (i != x or j != y):
                        # check for out of bounds case
                        tile.add_neighbours(ground[i][j])
                    else:  # case where the neighbour is itself
                        tile.add_neighbours(None)
            y += 1
        x += 1
        y = 0


def _to_tiles(map_fp, profile_fp):
    '''
    Reads the map and profile text file and create implemented Tile objects into the
    corresponding position and with the specified properties.

    :param map_fp: String - path to text file containing map layout
    :param profile_fp: String - path to text file containing details of each Tile (capacity)
    :return: list(list(Tile)) - 2D arrays of tiles matching position and properties
    '''
    ground = list()

    # reads the entire map
    with open(map_fp, 'r') as f:
        lines = f.readlines()

    # remove newline characters
    lines = map(lambda x: x.rstrip('\n'), lines)

    with open(profile_fp, 'r') as f:
        for col, line in enumerate(lines):
            # reads profile file as a stream
            profile_line = f.readline()

            cols = list()
            for row, char in enumerate(line):
                if char == '%':
                    cols.append(Obst(row, col))
                elif char == ' ':
                    cols.append(Empty(row, col))
                elif char == 'H':
                    cols.append(Home(row, col, int(profile_line[row])))
                elif char == 'h':
                    cols.append(Hub(row, col, int(profile_line[row])))
                elif char == '+':
                    cols.append(Road(row, col, int(profile_line[row])))
                else:
                    raise IOError(f'Unrecognized symbol detected on the map: {char}')

            ground.append(cols)

    # assigns all neighbours
    _attach_neighbours(ground, row, col)

    return ground


def _to_order_from_file(order_fp, ground, waiting, verbose=False):
    '''
    Attaches ordering of creation of cars to the waiting object based on
    the input text file

    :param order_fp: String - path to text file containing car origin and destination
    :param ground: list(list(Tile)) - 2D array of tiles
    :param waiting: Waiting - reference to simulation waiting object
    :param verbose: Boolean - if True, prints each car's origin and destination
    :return: None
    '''
    df = pd.read_csv(order_fp)

    for row in df.itertuples():
        start_x = row.start_x
        start_y = row.start_y

        home = ground[start_y][start_x]
        if not isinstance(home, Home):  # type check for Home
            raise IOError(f'Tile at {start_x, start_y} is not of type Home, given {type(home)}')

        end_x = row.end_x
        end_y = row.end_y
        hub = ground[end_y][end_x]
        if not isinstance(hub, Hub):  # type check for Hub
            raise IOError(f'Tile at {end_x, end_y} is not of type Hub, given {type(hub)}')

        if verbose:
            print(f'Home: {start_x, start_y} --> Hub: {end_x, end_y}')

        waiting.attach(row.timestep, end_x, end_y, home, hub)


def _to_order_by_sampling(ground, waiting):
    '''
    Builds a sampling function that can be called to sample from the given homes and hubs and automatically
    loads to the Waiting object

    :param ground: array-like - 2D array of tiles
    :param waiting: Waiting - reference to the Waiting object
    :return: (Int) => None - sampling function
    '''

    sampling_homes = list()
    sampling_hubs = list()

    # identify homes and hubs that will be sampled from
    for col, line in enumerate(ground):
        for row, tile in enumerate(line):
            if isinstance(tile, Home):
                sampling_homes.append(tile)
            elif isinstance(tile, Hub):
                sampling_hubs.append(tile)

    # define sampling function
    def sample(capacity_scale=0.25, beta=2):
        '''
        Loads the Waiting object with the cars.

        Note: It is the caller's responsibility to clear the waiting object

        :param capacity_scale: float - scale parameter for mean of Poisson distribution
        :param beta: float - scale parameter for exponential distribution to get timestep
        :return: None
        '''
        for home in sampling_homes:
            # Poisson sampling
            num_drivers = np.random.poisson(home.capacity * capacity_scale)

            # random determines hub(s) and timestep(s) with uniform and exponential distribution respectively
            hubs = np.random.choice(sampling_hubs, size=(num_drivers,))
            timesteps = np.random.exponential(beta, size=(num_drivers,)).astype(int)

            for hub, ts in zip(hubs, timesteps):
                waiting.attach(ts, hub.x, hub.y, home, hub)

    return sample
