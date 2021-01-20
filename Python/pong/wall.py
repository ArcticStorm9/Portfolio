import pygame
import random
class Wall:
    def __init__(self, x, y, width, height):
        self.mX = x
        self.mY = y
        self.mWidth = width
        self.mHeight = height
    def getX(self):
        return self.mX
    def getY(self):
        return self.mY
    def getWidth(self):
        return self.mWidth
    def getHeight(self):
        return self.mHeight
    def getRightX(self):
        return self.mX + self.mWidth
    def getBottomY(self):
        return self.mY + self.mHeight
    def draw(self, surface):
        color = (random.randint(0, 255), random.randint(0, 255), random.randint(0,255))
        myWall = pygame.Rect(self.mX, self.mY, self.mWidth, self.mHeight)
        pygame.draw.rect(surface, color, myWall, 0)