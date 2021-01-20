from text import Text
import pygame
class ScoreBoard:
    def __init__(self, x, y, width, height):
        self.mX = x
        self.mY = y
        self.mWidth = width
        self.mHeight = height
        self.mLeftScore = 0
        self.mRightScore = 0
        self.mServeStatus = 1
    def getX(self):
        return self.mX
    def getY(self):
        return self.mY
    def getWidth(self):
        return self.mWidth
    def getHeight(self):
        return self.mHeight
    def getLeftScore(self):
        return self.mLeftScore
    def getRightScore(self):
        return self.mRightScore
    def getServeStatus(self):
        return self.mServeStatus
    def isGameOver(self):
        if self.mServeStatus > 2:
            return True
        else:
            return False
    def scoreLeft(self):
        if self.mLeftScore < 9 and self.mRightScore < 9:
            self.mLeftScore += 1
            if self.mLeftScore == 9:
                self.mServeStatus = 3
    def scoreRight(self):
        if self.mLeftScore < 9 and self.mRightScore < 9:
            self.mRightScore += 1
            if self.mRightScore == 9:
                self.mServeStatus = 4
    def swapServe(self):
        if self.mServeStatus == 1:
            self.mServeStatus = 2
        elif self.mServeStatus == 2:
            self.mServeStatus = 1
    def draw(self, surface):
        leftScore = Text(str(self.mLeftScore), self.mX, self.mY)
        rightScore = Text(str(self.mRightScore), self.mX + self.mWidth, self.mY)
        leftScore.draw(surface)
        rightScore.draw(surface)