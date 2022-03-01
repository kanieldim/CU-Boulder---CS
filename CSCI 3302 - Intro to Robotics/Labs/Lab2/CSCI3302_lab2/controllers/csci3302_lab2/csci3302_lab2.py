"""csci3302_lab2 controller."""

# You may need to import some classes of the controller module. Ex:
#  from controller import Robot, Motor, DistanceSensor
import math
from controller import Robot, Motor, DistanceSensor

# Ground Sensor Measurements under this threshold are black
# measurements above this threshold can be considered white.
# TODO: Fill this in with a reasonable threshold that separates "line detected" from "no line detected"
GROUND_SENSOR_THRESHOLD = 500

# These are your pose values that you will update by solving the odometry equations
pose_x = 0
pose_y = 0
pose_theta = 0

# Constants to help with the Odometry update
WHEEL_FORWARD = 1
WHEEL_STOPPED = 0
WHEEL_BACKWARD = -1

# Index into ground_sensors and ground_sensor_readings for each of the 3 onboard sensors.
LEFT_IDX = 0
CENTER_IDX = 1
RIGHT_IDX = 2

# state = "speed_measurement"
state = "line_follower"

# create the Robot instance.
robot = Robot()

# ePuck Constants
EPUCK_AXLE_DIAMETER = 0.053 # ePuck's wheels are 53mm apart.
EPUCK_MAX_WHEEL_SPEED = 0.12019230769230771 # To be filled in with ePuck wheel speed in m/s


# get the time step of the current world.
SIM_TIMESTEP = int(robot.getBasicTimeStep())

# Initialize Motors
leftMotor = robot.getMotor('left wheel motor')
rightMotor = robot.getMotor('right wheel motor')
leftMotor.setPosition(float('inf'))
rightMotor.setPosition(float('inf'))
leftMotor.setVelocity(0.0)
rightMotor.setVelocity(0.0)

# Initialize and Enable the Ground Sensors
ground_sensor_readings = [0, 0, 0]
ground_sensors = [robot.getDistanceSensor('gs0'), robot.getDistanceSensor('gs1'), robot.getDistanceSensor('gs2')]
for gs in ground_sensors:
    gs.enable(SIM_TIMESTEP)


def update_odometry(left_wheel_direction, right_wheel_direction, time_elapsed):
    '''
    Given the amount of time passed and the direction each wheel was rotating,
    update the robot's pose information accordingly
    '''
    global pose_x, pose_y, pose_theta, EPUCK_MAX_WHEEL_SPEED, EPUCK_AXLE_DIAMETER
    # TODO: Update pose_theta
    # TODO: Update pose_x
    # TODO: Update pose_y
    
    left_dist =
    right_dist =
    
    
    if left_wheel_direction > right_wheel_direction:
        pose_theta -= (EPUCK_MAX_WHEEL_SPEED * time_elapsed / EPUCK_AXLE_DIAMETER) * (100 / math.pi)
    if right_wheel_direction > left_wheel_direction:
        pose_theta += (EPUCK_MAX_WHEEL_SPEED * time_elapsed / EPUCK_AXLE_DIAMETER) * (100 / math.pi)
   
    pose_x += EPUCK_MAX_WHEEL_SPEED * time_elapsed * math.cos(pose_theta)
    
    pose_y += EPUCK_MAX_WHEEL_SPEED * time_elapsed * math.sin(pose_theta)
    
    
