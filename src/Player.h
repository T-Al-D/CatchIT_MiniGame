#pragma once

#include <string>
#include "GameEntity.h"

using std::string;

class Player : public GameEntity
{
public:
	Player(string texture_sheet, unsigned short x, unsigned short y, unsigned short h, unsigned short w);
	~Player();

	void set_hits(unsigned short new_hits) { this->hits = new_hits; }
	void set_lost(bool new_value) { this->lost = new_value; }
	unsigned short get_hits() const { return this->hits; }
	unsigned short get_lost() const { return this->lost; }

private:
	unsigned short hits = 0;
	/* if player has lost, no level progression */
	bool lost = false;
};
