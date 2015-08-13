#include "Aircraft.hpp"

#include "Category.hpp"
#include "ResourceHolder.hpp"
#include "TextNode.hpp"


namespace
{
    std::vector<Aircraft::Data> initAircraftData()
    {
        std::vector<Aircraft::Data> data(Aircraft::TypeCount);

        data[Aircraft::Eagle].hp = 100;
        data[Aircraft::Eagle].speed = 200.f;
        data[Aircraft::Eagle].textureID = TextureID::Eagle;

        data[Aircraft::Raptor].hp = 20;
        data[Aircraft::Raptor].speed = 80.f;
        data[Aircraft::Raptor].textureID = TextureID::Raptor;

        return data;
    }

    std::vector<Aircraft::Data> data = initAircraftData();
}

Aircraft::Aircraft(Type type, const TextureHolder& textureHolder, const FontHolder& fontHolder)
    : Entity()
    , type_(type)
    , data_(data[type_])
    , sprite_(textureHolder.get(data_.textureID))
{
    sf::FloatRect bounds = sprite_.getLocalBounds();
    sprite_.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

    auto textNode = std::make_unique<TextNode>("", fontHolder);
    healthText_ = textNode.get();
    healthText_->setPosition(0, -50.f);

    addChild(std::move(textNode));
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(sprite_, states);
}

unsigned Aircraft::getCategory() const
{
    return (type_ == Type::Eagle) ? Category::PlayerEntity : Category::EnemyEntity;
}

void Aircraft::updateCurrent(const sf::Time& dt)
{
    Entity::updateCurrent(dt);
    healthText_->setText(std::to_string(data_.hp) + " HP");
    healthText_->setRotation(-getRotation());
}
