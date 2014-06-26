//
//  CATextField.cpp
//  project
//
//  Created by lh on 14-5-15.
//
//
 
#include "CATextField.h"
#include "CCDirector.h"
#include "actions/CCActionInterval.h"
#include "CCEGLView.h"
#include <locale>
#include <algorithm>
#include "sprite_nodes/CAScale9ImageView.h"
NS_CC_BEGIN

CATextField::CATextField()
:m_pDelegate(0)
,m_pMark(NULL)
,spaceHolderIsOn(true)
,m_cTextColor(ccc4(0, 0, 0, 255))
,m_cSpaceHolderColor(ccc4(193, 193, 193, 255))
,m_fFontSize(24)
,willBg(NULL)
,isEditing(false)
,frontWidth(0)
,frontStr("")
,byteCount(0)
,bytePos(0)
,beforeWidth(0)
,m_nInputType(KEY_BOARD_INPUT_NORMAL)
,m_keyboardType(KEY_BOARD_TYPE_NORMAL)
,afterWidth(0)
{
   
}

CATextField::~CATextField()
{
    
}

void CATextField::onEnterTransitionDidFinish()
{
    CAControl::onEnterTransitionDidFinish();
}

void CATextField::onExitTransitionDidStart()
{
    CAControl::onExitTransitionDidStart();
}

bool CATextField::resignFirstResponder()
{
    bool result =CAView::resignFirstResponder();
    if (result) {
        attachWithIME();
    }
    return result;
}

bool CATextField::becomeFirstResponder()
{
    bool result = CAView::becomeFirstResponder();
    if (result) {
        detachWithIME();
    }
    return result;
    
}

CATextField* CATextField::createWithFrame(const CCRect& frame)
{
    CATextField *text = new CATextField();
    if (text && text->initWithFrame(frame))
    {
        text->autorelease();
        return text;
    }
    CC_SAFE_DELETE(text);
    return NULL;
}

CATextField* CATextField::createWithCenter(const CCRect& rect)
{
    CATextField* textField = new CATextField();
    
    if (textField && textField->initWithCenter(rect))
    {
        textField->autorelease();
        return textField;
    }
    
    CC_SAFE_DELETE(textField);
    return NULL;
}

bool CATextField::initWithFrame(const CCRect& frame)
{
    if (!CAControl::initWithFrame(frame,CAColor_red)) {
        return false;
    }
    width = CCDirector::sharedDirector()->getWinSize().width;
    TextAttribute t;
    t.charsize =0;
    t.charlength =0;
    this->setBackGroundImage(CAImage::create("bg_textfield.png"));
    m_vByteLengthArr.push_back(t);
    labelOrginX =0.015625*width;
    labelWidth =this->getBounds().size.width-0.03125*width;
    m_pText = CALabel::createWithFrame(CCRectMake(labelOrginX, this->getBounds().origin.y, labelWidth, this->getBounds().size.height));
    m_pText->setText("");
    m_sText="";
    m_pText->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    m_pText->setTextAlignment(CATextAlignmentLeft);
    m_pText->setNumberOfLine(1);
    m_pText->setFontSize(m_fFontSize);
    m_pText->setColor(m_cTextColor);
    m_pText->isInput =true;
    this->addSubview(m_pText);
    willBg = CAView::createWithFrame(CCRectZero,ccc4(65, 105, 255, 200));
    m_pText->addSubview(willBg);
    this->initMarkSprite();
    return true;
}

bool CATextField::initWithCenter(const CCRect& rect)
{
    if (!CAControl::initWithCenter(rect)) {
        return false;
    }
    width = CCDirector::sharedDirector()->getWinSize().width;
    TextAttribute t;
    t.charsize =0;
    t.charlength =0;
    this->setBackGroundImage(CAImage::create("bg_textfield.png"));
    m_vByteLengthArr.push_back(t);
    labelOrginX =0.015625*width;
    labelWidth =this->getBounds().size.width-0.03125*width;
    m_pText = CALabel::createWithCenter(CCRectMake(labelOrginX, this->getBounds().origin.y, labelWidth, this->getBounds().size.height));
    m_pText->setText("");
    m_sText="";
    m_pText->setVerticalTextAlignmet(CAVerticalTextAlignmentCenter);
    m_pText->setNumberOfLine(1);
    m_pText->setFontSize(m_fFontSize);
    m_pText->setColor(m_cTextColor);
    m_pText->isInput=true;
    this->addSubview(m_pText);
    willBg = CAView::createWithFrame(CCRectZero,ccc4(65, 105, 255, 200));
    m_pText->addSubview(willBg);
    this->initMarkSprite();
    return true;
}

