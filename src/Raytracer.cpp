#include "Raytracer.h"

CollisionData Raytracer::TraceRay(Ray* ray, SceneObject* sceneObj) 
{
    for(int i = 0; i < m_sceneObjects->size(); i++) 
    {
        TraceRay(ray, &m_sceneObjects->at(i));
    }
}

CollisionData Raytracer::HandleCollision(Ray* ray, float distance, uint32_t object_index) 
{

}

CollisionData Raytracer::RegisterMiss(Ray* ray) 
{
    
}