#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <btBulletDynamicsCommon.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Model;

struct BaseEntity
{
    BaseEntity()
    {
        m_id = id++;
    };

    virtual ~BaseEntity()
    {
        printf("BaseEntity ID:%u deleted\n", m_id);
    }

    virtual void updateModelTransform() = 0;
    virtual glm::mat4 getModelTransformationMatrix() const = 0;

    static inline unsigned int id{0};

    unsigned int m_id;
    const Model *model = nullptr;

    glm::vec3 position{0, 0, 0};
    glm::mat4 rotation{0.0};
    glm::vec3 velocity{0, 0, 0};

    bool selected = false;
};

struct BasicSphere : BaseEntity, btRigidBody
{
    BasicSphere(glm::vec3 _pos, glm::vec3 _velocity, float _radius)
        : btRigidBody{btRigidBody::btRigidBodyConstructionInfo(1.0, nullptr, new btSphereShape(_radius))}, radius{_radius}
    {
        velocity = _velocity;
        setWorldTransform(btTransform(btQuaternion(0, 0, 0, 1), btVector3(_pos.x, _pos.y, _pos.z)));
        setLinearVelocity(btVector3(velocity.x, velocity.y, velocity.z));
        setMassProps
        position = _pos;
        std::printf("Entity<Ball> ID:%u\n", m_id);
    }

    ~BasicSphere() override
    {
        std::printf("Entity<Ball> ID:%u deleted | ", m_id);
    }

    void updateModelTransform() override
    {
        btTransform t = getWorldTransform();
        position = {t.getOrigin().getX(), t.getOrigin().getY(), t.getOrigin().getZ()};
        btQuaternion rot = t.getRotation();
        rotation = glm::rotate(glm::mat4(1.0), rot.getAngle(), glm::vec3(rot.getAxis().getX(), rot.getAxis().getY(), rot.getAxis().getZ()));
        velocity = {getLinearVelocity().getX(), getLinearVelocity().getY(), getLinearVelocity().getX()};
    }

    glm::mat4 getModelTransformationMatrix() const override
    {
        glm::vec3 scale{radius};
        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0), position);
        glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0), scale);
        return translationMatrix * rotation * scaleMatrix;
    }

    float radius;
    bool selected = false;
};

// struct Ground : BaseEntity
// {
//     Ground(glm::vec3 _pos, glm::vec2 _dimensions, glm::mat4 _init_rotation = glm::mat4(0));
//     ~Ground() override;

//     void updateModelTransform() override;
//     glm::mat4 getModelTransformationMatrix() const override;

//     glm::vec2 dimensions;
// };

// struct ThrowingCube : BaseEntity
// {
//     ThrowingCube(glm::vec3 _pos, glm::vec3 _dim, glm::vec3 vel, glm::mat4 _init_rotation = glm::mat4(0));
//     ~ThrowingCube() override;

//     void updateModelTransform() override;
//     glm::mat4 getModelTransformationMatrix() const override;

//     glm::vec3 velocity;
//     glm::vec3 dimensions;
//     bool selected = false;
// };

// struct Donut : BaseEntity
// {
//     Donut(glm::vec3 _pos, glm::vec3 vel, float radius);
//     ~Donut() override;

//     void updateModelTransform() override;
//     glm::mat4 getModelTransformationMatrix() const override;

//     glm::vec3 velocity;
//     float radius;
//     bool selected = false;
// };

#endif