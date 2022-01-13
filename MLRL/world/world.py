
from world.action import LEFT, RIGHT, DOWN, UP, EXIT
from agent.agent import agent
from PyQt6.QtWidgets import QApplication, QMainWindow
from PyQt6.QtGui import QPainter, QPen, QBrush, QPolygon, QColor
from PyQt6.QtCore import Qt, QPoint, QTimer, QRect
import sys 

"""
A world class which describes the contents of each world (read problem environment) used in the Q-learning demo

    Reinforcement learning demonstration - CuseHacks 2022
    Author: Matthew Cufari
    Date Created: Jan 7 2022

"""

"""
World class:
    noteworthy properties include - 
        The reward function (note this is abstracted from the agent definition without good reason)
        The domain of states
        The state -> [action, resulting state] pairs 
        The reward function need-not be a lambda but need follow the form
            f(d) -> REAL where d is in the domain of states

"""                          
def manhattanDist(x1,x2):
    return abs(x1[1]-x2[1])+abs(x1[0]-x2[0])
class world:
   
    def __init__(self, preDefinedName, rewardFunction=lambda s: 10 if (s=="EXIT_GOOD") else (-10 if (s=="EXIT_BAD") else -1 )):
        self.name = preDefinedName                                              # Name of grid_world type
        self.actions, self.domain, self.exit_states = self.getDomainAndActions(preDefinedName)    # Get the actions and domains of the world
        self.rewardFunction = rewardFunction                                    # Set the reward function of the world
        self.myAgent = agent(self.domain, self.actions, self.rewardFunction, epsilon=0.0, gamma=0.5) #Create a new agent
        
        self.initializeWindow() #Create a new world window
       
        
        
    """
        getDomainAndActions(preDefinedName):
            Purpose: Gather and collect the predefined domains of states and actions for each world layout/type
            Default: preDefinedName="gridWorld"
        
    """
    def getDomainAndActions(self, preDefinedName):
        if(preDefinedName=="gridWorld"):
            print("Making Grid World...")
            
            domain = [(0,0), (0,1), (0,2), (0,3), (0,4),
                      (1,0), (1,1),        (1,3), (1,4),
                      (2,0),  (2,1), (2,2), (2,3), (2,4), "EXIT_GOOD", "EXIT_BAD"]
            actions = {(0,0):[(RIGHT, (0,1)), (DOWN, (1,0))], (0,1):[(LEFT,(0,0)), (DOWN, (1,1)), (RIGHT,(0,2))], (0,2):[(RIGHT, (0,3)), (LEFT,(0,1))], 
                       (0,3):[(RIGHT,(0,4)), (LEFT, (0,2)), (DOWN, (1,3))], (0,4):[(EXIT, "EXIT_BAD")],
                       (1,0):[(UP, (0,1)), (RIGHT, (1,1)),(DOWN, (2,0))], (1,1):[(LEFT, (1,0)), (UP, (0,1)), (DOWN,(2,1))], (1,3):[(UP,(0,3)), (RIGHT, (1,4)), (DOWN,(2,3))],
                       (1,4):[(UP,(0,4)), (LEFT, (1,3)),(DOWN, (2,4))],
                       (2,0):[(UP, (1,0)), (RIGHT, (2,1))], (2,1):[(LEFT,(2,0)), (UP, (1,1)), (RIGHT, (2,2))], (2,2):[(RIGHT, (2,3)), (LEFT, (2,1))], 
                       (2,3):[(UP,(1,3)),(LEFT,(2,2)),(RIGHT,(2,4))], (2,4):[(EXIT,"EXIT_GOOD")], "EXIT_GOOD":[], "EXIT_BAD":[]}
            exit_states_good = [(2,4)]
            exit_states_bad = [(0,4)]
            return actions, domain, (exit_states_good, exit_states_bad)

        
        
        """
            Implementation a drawing solution which upon pressing the space bar returns control to the agent but does not close the window
            A sequence of actions which solves the problem would go something like this

                1: agent performs q-value update
                2: world updates the contents of the current window
                Always: World listens for key press (space or left-click) to modify and redraw screen

        """
    def initializeWindow(self):

        shad_self = self
        class MainWindow(QMainWindow): #Custom window class inheriting from qt main window
            def __init__(self):
                super().__init__()     #Use the superclass constructor to set all fields
                self.top = 150         #Set default parameters for window and size
                self.left = 150        #default
                self.height = 600      #Default
                self.width = 1200      #default
                self.interval = 1000   #2x the initial timer value

                self.setWindowTitle("Q-learner") #Window title
                self.setGeometry(self.top, self.left, self.width, self.height) #The dimensions of the window (x,y,width,height)
                self.timer = QTimer() #Timer object
                self.timer.timeout.connect(self.updateEvent) #Connect the timeout signal to the updateEvent occurrence
                
            def mousePressEvent(self, e): #When mouse is pressed perform an update
                self.updateEvent()

            def keyPressEvent(self, e): #Only when space is pressed perform speedy autonomous q-learner
                
                if e.key() == Qt.Key.Key_Space:
                    self.timer.stop()
                    self.interval = self.interval / 2
                    self.timer.setInterval(self.interval)
                    self.timer.start()
                if e.key() == Qt.Key.Key_Backspace:
                    self.timer.stop()
                    self.interval = 1000
                    self.timer.setInterval(self.interval)
            def updateEvent(self):
                shad_self.myAgent.iterateQValues() #Call to agent's q-learner algorithm
                self.update()                      #Call to trigger paintEvent

            def paintEvent(self, event):
                
                painter = QPainter(self)           #QPainter Object for mainWindow

                prime_pen = QPen(Qt.GlobalColor.white,  5, Qt.PenStyle.SolidLine) #Prime pen is white
                subPrime_pen = QPen(Qt.GlobalColor.white, 3, Qt.PenStyle.SolidLine) #subprime pen is white
                painter.setPen(prime_pen) #Set pen to white for rectangle grid

                for i in range(5):
                    for j in range(3):
                        if (j,i) not in shad_self.domain: #Unavail states are colored light_gray
                            painter.setBrush(QBrush(Qt.GlobalColor.lightGray, Qt.BrushStyle.SolidPattern)) #set brush strokes
                            painter.setPen(prime_pen) #set pen
                            painter.drawRect(self.width/5 * i, self.height/3 * j, self.width/5, self.height/3) #color rectangle
                            painter.setBrush(QBrush(Qt.GlobalColor.lightGray, Qt.BrushStyle.NoBrush))     #set brush strokes again
                            continue
                        elif (j,i) in shad_self.exit_states[1]: #bad exit == colored poorly
                            QVal = str(shad_self.myAgent.QValues[(j,i),EXIT]) #get string of qVal
                            painter.setBrush(QBrush(QColor(255, 0,0 ), Qt.BrushStyle.SolidPattern)) #set painter to red
                            painter.setPen(prime_pen)                                               #set pen to white border
                            rect = QRect(self.width/5 * (i+0.1), self.height/3 * (j+0.1), self.width/5-self.width/5 *0.2, self.height/3 - self.height/3*0.2) #get a rectangle
                            painter.drawRect(rect)   #draw the rectangle
                            
                            painter.setPen(subPrime_pen) #set pen to white
                            painter.drawText(rect, Qt.AlignmentFlag.AlignCenter,QVal) #add text of qval to rectangle
                            painter.setBrush(QBrush(Qt.GlobalColor.black, Qt.BrushStyle.NoBrush)) #set brush back to black
                            continue
                        elif (j,i) in shad_self.exit_states[0]: #good exit == colored goodly
                            
                            QVal = str(shad_self.myAgent.QValues[(j,i),EXIT]) #get string of qval
                            painter.setBrush(QBrush(QColor(0, 255,0 ), Qt.BrushStyle.SolidPattern)) #set painter to green
                            painter.setPen(prime_pen) #set pen
                            rect = QRect(self.width/5 * (i+0.1), self.height/3 * (j+0.1), self.width/5-self.width/5 *0.2, self.height/3 - self.height/3*0.2) #rectangle
                            painter.drawRect(rect) #draw rectangle
                            
                            painter.setPen(subPrime_pen) #set white pen 
                            painter.drawText(rect, Qt.AlignmentFlag.AlignCenter,QVal) #add text
                            painter.setBrush(QBrush(Qt.GlobalColor.black, Qt.BrushStyle.NoBrush)) #reset brush
                            continue 
                        
                        painter.setPen(prime_pen) #set pen to white
                        painter.setBrush(QBrush(Qt.GlobalColor.black, Qt.BrushStyle.SolidPattern)) #set brush to black
                        painter.drawRect(self.width/5 * i, self.height/3 * j, self.width/5, self.height/3) #draw grid
                        

                        """
                            Coordinates of 4 interior triangles of each grid cell
                        """

                        points_top = [QPoint(self.width/5 * i, self.height/3 * j),
                                    QPoint(self.width/5 * (i+1), self.height/3*j), 
                                    QPoint(self.width/5 * (i+0.5), self.height/3 * (j+0.5))]
                        points_left = [QPoint(self.width/5 * i, self.height/3 * j),
                                    QPoint(self.width/5 * (i), self.height/3*(j+1)), 
                                    QPoint(self.width/5 * (i+0.5), self.height/3 * (j+0.5))]
                        points_bottom = [QPoint(self.width/5 * i, self.height/3 * (j+1)),
                                    QPoint(self.width/5 * (i+1), self.height/3*(j+1)), 
                                    QPoint(self.width/5 * (i+0.5), self.height/3 * (j+0.5))]
                                    
                        points_right= [QPoint(self.width/5 * (i+1), self.height/3 * j),
                                    QPoint(self.width/5 * (i+1), self.height/3*(j+1)), 
                                    QPoint(self.width/5 * (i+0.5), self.height/3 * (j+0.5))]
                        poly_t = QPolygon(points_top)
                        poly_l = QPolygon(points_left)
                        poly_b = QPolygon(points_bottom)
                        poly_r = QPolygon(points_right)

                        """
                            Coloring the q-values
                        """
                        
                        painter.setPen(subPrime_pen) #white pen
                        for action in [UP, DOWN, LEFT, RIGHT]:
                            QVal = shad_self.myAgent.QValues[((j,i),action)]
                            b = 0
                            r = 0
                            g = 0
                            if QVal >= 0:
                                g = min(255, QVal / 10.0 * 255.) #get the proper color
                            elif QVal < 0:
                                r = min(255, -QVal/ 10.0 * 255.) #so on so forth
                            painter.setBrush(QBrush(QColor(r,g,b), Qt.BrushStyle.SolidPattern)) #set brush to color
                            
                            if action == UP: #if up color top triangle
                                painter.drawPolygon(poly_t)
                                br = poly_t.boundingRect()
                                painter.drawText(br, Qt.AlignmentFlag.AlignCenter, "{:6.2f}".format(QVal)) #add text of qval
                            elif action == RIGHT:
                                painter.drawPolygon(poly_r)
                                br = poly_r.boundingRect()
                                painter.drawText(br, Qt.AlignmentFlag.AlignCenter, "{:6.2f}".format(QVal))
                            elif action == LEFT:
                                painter.drawPolygon(poly_l)
                                br = poly_l.boundingRect()
                                painter.drawText(br, Qt.AlignmentFlag.AlignCenter, "{:6.2f}".format(QVal))
                            elif action == DOWN:
                                painter.drawPolygon(poly_b)
                                br = poly_b.boundingRect()
                                painter.drawText(br, Qt.AlignmentFlag.AlignCenter, "{:6.2f}".format(QVal))
                            
                      
                try:
                    j,i = shad_self.myAgent.currentState #get j,i of current state
                    painter.setPen(QPen(QColor(255, 255, 0), 5,  Qt.PenStyle.SolidLine)) #yellow
                    painter.setBrush(QBrush(QColor(255, 255,0), Qt.BrushStyle.SolidPattern)) #yellow
                    painter.drawEllipse(self.width/5 * (i+0.425), self.height/3 * (j+0.4), 40, 40) #color a disk with proper offset
                    painter.setPen(subPrime_pen) #set pen to white again
                except ValueError:
                    pass 
                            


        app = QApplication(sys.argv)

        window = MainWindow()
        
        window.show()
        app.exec()
        

        
