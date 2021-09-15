#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#if defined(DEBUG) || defined(_DEBUG)
#define GLM_FORCE_MESSAGES
#endif
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

// Helper functions
#include "hzgl/Control.hpp"
#include "hzgl/Texture.hpp"
#include "hzgl/ResourceManager.hpp"

static int width = 800;
static int height = 600;
static float aspect = static_cast<float>(width)/static_cast<float>(height);

GLuint quadVAO;
GLuint buffers[2];

GLFWwindow *window;

hzgl::ImGuiControl guiControl;
hzgl::ResourceManager resources;

static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

static void init(void)
{
    // a quad defined in clip coordinata
    float vertices[] = {
        -1.0f, -1.0f,
         1.0f,  1.0f,
        -1.0f,  1.0f,
         1.0f, -1.0f,
        -1.0f, -1.0f,
         1.0f,  1.0f
    };

    // texcoord for the vertices above
    float texcoords[] = {
        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        1.0f, 1.0f
    };

    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(2, buffers);

    glBindVertexArray(quadVAO);

    // feed vertex data to the GPU
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texcoords), texcoords, GL_STATIC_DRAW);

    // VBO plumbing
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)(0));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(0));
    glEnableVertexAttribArray(1);

    // prepare the shader programs
    resources.LoadShaderProgram({
        {GL_VERTEX_SHADER, "../assets/shaders/passthrough.vert"},
        {GL_FRAGMENT_SHADER, "../assets/shaders/passthrough.frag"},
        }, "Passthrough");

    resources.LoadShaderProgram({
        {GL_VERTEX_SHADER, "../assets/shaders/passthrough.vert"},
        {GL_FRAGMENT_SHADER, "../assets/shaders/greyscale.frag"},
        }, "Greyscale");

    resources.LoadShaderProgram({
        {GL_VERTEX_SHADER, "../assets/shaders/passthrough.vert"},
        {GL_FRAGMENT_SHADER, "../assets/shaders/convulution.frag"},
        }, "Convolution");

    resources.LoadTexture("../assets/images/flower.png", GL_TEXTURE_2D);
    resources.LoadTexture("../assets/images/red-panda.png", GL_TEXTURE_2D);
    resources.LoadTexture("../assets/images/flower-and-bee.png", GL_TEXTURE_2D);

    guiControl.Init(window, "#version 410");

    glfwGetFramebufferSize(window, &width, &height);
    framebuffer_size_callback(window, width, height);

    glViewport(0, 0, width, height);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // enable optional functionalities
    glEnable(GL_DEPTH_TEST);
}

static void display(void)
{
    // common
    static int pIndex = 0;
    static int tIndex = 0;

    // greyscale
    static float strength = 1;

    // 3 by 3 convulution
    static float kernelWeight = 1;
    static std::vector<float> kernel(9);

    static std::vector<std::string> convOperators = {
        "Emboss",
        "Outline",
        "Sharpen",
        "Triangle Blur",
        "Sobel Horizontal",
        "Sobel Vertical",
        "Prewitt Horizontal",
        "Prewitt Vertical",
    };

    static std::vector<std::vector<float>> convKernels = {
        { // emboss
            -2, -1,  0,
            -1,  1,  1,
             0,  1,  2
        },
        { // outline
            -1, -1, -1,
            -1,  8, -1,
            -1, -1, -1
        },
        { // sharpen
             0, -1,  0,
            -1,  5, -1,
             0, -1,  0
        },
        { // triangle blur
            0.0625f, 0.125f, 0.0625f,
            0.1250f, 0.250f, 0.1250f,
            0.0625f, 0.125f, 0.0625f
        },
        { // sobel horizontal
            -1,  0,  1,
            -2,  0,  2,
            -1,  0,  1
        },
        { // sobel vertical
            1,  2,  1,
            0,  0,  0,
           -1, -2, -1
        },
        { // prewitt horizontal
            -1,  0,  1,
            -1,  0,  1,
            -1,  0,  1
        },
        { // prewitt vertical
            1,  1,  1,
            0,  0,  0,
           -1, -1, -1
        }
    };

    const auto textureNames = resources.GetLoadedTextureNames();
    const auto programNames = resources.GetLoadedShaderProgramNames();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    guiControl.BeginFrame(false);
        guiControl.RenderListBox("Images", textureNames, &tIndex);
        guiControl.RenderListBox("Effects", programNames, &pIndex);

        if (programNames[pIndex] == "Greyscale")
        {
            ImGui::SliderFloat("strength", &strength, 0.0f, 1.0f);
        }
        else if (programNames[pIndex] == "Convolution")
        {
            static int prevIndex = -1;
            static int oIndex = 0;

            guiControl.RenderListBox("3 by 3 Kernels", convOperators, &oIndex);

            if (prevIndex != oIndex)
            {
                prevIndex = oIndex;
                kernel = convKernels[oIndex];
            }

            guiControl.RenderDragMatrix3("Selected Kernel", kernel);

            float sum = 0;
            for (float k: kernel) sum += k;
            kernelWeight = (sum <= 0) ? 1: sum;
        }
    guiControl.EndFrame();

    GLuint texture = resources.GetTextureID(tIndex);
    GLuint program = resources.GetProgramID(pIndex);

    glUseProgram(program);

    hzgl::SetSampler(program, "uTexture", texture, 0);

    if (programNames[pIndex] == "Greyscale")
    {
        hzgl::SetFloat(program, "uStrength", 1, strength);
    }
    else if (programNames[pIndex] == "Convolution")
    {
        hzgl::SetFloatv(program, "uKernel", 9, kernel.data());
        hzgl::SetFloat(program, "uKernelWeight", 1, kernelWeight);
        hzgl::SetFloat(program, "uTextureSize", 2, resources.GetTextureWidth(tIndex), resources.GetTextureHeight(tIndex));
    }

    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
    glUseProgram(0);
}

void cleanup()
{
    glDeleteBuffers(2, buffers);
    glDeleteVertexArrays(1, &quadVAO);
    resources.ReleaseAll();
}

int main(void)
{
    // initialize GLFW
    if (!glfwInit())
        return -1;

    // use OpenGL 4.1 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // use 8x multi-sampling
    glfwWindowHint(GLFW_SAMPLES, 8);

    // TEMP: disable window resizing for now
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(width, height, "Image Processing", NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to create window." << std::endl;
        glfwTerminate();
        return -1;
    }

    // make the window's context current
    glfwMakeContextCurrent(window);

    // enable vertical sync
    glfwSwapInterval(1);

    // register callback functions
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // load GL functions using GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    init();

    // loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        display();

        // swap front and back buffers
        glfwSwapBuffers(window);

        // poll for and process events
        glfwPollEvents();
    }

    cleanup();
    glfwTerminate();

    return 0;
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    if (width == 0 || height == 0)
        return;

    glViewport(0, 0, width, height);
    aspect = static_cast<float>(width)/static_cast<float>(height);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    if (action == GLFW_PRESS)
    {
        switch (key)
        {
        case GLFW_KEY_Q:
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;
        case GLFW_KEY_F:
        case GLFW_KEY_PRINT_SCREEN:
            hzgl::TakeScreenshot(0, 0, width, height);
            break;
        default:
            break;
        }
    }
}
