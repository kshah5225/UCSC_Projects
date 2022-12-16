"""ece10_lab2 controller."""

# You may need to import some classes of the controller module. Ex:
#  from controller import Robot, Motor, DistanceSensor
import math
from controller import Robot, Motor, DistanceSensor
import os

# Ground Sensor Measurements under this threshold are black
# measurements above this threshold can be considered white.
# TODO: Fill this in with a reasonable threshold that separates "line detected" from "no line detected"
GROUND_SENSOR_THRESHOLD = 310

# These are your pose values that you will update by solving the odometry equations
pose_x = 0
pose_y = 0
pose_theta = 0

# Index into ground_sensors and ground_sensor_readings for each of the 3 onboard sensors.
LEFT_IDX = 0
CENTER_IDX = 1
RIGHT_IDX = 2

# create the Robot instance.
robot = Robot()

# ePuck Constants
EPUCK_AXLE_DIAMETER = 0.053 # ePuck's wheels are 53mm apart.
EPUCK_MAX_WHEEL_SPEED = 0.125 # Done: To be filled in with ePuck wheel speed in m/s
#leftMotor.setVelocity(6.28)
#rightMotor.setVelocity(6.28)
MAX_SPEED = 6.28

# get the time step of the current world.
SIM_TIMESTEP = int(robot.getBasicTimeStep())

# Initialize Motors
leftMotor = robot.getDevice('left wheel motor')
rightMotor = robot.getDevice('right wheel motor')
leftMotor.setPosition(float('inf'))
rightMotor.setPosition(float('inf'))
leftMotor.setVelocity(0.0)
rightMotor.setVelocity(0.0)

# Initialize and Enable the Ground Sensors
gsr = [0, 0, 0]
ground_sensors = [robot.getDevice('gs0'), robot.getDevice('gs1'), robot.getDevice('gs2')]
for gs in ground_sensors:
    gs.enable(SIM_TIMESTEP)

# Allow sensors to properly initialize
for i in range(10): robot.step(SIM_TIMESTEP)  

