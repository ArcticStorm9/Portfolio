#Ian Shakespeare MWF 10am, PS: Had trouble making loops so I made it the hard way...
import pygame
import froggerlib
from random import randint

class Frogger:

    def __init__( self, width, height ):
        self.mWidth = width
        self.mHeight = height
        self.mGameOver = False
        #Initializes Stages and Frog
        stage1, lane_size, half_gap, object_height = 11, 50, 5, 40
        frog_speed = 20
        x, y = self.mWidth/2, stage1 * lane_size + half_gap
        self.mFrog = froggerlib.Frog( x, y, object_height, object_height, x, y, frog_speed, lane_size, lane_size )
        self.mStage1 = froggerlib.Stage( 0, stage1 * lane_size, self.mWidth, lane_size )
        self.mStage2 = froggerlib.Stage( 0, stage1 * lane_size - 300, self.mWidth, lane_size * 2 )
        #Initializes Roads and Cars
        road = 10
        w, h = 90, 40
        x, y = self.mWidth - w, road * lane_size + half_gap
        self.mCar1 = froggerlib.Car( randint(0, self.mWidth), y, w, h, -w, y, 10 )
        x, y = 0, road * lane_size
        self.mRoad1 = froggerlib.Road(x, y, self.mWidth, lane_size)
        road = 10
        w, h = 60, 40
        x, y = self.mWidth - w, (road * lane_size + half_gap) - 50
        self.mCar2 = froggerlib.Car( randint(0, self.mWidth), y, w, h, self.mWidth, y, 15 )
        x, y = 0, (road * lane_size + half_gap) - 50
        self.mRoad2 = froggerlib.Road(x, y, self.mWidth, lane_size)
        road = 10
        w, h = 40, 40
        x, y = self.mWidth - w, (road * lane_size + half_gap) - 100
        self.mCar3 = froggerlib.Car( randint(0, self.mWidth), y, w, h, -w, y, 25 )
        x, y = 0, (road * lane_size + half_gap) - 100
        self.mRoad3 = froggerlib.Road(x, y, self.mWidth, lane_size)
        road = 10
        w, h = 60, 40
        x, y = self.mWidth - w, (road * lane_size + half_gap) - 150
        self.mCar4 = froggerlib.Car( randint(0, self.mWidth), y, w, h, self.mWidth, y, 20 )
        x, y = 0, (road * lane_size + half_gap) - 150
        self.mRoad4 = froggerlib.Road(x, y - 5, self.mWidth, lane_size + 5)
        #Initializes Water and Logs
        lane_size = 50
        object_size = 40
        half_gap = 5
        x, y = 0, 4 * lane_size
        w, h = self.mWidth, lane_size
        self.mWater1 = froggerlib.Water(x, y, w, h)
        x, y = 0, 4 * lane_size + half_gap
        w, h = 4 * lane_size, object_size
        dx, dy = self.mWidth, y
        speed = randint(5, 15)
        self.mLog1 = froggerlib.Log(randint(0, self.mWidth), y, w, h, 0 - w, dy, speed)
        lane_size = 50
        object_size = 40
        half_gap = 5
        x, y = 0, 4 * lane_size
        w, h = self.mWidth, lane_size
        self.mWater2 = froggerlib.Water(x, y - 50, w, h)
        x, y = 0, 4 * lane_size + half_gap
        w, h = 4 * lane_size, object_size
        dx, dy = self.mWidth, y
        speed = randint(5, 15)
        self.mLog2 = froggerlib.Log(randint(0, self.mWidth), y - 50, w, h, dx, dy - 50, speed)
        lane_size = 50
        object_size = 40
        half_gap = 5
        x, y = 0, 4 * lane_size
        w, h = self.mWidth, lane_size
        self.mWater3 = froggerlib.Water(x, y - 100, w, h)
        x, y = 0, 4 * lane_size + half_gap
        w, h = 4 * lane_size, object_size
        dx, dy = self.mWidth, y
        speed = randint(5, 15)
        self.mLog3 = froggerlib.Log(randint(0, self.mWidth), y - 100, w, h, 0 - w, dy - 100, speed)
        lane_size = 50
        object_size = 40
        half_gap = 5
        x, y = 0, 4 * lane_size
        w, h = self.mWidth, lane_size
        self.mWater4 = froggerlib.Water(x, y - 150, w, h)
        x, y = 0, 4 * lane_size + half_gap
        w, h = 4 * lane_size, object_size
        dx, dy = self.mWidth, y
        speed = randint(5, 15)
        self.mLog4 = froggerlib.Log(randint(0, self.mWidth), y - 150, w, h, dx, dy - 150, speed)
        #Initializes Grasses and Homes
        self.mGrass1 = froggerlib.Grass(0, 0, 100, 50)
        self.mHome1 = froggerlib.Home(100, 0, 100, 50)
        self.mGrass2 = froggerlib.Grass(200, 0, 100, 50)
        self.mHome2 = froggerlib.Home(300, 0, 100, 50)
        self.mGrass3 = froggerlib.Home(400, 0, 100, 50)
        self.mHome3 = froggerlib.Home(500, 0, 100, 50)
        self.mGrass4 = froggerlib.Grass(600, 0, 100, 50)
        
        return
    
    def evolve(self, dt):
        if self.mGameOver:
            return
        self.mFrog.move()
        self.mLog1.move()
        if self.mLog1.atDesiredLocation():
            self.mLog1.setX( self.mWidth )
        self.mLog1.supports(self.mFrog)
        self.mLog2.move()
        if self.mLog2.atDesiredLocation():
            self.mLog2.setX( 0 - self.mLog2.getWidth() )
        self.mLog2.supports(self.mFrog)
        self.mLog3.move()
        if self.mLog3.atDesiredLocation():
            self.mLog3.setX( self.mWidth )
        self.mLog3.supports(self.mFrog)
        self.mLog4.move()
        if self.mLog4.atDesiredLocation():
            self.mLog4.setX( 0 - self.mLog4.getWidth() )
        self.mLog4.supports(self.mFrog)
        if self.mFrog.outOfBounds( self.mWidth, self.mHeight ):
            self.mGameOver = True
        self.mCar1.move()
        if self.mCar1.atDesiredLocation():
            self.mCar1.setX(self.mWidth + 1)
        if self.mCar1.hits(self.mFrog):
            self.mGameOver = True
        self.mCar2.move()
        if self.mCar2.atDesiredLocation():
            self.mCar2.setX( -self.mCar2.getWidth() )
        if self.mCar2.hits(self.mFrog):
            self.mGameOver = True
        self.mCar3.move()
        if self.mCar3.atDesiredLocation():
            self.mCar3.setX(self.mWidth + 1)
        if self.mCar3.hits(self.mFrog):
            self.mGameOver = True
        self.mCar4.move()
        if self.mCar4.atDesiredLocation():
            self.mCar4.setX( -self.mCar4.getWidth() )
        if self.mCar4.hits(self.mFrog):
            self.mGameOver = True
        if self.mWater1.hits(self.mFrog):
            self.mGameOver = True
        if self.mWater2.hits(self.mFrog):
            self.mGameOver = True
        if self.mWater3.hits(self.mFrog):
            self.mGameOver = True
        if self.mWater4.hits(self.mFrog):
            self.mGameOver = True
        if self.mGrass1.hits(self.mFrog):
            self.mGameOver = True
        if self.mGrass2.hits(self.mFrog):
            self.mGameOver = True
        if self.mGrass3.hits(self.mFrog):
            self.mGameOver = True
        if self.mGrass4.hits(self.mFrog):
            self.mGameOver = True
        if self.mHome1.hits(self.mFrog):
            self.mFrog.setX(self.mWidth/2)
            self.mFrog.setDesiredX(self.mWidth/2)
            self.mFrog.setY(11*50+5)
            self.mFrog.setDesiredY(11*50+5)
        if self.mHome2.hits(self.mFrog):
            self.mFrog.setX(self.mWidth/2)
            self.mFrog.setDesiredX(self.mWidth/2)
            self.mFrog.setY(11*50+5)
            self.mFrog.setDesiredY(11*50+5)
        if self.mHome3.hits(self.mFrog):
            self.mFrog.setX(self.mWidth/2)
            self.mFrog.setDesiredX(self.mWidth/2)
            self.mFrog.setY(11*50+5)
            self.mFrog.setDesiredY(11*50+5)
        
    def actOnPressLEFT( self ):
        self.mFrog.left()
        return
    
    def actOnPressRIGHT( self ):
        self.mFrog.right()
        return
    
    def actOnPressUP( self ):
        self.mFrog.up()
        return
    
    def actOnPressDOWN( self ):
        self.mFrog.down()
        return
    
    def draw_rect(self, surface, locatable, color):
        rect = pygame.Rect( int( locatable.getX( ) ), int( locatable.getY( ) ), int( locatable.getWidth( ) ), int( locatable.getHeight( ) ) )
        pygame.draw.rect( surface, color, rect, 0 )
        return
    
    def draw(self, surface):
        surface.fill( (0,0,0) )
        self.draw_rect(surface, self.mStage1, (171, 106, 171))
        self.draw_rect(surface, self.mStage2, (171, 106, 171))
        
        self.draw_rect(surface, self.mRoad1, (50, 50, 50))
        self.draw_rect(surface, self.mRoad2, (50, 50, 50))
        self.draw_rect(surface, self.mRoad3, (50, 50, 50))
        self.draw_rect(surface, self.mRoad4, (50, 50, 50))
        
        self.draw_rect(surface, self.mWater1, (0, 0, 255))
        self.draw_rect(surface, self.mWater2, (0, 0, 255))
        self.draw_rect(surface, self.mWater3, (0, 0, 255))
        self.draw_rect(surface, self.mWater4, (0, 0, 255))
        self.draw_rect(surface, self.mLog1, (153, 126, 50))
        self.draw_rect(surface, self.mLog2, (153, 126, 50))
        self.draw_rect(surface, self.mLog3, (153, 126, 50))
        self.draw_rect(surface, self.mLog4, (153, 126, 50))
        
        self.draw_rect(surface, self.mHome1, (50, 150, 150))
        self.draw_rect(surface, self.mHome2, (50, 150, 150))
        self.draw_rect(surface, self.mHome3, (50, 150, 150))
        self.draw_rect(surface, self.mGrass1, (50, 150, 50))
        self.draw_rect(surface, self.mGrass2, (50, 150, 50))
        self.draw_rect(surface, self.mGrass3, (50, 150, 50))
        self.draw_rect(surface, self.mGrass4, (50, 150, 50))
        
        rect = pygame.Rect(int(self.mFrog.getX()), int(self.mFrog.getY()), int( self.mFrog.getWidth()), int(self.mFrog.getHeight()))
        pygame.draw.rect( surface, (0,255,0), rect, 0 )
        
        rect = pygame.Rect(int(self.mCar2.getX()), int(self.mCar2.getY()), int(self.mCar2.getWidth()), int(self.mCar2.getHeight()))
        pygame.draw.rect( surface, (0,0,255), rect, 0 )
        rect = pygame.Rect(int(self.mCar1.getX()), int(self.mCar1.getY()), int(self.mCar1.getWidth()), int(self.mCar1.getHeight()))
        pygame.draw.rect( surface, (255,255,0), rect, 0 )
        rect = pygame.Rect(int(self.mCar3.getX()), int(self.mCar3.getY()), int(self.mCar3.getWidth()), int(self.mCar3.getHeight()))
        pygame.draw.rect( surface, (255,0,0), rect, 0 )
        rect = pygame.Rect(int(self.mCar4.getX()), int(self.mCar4.getY()), int(self.mCar4.getWidth()), int(self.mCar4.getHeight()))
        pygame.draw.rect( surface, (255,0,255), rect, 0 )
        
        return