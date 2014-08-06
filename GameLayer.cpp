#include "GameLayer.h"

#define MATRIX_WIDTH (9)
#define MATRIX_HEIGHT (9)

#define SPIRTE_GAP (1)

#define userDefault UserDefault::getInstance()

int choices[2][6][2] = {
	{
		{1,-1},{1,0},{0,1},{-1,0},{-1,-1},{0,-1}
	},
	{
		{1,0},{1,1},{0,1},{-1,1},{-1,0},{0,-1}
	}
};

GameLayer::GameLayer()
	:m_exit(NULL),
	m_matrix(NULL),
	m_mark(NULL),
	//spriteSheet(NULL),
	m_width(0),
	m_height(0),
	m_isTouchEnable(true),
	m_raindrop(NULL),
	m_markSize(0),
	m_isTrapped(false)
{

}

GameLayer::~GameLayer()
{
	if(m_matrix){
		free(m_matrix);
	}
	if(m_mark){
		free(m_mark);
	}
}

Scene *GameLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = GameLayer::create();
	scene->addChild(layer);
	return scene;
}
bool GameLayer::init()
{
	if (!Layer::init()) {
		return false;
	}

	// background
	Size winSize = Director::getInstance()->getWinSize();
	auto background = Sprite::create("main_game/lawn.png");
	background->setAnchorPoint(Point(0, 1));
	background->setPosition(Point(0, winSize.height));
	this->addChild(background);

	m_height = MATRIX_HEIGHT;
	m_width = MATRIX_WIDTH;
	//初始化地图矩阵
	int arraySize = sizeof(SquareSprite *) * m_width * m_height;
	m_matrix = (SquareSprite **)malloc(arraySize);
	memset((void*)m_matrix, 0, arraySize);
	//初始化标记数组
	m_markSize = sizeof(bool) * m_width * m_height;
	m_mark = (bool*)malloc(m_markSize);
	memset((void*)m_mark,false,m_markSize);
	//初始化所有地图精灵
	for(int row = 0;row<m_height;++row)
	{
		for(int col = 0;col<m_width;++col)
		{
			SquareSprite * sprite = SquareSprite::create(row,col);
			Point position = positionOfItem(row, col);
			sprite->setPosition(position);
			addChild(sprite,1);
			m_matrix[row * m_width + col] = sprite;
		}
	}
	//随机初始化云彩
	initCloud();
	//初始化小雨滴
	m_raindrop = Raindrop::create(4,4);
	Point position = positionOfItem(4, 4);
	m_raindrop->setPosition(position);
	addChild(m_raindrop,2);
	// bind touch event实现触摸效果
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	//响应键盘消息
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyReleased = CC_CALLBACK_2(GameLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

	return true;
}
//得到坐标
Point GameLayer::positionOfItem(int row, int col)
{
	float x = (SquareSprite::getContentWidth() + SPIRTE_GAP) * col + SquareSprite::getContentWidth() / 2;
	float y = (SquareSprite::getContentWidth() + SPIRTE_GAP) * row + SquareSprite::getContentWidth() / 2 + 45;
	if(row%2)//形成偏移的效果
	{
		x = x+SquareSprite::getContentWidth() / 2;
	}
	return Point(x, y);
}
//响应安卓返回键
void GameLayer::onKeyReleased(EventKeyboard::KeyCode keycode,Event* event)
{
	if(keycode == EventKeyboard::KeyCode::KEY_BACKSPACE)
	{
		/*Scene* newScene = Pause::createScene();
		Pause* layer = Pause::create();
		layer->scene_num = 1;
		newScene->addChild(layer);
		Director::sharedDirector()->pushScene(newScene);*/
	}
}
//获取点击事件
bool GameLayer::onTouchBegan(Touch *touch, Event *unused)
{
	/*
	if(exit)
	{
		exit->removeFromParentAndCleanup(true);
		exit = NULL;
	}*/
	//m_srcSushi = NULL;
	if (m_isTouchEnable ) 
	{
		//点击出现云彩
		auto location = touch->getLocation();
		SquareSprite* srcSprite = spriteOfPoint(&location);
		if(srcSprite)
		{
			if(!srcSprite->getSelected())//未被选择过
			{
				srcSprite->setSelected(true);
				CCTexture2D * texture = CCTextureCache::sharedTextureCache()->addImage("block2.png");
				srcSprite->setTexture(texture);
				moveRaindrop();
			}
		}
	}
	return m_isTouchEnable;
}
//得到点击了哪个格子
SquareSprite *GameLayer::spriteOfPoint(Point *point)
{
	SquareSprite *sprite = NULL;
	Rect rect = Rect(0, 0, 0, 0);

	for (int i = 0; i < m_height * m_width; i++) {
		sprite = m_matrix[i];
		if (sprite) {
			rect.origin.x = sprite->getPositionX() - (sprite->getContentSize().width / 2);
			rect.origin.y = sprite->getPositionY() - (sprite->getContentSize().height / 2);
			rect.size = sprite->getContentSize();
			//修改，空隙也属于精灵的一部分
			rect.size.height += SPIRTE_GAP;
			rect.size.width += SPIRTE_GAP;
			if (rect.containsPoint(*point)) {
				return sprite;
			}
		}
	}
	return NULL;
}
//随机初始化云彩
void GameLayer::initCloud()
{
	srand(time(NULL));
	//初始化云彩的数量
	int num = rand()%14 + 7;
	//初始化云彩的位置
	while(num--)
	{
		int col = rand()%9;
		int row = rand()%9;
		if(col != 4 && row != 4)
		{
			SquareSprite* srcSprite = m_matrix[row*MATRIX_WIDTH + col];
			srcSprite->setSelected(true);
			CCTexture2D * texture = CCTextureCache::sharedTextureCache()->addImage("block2.png");
			srcSprite->setTexture(texture);
		}
	}
}
//移动雨滴
void GameLayer::moveRaindrop()
{
	SquareSprite* next = NULL;
	int row = m_raindrop->getRow();
	int col = m_raindrop->getCol();
	int bestWay = 81;
	int odd = row%2;
	for(int i = 0;i<6;++i)//分别向可以走的六个方向调用寻路的递归函数
	{
		//每次调用都重新初始化标记数组
		memset((void*)m_mark,false,m_markSize);
		//当前坐标也标记为走过了
		m_mark[row*m_width+col] = true;
		int next_row = row + choices[odd][i][0];
		int next_col = col + choices[odd][i][1];
		SquareSprite* next_sprite = m_matrix[next_row*MATRIX_WIDTH + next_col];
		if(next_sprite->getSelected())//已经变成云了
		{
			continue;
		}
		else
		{
			int result = findWay(next_row,next_col,1,i);
			if(result != -1)
			{
				if(result < bestWay)
				{
					bestWay = result;
					next = next_sprite;
				}
			}
			else//雨滴成功逃脱了
			{
				//更换到endlayer
				//CCDirector::sharedDirector()->replaceScene(EndLayer::createScene());
				//Director::getInstance()->end();
				m_isTrapped = true;
			}
		}
	}
	if(bestWay == 81)//如果雨滴被围住了，随便找一个方向走
	{
		for(int i = 0;i<6;++i)
		{
			int next_row = row + choices[odd][i][0];
			int next_col = col + choices[odd][i][1];
			SquareSprite* next_sprite = m_matrix[next_row*MATRIX_WIDTH + next_col];
			if(!next_sprite->getSelected())//可以走就走
			{
				next = next_sprite;
			}
		}
	}
	if(next)
	{
		m_raindrop->runAction(MoveTo::create(0.3, next->getPosition()));
		m_raindrop->setCol(next->getCol());
		m_raindrop->setRow(next->getRow());
	}
	else{//雨滴被围住了
		//更换到endlayer
		Director::getInstance()->end();
		//CCDirector::sharedDirector()->replaceScene(EndLayer::createScene());
	}
	if(m_isTrapped){
		Director::getInstance()->end();
	}
}
//雨滴的逃生路线，result代表最短路径的长度，用于筛选最短路径，返回值也是result
//返回值 -1代表雨滴成功逃脱了，进入结束页面
//			 81代表雨滴被围住了。。
//贪心算法，雨滴可以向六个方向移动，当雨滴向某一个方向移动的时候，我们认为他会一直向该方向移动才能找到最佳路径
//通过最后的tag记录当前行进的方向
int GameLayer::findWay(int row,int col,int result,int tag)
{
	m_mark[row*m_width+col] = true;
	int odd = row%2;
	int best_way = 81;
	if(col <= 0 || col >= 8 || row <= 0 || row >= 8){//走到终点
		if(result == 1){
			return -1;//雨滴已经走到了终点
		}
		return result;
	}
	for(int j = tag;j<6+tag;++j)
	{
		int i = j%6;
		int next_row = row + choices[odd][i][0];
		int next_col = col + choices[odd][i][1];
		SquareSprite* next_sprite = m_matrix[next_row*MATRIX_WIDTH + next_col];
		if(next_sprite->getSelected() || m_mark[next_row*m_width+next_col])//已经变成云了或该点走过了
		{
			continue;
		}
		else
		{
			int res = findWay(next_row,next_col,result+1,i);
			if(res < best_way)
			{
				best_way = res;
			}
		}
	}
	return best_way;
}