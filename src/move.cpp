#include "move.hpp"


Move::Move(int startPosX, int startPosY, int endPosX, int endPosY, ChessPieceType piece)
{
	m_startPosX = startPosX;
	m_startPosY = startPosY;
	m_endPosX = endPosX;
	m_endPosY = endPosY;
	m_piece = piece;
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