void CATextField::initMarkSprite()
{
    int pixels[1][1];
    pixels[0][0] = 0;
    
    
    
    CAImage *image = new CAImage();
    image->initWithData(pixels, kCAImagePixelFormat_RGB888, 1, 1, CCSizeMake(m_fFontSize / 10.0f, m_fFontSize));
    
    m_pMark = CAView::create();
    m_pMark->setVisible(false);
    CCSize contentsize =this->getBounds().size;
	m_pMark ->setColor(CAColor_white);
    m_pMark->setFrame(CCRect(labelOrginX, 0, image->getContentSize().width, m_fFontSize));
    this->addSubview(m_pMark);
    
    m_pCursorAction = CCRepeatForever::create((CCActionInterval *) CCSequence::create(CCFadeOut::create(0.5f), CCFadeIn::create(0.5f), NULL));
    m_pMark->runAction(m_pCursorAction);
    
}

void CATextField::setFontSize(float var)
{
    m_fFontSize = var;
    
    m_pText->setFontSize(var);
    
    m_pMark->setFrame(CCRect(labelOrginX, 0, var / 10.0f, var));
}

float CATextField::getFontSize()
{
    return m_fFontSize;
}

void CATextField::setText(std::string var)
{
    m_sText=var;
}

std::string CATextField::getText()
{
    return m_sText;
}

void CATextField::setPlaceHolder(std::string var)
{
    m_sPlaceHolder = var;
    m_pText->setColor(getSpaceHolderColor());
    m_pText->setText(var);
}

std::string CATextField::getPlaceHolder()
{
    return m_sPlaceHolder;
}

void CATextField::setSpaceHolderColor(CAColor4B var)
{
    m_cSpaceHolderColor = var;
    m_pText->setColor(var);
    
}

CAColor4B CATextField::getSpaceHolderColor()
{
    return m_cSpaceHolderColor;
}

void CATextField::setTextColor(CAColor4B var)
{
    m_pText->setColor(var);
    m_cTextColor = var;
}

CAColor4B CATextField::getTextColor()
{
    
    return m_cTextColor;
}

void CATextField::setTextAlignment(CATextAlignment var)
{
    m_pText->setTextAlignment(var);
    m_aTextAlignment = var;
}

CATextAlignment CATextField::getTextAlignment()
{
    return m_aTextAlignment;
}

bool CATextField::attachWithIME()
{
    bool bRet = CCIMEDelegate::attachWithIME();
    if (bRet)
    {
        // open keyboard
        CCEGLView * pGlView = CCDirector::sharedDirector()->getOpenGLView();
        if (pGlView)
        {
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID||CC_TARGET_PLATFORM==CC_PLATFORM_IOS)        
            if (getKeyboardType() ==KEY_BOARD_TYPE_NORMAL)
            {
                pGlView->setIMEKeyboardDefault();
            }
            else if (getKeyboardType() ==KEY_BOARD_TYPE_NUMBER)
            {
                pGlView->setIMEKeyboardNumber();
            }
            else if(getKeyboardType() ==KEY_BOARD_TYPE_ALPHABET)
            {
                pGlView->setIMEKeyboardAlphabet();
            }
#endif
            pGlView->setIMEKeyboardState(true);
        }
    }
    return bRet;
}

bool CATextField::detachWithIME()
{
    bool bRet = CCIMEDelegate::detachWithIME();
    if (bRet)
    {
        // close keyboard
        CCEGLView * pGlView = CCDirector::sharedDirector()->getOpenGLView();
        if (pGlView)
        {
            pGlView->setIMEKeyboardState(false);
        }
    }
    return bRet;
}

void CATextField::setInputType(eKeyBoardInputType type)
{
    m_nInputType=type;
}

eKeyBoardInputType CATextField::getInputType()
{
    return m_nInputType;
}

