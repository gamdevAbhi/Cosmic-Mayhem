#include <engine/spriteRenderer.hpp>

// initialize the members of spriteRenderer
void Engine::SpriteRenderer::start()
{
    if(shader == nullptr)
    {
        shader = new Shader("\\resources\\shaders\\sprite_shader.vert", 
        "\\resources\\shaders\\sprite_shader.frag");
        if(shader->getStatus() != SHADER_NO_ERROR) std::cout << shader->getStatus() << std::endl;
    }

    vertices = std::vector<vertex>
    {
        vertex{glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
        vertex{glm::vec3(1.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
        vertex{glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
        vertex{glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)}
    };

    indices = std::vector<GLuint>
    {
        0, 1, 3,
        0, 2, 3
    };

    color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    vao = new VAO();
    vao->bind();
    vbo = new VBO(vertices.size() * sizeof(vertex), vertices.data());
    vbo->bind();
    ebo = new EBO(indices.size() * sizeof(GLuint), indices.data());
    ebo->bind();

    vao->link(*vbo, 0, 3, sizeof(vertex), (void*)0);
    vao->link(*vbo, 1, 2, sizeof(vertex), (void*)(3 * sizeof(float)));

    vbo->unbind();
    vao->unbind();
    ebo->unbind();

    order = 0;
}

// set draw order
void Engine::SpriteRenderer::setOrder(int index)
{
    if(index > -1) order = index;
}

// draw the actor
void Engine::SpriteRenderer::draw()
{
    shader->use();
    vao->bind();

    Actor* actor = getActor();
    Transform* transform = actor->getComponent<Transform>();
    glm::mat4 world_transform = transform->getMatrix();
    world_transform[3][2] = -order;
    
    Engine::Camera* camera = Engine::Camera::getRenderCamera();

    if(camera == nullptr) Handler::error("no rendering camera exist", getActor()->name);
    
    glm::mat4 camera_matrix = camera->getMatrix();

    glUniform4fv(shader->getLocation("color"), 1, &color[0]);
    glUniformMatrix4fv(shader->getLocation("camera_transform"), 1, GL_FALSE, &camera_matrix[0][0]);
    glUniformMatrix4fv(shader->getLocation("world_transform"), 1, GL_FALSE, &world_transform[0][0]);

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    vao->unbind();
}