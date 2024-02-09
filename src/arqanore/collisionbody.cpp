#include <arqanore/collisionbody.h>
#include "arqanore/mathhelper.h"
#include "arqanore/physics.h"

bool arqanore::CollisionBody::active() {
    if (this->body == nullptr) {
        return false;
    }

    return this->body->isActive();
}

arqanore::Vector3 arqanore::CollisionBody::position() {
    auto value = this->transform.getPosition();
    auto result = Vector3(value.x, value.y, value.z);

    return result;
}

arqanore::Quaternion arqanore::CollisionBody::rotation() {
    auto value = this->transform.getOrientation();
    auto result = Quaternion(value.x, value.y, value.z, value.w);

    return result;
}

void arqanore::CollisionBody::active(bool value) {
    if (this->body == nullptr) {
        return;
    }

    this->body->setIsActive(value);
}

void arqanore::CollisionBody::position(Vector3 value) {
    auto position = rp3d::Vector3(value.x, value.y, value.z);

    this->transform.setPosition(position);
    this->body->setTransform(this->transform);
}

void arqanore::CollisionBody::rotation(Quaternion value) {
    auto orientation = rp3d::Quaternion(value.x, value.y, value.z, value.w);

    this->transform.setOrientation(orientation);
    this->body->setTransform(this->transform);
}

arqanore::CollisionBody::CollisionBody() {
    auto position = rp3d::Vector3(0, 0, 0);
    auto rotation = rp3d::Quaternion::identity();

    this->transform = rp3d::Transform(position, rotation);
    this->body = Physics::world->createCollisionBody(this->transform);
}

arqanore::CollisionBody::CollisionBody(Vector3 position, Quaternion rotation) {
    auto transform_pos = rp3d::Vector3(position.x, position.y, position.z);
    auto transform_rot = rp3d::Quaternion(rotation.x, rotation.y, rotation.z, rotation.w);

    this->transform = rp3d::Transform(transform_pos, transform_rot);
    this->body = Physics::world->createCollisionBody(this->transform);
}

void arqanore::CollisionBody::add_collider(arqanore::Collider &collider) {
    if (collider.shape == nullptr) {
        return;
    }

    this->body->addCollider(collider.shape, rp3d::Transform::identity());
}

void arqanore::CollisionBody::dispose() {
    Physics::world->destroyCollisionBody(this->body);
}

bool arqanore::CollisionBody::colliding(CollisionBody &other) {
    return Physics::world->testOverlap(this->body, other.body);
}
