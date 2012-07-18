//
//  ViewController.h
//  BurstlyBannerSample
//
//  Created by Tommy McGlynn on 4/23/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "OAIAdManager.h"
#import "OAIAdManagerDelegateProtocol.h"
#import "CCBurstly.h"

@interface ViewController : UIViewController <OAIAdManagerDelegate>
{
    BurstlyAdDelegate *delegateInstance;
}

- (void) setupAd;
- (void)showAd; 
- (void)setDelegate: (BurstlyAdDelegate *)instance; 



@property (nonatomic, retain) OAIAdManager *mBanner;
@property Anchor mBurstlyAnchor;
@property (nonatomic, retain) NSString *mPublisherId;
@property (nonatomic, retain) NSString *mZoneId;
@property (nonatomic, retain) NSString *mBurstlyAdId;


@end
