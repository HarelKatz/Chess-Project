/*
Authors:    Harel Katz,			Yuval Dahan
Emails:		harelka2@gmail.com,	yuvaldahn@gmail.com
*/
#pragma once
#include "Piece.h"
class Knight :	public Piece
{
public:
	Knight(Side color);
	~Knight();
	virtual bool is_valid_move(Location src, Location dst, Piece* board_arr[][8]);
	virtual char get_type();
};

