#include "move.hpp"

Move::bool legalMove(){
//if pawn
//	if newRow < oldRow {return false}
//	if firstMove and move > 2 return false
//	if !firstMove and move > 1 {return false}
//	if oldColumn != newColumn
//		if piece_moving_diagonal
//			if opposingPieceAtDestination {return true} captureCount++
//			else return false
//
//else if rook
//	if (oldRow != newRow) or (oldColumn != newColumn)
//		if oldRow != newRow and oldColumn != newColumn return false (moved diagonal)
//		if pathBlocked return False
//		if noPieceAtDestination return True
//		if ownPieceAtDestination return False
//		if opposingPieceAtDestination return True, captureCount++
//	else return False
//
//else if knight
//	if ((oldRow == newRow + 1 or oldRow == newRow - 1) and (oldColumn == newColumn - 2 or oldColumn == newColumn +2		)) or ((oldRow == newRow - 2 or oldRow == newRow + 2) and (oldColumn == newCOlumn - 1 or oldColumn == newColumn 		+1))
//			if ownPieceAtDestination return False
//			else return True
//	else return false
//
//else if queen
//else if bishop
//	if newRow == oldRow or newColumn == oldColumn {return false}
//	if pathBlocked return false
//	if opposingPieceAtDestination return true
//else (king case)
//	if (oldRow == newRow +- 1) or (oldColumn == newColumn +-1)
//		if ownPieceAtDestination return False
//		else true
//	else true
}

Move::Move(startPos, endPos, PieceType)
{
}

Tuple<int, int> Move::getStartTile()
{
	return Tuple<int, int>();
}

Tuple<int, int> Move::getEndTile()
{
	return Tuple<int, int>();
}
