from controller import Robot, DistanceSensor, Motor

# time in [ms] of a simulation step
TIME_STEP = 64

MAX_SPEED = 6.28

# create the Robot instance.
robot = Robot()

# initialize devices
ps = []
psNames = [
    'ps0', 'ps1', 'ps2', 'ps3',
    'ps4', 'ps5', 'ps6', 'ps7'
]

for i in range(8):
    ps.append(robot.getDevice(psNames[i]))
    ps[i].enable(TIME_STEP)
    


leftMotor = robot.getDevice('left wheel motor')
rightMotor = robot.getDevice('right wheel motor')
leftSensor = robot.getDevice('left wheel sensor')
rightSensor = robot.getDevice('right wheel sensor')
leftSensor.enable(1)
rightSensor.enable(1)
leftMotor.setPosition(float('inf'))
rightMotor.setPosition(float('inf'))
leftMotor.setVelocity(0.0)
rightMotor.setVelocity(0.0)

currstate = 1

# feedback loop: step simulation until receiving an exit event
while robot.step(TIME_STEP) != -1:
    # read sensors outputs
    psValues = []
    for i in range(8):
        psValues.append(ps[i].getValue())

    # detect obstacles
    #right_obstacle = psValues[0] > 80.0 or psValues[1] > 80.0 or psValues[2] > 80.0
    #left_obstacle = psValues[5] > 80.0 or psValues[6] > 80.0 or psValues[7] > 80.0

    # modify speeds according to obstacles
    
    #1 is state drive forward until within 5cm of infont object
    if currstate==1:
        leftSpeed  = MAX_SPEED
        rightSpeed = MAX_SPEED
        if ((psValues[0]>100) or (psValues[7]>100)):
            currstate=2
            
            
    #2 turn 180 degrees
    elif currstate==2:
        leftSpeed  = MAX_SPEED
        rightSpeed = -MAX_SPEED
        #print(leftSensor.getValue())
        if (leftSensor.getValue())>41.2:
            currstate=3
    #3 is state drive forward until within 5cm of infont object
    elif currstate==3:
        leftSpeed  = MAX_SPEED
        rightSpeed = MAX_SPEED
        if ((psValues[0]>100) or (psValues[7]>100)):
            currstate=4
    #4 rotate clockwise until left sensor(ps5) reads less than 5cm
    elif currstate==4:
        leftSpeed  = MAX_SPEED
        rightSpeed = -MAX_SPEED
        #print(leftSensor.getValue())
        if (psValues[5])>150:
            currstate=5
    #5 go forward for as long as left sensor senses something within 5cm  
    elif currstate==5:
        leftSpeed  = MAX_SPEED
        rightSpeed = MAX_SPEED
        if (psValues[5])<150:
            currstate=6
    #6 stop forever
    elif currstate==6:
        leftSpeed  = 0
        rightSpeed = 0
    
    
    # write actuators inputs
    leftMotor.setVelocity(leftSpeed)
    rightMotor.setVelocity(rightSpeed)
