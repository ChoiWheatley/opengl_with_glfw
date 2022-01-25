#include "Projection.h"

glm::mat4 Projection::getMatrix() const
{
    return glm::mat4();
}

void Projection::addFOV(float offset)
{
}

Projection::Projection()
{
    aspectRatio = Constants::Camera::aspectRatio;
    near = Constants::Camera::near;
    far = Constants::Camera::far;
    fov = Constants::Camera::fov;
}

Projection::Projection(float aspectRatio, float near, float far, float fov)
    : aspectRatio{ aspectRatio }, near{ near }, far{ far }, fov{ fov }
{
}

