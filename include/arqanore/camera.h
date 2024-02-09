#pragma once

#include "vector3.h"
#include "quaternion.h"

namespace arqanore {
    class Camera {
    public:
        Vector3 position;
        Quaternion rotation;
        float fov;
        float near;
        float far;

        Camera();
    };
}