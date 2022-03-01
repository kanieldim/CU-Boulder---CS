"""state_machine_controller controller."""

# You may need to import some classes of the controller module. Ex:
#  from controller import Robot, Motor, DistanceSensor
from controller import Robot

# time in [ms] of a simulation step
TIME_STEP = 64

MAX_SPEED = 6.28

# create the Robot instance.
robot = Robot()

state_1 = False
state_1_done = False

# initialize devices
ps = []
psNames = [
    'ps0', 'ps1', 'ps2', 'ps3',
    'ps4', 'ps5', 'ps6', 'ps7'
]

for i in range(8):
    ps.append(robot.getDistanceSensor(psNames[i]))
    ps[i].enable(TIME_STEP)

leftMotor = robot.getMotor('left wheel motor')
rightMotor = robot.getMotor('right wheel motor')
leftMotor.setPosition(float('inf'))
rightMotor.setPosition(float('inf'))
leftMotor.setVelocity(0.0)
rightMotor.setVelocity(0.0)

# get the time step of the current world.
# timestep = int(robot.getBasicTimeStep())

# You should insert a getDevice-like function in order to get the
# instance of a device of the robot. Something like:
#  motor = robot.getMotor('motorname')
#  ds = robot.getDistanceSensor('dsname')
#  ds.enable(timestep)

# Main loop:
# - perform simulation steps until Webots is stopping the controller
while robot.step(TIME_STEP) != -1:
     # read sensors outputs
    psValues = []
    for i in range(8):
        psValues.append(ps[i].getValue())

    # detect obstacles
    front_obstacle = psValues[0] > 80.0 and psValues[7] > 80.0
    back_obstacle = psValues[3] > 78.0 and psValues[4] > 67.0
    end = psValues[5] > 80.0
    # initialize motor speeds at 50% of MAX_SPEED.
    leftSpeed = 0.1 * MAX_SPEED
    rightSpeed = 0.1 * MAX_SPEED
    # modify speeds according to obstacles
    # Fist
    if front_obstacle and not state_1 and not state_1_done:
        state_1 = True
    
    # Second   
    if not back_obstacle and state_1 and not state_1_done :
        leftSpeed = 0.1 * MAX_SPEED 
        rightSpeed = -0.1 * MAX_SPEED  
    
    # Third
    if not front_obstacle and back_obstacle and state_1 and not state_1_done:
        leftSpeed  = 0.1 * MAX_SPEED
        rightSpeed = 0.1 * MAX_SPEED
        state_1 = False
        state_1_done = True
        
    # Fourth
    if not state_1 and state_1_done and front_obstacle:
        leftSpeed = 0.1 * MAX_SPEED 
        rightSpeed = -0.1 * MAX_SPEED
        state_1 = True
    
    if end and state_1_done and state_1:
        leftMotor.setVelocity(0.0)
        rightMotor.setVelocity(0.0) 
        break    

        
    # write actuators inputs
    leftMotor.setVelocity(leftSpeed)
    rightMotor.setVelocity(rightSpeed)

# Enter here exit cleanup code.
