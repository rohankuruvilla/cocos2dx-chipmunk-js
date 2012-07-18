#include "string"
#include "map"

#ifndef __BURSTLYCONTROLLER_C_INTERFACE_H__
#define __BURSTLYCONTROLLER_C_INTERFACE_H__ 1

class BurstlyAdDelegate {
public:
    void virtual nativeDidFinishLoading (const char *adId) = 0;
    void virtual nativeDidStartRequest (const char *adId)= 0;
    void virtual nativeDidPrecacheAd (const char *adId)= 0;
    void virtual nativeDidFinishLoading (const char *adId, bool isInterstitial)= 0;
    void virtual nativeRequestThrottled (int time)= 0;
    void virtual nativeFailedToLoad (const char *adId)= 0;
    void virtual nativeAttemptingToLoad (const char *adId)= 0;
};

class BurstlyAdController {
public:
    int setupBurstlyParams (const char *pubId, const char *zId, int pos, const char *burstlyAdId);
    void showBurstlyAd ();
    void setDelegate(BurstlyAdDelegate *delegate);
};


#endif