bool CATextField::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (isEditing)
    {
        return false;
    }
    frontLength = 0;
    CCPoint point = this->convertTouchToNodeSpace(pTouch);
    
    if (this->getBounds().containsPoint(point))
    {
        resignFirstResponder();
        if (isFirstResponder())
        {
			attachWithIME();
            m_pMark->setVisible(true);
            byteCount =0;
            float markWidth =labelOrginX+ m_pText->getLabelSize().width;
            if (m_pText->getLabelSize().width>labelWidth)
            {
                markWidth = labelWidth;
            }else if(spaceHolderIsOn)
            {
                markWidth =labelOrginX;
            }
            m_pMark->setCenterOrigin(CCPoint(markWidth, this->getBounds().size.height/2));
            beforeWidth= m_pMark->getFrameOrigin().x;
            
            if (m_nInputType ==KEY_BOARD_INPUT_PASSWORD)
            {
                
                return true;
            }

			if (m_vByteLengthArr.size()==1)
			{
				m_pMark->setCenterOrigin(CCPoint(labelOrginX, this->getBounds().size.height / 2));
                beforeWidth= m_pMark->getFrameOrigin().x;
				bytePos = 0;
				return true;
					
			}
            
            float temporary = .0f;
            
            for (int i=0; i<m_vByteLengthArr.size(); i++)
            {
                
                
                TextAttribute t =m_vByteLengthArr.at(i);
                //((*(m_vByteLengthArr.begin()+i)));
                temporary+=t.charlength;
                byteCount+=t.charsize;
                if (temporary+labelOrginX>point.x+m_pText->getImageRect().origin.x&&i!=m_vByteLengthArr.size()-1)
                {
                    m_pMark->setCenterOrigin(CCPoint(temporary+labelOrginX-m_pText->getImageRect().origin.x, this->getBounds().size.height/2));
                    beforeWidth= m_pMark->getFrameOrigin().x;
                    frontLength = labelWidth-beforeWidth;
                    bytePos = i;
                    
                    break;
                }
                else if(i==m_vByteLengthArr.size()-1)
                {
                    m_pMark->setCenterOrigin(CCPoint(temporary+labelOrginX-m_pText->getImageRect().origin.x, this->getBounds().size.height/2));
                    beforeWidth= m_pMark->getFrameOrigin().x;
                    frontLength = labelWidth-beforeWidth;
                    bytePos = i;
                }
            }
            
        }
        return true;
    }
    else
    {
        if (becomeFirstResponder())
        {
            if (!strcmp(m_pText->getText().c_str(), ""))
            {
                m_pText->setColor(m_cSpaceHolderColor);
                m_pText->setText(m_sPlaceHolder);
                m_sText="";
                spaceHolderIsOn=true;
            }
            m_pMark->setVisible(false);
            return false;
        }
        return false;
    }
    
    return true;
}

bool CATextField::canAttachWithIME()
{
    return (m_pDelegate) ? (! m_pDelegate->onTextFieldAttachWithIME(this)) : true;
}