def main():
    global robot, ground_sensors, ground_sensor_readings, state
    global leftMotor, rightMotor, SIM_TIMESTEP, WHEEL_FORWARD, WHEEL_STOPPED, WHEEL_BACKWARDS
    global pose_x, pose_y, pose_theta

    measurement_start_time = None
    
    # Part 2 & 3 Variables
    last_odometry_update_time = None
    loop_closure_detection_time = 0
    
    # Variables to keep track of which direction each wheel is turning for odometry
    left_wheel_direction = WHEEL_STOPPED
    right_wheel_direction = WHEEL_STOPPED
    
    # Allow sensors to properly initialize
    for i in range(10): robot.step(SIM_TIMESTEP)  
    
    # Main Control Loop:
    while robot.step(SIM_TIMESTEP) != -1:
    
        # Read ground sensor values
        for i, gs in enumerate(ground_sensors):
            ground_sensor_readings[i] = gs.getValue()

        # print(ground_sensor_readings)
            
        if state == "speed_measurement":
            # TODO
            leftMotor.setVelocity(leftMotor.getMaxVelocity())
            rightMotor.setVelocity(rightMotor.getMaxVelocity())
            
            if measurement_start_time == None:
                measurement_start_time = robot.getTime()
                
            if ground_sensor_readings[LEFT_IDX] < GROUND_SENSOR_THRESHOLD and ground_sensor_readings[RIGHT_IDX] < GROUND_SENSOR_THRESHOLD and ground_sensor_readings[CENTER_IDX] < GROUND_SENSOR_THRESHOLD:
                leftMotor.setVelocity(0.0)
                rightMotor.setVelocity(0.0)
                
                time_difference = robot.getTime() - measurement_start_time
                print("Time taken: ", time_difference)
                state = "none"
                
                EPUCK_MAX_WHEEL_SPEED = .1 / 0.832
                print("Speed", .1/0.832)   
                state = "line_follower"                 
                           
        elif state == "line_follower":
            
            # If first time entering this state ever, just take the current time as "last odometry update" time
            if last_odometry_update_time is None:
                last_odometry_update_time = robot.getTime()
            
            
            if ground_sensor_readings[CENTER_IDX] < GROUND_SENSOR_THRESHOLD:
                leftMotor.setVelocity(leftMotor.getMaxVelocity())
                rightMotor.setVelocity(rightMotor.getMaxVelocity())
                left_wheel_direction = WHEEL_FORWARD
                right_wheel_direction = WHEEL_FORWARD

            # Go left (CCW) if center reads line 
            elif ground_sensor_readings[LEFT_IDX] < GROUND_SENSOR_THRESHOLD:
                leftMotor.setVelocity(-1 * leftMotor.getMaxVelocity())
                rightMotor.setVelocity(rightMotor.getMaxVelocity())
                left_wheel_direction = WHEEL_BACKWARD
                right_wheel_direction = WHEEL_FORWARD

            # Go right (CW) if center reads line 
            elif ground_sensor_readings[RIGHT_IDX] < GROUND_SENSOR_THRESHOLD:
                leftMotor.setVelocity(leftMotor.getMaxVelocity())
                rightMotor.setVelocity(-1 * rightMotor.getMaxVelocity())
                left_wheel_direction = WHEEL_FORWARD
                right_wheel_direction = WHEEL_BACKWARD


            # If epuck cannot find the line on any sensor, rotate CCW in place
            elif (ground_sensor_readings[LEFT_IDX] > GROUND_SENSOR_THRESHOLD) and (ground_sensor_readings[RIGHT_IDX] > GROUND_SENSOR_THRESHOLD) and (ground_sensor_readings[CENTER_IDX] > GROUND_SENSOR_THRESHOLD):
                leftMotor.setVelocity(-1 * leftMotor.getMaxVelocity())
                rightMotor.setVelocity(rightMotor.getMaxVelocity())
                left_wheel_direction = WHEEL_BACKWARD
                right_wheel_direction = WHEEL_FORWARD

            else:
                leftMotor.setVelocity(leftMotor.getMaxVelocity())
                rightMotor.setVelocity(rightMotor.getMaxVelocity())
                left_wheel_direction = WHEEL_FORWARD
                right_wheel_direction = WHEEL_FORWARD
            # TODO: Call update_odometry Here
            

            # TODO: Insert Line Following Code Here                

            # TODO: Insert Loop Closure Code Here

            print("Current pose: [%5f, %5f, %5f]" % (pose_x, pose_y, pose_theta))
        else:
            pass
    
    
if __name__ == "__main__":
    main()