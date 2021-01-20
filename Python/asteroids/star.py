from circle import Circle
from random import randint

class Star( Circle ):
    def __init__(self, x, y, world_width, world_height):
        Circle.__init__(self, x, y, 0, 0, 0, 2, world_width, world_height)
        self.mBrightness = randint(0, 255)
        
    def getBrightness(self):
        return self.mBrightness
    
    def setBrightness(self, brightness):
        if brightness >= 0 and brightness <= 255:
            self.mBrightness = brightness
            self.setColor((brightness, brightness, brightness))
    
    def evolve(self, dt):
        var = randint(1, 3)
        if var == 1:
            self.setBrightness(self.mBrightness + 10)
        elif var == 2:
            self.setBrightness(self.mBrightness - 10)