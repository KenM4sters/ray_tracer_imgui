#pragma once
#include "Core.h"
#include "Scene.h"

/**
 * Don't get confused between Raytracer and Renderer - this Raytacer class is solely designed to handle
 * the copmutations behind calculating intersections with rays and objects, and returning those
 * results to the renderer for the actual texture rendering. 
 * 
 * Nothing application-specific is going on here - just maths.  
*/

/*
 * A very simple struct that simply holds all the information the Raytracer will need to trace 
 * a ray through 3D space.
*/
struct Ray {
    glm::vec3 Origin;
    glm::vec3 Direction;
};

struct CollisionData {
    glm::vec3 WorldPosition; // Clarifying that it's not relative to an object or something.
    glm::vec3 Normal;
    float DistanceFromCamera = -1.0f; // Which is the origin for now.

    uint32_t object_index;
};

/*
 * Since the Raytracer really isn't specific to any one class, although in this case the Renderer
 * is the only class that happens to need it, I've decided to make its functions static. 
 * 
 * A Raytracer object doesn't really make much sense to me, since it's more of a utility class 
 * like Time, and just helps the renderer compute ray tracing. 
*/
class Raytracer {
    public:
        static CollisionData TraceRay(Ray* ray);
        static CollisionData HandleCollision(Ray* ray, float distance, uint32_t obj_index);
        static CollisionData RegisterMiss(Ray* ray);

        static std::shared_ptr<std::vector<SceneObject>> m_sceneObjects;
};

