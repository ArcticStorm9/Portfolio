import math

class Movable:
    def __init__(self, x, y, dx, dy, world_width, world_height):
        self.mX = x
        self.mY = y
        self.mDX = dx
        self.mDY = dy
        self.mWorldWidth = world_width
        self.mWorldHeight = world_height
        self.mActive = True
        
    def getX(self):
        return self.mX
    def getY(self):
        return self.mY
    def getDX(self):
        return self.mDX
    def getDY(self):
        return self.mDY
    def getWorldWidth(self):
        return self.mWorldWidth
    def getWorldHeight(self):
        return self.mWorldHeight
    def getActive(self):
        return self.mActive
    
    def setActive(self, active):
        self.mActive = active
        
    def hits(self, other):
        d = math.sqrt((other.getX()-self.getX())**2 + (other.getY()-self.getY())**2)
        if other.getRadius() + self.getRadius() >= d:
            return True
        else:
            return False
    
    def move(self, dt):
        self.mX += self.mDX * dt
        self.mY += self.mDY * dt
        if self.mX >= self.mWorldWidth:
            self.mX -= self.mWorldWidth
        elif self.mX < 0:
            self.mX += self.mWorldWidth
        if self.mY >= self.mWorldHeight:
            self.mY -= self.mWorldHeight
        elif self.mY < 0:
            self.mY += self.mWorldHeight
    
    def accelerate(self, delta_velocity):
        raise NotImplementedError
    
    def evolve(self, dt):
        raise NotImplementedError
    
    def draw(self, surface):
        raise NotImplementedError
    
    def getRadius(self):
        raise NotImplementedError