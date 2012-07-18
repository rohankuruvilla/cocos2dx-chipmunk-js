#import "BurstlyController.h"
#import "ViewController.h"



BurstlyController *__mBurstlyController;

void BurstlyAdController::setDelegate(BurstlyAdDelegate *delegate) {
    [__mBurstlyController.viewController setDelegate: delegate];
}

int BurstlyAdController::setupBurstlyParams (const char *pubId, const char *zId, int pos, const char *burstlyAdId)
{
    __mBurstlyController = [[BurstlyController alloc] init];
    return [(id) __mBurstlyController setPubId:(void *)pubId zoneId:(void *)zId pos:(void *)pos 
                                   burstlyAdId: (void *)burstlyAdId];
}

void BurstlyAdController::showBurstlyAd() {
    [(id) __mBurstlyController.viewController showAd];
}


@implementation BurstlyController

@synthesize viewController = _viewController;

-(NSString *)getNSStringFromChar: (void *) str
{
    return [NSString stringWithCString: (const char *)str encoding:NSASCIIStringEncoding];
}


- (int) setPubId:(void *)pubId zoneId:(void *)zId pos:(void *) pos 
     burstlyAdId: (void *) burstlyAdId 
{
    self.viewController = [[[ViewController alloc] initWithNibName:nil bundle:nil] autorelease];
    UIWindow *window = [UIApplication sharedApplication].keyWindow;
    
    NSString *pubIdStr = [self getNSStringFromChar:pubId];
    NSString *zIdStr = [self getNSStringFromChar:zId];
    NSString *burstlyAdIdStr = [self getNSStringFromChar:burstlyAdId];
    int anchor = (int) pos;    
    
    self.viewController.mBurstlyAdId = burstlyAdIdStr;
    self.viewController.mBurstlyAnchor = (Anchor) anchor;
    self.viewController.mPublisherId = pubIdStr;
    self.viewController.mZoneId = zIdStr;    
    [self.viewController setupAd];
    
    [window addSubview: self.viewController.view];
    [window makeKeyAndVisible];
    
    return 1;
}


- (void)dealloc {
    [super dealloc];
    [_viewController release];
    
}

@end