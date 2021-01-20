from ship import Ship
from rock import Rock
from star import Star
from random import randint
import sys
import pygame

class Asteroids:
    def __init__(self, world_width, world_height):
        self.mWorldWidth = world_width
        self.mWorldHeight = world_height
        self.mShip = Ship(self.mWorldWidth // 2, self.mWorldHeight // 2, self.mWorldWidth, self.mWorldHeight)
        self.mRocks = []
        for i in range(10):
            self.mRocks.append(Rock(randint(0, self.mWorldWidth), randint(0, self.mWorldHeight), self.mWorldWidth, self.mWorldHeight))
        self.mBullets = []
        self.mStars = []
        for i in range(20):
            self.mStars.append(Star(randint(0, self.mWorldWidth), randint(0, self.mWorldHeight), self.mWorldWidth, self.mWorldHeight))
        self.mObjects = [self.mShip]
        for rock in self.mRocks:
            self.mObjects.append(rock)
        for star in self.mStars:
            self.mObjects.append(star)
    
    def getWorldWidth(self):
        return self.mWorldWidth
    def getWorldHeight(self):
        return self.mWorldHeight
    def getShip(self):
        return self.mShip
    def getRocks(self):
        return self.mRocks
    def getBullets(self):
        return self.mBullets
    def getStars(self):
        return self.mStars
    def getObjects(self):
        return self.mObjects
    
    def turnShipLeft(self, delta_rotation):
        self.mShip.rotate(delta_rotation * -1)
    
    def turnShipRight(self, delta_rotation):
        self.mShip.rotate(delta_rotation)
        
    def accelerateShip(self, delta_velocity):
        self.mShip.accelerate(delta_velocity)
    
    def fire(self):
        if len(self.mBullets) < 3:
            b = self.mShip.fire()
            self.mBullets.append(b)
            self.mObjects.append(b)
            
    def evolveAllObjects(self, dt):
        for obj in self.mObjects:
            obj.evolve(dt)
    
    def collideShipAndBullets(self):
        if self.mShip.getActive():
            for bullet in self.mBullets:
                if bullet.hits(self.mShip):
                    self.mShip.setActive(False)
                    bullet.setActive(False)
            
    def collideShipAndRocks(self):
        if self.mShip.getActive():
            for rock in self.mRocks:
                if rock.hits(self.mShip):
                    self.mShip.setActive(False)
                    rock.setActive(False)
            
    def collideRocksAndBullets(self):
        for bullet in self.mBullets:
            for rock in self.mRocks:
                if rock.hits(bullet):
                    bullet.setActive(False)
                    rock.setActive(False)
    
    def removeInactiveObjects(self):
        nl = []
        for obj in self.mObjects:
            if obj.getActive():
                nl.append(obj)
        self.mObjects = nl
        nl = []
        for rock in self.mRocks:
            if rock.getActive():
                nl.append(rock)
        self.mRocks = nl
        nl = []
        for bullet in self.mBullets:
            if bullet.getActive():
                nl.append(bullet)
        self.mBullets = nl
                
    def evolve(self, dt):
        self.collideShipAndBullets()
        self.collideShipAndRocks()
        self.collideRocksAndBullets()
        self.removeInactiveObjects()
        self.evolveAllObjects(dt)
            
    def draw(self, surface):
        if self.mShip.getActive() and len(self.mRocks) > 0:
            rect = pygame.Rect(0, 0, self.mWorldWidth, self.mWorldHeight)
            pygame.draw.rect(surface, (0, 0, 0), rect, 0)
            for obj in self.mObjects:
                if obj.getActive():
                    obj.draw(surface)
        else:
            sys.exit( 0 )