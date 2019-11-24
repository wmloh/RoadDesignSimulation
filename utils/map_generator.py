from tiles.empty import Empty
from tiles.home import Home
from tiles.hub import Hub
from tiles.obstacle import Obst
from tiles.road import Road
import pandas as pd


def generate_map(map_fp, profile_fp, order_fp, waiting):
    ground = _to_tiles(map_fp, profile_fp)
    _to_order(order_fp, ground, waiting)
    return ground


def _attach_neighbours(ground, lenX, lenY):
    x = 0
    y = 0

    for row in ground:
        for tile in row:
            for i in range(x - 1, x + 2):
                for j in range(y - 1, y + 2):
                    if 0 <= i < lenX and 0 <= j < lenY and (i != x or j != y):
                        tile.add_neighbours(ground[i][j])
                    else:
                        tile.add_neighbours(None)
            y += 1
        x += 1
        y = 0


def _to_tiles(map_fp, profile_fp):
    ground = list()

    with open(map_fp, 'r') as f:
        lines = f.readlines()
    lines = map(lambda x: x.rstrip('\n'), lines)

    with open(profile_fp, 'r') as f:
        for col, line in enumerate(lines):
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

    _attach_neighbours(ground, row, col)

    return ground


def _to_order(order_fp, ground, waiting, verbose=True):
    df = pd.read_csv(order_fp)

    for row in df.itertuples():
        start_x = row.start_x
        start_y = row.start_y

        home = ground[start_y][start_x]
        if not isinstance(home, Home):
            raise IOError(f'Tile at {start_x, start_y} is not of type Home, given {type(home)}')

        end_x = row.end_x
        end_y = row.end_y
        hub = ground[end_y][end_x]
        if not isinstance(hub, Hub):
            raise IOError(f'Tile at {end_x, end_y} is not of type Hub, given {type(hub)}')

        if verbose:
            print(f'Home: {start_x, start_y} --> Hub: {end_x, end_y}')

        waiting.attach(row.timestep, end_x, end_y, home, hub)
