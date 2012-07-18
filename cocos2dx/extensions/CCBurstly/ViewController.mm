//
//  ViewController.m
//  BurstlyBannerSample
//
//  Created by Tommy McGlynn on 4/23/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "ViewController.h"

@implementation ViewController

@synthesize mBanner;

@synthesize mBurstlyAnchor = Anchor_Top;
@synthesize mPublisherId;
@synthesize mZoneId;
@synthesize mBurstlyAdId;

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    
 
}

- (void)setupAd 
{
    // Create Burstly banner.
    mBanner = [[OAIAdManager alloc] initWithDelegate:self];
    [self.view addSubview:mBanner.view];
    [mBanner precacheAd];
    [mBanner requestRefreshAd];

}

- (void)showAd 
{
    // Create Burstly banner.
    [mBanner requestRefreshAd];
    
}


- (void)adManager:(OAIAdManager*)manager adNetworkControllerPresentFullScreen:(NSString*)aNetwork;
{
}

- (void)adManager:(OAIAdManager*)manager adNetworkControllerDismissFullScreen:(NSString*)aNetwork;
{
}

- (UIInterfaceOrientation)currentOrientation {
    return [[UIApplication sharedApplication] statusBarOrientation];
}


- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
    
    self.mBanner = nil;
    [self.mBanner release];

    [self.mPublisherId release];
    [self.mZoneId release];
    [self.mBurstlyAdId release];

}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated
{
	[super viewWillDisappear:animated];
}

- (void)viewDidDisappear:(BOOL)animated
{
	[super viewDidDisappear:animated];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
    } else {
        return YES;
    }
}

#pragma mark - OAIAdManager delegate

- (NSString *)publisherId
{
    return self.mPublisherId;
}

- (NSString*)getZone
{
    return self.mZoneId;
}

- (UIViewController*)viewControllerForModalPresentation
{
    return self;
}

- (Anchor)burstlyAnchor {
    // The ad will attach to the anchor point at the top center.
	return self.mBurstlyAnchor;
}

- (CGPoint)burstlyAnchorPoint {
    // Set anchor to top/center.
	return CGPointMake(self.view.frame.size.width / 2, 0);
}

- (CGFloat)defaultSessionLife {
    // A new ad will automatically be requested every 15 seconds.
	return 15.0f;
}

- (void)setDelegate: (BurstlyAdDelegate *)instance
{
    self->delegateInstance = instance;
}


- (void)adManager:(OAIAdManager*)manager requestThrottled:(NSNumber*)time {
    int time_int = [time intValue];
    self->delegateInstance->nativeRequestThrottled(time_int);  
    NSLog(@"adManager:%p interstitialRequestThrottled:%@", manager, time);
}

- (void)adManager:(OAIAdManager*)manager didPrecacheAd:(NSString*)aNetwork {
    const char * testStr = [aNetwork cStringUsingEncoding: NSASCIIStringEncoding];
    self->delegateInstance->nativeDidPrecacheAd(testStr);  
    NSLog(@"adManager:%p interstitialDidPrecache:%@", manager, aNetwork);
}

- (void)adManager:(OAIAdManager*)manager attemptingToLoad:(NSString*)aNetwork {
    const char * testStr = [aNetwork cStringUsingEncoding: NSASCIIStringEncoding];
    self->delegateInstance->nativeAttemptingToLoad(testStr);  
	NSLog(@"adManager:%p attemptingToLoad:%@", manager, aNetwork);
}

- (void)adManager:(OAIAdManager*)manager didLoad:(NSString*)aNetwork {
    const char * testStr = [aNetwork cStringUsingEncoding: NSASCIIStringEncoding];
    self->delegateInstance->nativeDidFinishLoading(testStr);    
	NSLog(@"adManager:%p didLoad:%@", manager, aNetwork);
}

- (void)adManager:(OAIAdManager*)manager failedToLoad:(NSString*)aNetwork {
    const char * testStr = [aNetwork cStringUsingEncoding: NSASCIIStringEncoding];
    self->delegateInstance->nativeFailedToLoad(testStr);  
	NSLog(@"adManager:%p failedToLoad:%@", manager, aNetwork);
}

- (void)adManager:(OAIAdManager*)manager didLoad:(NSString*)aNetwork isInterstitial:(BOOL)isInterstitial {
    const char * testStr = [aNetwork cStringUsingEncoding: NSASCIIStringEncoding];
    self->delegateInstance->nativeDidFinishLoading(testStr, true);  
    NSLog(@"adManager:%p didLoad Interstial:%@", manager, aNetwork);
}

@end



