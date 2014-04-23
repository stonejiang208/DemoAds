//-*- C++ -*-
#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#include "ProtocolAds.h"
class MyAdsListener : public cocos2d::plugin::AdsListener
{
public:
	virtual void onAdsResult(cocos2d::plugin::AdsResultCode code, const char* msg);
	virtual void onPlayerGetPoints(cocos2d::plugin::ProtocolAds* pAdsPlugin, int points);

};
class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void testShow(cocos2d::Ref* pSender);
	void testHide(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
	cocos2d::plugin::ProtocolAds* _admob;
	MyAdsListener* _listener;
	cocos2d::plugin::ProtocolAds* _ads;
	cocos2d::plugin::ProtocolAds::AdsPos _pos;
	cocos2d::plugin::TAdsInfo adInfo;
};

#endif // __HELLOWORLD_SCENE_H__
