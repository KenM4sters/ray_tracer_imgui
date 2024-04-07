#include "Raytracer.h"
#include "Renderer.h"

CollisionData Raytracer::TraceRay(Ray* ray) 
{
    // The following code firstly determines if any intersections are presenet between a line
    // (the ray), and a sphere (the sphere objects in the scene). Should there be any, then it
    // generates and pushes important information about the intersection into a CollisionData
    // object, which the function then returns to the renderer. 

    // Equation of a line (ray)
    //================================================================    
    // r(t) = ray.Origin + t(ray.Direction)
    //      = (0.0f, 0.0f, 0.0f) + t(uv.x, uv.y, -1.0f)
    //      = (tuv.x, tuv.y, t)
    //================================================================
    //
    // Equation of a Sphere (SceneObject)
    //================================================================
    // (x - pos.x)^2 + (y - pos.y)^z + (z - pos.z)^2 = r^2, where:
    //
    //           r = SphereObject.Radius,
    //           pos = SphereObject.Position
    //================================================================

    // For a line to intersect with a sphere, where an intersection can be thought of as a point of
    // contact between the line and the sphere's circumference, there must be at least one unique solution
    // to both the line and sphere equations, ie there must be at least one set of XYZ coordinates
    // that satisfy both equations.

    // In other words, if we substitute the arguments x, y, z of the line equation into the
    // equation of the sphere, then we should the equation should still make sense
    // (x^2 + y^2 + z^2 = r^2 ). If the equation doesn't stand true with the arguments of the
    // line, then there are NO solutions.

    // Resulting equation
    //================================================================
    //
    // ((t)dx - px)^2 + ((t)dx - px)^2 + ((t)dx - px)^2 = r^z, where:
    //           
    //            d = ray.Direction,
    //            p = sphere.Position,
    // 
    // (t^2dirx^2 - 2tdirxposx + posx^2) + (t^2diry^2 - 2tdiryposy + posy^2) + (t^2dirz^2 - 2tdirzposz + posz^2) = r^2
    //
    // t^2(dix^2 + diry^2 + dirz^2) + t(2dirxposx + 2diryposy + 2dirzposz) + (posx^2 + posy^2 + posz^2 - r^2) = 0
    // 
    // 
    //
    // t^2()
    //================================================================

    // Fetch Scene objects to test against.
    auto scene_objects = Renderer::GetActiveScene()->GetSceneObjects();

    float intersection_distance = std::numeric_limits<float>::max();
    uint32_t intersected_sphere_index = -1;
    

    float a  = glm::dot(ray->Direction, ray->Direction);

    for(int i = 0; i < scene_objects->size(); i++) 
    {
        auto& sphere = scene_objects->at(i);
        float b = glm::dot(ray->Direction, sphere.Position);
        float c = glm::dot(sphere.Position, sphere.Position);

        // -b +- sqrt(b^2 - 4ac) / 2a

        float discriminant = pow(b, 2.0f) - 4*a*c;
        if(discriminant < 0.0f)
            continue;
        
        float closest_intersection = -b - (discriminant / 2.0f*a);
            WR::Core::Logger::PrintInteger(closest_intersection);

        // second criteria ensures that only the closest sphere is recorded as the intersected object (rays don't just dissapear after colliding).
        if(closest_intersection > 0.0f && closest_intersection < intersection_distance)
        {
            intersection_distance = closest_intersection;
            intersected_sphere_index = i;
        }
    }

    if(intersected_sphere_index < 0)
        return RegisterMiss(ray);

    return HandleCollision(ray, intersection_distance, intersected_sphere_index);

}

CollisionData Raytracer::HandleCollision(Ray* ray, float distance, uint32_t obj_index) 
{
    CollisionData data;
    WR::Core::Logger::PrintInteger(distance);

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