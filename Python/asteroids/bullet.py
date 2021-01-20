from circle import Circle

class Bullet( Circle ):
    def __init__(self, x, y, dx, dy, rotation, world_width, world_height):
        Circle.__init__(self, x, y, dx, dy, rotation, 3, world_width, world_height)
        self.mAge = 0
        self.accelerate(100)
        self.move(0.1)
        
    def getAge(self):
        return self.mAge
        
    def setAge(self, age):
        self.mAge = age
        
    def evolve(self, dt):
        self.move(dt)
        self.mAge += dt
        if self.mAge > 6:
            self.setActive(False)
        