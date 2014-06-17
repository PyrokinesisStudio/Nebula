# Nebula

3D Game Engine in c++

## Dependencies

- GLFW
- Boost
- PhysX

## Testing

For consideration for merging into master, GRU/test/Window must:
- ``view free``
    - nsew movement
- ``gui terminal``
    - rendering over scene
    - text entry
    - commands working
    - toggle enable/disable
- cube scene
    - lights rendering properly
    - cubes rendering properly

## News

Nebula is mergin into GRU. All my game engine code is being condesend and put in GRU.

## News

The Nebula library is merging into GRU as part of my campaign to reduce my game engine to a single static library. I am also replacing some of my own implementations with boost in order to reduce the size of my code. Once Nebula is merged into GRU, GRU will be renamed Nebula.

## TODO

- Reflections
- Shaddows
- Smoke
- Stenciling
- Fog
- Curved Reflections
- Find on internet code to parse PLY files. Or some other standard for 3d model storage.

## Rendering Ideas

### Curved reflections

#### Geometry Based Methods

In geometry-based methods, each vertex of a reflected object is transformed by the reflector and the reflected object is then constructed normally using the transformed vertices.

##### Explosion map

A sphere surrounds the reflecting surface. The surface oif the sphere is divided up based on which triangle of the reflector reflects that region of space. The surface of the sphere is mapped to the circle. The explosion map is implemented using a texture or frame buffer object. The reflector is rendered with shaders that transform the verticies to the circle. This scene is rendered to a texture or FBO. This object is then used to determine the triangle which reflects each vertex of each reflected object.

##### V-Clip variant (concept)

Since the explosion map can be inaccurate base on the radius of the sphere and the distance of the reflected object, a more accurate method is sought. Using something like the V-Clip algorithm, represent the region of space which a triangle reflects as a voronoi region. The V-Clip algorithm would need to be adapted since the face-edge planes are no longer orthogonal to the faces, nor are they necessarily a standard plane. Also, if vertex normals are averaged and not per-face, the edge regions will be non-existant.



