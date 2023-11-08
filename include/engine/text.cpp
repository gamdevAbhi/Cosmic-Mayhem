#include <engine/text.hpp>

// get font
Engine::Font* Engine::Text::getFont()
{
    return font;
}

// get text
std::string Engine::Text::getText()
{
    return text;
}

// get text color
glm::vec4 Engine::Text::getTextColor()
{
    return textColor;
}

// get font size
int Engine::Text::getFontSize()
{
    return fontSize;
}

// set font
void Engine::Text::setFont(Font* font)
{
    this->font = font;
    updateProperties();
    nodeUpdate();
}

// set text
void Engine::Text::setText(std::string text)
{
    this->text = text;
    updateProperties();
    nodeUpdate();
}

// set text color
void Engine::Text::setTextColor(glm::vec4 color)
{
    textColor = color;
}

// set font size
void Engine::Text::setFontSize(int fontSize)
{
    this->fontSize = fontSize;
    updateProperties();
    nodeUpdate();
}

// start function
void Engine::Text::start()
{
    font = defaultFont;
    text = "text";
    fontSize = 20;
    textColor = glm::vec4(1.f, 1.f, 1.f, 1.f);
    order = 0;

    updateProperties();

    glm::vec3 position = (getActor()->getComponent<Transform>() != nullptr)?
    getActor()->getComponent<Transform>()->getWorldPosition() : 
    getActor()->getComponent<RectTransform>()->getRectPosition();
    glm::vec3 scale = (getActor()->getComponent<Transform>() != nullptr)?
    getActor()->getComponent<Transform>()->getWorldScale() : 
    getActor()->getComponent<RectTransform>()->getRectScale();

    float x = vertices[vertices.size() - 1].position.x * std::abs(scale.x);
    float y = fontSize * std::abs(scale.y);
    float diagonal = std::sqrt(std::pow(x, 2) + std::pow(y, 2));

    node = new Node(this, AABB(position.x, position.y, diagonal / 2.0f));

    while(true)
    {
        if(!root->getBoundary().contains(node->getBoundary())) root = root->expand(node->getBoundary());
        else break;
    }

    root->insert(node);
}

// on transform changed
void Engine::Text::onTransformChanged()
{
    nodeUpdate();
}

// update properties
void Engine::Text::updateProperties()
{
    vertices.clear();
    indices.clear();
    sprites.clear();

    if(text == "") text = " ";

    std::map<char, Character> characters = font->getCharacter(fontSize);
    
    float x = 25.f;
    float y = 25.f;
    float scale = 12.f;

    for(int i = 0; i < text.size(); i++)
    {
        Character c = characters[text[i]];

        float xPos = x + c.bearing.x * scale;
        float yPos = y - (c.size.y - c.bearing.y) * scale;
        float w = c.size.x * scale;
        float h = c.size.y * scale;
        int vertIndex = vertices.size();

        vertices.push_back(vertex{glm::vec3(xPos, yPos + h, 0.f), glm::vec2(0.f, 0.f)});
        vertices.push_back(vertex{glm::vec3(xPos, yPos, 0.f), glm::vec2(0.f, 1.f)});
        vertices.push_back(vertex{glm::vec3(xPos + w, yPos + h, 0.f), glm::vec2(1.f, 1.f)});
        vertices.push_back(vertex{glm::vec3(xPos + w, yPos + h, 0.f), glm::vec2(1.f, 0.f)});

        indices.push_back(vertIndex);
        indices.push_back(vertIndex + 1);
        indices.push_back(vertIndex + 2);
        indices.push_back(vertIndex);
        indices.push_back(vertIndex + 3);
        indices.push_back(vertIndex + 2);

        sprites.push_back(c.sprite);

        x += (c.advance >> 6) * scale;
    }
}

// update the node
void Engine::Text::nodeUpdate()
{
    glm::vec3 position = (getActor()->getComponent<Transform>() != nullptr)?
    getActor()->getComponent<Transform>()->getWorldPosition() : 
    getActor()->getComponent<RectTransform>()->getRectPosition();
    glm::vec3 scale = (getActor()->getComponent<Transform>() != nullptr)?
    getActor()->getComponent<Transform>()->getWorldScale() : 
    getActor()->getComponent<RectTransform>()->getRectScale();

    float x = vertices[vertices.size() - 1].position.x * std::abs(scale.x);
    float y = fontSize * std::abs(scale.y);
    float diagonal = std::sqrt(std::pow(x, 2) + std::pow(y, 2));

    AABB boundary = AABB(position.x, position.y, diagonal / 2.0f);
    
    while(true)
    {
        if(!root->getBoundary().contains(boundary)) root = root->expand(boundary);
        else break;
    }

    node->update(boundary, root);
}

// on destroy
void Engine::Text::onDestroy()
{
    node->destroy();
}

// intialize the member of the text renderer
void Engine::Text::initialize()
{
    vao = new VAO();
    vao->bind();
    vbo = new VBO(0, NULL, GL_DYNAMIC_DRAW);
    vbo->bind();
    ebo = new EBO(0, NULL, GL_DYNAMIC_DRAW);
    ebo->bind();

    vao->link(*vbo, 0, 3, sizeof(vertex), 0);
    vao->link(*vbo, 1, 2, sizeof(vertex), (void*)(3 * sizeof(float)));

    vbo->unbind();
    vao->unbind();
    ebo->unbind();
    
    defaultFont = new Font("\\resources\\fonts\\EvilEmpire.ttf");
    root = new QuadTree(AABB(0, 0, 100));
}

// draw text
void Engine::Text::draw()
{
    renderShader->use();
    vao->bind();

    glm::mat4 view_projection_matrix;
    glm::mat4 transform_matrix;

    if(getActor()->getComponent<Transform>() != nullptr)
    {
        Engine::Camera* camera = Engine::Camera::getRenderCamera();
        view_projection_matrix = camera->getOrtho();

        Transform* transform = getActor()->getComponent<Transform>();
        transform_matrix = transform->getMatrix();
    }
    else
    {
        view_projection_matrix = glm::ortho(0.0f, 800.f, 0.0f, 600.f);
        transform_matrix = getActor()->getComponent<RectTransform>()->getRectMatrix();
    }

    glUniform4fv(renderShader->getLocation("color"), 1, &textColor[0]);
    glUniformMatrix4fv(renderShader->getLocation("viewProjMat"), 1, GL_FALSE, &view_projection_matrix[0][0]);
    glUniformMatrix4fv(renderShader->getLocation("transformMat"), 1, GL_FALSE, &transform_matrix[0][0]);
    glUniform1i(renderShader->getLocation("tex"), 0);

    int spriteIndex = 0;

    for(int i = 0; i < vertices.size(); i += 4)
    {
        sprites[spriteIndex]->bind();

        vbo->subData(4 * sizeof(vertex), vertices.data() + i);
        ebo->subData(6 * sizeof(GLuint), indices.data() + i + (spriteIndex * 2));

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        sprites[spriteIndex++]->unbind();
    }

    vao->unbind();
}