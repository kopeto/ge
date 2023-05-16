
// GLEW needs to be included first
#include <GL/glew.h>

// GLFW is included next
#include <GLFW/glfw3.h>
#include <iostream>

#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <btBulletDynamicsCommon.h>

#include "GEPhysics.hpp"
#include "Render.hpp"
#include "GEEntityManager.hpp"
#include "GEEntity.hpp"

#define MAX(X, Y) ((X > Y) ? X : Y)
#define MIN(X, Y) ((X < Y) ? X : Y)

unsigned int WIDTH = 1600;
unsigned int HEIGHT = 1200;

GLFWwindow *InitDefaults();


// // camera
Camera camera(INITIAL_POS);

// Entity Manager
GE::EntityManager<BaseEntity> EntManager{};

// // PHYSICS
GE::Physics<BaseEntity> WorldPhysics{};

// // RENDER
GE::Render render{EntManager, (int)WIDTH, (int)HEIGHT};


int main(int argc, char **argv)
{
    GLFWwindow *window = InitDefaults();

    BasicSphere* sphere = new BasicSphere(glm::vec3{0,0,0}, glm::vec3{0,0,0}, 1.0);
    WorldPhysics.addBodyToWorld(sphere);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    //  RENDER LOOP                                                                                       //
    ////////////////////////////////////////////////////////////////////////////////////////////////////////

    while (!glfwWindowShouldClose(window))
    {
        static float last_frame = glfwGetTime();
        static float now = last_frame;
        static float dt  = 0.0f;
        // Handle events
        if ( glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS )         glfwSetWindowShouldClose(window, true);
        if ( glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS )    glfwSetWindowShouldClose(window, true);

        now = glfwGetTime();
        dt = now - last_frame;
        last_frame = now;

        WorldPhysics.step(dt);
        if(sphere)
            printf("%.3lf \n",sphere->getWorldTransform().getOrigin().getY());
        
        glfwSwapInterval(1);
        glfwSwapBuffers(window);
        glfwPollEvents();

    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////

    glfwTerminate();

    return 0;
}

GLFWwindow *InitDefaults()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL TESTS", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(1);
    }
    glfwMakeContextCurrent(window);
    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    GLFWcursor* customCursor = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
    if(customCursor)
        glfwSetCursor(window, customCursor);
    else
        printf("Error creating a custom cursor\n");

    glfwSetCursorPos(window, 100.0, 100.0);

    glewInit();

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    return window;
}

