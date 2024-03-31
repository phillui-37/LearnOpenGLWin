#include "Const.h"
#ifdef LESSON_1_3
#include <filesystem>

#include "1_3_Shaders.h"
#include "util.h"
#include "Shader.h"

#define EX2

constexpr float vertices[] = {
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
#ifdef EX1
     0.0f, -1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
#else
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  // top 
#endif
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


GLFWwindow* init(unsigned w, unsigned h)
{
    // init
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create window
    auto window = glfwCreateWindow(w, h, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);

    // ensure GLAD init correctly
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    return window;
};

void setup_vertex(unsigned* VAO, unsigned* VBO)
{
    glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(*VAO);

    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void loop(GLFWwindow* window, Shader& shader, const unsigned& VAO)
{
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
#ifdef EX2
    shader.setFloat("xOffset", 0.5f);
#endif
    shader.use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
    glfwPollEvents();
};

int Lesson::start(unsigned w, unsigned h)
{
    auto window = init(w, h);
    if (window == nullptr) return -1;

#ifdef EX2
    auto shader = Shader("shader/1_3_ex2.vert", "shader/1_3.frag");
#else
    auto shader = Shader("shader/1_3.vert", "shader/1_3.frag");
#endif

    unsigned VAO, VBO;
    setup_vertex(&VAO, &VBO);

    while (!glfwWindowShouldClose(window))
        loop(window, shader, VAO);

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();

    return 0;
};


#endif
