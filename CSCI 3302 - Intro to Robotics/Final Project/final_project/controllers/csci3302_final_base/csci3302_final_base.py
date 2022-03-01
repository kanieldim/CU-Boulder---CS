"""robot controller."""

# You may need to import some classes of the controller module. Ex:
#  from controller import Robot, Motor, DistanceSensor
import math
import copy
from controller import Robot, Motor, DistanceSensor
import csci3302_final_supervisor
import numpy as np



state = "get_path"


#########################################################
# Starter code: You shouldn't have to modify any of this

# create the Robot instance.
csci3302_final_supervisor.init_supervisor()
robot = csci3302_final_supervisor.supervisor

# Map Variables
MAP_BOUNDS = [1.,1.] 
CELL_RESOLUTIONS = np.array([0.1, 0.1]) # 10cm per cell
NUM_X_CELLS = int(MAP_BOUNDS[0] / CELL_RESOLUTIONS[0])
NUM_Y_CELLS = int(MAP_BOUNDS[1] / CELL_RESOLUTIONS[1])

world_map = np.zeros([NUM_Y_CELLS,NUM_X_CELLS])

def populate_map(m):
    obs_list = csci3302_final_supervisor.supervisor_get_obstacle_positions()
    obs_size = 0.06 # 6cm boxes
    for obs in obs_list:
        obs_coords_lower = obs - obs_size/2.
        obs_coords_upper = obs + obs_size/2.
        obs_coords = np.linspace(obs_coords_lower, obs_coords_upper, 10)
        for coord in obs_coords:
            m[transform_world_coord_to_map_coord(coord)] = 1
        obs_coords_lower = [obs[0] - obs_size/2, obs[1] + obs_size/2.]
        obs_coords_upper = [obs[0] + obs_size/2., obs[1] - obs_size/2.]
        obs_coords = np.linspace(obs_coords_lower, obs_coords_upper, 10)
        for coord in obs_coords:
            m[transform_world_coord_to_map_coord(coord)] = 1


# Robot Pose Values
pose_x = 0
pose_y = 0
pose_theta = 0
left_wheel_direction = 0
right_wheel_direction = 0

# Constants to help with the Odometry update
WHEEL_FORWARD = 1
WHEEL_STOPPED = 0
WHEEL_BACKWARD = -1

# GAIN Values
theta_gain = 1.0
distance_gain = 0.3


EPUCK_MAX_WHEEL_SPEED = 0.12880519 # m/s
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

MAX_VEL_REDUCTION = 0.25


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

def get_wheel_speeds(target_pose):
    '''
    @param target_pose: Array of (x,y,theta) for the destination robot pose
    @return motor speed as percentage of maximum for left and right wheel motors
    '''
    global pose_x, pose_y, pose_theta, left_wheel_direction, right_wheel_direction

    pose_x, pose_y, pose_theta = csci3302_final_supervisor.supervisor_get_robot_pose()


    bearing_error = math.atan2( (target_pose[1] - pose_y), (target_pose[0] - pose_x) ) - pose_theta
    distance_error = np.linalg.norm(target_pose[:2] - np.array([pose_x,pose_y]))
    heading_error = target_pose[2] -  pose_theta

    BEAR_THRESHOLD = 0.06
    DIST_THRESHOLD = 0.03
    dT_gain = theta_gain
    dX_gain = distance_gain
    if distance_error > DIST_THRESHOLD:
        dTheta = bearing_error
        if abs(bearing_error) > BEAR_THRESHOLD:
            dX_gain = 0
    else:
        dTheta = heading_error
        dX_gain = 0

    dTheta *= dT_gain
    dX = dX_gain * min(3.14159, distance_error)

    phi_l = (dX - (dTheta*EPUCK_AXLE_DIAMETER/2.)) / EPUCK_WHEEL_RADIUS
    phi_r = (dX + (dTheta*EPUCK_AXLE_DIAMETER/2.)) / EPUCK_WHEEL_RADIUS

    left_speed_pct = 0
    right_speed_pct = 0
    
    wheel_rotation_normalizer = max(abs(phi_l), abs(phi_r))
    left_speed_pct = (phi_l) / wheel_rotation_normalizer
    right_speed_pct = (phi_r) / wheel_rotation_normalizer
    
    if distance_error < 0.05 and abs(heading_error) < 0.05:    
        left_speed_pct = 0
        right_speed_pct = 0
        
    left_wheel_direction = left_speed_pct * MAX_VEL_REDUCTION
    phi_l_pct = left_speed_pct * MAX_VEL_REDUCTION * leftMotor.getMaxVelocity()

    right_wheel_direction = right_speed_pct * MAX_VEL_REDUCTION
    phi_r_pct = right_speed_pct * MAX_VEL_REDUCTION * rightMotor.getMaxVelocity()
       
    return phi_l_pct, phi_r_pct



