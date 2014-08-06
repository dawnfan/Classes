#ifndef __GameAbout_H__
#define __GameAbout_H__

#include "cocos2d.h"

USING_NS_CC;


class GameAbout : public Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
	//响应安卓返回键
	virtual void onKeyReleased(EventKeyboard::KeyCode keycode,Event* event)override;
	//点击函数
	virtual bool onTouchBegan(Touch *touch, Event *unused) override;
    CREATE_FUNC(GameAbout);
};

#endif // __GameAbout_H__
