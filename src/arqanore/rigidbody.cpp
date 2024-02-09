#include "arqanore/rigidbody.h"
#include "arqanore/physics.h"
#include "arqanore/mathhelper.h"

arqanore::Vector3 arqanore::RigidBody::position() {
    auto value = this->transform.getPosition();
    auto result = Vector3(value.x, value.y, value.z);

    return result;
}

arqanore::Vector3 arqanore::RigidBody::linear_velocity() {
    auto value = this->body->getLinearVelocity();
    auto result = Vector3(value.x, value.y, value.z);

    return result;
}

arqanore::Vector3 arqanore::RigidBody::angular_velocity() {
    auto value = this->body->getAngularVelocity();
    auto result = Vector3(value.x, value.y, value.z);

    return result;
}

arqanore::Vector3 arqanore::RigidBody::linear_lock_axis() {
    auto value = this->body->getLinearLockAxisFactor();
    auto result = Vector3(value.x, value.y, value.z);

    return result;
}

arqanore::Vector3 arqanore::RigidBody::angular_lock_axis() {
    auto value = this->body->getAngularLockAxisFactor();
    auto result = Vector3(value.x, value.y, value.z);

    return result;
}

arqanore::Vector3 arqanore::RigidBody::force() {
    auto value = this->body->getForce();
    auto result = Vector3(value.x, value.y, value.z);

    return result;
}

arqanore::Vector3 arqanore::RigidBody::torque() {
    auto value = this->body->getTorque();
    auto result = Vector3(value.x, value.y, value.z);

    return result;
}

arqanore::Quaternion arqanore::RigidBody::rotation() {
    auto value = this->transform.getOrientation();
    auto result = Quaternion(value.x, value.y, value.z, value.w);

    return result;
}

float arqanore::RigidBody::mass() {
    return this->body->getMass();
}

float arqanore::RigidBody::linear_damping() {
    return this->body->getLinearDamping();
}

float arqanore::RigidBody::angular_damping() {
    return this->body->getAngularDamping();
}

bool arqanore::RigidBody::active() {
    return this->body->isActive();
}

bool arqanore::RigidBody::gravity_enabled() {
    return this->body->isGravityEnabled();
}

void arqanore::RigidBody::position(Vector3 value) {
    auto position = rp3d::Vector3(value.x, value.y, value.z);

    this->transform.setPosition(position);
    this->transform_prev = this->transform;
    this->body->setTransform(this->transform);
}

void arqanore::RigidBody::linear_velocity(arqanore::Vector3 value) {
    auto vec = rp3d::Vector3(value.x, value.y, value.z);
    this->body->setLinearVelocity(vec);
}

void arqanore::RigidBody::angular_velocity(arqanore::Vector3 value) {
    auto vec = rp3d::Vector3(value.x, value.y, value.z);
    this->body->setAngularVelocity(vec);
}

void arqanore::RigidBody::linear_lock_axis(arqanore::Vector3 value) {
    auto vec = rp3d::Vector3(value.x, value.y, value.z);
    this->body->setLinearLockAxisFactor(vec);
}

void arqanore::RigidBody::angular_lock_axis(arqanore::Vector3 value) {
    auto vec = rp3d::Vector3(value.x, value.y, value.z);
    this->body->setAngularLockAxisFactor(vec);
}

void arqanore::RigidBody::rotation(Quaternion value) {
    auto orientation = rp3d::Quaternion(value.x, value.y, value.z, value.w);

    this->transform.setOrientation(orientation);
    this->transform_prev = this->transform;
    this->body->setTransform(this->transform);
}

void arqanore::RigidBody::mass(float value) {
    this->body->setMass(value);
}

void arqanore::RigidBody::linear_damping(float value) {
    this->body->setLinearDamping(value);
}

void arqanore::RigidBody::angular_damping(float value) {
    this->body->setAngularDamping(value);
}

void arqanore::RigidBody::sleeping(bool value) {
    this->body->setIsSleeping(value);
}

void arqanore::RigidBody::active(bool value) {
    this->body->setIsActive(value);
}

void arqanore::RigidBody::gravity_enabled(bool value) {
    this->body->enableGravity(value);
}

arqanore::RigidBody::RigidBody() {
    auto position = rp3d::Vector3(0, 0, 0);
    auto rotation = rp3d::Quaternion::identity();

    this->transform = rp3d::Transform(position, rotation);
    this->transform_prev = rp3d::Transform(position, rotation);
    this->body = nullptr;
}

arqanore::RigidBody::RigidBody(unsigned int type) : RigidBody() {
    auto position = rp3d::Vector3(0, 0, 0);
    auto rotation = rp3d::Quaternion::identity();

    this->transform = rp3d::Transform(position, rotation);
    this->transform_prev = rp3d::Transform(position, rotation);
    this->body = Physics::world->createRigidBody(this->transform);

    if (type == 0) {
        this->body->setType(rp3d::BodyType::DYNAMIC);
    } else if (type == 1) {
        this->body->setType(rp3d::BodyType::STATIC);
    } else {
        throw std::runtime_error("Invalid RigidBody type");
    }
}

arqanore::RigidBody::RigidBody(unsigned int type, Vector3 position, Quaternion rotation) : RigidBody() {
    auto transform_pos = rp3d::Vector3(position.x, position.y, position.z);
    auto transform_rot = rp3d::Quaternion(rotation.x, rotation.y, rotation.z, rotation.w);

    this->transform = rp3d::Transform(transform_pos, transform_rot);
    this->transform_prev = rp3d::Transform(transform_pos, transform_rot);
    this->body = Physics::world->createRigidBody(this->transform);

    if (type == 0) {
        this->body->setType(rp3d::BodyType::DYNAMIC);
    } else if (type == 1) {
        this->body->setType(rp3d::BodyType::STATIC);
    } else {
        throw std::runtime_error("Invalid RigidBody type");
    }
}

bool arqanore::RigidBody::sleeping() {
    return this->body->isSleeping();
}

void arqanore::RigidBody::update(double factor) {
    auto transform_current = this->body->getTransform();

    this->transform = rp3d::Transform::interpolateTransforms(this->transform_prev, transform_current, factor);
    this->transform_prev = transform_current;
}

void arqanore::RigidBody::apply_force(Vector3 value) {
    this->body->applyWorldForceAtCenterOfMass(rp3d::Vector3(value.x, value.y, value.z));
}

void arqanore::RigidBody::apply_torque(Vector3 value) {
    this->body->applyWorldTorque(rp3d::Vector3(value.x, value.y, value.z));
}

void arqanore::RigidBody::reset_force() {
    this->body->resetForce();
}

void arqanore::RigidBody::reset_torque() {
    this->body->resetTorque();
}

void arqanore::RigidBody::add_collider(Collider &collider) {
    if (collider.shape == nullptr) {
        return;
    }

    this->body->addCollider(collider.shape, rp3d::Transform::identity());
}

void arqanore::RigidBody::dispose() {
    Physics::world->destroyRigidBody(this->body);
}