/*
Authors:	Harel Katz,			Yuval Dahan
Emails:		harelka2@gmail.com, yuvaldahn@gmail.com
*/
#include "Board.h"

Board::Board(string init_board)
{
	int pos = 0;
	for (int i = 0; i < 8; ++i, ++pos)
	{
		for (int j = 0; j < 8; ++j, ++pos)
		{
			this->_board_arr[i][j] = get_piece(init_board[pos]);
		}
	}
	this->_turn = (init_board[pos]) ? BLACK : WHITE;
}

MoveResult Board::move(Location src, Location dst)
{
	Piece* p_src = this->_board_arr[src.get_row()][src.get_col()];
	Piece* p_dst = this->_board_arr[dst.get_row()][dst.get_col()];
	Side src_side = p_src->get_color();
	Side dst_side = p_dst->get_color();
	if (p_src == nullptr)
	{
		return NO_PLAYER_TOOL_IN_SRC;
	}
	else if (dst_side == src_side)
	{
		return PLAYER_TOOL_IN_DST;
	}
	else if (p_src == p_dst)
	{
		return SRC_AND_DST_SAME;
	}

	try
	{
		p_src->is_valid_move(src, dst, this->_board_arr);
	}
	catch (MoveResult result)
	{
		return result;
	}

	if (is_check(src, dst, src_side))
	{
		return SELF_CHESS_MOVE;
	}
	else if (is_check(src, dst, dst_side))
	{
		return CHESS_MOVE;
	}

	return GOOD_MOVE;
}

bool Board::is_check(Location src, Location dst, Side _side)
{
	Piece* temp = this->_board_arr[dst.get_row()][dst.get_col()];
	this->_board_arr[dst.get_row()][dst.get_col()] = this->_board_arr[src.get_row()][src.get_col()];
	_board_arr[src.get_row()][src.get_col()] = nullptr;
	Location king = getKing(_side);
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if (_side != this->_board_arr[i][j]->get_color())
			{
				try
				{
					this->_board_arr[i][j]->is_valid_move(Location(i, j), king, this->_board_arr);
					return true;
				}
				catch (...) {}
			}
		}
	}
	return false;
}

Piece * Board::get_piece(char p)
{
	Side side = WHITE;
	if (p > 'Z')
	{
		side = BLACK;
		p = p - 'a' + 'A';
	}
	switch (p)
	{
	case 'K':
		return King(side);
		break;
	case 'Q':
		return Queen(side);
		break;
	case 'R':
		return Rook(side);
		break;
	case 'N':
		return Knight(side);
		break;
	case 'B':
		return Bishop(side);
		break;
	case 'P':
		return Pawn(side);
		break;
	case '#':
		return nullptr;
	}
}
