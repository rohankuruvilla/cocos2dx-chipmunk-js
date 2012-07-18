//
//  BurstlySDKSampleAppInterstitial.h
//  BurstlySDKSampleApp
//
//  Created by Abi on 7/1/11.
//  Copyright 2011 Burstly. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "OAIAdManager.h"
#import "OAIAdManagerDelegateProtocol.h"

@class BurstlySDKSampleAppViewController;

@interface BurstlyInterstitialAd : NSObject<OAIAdManagerDelegate> {
    NSString *pubId;
	NSString *zoneId;
	UIViewController *viewController;
	OAIAdManager *adManager;
}

@property (nonatomic, retain) NSString *pubId;
@property (nonatomic, retain) NSString *zoneId;
@property (nonatomic, retain) UIViewController *viewController;

- (void) preCacheAd;
- (void) requestAd;
@end
