#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GameLayer.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();  
	void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(HelloWorld);

	//开始按键的回调函数
	void startGame(cocos2d::Ref* pSender);
	//声音按键的回调函数
	void setOptions(cocos2d::Ref* pSender);
	//响应安卓返回键
	virtual void onKeyReleased(EventKeyboard::KeyCode keycode,Event* event)override;
	virtual bool onTouchBegan(Touch *touch, Event *unused) override;
private:
	CCMenuItemImage *item_Voice;
	bool AudioState;
	LabelTTF * exit;
	//记录是否按了别的地方
	bool touchedBack;
};

#endif // __HELLOWORLD_SCENE_H__
