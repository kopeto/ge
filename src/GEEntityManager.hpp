#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// #include "Model.hpp"

struct Model;

namespace GE
{

    template <class DerivedEntityType, class BaseEntity>
    concept Derived = std::is_base_of_v<BaseEntity, DerivedEntityType>;



    template <typename BaseEntity>
    struct EntityManager
    {
        std::vector<BaseEntity *> Entities;
        std::vector<Model *> Models;

        BaseEntity *selected = nullptr;

        EntityManager(size_t size = 100)
        {
            Entities.reserve(size);
        }

        virtual ~EntityManager()
        {
            for (BaseEntity *e : Entities)
            {
                delete e;
            }
        }

        virtual void removeEntity(BaseEntity *e)
        {
            e->model = nullptr;
        }

        virtual const Model *createModel(Model *model)
        {
            return Models.emplace_back(model);
        }

        template <Derived<BaseEntity> DerivedEntityType, typename... Ts>
        DerivedEntityType &createEntity(const Model *model, Ts... vars)
        {
            DerivedEntityType *e = new DerivedEntityType(vars...);
            e->model = model;
            Entities.push_back(e);
            return *e;
        }
    };
} // namespace GE

#endif