def transform_world_coord_to_map_coord(world_coord):
    """
    @param world_coord: Tuple of (x,y) position in world coordinates
    @return grid_coord: Tuple of (i,j) coordinates corresponding to grid row (y-coord) and column (x-coord) in our map
    """
    col, row = np.array(world_coord) / CELL_RESOLUTIONS
    if row < 0 or col < 0 or row >= NUM_Y_CELLS or col >= NUM_X_CELLS:
        return None

    return tuple(np.array([row, col]).astype(int))


def transform_map_coord_world_coord(map_coord):
    """
    @param map_coord: Tuple of (i,j) coordinates corresponding to grid column and row in our map
    @return world_coord: Tuple of (x,y) position corresponding to the center of map_coord, in world coordinates
    """
    row, col = map_coord
    if row < 0 or col < 0 or row >= NUM_Y_CELLS or col >= NUM_X_CELLS:
        return None
    
    return np.array([(col+0.5)*CELL_RESOLUTIONS[1], (row+0.5)*CELL_RESOLUTIONS[0]])


def display_map(m):
    """
    @param m: The world map matrix to visualize
    """
    m2 = copy.copy(m)
    robot_pos = transform_world_coord_to_map_coord([pose_x,pose_y])
    m2[robot_pos] = 8
    map_str = ""
    for row in range(m.shape[0]-1,-1,-1):
        for col in range(m.shape[1]):
            if m2[row,col] == 0: map_str += '[ ]'
            elif m2[row,col] == 1: map_str += '[X]'
            elif m2[row,col] == 2: map_str += '[+]'
            elif m2[row,col] == 3: map_str += '[G]'
            elif m2[row,col] == 4: map_str += '[S]'
            elif m2[row,col] == 8: map_str += '[r]'
            else: map_str += '[E]'

        map_str += '\n'

    print(map_str)
    print(' ')

# ^ Starter code: You shouldn't have to modify any of this ^
############################################################




###################
# Part 1.1
###################
def get_travel_cost(source_vertex, dest_vertex):
    """
    @param source_vertex: world_map coordinates for the starting vertex
    @param dest_vertex: world_map coordinates for the destination vertex
    @return cost: Cost to travel from source to dest vertex.
    """
    global world_map
    
    n, m = world_map.shape
    
    sx, sy = source_vertex
    dx, dy = dest_vertex
    cost = 1e5
    
    # if they are same cell
    #if(world_map[sx][sy] == world_map[dx][dy]):
    if(source_vertex == dest_vertex):
        cost = 0
        
    #if destination cell is occupied
    elif(world_map[dx][dy] == 1):
        cost = 1e5
    
    # if they are neighbors
    elif((sx+1 < n) and (world_map[sx+1][sy] == world_map[dx][dy])):
        cost = 1
    elif((sx-1 >= 0) and (world_map[sx-1][sy] == world_map[dx][dy])):
        cost = 1
    elif((sy+1 < m) and (world_map[sx][sy+1] == world_map[dx][dy])):
        cost = 1
    elif((sy-1 >= 0) and (world_map[sx][sy-1] == world_map[dx][dy])):
        cost = 1
        
        #if((world_map[sx+1][sy] == world_map[dx][dy]) or (world_map[sx-1][sy] == world_map[dx][dy])
            #or (world_map[sx][sy+1] == world_map[dx][dy]) or (world_map[sx][sy-1] == world_map[dx][dy])):
            #cost = 1
    #else:
        #cost = 1e5

    return cost #if not neighbors or occupied cell



