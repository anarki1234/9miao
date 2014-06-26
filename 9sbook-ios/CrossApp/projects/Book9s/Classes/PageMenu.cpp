//  Copyright (c) 2014 http://9miao.com All rights reserved.
// 9秒小说阅读器在线讨论 http://www.9miao.com/group-40-59173.html
#include "PageMenu.h"
#include "PageManager.h"
#include "PageReader.h"
#include "MenuCell.h"

PageMenu *g_pCurrentPageMenu;
PageMenu *PageMenu::GetCurrentPageMenu()
{
	return g_pCurrentPageMenu;
}
PageMenu::PageMenu()
{
	m_pMenuList = NULL;
	CANavigationBarItem *pItem = CANavigationBarItem::create( ("目录") );
	setNavigationBarItem( pItem );
	pItem->setLeftButtonItem( CABarButtonItem::create( "" , CAImage::create( "BackButton.png" ) , CAImage::create( "BackButton.png" ) ) );
	m_nPage = 1;
}
PageMenu::~PageMenu()
{
}
void PageMenu::viewDidLoad()
{
	g_pCurrentPageMenu = this;
	PageBase::viewDidLoad();

	CAImageView *pBk = CAImageView::createWithImage(CAImage::create("Bk.png"));
	pBk->setFrame( getView()->getFrame() );
	getView()->addSubview( pBk );

	m_pMenuList = new CATableView();
	m_pMenuList->initWithFrame( CCRect( 0 , 0 , getView()->getFrame().size.width , getView()->getFrame().size.height - 120 ) );
	m_pMenuList->setTableViewDataSource(this);
    m_pMenuList->setTableViewDelegate(this);
	m_pMenuList->setTablePullViewHeight( 96 );
	//m_pMenuList->setTablePullDownView( CAView::createWithColor( ccc4( 34 , 168 , 109 , 255 ) ) );
	m_pMenuList->setTablePullUpView( CAImageView::createWithImage(CAImage::create("MenuDropList.png") ) );
	m_pMenuList->setTablePullDownView( CAView::createWithColor( ccc4( 34 , 168 , 109 , 255 ) ) );
	getView()->addSubview( m_pMenuList );
	m_pMenuList->release();
	m_pMenuList->setAllowsSelection( true );

	CAImageView *pBk2 = CAImageView::createWithImage(CAImage::create("Bk2.png"));
	pBk2->setFrame( CCRect( 0 , getView()->getFrame().size.height - 120 , getView()->getFrame().size.width , 120 ) );
	getView()->addSubview( pBk2 );

	m_pProgress = CAProgress::create();
	m_pProgress->setFrame( CCRect( 0 , -40 , 720 , 44 ) );
	//m_pProgress->setProgressTintColor( ccc4( 34 , 168 , 109 , 255 ) );
	m_pProgress->setProgressTintColor( ccc4( 255 , 255 , 255 , 255 ) );
	m_pProgress->setProgressTintImage( CAImage::create( "DownloadProgress.png" ) );
	m_pProgress->setProgresstrackColor( ccc4( 74 , 103 , 92 , 255 ) );
	m_pProgress->setVisible( false );
	pBk2->addSubview( m_pProgress );

	m_pProgressLabel = CALabel::createWithFrame( m_pProgress->getFrame() );
	m_pProgressLabel->setColor( ccc4( 255 , 255 , 255 , 255 ) );
	m_pProgressLabel->setFontSize( 28 );
	m_pProgressLabel->setTextAlignment( CATextAlignmentCenter );
	m_pProgressLabel->setVerticalTextAlignmet( CAVerticalTextAlignmentCenter );
	pBk2->addSubview( m_pProgressLabel );

	// 下载全书
	{
		CAButton *pButton = CAButton::createWithFrame( CCRect( 64 , 22 , 260 , 88 ) , CAButtonTypeCustom );
		pButton->setBackGroundViewForState( CAControlStateNormal , CAScale9ImageView::createWithImage( CAImage::create( "ButtonNormal.png" ) ) );
		pButton->setBackGroundViewForState( CAControlStateHighlighted , CAScale9ImageView::createWithImage( CAImage::create( "ButtonLight.png" ) ) );
		pButton->setBackGroundViewForState( CAControlStateDisabled , CAScale9ImageView::createWithImage( CAImage::create( "ButtonDisable.png" ) ) );
		CALabel *pLabel = CALabel::createWithFrame( CCRect( 0 , 0 , pButton->getFrame().size.width , pButton->getFrame().size.height ) );
		pLabel->setText( ("下载全书") );
		pLabel->setColor( ccc4( 255 , 255 , 255 , 255 ) );
		pLabel->setFontSize( 28 );
		pLabel->setTextAlignment( CATextAlignmentCenter );
		pLabel->setVerticalTextAlignmet( CAVerticalTextAlignmentCenter );
		pButton->addSubview( pLabel );
		pBk2->addSubview( pButton );
		pButton->addTarget( this , CAControl_selector(PageMenu::OnDownloadAllButtonDown) , CAControlTouchUpInSide );
	}

	// 章节下载
	{
		CAButton *pButton = CAButton::createWithFrame( CCRect( 400 , 22 , 260 , 88 ) , CAButtonTypeCustom );
		pButton->setBackGroundViewForState( CAControlStateNormal , CAScale9ImageView::createWithImage( CAImage::create( "ButtonNormal.png" ) ) );
		pButton->setBackGroundViewForState( CAControlStateHighlighted , CAScale9ImageView::createWithImage( CAImage::create( "ButtonLight.png" ) ) );
		pButton->setBackGroundViewForState( CAControlStateDisabled , CAScale9ImageView::createWithImage( CAImage::create( "ButtonDisable.png" ) ) );
		CALabel *pLabel = CALabel::createWithFrame( CCRect( 0 , 0 , pButton->getFrame().size.width , pButton->getFrame().size.height ) );
		pLabel->setText( ("下载后续章节") );
		pLabel->setColor( ccc4( 255 , 255 , 255 , 255 ) );
		pLabel->setFontSize( 28 );
		pLabel->setTextAlignment( CATextAlignmentCenter );
		pLabel->setVerticalTextAlignmet( CAVerticalTextAlignmentCenter );
		pButton->addSubview( pLabel );
		pBk2->addSubview( pButton );
		pButton->addTarget( this , CAControl_selector(PageMenu::OnDownloadButtonDown) , CAControlTouchUpInSide );
	}

	ShowWait( true );
	BookDB::Instance()->GetBookMenu( &m_bookData , this , BookDB_selector(PageMenu::OnComplete) );
}
void PageMenu::OnDownloadAllButtonDown( CAControl* pTarget, CCPoint point )
{
	BookDB::Instance()->DownloadBook( &m_bookData , 0 , (int)m_bookData.m_vecMenu.size() , this , BookDB_selector(PageMenu::OnDownloadComplete) );
	for ( int i = 0 ; i < (int)m_bookData.m_vecMenu.size() ; i ++ )
	{
		if ( m_vecMenuCell[i] != NULL )
		{
			m_vecMenuCell[i]->UpdateStatus( BookDB::Instance()->GetBookMenuDownloadStatus( &m_bookData , i ) , -1 );
		}
	}
}
void PageMenu::OnDownloadButtonDown( CAControl* pTarget, CCPoint point )
{
	BookData out;
	if ( BookDB::Instance()->FindLastReadBook( &out , m_bookData.GetKeyName() ) )
		m_bookData.m_nLastReadMenu = out.m_nLastReadMenu;
	else
		m_bookData.m_nLastReadMenu = 0;
	BookDB::Instance()->DownloadBook( &m_bookData , m_bookData.m_nLastReadMenu , (int)m_bookData.m_vecMenu.size() , this , BookDB_selector(PageMenu::OnDownloadComplete) );
	for ( int i = m_bookData.m_nLastReadMenu ; i < (int)m_bookData.m_vecMenu.size() ; i ++ )
	{
		if ( m_vecMenuCell[i] != NULL )
		{
			m_vecMenuCell[i]->UpdateStatus( BookDB::Instance()->GetBookMenuDownloadStatus( &m_bookData , i ) , -1 );
		}
	}
}
void PageMenu::viewDidUnload()
{
	g_pCurrentPageMenu = NULL;
	m_pMenuList->setTableViewDataSource(NULL);
	m_pMenuList->setTableViewDelegate(NULL);
	m_pMenuList = NULL;
	PageBase::viewDidUnload();
}
void PageMenu::SetBookData( BookData &data )
{
	m_bookData = data;
	m_vecMenuCell.clear();
	m_vecMenuCell.resize( m_bookData.m_vecMenu.size() );
}
void PageMenu::OnComplete( void *pData )
{
	ShowWait( false );
	if ( pData != NULL )
	{
		m_bookData = *(BookData*)pData;
		m_vecMenuCell.clear();
		m_vecMenuCell.resize( m_bookData.m_vecMenu.size() );
		if ( m_pMenuList != NULL ) m_pMenuList->reloadData();
	}
}
void PageMenu::OnDownloadComplete( void *pData )
{
	int row = *(int*)pData;
	if ( row < m_bookData.m_vecMenu.size() )
	{
		if ( m_vecMenuCell[row] != NULL )
			m_vecMenuCell[row]->UpdateStatus( BookDB::Instance()->GetBookMenuDownloadStatus( &m_bookData , row ) , -1 );
		float cur = (float)BookDB::Instance()->GetDownloadingNum() - 1;
		float max = (float)BookDB::Instance()->GetDownloadingMaxNum();
		if ( m_pProgress != NULL )
		{
			if ( cur > 0 && cur <= max && max > 0 )
			{
				m_pProgress->setVisible( true );
				m_pProgressLabel->setVisible( true );
				m_pProgress->setProgress( (max - cur) / max );

				char buf[256];
				snprintf( buf , 256 , "%d%%" , (int)((max - cur) / max * 100.0f) );
				m_pProgressLabel->setText( buf );
			}
			else
			{
				m_pProgress->setProgress( 0 );
				m_pProgress->setVisible( false );
				m_pProgressLabel->setVisible( false );
			}
		}
	}
}
void PageMenu::OnUpdateStatus( BookData *pBookData )
{
	if ( pBookData->GetKeyName() == m_bookData.GetKeyName() )
		OnDownloadComplete( &pBookData->m_nLastReadMenu );
}
CATableViewCell* PageMenu::tableCellAtIndex(CATableView *table, unsigned int section, unsigned int row)
{
	CATableViewCell* cell = table->dequeueReusableCellWithIdentifier("aaa");
    if (cell == NULL)
    {
        cell = CATableViewCell::create("aaa");

		cell->setBackGroundViewForState(CAControlStateSelected, CAView::createWithColor(ccc4(89, 104, 109, 255)));
		cell->setBackGroundViewForState(CAControlStateHighlighted, CAView::createWithColor(ccc4(89, 104, 109, 255)));
		cell->setBackGroundViewForState(CAControlStateNormal, CAView::createWithColor(ccc4(0, 0, 0, 0)));
    }
    cell->removeAllSubviews();

	
	if ( row < m_bookData.m_vecMenu.size() )
	{
		MenuCell *pIcon = new MenuCell( this );
		pIcon->LoadFromBookMenuData( &m_bookData.m_vecMenu[row] );
		pIcon->UpdateStatus( BookDB::Instance()->GetBookMenuDownloadStatus( &m_bookData , row ) , BookDB::Instance()->GetBookMenuReadStatus( &m_bookData , row ) );
		cell->addSubview(pIcon);
		pIcon->release();
		m_vecMenuCell[row] = pIcon;
	}
	return cell;
}
unsigned int PageMenu::numberOfRowsInSection(CATableView *table, unsigned int section)
{
	int num = m_nPage * 30;
	if ( num > m_bookData.m_vecMenu.size() ) num = m_bookData.m_vecMenu.size();
	return num;
}
unsigned int PageMenu::tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
	return 65;
}
void PageMenu::tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
{
	CCDelayTime *p2 = CCDelayTime::create(0.5);
	CCCallFunc *p3 = CCCallFunc::create( this , callfunc_selector(PageMenu::TouchBeginFinish) );
	CCSequence *p4 = CCSequence::create( p2 , p3 , NULL );
	this->getView()->runAction( p4 );
	ShowWait( true );
	m_nTouchBeginRow = row;
}
void PageMenu::TouchBeginFinish()
{
	ShowWait( false );
	if ( m_nTouchBeginRow >= 0 && m_nTouchBeginRow < (unsigned int)m_bookData.m_vecMenu.size() )
	{
		PageBase *pPageReader = PageManager::Instance()->CreatePageReader( m_bookData , m_nTouchBeginRow );
		getNavigationController()->replaceViewController( pPageReader , true );
	}
}
void PageMenu::tableViewDidShowPullDownView(CATableView* table)
{
	
}
void PageMenu::tableViewDidShowPullUpView(CATableView* table)
{
	m_nPage ++;
	table->reloadData();
}
void PageMenu::OnCellDeleted( MenuCell *p )
{
	for ( int i = 0 ; i < (int)m_vecMenuCell.size() ; i ++ )
		if ( m_vecMenuCell[i] == p ) m_vecMenuCell[i] = NULL;
}