//  Copyright (c) 2014 http://9miao.com All rights reserved.
// 9秒小说阅读器在线讨论 http://www.9miao.com/group-40-59173.html
#include "MenuCell.h"
#include "PageManager.h"

MenuCell::MenuCell( OnCellDel *pOnCellDeleted )
{
	m_pOnCellDeleted = pOnCellDeleted;
	setFrame( CCRect( 0 , 0 , 720 , 65 ) );
	m_pMenuName = CALabel::createWithFrame( CCRect( 45 , 0 , 610 , 65 ) );
	m_pMenuName->setTextAlignment( CATextAlignmentLeft );
	m_pMenuName->setFontSize( 28 );
	m_pMenuName->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
	m_pMenuName->setColor( ccc4( 255 , 255 , 255 , 255 ) );
	//m_pMenuName->setNumberOfLine( 1 );
	addSubview( m_pMenuName );

	m_pDownloadingIcon = CAImageView::createWithImage( CAImage::create( "DownloadingIcon.png" ) );
	m_pDownloadingIcon->setFrame( CCRect( 670 , 15 , 31 , 31 ) );
	m_pDownloadingIcon->setVisible( false );
	addSubview( m_pDownloadingIcon );

	m_pDownloadFinishIcon = CAImageView::createWithImage( CAImage::create( "DownloadFinishIcon.png" ) );
	m_pDownloadFinishIcon->setFrame( CCRect( 670 , 15 , 31 , 31 ) );
	m_pDownloadFinishIcon->setVisible( false );
	addSubview( m_pDownloadFinishIcon );

	m_pDownloadFaield = CAImageView::createWithImage( CAImage::create( "DownloadFailed.png" ) );
	m_pDownloadFaield->setFrame( CCRect( 670 , 15 , 31 , 31 ) );
	m_pDownloadFaield->setVisible( false );
	addSubview( m_pDownloadFaield );

	m_pNotRead =  CAImageView::createWithImage( CAImage::create( "NotRead.png" ) );
	m_pNotRead->setFrame( CCRect( 17 , 26 , 12 , 12 ) );
	m_pNotRead->setVisible( false );
	addSubview( m_pNotRead );

	m_pReading =  CAImageView::createWithImage( CAImage::create( "Reading.png" ) );
	m_pReading->setFrame( CCRect( 17 , 26 , 12 , 12 ) );
	m_pReading->setVisible( false );
	addSubview( m_pReading );

	m_pReaded =  CAImageView::createWithImage( CAImage::create( "Readed.png" ) );
	m_pReaded->setFrame( CCRect( 17 , 26 , 12 , 12 ) );
	m_pReaded->setVisible( false );
	addSubview( m_pReaded );
}
MenuCell::~MenuCell()
{
	m_pOnCellDeleted->OnCellDeleted( this );
}
void MenuCell::LoadFromBookMenuData( BookMenu *pBookMenu )
{
	m_pMenuName->setText( pBookMenu->m_strBookMenu );
}
void MenuCell::UpdateStatus( int download_status , int read_status )
{
	if ( download_status == STATUS_NONE )
	{
		m_pDownloadingIcon->setVisible( false );
		m_pDownloadFinishIcon->setVisible( false );
		m_pDownloadFaield->setVisible( false );
	}
	else if ( download_status == STATUS_DOWNLOADING )
	{
		m_pDownloadingIcon->setVisible( true );
		m_pDownloadFinishIcon->setVisible( false );
		m_pDownloadFaield->setVisible( false );
	}
	else if ( download_status == STATUS_DOWNLOAD_FINISH )
	{
		m_pDownloadingIcon->setVisible( false );
		m_pDownloadFinishIcon->setVisible( true );
		m_pDownloadFaield->setVisible( false );
	}
	else if ( download_status == STATUS_DOWNLOAD_FAILED )
	{
		m_pDownloadingIcon->setVisible( false );
		m_pDownloadFinishIcon->setVisible( false );
		m_pDownloadFaield->setVisible( true );
	}
	if ( read_status == STATUS_NOTREAD )
	{
		m_pNotRead->setVisible( true );
		m_pReading->setVisible( false );
		m_pReaded->setVisible( false );
	}
	else if ( read_status == STATUS_READED )
	{
		m_pNotRead->setVisible( false );
		m_pReading->setVisible( false );
		m_pReaded->setVisible( true );
	}
	else if ( read_status == STATUS_READING )
	{
		m_pNotRead->setVisible( false );
		m_pReading->setVisible( true );
		m_pReaded->setVisible( false );
	}
}