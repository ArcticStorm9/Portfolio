from rotatable import Rotatable
import pygame

class Circle( Rotatable ):
    def __init__(self, x, y, dx, dy, rotation, radius, world_width, world_height):
        Rotatable.__init__(self, x, y, dx, dy, rotation, world_width, world_height)
        self.mRadius = radius
        self.mColor = (255,255,255)
        
    def getRadius(self):
        return self.mRadius
    def getColor(self):
        return self.mColor
    
    def setRadius(self, radius):
        if radius >= 1:
            self.mRadius = radius
            
    def setColor(self, color):
        self.mColor = color
        
    def draw(self, surface):
        pygame.draw.circle(surface, self.mColor, (int(self.mX), int(self.mY)), int(self.mRadius))