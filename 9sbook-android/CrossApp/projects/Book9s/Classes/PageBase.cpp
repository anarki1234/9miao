//  Copyright (c) 2014 http://9miao.com All rights reserved.
// 9秒小说阅读器在线讨论 http://www.9miao.com/group-40-59173.html
#include "PageBase.h"
#include "PageHome.h"

PageBase::PageBase() 
{
}

void PageBase::HttpRequest( std::string url , SEL_HttpResponse onComplete )
{
	CCHttpClient* httpClient = CCHttpClient::getInstance();
    CCHttpRequest* httpReq = new CCHttpRequest();
    httpReq->setRequestType(CCHttpRequest::kHttpGet);
    httpReq->setUrl(utf8_to_url_string(url.c_str()).c_str());
    httpReq->setResponseCallback(this,onComplete);
    httpClient->setTimeoutForConnect(30);
    httpClient->send(httpReq);
    httpReq->release();
}

void PageBase::viewDidLoad()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	setKeypadEnabled( true );
#endif

	m_pPageView = CAView::createWithFrame( CAViewController::getView()->getFrame() , ccc4( 0 , 0 , 0 , 0 ) );
	CAViewController::getView()->addSubview( m_pPageView );

	m_pWaitView = CAView::createWithFrame( CAViewController::getView()->getFrame() , ccc4( 0 , 0 , 0 , 128 ) );
	CAViewController::getView()->addSubview( m_pWaitView );
	m_pWaitIcon = CAImageView::createWithImage( CAImage::create( "WaitIcon.png" ) );
	m_pWaitIcon->setFrame( CCRect( ( m_pWaitView->getFrame().size.width - m_pWaitIcon->getFrame().size.width ) / 2 ,
		( m_pWaitView->getFrame().size.height - m_pWaitIcon->getFrame().size.height ) / 2 , 0 , 0 ) );
	m_pWaitView->addSubview( m_pWaitIcon );
	m_pWaitView->setVisible( false );
}
void PageBase::viewDidUnload()
{
	if ( m_pWaitView->isVisible() ) m_pWaitView->setVisible( false );
	//this->getView()->removeAllSubviews();
}
CAView *PageBase::getView()
{
	return m_pPageView;
}
CAView *PageBase::getWait()
{
	return m_pWaitView;
}
void PageBase::ShowWait( bool bShow )
{
	m_pWaitView->setVisible( bShow );
	if ( bShow )
	{
		CAScheduler::schedule( schedule_selector( PageBase::OnTimer ) , this , 0.1 , false );
	}
	else
	{
		CAScheduler::unschedule( schedule_selector( PageBase::OnTimer ) , this );
	}
}
void PageBase::OnTimer( float time )
{
	m_pWaitIcon->setRotation( m_pWaitIcon->getRotation() + 45 );
}
void PageBase::BeginFrameMove( bool bBegin )
{
	if ( bBegin )
	{
		CAScheduler::schedule( schedule_selector( PageBase::OnFrameMove ) , this , 0.1 , false );
	}
	else
	{
		CAScheduler::unschedule( schedule_selector( PageBase::OnFrameMove ) , this );
	}
}
void PageBase::OnFrameMove( float time )
{
}
void PageBase::keyBackClicked()
{
	if ( getNavigationController() && dynamic_cast<PageHome*>( this ) )
	{
		if ( getNavigationController()->isNavigationBarHidden() )
			getNavigationController()->setNavigationBarHidden( false , false );
		else
			getNavigationController()->popViewControllerAnimated( true );
	}
}