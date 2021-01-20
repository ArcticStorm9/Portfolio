from rotatable import Rotatable
import math
import pygame

class Polygon( Rotatable ):
    def __init__(self, x, y, dx, dy, rotation, world_width, world_height):
        Rotatable.__init__(self, x, y, dx, dy, rotation, world_width, world_height)
        self.mOriginalPolygon = []
        self.mColor = (255, 255, 255)
    
    def getPolygon(self):
        return self.mOriginalPolygon
    def getColor(self):
        return self.mColor
    
    def setPolygon(self, newPosition):
        self.mOriginalPolygon = newPosition
    
    def setColor(self, newColor):
        self.mColor = newColor
    
    def getRadius(self):
        total = 0
        if len(self.mOriginalPolygon) == 0:
            return 0
        else:
            for point in self.mOriginalPolygon:
                total += math.sqrt(point[0]**2 + point[1]**2)
            return total / len(self.mOriginalPolygon)
        
    def draw(self, surface):
        shape = self.mOriginalPolygon[::]
        shape = self.rotateAndTranslatePointList(shape)
        pygame.draw.polygon(surface, self.mColor, shape, 1)