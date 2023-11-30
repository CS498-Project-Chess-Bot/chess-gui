#include "move.hpp"


Move::Move(int startPosX, int startPosY, int endPosX, int endPosY, ChessPieceType piece)
{
	m_startPosX = startPosX;
	m_startPosY = startPosY;
	m_endPosX = endPosX;
	m_endPosY = endPosY;
	m_piece = piece;
}

Move::Move(std::string& text, ChessPieceType piece) {
	m_piece = piece;

	CORE_ASSERT(text.size() == 4, "Invalid string input to Move constructor!");

	m_startPosX = (int)(text[0] - 'a');
	m_startPosY = (int)(text[1] - '0') - 1;
	m_endPosX = (int)(text[2] - 'a');
	m_endPosY = (int)(text[3] - '0') - 1;
}

std::tuple<int, int> Move::getStartTile()
{
	return std::make_tuple(m_startPosX, m_startPosY);
}

std::tuple<int, int> Move::getEndTile()
{
	return std::make_tuple(m_endPosX, m_endPosY);
}

ChessPieceType Move::getPieceType()
{
	return m_piece;
}
