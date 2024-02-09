#include "arqanore/collider.h"
#include "arqanore/physics.h"

/* COLLIDER */
arqanore::Collider::Collider() {
    this->shape = nullptr;
}

/* BOXCOLLIDER */
arqanore::BoxCollider::BoxCollider() : Collider() {

}

arqanore::BoxCollider::BoxCollider(float width, float height, float depth) : Collider() {
    auto size = rp3d::Vector3(width / 2.0f, height / 2.0f, depth / 2.0f);
    this->shape = Physics::engine.createBoxShape(size);
}

void arqanore::BoxCollider::dispose() {
    Physics::engine.destroyBoxShape((rp3d::BoxShape *) this->shape);
}

/* SPHERECOLLIDER */
arqanore::SphereCollider::SphereCollider() : Collider() {

}

arqanore::SphereCollider::SphereCollider(float radius) {
    this->shape = Physics::engine.createSphereShape(radius);
}

void arqanore::SphereCollider::dispose() {
    Physics::engine.destroySphereShape((rp3d::SphereShape *) this->shape);
}

/* CONCAVECOLLIDER */
arqanore::ConcaveCollider::ConcaveCollider() : Collider() {
    this->triangle_mesh = nullptr;

    for (int i = 0; i < 99; i++) {
        this->triangle_data[i] = nullptr;
    }
}

arqanore::ConcaveCollider::ConcaveCollider(Model &model) : Collider() {
    this->triangle_mesh = Physics::engine.createTriangleMesh();
    this->triangle_data_count = model.meshes.size();

    for (int i = 0; i < this->triangle_data_count; i++) {
        Mesh &mesh = model.meshes[i];

        this->triangle_data[i] = new rp3d::TriangleVertexArray(mesh.vertices.size(), mesh.vertices.data(), 3 * sizeof(float), mesh.indices.size() / 3, mesh.indices.data(), 3 * sizeof(int), rp3d::TriangleVertexArray::VertexDataType::VERTEX_FLOAT_TYPE, rp3d::TriangleVertexArray::IndexDataType::INDEX_INTEGER_TYPE);
        this->triangle_mesh->addSubpart(this->triangle_data[i]);
    }

    this->shape = Physics::engine.createConcaveMeshShape(this->triangle_mesh);
}

void arqanore::ConcaveCollider::dispose() {
    Physics::engine.destroyConcaveMeshShape((rp3d::ConcaveMeshShape *) this->shape);
    Physics::engine.destroyTriangleMesh(this->triangle_mesh);
}
