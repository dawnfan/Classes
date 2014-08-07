#include "SquareSprite.h"
#include <stdlib.h>

USING_NS_CC;


float SquareSprite::getContentWidth()
{
	static float itemWidth = 0;
	if (0 == itemWidth) {
		CCTexture2D * texture = CCTextureCache::sharedTextureCache()->addImage("block1.png");
		Sprite *sprite = CCSprite::createWithTexture(texture);
		itemWidth = sprite->getContentSize().width;
	}
	return itemWidth;
}

SquareSprite *SquareSprite::create(int row, int col)
{
	SquareSprite *square = new SquareSprite();
	square->m_row = row;
	square->m_col = col;
	square->m_selected = false;
	square->m_prev = NULL;
	//square->m_inQueue = false;
	//sushi->m_imgIndex = rand() % TOTAL_SUSHI;
	//square->initWithSpriteFrameName("block1.png");
	square->initWithFile("block1.png");
	square->autorelease();
	return square;
}