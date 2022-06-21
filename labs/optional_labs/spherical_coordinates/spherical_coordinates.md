# Spherical Coordinates
This is an optional lab provided as an extra resource.

## Objective
Be able to understand aspects of spherical coordinates and simple
methodologies in user controls.

## Background
Cartesian coordinates can often be difficult to implement and understand mathematically in
spherical spaces. For this reason there is a coordinate transform to simplify computations between 
different points on a sphere. In practically any graphical application that involves a camera or 
controllable object, the spherical or polar coordinate system is used. The standard for 
implementing this on a production level is often done with quaternions but to simplify things we 
will be using euler angles for our computation.

## Yaw, pitch and roll

Yaw is a rotation around the height axis, pitch is a rotation around the strafe axis, and roll is a 
rotation on the depth axis. 

<p align="center"> <img src="spherical.png" alt="github issues" class="shadow" style="height:300px;width:auto;border-radius:5px;1"></p>

In computer graphics, strafe is the x-axis, height is the y-axis and depth is the z-axis. 
If we recall from linear algebra, an orthogonal vector can be created from two vectors by taking 
their cross product. Since direction is important in graphics, the positive direction of the x axis
is always asumed to be to the right and the positive direction of the y axis (height) is always 
assumed to be up. The only difference is the direction of the z-axis (depth). This can vary between
applications but for our purposes the direction will be toward the user. Lastly, if we ensure that 
that the two vectors we take the cross product of are orthogonal as well, the resulting three 
vectors will form an orthogonal basis.

# Design constraints

For the purpose of our system and requirements in implementing manual movement and its strategy, you 
will be required to implement pitch and yaw. We will be ignoring roll as it is normally not needed 
and often times dont have enough buttons without involving multiple key presses.

Two of the difficulties we face with implementing the manual strategy is supporting asynchronous key 
presses and ensuring that the drone is always moving in transformed direction. To calculate 
this we can not just interpolate on the z axis because the camera will not always be facing 
parallel to the depth axis and/or perpendicularly to the height axis. Therefore the transform for 
the resulting x y and z <b>position</b> will need to consider all three direction axes for each 
value. I.e. x will depend on all three axes, etc.

## Methodology

We will use two variables pitch and yaw represented in radians. We will also want to ensure that our 
pitch is never greater than pi or less than -pi in order to avoid the axes being flipped. The 
resulting calculations will be as follows for the drone forward direction.

```
Vec3 direction;
forward.x = cos(yaw) * cos(pitch);
forward.y = sin(pitch);
forward.z = sin(yaw) * cos(pitch);
direction = forward.normalize();
```

An orthogonal basis could be calculated from this but we would only do this if we were programming 
our own cameras from the ground up. We aren't. Luckily, three.js has its own cameras and will do 
this for us. We simply only need to know the forward direction of the new drone to return to the front 
end drone and camera.

## Handling the input

It would be a good idea to create a handler class that can be passed around so that input information 
can be accessed by whichever class needs it. Without using it, the code would rely on many getters and 
setters and that would be very inefficient. 

Regarding the difficulty of asynchronous key pressed two vectors for turn and translation should be used. A positive version and a negative version. When a negative key is pressed (back, left or down) this vector should be updated to -1. 
When a positive key is pressed (forward, up or right) the positive vector should be updated to 1. 
When any key is released the values should be set to 0. The purpose of this is so that if a 
positive and negative key are pressed they add to zero. For an example:

```
<-1, 0, -1> + <1, 0, 0> = <0, 0, -1>
```
The same principle will apply to turning. As well, similar to speed translation, a 
turn speed may be ideal to prevent undesirable rotation speeds. For fine tuning you may even consider
implementing a seperate speed for both pitch and yaw. Finally, the resulting calculation you will 
want to return is the position and direction. These values are passed to the front end. For the position 
to work correctly with the pitch and yaw however, you will want to calculate the new position using the 
new direction.