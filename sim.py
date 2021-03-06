import pyglet

"""
things to fo here:
 - simulate an labirynth with n * n squares with given n 
 - in each tick calculate the distance from the mouse to walls around
 - in each tick calculate power for the motors based on change in inputs and last motors power
 - determine where are walls and mark them on the virtual map
 - find the shortest virtual path for given start, end point on the map

library for visualisation: Pyglet - http://pyglet.org
shortest path algorithm: A* / Djistra 

predictions of movement and calculation of power
 - if input from left and right value are the same, mouse is in the middle of the cell width 
 - if input from main (heagding forward) sensor is lesser than previous and statement above is true we moving toward a wall 
 - ... 

rotating conditions:
 - ...
 - ...

"""

last = {
    "motors" : [
        0, 0
    ],
    "distances" : [
        0, 0, 0
    ],
    "turning_left" : False,
    "turning_right" : False
}

def turning_right ():
    pass

def turning_left ():
    pass

def update_motors_power (last : dict, distances : list, scale : int) -> tuple:
    last_distances = last["distances"]
    last_motors_power = last["motors"]
    motors_power = [0 for _ in range (len(last_motors_power))]
    if not last_distances.any(): # if it is the first incoming value
        if distances[0] > distances[-1]:
            motors_power[0] = -1
            motors_power[-1] = 1
        elif distances[-1] > distances[0]:
            motors_power[-1] = -1
            motors_power[1] = 1

    else:
        if distances[0] > distances[-1]:
            if distances[0] - distances[-1] < last_distances[0] - last_distances[-1]: # the rotation is working -> there is a wall on right 
                motors_power[0] = last_motors_power[0] / (scale * 2)
                motors_power[-1] = last_motors_power[-1] / (scale * 2)
            else: # there is not any wall on right 
                last["turning_right"] = True
                turning_right()
        elif distances[-1] > distances[0]:
            if distances[-1] - distances[0] < last_distances[-1] - last_distances[0]:
                motors_power[0] = last_motors_power[0] / (scale * 2)
                motors_power[-1] = last_motors_power[-1] / (scale * 2)
            else:
                last["turning_left"] = True
                turning_left()
    
    last["distances"] = distances
    last["motors"] = [x * scale for x in motors_power]

    return (motors_power[0], motors_power[1])

class Sim:

    def __init__(self) -> None:
        pass

