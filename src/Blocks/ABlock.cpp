//
// Created by njoachim on 05/06/19.
//

#include "ABlock.hpp"
#include "../PowerUp/Stock.hpp"
#include "../PowerUp/Power.hpp"
#include "../PowerUp/Speed.hpp"

ABlock::ABlock(irr::scene::ISceneManager *smgr, irr::scene::IMeshSceneNode *cube, irr::video::IVideoDriver* driver, irr::video::ITexture *texture, irr::IrrlichtDevice *device, const bool &destructible, int boost)
: _smgr(smgr), _block(cube), _driver(driver), _texture(texture), _destructible(destructible), _powerUp(nullptr)
{
    if (texture) {
        cube->setMaterialTexture(0, texture);
        cube->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    }
    irr::core::vector3df extent = cube->getTransformedBoundingBox().getExtent();
    irr::f32 factor = 10 / extent.X;
    irr::core::vector3d<irr::f32> factorEscalate(factor, factor, factor);
    cube->setScale(factorEscalate);
    vector3df pos = cube->getPosition();
    if (_destructible && rand() % 100 < boost) {
        int power = rand() % 3;
        if (power == 0) {
            _powerUp = new Speed(smgr, driver, device, pos);
        } else if (power == 1) {
            _powerUp = new Power(smgr, driver, device, pos);
        } else
            _powerUp = new Stock(smgr, driver, device, pos);
    }
}

ABlock::ABlock(ABlock &&block) noexcept
{
    (void)block;
}

ABlock::ABlock(ABlock const &block) noexcept
{
    (void)block;
}

ABlock& ABlock::operator=(ABlock &&block) noexcept
{
    (void)block;
    return *this;
}

ABlock& ABlock::operator=(ABlock const &block) noexcept
{
    (void)block;
    return *this;
}

ABlock::~ABlock()
{
    _block->remove();
}

irr::scene::IMeshSceneNode* ABlock::getCube()
{
    return _block;
}

bool ABlock::isDestructible()
{
    return _destructible;
}

irr::core::vector3df ABlock::getPos() const
{
    return _block->getPosition();
}

void ABlock::changeMesh(const std::string &path)
{
    _block->setMesh(_smgr->getMesh(path.c_str())->getMesh(0));
}

void ABlock::changeTexture(const std::string &path)
{
    _texture = _driver->getTexture(path.c_str());
    _block->setMaterialTexture(0, _texture);
}

void ABlock::setPos(const irr::core::vector3df &pos)
{
    _block->setPosition(pos);
}

void ABlock::setScale(const irr::core::vector3df &scale)
{
    _block->setScale(scale);
}

APowerUp *ABlock::getPowerUp()
{
    return _powerUp;
}