//
//  MyWebView.h
//  project
//
//  Created by lh on 14-5-12.
//
//

#import <Foundation/Foundation.h>
#include "LhWebView.h"
#include "cocos2d.h"
USING_NS_CC;
@interface MyWebView : NSObject<UIWebViewDelegate,UIAlertViewDelegate>
{
    
    LhWebView *mLayerWebView;
    UIView    *mView;
    
    UIWebView *mWebView;
    
    UIToolbar *mToolbar;
    
    UIBarButtonItem *mBackButton;
}
-(void) setLayerWebView : (LhWebView*) iLayerWebView URLString:(const char*) urlString;

-(void) backClicked:(id)sender;
@end
