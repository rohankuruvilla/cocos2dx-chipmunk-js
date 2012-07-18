#import "ViewController.h"

@interface BurstlyController : NSObject
{
    int someVar;
}


@property (strong, nonatomic) ViewController *viewController;

- (int) setPubId:(void *)pubId zoneId: (void *) zId pos: (void *) pos burstlyAdId: (void *)burstlyAdId;
-(NSString *)getNSStringFromChar: (void *) str;

@end
