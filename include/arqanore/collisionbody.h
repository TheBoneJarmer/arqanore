#pragma once

#include <reactphysics3d/reactphysics3d.h>
#include "vector3.h"
#include "collider.h"

namespace arqanore {
    class CollisionBody {
    private:
        rp3d::CollisionBody *body;
        rp3d::Transform transform;

    public:
        bool active();

        Vector3 position();

        Quaternion rotation();

        void active(bool value);

        void position(Vector3 value);

        void rotation(Quaternion value);

        CollisionBody();

        CollisionBody(Vector3 position, Quaternion rotation);

        bool colliding(CollisionBody &other);

        void add_collider(Collider &collider);

        void dispose();
    };
}
