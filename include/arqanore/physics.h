#pragma once

#include <reactphysics3d/reactphysics3d.h>
#include "vector3.h"

namespace arqanore {
    class Physics {
        friend class Window;

        friend class CollisionBody;

        friend class RigidBody;

        friend class BoxCollider;

        friend class SphereCollider;

        friend class ConcaveCollider;

    private:
        static rp3d::PhysicsCommon engine;
        static rp3d::PhysicsWorld *world;

        static void init();

        static void update(double dt);

    public:
        static Vector3 gravity();

        static bool gravity_enabled();

        static bool sleeping_enabled();

        static float sleep_linear_velocity();

        static float sleep_angular_velocity();

        static float time_before_sleep();

        static void gravity(Vector3 value);

        static void gravity_enabled(bool value);

        static void sleeping_enabled(bool value);

        static void sleep_linear_velocity(float value);

        static void sleep_angular_velocity(float value);

        static void time_before_sleep(float value);
    };
}
