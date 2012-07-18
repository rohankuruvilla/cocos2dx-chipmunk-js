//
//  BurstlySDKSampleAppViewController.h
//  BurstlySDKSampleApp
//
//  Created by Abi on 6/27/11.
//  Copyright 2011 Burstly. All rights reserved.
//

#import <UIKit/UIKit.h>

#define INTERSTITIAL_ENABLED 1


@class BurstlyBannerAd;
@class BurstlyInterstitialAd;

@interface BurstlySDKSampleAppViewController : UIViewController {
    BurstlyBannerAd *bannerAd;
    BurstlyInterstitialAd *interstitialAd;
    IBOutlet UIButton *interstitialButton;
    UIView *spinnerView;
}

@property (nonatomic, retain) BurstlyBannerAd *bannerAd;
@property (nonatomic, retain) BurstlyInterstitialAd *interstitialAd;
@property (nonatomic, retain) UIButton *interstitialButton;
@property (nonatomic, retain) UIView *spinnerView;


- (IBAction) displayIntersitital;
- (void)removeSpinner;

@end
