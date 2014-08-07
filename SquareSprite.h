#ifndef __SquareSprite_H__
#define __SquareSprite_H__

#include "cocos2d.h"

USING_NS_CC;

typedef enum {
	DISPLAY_MODE_NORMAL = 0,
	DISPLAY_MODE_HORIZONTAL,
	DISPLAY_MODE_VERTICAL,
} DisplayMode;


class SquareSprite :  public Sprite
{
public:
	static SquareSprite *create(int row, int col);
	static float getContentWidth();

	//精灵所在的行列数
	CC_SYNTHESIZE(int, m_row, Row);
	CC_SYNTHESIZE(int, m_col, Col);
	//是否被选中
	CC_SYNTHESIZE(bool,m_selected,Selected);
	//选路时前面的方块
	CC_SYNTHESIZE(SquareSprite*,m_prev,Prev);
	//选路时是否在队列里面
	//CC_SYNTHESIZE(bool,m_inQueue,Que);
	//CC_SYNTHESIZE_READONLY(DisplayMode, m_displayMode, DisplayMode);
	//void setDisplayMode(DisplayMode mode);
};

#endif /* defined(__SquareSprite_H__) */
