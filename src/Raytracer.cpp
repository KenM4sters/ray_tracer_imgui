#include "Raytracer.h"
#include "Renderer.h"

CollisionData Raytracer::TraceRay(Ray* ray) 
{
    // The following code firstly determines if any intersections are presenet between a line
    // (the ray), and a sphere (the sphere objects in the scene). Should there be any, then it
    // generates and pushes important information about the intersection into a CollisionData
    // object, which the function then returns to the renderer. 

    // -B +- sqrt(B^2 - 4AC) / 2A

    // (bx^2 + by^2 + bz^2)t^2 + (axbx + ayby + azbz)2t + (ax^2 + ay^2 + az^2 - r^2) = 0
    //
    //            A = (bx^2 + by^2 + bz^2)
    //            B = 2(axbx + ayby + azbz)
    //            C = (ax^2 + ay^2 + az^2 - r^2) where,
    //
    //            a = ray.Origin,
    //            b = ray.Direction

    // Fetch Scene objects to test against.
    auto scene_objects = Renderer::GetActiveScene()->GetSceneObjects();
    float intersection_distance = std::numeric_limits<float>::max();
    int intersected_sphere_index = -1;
    

    float A  = glm::dot(ray->Direction, ray->Direction); // ray.Direction doesn't change per sceneObject, so we'll declare A here.


    for(size_t i = 0; i < scene_objects->size(); i++) 
    {
        auto& sphere = scene_objects->at(i);

        // The equation of a sphere needs to its x, y and z components adjusted by the sphere's
        // position if it's not at the origin, which in our case it isn't, since that's where
        // are rays are casted from.
        //
        // The adjustment is simple - we just subtract the sphere's position from each component,
        // but re-substituting our ray equation into this new equation can get very messy and looks
        // a whole lot less intuitve, so instead, we'll redfine our a (ray.Origin) variable 
        // as "ray.Origin - sphere.Position" after expanding the origial equation out and let
        // glm compute the more complicated dot product.

        glm::vec3 origin = ray->Origin - sphere.Position;


        float B = 2*(glm::dot(ray->Direction, origin));
        float C = glm::dot(origin, origin) - (pow(sphere.Radius, 2));

        float discriminant = pow(B, 2.0f) - (4.0f*A*C);

        if(discriminant < 0.0f)
            continue;
        
        float closest_intersection = -B - (glm::sqrt(discriminant) / (2.0f*A));

        // second criteria ensures that only the closest sphere is recorded as the intersected object (rays don't just dissapear after colliding).
        if(closest_intersection > 0.0f && closest_intersection < intersection_distance)
        {
            intersection_distance = closest_intersection;
            intersected_sphere_index = (uint32_t)i;
        }
    }

    if(intersected_sphere_index < 0)
        return RegisterMiss(ray);

    return HandleCollision(ray, intersection_distance, intersected_sphere_index);

}

CollisionData Raytracer::HandleCollision(Ray* ray, float distance, uint32_t obj_index) 
{
    CollisionData data;
    data.DistanceFromCamera = distance;
    data.object_index = obj_index;

    return data;
}

CollisionData Raytracer::RegisterMiss(Ray* ray) 
{
    CollisionData data;
    data.DistanceFromCamera = -1.0f;
    return data;
}