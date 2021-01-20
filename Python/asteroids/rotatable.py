import math
from movable import Movable

class Rotatable( Movable ):
    def __init__(self, x, y, dx, dy, rotation, world_width, world_height):
        Movable.__init__(self, x, y, dx, dy, world_width, world_height)
        self.mRotation = rotation
    
    def getRotation(self):
        return self.mRotation
    
    def rotate(self, delta_rotation):
        self.mRotation += delta_rotation
        if self.mRotation >= 360:
            self.mRotation -= 360
        elif self.mRotation < 0:
            self.mRotation += 360
            
    def splitDeltaVIntoXAndY(self, rotation, delta_velocity):
        x = delta_velocity * math.cos(math.radians(rotation))
        y = delta_velocity * math.sin(math.radians(rotation))
        return [x, y]
    
    def accelerate(self, delta_velocity):
        speed = self.splitDeltaVIntoXAndY(self.mRotation, delta_velocity)
        self.mDX += speed[0]
        self.mDY += speed[1]
        
    def rotatePoint(self, x, y):
        r = math.sqrt(x * x + y * y)
        theta = math.atan2(y, x) + math.radians(self.mRotation)
        new_x = r * math.cos(theta)
        new_y = r * math.sin(theta)
        return [new_x, new_y]
    
    def translatePoint(self, x, y):
        new_x = x + self.mX
        new_y = y + self.mY
        return [new_x, new_y]
    
    def rotateAndTranslatePoint(self, x, y):
        rotated = self.rotatePoint(x,y)
        translated = self.translatePoint(rotated[0], rotated[1])
        return translated[0], translated[1]
    
    def rotateAndTranslatePointList(self, point_list):
        new_points = []
        for point in point_list:
            new_points.append(self.rotateAndTranslatePoint(point[0], point[1]))
        return new_points