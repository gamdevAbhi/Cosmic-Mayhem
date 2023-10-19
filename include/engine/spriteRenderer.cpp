#include <engine/spriterenderer.hpp>

// initialize the members of spriteRenderer
void Engine::SpriteRenderer::initialize()
{
    // create shader
    shader = new Shader("\\resources\\shaders\\sprite_shader.vert", 
    "\\resources\\shaders\\sprite_shader.frag");
    if(shader->getStatus() != SHADER_NO_ERROR) Handler::error("can't make the default shader", 
    "sprite renderer");

    // create default sprite
    defaultSprite = new Sprite("\\resources\\sprites\\default_sprite.png");

    // create vertices
    vertices = std::vector<vertex>
    {
        vertex{glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
        vertex{glm::vec3(1.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
        vertex{glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
        vertex{glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)}
    };

    // create indices
    indices = std::vector<GLuint>
    {
        0, 1, 3,
        0, 2, 3
    };

    // creating vao, vbo and ebo
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
}

void Engine::SpriteRenderer::start()
{
    color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    sprite = defaultSprite;
    order = 0;
    add(this);
}

// set draw order
void Engine::SpriteRenderer::setOrder(unsigned int index)
{
    order = index;
    orderChanged();
}

// set sprite
void Engine::SpriteRenderer::setSprite(Sprite* sprite)
{
    if(sprite == nullptr) this->sprite = defaultSprite;
    else this->sprite = sprite;
}

// draw the actor
void Engine::SpriteRenderer::draw()
{
    shader->use();
    vao->bind();

    Engine::Camera* camera = Engine::Camera::getRenderCamera();
    glm::mat4 camera_matrix = camera->getMatrix();

    for(int i = 0; i < renderers.size(); i++)
    {
        Actor* actor = renderers[i]->getActor();
        
        if(actor->getActive() == false) continue;

        Transform* transform = actor->getComponent<Transform>();
        glm::mat4 world_transform = transform->getMatrix();

        glUniform4fv(shader->getLocation("color"), 1, &renderers[i]->color[0]);
        glUniformMatrix4fv(shader->getLocation("camera_transform"), 1, GL_FALSE, &camera_matrix[0][0]);
        glUniformMatrix4fv(shader->getLocation("world_transform"), 1, GL_FALSE, &world_transform[0][0]);
        glUniform1i(shader->getLocation("sprite"), 0);
        
        renderers[i]->sprite->bind();
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        renderers[i]->sprite->unbind();
    }
    

    vao->unbind();
}

void Engine::SpriteRenderer::onDestroy()
{
    remove(this);
}

// compare two sprite renderer
bool Engine::SpriteRenderer::compare(Engine::SpriteRenderer *left, Engine::SpriteRenderer *right)
{
    return left->order > right->order;
}

// get the index
unsigned int Engine::SpriteRenderer::getOrder()
{
    return order;
}

// add renderer to renderering
void Engine::SpriteRenderer::add(SpriteRenderer* renderer)
{
    renderers.push_back(renderer);
    shouldSort = true;
}

// remove renderer from rendering
void Engine::SpriteRenderer::remove(SpriteRenderer* renderer)
{
    int i = 0;

    while(i < renderers.size())
    {
        if(renderers[i] != renderer) 
        {
            i++;
            continue;
        }
        renderers.erase(renderers.begin() + i);
    }

    shouldSort = true;
}

// call when order is changed
void Engine::SpriteRenderer::orderChanged()
{
    shouldSort = true;
}

// calls before start drawing
void Engine::SpriteRenderer::beforeDraw()
{
    if(shouldSort == false) return;

    int index = 0;

    // removing null renderers
    while(index < renderers.size())
    {
        if(renderers[index] != nullptr) index++;
        else
        {
            renderers.erase(renderers.begin() + index);
        }
    }

    // sorting
    std::sort(renderers.begin(), renderers.end(), compare);
    shouldSort = false;
}