#include "Layer.h"

const sf::Vector2f& Layer::getPos() const
{
    return m_bg.getPosition();
}

const sf::Vector2f& Layer::getRenderingSize() const
{
    return m_bg.getSize();
}

const sf::Color& Layer::getBgColor() const
{
    return m_bg.getFillColor();
}
