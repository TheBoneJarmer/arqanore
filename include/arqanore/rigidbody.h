#pragma once

#include <reactphysics3d/reactphysics3d.h>
#include "vector3.h"
#include "collider.h"

namespace arqanore {
    class RigidBody {
    private:
        rp3d::RigidBody *body;
        rp3d::Transform transform;
        rp3d::Transform transform_prev;

    public:
        Vector3 position();

        Vector3 linear_velocity();

        Vector3 angular_velocity();

        Vector3 linear_lock_axis();

        Vector3 angular_lock_axis();

        Vector3 force();

        Vector3 torque();

        Quaternion rotation();

        float mass();

        float linear_damping();

        float angular_damping();

        bool sleeping();

        bool active();

        bool gravity_enabled();

        void position(Vector3 value);

        void linear_velocity(Vector3 value);

        void angular_velocity(Vector3 value);

        void linear_lock_axis(Vector3 value);

        void angular_lock_axis(Vector3 value);

        void rotation(Quaternion value);

        void mass(float value);

        void linear_damping(float value);

        void angular_damping(float value);

        void sleeping(bool value);

        void active(bool value);

        void gravity_enabled(bool value);

        RigidBody();

        RigidBody(unsigned int type);

        RigidBody(unsigned int type, Vector3 position, Quaternion rotation);

        void update(double factor);

        void apply_force(Vector3 value);

        void apply_torque(Vector3 value);

        void reset_force();

        void reset_torque();

        void add_collider(Collider &collider);

        void dispose();
    };
}