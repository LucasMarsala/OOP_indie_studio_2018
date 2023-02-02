//
// Created by njoachim on 18/06/19.
//

#ifndef OOP_INDIE_STUDIO_2018_STOCK_HPP
#define OOP_INDIE_STUDIO_2018_STOCK_HPP

#include "APowerUp.hpp"

class Stock  : public APowerUp{
    public:

        Stock(ISceneManager *smgr, irr::video::IVideoDriver* driver, IrrlichtDevice *device, vector3df &pos);
        ~Stock() override ;
        void activatePower(APlayers &player) override;
};

#endif //OOP_INDIE_STUDIO_2018_STOCK_HPP
