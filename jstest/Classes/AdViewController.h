//
//  AdViewController.h
//  HelloWorld
//
//  Created by Rohan Kuruvilla on 6/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "OAIAdManager.h"
#import "OAIAdManagerDelegateProtocol.h"

@interface AdViewController : UIViewController <OAIAdManagerDelegate> {
    OAIAdManager *adManager;
}

@end
