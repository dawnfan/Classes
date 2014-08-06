#include "Raindrop.h"

USING_NS_CC;

Raindrop *Raindrop::create(int row, int col)
{
	Raindrop *square = new Raindrop();
	square->m_row = row;
	square->m_col = col;
	square->initWithFile("block3.png");
	square->autorelease();
	return square;
}