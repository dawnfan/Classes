#include "EndLayer.h"
#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
USING_NS_CC;


Scene *EndLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = EndLayer::create();
	scene->addChild(layer);
	return scene;
}

bool EndLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}   
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	//背景初始化
	end_bg= Sprite::create("main_game/bg_success.png");
	end_bg->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(end_bg,0);
	//步数初始化
	end_step = LabelTTF::create("step", "fonts/fzmwt.ttf", 70);
	end_step->setPosition(ccp(visibleSize.width/2+30,visibleSize.height/2+130));
	end_step->setColor(Color3B::RED);

	//返回主界面按键
	auto closeItem = MenuItemImage::create(
										   "main_game/home1.png",
										   "main_game/home2.png",
										   CC_CALLBACK_1(EndLayer::menuCloseCallback, this));
	
	closeItem->setPosition(ccp(-110,-200));
	
	//重新开始按钮
	auto end_retry = MenuItemImage::create(
											"main_game/retry1.png",
											"main_game/retry2.png",
											CC_CALLBACK_1(EndLayer::Retry, this));
	end_retry->setPosition(ccp(80,-135));

	//分享按钮
	auto end_share = MenuItemImage::create(
											"main_game/share1.png",
											"main_game/share2.png",
											CC_CALLBACK_1(EndLayer::Share,this));
	end_share->setPosition(ccp(-30,-155));
	
	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem,end_retry,end_share,NULL);
	this->addChild(menu,1);

	//响应键盘消息
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyReleased = CC_CALLBACK_2(EndLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

	return true;
}

void EndLayer::Retry(Ref* pSender)
{
	auto newScene = GameLayer::createScene();
	CCDirector::sharedDirector()->replaceScene(newScene);
}

void EndLayer::Share(Ref* pSender)
{
	//待修改——分享
	auto newScene = GameLayer::createScene();
	CCDirector::sharedDirector()->replaceScene(newScene);
}

void EndLayer::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif
	auto newScene = HelloWorld::createScene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.3,newScene));
	//Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

//响应安卓返回键
void EndLayer::onKeyReleased(EventKeyboard::KeyCode keycode,Event* event)
{
	if(keycode == EventKeyboard::KeyCode::KEY_BACKSPACE)
	{
		Director::sharedDirector()->replaceScene(CCTransitionCrossFade::create(0.3,HelloWorld::createScene()));
	}
}