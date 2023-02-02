/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Properties
*/

#ifndef PROPERTIES_HPP_
#define PROPERTIES_HPP_

#include <cstddef>
#include <type_traits>
#include "../Integration/Integration.hpp"
#include "../GUI/EventReceiver.hpp"
#include <iostream>
#include <vector>

enum Prop {
    MOVE =      0x10000000,
    COLLIDE =   0x01000000,
};

enum State {
    P1,
    P2,
    AI
};

///////////////////////////////////////////////////////////////////////////////////////////////////

template<std::size_t BITFIELD> class Properties {
    public:

        /*_______________________________MOVE_PROPERTY_______________________________*/
        template<class C = std::enable_if<BITFIELD | MOVE>, class T> bool MoveLeft(T &object, irr::f32 deltaFrame,
        std::vector<bool> direction)
        {
            irr::core::vector3df nextPos = object.getPosition();
            bool val = false;

            if (object.getState() == State::AI && object.getIdleState() == true) {
                object.setWalkAnimation();
                object.setIdleState(false);
            }
            object.setRotation(irr::core::vector3df{0, 90, 0});
                object._oldpos = object.getPosition();
            if (direction[2] == true) {
                nextPos.X -= object.getSpeed() * deltaFrame;
                object.setPosition(nextPos);
                val = true;
            }
            return (val);
        }

        template<class C = std::enable_if<BITFIELD | MOVE>, class T> bool MoveRight(T &object, irr::f32 deltaFrame,
        std::vector<bool> direction)
        {
            irr::core::vector3df nextPos = object.getPosition();
            bool val = false;

            if (object.getState() == State::AI && object.getIdleState() == true) {
                object.setWalkAnimation();
                object.setIdleState(false);
            }
            object.setRotation(irr::core::vector3df{0, -90, 0});
                object._oldpos = object.getPosition();
            if (direction[3] == true) {
                nextPos.X += object.getSpeed() * deltaFrame;
                object.setPosition(nextPos);
                val = true;
            }
            return (val);
        }

        template<class C = std::enable_if<BITFIELD | MOVE>, class T> bool MoveUp(T &object, irr::f32 deltaFrame,
        std::vector<bool> direction)
        {
            irr::core::vector3df nextPos = object.getPosition();
            bool val = false;

            if (object.getState() == State::AI && object.getIdleState() == true) {
                object.setWalkAnimation();
                object.setIdleState(false);
            }
            object.setRotation(irr::core::vector3df{0, 180, 0});
                object._oldpos = object.getPosition();
            if (direction[0]) {
                nextPos.Z += object.getSpeed() * deltaFrame;
                object.setPosition(nextPos);
                val = true;
            }
            return (val);
        }

        template<class C = std::enable_if<BITFIELD | MOVE>, class T> bool MoveDown(T &object, irr::f32 deltaFrame,
        std::vector<bool> direction)
        {
            irr::core::vector3df nextPos = object.getPosition();
            bool val = false;

            if (object.getState() == State::AI && object.getIdleState() == true) {
                object.setWalkAnimation();
                object.setIdleState(false);
            }
            object.setRotation(irr::core::vector3df{0, 0, 0});
                object._oldpos = object.getPosition();
            if (direction[1] == true) {
                nextPos.Z -= object.getSpeed() * deltaFrame;
                object.setPosition(nextPos);
                val = true;
            }
            return (val);
        }

        template<class C = std::enable_if<BITFIELD | MOVE>, class T> void MoveDownRight(T &object, irr::f32 deltaFrame)
        {
            irr::core::vector3df nextPos = object.getPosition();

                nextPos.X += object.getSpeed() * deltaFrame;
                nextPos.Z -= object.getSpeed() * deltaFrame;
                object.setPosition(nextPos);
                object.setRotation(irr::core::vector3df{0, -45, 0});
        }

        template<class C = std::enable_if<BITFIELD | MOVE>, class T> void MoveDownLeft(T &object, irr::f32 deltaFrame)
        {
            irr::core::vector3df nextPos = object.getPos();

                nextPos.X -= object.getSpeed() * deltaFrame;
                nextPos.Z -= object.getSpeed() * deltaFrame;
                object.setPosition(nextPos);
                object.setRotation(irr::core::vector3df{0, 45, 0});
        }

        template<class C = std::enable_if<BITFIELD | MOVE>, class T> void MoveUpRight(T &object, irr::f32 deltaFrame)
        {
            irr::core::vector3df nextPos = object.getPosition();

                nextPos.X += object.getSpeed() * deltaFrame;
                nextPos.Z += object.getSpeed() * deltaFrame;
                object.setPosition(nextPos);
                object.setRotation(irr::core::vector3df{0, -135, 0});
        }

        template<class C = std::enable_if<BITFIELD | MOVE>, class T> void MoveUpLeft(T &object, irr::f32 deltaFrame)
        {
            irr::core::vector3df nextPos = object.getPosition();

                nextPos.X -= object.getSpeed() * deltaFrame;
                nextPos.Z += object.getSpeed() * deltaFrame;
                object.setPosition(nextPos);
                object.setRotation(irr::core::vector3df{0, 135, 0});
        }

        template<class C = std::enable_if<BITFIELD | MOVE>, class T> bool Move(T &object,
        EventReceiver &receiver, irr::f32 deltaFrame, std::vector<bool> direction, std::vector<irr::EKEY_CODE> keys)
        {
            if (object.getIdleState() && (receiver.isKeyDown(keys[0]) ||
            receiver.isKeyDown(keys[1]) ||
            receiver.isKeyDown(keys[2]) ||
            receiver.isKeyDown(keys[3]))) {
                object.setWalkAnimation();
                object.setIdleState(false);
            } else if (!object.getIdleState() && (!receiver.isKeyDown(keys[0]) &&
            !receiver.isKeyDown(keys[1]) &&
            !receiver.isKeyDown(keys[2]) &&
            !receiver.isKeyDown(keys[3]))) {
                object.setIdleAnimation();
                object.setIdleState(true);
            }
            else if (receiver.isKeyDown(keys[0])) {
                return MoveUp(object, deltaFrame, direction);
            } else if (receiver.isKeyDown(keys[1]))
                return MoveDown(object, deltaFrame, direction);
            else if (receiver.isKeyDown(keys[2]))
                return MoveLeft(object, deltaFrame, direction);
            else if (receiver.isKeyDown(keys[3]))
                return MoveRight(object, deltaFrame, direction);
            return (false);
        }
        /*___________________________END_MOVE_PROPERTY_______________________________*/

        template<class C = std::enable_if<BITFIELD | COLLIDE>, class T, class U> bool CollideWith(T &source, U &dest, std::vector<bool> *direction,
        std::vector<irr::f32>hitboxSource)
        {
            irr::f32 maxEdgeX = source.getTransformedBoundingBox().getCenter().X + hitboxSource[0];
            irr::f32 minEdgeX = source.getTransformedBoundingBox().getCenter().X - hitboxSource[0];
            irr::f32 maxEdgeY = source.getTransformedBoundingBox().getCenter().Y + hitboxSource[1];
            irr::f32 minEdgeY = source.getTransformedBoundingBox().getCenter().Y - hitboxSource[1];
            irr::f32 maxEdgeZ = source.getTransformedBoundingBox().getCenter().Z + hitboxSource[2];
            irr::f32 minEdgeZ = source.getTransformedBoundingBox().getCenter().Z - hitboxSource[2];

            if (source.getRotation().Y == -90 &&
            maxEdgeX > dest.getTransformedBoundingBox().MinEdge.X &&
            minEdgeX < dest.getTransformedBoundingBox().MaxEdge.X &&
            ((minEdgeZ > dest.getTransformedBoundingBox().MinEdge.Z &&
            minEdgeZ < dest.getTransformedBoundingBox().MaxEdge.Z) ||
            (maxEdgeZ < dest.getTransformedBoundingBox().MaxEdge.Z &&
            maxEdgeZ > dest.getTransformedBoundingBox().MinEdge.Z))) {
                (*direction)[3] = false;
                return (true);
            }
            if (source.getRotation().Y == 180 &&
            maxEdgeZ > dest.getTransformedBoundingBox().MinEdge.Z &&
            minEdgeZ < dest.getTransformedBoundingBox().MaxEdge.Z &&
            ((minEdgeX < dest.getTransformedBoundingBox().MaxEdge.X &&
            minEdgeX > dest.getTransformedBoundingBox().MinEdge.X) ||
            (maxEdgeX < dest.getTransformedBoundingBox().MaxEdge.X &&
            maxEdgeX > dest.getTransformedBoundingBox().MinEdge.X))) {
                (*direction)[0] = false;
                return (true);
            }
            if (source.getRotation().Y == 90 &&
            minEdgeX < dest.getTransformedBoundingBox().MaxEdge.X &&
            maxEdgeX > dest.getTransformedBoundingBox().MinEdge.X &&
            ((minEdgeZ > dest.getTransformedBoundingBox().MinEdge.Z &&
            minEdgeZ < dest.getTransformedBoundingBox().MaxEdge.Z) ||
            (maxEdgeZ < dest.getTransformedBoundingBox().MaxEdge.Z &&
            maxEdgeZ > dest.getTransformedBoundingBox().MinEdge.Z))) {
                (*direction)[2] = false;
                return (true);
            }
            if (source.getRotation().Y == 0 &&
            minEdgeZ < dest.getTransformedBoundingBox().MaxEdge.Z &&
            maxEdgeZ > dest.getTransformedBoundingBox().MinEdge.Z &&
            ((minEdgeX < dest.getTransformedBoundingBox().MaxEdge.X &&
            minEdgeX > dest.getTransformedBoundingBox().MinEdge.X) ||
            (maxEdgeX < dest.getTransformedBoundingBox().MaxEdge.X &&
            maxEdgeX > dest.getTransformedBoundingBox().MinEdge.X))) {
                (*direction)[1] = false;
                return (true);
            }
            return (false);
        }

        template<class C = std::enable_if<BITFIELD | COLLIDE>, class T, class U> bool CollideWith(T &source, U &dest, std::vector<bool> *direction,
        std::vector<irr::f32>hitboxSource, std::vector<irr::f32>hitboxDest)
        {
            irr::f32 maxEdgeX = source.getTransformedBoundingBox().getCenter().X + hitboxSource[0];
            irr::f32 minEdgeX = source.getTransformedBoundingBox().getCenter().X - hitboxSource[0];
            irr::f32 maxEdgeY = source.getTransformedBoundingBox().getCenter().Y + hitboxSource[1];
            irr::f32 minEdgeY = source.getTransformedBoundingBox().getCenter().Y - hitboxSource[1];
            irr::f32 maxEdgeZ = source.getTransformedBoundingBox().getCenter().Z + hitboxSource[2];
            irr::f32 minEdgeZ = source.getTransformedBoundingBox().getCenter().Z - hitboxSource[2];
            irr::f32 destmaxEdgeX = dest.getTransformedBoundingBox().getCenter().X + hitboxDest[0];
            irr::f32 destminEdgeX = dest.getTransformedBoundingBox().getCenter().X - hitboxDest[0];
            irr::f32 destmaxEdgeY = dest.getTransformedBoundingBox().getCenter().Y + hitboxDest[1];
            irr::f32 destminEdgeY = dest.getTransformedBoundingBox().getCenter().Y - hitboxDest[1];
            irr::f32 destmaxEdgeZ = dest.getTransformedBoundingBox().getCenter().Z + hitboxDest[2];
            irr::f32 destminEdgeZ = dest.getTransformedBoundingBox().getCenter().Z - hitboxDest[2];

            if (source.getRotation().Y == -90 &&
            maxEdgeX > destminEdgeX &&
            minEdgeX < destmaxEdgeX &&
            ((minEdgeZ > destminEdgeZ &&
            minEdgeZ < destmaxEdgeZ) ||
            (maxEdgeZ < destmaxEdgeZ &&
            maxEdgeZ > destminEdgeZ))) {
                (*direction)[3] = false;
                return (true);
            }
            if (source.getRotation().Y == 180 &&
            maxEdgeZ > destminEdgeZ &&
            minEdgeZ < destmaxEdgeZ &&
            ((minEdgeX < destmaxEdgeX &&
            minEdgeX > destminEdgeX) ||
            (maxEdgeX < destmaxEdgeX &&
            maxEdgeX > destminEdgeX))) {
                (*direction)[0] = false;
                return (true);
            }
            if (source.getRotation().Y == 90 &&
            minEdgeX < destmaxEdgeX &&
            maxEdgeX > destminEdgeX &&
            ((minEdgeZ > destminEdgeZ &&
            minEdgeZ < destmaxEdgeZ) ||
            (maxEdgeZ < destmaxEdgeZ &&
            maxEdgeZ > destminEdgeZ))) {
                (*direction)[2] = false;
                return (true);
            }
            if (source.getRotation().Y == 0 &&
            minEdgeZ < destmaxEdgeZ &&
            maxEdgeZ > destminEdgeZ &&
            ((minEdgeX < destmaxEdgeX &&
            minEdgeX > destminEdgeX) ||
            (maxEdgeX < destmaxEdgeX &&
            maxEdgeX > destminEdgeX))) {
                (*direction)[1] = false;
                return (true);
            }
            return (false);
        }

        template<class C = std::enable_if<BITFIELD | COLLIDE>, class T, class U> bool CollideWith(T &source, U &dest, std::vector<bool> *direction,
        std::vector<irr::f32> hitboxSource, float boundingSpeed, float deltaFrameTime, bool slideAllow = false)
        {
            irr::f32 maxEdgeX = source.getTransformedBoundingBox().getCenter().X + hitboxSource[0];
            irr::f32 minEdgeX = source.getTransformedBoundingBox().getCenter().X - hitboxSource[0];
            irr::f32 maxEdgeY = source.getTransformedBoundingBox().getCenter().Y + hitboxSource[1];
            irr::f32 minEdgeY = source.getTransformedBoundingBox().getCenter().Y - hitboxSource[1];
            irr::f32 maxEdgeZ = source.getTransformedBoundingBox().getCenter().Z + hitboxSource[2];
            irr::f32 minEdgeZ = source.getTransformedBoundingBox().getCenter().Z - hitboxSource[2];

            if (source.getRotation().Y == -90 &&
            maxEdgeX + 1 > dest.getTransformedBoundingBox().MinEdge.X &&
            minEdgeX  + 1 < dest.getTransformedBoundingBox().MaxEdge.X &&
            ((minEdgeZ > dest.getTransformedBoundingBox().MinEdge.Z &&
            minEdgeZ + 1< dest.getTransformedBoundingBox().MaxEdge.Z) ||
            (maxEdgeZ < dest.getTransformedBoundingBox().MaxEdge.Z &&
            maxEdgeZ - 1 > dest.getTransformedBoundingBox().MinEdge.Z))) {
                irr::core::vector3df nextPos = source.getPosition();
                if (slideAllow) {
                    if (maxEdgeZ - 1 > dest.getTransformedBoundingBox().MinEdge.Z &&
                    maxEdgeZ - 1 - dest.getTransformedBoundingBox().MinEdge.Z < 1)
                        nextPos.Z -= boundingSpeed * deltaFrameTime;
                    if (minEdgeZ + 1< dest.getTransformedBoundingBox().MaxEdge.Z &&
                    minEdgeZ + 1 - dest.getTransformedBoundingBox().MaxEdge.Z > -1)
                        nextPos.Z += boundingSpeed * deltaFrameTime;
                }
                nextPos.X -= boundingSpeed * deltaFrameTime * 2;
                source.setPosition(nextPos);
                (*direction)[3] = false;
                return (true);
            }
            if (source.getRotation().Y == 180 &&
            maxEdgeZ + 1 > dest.getTransformedBoundingBox().MinEdge.Z &&
            minEdgeZ  + 1< dest.getTransformedBoundingBox().MaxEdge.Z &&
            ((minEdgeX + 1 < dest.getTransformedBoundingBox().MaxEdge.X &&
            minEdgeX > dest.getTransformedBoundingBox().MinEdge.X) ||
            (maxEdgeX < dest.getTransformedBoundingBox().MaxEdge.X &&
            maxEdgeX - 1 > dest.getTransformedBoundingBox().MinEdge.X))) {
                irr::core::vector3df nextPos = source.getPosition();
                if (slideAllow) {
                    if (maxEdgeX - 1 > dest.getTransformedBoundingBox().MinEdge.X &&
                    maxEdgeX - 1 - dest.getTransformedBoundingBox().MinEdge.X < 1)
                        nextPos.X -= boundingSpeed * deltaFrameTime;
                    if (minEdgeX + 1 < dest.getTransformedBoundingBox().MaxEdge.X &&
                    minEdgeX + 1 - dest.getTransformedBoundingBox().MaxEdge.X > -1)
                        nextPos.X += boundingSpeed * deltaFrameTime;
                }
                nextPos.Z -= boundingSpeed * deltaFrameTime * 2;
                source.setPosition(nextPos);
                (*direction)[0] = false;
                return (true);
            }
            if (source.getRotation().Y == 90 &&
            minEdgeX - 1 < dest.getTransformedBoundingBox().MaxEdge.X &&
            maxEdgeX  - 1 > dest.getTransformedBoundingBox().MinEdge.X &&
            ((minEdgeZ > dest.getTransformedBoundingBox().MinEdge.Z &&
            minEdgeZ + 1< dest.getTransformedBoundingBox().MaxEdge.Z) ||
            (maxEdgeZ < dest.getTransformedBoundingBox().MaxEdge.Z &&
            maxEdgeZ - 1 > dest.getTransformedBoundingBox().MinEdge.Z))) {
                irr::core::vector3df nextPos = source.getPosition();
                if (slideAllow) {
                    if (maxEdgeZ - 1 > dest.getTransformedBoundingBox().MinEdge.Z &&
                    maxEdgeZ - 1 - dest.getTransformedBoundingBox().MinEdge.Z < 1)
                        nextPos.Z -= boundingSpeed * deltaFrameTime;
                    if (minEdgeZ + 1< dest.getTransformedBoundingBox().MaxEdge.Z &&
                    minEdgeZ + 1 - dest.getTransformedBoundingBox().MaxEdge.Z > -1)
                        nextPos.Z += boundingSpeed * deltaFrameTime;
                }
                nextPos.X += boundingSpeed * deltaFrameTime * 2;
                source.setPosition(nextPos);
                (*direction)[2] = false;
                return (true);
            }
            if (source.getRotation().Y == 0 &&
            minEdgeZ - 1 < dest.getTransformedBoundingBox().MaxEdge.Z &&
            maxEdgeZ  - 1> dest.getTransformedBoundingBox().MinEdge.Z &&
            ((minEdgeX + 1< dest.getTransformedBoundingBox().MaxEdge.X &&
            minEdgeX > dest.getTransformedBoundingBox().MinEdge.X) ||
            (maxEdgeX < dest.getTransformedBoundingBox().MaxEdge.X &&
            maxEdgeX  - 1 > dest.getTransformedBoundingBox().MinEdge.X))) {
                irr::core::vector3df nextPos = source.getPosition();
                if (slideAllow) {
                    if (maxEdgeX - 1 > dest.getTransformedBoundingBox().MinEdge.X &&
                    maxEdgeX - 1 - dest.getTransformedBoundingBox().MinEdge.X < 1)
                        nextPos.X -= boundingSpeed * deltaFrameTime;
                    if (minEdgeX + 1 < dest.getTransformedBoundingBox().MaxEdge.X &&
                    minEdgeX + 1 - dest.getTransformedBoundingBox().MaxEdge.X > -1)
                        nextPos.X += boundingSpeed * deltaFrameTime;
                }
                nextPos.Z += boundingSpeed * deltaFrameTime * 2;
                source.setPosition(nextPos);
                (*direction)[1] = false;
                return (true);
            }
            (*direction)[0] = true;
            (*direction)[1] = true;
            (*direction)[2] = true;
            (*direction)[3] = true;
            return (false);
        }

    protected:
    private:
};

///////////////////////////////////////////////////////////////////////////////////////////////////

#endif /* !PROPERTIES_HPP_ */
