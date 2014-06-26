package org.cocos2dx.lib;

import java.io.FileNotFoundException;

import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.ContentResolver;
import android.content.DialogInterface;
import android.content.Intent;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;

public class AndroidNativeTool
{
	private static AlertDialog mDialog = null;
	private static Activity s_pContext;
	native static void NativeReturn( String arg1 , Object arg2 );
	
	public AndroidNativeTool( final Activity context )
	{
		s_pContext = context;
		final CharSequence[] items = { "����", "¼��","��Ƶ","���" }; 
		mDialog = new AlertDialog.Builder(context).setTitle("ѡ��ͼƬ").setItems(items,   
    	new DialogInterface.OnClickListener() {   
        public void onClick(DialogInterface dialog,int item)
        {   
	        switch( item )
	        {
	        case 0:
	        	CAImageCapture();
	            break;
	        case 1:
	        	CAVideoCapture();
	            break;
	        case 2:
	        	CAVideoAlbum();
	        	break;
	        case 3:
	        	CAImageAlbum();
	            break;
	        }
        } } ).create();
	}
	public static void ShowDlg( String[] args )
    {
		s_pContext.runOnUiThread(new Runnable() {
            @Override
            public void run()
            {
            	mDialog.show();
            }
        });
    }
	
	public static void CAImageCapture()
	{
		Intent getImageByCamera= new Intent("android.media.action.IMAGE_CAPTURE");     
		s_pContext.startActivityForResult(getImageByCamera,0);
	}
	public static void CAVideoCapture()
	{
		Intent getImageByCamera2= new Intent("android.media.action.VIDEO_CAPTURE");     
		s_pContext.startActivityForResult(getImageByCamera2, 1);  
	}
	public static void CAVideoAlbum()
	{
		Intent intent = new Intent(Intent.ACTION_GET_CONTENT);
    	intent.setType("video/*"); //String VIDEO_UNSPECIFIED = "video/*";
    	Intent wrapperIntent = Intent.createChooser(intent, null);
    	s_pContext.startActivityForResult(wrapperIntent, 2);
	}
	public static void CAImageAlbum()
	{
		Intent getImage = new Intent(Intent.ACTION_GET_CONTENT);   
        //getImage.addCategory(Intent.CATEGORY_OPENABLE);   
        getImage.setType("image/*");  
        Intent wrapperIntent2 = Intent.createChooser(getImage, null);
        s_pContext.startActivityForResult(wrapperIntent2, 3);
	}
    public void onActivityResult(int requestCode, int resultCode, Intent intent)
    {  
    	ContentResolver resolver = s_pContext.getContentResolver();   
    	System.out.println(resultCode);
        if (resultCode == -1) {  
            switch (requestCode) {  
            case 2:
            case 3:  // Photo
                //���ͼƬ��uri   
            	//runNativeCallback(requestCode,resultCode,intent);
                Uri originalUri = intent.getData();  
                
                
                String[] proj = {MediaStore.Images.Media.DATA};

                

                //������android��ý�����ݿ�ķ�װ�ӿڣ�����Ŀ�Android�ĵ�

                Cursor cursor = s_pContext.managedQuery(originalUri, proj, null, null, null); 
                		//

                //���Ҹ������ ����ǻ���û�ѡ���ͼƬ������ֵ

                int column_index = cursor.getColumnIndexOrThrow(MediaStore.Images.Media.DATA);

                //�����������ͷ ���������Ҫ����С�ĺ���������Խ��

                cursor.moveToFirst();

                //����������ֵ��ȡͼƬ·��

                String path = cursor.getString(column_index);
                /*Bitmap bitmap = null;  
                try {  
                    Bitmap originalBitmap = BitmapFactory.decodeStream(resolver.openInputStream(originalUri));  
                } catch (FileNotFoundException e) {  
                    e.printStackTrace();  
                }*/
                NativeReturn( path , null );
                break;  
            case 1:
            case 0:  // camera image
                /*Bundle extras = intent.getExtras();   
                Bitmap originalBitmap1 = (Bitmap) extras.get("data");  */
            	originalUri = intent.getData();   
                NativeReturn( originalUri.getPath() , null );
                break;  
            default:  
                break;  
            }  
        }
    }
}
