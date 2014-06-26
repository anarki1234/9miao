//
//  LhWebView.cpp
//  project
//
//  Created by lh on 14-5-12.
//
//

#include "LhWebView.h"
#import "MyWebView.h"
static MyWebView* m_webView = nil;
LhWebView::LhWebView()
{
    
}
LhWebView::~LhWebView()
{

    CAImageCache::sharedImageCache()->removeUnusedTextures();
    
}
bool LhWebView::initWithUrl(std::string url)
{
    if (!CAView::init()) {
        return false;
    }
    
    m_webView = [[MyWebView alloc] init];
    
    [m_webView setLayerWebView : NULL URLString:url.c_str()];
     
     return true;
}
void LhWebView::webViewDidFinishLoad()
{
    
}
void LhWebView::onBackButtonClick()
{
    
}