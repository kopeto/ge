#ifndef RENDER_HPP
#define RENDER_HPP

#include <glm/glm.hpp>

#include "Render_Model.hpp"
#include "Render_Shader.hpp"
#include "Render_Camera.hpp"
#include "Render_Skybox.hpp"
#include "Render_Framebuffer.hpp"
#include "Physics.hpp"
#include "Render_Light.hpp"
#include "EntityManager.hpp"

namespace GE
{

    struct Render
    {
        Render() = delete;
        Render(EntityManager &entMan, int _w, int _h);

        void RenderScene(Shader *shader, Camera &camera, Light &light) const;

    private:
        int src_W, src_H;
        EntityManager &entityManager;

        void DrawEntity(Entity *e, Shader *shader, Camera &camera, Light &light) const;
    };
} // namespace GE

#endif