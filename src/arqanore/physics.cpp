#include "arqanore/physics.h"

rp3d::PhysicsCommon arqanore::Physics::engine;

rp3d::PhysicsWorld *arqanore::Physics::world;

void arqanore::Physics::init() {
    world = engine.createPhysicsWorld();
}

void arqanore::Physics::update(double dt) {
    world->update(dt);
}

arqanore::Vector3 arqanore::Physics::gravity() {
    auto vec = world->getGravity();
    return Vector3(vec.x, vec.y, vec.z);
}

bool arqanore::Physics::gravity_enabled() {
    return world->isGravityEnabled();
}

bool arqanore::Physics::sleeping_enabled() {
    return world->isSleepingEnabled();
}

float arqanore::Physics::sleep_linear_velocity() {
    return world->getSleepLinearVelocity();
}

float arqanore::Physics::sleep_angular_velocity() {
    return world->getSleepAngularVelocity();
}

float arqanore::Physics::time_before_sleep() {
    return world->getTimeBeforeSleep();
}

void arqanore::Physics::gravity(arqanore::Vector3 value) {
    auto vec = rp3d::Vector3(value.x, value.y, value.z);
    world->setGravity(vec);
}

void arqanore::Physics::gravity_enabled(bool value) {
    world->setIsGravityEnabled(value);
}

void arqanore::Physics::sleeping_enabled(bool value) {
    world->enableSleeping(value);
}

void arqanore::Physics::sleep_linear_velocity(float value) {
    world->setSleepLinearVelocity(value);
}

void arqanore::Physics::sleep_angular_velocity(float value) {
    world->setSleepAngularVelocity(value);
}

void arqanore::Physics::time_before_sleep(float value) {
    world->setTimeBeforeSleep(value);
}
