#pragma once

#include <reactphysics3d/reactphysics3d.h>
#include "model.h"

namespace arqanore {
    class Collider {
    public:
        rp3d::CollisionShape *shape;

        Collider();
    };

    class BoxCollider : public Collider {
    public:
        BoxCollider();

        BoxCollider(float width, float height, float depth);

        void dispose();
    };

    class SphereCollider : public Collider {
    public:
        SphereCollider();

        SphereCollider(float radius);

        void dispose();
    };

    class ConcaveCollider : public Collider {
    private:
        rp3d::TriangleVertexArray *triangle_data[99];
        rp3d::TriangleMesh *triangle_mesh;
        unsigned int triangle_data_count;

    public:
        ConcaveCollider();

        ConcaveCollider(Model &model);

        void dispose();
    };
}
