#include "Player.h"

Player::Player(string texture_sheet, unsigned short x, unsigned short y, unsigned short h, unsigned short w)
	: GameEntity(texture_sheet, x, y, h, w)
{
}

Player::~Player()
{
}