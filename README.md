*This project has been created as part of the 42 curriculum by avaliull, kjongeri*

# Description

The goal of this project was to learn about raytracing. A method of computing 3D graphics by shooting rays from a virtual camera.
If the ray hits an object you calculate if it's currently being lit or if it's in shadow. Raytracing and the even more realistic pathtracing can create very realistic images. We implemented both.
The program reads from a .rt file. The .rt file contains the coordinates, sizes and colors of the objects. From this .rt file we create a 3D scene and render it.
By default, the project runs a simple raytracing algorithm. There is an option to turn on path tracing and some advanced rendering features. They will be described below.

# Instructions

- compile the program by going to our raytracer directory and run: make
- then use the program by running: ./minirt [.rt]
- you can add the --il (indirect lighting) flag to enable path tracing

we have provided a lot of .rt files with the project, but you can also make your own by following these rules:

-  The first piece of information for each element is the type identifier (composed
of one or two characters), followed by all specific information for each object
in a strict order such as:

- Ambient lighting:
A 0.2 255,255,255
    identifier: A
    ambient lighting ratio in the range [0.0,1.0]: 0.2
    R, G, B colors in the range [0-255]: 255, 255, 255

- Camera:
C -50.0,0,20 0,0,1 70
    identifier: C
    x, y, z coordinates of the viewpoint: -50.0,0,20
    3D normalized orientation vector, in the range [-1,1] for each x, y, z axis: 0.0,0.0,1.0
    FOV: Horizontal field of view in degrees in the range [0,180]: 70

- Light:
L -40.0,50.0,0.0 0.6 10,0,255
    identifier: L
    x, y, z coordinates of the light point: -40.0,50.0,0.0
    the light brightness ratio in the range [0.0,1.0]: 0.6
    (unused in mandatory part) R, G, B colors in the range [0-255]: 10, 0, 255

- Sphere:
sp 0.0,0.0,20.6 12.6 10,0,255
    identifier: sp
    x, y, z coordinates of the sphere center: 0.0,0.0,20.6
    the sphere diameter: 12.6
    R,G,B colors in the range [0-255]: 10, 0, 255

- Plane:
pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
    identifier: pl
    x, y, z coordinates of a point in the plane: 0.0,0.0,-10.0
    3D normalized normal vector, in the range [-1,1] for each x, y, z axis:
    0.0,1.0,0.0
    R,G,B colors in the range [0-255]: 0,0,225

- Cylinder:
cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
    identifier: cy
    x, y, z coordinates of the center of the cylinder: 50.0,0.0,20.6
    3D normalized vector of axis of cylinder, in the range [-1,1] for each x, y,
    axis: 0.0,0.0,1.0
    the cylinder diameter: 14.2
    the cylinder height: 21.42
    R, G, B colors in the range [0,255]: 10, 0, 255

- Quad:
qu 0,0,0 555,0,0 0,0,555 0,0,225
    identifier: qu
    Q, a 3D vector representing the the starting corner
    u, a 3D vector representing the first side. Q+u gives one of the corners adjacent to Q
    v, a 3D vector representing the second side. Q+v gives the other corner adjacent to Q
    R,G,B colors in the range [0-255]: 0,0,225

# Materials

You can add material properties to objects by adding the name of the material after RGB specification.
-   LAMBERTIAN - the default option, not specified in the file: makes the object matte
-   METAL: makes the object reflective
-   EMIT: make the object emit light. This function is unfinished. The code that makes the object emit
light is in place, but the parser does not handle the additional information required. As a result,
objects will always appear dark when EMIT is assigned.

-   Example of a sphere descrition for a .rt file with METAL property:
sp 0.0,0.0,20.6 12.6 10,0,255 METAL


# Resources

book series on raytracing(actually path tracing):
https://raytracing.github.io/books/RayTracingInOneWeekend.html
https://raytracing.github.io/books/RayTracingTheNextWeek.html

video on raytracing math: https://www.youtube.com/watch?v=4NshnkzOdI0

explanations on how raytracing works:
https://www.youtube.com/watch?v=H5TB2l7zq6s
https://www.youtube.com/watch?v=ezXGTRSx1g8
https://www.youtube.com/watch?v=nOCPpT-Sn0A
https://www.youtube.com/watch?v=Qz0KTGYJtUk

playlist on linear algebra:
https://www.youtube.com/watch?v=fNk_zzaMoSs&list=PLZHQObOWTQDPD3MizzM2xVFitgF8hE_ab

MLX42 wiki for the graphical library:
https://github.com/codam-coding-college/MLX42/wiki

kjongeri used ai to better understand some of the concepts in rayTracingInOneWeekend and to help come up with a good way to deal with the cylinders. Also some debugging.
