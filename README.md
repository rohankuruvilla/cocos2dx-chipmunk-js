Android build for Chipmunk JavaScript bindings for Cocos2d-x. Using old bindings of Cocos2d-x to bootstrap the test suite.

This repository has two main parts.

1. Chipmunk JS Bindings - at jstest/proj.android/jni/jsbindings
2. Chipmunk Tests - at jstest/proj.android/assets/testChipmunk.js

Note:

Test suite is sort of incomplete until the new cocos2d-x JS bindings can be incorporated.

How to build:

1. Run ./build_native.sh from jstest/proj.android directory.
2.1. If using Eclipse:

   2.1.1. Import project jstest
   2.1.2. Run project on emulator or device

2.2. If using command line:
     
   2.2.1. Rung "ant debug" from jstest/proj.android directory. Or "ant release"
   2.2.2. Run on device or emulator.

