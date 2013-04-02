Implementation Details:
==============================================================================================================================================================
1. All lights have a white diffuse light and a light gray ambient light. 
2. The materials are not colored with glColor(), instead the material color is decided only by glMaterialfv( )
3. Lights are all placed on different diagonals of the cube. 
4. There is no global Ambient light set. The openGL default global ambient light is what is seen on spheres when all lights are off. 

Enabled Techniques:
==============================================================================================================================================================
1. Back face culling.
2. Depth Buffer

Camera Motion:
==============================================================================================================================================================
1. Implemented an Arc Ball type camera motion using the mouse and the keys: 'a', 's', 'd', 'w'

Front Face Spheres:
==============================================================================================================================================================
1. Face 1 Spheres have only Ambient reflections. Even when all the lights are turned off, they're visible due to the ambient property.

Right Face Spheres:
==============================================================================================================================================================
1. Right Face spheres have only diffuse reflections. When all the lights are turned off, they're not visible at all!

Back Face Spheres:
==============================================================================================================================================================
1. Back Face Spheres have both ambient and diffuse relections enabled. 

Bottom Face Spheres:
==============================================================================================================================================================
1. Bottom Face Spheres have a fixed amount of red diffuse and ambient reflection. 
2. They have a specular reflective property for white light. 

Left Face Spheres:
==============================================================================================================================================================
1. Left Face Spheres has the spheres in the 2nd and 4th row with emissive property and the emitted light continuously changes.
2. Some other spheres in the first and the third row are reactive to only one color of emitted light.

Top Face Spheres:
==============================================================================================================================================================
1. Top Face Spheres have different properties in different rows.
2. First row has only Ambient reflection.
3. The second row has only Diffuse relection.
4. The third row has both ambient and diffuse reflections, with varying specular reflections.
5. The fourth row has only varying emissive property.