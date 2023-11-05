#include <engine/billboard.hpp>

// set the color
void Engine::Billboard::setColor(glm::vec4 color)
{
    this->color = color;
}

// set sprite
void Engine::Billboard::setSprite(Sprite* sprite)
{
    if(sprite == nullptr) this->sprite = defaultSprite;
    else this->sprite = sprite;
}

// get the color
glm::vec4 Engine::Billboard::getColor()
{
    return color;
}

// get sprite
Engine::Sprite* Engine::Billboard::getSprite()
{
    return sprite;
}

void Engine::Billboard::start()
{
    color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    sprite = defaultSprite;
    order = 0;
    
    glm::vec2 position = getActor()->getComponent<RectTransform>()->getScreenPosition();
    glm::vec2 scale = getActor()->getComponent<RectTransform>()->getScreenScale();

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

void Engine::Billboard::onTransformChanged()
{
    glm::vec2 position = getActor()->getComponent<RectTransform>()->getScreenPosition();
    glm::vec2 scale = getActor()->getComponent<RectTransform>()->getScreenScale();

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

void Engine::Billboard::onDestroy()
{
    node->destroy();
}

// initialize the members of billboard
void Engine::Billboard::initField()
{
    shader = new Shader("\\resources\\shaders\\billboard_shader.vert", 
    "\\resources\\shaders\\billboard_shader.frag");
 
    if(shader->getStatus() != SHADER_NO_ERROR) Handler::error("can't make the default shader", 
    "billboard renderer");

    defaultSprite = new Sprite("\\resources\\sprites\\default_sprite.png");

    root = new QuadTree(AABB(0, 0, 100));
}

// draw billboards
void Engine::Billboard::draw()
{
    shader->use();
    vao->bind();

    glm::mat4 ortho = UI::getOrtho();
    glm::mat4 screen_transform = getActor()->getComponent<RectTransform>()->getScreenMatrix();

    glUniform4fv(shader->getLocation("color"), 1, &color[0]);
    glUniformMatrix4fv(shader->getLocation("screen_ortho"), 1, GL_FALSE, &ortho[0][0]);
    glUniformMatrix4fv(shader->getLocation("screen_transform"), 1, GL_FALSE, &screen_transform[0][0]);
    glUniform1i(shader->getLocation("sprite"), 0);
    
    sprite->bind();
    
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    
    sprite->unbind();
    vao->unbind();
}