class PriorityQueue:
    __doc__ = '''
    Class for a priority queue with customizations for the A* search algorithm (using heaps)
    
    Time complexity:
    * push - O(log n)
    * pop - O(log n)
    '''

    def __init__(self, key=lambda x: x[0]):
        self.container = list()
        self.key = key

    def push(self, obj):
        container = self.container
        key = self.key

        container.append(obj)
        length = len(container)
        k = length - 1
        while (k - 1) // 2 >= 0 and key(container[(k - 1) // 2]) > key(container[k]):
            parent_idx = (k - 1) // 2
            container[k], container[parent_idx] = container[parent_idx], container[k]
            k = parent_idx

    def pop(self):
        container = self.container
        key = self.key

        container[0], container[-1] = container[-1], container[0]
        obj = container.pop()

        length = len(container)
        k = 0
        while 2 * k + 1 < length:
            j = 2 * k + 1

            if j + 1 < length and key(container[j + 1]) < key(container[j]):
                j += 1

            if key(container[j]) >= key(container[k]):
                break

            container[j], container[k] = container[k], container[j]
            k = j

        return obj

    def find(self, item, key=lambda x: x[1]):
        for ele in self.container:
            if key(ele) == item:
                return ele
        return None

    def empty(self):
        return len(self.container) == 0

    def __iter__(self):
        return self.container.__iter__()

    def __len__(self):
        return len(self.container)

    def __contains__(self, item):
        return item in self.container
