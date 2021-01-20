from polygon import Polygon
import random
import math

class Rock( Polygon ):
    def __init__(self, x, y, world_width, world_height):
        Polygon.__init__(self, x, y, 0, 0, random.uniform(0, 359.9), world_width, world_height)
        self.mSpinRate = random.randint(-90, 90)
        self.accelerate(random.randint(10, 20))
        self.setPolygon(self.createRandomPolygon(random.randint(10, 40), random.randint(7, 12)))
        
    def createRandomPolygon(self, radius, number_of_points):
        pointlist = []
        theta = 2 * math.pi / number_of_points
        for i in range(number_of_points):
            r = random.uniform(radius * 0.7, radius * 1.3)
            new_x = r * math.cos(theta * i)
            new_y = r * math.sin(theta * i)
            pointlist.append([new_x, new_y])
        return pointlist
    
    def getSpinRate(self):
        return self.mSpinRate
    
    def setSpinRate(self, spin_rate):
        self.mSpinRate = spin_rate
        
    def evolve(self, dt):
        self.move(dt)
        self.rotate(self.mSpinRate * dt)