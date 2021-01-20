import pygame
import random
class Paddle:
    def __init__(self, x, y, width, height, speed, min_y, max_y):
        self.mX = x
        self.mY = y
        self.mWidth = width
        self.mHeight = height
        self.mSpeed = speed
        self.mMinY = min_y
        self.mMaxY = max_y
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
    def getSpeed(self):
        return self.mSpeed
    def getMinY(self):
        return self.mMinY
    def getMaxY(self):
        return self.mMaxY
    def setPosition(self,y):
        if y != self.getY():
            self.mY = y
            if self.getY() <= self.getMinY():
                self.mY = self.getMinY()
            elif self.getBottomY() >= self.getMaxY():
                self.mY = self.getMaxY() - self.getHeight()
    def moveUp(self,dt):
        new_y = self.getY() - self.getSpeed() * dt
        self.setPosition(new_y)
    def moveDown(self,dt):
        new_y = self.getY() + self.getSpeed() * dt
        self.setPosition(new_y)
    def draw(self, surface):
        color = (random.randint(0, 255), random.randint(0, 255), random.randint(0,255))
        myPaddle = pygame.Rect(self.mX, self.mY, self.mWidth, self.mHeight)
        pygame.draw.rect(surface, color, myPaddle, 0)