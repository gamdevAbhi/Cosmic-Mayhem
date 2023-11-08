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
    updateVertices();
}

// set text
void Engine::Text::setText(std::string text)
{
    this->text = text;
    updateVertices();
}

// set text color
void Engine::Text::setTextColor(glm::vec4 color)
{
    textColor = color;
    updateVertices();
}

// set font size
void Engine::Text::setFontSize(int fontSize)
{
    this->fontSize = fontSize;
    updateVertices();
}

// update vertices
void Engine::Text::updateVertices()
{
    vertices.clear();
}

// draw text
void Engine::Text::draw()
{

}

// intialize the member of the text renderer
void Engine::Text::initialize()
{

}

