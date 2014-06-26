package com.component.impl;

import android.annotation.TargetApi;
import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.View;
import android.view.View.OnLongClickListener;
import android.view.ViewGroup.LayoutParams;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.AbsoluteLayout;

@SuppressWarnings("deprecation")
public class WebViewCtrl {

	private final String Tag = "WebViewCtrl";
	private WebView webView = null;
	private static AbsoluteLayout layout = null;
	private static Activity context;
	private static WebViewCtrl instance = null;

	public WebViewCtrl() {
	}

	public static WebViewCtrl getInstance() {
		if (instance == null)
			instance = new WebViewCtrl();
		return instance;
	}

	public static void init(Activity activity) {
		WebViewCtrl.context = activity;
		layout = new AbsoluteLayout(context);

		DisplayMetrics metrics = new DisplayMetrics();
		context.getWindowManager().getDefaultDisplay().getMetrics(metrics);
		int width = metrics.widthPixels;
		int height = metrics.heightPixels;
		int margin = 0;
		if ((float) width / height > 2.0 / 3.0) {
			// 宸﹀彸鐣欒竟
			margin = (int) ((width - ((2.0 * height) / 3.0)) / 2.0);
			layout.setPadding(margin, 0, margin, 0);
		} else if ((float) width / height < 2.0 / 3.0) {
			// 涓婁笅鐣欒竟
			margin = (int) ((height - ((3.0 * width) / 2.0)) / 2.0);
			layout.setPadding(0, margin, 0, margin);
		}

		context.addContentView(layout, new LayoutParams(
				LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT));
	}

	// 鏄剧ずwebView
	/*private void initWebView() {
		try {
			if (webView != null) {
				layout.removeView(webView);
				webView = null;
			}
			// 鍒濆鍖杦ebView
			webView = new WebView(context);
			// 璁剧疆webView鑳藉鎵цjavascript鑴氭湰
			webView.getSettings().setJavaScriptEnabled(true);
			webView.setScrollBarStyle(0);
			webView.setHorizontalScrollBarEnabled(false);
			webView.setVerticalScrollBarEnabled(false);
			// 璁剧疆鍙互鏀寔缂╂斁
			// webView.getSettings().setSupportZoom(true);
			// 璁剧疆鍑虹幇缂╂斁宸ュ叿
			// webView.getSettings().setBuiltInZoomControls(true);
			// webView.setLayerType(View.LAYER_TYPE_SOFTWARE, null);

			webView.getSettings().setSupportZoom(false);

			if (Build.VERSION.SDK_INT >= 11) {
				webViewBgTransFix(webView);
			}

			webView.setBackgroundColor(0);
			// 浣块〉闈㈣幏寰楃劍鐐�			webView.setFocusable(false);
			// 濡傛灉椤甸潰涓摼鎺ワ紝濡傛灉甯屾湜鐐瑰嚮閾炬帴缁х画鍦ㄥ綋鍓峛rowser涓搷搴�			webView.setWebViewClient(new WebViewClient() {
				public boolean shouldOverrideUrlLoading(WebView view, String url) {
					if (url.indexOf("tel:") < 0) {
						view.loadUrl(url);
					}
					return true;
				}
			});

			webView.setOnLongClickListener(new OnLongClickListener() {
				public boolean onLongClick(View v) {
					return true;
				}
			});
			layout.addView(webView);
		} catch (Exception e) {
			Log.d(Tag, "initWebView", e);
		}
	}

	@TargetApi(11)
	private void webViewBgTransFix(WebView webView) {
		webView.setLayerType(View.LAYER_TYPE_SOFTWARE, null);
	}

	public void openWebView(final String url) {
		if (context == null)
			return;
		context.runOnUiThread(new Runnable() {
			// 鍦ㄤ富绾跨▼閲屾坊鍔犲埆鐨勬帶浠�			public void run() {
				try {
					initWebView();
					// 杞藉叆URL
					if (webView != null)
						webView.loadUrl(url);
				} catch (Exception e) {
					Log.d(Tag, "openWebView", e);
				}
			}
		});
	}

	// 璁剧疆鎺т欢鎵�湪鐨勪綅缃甕Y锛屽苟涓斾笉鏀瑰彉瀹介珮锛�	// XY涓虹粷瀵逛綅缃�	public void setWebViewPos(final int x, final int y) {
		if (context == null)
			return;
		context.runOnUiThread(new Runnable() {
			public void run() {
				try {
					if (webView == null)
						return;
					LayoutParams laParams = (LayoutParams) webView
							.getLayoutParams();
					AbsoluteLayout.LayoutParams newLaParams = new AbsoluteLayout.LayoutParams(
							laParams.width, laParams.height, x, y);

					webView.setLayoutParams(newLaParams);
				} catch (Exception e) {
					Log.d(Tag, "setWebViewPos", e);
				}
			}
		});
	}

	// 璁剧疆鎺т欢瀹介珮
	public void setWebViewSize(final int width, final int height) {
		if (context == null)
			return;
		context.runOnUiThread(new Runnable() {
			public void run() {
				try {
					if (webView == null)
						return;
					LayoutParams laParams = (LayoutParams) webView
							.getLayoutParams();
					laParams.width = width;
					laParams.height = height;

					webView.setLayoutParams(laParams);
				} catch (Exception e) {
					Log.d(Tag, "setWebViewSize", e);
				}
			}
		});
	}

	// 绉婚櫎webView
	public void removeWebView() {
		if (context == null)
			return;
		context.runOnUiThread(new Runnable() {
			public void run() {
				try {
					if (webView != null) {
						layout.removeView(webView);
						webView = null;
					}
				} catch (Exception e) {
					Log.d(Tag, "removeWebView", e);
				}
			}
		});
	}*/

	// 鎵撳紑娴忚鍣�	
	public void browserOpenURL(final String url) {
		context.runOnUiThread(new Runnable() {
			public void run() {
				try {
					if (context == null)
						return;
					Intent intent = new Intent();
					intent.setAction("android.intent.action.VIEW");
					Uri content_url = Uri.parse(url);
					intent.setData(content_url);
					context.startActivity(intent);
				} catch (Exception e) {
					Log.d(Tag, "browserOpenURL", e);
				}
			}
		});
	}
}
