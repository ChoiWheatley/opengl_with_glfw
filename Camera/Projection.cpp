#include "Projection.h"
#include "Constants.h"

glm::mat4 Projection::getMatrix() const
{
    return glm::perspective(
        glm::radians(fov),
        aspectRatio,
        near,
        far
    );
}

void Projection::addFOV(float offset)
{
    fov += offset;
    if (fov > fovMax)
        fov = fovMax;
    if (fov < fovMin)
        fov = fovMin;
}

Projection::Projection()
{
    aspectRatio = Constants::Camera::aspectRatio;
    near = Constants::Camera::near;
    far = Constants::Camera::far;
    fov = Constants::Camera::fov;
    fovMin = Constants::Camera::fovMin;
    fovMax = Constants::Camera::fovMax;
}

Projection::Projection(float aspectRatio, float near, float far, float fov, float fovMin, float fovMax)
    : aspectRatio{ aspectRatio }, near{ near }, far{ far }, fov{ fov }, fovMin{ fovMin }, fovMax{ fovMax }
{
}

