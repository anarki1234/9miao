//
//  MyWebView.m
//  project
//
//  Created by lh on 14-5-12.
//
//

#import "MyWebView.h"
#import "EAGLView.h"
@implementation MyWebView
- (id)init{
    
    self = [super init];
    
    if (self) {
        
        // init code here.
        
    }
    
    return self;
    
}
- (void)webViewDidFinishLoad:(UIWebView *)thisWebView{
    
    [mWebView setUserInteractionEnabled:YES];
    
    mLayerWebView->webViewDidFinishLoad();
    
}
-(void) setLayerWebView : (LhWebView*) iLayerWebView URLString:(const char*) urlString{
    
    mLayerWebView = iLayerWebView;
    CGRect bouds = [[UIScreen mainScreen]applicationFrame];
    CGSize size = bouds.size;
    
    CCLOG("%f %f",size.width,size.height);
    
    mView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, size.width , size.height)];
    
    // create webView
    
    //Bottom size
    
    int wBottomMargin = size.height*0.10;
    
    int wWebViewHeight = size.height - wBottomMargin;
    mWebView = [[UIWebView alloc] initWithFrame:CGRectMake(0, 0, size.width, wWebViewHeight)];
    //CGRectMake(0, 0, size.width, wWebViewHeight)
    mWebView.delegate = self;
    
    NSString *urlBase = [NSString stringWithCString:urlString encoding:NSUTF8StringEncoding];
    mWebView.allowsInlineMediaPlayback = YES;
    mWebView.mediaPlaybackRequiresUserAction = NO;
    [mWebView loadRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:urlBase ]]];
    mWebView.scalesPageToFit = YES;
    [mWebView setUserInteractionEnabled:NO]; //don't let the user scroll while things are
    
    //create a tool bar for the bottom of the screen to hold the back button
    
    mToolbar = [UIToolbar new];
    
    [mToolbar setFrame:CGRectMake(0, wWebViewHeight, size.width, wBottomMargin)];
    
    mToolbar.barStyle = UIBarStyleBlackOpaque;
    
    //Create a button
    
    mBackButton = [[UIBarButtonItem alloc] initWithTitle:@"返 回"
                   
                                                   style: UIBarButtonItemStyleDone
                   
                                                  target: self
                   
                                                  action:@selector(backClicked:)];
    
    //[backButton setBounds:CGRectMake(0.0, 0.0, 95.0, 34.0)];
    
    [mToolbar setItems:[NSArray arrayWithObjects:mBackButton,nil] animated:YES];
    
    [mView addSubview:mToolbar];
    
    //[mToolbar release];
    

    
    // add the webView to the view
    
    [mView addSubview:mWebView];
    
    [[EAGLView sharedEGLView] addSubview:mView];
    
}
- (void)webView:(UIWebView *)thisWebView didFailLoadWithError:(NSError *)error {
    
    if ([error code] != -999 || error != NULL) { //error -999 happens when the user clicks on something before it's done loading.
        
        
        
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Network Error" message:@"Unable to load the page. Please keep network connection."
                              
                                                       delegate:self cancelButtonTitle:nil otherButtonTitles:@"OK", nil];
        
        [alert show];
        
        [alert release];
        
      
        
    }
}

-(void) backClicked:(id)sender {
    
    [[NSURLCache sharedURLCache] removeAllCachedResponses];
    
    NSHTTPCookie *cookie;
    NSHTTPCookieStorage *storage = [NSHTTPCookieStorage sharedHTTPCookieStorage];
    for (cookie in [storage cookies])
    {
        [storage deleteCookie:cookie];
    }
    
    mWebView.delegate = nil; //keep the webview from firing off any extra messages
    
    //remove items from the Superview...just to make sure they're gone
    
    [mToolbar removeFromSuperview];
    
    [mWebView removeFromSuperview];
    
    [mView removeFromSuperview];
    
   
    mLayerWebView->onBackButtonClick();
    
}


@end
