class HashTable(object):
    def __init__(self, length = 4):
        self.array = [None] * length
    
    def hash(self, key):
        length = len(self.array)
        print("Hash Key: %s" % hash(key))
        return hash(key) % length

    def add(self, key, value):
        if self.is_full():
            self.double()

        index = self.hash(key)
        if self.array[index] is not None:
            for kvp in self.array[index]:
                if kvp[0] == key:
                    kvp[1] = value
                    break
                else:
                    self.array[index].append([key, value])
        else:
            self.array[index] = []
            self.array[index].append([key, value])

    def get(self, key):
        index = self.hash(key)
        if self.array[index] is None:
            raise KeyError()
        else:
            for kvp in self.array[index]:
                if kvp[0] == key:
                    return kvp[1]
            raise KeyError()

    def is_full(self):
        items = 0
        for item in self.array:
            if item is not None:
                items += 1
        return items > len(self.array) / 2

    def double(self):
        ht2 = HashTable(length = len(self.array) * 2)
        for i in range(len(self.array)):
            if self.array[i] is None:
                continue

            for kvp in self.array[i]:
                ht2.add(kvp[0], kvp[1])

        self.array = ht2.array

ht = HashTable()
ht.add('Luca', 1)