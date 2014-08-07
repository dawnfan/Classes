#ifndef __EndLayer_H__
#define __EndLayer_H__

#include "cocos2d.h"

USING_NS_CC;

class EndLayer : public Layer
{
public:
	static Scene* createScene();
	CREATE_FUNC(EndLayer);
	bool m_isRun;
	int m_step;
	//分享按键回调函数
	void Share(cocos2d::Ref* pSender);
	//重新开始按键回调
	void Retry(cocos2d::Ref* pSender);
	//返回主界面回调
	void menuCloseCallback(cocos2d::Ref* pSender);
	virtual void onKeyReleased(EventKeyboard::KeyCode keycode,Event* event)override;
	virtual bool init();
	LabelTTF* end_step;
	Sprite* end_bg;
};

#endif /* defined(__EndLayer_H__) */