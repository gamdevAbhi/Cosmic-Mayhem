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

// get text scale
glm::vec2 Engine::Text::getScale()
{
    return scale;
}

// get character per line limit
unsigned int Engine::Text::getCharPerLine()
{
    return charPerLine;
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

// set text scale
void Engine::Text::setScale(glm::vec2 scale)
{
    this->scale = scale;
}

// characters per line limit
void Engine::Text::setCharPerLine(unsigned int chars)
{
    charPerLine = chars;
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
    text = "Sample Text";
    fontSize = 48;
    textColor = glm::vec4(1.f, 1.f, 1.f, 1.f);
    scale = glm::vec2(0.5f);
    charPerLine = 0;
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
    updateProperties();
    nodeUpdate();
}

// update properties
void Engine::Text::updateProperties()
{
    vertices.clear();
    sprites.clear();

    if(text == "") text = " ";

    std::map<char, Character> characters = font->getCharacter(fontSize);
    glm::vec2 scale;

    if(getActor()->getComponent<Transform>() != nullptr)
    {
        glm::vec2 worldPerScreen = Camera::getRenderCamera()->getPerWorldToScreen();
        scale.x = worldPerScreen.x * getActor()->getComponent<Transform>()->getWorldScale().x;
        scale.y = worldPerScreen.y * getActor()->getComponent<Transform>()->getWorldScale().y;
    }
    else
    {
        scale.x = getActor()->getComponent<RectTransform>()->getRectScale().x;
        scale.y = getActor()->getComponent<RectTransform>()->getRectScale().y;
    }

    for(int i = 0; i < text.size(); i++)
    {
        Character c = characters[text[i]];

        float xPos = c.bearing.x / scale.x;
        float yPos = (c.size.y - c.bearing.y) / scale.y;
        float w = c.size.x / scale.x;
        float h = c.size.y / scale.y;

        vertices.push_back(vertex{glm::vec3(xPos, yPos, 0.f), glm::vec2(0.f, 1.f)});
        vertices.push_back(vertex{glm::vec3(xPos, yPos + h, 0.f), glm::vec2(0.f, 0.f)});
        vertices.push_back(vertex{glm::vec3(xPos + w, yPos, 0.f), glm::vec2(1.f, 1.f)});
        vertices.push_back(vertex{glm::vec3(xPos + w, yPos + h, 0.f), glm::vec2(1.f, 0.f)});

        sprites.push_back(c.sprite);

        if(offsets.size() == 0) offsets.push_back(glm::vec2(0.f, 0.f));
        else if(charPerLine > 0 && offsets.size() % charPerLine == 0)
        {
            float x = offsets[offsets.size() - 1].x;
            float y = offsets[offsets.size() - 1].y;
            x = 0.f;
            y -= c.size.y / scale.y;
            offsets.push_back(glm::vec2(x, y));
            lengthX = x;
            lengthY = y;
        }
        else 
        {
            float x = offsets[offsets.size() - 1].x;
            float y = offsets[offsets.size() - 1].y;
            x += (c.advance >> 6) / scale.x;
            offsets.push_back(glm::vec2(x, y));

            if(charPerLine > text.size()) 
            {
                lengthX = x;
                lengthY = c.size.y / scale.y;
            }  
        }
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

    float x = std::abs(lengthX * scale.x);
    float y = std::abs(lengthY * scale.y);
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
    vbo = new VBO(4 * sizeof(vertex), quadVertices.data(), GL_DYNAMIC_DRAW);
    vbo->bind();
    ebo = new EBO(6 * sizeof(GLuint), quadIndices.data(), GL_DYNAMIC_DRAW);
    ebo->bind();

    vao->link(*vbo, 0, 3, sizeof(vertex), (void*)0);
    vao->link(*vbo, 1, 2, sizeof(vertex), (void*)(3 * sizeof(float)));

    vbo->unbind();
    vao->unbind();
    ebo->unbind();
    
    shader = new Shader("\\resources\\shaders\\text_shader.vert", "\\resources\\shaders\\text_shader.frag");

    if(shader->getStatus() != SHADER_NO_ERROR)
    {
        Handler::debug("text shader not created", "text renderer");
    }

    defaultFont = new Font("\\resources\\fonts\\EvilEmpire.ttf");
    root = new QuadTree(AABB(0, 0, 100));
}

// draw text
void Engine::Text::draw()
{
    shader->use();
    vao->bind();
    vbo->bind();
    ebo->bind();

    glm::mat4 view_projection_matrix;
    glm::mat4 parent_matrix;
    glm::mat4 transform_matrix;

    if(getActor()->getComponent<Transform>() != nullptr)
    {
        Engine::Camera* camera = Engine::Camera::getRenderCamera();
        view_projection_matrix = camera->getOrtho();

        Transform* transform = getActor()->getComponent<Transform>();
        parent_matrix = transform->getMatrix();
    }
    else
    {
        view_projection_matrix = UI::getOrtho();

        RectTransform* transform = getActor()->getComponent<RectTransform>();
        parent_matrix = transform->getRectMatrix();
    }

    glm::mat4 translate = glm::translate(glm::mat4(1.f), glm::vec3(0.f));
    glm::mat4 rotation = glm::mat4_cast(glm::quat(glm::vec3(0.f)));
    glm::mat4 scale = glm::scale(glm::mat4(1.f), glm::vec3(this->scale, 1.f));

    glUniform4fv(renderShader->getLocation("color"), 1, &textColor[0]);
    glUniformMatrix4fv(renderShader->getLocation("viewProjMat"), 1, GL_FALSE, &view_projection_matrix[0][0]);
    glUniform1i(renderShader->getLocation("tex"), 0);


    for(int i = 0; i < sprites.size(); i ++)
    {
        sprites[i]->bind();

        translate = glm::translate(glm::mat4(1.f), glm::vec3(offsets[i], 0.f));
        transform_matrix = parent_matrix * (translate * rotation * scale);

        glUniformMatrix4fv(renderShader->getLocation("transformMat"), 1, GL_FALSE, &transform_matrix[0][0]);

        vbo->subData(4 * sizeof(vertex), &vertices[i * 4]);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        sprites[i]->unbind();
    }

    vbo->unbind();
    vao->unbind();
    ebo->unbind();
}