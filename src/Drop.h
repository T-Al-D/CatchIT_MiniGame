#pragma once

#include <string>

#include "GameEntity.h"
#include "Player.h"
#include "Sound.h"

class Drop : public GameEntity
{
public:
	Drop(string texture_sheet, unsigned short x, unsigned short y, unsigned short h, unsigned short w);
	~Drop();

	void update_drop();
	void set_sound(Sound* new_sound) { this->catched_sound = new_sound; }
	bool check_collision(Drop* drop, Player* player);

private:
	/* to play out the catching sound I had tu assin it to the Drop-Object*/
	Sound* catched_sound;
};