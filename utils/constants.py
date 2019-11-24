# car state values
STEPPED = 0
BLOCKED = 1
REACHED = 2

# directions
NW = 0
N = 1
NE = 2
W = 3
E = 4
SW = 5
S = 6
SE = 7

KEYMAPPING = [
    (-1, -1),
    (0, -1),
    (1, -1),
    (-1, 0),
    (1, 0),
    (-1, 1),
    (0, 1),
    (1, 1)
]

INVERSE_DIR = {
    NW: 'NW',
    N: 'N',
    NE: 'NE',
    W: 'W',
    E: 'E',
    SW: 'SW',
    S: 'S',
    SE: 'SE'
}

# cost values
DEFAULT = -1
NUM_TILES = 8
ORTHO_COST = 10
DIAG_COST = 14


def cost_function(x, y, desX, desY):
    deltaX = abs(x - desX)
    deltaY = abs(y - desY)

    cost = min(deltaX, deltaY) * DIAG_COST
    cost += (max(deltaX, deltaY) - cost) * ORTHO_COST

    return cost
