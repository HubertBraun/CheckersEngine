#include"Piece.h"

void Piece::changeDirection(short& direction, short& ratiox, short& ratioy)	//allows capture in all directions
{
	switch (direction)	
	{
	case 0:
		ratiox = -1;
		ratioy = -1;
		break;
	case 1:
		ratiox = 1;
		ratioy = -1;
		break;
	case 2:
		ratiox = -1;
		ratioy = 1;
		break;
	case 3:
		ratiox = 1;
		ratioy = 1;
		break;

	default:
		break;
	}
	direction++;
}