bool CATextField::canDetachWithIME()
{
    return (m_pDelegate) ? (! m_pDelegate->onTextFieldDetachWithIME(this)) : true;
}
void CATextField::analyzeString(std::string str,int len)
{
    
    for (int i=0; i<len; i++)
    {
        if (str[i]>0&& str[i]<127)
        {
//            if (str[i]!=32)
            {
               insertText(str.substr(i,1).c_str(), 1);
            }
//            else
//            {
//                continue;
//            }
        }
        else
        {
            std::string ss= str.substr(i,3);
            insertText(ss.c_str(), 3);
            i+=2;
        }
        
    }
    
}
void CATextField::insertText(const char * text, int len)
{

    if (len>3) {
        analyzeString(text, len);
        return;
    }
    if (m_nInputType == KEY_BOARD_INPUT_PASSWORD)
    {
        if (len>=2)
            return;
        
        m_sText.append(text);
        
        std::string password="";
        for (int i=0; i<m_sText.length(); i++)
        {
            password.append("*");
        }
        m_pText->setColor(m_cTextColor);
        m_pText->setText(password);
        
        CCRect rect = CCRectZero;
        rect.size = this->getBounds().size;
        rect.size.width = MIN(labelWidth, m_pText->getLabelSize().width);
        if (m_pText->getLabelSize().width < labelWidth)
        {
            m_pMark->setCenterOrigin(CCPoint(labelOrginX+ m_pText->getLabelSize().width,
                                             this->getBounds().size.height/2));
        }
        else
        {
            //textlength+lengt
            if (m_pText->getLabelSize().width<rect.size.width)
            {
                
                
                m_pMark->setCenterOrigin(CCPoint(labelOrginX+m_pText->getLabelSize().width,
                                                 this->getBounds().size.height/2));
                CCPoint pos = m_pText->getFrame().origin;
                
                CCRect r =m_pText->getImageRect();
                
                r.size.width = labelWidth;
                m_pText->setImageRect(r);
                
                m_pText->setFrameOrigin(pos);
                
            }
            else
            {
                CCPoint pos = m_pText->getFrame().origin;
                
                CCRect r =m_pText->getImageRect();
                r.origin.x =(m_pText->getLabelSize().width-labelWidth);
                
                r.size.width = labelWidth;
                m_pText->setImageRect(r);

                m_pText->setFrameOrigin(pos);

                m_pMark->setCenterOrigin(CCPoint(labelOrginX+ rect.size.width,
                                                 this->getBounds().size.height/2));
            }
        }
        return;
    }
    
    
    if (!strcmp(text, "\n"))
    {
        return;
    }
    
    std::string inputstr;
    spaceHolderIsOn = false;
    
    if(isEditing)
    {
        isEditing =false;
    }
    willBg->setVisible(false);
    
    if (len > 0)
    {
        if (m_pDelegate && m_pDelegate->onTextFieldInsertText(this,text, len))
        {
            // delegate doesn't want to insert text
            return;
        }
        std::string sText(frontStr);
        std::string beforeStr = frontStr.substr(0,byteCount);
        std::string backStr = frontStr.substr(byteCount,frontStr.length());
        char str[512]="";
        sprintf(str, "%s%s%s",beforeStr.c_str(),text,backStr.c_str());
        m_sText = str;
        m_pText->setText(str);
        float byteLength=m_pText->getLabelSize().width-frontWidth;
        TextAttribute t;
        t.charlength = byteLength;
        t.charsize = strlen(text);
        

        bytePos++;
        m_vByteLengthArr.insert(m_vByteLengthArr.begin()+bytePos, t);
        byteCount+=t.charsize;
        m_pText->setColor(m_cTextColor);
        frontStr = m_pText->getText();
        
        frontWidth =m_pText->getLabelSize().width;
        
        float _width = 0;
        for (int i=0; i<bytePos+1; i++)
        {
            TextAttribute t = m_vByteLengthArr.at(i);
            _width += t.charlength;
        }
        float _backwidth = frontWidth-_width;
        afterWidth = _backwidth;
        frontLength=_backwidth;
        CCRect rect = CCRectZero;
        rect.size = this->getBounds().size;
        if (m_pText->getLabelSize().width < labelWidth)
        {
            //小于文本框没问题
            m_pMark->setCenterOrigin(CCPoint(labelOrginX+ _width,
                                             this->getBounds().size.height/2));
            //m_pText->getLabelSize().width
            
        }
        else
        {
            CCPoint pos = m_pText->getFrame().origin;
            CCRect r =m_pText->getImageRect();
            r.size.width = labelWidth;
            m_pText->setFrameOrigin(pos);
            if (_width>labelWidth)
            {//m_pText->getLabelSize().width-r.origin.x
                m_pMark->setCenterOrigin(CCPoint(labelOrginX + labelWidth, this->getBounds().size.height/2));
                r.origin.x =(m_pText->getLabelSize().width-_backwidth-labelWidth);
            }else
            {
                m_pMark->setCenterOrigin(CCPoint(labelOrginX +_width, this->getBounds().size.height/2));
                r.origin.x =(m_pText->getImageRect().origin.x);
            }
            //r.origin.x =(0);
            m_pText->setImageRect(r);
        }
    }
}

