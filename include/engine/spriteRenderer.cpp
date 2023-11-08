#include <engine/spriterenderer.hpp>

// get the color
glm::vec4 Engine::SpriteRenderer::getColor()
{
    return color;
}

// get sprite
Engine::Sprite* Engine::SpriteRenderer::getSprite()
{
    return sprite;
}

// set the color
void Engine::SpriteRenderer::setColor(glm::vec4 color)
{
    this->color = color;
}

// set sprite
void Engine::SpriteRenderer::setSprite(Sprite* sprite)
{
    if(sprite == nullptr) this->sprite = defaultSprite;
    else this->sprite = sprite;
}

// start function
void Engine::SpriteRenderer::start()
{
    color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    sprite = defaultSprite;
    order = 0;
    
    glm::vec2 position = getActor()->getComponent<Transform>()->getWorldPosition();
    glm::vec2 scale = getActor()->getComponent<Transform>()->getWorldScale();

    float x = std::abs(scale.x) * 2;
    float y = std::abs(scale.y) * 2;
    float diagonal = std::sqrt(std::pow(x, 2) + std::pow(y, 2));

    node = new Node(this, AABB(position.x, position.y, diagonal / 2.0f));

    while(true)
    {
        if(!root->boundary.contains(node->boundary)) root = root->expand(node->boundary);
        else break;
    }

    root->insert(node);
}

// on transform changed
void Engine::SpriteRenderer::onTransformChanged()
{
    glm::vec2 position = getActor()->getComponent<Transform>()->getWorldPosition();
    glm::vec2 scale = getActor()->getComponent<Transform>()->getWorldScale();

    float x = std::abs(scale.x) * 2;
    float y = std::abs(scale.y) * 2;
    float diagonal = std::sqrt(std::pow(x, 2) + std::pow(y, 2));

    AABB boundary = AABB(position.x, position.y, diagonal / 2.0f);
    
    while(true)
    {
        if(!root->boundary.contains(boundary)) root = root->expand(boundary);
        else break;
    }

    node->update(boundary, root);
}

// on destroy
void Engine::SpriteRenderer::onDestroy()
{
    node->destroy();
}

// initialize the members of sprite renderer
void Engine::SpriteRenderer::initialize()
{
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

    vao = new VAO();
    vao->bind();
    vbo = new VBO(vertices.size() * sizeof(vertex), vertices.data(), GL_STATIC_DRAW);
    vbo->bind();
    ebo = new EBO(indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
    ebo->bind();

    vao->link(*vbo, 0, 3, sizeof(vertex), (void*)0);
    vao->link(*vbo, 1, 2, sizeof(vertex), (void*)(3 * sizeof(float)));

    vbo->unbind();
    vao->unbind();
    ebo->unbind();

    shader = new Shader("\\resources\\shaders\\sprite_shader.vert", 
    "\\resources\\shaders\\sprite_shader.frag");
 
    if(shader->getStatus() != SHADER_NO_ERROR) Handler::error("can't make the default shader", 
    "sprite renderer");

    defaultSprite = new Sprite("\\resources\\sprites\\default_sprite.png");

    root = new QuadTree(AABB(0, 0, 100));
}

// renders sprites
void Engine::SpriteRenderer::draw()
{
    shader->use();
    vao->bind();

    Engine::Camera* camera = Engine::Camera::getRenderCamera();
    glm::mat4 camera_matrix = camera->getOrtho();

    Transform* transform = getActor()->getComponent<Transform>();
    glm::mat4 world_transform = transform->getMatrix();

    glUniform4fv(shader->getLocation("color"), 1, &color[0]);
    glUniformMatrix4fv(shader->getLocation("camera_transform"), 1, GL_FALSE, &camera_matrix[0][0]);
    glUniformMatrix4fv(shader->getLocation("world_transform"), 1, GL_FALSE, &world_transform[0][0]);
    glUniform1i(shader->getLocation("sprite"), 0);
    
    sprite->bind();

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    
    sprite->unbind();
    vao->unbind();
}