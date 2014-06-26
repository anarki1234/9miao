//  Copyright (c) 2014 http://9miao.com All rights reserved.
// 9秒小说阅读器在线讨论 http://www.9miao.com/group-40-59173.html
#include "ViewController.h"
#include "PageManager.h"
#include "PageSearch.h"
#include "PageReader.h"
#include "PageMenu.h"
#include "PageRank.h"
#include "PageSetting.h"
#include "PageBookInfo.h"


class MessageBoxView : public CAView
{
public:
	MessageBoxView( CCRect frame )
	{
		setFrame( frame );
		setColor( ccc4( 0 , 0 , 0 , 127 ) );
	}
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
	{
		setVisible( false );
		return true;
	}
};
CAWindow* ViewController::createWindow()
{
	CAWindow* _window = CAWindow::create();

	CANavigationController *p = new CANavigationController();
	p->initWithRootViewController( PageManager::Instance()->CreatePageHome() );
	p->getNavigationBar()->setBackGroundImage( CAImage::create("Title.png") );
	PageManager::Instance()->SetNavigationController( p );

	_window->setRootViewController(p);

	CAView *pMessageBox = new MessageBoxView( _window->getFrame() );
	_window->addSubview( pMessageBox );
	pMessageBox->setVisible( false );
	PageManager::Instance()->SetMessageBoxLayer( pMessageBox );
	p->release();
	pMessageBox->release();
	return _window;
}
