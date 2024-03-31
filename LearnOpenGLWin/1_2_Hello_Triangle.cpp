#include "Const.h"
#ifdef LESSON_1_2
#include <filesystem>

#include "1_2_Hello_Triangle.h"
#include "util.h"

// #define EX1
#define EX2

#ifdef EX2
#include <vector>
#endif

constexpr float vertices[] = {
#ifdef EX1
    0.5f, 0.5f, 0.0f, // top right
    0.5f, -0.5f, 0.0f, // bottom right
    -0.5f, 0.5f, 0.0f, // top left
    0.5f, -0.5f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, // bottom left
    -0.5f, 0.5f, 0.0f, // top left
#elif defined EX2
    0.5f, 0.5f, 0.0f, // top right
    0.5f, -0.5f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, // bottom left
    1.0f, 1.0f, 0.0f, // top right
    1.0f, 0.0f, 0.0f, // bottom right
    0.0f, 0.0f, 0.0f, // bottom left
#else
    0.5f, 0.5f, 0.0f, // top right
    0.5f, -0.5f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, // bottom left
    -0.5f, 0.5f, 0.0f, // top left
#endif
};
constexpr unsigned int indices[] = {
    // note that we start from 0!
    0, 1, 3, // first Triangle
    1, 2, 3, // second Triangle
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

int setup_shader(const char* const* vert, const char* const* frag, unsigned* program)
{
    const unsigned vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, vert, NULL);
    glCompileShader(vertShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return -1;
    }

    unsigned fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, frag, NULL);
    glCompileShader(fragShader);
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        return -1;
    }

    *program = glCreateProgram();
    glAttachShader(*program, vertShader);
    glAttachShader(*program, fragShader);
    glLinkProgram(*program);

    glGetProgramiv(*program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(*program, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return -1;
    }
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    return 0;
}

#ifdef EX2
void setup_vertex(std::vector<unsigned>& VAO, std::vector<unsigned>& VBO)
#else
void setup_vertex(unsigned* VAO, unsigned* VBO, unsigned* EBO)
#endif
{
#ifdef EX2
    for (int i = 0; i < VAO.size(); ++i)
    {
        glGenVertexArrays(1, &VAO[i]);
        glGenBuffers(1, &VBO[i]);
        glBindVertexArray(VAO[i]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(i * 9 * sizeof(float)));
        glEnableVertexAttribArray(0);
    }
#else
    glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBO);
    glGenBuffers(1, EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(*VAO);

    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
#endif
#if !defined EX1 && !defined EX2 && !defined EX3
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
#endif



    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
#if !defined EX1 && !defined EX2 && !defined EX3
    glBindBuffer(GL_ARRAY_BUFFER, 0);
#endif


    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


    // uncomment this call to draw in wireframe polygons.
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

#ifdef EX2
void loop(GLFWwindow* window, const unsigned* program, const std::vector<unsigned>& VAO)
#else
void loop(GLFWwindow* window, const unsigned* program, const unsigned* VAO)
#endif
{
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // draw our first triangle
    glUseProgram(*program);
#ifndef EX2
    glBindVertexArray(*VAO);
#else
    for (auto _vao : VAO)
    {
        glBindVertexArray(_vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
#endif
    // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
#ifdef EX1
    glDrawArrays(GL_TRIANGLES, 0, 6);
#elif !defined EX2
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
#endif
    // glBindVertexArray(0); // no need to unbind it every time 

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
    glfwPollEvents();
};

int Lesson::start(unsigned w, unsigned h)
{
    auto window = init(w, h);
    if (window == nullptr) return -1;

    const auto vert = load_shader(Vertex, "1_2");
    const auto frag = load_shader(Fragment, "1_2");
    const char* c_vert = &vert[0];
    const char* c_frag = &frag[0];
    unsigned program;
    if (setup_shader(&c_vert, &c_frag, &program) != 0) return -1;

#ifdef EX2
    std::vector<unsigned> VAO{0,0}, VBO{0,0};
    setup_vertex(VAO, VBO);
#else
    unsigned VAO, VBO, EBO;
    setup_vertex(&VAO, &VBO, &EBO);
#endif
    
    while (!glfwWindowShouldClose(window))
#ifdef EX2
        loop(window, &program, VAO);
#else
        loop(window, &program, &VAO);
#endif
    glfwTerminate();
    return 0;
};


#endif
