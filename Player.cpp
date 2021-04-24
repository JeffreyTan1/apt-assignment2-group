#include "Player.h"

Player::Player(std::string name, int points, LinkedList *hand)
{
    this->name = name;
    this->points = points;
    this->hand = hand;
}

Player::~Player()
{
    delete hand;
}

std::string Player::getName()
{
    return name;
}

int Player::getPoints()
{
    return points;
}

LinkedList *Player::getHand()
{
    return hand;
}