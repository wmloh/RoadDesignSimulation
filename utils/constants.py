### CAR MOVE STATE VALUES ###
STEPPED = 0
BLOCKED = 1
REACHED = 2

### DIRECTIONS ###

# indexing of neighbours
NW = 0
N = 1
NE = 2
W = 3
E = 4
SW = 5
S = 6
SE = 7

# relative coordinates of neighbours
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

# constants-to-strings mapping
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

### REPRESENTATIONS

# representation of ground
HOME_VEC = [1, 0, 0, 0, 0]
HUB_VEC = [0, 1, 0, 0, 0]
OBST_VEC = [0, 0, 1, 0, 0]
ROAD_VEC = [0, 0, 0, 1, 0]
EMPTY_VEC = [0, 0, 0, 0, 1]

### SCORING

# cost values
DEFAULT = -1
NUM_TILES = 8
ORTHO_COST = 10
DIAG_COST = 14


def cost_function(x, y, desX, desY):
    '''
    Computes an approximated Euclidean distance between origin and destination

    :param x: Int - origin x-coordinate
    :param y: Int - origin y-coordinate
    :param desX: Int - destination x-coordinate
    :param desY: Int - destination y-coordinate
    :return: Int - approximated Euclidean distance as cost
    '''
    deltaX = abs(x - desX)
    deltaY = abs(y - desY)

    cost = min(deltaX, deltaY) * DIAG_COST
    cost += (max(deltaX, deltaY) - cost) * ORTHO_COST

    return cost
