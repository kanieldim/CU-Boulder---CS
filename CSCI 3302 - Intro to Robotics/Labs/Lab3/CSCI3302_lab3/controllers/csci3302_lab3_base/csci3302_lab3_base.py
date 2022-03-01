"""robot controller."""

# You may need to import some classes of the controller module. Ex:
#  from controller import Robot, Motor, DistanceSensor
import math
from controller import Robot, Motor, DistanceSensor
import csci3302_lab3_supervisor
import numpy as np

# Robot Pose Values
pose_x = 0
pose_y = 0
pose_theta = 0

# Constants to help with the Odometry update
WHEEL_FORWARD = 1
WHEEL_STOPPED = 0
WHEEL_BACKWARD = -1

#state = "turn_drive_turn_control" # Start in the easier, non-feedback control case!
state = "feedback_control" # End with the more complex feedback control method!
sub_state = "bearing" # TODO: It may be helpful to use sub_state to designate operation modes within the "turn_drive_turn_control" state

# create the Robot instance.
csci3302_lab3_supervisor.init_supervisor()
robot = csci3302_lab3_supervisor.supervisor

EPUCK_MAX_WHEEL_SPEED = 0.12880519 # Unnecessarily precise ePuck speed in m/s. REMINDER: motor.setVelocity() takes ROTATIONS/SEC as param, not m/s.
EPUCK_AXLE_DIAMETER = 0.053 # ePuck's wheels are 53mm apart.
EPUCK_WHEEL_RADIUS = 0.0205 # ePuck's wheels are 0.041m in diameter.

# get the time step of the current world.
SIM_TIMESTEP = int(robot.getBasicTimeStep())

# Initialize Motors
leftMotor = robot.getMotor('left wheel motor')
rightMotor = robot.getMotor('right wheel motor')
leftMotor.setPosition(float('inf'))
rightMotor.setPosition(float('inf'))
leftMotor.setVelocity(0.0)
rightMotor.setVelocity(0.0)


def update_odometry(left_wheel_direction, right_wheel_direction, time_elapsed):
    '''
    Given the amount of time passed and the direction each wheel was rotating,
    update the robot's pose information accordingly
    '''
    global pose_x, pose_y, pose_theta, EPUCK_MAX_WHEEL_SPEED, EPUCK_AXLE_DIAMETER
    pose_theta += (right_wheel_direction - left_wheel_direction) * time_elapsed * EPUCK_MAX_WHEEL_SPEED / EPUCK_AXLE_DIAMETER;
    pose_x += math.cos(pose_theta) * time_elapsed * EPUCK_MAX_WHEEL_SPEED * (left_wheel_direction + right_wheel_direction)/2.;
    pose_y += math.sin(pose_theta) * time_elapsed * EPUCK_MAX_WHEEL_SPEED * (left_wheel_direction + right_wheel_direction)/2.;
    pose_theta = get_bounded_theta(pose_theta)

def get_bounded_theta(theta):
    '''
    Returns theta bounded in [-PI, PI]
    '''
    while theta > math.pi: theta -= 2.*math.pi
    while theta < -math.pi: theta += 2.*math.pi
    return theta

