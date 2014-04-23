#include "HelloWorldScene.h"
#include "PluginManager.h"
#include "Configs.h"

USING_NS_CC;
using namespace cocos2d::plugin;
void MyAdsListener::onAdsResult(AdsResultCode code, const char* msg)
{
	log("OnAdsResult, code : %d, msg : %s", code, msg);
}

void MyAdsListener::onPlayerGetPoints(cocos2d::plugin::ProtocolAds* pAdsPlugin, int points)
{
	log("Player get points : %d", points);

	// @warning should add code to give game-money to player here

	// spend the points of player
	if (pAdsPlugin != NULL) {
		pAdsPlugin->spendPoints(points);
	}
}


Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    _listener = new MyAdsListener();
    _admob = dynamic_cast<ProtocolAds*>(PluginManager::getInstance()->loadPlugin("AdsAdmob"));
    TAdsDeveloperInfo devInfo;
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    devInfo["AdmobID"] = ADMOB_ID_IOS;
    devInfo["FlurryAppKey"] = FLURRY_KEY_IOS;
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    devInfo["AdmobID"] = ADMOB_ID_ANDROID;
    devInfo["FlurryAppKey"] = FLURRY_KEY_ANDROID;
#endif
    
    _admob->configDeveloperInfo(devInfo);
    _admob->setAdsListener(_listener);
    _admob->setDebugMode(true);

		_ads = _admob;
		_pos = ProtocolAds::kPosTop;

    // init the AdsInfo
    adInfo["AdmobType"] = "1";
    adInfo["AdmobSizeEnum"] = "1";
    

		
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World Plugins", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

		LabelTTF* label1 = LabelTTF::create("ShowAds", "Arial", 24);
		MenuItemLabel* pItemShow = MenuItemLabel::create(label1, CC_CALLBACK_1(HelloWorld::testShow, this));
		pItemShow->setPosition (Point (100,200));
		menu->addChild (pItemShow);


		LabelTTF* label2 = LabelTTF::create("HideAds", "Arial", 24);
		MenuItemLabel* pItemHide = MenuItemLabel::create(label2, CC_CALLBACK_1(HelloWorld::testHide, this));
		pItemHide->setPosition (Point (100,160));
		menu->addChild (pItemHide);
		
	  testShow (0);	
    return true;
}

void HelloWorld::testShow (Ref* )
{
	if (_ads)
	{
		_ads->showAds(adInfo, _pos);
	}
}

void HelloWorld::testHide (Ref* )
{
	if (_ads)
	{
		_ads->hideAds(adInfo);
	}
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
if (_admob != NULL)
    {
			_admob->hideAds(adInfo);
    	PluginManager::getInstance()->unloadPlugin("AdsAdmob");
    	_admob = NULL;
    }

    if (NULL != _listener)
    {
    	delete _listener;
    	_listener = NULL;
    }
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
