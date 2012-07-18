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

@interface ViewController : UIViewController <OAIAdManagerDelegate>

@property (nonatomic, retain) OAIAdManager *mBanner;

@end
