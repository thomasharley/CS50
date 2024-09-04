# Object oriented programming practice.

class Jar:
    def __init__(self, capacity=12):
        self.capacity = capacity
        self.size = 0

    def __str__(self):
        return "🍪" * self.size

    def deposit(self, n):
        self.size = self.size + n
        if self.size > self.capacity:
            raise ValueError("Too many cookies!")

    def withdraw(self, n):
        self.size = self.size - n
        if self.size < 0:
            raise ValueError("Cannot have negative cookies!")

    # in the getters/ setters, need to put underscores to mark variables as different

    @property # getter
    def capacity(self):
        return self._capacity
    
    @capacity.setter # setter
    def capacity(self, capacity):
        if capacity < 0 or capacity > 12:
            raise ValueError("Invalid Capacity!")
        self._capacity = capacity

    @property # getter
    def size(self):
        return self._size
    
    @size.setter
    def size(self, size):
        if size > self.capacity:
            raise ValueError("Invalid Size!")
        self._size = size


def main(): # for testing the class

    jar = Jar()

    print(str(jar))

    jar.deposit(13)
    print(str(jar))

    #jar.withdraw(5)

main()






