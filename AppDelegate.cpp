#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;

#define userDefault UserDefault::getInstance()

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if(!glview) {
		glview = GLView::create("My Game");
		director->setOpenGLView(glview);
	}

	glview->setFrameSize(360,640);

	//glview->setDesignResolutionSize(720 , 1280 , kResolutionShowAll);

	glview->setDesignResolutionSize(320.0, 480.0, ResolutionPolicy::FIXED_WIDTH);
	std::vector<std::string> searchPath;
	searchPath.push_back("w640");
	CCFileUtils::getInstance()->setSearchPaths(searchPath);
	director->setContentScaleFactor(720.0 / 320.0);

	// turn on display FPS
	director->setDisplayStats(false);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);

	// create a scene. it's an autorelease object
	auto scene = HelloWorld::createScene();

	// run
	director->runWithScene(scene);

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();

	// if you use SimpleAudioEngine, it must be pause
	// SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	if(userDefault->getBoolForKey("Music"))
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	if(userDefault->getBoolForKey("Music"))
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
