//
//  BurstlyBannerAd.h
//  BurstlySample
//
//  Created by Abishek Ashok on 1/27/11.
//  Copyright 2011 rawr llc. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "OAIAdManager.h"
#import "OAIAdManagerDelegateProtocol.h"

@interface BurstlyBannerAd : UIView <OAIAdManagerDelegate> {
	NSString *pubId;
	NSString *zoneId;
	UIViewController *viewController;
	OAIAdManager *adManager;
}

@property (nonatomic, retain) NSString *pubId;
@property (nonatomic, retain) NSString *zoneId;
@property (nonatomic, retain) UIViewController *viewController;
@property (nonatomic, retain) OAIAdManager *adManager;

- (void)refreshAd;
- (void)setPaused:(BOOL)p;

@end
