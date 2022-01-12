from typing import TypeVar
from world.action import Action, LEFT, RIGHT, DOWN, UP, EXIT
from agent.agent import agent
from PyQt6.QtWidgets import QApplication, QWidget, QMainWindow, QPushButton
from PyQt6.QtGui import QPainter, QPen, QBrush, QPolygon, QColor, QFont
from PyQt6.QtCore import Qt, QPoint
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

class world:
   
    def __init__(self, preDefinedName, rewardFunction=lambda s: 10 if (s=="EXIT_GOOD") else (-10 if (s=="EXIT_BAD") else -1)):
        self.name = preDefinedName
        self.actions, self.domain = self.getDomainAndActions(preDefinedName)
        self.rewardFunction = rewardFunction
        self.myAgent = agent(self.domain, self.actions, self.rewardFunction, epsilon=0.0, gamma=1.0)
        self.app, self.window = self.initializeWindow()
        """
        Add visualization code here
        #self.initializeWindow()
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
            return actions, domain
        
    def initializeWindow(self):
        shad_self = self
        class MainWindow(QMainWindow):
            def __init__(self):
                super().__init__()
                self.top = 150
                self.left = 150
                self.height = 600
                self.width = 1200

                self.setWindowTitle("Q-learner")
                self.setGeometry(self.top, self.left, self.width, self.height)
                #self.button = QPushButton("Press Me!")
                #self.button.setCheckable(True)
                #self.button.clicked.connect(self.the_button_was_clicked)

                # Set the central widget of the Window.
                #self.setCentralWidget(self.button)
                
            def mousePressEvent(self, e):
                shad_self.myAgent.iterateQValues()
                self.update()

            def paintEvent(self, event):
                
                painter = QPainter(self)

                prime_pen = QPen(Qt.GlobalColor.blue,  5, Qt.PenStyle.SolidLine)
                subPrime_pen = QPen(Qt.GlobalColor.white, 3, Qt.PenStyle.SolidLine)
                painter.setPen(prime_pen)

                for i in range(5):
                    for j in range(3):
                        if j == 1 and i == 2:
                            painter.setBrush(QBrush(Qt.GlobalColor.black, Qt.BrushStyle.SolidPattern))
                            painter.setPen(prime_pen)
                            painter.drawRect(self.width/5 * i, self.height/3 * j, self.width/5, self.height/3)
                            painter.setBrush(QBrush(Qt.GlobalColor.black, Qt.BrushStyle.NoBrush))
                            continue
                        if j == 0 and i == 4:
                            QVal = abs(shad_self.myAgent.QValues[((j,i),EXIT)])
                            
                            painter.setBrush(QBrush(QColor(min(255, QVal * 10), 0,0 ), Qt.BrushStyle.SolidPattern))
                            painter.setPen(prime_pen)
                            painter.drawRect(self.width/5 * i, self.height/3 * j, self.width/5, self.height/3)
                            painter.setBrush(QBrush(Qt.GlobalColor.black, Qt.BrushStyle.NoBrush))
                            continue 
                        if j == 2 and i == 4:
                            QVal = abs(shad_self.myAgent.QValues[((j,i),EXIT)])
                            
                            painter.setBrush(QBrush(QColor(0, min(255, QVal * 10),0 ), Qt.BrushStyle.SolidPattern))
                            painter.setPen(prime_pen)
                            painter.drawRect(self.width/5 * i, self.height/3 * j, self.width/5, self.height/3)
                            painter.setBrush(QBrush(Qt.GlobalColor.black, Qt.BrushStyle.NoBrush))
                            continue 
                        painter.setPen(prime_pen)
                        painter.drawRect(self.width/5 * i, self.height/3 * j, self.width/5, self.height/3)
                        painter.setBrush(QBrush(Qt.GlobalColor.black, Qt.BrushStyle.NoBrush))

                        

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

                        painter.setPen(subPrime_pen)
                        

                        for action in [UP, DOWN, LEFT, RIGHT]:
                            QVal = shad_self.myAgent.QValues[((j,i),action)]
                            b = 0
                            r = 0
                            g = 0
                            if QVal > 0:
                                g = QVal / 10.0 * 255.
                            if QVal < 0:
                                r = QVal/ -10.0 * 255.
                            painter.setBrush(QBrush(QColor(r,g,b), Qt.BrushStyle.SolidPattern))

                            if action == UP:
                                painter.drawPolygon(poly_t)
                            elif action == RIGHT:
                                painter.drawPolygon(poly_r)
                            elif action == LEFT:
                                painter.drawPolygon(poly_l)
                            elif action == DOWN:
                                painter.drawPolygon(poly_b)
                            
                                
                        if (j,i) == shad_self.myAgent.currentState: 
                            painter.setPen(QPen(QColor(255, 255, 0), 5,  Qt.PenStyle.SolidLine))
                            painter.setBrush(QBrush(QColor(255, 255,0), Qt.BrushStyle.SolidPattern))
                            painter.drawEllipse(self.width/5 * (i+0.425), self.height/3 * (j+0.4), 40, 40)


        app = QApplication(sys.argv)

        window = MainWindow()
        
        window.show()
        app.exec()
        return app, window

        """
            Implement a method which initializes a window for the game to take place. The window should be empty and all grey
        """
    def draw(self, qValues, activeState): 
        
        return False
        """
            Implement a drawing solution which upon pressing the space bar returns control to the agent but does not close the window
            A sequence of actions which solves the problem would go something like this

                1: agent performs q-value update
                2: agent calls self.universe.world.draw()
                3: world.draw() updates the contents of the current window
                4: world.draw() returns a boolean True if the user presses space or left-click
                5: world.draw() returns a boolean False if the user presses back-space or delete
            Pseudo code solution:

                #self.window() is an abstract window object that is assumed to exist from the call to self.initializeWindow()
                window <- add grid-world grid with white lines
                
                window <- [draw triangle with label qValues[(state, action)] for (state,action) pair in world.actions]
                window <- draw orange disk at location of activeState
                window <- wait for input (space-bar, left-click, delete, back-space)

                $user input

                return False if delete or backspace
                return true otherwise


        """
