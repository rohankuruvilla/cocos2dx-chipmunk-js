//
//  SWScrollView.h
//  SWGameLib
//
//  Copyright (c) 2010-2012  cocos2d-x.org
//  Copyright (c) 2010 Sangwoo Im
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//  
//
//  Created by Sangwoo Im on 6/3/10.
//  Copyright 2010 Sangwoo Im. All rights reserved.
//

#ifndef __CCBURSTLY_H__
#define __CCBURSTLY_H__

#include "layers_scenes_transitions_nodes/CCLayer.h"


typedef enum {
  CCBurstlyPositionTop = 0,
  CCBurstlyPositionLeft,
  CCBurstlyPositionBottom,
  CCBurstlyPositionRight
} CCBurstlyPosition;

NS_CC_EXT_BEGIN

/**
 * @addtogroup GUI
 * @{
 */

class CCBurstly;

class CC_DLL CCBurstlyDelegate
{
public:
    virtual ~CCBurstlyDelegate() {}
    virtual void CCBurstly_attemptingToLoad(std::string network) = 0;
    virtual void CCBurstly_didLoad(std::string network) = 0;
    virtual void CCBurstly_didPrecacheAd(std::string network) = 0;
    virtual void CCBurstly_failedToDisplayAds(CCBurstly* bur) = 0;
    virtual void CCBurstly_failedToLoad(CCBurstly* bur) = 0;
    virtual void CCBurstly_requestThrottled(int timeInMsec) = 0;
    virtual void CCBurstly_startRequestToServer(CCBurstly* bur) = 0;
    // virtual void scrollViewDidZoom(CCScrollView* view) = 0;
};


/**
 * ScrollView support for cocos2d for iphone.
 * It provides scroll view functionalities to cocos2d projects natively.
 */
class CC_DLL CCBurstly : public CCLayer
{
public:
    CCBurstly();
    virtual ~CCBurstly();

    bool init();
    virtual void registerWithTouchDispatcher();
    /**
     * Returns an autoreleased scroll view object.
     * @deprecated: This interface will be deprecated sooner or later.
     * @param size view size
     * @param container parent object
     * @return autoreleased scroll view object
     */
    CC_DEPRECATED_ATTRIBUTE static CCBurstly* viewWithViewSize(CCSize size, CCNode* container = NULL);

    /**
     * Returns an autoreleased scroll view object.
     *
     * @param size view size
     * @param container parent object
     * @return autoreleased scroll view object
     */
    static CCBurstly* create(CCSize size, CCNode* container = NULL);

    /**
     * Returns an autoreleased scroll view object.
     * @deprecated: This interface will be deprecated sooner or later.
     * @param size view size
     * @param container parent object
     * @return autoreleased scroll view object
     */
    CC_DEPRECATED_ATTRIBUTE static CCBurstly* node();

    /**
     * Returns an autoreleased scroll view object.
     *
     * @param size view size
     * @param container parent object
     * @return autoreleased scroll view object
     */
    static CCBurstly* create();

    /**
     * Returns a scroll view object
     *
     * @param size view size
     * @param container parent object
     * @return scroll view object
     */
    bool initWithViewSize(CCSize size, CCNode* container = NULL);

    /**
     * Sets a new content offset. It ignores max/min offset. It just sets what's given. (just like UIKit's UIScrollView)
     *
     * @param offset new offset
     * @param If YES, the view scrolls to the new offset
     */
    void setPosition(const CCBurstlyPosition &pos);
    //CCPoint getPosition();
    
    void precacheAd();
    void sendRequestForAd();
    
    CCScrollViewDelegate* getDelegate() { return m_pDelegate; }
    void setDelegate(CCScrollViewDelegate* pDelegate) { m_pDelegate = pDelegate; }

    void onShowActivity();
    void onHideActivity();
    
    void sendRequestForAd();
    
    void showAd();
    void hideAd();

    void setArParams(std::string params);
    
    void setPaused(bool isPaused);
    void setPublisherId(std::string publisherId);
    
    void setZoneId(std::string zoneId);
    
private:
    /**
     * Init this object with a given size to clip its content.
     *
     * @param size view size
     * @return initialized scroll view object
     */
    bool initWithViewSize(CCSize size);
    void beforeDraw();
    /**
     * retract what's done in beforeDraw so that there's no side effect to
     * other nodes.
     */
    void afterDraw();

protected:
    /**
     * current zoom scale
     */
    CCFloat m_fZoomScale;
    /**
     * min zoom scale
     */
    CCFloat m_fMinZoomScale;
    /**
     * max zoom scale
     */
    CCFloat m_fMaxZoomScale;
    /**
     * scroll view delegate
     */
    CCScrollViewDelegate* m_pDelegate;

    CCScrollViewDirection m_eDirection;
    /**
     * If YES, the view is being dragged.
     */
    bool m_bDragging;

    /**
     * Content offset. Note that left-bottom point is the origin
     */
    CCPoint m_tContentOffset;

    /**
     * Container holds scroll view contents, Sets the scrollable container object of the scroll view
     */
    CCNode* m_pContainer;
    /**
     * Determiens whether user touch is moved after begin phase.
     */
    bool m_bTouchMoved;
    /**
     * max inset point to limit scrolling by touch
     */
    CCPoint m_fMaxInset;
    /**
     * min inset point to limit scrolling by touch
     */
    CCPoint m_fMinInset;
    /**
     * Determines whether the scroll view is allowed to bounce or not.
     */
    bool m_bBounceable;

    bool m_bClippingToBounds;

    /**
     * scroll speed
     */
    CCPoint m_tScrollDistance;
    /**
     * Touch point
     */
    CCPoint m_tTouchPoint;
    /**
     * length between two fingers
     */
    CCFloat m_fTouchLength;
    /**
     * UITouch objects to detect multitouch
     */
    CCArray* m_pTouches;
    /**
     * size to clip. CCNode boundingBox uses contentSize directly.
     * It's semantically different what it actually means to common scroll views.
     * Hence, this scroll view will use a separate size property.
     */
    CCSize m_tViewSize;
    /**
     * max and min scale
     */
    CCFloat m_fMinScale, m_fMaxScale;
};

// end of GUI group
/// @}

NS_CC_EXT_END

#endif /* __CCSCROLLVIEW_H__ */