void CATextField::willInsertText(const char *text, int len)
{
    
    
    if (m_nInputType ==KEY_BOARD_INPUT_PASSWORD)
        return;
    
    if (len>0)
    {
        temporaryString =text;
        isEditing = true;
        char sText[512]="";
        
        std::string beforeStr = frontStr.substr(0,byteCount);
        std::string backStr= frontStr.substr(byteCount,frontStr.length());
        sprintf(sText, "%s%s",frontStr.c_str(),text);
        m_pText->setText(sText);
        m_pText->setColor(ccc4(0, 0, 0, 255));
        float bglength=m_pText->getLabelSize().width;
        float textlength =0;
        if (lengthArr.size()>0)
        {
            textlength=0;
            bglength =0;
        }
        CCRect rect = CCRectZero;
        rect.size = this->getBounds().size;
        rect.size.width = MIN(labelWidth, m_pText->getLabelSize().width);

        if (m_pText->getLabelSize().width < labelWidth)
        {

            m_pMark->setCenterOrigin(CCPoint(labelOrginX , this->getBounds().size.height/2));
            willBg->setVisible(true);
            willBg->setFrame(CCRectMake(labelOrginX+ frontWidth,
                                        0 ,
                                        bglength-frontWidth,
                                        m_pText->getLabelSize().height));
        }
        else
        {
            CCPoint pos = m_pText->getFrame().origin;
            CCRect r =m_pText->getImageRect();
            r.origin.x =(m_pText->getLabelSize().width-labelWidth);
            r.size.width = labelWidth;
            m_pText->setImageRect(r);
            
            m_pText->setFrameOrigin(pos);
            m_pMark->setCenterOrigin(CCPoint(labelOrginX + rect.size.width, this->getBounds().size.height/2));//rect.size.width
            
            willBg->setVisible(true);
            
            if (frontWidth ==0)
            {
                willBg->setFrame(CCRectMake(labelOrginX, 0,labelWidth, m_pText->getLabelSize().height));//-m_pText->getLabelSize().height
            }
            else
            {
                float orgx=(labelOrginX+ m_pText->getBounds().size.width- (m_pText->getLabelSize().width-frontWidth));
                if(bglength>labelWidth&&m_pText->getBounds().size.width- (m_pText->getLabelSize().width-frontWidth)<0)
                {
                    bglength=labelWidth;
                    
                    orgx =labelOrginX;
                     willBg->setFrame(CCRectMake(orgx, 0,bglength, m_pText->getLabelSize().height));
                    
                }else
                {
                     willBg->setFrame(CCRectMake(orgx, 0,bglength-frontWidth, m_pText->getLabelSize().height));
                }
               
            }
            
            
        }

        return;
    }
    else if(len==0&&isEditing)
    {
        willBg->setFrame(CCRectMake(labelOrginX, 0,0, m_pText->getLabelSize().height));
        willBg->setVisible(false);
        temporaryString="";
        isEditing =false;
        CCRect rect = CCRectZero;
        rect.size = this->getBounds().size;
        rect.size.width = MIN(labelOrginX, m_pText->getLabelSize().width);
        if (strcmp(m_sText.c_str(), ""))
        {
            
            m_pMark->setCenterOrigin(CCPoint(labelOrginX+ rect.size.width, this->getBounds().size.height/2));
            m_pText->setText(m_sText);
        }else
        {
            m_pText->setText(m_sPlaceHolder.c_str());
            m_pText->setColor(m_cSpaceHolderColor);
            m_pMark->setCenterOrigin(CCPoint(labelOrginX , this->getBounds().size.height/2));
        }
        return;
    }
}
void CATextField::deleteBackward()
{
    if (m_nInputType==KEY_BOARD_INPUT_PASSWORD)
    {
        m_pText->setColor(m_cSpaceHolderColor);
        m_pText->setText(m_sPlaceHolder);
        m_sText="";
        spaceHolderIsOn=true;
        m_pMark->setCenterOrigin(CCPoint(labelOrginX, this->getBounds().size.height/2));
        return;
    }
    if(spaceHolderIsOn||m_vByteLengthArr.size()==1)//||bytePos==0
    {
        
        return;
    }
    
    int nStrLen =byteCount;
    
    std::string backString = m_pText->getText().substr(byteCount,m_pText->getText().length()-byteCount);
    // get the delete byte number
    int nDeleteLen = 1;    // default, erase 1 byte
    
    if (nStrLen == 0)
    {
        return;
    }
    
    while(0x80 == (0xC0 & m_pText->getText().at(nStrLen - nDeleteLen)))
    {
        ++nDeleteLen;
    }
    if (m_pDelegate && m_pDelegate->onTextFieldDeleteBackward(this, m_pText->getText().c_str() + nStrLen - nDeleteLen, nDeleteLen))
    {
        // delegate doesn't wan't to delete backwards
        return;
    }
    // if all text deleted, show placeholder string
    if (m_pText->getText().length() <= nDeleteLen)
    {
        m_pText->setColor(m_cSpaceHolderColor);
        m_pText->setText(m_sPlaceHolder);
        m_sText="";
        spaceHolderIsOn=true;
        frontWidth=0;
        m_vByteLengthArr.clear();
        TextAttribute tt;
        tt.charsize =0;
        tt.charlength =0;
        m_vByteLengthArr.push_back(tt);
        bytePos =0;
        byteCount =0;
        frontStr="";
        m_pMark->setCenterOrigin(CCPoint(labelOrginX, this->getBounds().size.height/2));
        return;
    }
    
    // set new input text
    std::string sText(m_pText->getText().c_str(), nStrLen - nDeleteLen);
    char str[512]="";
    sprintf(str, "%s%s",sText.c_str(),backString.c_str());
    
    float markWidth =m_pText->getLabelSize().width;

    TextAttribute t =m_vByteLengthArr.at(bytePos);
    m_vByteLengthArr.erase(m_vByteLengthArr.begin()+bytePos);
    
    if ( m_vByteLengthArr.size()>1&&bytePos>0)
    {
        
        bytePos--;
    }
    else
    {
        return;
    }
   
    byteCount=byteCount-nDeleteLen;
    frontStr=str;
    CCRect rect = CCRectZero;
    rect.size = this->getBounds().size;
    rect.size.width = MIN(labelOrginX, m_pText->getLabelSize().width);
    m_pText->setText(str);
    m_sText=str;
    
    float backLength = 0;
    for (int i =bytePos+1; i<m_vByteLengthArr.size(); i++)
    {
        TextAttribute t = m_vByteLengthArr.at(i);
        backLength += t.charlength;
    }
    afterWidth = MAX(0, afterWidth);
    if (m_pText->getLabelSize().width-afterWidth>labelWidth)
    {
        CCLog("//%d  %ld",bytePos,m_vByteLengthArr.size());
        CCLog("--%f  %f %f",frontLength,afterWidth,t.charlength);
        CCPoint pos = m_pText->getFrame().origin;
        CCRect r =m_pText->getImageRect();
        
        float orgX =m_pText->getLabelSize().width-afterWidth-labelWidth;
        if( orgX + labelWidth<m_pText->getLabelSize().width)
        {
            
            if (t.charlength>afterWidth)
            {
                r.origin.x =( m_pText->getLabelSize().width-labelWidth);
            }else
            {
                 r.origin.x =( orgX+t.charlength);
            }
            afterWidth -=t.charlength;
            
        }
        else
        {
            r.origin.x =( m_pText->getLabelSize().width-labelWidth);
        }
        
        if (bytePos == m_vByteLengthArr.size()-1)
        {
            markWidth =labelOrginX+ labelWidth;
        }
        else if(afterWidth>0)
        {
            CCLog("%f  %f",frontLength,afterWidth);
            markWidth=labelWidth-(frontLength-afterWidth);
            CCLog("%f",markWidth);
            //m_pMark->getFrameOrigin().x-t.charlength;
        }
        else
        {
            CCLog("frontLength  %f",frontLength);
            markWidth =labelWidth-frontLength;
        }
        
      //  r.origin.x =( m_pText->getLabelSize().width-labelWidth-afterWidth);
        r.size.width = labelWidth;
        m_pText->setImageRect(r);
        m_pText->setFrameOrigin(pos);
    }
    else
    {
        
        if (bytePos == m_vByteLengthArr.size()-1)
        {
            markWidth =labelOrginX+ m_pText->getLabelSize().width;
        }
        else
        {

            markWidth = labelOrginX+m_pText->getLabelSize().width-backLength;

        }
        beforeWidth= beforeWidth-t.charlength;
       
    }
    frontWidth = m_pText->getLabelSize().width;
    m_pMark->setCenterOrigin(CCPoint( markWidth, this->getBounds().size.height/2));
}

const char* CATextField::getContentText()
{
    return m_sText.c_str();
}

void CATextField::getKeyBoardHeight(int height)
{
    if( m_pDelegate && m_pDelegate->getKeyBoardHeight(height) )
    {
        return;
    }
    
}

void CATextField::setBackGroundImage(CAImage *image)
{
    this->setBackGroundViewForState(CAControlStateNormal, CAScale9ImageView::createWithImage(image));
}

CAImage *CATextField::getBackGroundImage()
{
    return  this->getBackGroundImage();
}

void CATextField::setContentSize(const CCSize& var)
{
    CCSize size = var;
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    if (size.height < winSize.width/10)
    {
        size.height = winSize.width/10;
    }
    CAControl::setContentSize(size);
    
}
NS_CC_END