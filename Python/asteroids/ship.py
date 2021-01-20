from polygon import Polygon
import bullet

class Ship( Polygon ):
    def __init__(self, x, y, world_width, world_height):
        Polygon.__init__(self, x, y, 0, 0, 0, world_width, world_height)
        self.setPolygon([(10, 0), (-10, 10), (-10, -10)])
        
    def fire(self):
        (x, y) = self.rotateAndTranslatePoint(self.mOriginalPolygon[0][0], self.mOriginalPolygon[0][1])
        return bullet.Bullet(x, y, float(self.getDX()), float(self.getDY()), float(self.getRotation()), float(self.getWorldWidth()), float(self.getWorldHeight()))
        
    def evolve(self, dt):
        self.move(dt)