###################
# Part 1.2
###################
def dijkstra(source_vertex):
    """
    @param source_vertex: Starting vertex for the search algorithm.
    @return prev: Data structure that maps every vertex to the coordinates of the 
                    previous vertex (along the shortest path back to source)
    """
    global world_map
    
    #source map coordinate
    source_coord = transform_world_coord_to_map_coord(source_vertex)

    # TODO: Initialize these variables
    #dist = np.full([NUM_X_CELLS, NUM_Y_CELLS], np.inf)  # [0] * NUM_X_CELLS * NUM_Y_CELLS
    #q_cost = dist.copy()
    #prev = np.full([NUM_X_CELLS, NUM_Y_CELLS], None) # [-1] * NUM_X_CELLS * NUM_Y_CELLS
    

    # TODO: Your code here
    
    ### try this for loop in 3 1 liners according to Aaquib ###
    #dist[source_vertex[0]][source_coord[1]] = 0
    #for x, y in world_map:
        #if (x != source_coord[0]) or (y != source_coord[1]): #if (x, y) != source_coord (x, y)
            #dist[x][y] = np.inf
            #prev[x][y] = None
            
        #q_cost.append((x, y), dist[x][y]) #(v, dist[v]) ????
        #q_cost.sort() #maybe sort by distances and not (x, y)?
        
    #for qx in range(NUM_X_CELLS):
        #for qy in range(NUM_Y_CELLS):
            #loc = (qx, qy)
            #q_cost
            #q_cost.append(get_travel_cost(source_vertex, loc), loc))
            #q_cost.sort() #sorts by first element, lowest to highest based on lowest travel cost
            
    dist = {} #dictionary
    prev = {} #dictionary
    
    #sets all distances to infinity and previous locations to None
    for x in range(NUM_X_CELLS):
        for y in range(NUM_Y_CELLS):
            dist[(x, y)] = math.inf
            prev[(x, y)] = None
            
    #set source vertex to be zero
    dist[(source_vertex[0], source_vertex[1])] = 0
    q_cost = dist.copy() #deep copy
                
    while q_cost: # is not empty:
        key_min = min(q_cost.keys(), key=(lambda k: q_cost[k])) # source: https://www.w3resource.com/python-exercises/dictionary/python-data-type-dictionary-exercise-15.php
        q_cost.pop(key_min) # extracts smallest element, ie min travel distance
        #dist[key_min[1]] = u[0] # sets distance to destination vertex
        neighbors = []
        if key_min[0] < NUM_X_CELLS - 1:
            neighbors.append([key_min[0]+1, key_min[1]]) # right
        if key_min[0] > 0:
            neighbors.append([key_min[0]-1, key_min[1]]) # left
        if key_min[1] < NUM_Y_CELLS - 1:
            neighbors.append([key_min[0], key_min[1]+1]) # top
        if key_min[1] > 0:
            neighbors.append([key_min[0], key_min[1]-1]) # bottom
        
        for neighbor in neighbors:
            #for q in q_cost:
            #if q[1] == neighbor: # if neighbor location is same as q location
            temp_cost = get_travel_cost(key_min, neighbor) + dist[key_min] # cost of neighbor from u + cost to get to u
            if temp_cost < dist[(neighbor[0], neighbor[1])]:
                dist[(neighbor[0], neighbor[1])] = temp_cost
                q_cost[(neighbor[0], neighbor[1])] = temp_cost
                prev[(neighbor[0], neighbor[1])] = key_min
                #dist[neighbor] = temp_cost
                #prev[neighbor] = key_min[1]
                    
                    #q_cost.remove(q)
                    #q_cost.insert((neighbor, dist[neighbor[0]][neighbor[1]]), 0)
    
    
    return prev


###################
# Part 1.3
###################
def reconstruct_path(prev, goal_vertex):
    """
    @param prev: Data structure mapping each vertex to the next vertex along the path back to "source" (from Dijkstra)
    @param goal_vertex: Map coordinates of the goal_vertex
    @return path: List of vertices where path[0] = source_vertex_ij_coords and path[-1] = goal_vertex_ij_coords
    """
    
    #path = [goal_vertex]
    #print(path)
    
    # Hint: Start at the goal_vertex and work your way backwards using prev until there's no "prev" left to follow.
    #       Then, reverse the list and return it!
    
    previous = goal_vertex.copy()
    path = [previous]
    previous = prev[(previous[0], previous[1])]
    #print(previous)
    #print(path)
    #print(prev[(previous[0], previous[1])])
    
    while previous is not None:
        path.insert(0, previous)
        #path.append(prev[(previous[0], previous[1])])
        previous = prev[(previous[0], previous[1])]
    
    return path