def main():
    global robot, state, sub_state
    global leftMotor, rightMotor, SIM_TIMESTEP, WHEEL_FORWARD, WHEEL_STOPPED, WHEEL_BACKWARDS
    global pose_x, pose_y, pose_theta

    last_odometry_update_time = None

    # Keep track of which direction each wheel is turning
    left_wheel_direction = WHEEL_STOPPED
    right_wheel_direction = WHEEL_STOPPED

    # Important IK Variable storing final desired pose
    target_pose = None # Populated by the supervisor, only when the target is moved.


    # Sensor burn-in period
    for i in range(10): robot.step(SIM_TIMESTEP)
    
    b_error_zero = False
    d_error_zero = False
    h_error_zero = False
    
    # Main Control Loop:
    while robot.step(SIM_TIMESTEP) != -1:
        # Odometry update code -- do not modify
        if last_odometry_update_time is None:
            last_odometry_update_time = robot.getTime()
        time_elapsed = robot.getTime() - last_odometry_update_time
        update_odometry(left_wheel_direction, right_wheel_direction, time_elapsed)
        last_odometry_update_time = robot.getTime()

        # Get target location -- do not modify
        if target_pose is None:
            target_pose = csci3302_lab3_supervisor.supervisor_get_relative_target_pose()
            print("New IK Goal Received! Target: %s" % str(target_pose))

        # Your code starts here
        bearing_error = math.atan((target_pose[1] - pose_y) / (target_pose[0] - pose_x)) - pose_theta # TODO: Populate this!
        distance_error = math.sqrt((pose_x - target_pose[0])**2 + (pose_y - target_pose[1])**2) # TODO: Populate this!
        heading_error = target_pose[2] - pose_theta # TODO: Populate this!

        if state == "turn_drive_turn_control":
            # 1
            if bearing_error > 0 and b_error_zero == False:
                leftMotor.setVelocity(-leftMotor.getMaxVelocity()/4)
                rightMotor.setVelocity(rightMotor.getMaxVelocity()/4)
                left_wheel_direction = WHEEL_BACKWARD / 4
                right_wheel_direction = WHEEL_FORWARD / 4
            
            # 2           
            if bearing_error <= 0 and b_error_zero == False:
                leftMotor.setVelocity(0.0)
                rightMotor.setVelocity(0.0)
                left_wheel_direction = WHEEL_STOPPED
                right_wheel_direction = WHEEL_STOPPED
                b_error_zero = True
                          
            # 3     
            if distance_error > 0.03 and b_error_zero == True and d_error_zero == False:
                leftMotor.setVelocity(leftMotor.getMaxVelocity()/4)
                rightMotor.setVelocity(rightMotor.getMaxVelocity()/4)
                left_wheel_direction = WHEEL_FORWARD / 4
                right_wheel_direction = WHEEL_FORWARD / 4
            # 4           
            if distance_error <= 0.03 and b_error_zero == True and d_error_zero == False:
                leftMotor.setVelocity(0.0)
                rightMotor.setVelocity(0.0)
                left_wheel_direction = WHEEL_STOPPED
                right_wheel_direction = WHEEL_STOPPED
                d_error_zero = True
                
            # 5    
            if heading_error > 0.03 or heading_error < -0.03 and b_error_zero == True and d_error_zero == True and h_error_zero == False:
                leftMotor.setVelocity(-leftMotor.getMaxVelocity()/4)
                rightMotor.setVelocity(rightMotor.getMaxVelocity()/4)
                left_wheel_direction = WHEEL_BACKWARD / 4
                right_wheel_direction = WHEEL_FORWARD / 4
               
            # 6           
            if heading_error < 0.03 and heading_error > -0.03 and b_error_zero == True and d_error_zero == True and h_error_zero == False:
                leftMotor.setVelocity(0.0)
                rightMotor.setVelocity(0.0)
                left_wheel_direction = WHEEL_STOPPED
                right_wheel_direction = WHEEL_STOPPED
                h_error_zero = True
                
         
        elif state == "feedback_control":   
            
            Xr = min(distance_error, 0.05)
            theta_change = 0

            if distance_error > 0.05:
                theta_change = bearing_error

            else:
                theta_change = (0.1-distance_error)/0.1 * heading_error + distance_error/0.1 * bearing_error

            phi_left = (Xr - (theta_change * EPUCK_AXLE_DIAMETER) / 2) / EPUCK_WHEEL_RADIUS
            phi_right = (Xr + (theta_change * EPUCK_AXLE_DIAMETER) / 2) / EPUCK_WHEEL_RADIUS

            normalized_phi_left = phi_left / (abs(phi_left) + abs(phi_right)) #(max(abs(phi_left), abs(phi_right)))
            normalized_phi_right = phi_right / (abs(phi_left) + abs(phi_right)) #(max(abs(phi_left), abs(phi_right)))

            print("left phi:  ", phi_left)
            print("right phi: ", phi_right)

            print("normalized left phi:  ", normalized_phi_left)
            print("normalized right phi: ", normalized_phi_right)

            print("Theta Change: ", theta_change)

            #if (abs(bearing_error) > 0 or abs(distance_error) > 0.05 or (heading_error > 0.01 or heading_error < -0.01)):
            #if (abs(theta_change) > 0 and abs(distance_error) > 0.02): # and abs(heading_error) > 0.01):
            leftMotor.setVelocity(leftMotor.getMaxVelocity() * normalized_phi_left)
            left_wheel_direction = WHEEL_FORWARD * normalized_phi_left
            rightMotor.setVelocity(rightMotor.getMaxVelocity() * normalized_phi_right)
            right_wheel_direction = WHEEL_FORWARD * normalized_phi_right

            if abs(heading_error) < 0.1 and abs(distance_error) < 0.05:
                leftMotor.setVelocity(0.0)
                left_wheel_direction = WHEEL_STOPPED
                rightMotor.setVelocity(0.0)
                right_wheel_direction = WHEEL_STOPPED
         
            
            
        else:
            pass

        # To help you debug! Feel free to comment out.
        print("Current pose: [%5f, %5f, %5f]\t\t Target pose: [%5f, %5f, %5f]\t\t Errors: [%5f, %5f, %5f]" % (pose_x, pose_y, pose_theta, target_pose[0], target_pose[1], target_pose[2],bearing_error, distance_error, heading_error))
    
    
if __name__ == "__main__":
    main()





