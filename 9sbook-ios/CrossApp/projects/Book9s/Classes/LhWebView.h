//
//  LhWebView.h
//  project
//
//  Created by lh on 14-5-12.
//
//

#ifndef __project__LhWebView__
#define __project__LhWebView__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
class LhWebView:public CAView
{
public:
    LhWebView();
    virtual ~LhWebView();
    virtual bool initWithUrl(std::string url);
    void webViewDidFinishLoad();
    void onBackButtonClick();
private:
    int mWebViewLoadCounter;
};
#endif /* defined(__project__LhWebView__) */