vL = MAX_SPEED # Done: Initialize variable for left speed, radians/sec
vR = MAX_SPEED # Done: Initialize variable for right speed, radians/sec
tempODOI=0
tempheadI=0
tempXI=0
tempZI=0
triggerflag = 20
Turning_power = MAX_SPEED*.2#adjust
# Main Control Loop:
while robot.step(SIM_TIMESTEP) != -1:

    # Read ground sensor values
    for i, gs in enumerate(ground_sensors):
        gsr[i] = gs.getValue()

    #print(gsr) # Done: Uncomment to see the ground sensor values!

    # Hints: 
    #
    # 1) Setting vL=MAX_SPEED and vR=-MAX_SPEED lets the robot turn
    #    in place. vL=MAX_SPEED and vR=0.5*MAX_SPEED makes the
    #    robot drive a right curve.
    #
    # 2) If your robot "overshoots", turn slower.
    #
    # 3) Only set the wheel speeds once so that you can use the speed
    #    that you calculated in your odometry calculation.
    #
    # 4) Remove all console output to speed up simulation of the robot
    #    
    #
    
    # Done: Insert Line Following Code Here                
    #vL = (MAX_SPEED - 0.0136 * (gsr[2]-gsr[0]))/2.25
    #vR = (MAX_SPEED + 0.0136 * (gsr[2]-gsr[0]))/2.25
    #vL = (MAX_SPEED - 2*(MAX_SPEED/1000) * (gsr[2]-gsr[0]))
    #vR = (MAX_SPEED + 2*(MAX_SPEED/1000) * (gsr[2]-gsr[0]))
    #vL=((gsr[LEFT_IDX]-250)*157)/12500
    #vR=((gsr[RIGHT_IDX]-250)*157)/12500
    #vL=((gsr[LEFT_IDX])*157)/25000
    #vR=((gsr[RIGHT_IDX])*157)/25000
    #vL=gsr[LEFT_IDX]*0.007850000000000001-1.57
    #vR=gsr[RIGHT_IDX]*0.007850000000000001-1.57
    vL = ((((gsr[LEFT_IDX]-gsr[RIGHT_IDX])*MAX_SPEED)/1000)+MAX_SPEED)-(MAX_SPEED/2)
    vR = ((((gsr[LEFT_IDX]-gsr[RIGHT_IDX])*-MAX_SPEED)/1000)+MAX_SPEED)-(MAX_SPEED/2)
    """if triggerflag>0:
        vL=MAX_SPEED
        vR=MAX_SPEED
    elif gsr[CENTER_IDX]>gsr[LEFT_IDX]:
        vR=Turning_power
        vL=-Turning_power
    elif gsr[CENTER_IDX]>gsr[RIGHT_IDX]:
        vR=-Turning_power
        vL=Turning_power
    else:
        vL = ((((gsr[LEFT_IDX]-gsr[RIGHT_IDX])*6.28)/1000)+6.28)
        vR = ((((gsr[LEFT_IDX]-gsr[RIGHT_IDX])*-6.28)/1000)+6.28)"""
    if vL>MAX_SPEED:
        vL=MAX_SPEED
    if vR>MAX_SPEED:
        vR=MAX_SPEED
    if vL<-MAX_SPEED:
        vL=-MAX_SPEED
    if vR<-MAX_SPEED:
        vR=-MAX_SPEED
    #vL = ((MAX_SPEED/2)+((MAX_SPEED*(gsr[0]-gsr[2]))/500))/.95
    #vR = ((MAX_SPEED/2)+((MAX_SPEED*(gsr[2]-gsr[0]))/500))/.95
    #print("VR:",vR,"  VL:",vL)
    #tempvelL=0
    #tempvelR=0
    #print(gsr)
    #if(gsr[1]<400):
    #    tempvelL=MAX_SPEED/2
    #    tempvelR=MAX_SPEED/2
    #elif(gsr[2]<400):
    #    tempvelL=-1*MAX_SPEED/4
    #    tempvelR=MAX_SPEED/4
    #elif(gsr[0]<400):
    #    tempvelL=MAX_SPEED/4
    #    tempvelR=-1*MAX_SPEED/4
    #else:
    #    tempvelL=-1*MAX_SPEED
    #    tempvelR=MAX_SPEED
    #vL=tempvelL
    #vR=tempvelR
    
    # Done: Call update_odometry Here
    
    # Hints:
    #
    # 1) Divide vL/vR by MAX_SPEED to normalize, then multiply with
    # the robot's maximum speed in meters per second. 
    #
    # 2) SIM_TIMESTEP tells you the elapsed time per step. You need
    # to divide by 1000.0 to convert it to seconds
    #
    # 3) Do simple checks to make sure things are working. In the beginning, 
    #    only one value changes. Once you do a right turn, this value should be constant.
    #
    # 4) Focus on getting things generally right first, then worry
    #    about calculating odometry in the world coordinate system of the
    #    Webots simulator first (x points down, y points right)
    #0.0358 this is perfect value
    tempheadD=0.0377*((vR-vL)/6.28)
    tempheadI+=tempheadD
    tempODOD=((vL+vR)/(2*6.28))*(EPUCK_MAX_WHEEL_SPEED/1000)*SIM_TIMESTEP
    tempODOI+=tempODOD
    tempXD=math.sin(tempheadI)*tempODOD
    tempXI+=tempXD
    tempZD=math.cos(tempheadI)*tempODOD
    tempZI+=tempZD
    
    pose_x=tempXI
    pose_y=tempZI
    pose_theta=tempheadI
    
    # Done: Insert Loop Closure Code Here
    
    # Hints:
    #
    # 1) Set a flag whenever you encounter the line
    #
    # 2) Use the pose when you encounter the line last 
    #    for best results
    triggerflag=triggerflag-1
    #print(triggerflag)
    if(gsr[0]<GROUND_SENSOR_THRESHOLD and gsr[1]<GROUND_SENSOR_THRESHOLD and gsr[2]<GROUND_SENSOR_THRESHOLD and triggerflag<0 and ((math.sqrt((pose_x*pose_x)+(pose_y*pose_y))/tempODOI)*100)<20):
        triggerflag = 20
        print("%error:" ,(math.sqrt((pose_x*pose_x)+(pose_y*pose_y))/tempODOI)*100,"%")
        tempXI=0
        tempZI=0
        tempheadI=0
        tempODOI=0
    
    
    print("Current pose: [%5f, %5f, %5f]" % (pose_x, pose_y, pose_theta))
    leftMotor.setVelocity(vL)
    rightMotor.setVelocity(vR)