###################
# Part 1.4
###################
def visualize_path(path):
    """
    @param path: List of graph vertices along the robot's desired path    
    """
    global world_map
    n, m = world_map.shape
    
    # TODO: Set a value for each vertex along path in the world_map for rendering: 2 = Path, 3 = Goal, 4 = Start
    for x in range(n):
        for y in range(m):
            if (x, y) in path:
                world_map[x, y] = 2    # path node
            if (x, y) == path[-1]:
                world_map[x, y] = 3    # goal node
            if (x, y) == path[0]:
                world_map[x, y] = 4    # start node
            
    return
    

def main():
    global robot, state, sub_state, map
    global leftMotor, rightMotor, SIM_TIMESTEP, WHEEL_FORWARD, WHEEL_STOPPED, WHEEL_BACKWARDS
    global pose_x, pose_y, pose_theta, left_wheel_direction, right_wheel_direction

    last_odometry_update_time = None

    # Keep track of which direction each wheel is turning
    left_wheel_direction = WHEEL_STOPPED
    right_wheel_direction = WHEEL_STOPPED

    # Important IK Variable storing final desired pose
    target_pose = None # Populated by the supervisor, only when the target is moved.


    # Sensor burn-in period
    for i in range(10): robot.step(SIM_TIMESTEP)

    start_pose = csci3302_final_supervisor.supervisor_get_robot_pose()
    pose_x, pose_y, pose_theta = start_pose

    
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
            target_pose = csci3302_final_supervisor.supervisor_get_target_pose()
            world_map[transform_world_coord_to_map_coord(target_pose[:2])] = 3 # Goal vertex!
            print("New IK Goal Received! Target: %s" % str(target_pose))
            print("Current pose: [%5f, %5f, %5f]\t\t Target pose: [%5f, %5f, %5f]" % (pose_x, pose_y, pose_theta, target_pose[0], target_pose[1], target_pose[2]))
            populate_map(world_map)
            display_map(world_map)

        


        if state == 'get_path':
            ###################
            # Part 2.1a
            ###################       
            # Compute a path from start to target_pose
            start_x, start_y = transform_world_coord_to_map_coord([pose_x, pose_y])
            goal_x, goal_y = transform_world_coord_to_map_coord([target_pose[0], target_pose[1]])
            dijkstras = dijkstra([start_x, start_y])
            path = reconstruct_path(dijkstras, [goal_x, goal_y])
            visualize_path(path)
            #display_map(world_map)
            state = 'get_waypoint'
            #print(path)
            #pass
        elif state == 'get_waypoint':
            ###################
            # Part 2.1b
            ###################       
            # Get the next waypoint from the path
            if len(path) > 1: #is not empty
                #print(path)
                loc = path.pop(0)
                #print("current Location: ", loc)
                loc_coord = transform_map_coord_world_coord(loc)
                waypoint = transform_map_coord_world_coord(path[0])
                theta = math.atan2(waypoint[1] - loc_coord[1], waypoint[0] - loc_coord[0]) # source: https://www.w3schools.com/python/ref_math_atan2.asp
                pose = (waypoint[0], waypoint[1], theta) # (x, y, theta) of new location to go to
                state = 'move_to_waypoint'
            else:
                state = 'get_path'
            #pass
        elif state == 'move_to_waypoint':
            ###################
            # Part 2.1c
            ###################       

            # Hint: Use the IK control function to travel to the current waypoint
            # Syntax/Hint for using the IK Controller:
            # lspeed, rspeed = get_wheel_speeds(target_wp)
            # leftMotor.setVelocity(lspeed)
            # rightMotor.setVelocity(rspeed)    
            #pass
            wheel_speeds = get_wheel_speeds(pose)
            leftMotor.setVelocity(wheel_speeds[0])
            rightMotor.setVelocity(wheel_speeds[1])
            #left_wheel_direction = 
            #right_wheel_direction = 
            if wheel_speeds[0] == 0 and wheel_speeds[1] == 0:
                state = 'get_waypoint'
        else:
            # Stop
            left_wheel_direction, right_wheel_direction = 0, 0
            leftMotor.setVelocity(0)
            rightMotor.setVelocity(0)    
            #pass
            
            
        display_map(world_map)
    
    
if __name__ == "__main__":
    main()





