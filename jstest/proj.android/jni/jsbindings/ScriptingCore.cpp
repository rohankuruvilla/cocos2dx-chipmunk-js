//
//  ScriptingCore.cpp
//  testmonkey
//
//  Created by Rolando Abarca on 3/14/12.
//  Copyright (c) 2012 Zynga Inc. All rights reserved.
//

#include <iostream>
#include "cocos2d.h"
#include "ScriptingCore.h"
#include "cocos2d_generated.hpp"
#include "cocos_denshion_generated.hpp"

#include "js_bindings_chipmunk_functions.h"
#include "js_bindings_chipmunk_manual.h"

using namespace cocos2d;

static JSClass global_class = {
  "global", JSCLASS_GLOBAL_FLAGS,
  JS_PropertyStub, JS_PropertyStub, JS_PropertyStub, JS_StrictPropertyStub,
  JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, JS_FinalizeStub,
  JSCLASS_NO_OPTIONAL_MEMBERS
};


ScriptingCore::ScriptingCore()
{
  this->rt = JS_NewRuntime(8 * 1024 * 1024);
  this->cx = JS_NewContext(rt, 8192);
  JS_SetOptions(this->cx, JSOPTION_VAROBJFIX);
  JS_SetVersion(this->cx, JSVERSION_LATEST);
  JS_SetErrorReporter(this->cx, ScriptingCore::reportError);
  global = JS_NewCompartmentAndGlobalObject(cx, &global_class, NULL);
  if (!JS_InitStandardClasses(cx, global)) {
    CCLog("js error");
  }
  // create the cocos namespace
  JSObject *cocos = JS_NewObject(cx, NULL, NULL, NULL);
  jsval cocosVal = OBJECT_TO_JSVAL(cocos);
  JS_SetProperty(cx, global, "cc", &cocosVal);

  // register the internal classes
  S_CCPoint::jsCreateClass(this->cx, cocos, "Point");
  S_CCSize::jsCreateClass(this->cx, cocos, "Size");
  S_CCRect::jsCreateClass(this->cx, cocos, "Rect");
  S__ccGridSize::jsCreateClass(this->cx, cocos, "GridSize");
  S_CCSet::jsCreateClass(this->cx, cocos, "Set");
  S_CCTouch::jsCreateClass(this->cx, cocos, "Touch");
  S_CCDirector::jsCreateClass(this->cx, cocos, "Director");
  S_CCNode::jsCreateClass(this->cx, cocos, "Node");
  S_CCTextureAtlas::jsCreateClass(this->cx, cocos, "TextureAtlas");
  S_CCSpriteBatchNode::jsCreateClass(this->cx, cocos, "SpriteBatchNode");
  S_CCScene::jsCreateClass(this->cx, cocos, "Scene");
  S_CCLayer::jsCreateClass(this->cx, cocos, "Layer");
  S_CCSprite::jsCreateClass(this->cx, cocos, "Sprite");
  S_CCRenderTexture::jsCreateClass(this->cx, cocos, "RenderTexture");
  S_CCMenu::jsCreateClass(this->cx, cocos, "Menu");
  S_CCMenuItem::jsCreateClass(this->cx, cocos, "MenuItem");
  S_CCMenuItemLabel::jsCreateClass(this->cx, cocos, "MenuItemLabel");
  S_CCMenuItemSprite::jsCreateClass(this->cx, cocos, "MenuItemSprite");
  S_CCMenuItemImage::jsCreateClass(this->cx, cocos, "MenuItemImage");
  S_CCSpriteFrame::jsCreateClass(this->cx, cocos, "SpriteFrame");
  S_CCSpriteFrameCache::jsCreateClass(this->cx, cocos, "SpriteFrameCache");
  S_CCAnimation::jsCreateClass(this->cx, cocos, "Animation");
  S_CCAction::jsCreateClass(this->cx, cocos, "Action");
  S_CCActionInterval::jsCreateClass(this->cx, cocos, "ActionInterval");
  S_CCFiniteTimeAction::jsCreateClass(this->cx, cocos, "FiniteTimeAction");
  S_CCActionInstant::jsCreateClass(this->cx, cocos, "ActionInstant");
  S_CCDelayTime::jsCreateClass(this->cx, cocos, "DelayTime");
  S_CCAnimate::jsCreateClass(this->cx, cocos, "Animate");
  S_CCMoveTo::jsCreateClass(this->cx, cocos, "MoveTo");
  S_CCMoveBy::jsCreateClass(this->cx, cocos, "MoveBy");
  S_CCRotateBy::jsCreateClass(this->cx, cocos, "RotateBy");
  S_CCRotateTo::jsCreateClass(this->cx, cocos, "RotateTo");
  S_CCActionEase::jsCreateClass(this->cx, cocos, "ActionEase");
  S_CCEaseRateAction::jsCreateClass(this->cx, cocos, "EaseRateAction");
  S_CCEaseIn::jsCreateClass(this->cx, cocos, "EaseIn");
  S_CCEaseOut::jsCreateClass(this->cx, cocos, "EaseOut");
  S_CCEaseInOut::jsCreateClass(this->cx, cocos, "EaseInOut");
  S_CCEaseBackInOut::jsCreateClass(this->cx, cocos, "EaseBackInOut");
  S_CCEaseBackOut::jsCreateClass(this->cx, cocos, "EaseBackOut");
  S_CCEaseElasticIn::jsCreateClass(this->cx, cocos, "EaseElasticIn");
  S_CCEaseElastic::jsCreateClass(this->cx, cocos, "EaseElastic");
  S_CCEaseElasticOut::jsCreateClass(this->cx, cocos, "EaseElasticOut");
  S_CCEaseElasticInOut::jsCreateClass(this->cx, cocos, "EaseElasticInOut");
  S_CCEaseBounce::jsCreateClass(this->cx, cocos, "EaseBounce");
  S_CCEaseBounceIn::jsCreateClass(this->cx, cocos, "EaseBounceIn");
  S_CCEaseBounceInOut::jsCreateClass(this->cx, cocos, "EaseBounceInOut");
  S_CCEaseBackIn::jsCreateClass(this->cx, cocos, "EaseBackIn");
  S_CCEaseBounceOut::jsCreateClass(this->cx, cocos, "EaseBounceOut");
  S_CCEaseExponentialIn::jsCreateClass(this->cx, cocos, "EaseExponentialIn");
  S_CCEaseExponentialOut::jsCreateClass(this->cx, cocos, "EaseExponentialOut");
  S_CCEaseExponentialInOut::jsCreateClass(this->cx, cocos, "EaseExponentialInOut");
  S_CCEaseSineIn::jsCreateClass(this->cx, cocos, "EaseSineIn");
  S_CCEaseSineOut::jsCreateClass(this->cx, cocos, "EaseSineOut");
  S_CCEaseSineInOut::jsCreateClass(this->cx, cocos, "EaseSineInOut");
  S_CCRepeatForever::jsCreateClass(this->cx, cocos, "RepeatForever");
  S_CCSequence::jsCreateClass(this->cx, cocos, "Sequence");
  S_CCLabelTTF::jsCreateClass(this->cx, cocos, "LabelTTF");
  S_CCParticleSystem::jsCreateClass(this->cx, cocos, "ParticleSystem");
  S_CCFileUtils::jsCreateClass(this->cx, cocos, "FileUtils");
  S_CCTexture2D::jsCreateClass(this->cx, cocos, "Texture2D");
  S_CCTextureCache::jsCreateClass(this->cx, cocos, "TextureCache");
  S_CCParallaxNode::jsCreateClass(this->cx, cocos, "ParallaxNode");
  S_CCTintBy::jsCreateClass(this->cx, cocos, "TintBy");
  S_CCTintTo::jsCreateClass(this->cx, cocos, "TintTo");
  S_CCLayerColor::jsCreateClass(this->cx, cocos, "LayerColor");
  S_CCBlink::jsCreateClass(this->cx, cocos, "Blink");
  S_CCSpeed::jsCreateClass(this->cx, cocos, "Speed");
  S_CCGridAction::jsCreateClass(this->cx, cocos, "GridAction");
  S_CCGrid3DAction::jsCreateClass(this->cx, cocos, "Grid3DAction");
  S_CCWaves3D::jsCreateClass(this->cx, cocos, "Waves3D");
  S_CCTransitionScene::jsCreateClass(this->cx, cocos, "TransitionScene");
  S_CCTransitionSceneOriented::jsCreateClass(this->cx, cocos, "TransitionSceneOriented");
  S_CCTransitionRotoZoom::jsCreateClass(this->cx, cocos, "TransitionRotoZoom");
  S_CCTransitionFadeDown::jsCreateClass(this->cx, cocos, "TransitionFadeDown");
  S_CCTransitionJumpZoom::jsCreateClass(this->cx, cocos, "TransitionJumpZoom");
  S_CCTransitionMoveInL::jsCreateClass(this->cx, cocos, "TransitionMoveInL");
  S_CCTransitionMoveInR::jsCreateClass(this->cx, cocos, "TransitionMoveInR");
  S_CCTransitionMoveInT::jsCreateClass(this->cx, cocos, "TransitionMoveInT");
  S_CCTransitionMoveInB::jsCreateClass(this->cx, cocos, "TransitionMoveInB");
  S_CCTransitionSlideInL::jsCreateClass(this->cx, cocos, "TransitionSlideInL");
  S_CCTransitionSlideInR::jsCreateClass(this->cx, cocos, "TransitionSlideInR");
  S_CCTransitionSlideInB::jsCreateClass(this->cx, cocos, "TransitionSlideInB");
  S_CCTransitionSlideInT::jsCreateClass(this->cx, cocos, "TransitionSlideInT");
  S_CCTransitionShrinkGrow::jsCreateClass(this->cx, cocos, "TransitionShrinkGrow");
  S_CCTransitionFlipX::jsCreateClass(this->cx, cocos, "TransitionFlipX");
  S_CCTransitionFlipY::jsCreateClass(this->cx, cocos, "TransitionFlipY");
  S_CCTransitionFlipAngular::jsCreateClass(this->cx, cocos, "TransitionFlipAngular");
  S_CCTransitionZoomFlipX::jsCreateClass(this->cx, cocos, "TransitionZoomFlipX");
  S_CCTransitionZoomFlipY::jsCreateClass(this->cx, cocos, "TransitionZoomFlipY");
  S_CCTransitionZoomFlipAngular::jsCreateClass(this->cx, cocos, "TransitionZoomFlipAngular");
  S_CCTransitionFade::jsCreateClass(this->cx, cocos, "TransitionFade");
  S_CCTransitionCrossFade::jsCreateClass(this->cx, cocos, "TransitionCrossFade");
  S_CCTransitionTurnOffTiles::jsCreateClass(this->cx, cocos, "TransitionTurnOffTiles");
  S_CCTransitionSplitCols::jsCreateClass(this->cx, cocos, "TransitionSplitCols");
  S_CCTransitionSplitRows::jsCreateClass(this->cx, cocos, "TransitionSplitRows");
  S_CCTransitionFadeTR::jsCreateClass(this->cx, cocos, "TransitionFadeTR");
  S_CCTransitionFadeBL::jsCreateClass(this->cx, cocos, "TransitionFadeBL");
  S_CCTransitionFadeUp::jsCreateClass(this->cx, cocos, "TransitionFadeUp");
  S_CCFadeOutBLTiles::jsCreateClass(this->cx, cocos, "FadeOutBLTiles");
  S_CCProgressFromTo::jsCreateClass(this->cx, cocos, "ProgressFromTo");
  S_CCFadeOutUpTiles::jsCreateClass(this->cx, cocos, "FadeOutUpTiles");
  S_CCAnimationCache::jsCreateClass(this->cx, cocos, "AnimationCache");
  S_CCPlace::jsCreateClass(this->cx, cocos, "Place");
  S_CCLabelBMFont::jsCreateClass(this->cx, cocos, "LabelBMFont");
  S_CCReverseTime::jsCreateClass(this->cx, cocos, "ReverseTime");
  S_CCFadeOutTRTiles::jsCreateClass(this->cx, cocos, "FadeOutTRTiles");
  S_CCCamera::jsCreateClass(this->cx, cocos, "Camera");
  S_CCProgressTo::jsCreateClass(this->cx, cocos, "ProgressTo");
  S_CCWavesTiles3D::jsCreateClass(this->cx, cocos, "WavesTiles3D");
  S_CCMotionStreak::jsCreateClass(this->cx, cocos, "MotionStreak");
  S_CCTransitionProgressRadialCCW::jsCreateClass(this->cx, cocos, "TransitionRadialProgressCCW");
  S_CCFadeOutDownTiles::jsCreateClass(this->cx, cocos, "FadeOutDownTiles");
  S_CCTurnOffTiles::jsCreateClass(this->cx, cocos, "TurnOffTiles");
  S_CCDeccelAmplitude::jsCreateClass(this->cx, cocos, "DeccelAmplitude");
  S_CCProgressTimer::jsCreateClass(this->cx, cocos, "ProgressTimer");
  S_CCReuseGrid::jsCreateClass(this->cx, cocos, "ReuseGrid");
  S_CCStopGrid::jsCreateClass(this->cx, cocos, "StopGrid");
  S_CCTwirl::jsCreateClass(this->cx, cocos, "Twirl");
  S_CCShakyTiles3D::jsCreateClass(this->cx, cocos, "ShakyTiles3D");
  S_CCTransitionProgressRadialCW::jsCreateClass(this->cx, cocos, "TransitionProgressRadialCW");
  S_CCAtlasNode::jsCreateClass(this->cx, cocos, "AtlasNode");
  S_CCWaves::jsCreateClass(this->cx, cocos, "Waves");
  S_CCShow::jsCreateClass(this->cx, cocos, "Show");
  S_CCOrbitCamera::jsCreateClass(this->cx, cocos, "OrbitCamera");
  S_CCShatteredTiles3D::jsCreateClass(this->cx, cocos, "ShatteredTiles3D");
  S_CCHide::jsCreateClass(this->cx, cocos, "Hide");
  S_CCToggleVisibility::jsCreateClass(this->cx, cocos, "ToggleVisibility");
  S_CCActionCamera::jsCreateClass(this->cx, cocos, "ActionCamera");
  S_CCShuffleTiles::jsCreateClass(this->cx, cocos, "ShuffleTiles");
  S_CCLayerGradient::jsCreateClass(this->cx, cocos, "LayerGradient");
  S_CCFlipX::jsCreateClass(this->cx, cocos, "FlipX");
  S_CCRepeat::jsCreateClass(this->cx, cocos, "Repeat");
  S_CCFlipY::jsCreateClass(this->cx, cocos, "FlipY");
  S_CCBezierBy::jsCreateClass(this->cx, cocos, "BezierBy");
  S_CCPageTurn3D::jsCreateClass(this->cx, cocos, "PageTurn3D");
  S_CCLens3D::jsCreateClass(this->cx, cocos, "Lens3D");
  S_CCRipple3D::jsCreateClass(this->cx, cocos, "Ripple3D");
  S_CCApplication::jsCreateClass(this->cx, cocos, "Application");
  S_CCFlipX3D::jsCreateClass(this->cx, cocos, "FlipX3D");
  S_CCJumpTo::jsCreateClass(this->cx, cocos, "JumpTo");
  S_CCTransitionPageTurn::jsCreateClass(this->cx, cocos, "TransitionPageTurn");
  S_CCFlipY3D::jsCreateClass(this->cx, cocos, "FlipY3D");
  S_CCLiquid::jsCreateClass(this->cx, cocos, "Liquid");
  S_CCTiledGrid3DAction::jsCreateClass(this->cx, cocos, "TiledGrid3DAction");
  S_CCJumpBy::jsCreateClass(this->cx, cocos, "JumpBy");
  S_CCFollow::jsCreateClass(this->cx, cocos, "Follow");
  S_CCSkewBy::jsCreateClass(this->cx, cocos, "SkewBy");
  S_CCAccelDeccelAmplitude::jsCreateClass(this->cx, cocos, "AccelDeccelAmplitude");
  S_CCLabelAtlas::jsCreateClass(this->cx, cocos, "LabelAtlas");
  S_CCAccelAmplitude::jsCreateClass(this->cx, cocos, "AccelAmplitude");
  S_CCSkewTo::jsCreateClass(this->cx, cocos, "SkewTo");
  S_CCShaky3D::jsCreateClass(this->cx, cocos, "Shaky3D");
  S_CCSplitCols::jsCreateClass(this->cx, cocos, "SplitCols");
  S_CCFadeOut::jsCreateClass(this->cx, cocos, "FadeOut");
  S_CCTileMapAtlas::jsCreateClass(this->cx, cocos, "TileMapAtlas");
  S_CCFadeTo::jsCreateClass(this->cx, cocos, "FadeTo");
  S_CCJumpTiles3D::jsCreateClass(this->cx, cocos, "JumpTiles3D");
  S_CCFadeIn::jsCreateClass(this->cx, cocos, "FadeIn");
  S_CCSplitRows::jsCreateClass(this->cx, cocos, "SplitRows");
  S_CCScaleBy::jsCreateClass(this->cx, cocos, "ScaleBy");
  S_CCScaleTo::jsCreateClass(this->cx, cocos, "ScaleTo");
  S_CCBezierTo::jsCreateClass(this->cx, cocos, "BezierTo");
  S_CCTMXTiledMap::jsCreateClass(this->cx, cocos, "TMXTiledMap");
  S_CCTMXLayer::jsCreateClass(this->cx, cocos, "TMXLayer");

  S_SimpleAudioEngine::jsCreateClass(this->cx, cocos, "SimpleAudioEngine");

  // register some global functions
  JS_DefineFunction(this->cx, global, "require", ScriptingCore::executeScript, 0, JSPROP_READONLY | JSPROP_PERMANENT);
  JS_DefineFunction(this->cx, cocos, "log", ScriptingCore::log, 0, JSPROP_READONLY | JSPROP_PERMANENT);
  JS_DefineFunction(this->cx, cocos, "executeScript", ScriptingCore::executeScript, 1, JSPROP_READONLY | JSPROP_PERMANENT);
  JS_DefineFunction(this->cx, cocos, "addGCRootObject", ScriptingCore::addRootJS, 1, JSPROP_READONLY | JSPROP_PERMANENT);
  JS_DefineFunction(this->cx, cocos, "removeGCRootObject", ScriptingCore::removeRootJS, 1, JSPROP_READONLY | JSPROP_PERMANENT);
  JS_DefineFunction(this->cx, cocos, "forceGC", ScriptingCore::forceGC, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    
  // register chipmunk functions
  JSObject *chipmunk = JS_NewObject(this->cx, NULL, NULL, NULL);
  jsval chipmunkVal = OBJECT_TO_JSVAL(chipmunk);
  JS_SetProperty(this->cx, global, "cp", &chipmunkVal);

  JS_DefineFunction(this->cx, chipmunk, "arbiterGetCount", JSPROXY_cpArbiterGetCount, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "arbiterGetDepth", JSPROXY_cpArbiterGetDepth, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "arbiterGetElasticity", JSPROXY_cpArbiterGetElasticity, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "arbiterGetFriction", JSPROXY_cpArbiterGetFriction, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "arbiterGetNormal", JSPROXY_cpArbiterGetNormal, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "arbiterGetPoint", JSPROXY_cpArbiterGetPoint, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "arbiterGetSurfaceVelocity", JSPROXY_cpArbiterGetSurfaceVelocity, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "arbiterIgnore", JSPROXY_cpArbiterIgnore, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "arbiterIsFirstContact", JSPROXY_cpArbiterIsFirstContact, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "arbiterSetElasticity", JSPROXY_cpArbiterSetElasticity, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "arbiterSetFriction", JSPROXY_cpArbiterSetFriction, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "arbiterSetSurfaceVelocity", JSPROXY_cpArbiterSetSurfaceVelocity, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "arbiterTotalImpulse", JSPROXY_cpArbiterTotalImpulse, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "arbiterTotalImpulseWithFriction", JSPROXY_cpArbiterTotalImpulseWithFriction, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "arbiterTotalKE", JSPROXY_cpArbiterTotalKE, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "areaForCircle", JSPROXY_cpAreaForCircle, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "areaForSegment", JSPROXY_cpAreaForSegment, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bBArea", JSPROXY_cpBBArea, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bBClampVect", JSPROXY_cpBBClampVect, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bBContainsBB", JSPROXY_cpBBContainsBB, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bBContainsVect", JSPROXY_cpBBContainsVect, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bBExpand", JSPROXY_cpBBExpand, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bBIntersects", JSPROXY_cpBBIntersects, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bBIntersectsSegment", JSPROXY_cpBBIntersectsSegment, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bBMerge", JSPROXY_cpBBMerge, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bBMergedArea", JSPROXY_cpBBMergedArea, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bBNew", JSPROXY_cpBBNew, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bBNewForCircle", JSPROXY_cpBBNewForCircle, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bBSegmentQuery", JSPROXY_cpBBSegmentQuery, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bBWrapVect", JSPROXY_cpBBWrapVect, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodyActivate", JSPROXY_cpBodyActivate, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodyActivateStatic", JSPROXY_cpBodyActivateStatic, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodyAlloc", JSPROXY_cpBodyAlloc, 0, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodyApplyForce", JSPROXY_cpBodyApplyForce, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodyApplyImpulse", JSPROXY_cpBodyApplyImpulse, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodyDestroy", JSPROXY_cpBodyDestroy, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodyFree", JSPROXY_cpBodyFree, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodyGetAngVel", JSPROXY_cpBodyGetAngVel, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodyGetAngVelLimit", JSPROXY_cpBodyGetAngVelLimit, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodyGetAngle", JSPROXY_cpBodyGetAngle, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodyGetForce", JSPROXY_cpBodyGetForce, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodyGetMass", JSPROXY_cpBodyGetMass, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodyGetMoment", JSPROXY_cpBodyGetMoment, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodyGetPos", JSPROXY_cpBodyGetPos, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodyGetRot", JSPROXY_cpBodyGetRot, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodyGetSpace", JSPROXY_cpBodyGetSpace, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodyGetTorque", JSPROXY_cpBodyGetTorque, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodyGetVel", JSPROXY_cpBodyGetVel, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodyGetVelAtLocalPoint", JSPROXY_cpBodyGetVelAtLocalPoint, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodyGetVelAtWorldPoint", JSPROXY_cpBodyGetVelAtWorldPoint, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodyGetVelLimit", JSPROXY_cpBodyGetVelLimit, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodyInit", JSPROXY_cpBodyInit, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodyInitStatic", JSPROXY_cpBodyInitStatic, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodyIsRogue", JSPROXY_cpBodyIsRogue, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodyIsSleeping", JSPROXY_cpBodyIsSleeping, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodyIsStatic", JSPROXY_cpBodyIsStatic, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodyKineticEnergy", JSPROXY_cpBodyKineticEnergy, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodyLocal2World", JSPROXY_cpBodyLocal2World, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodyNew", JSPROXY_cpBodyNew, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodyNewStatic", JSPROXY_cpBodyNewStatic, 0, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodyResetForces", JSPROXY_cpBodyResetForces, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodySetAngVel", JSPROXY_cpBodySetAngVel, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodySetAngVelLimit", JSPROXY_cpBodySetAngVelLimit, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodySetAngle", JSPROXY_cpBodySetAngle, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodySetForce", JSPROXY_cpBodySetForce, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodySetMass", JSPROXY_cpBodySetMass, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodySetMoment", JSPROXY_cpBodySetMoment, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodySetPos", JSPROXY_cpBodySetPos, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodySetTorque", JSPROXY_cpBodySetTorque, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodySetVel", JSPROXY_cpBodySetVel, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodySetVelLimit", JSPROXY_cpBodySetVelLimit, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodySleep", JSPROXY_cpBodySleep, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodySleepWithGroup", JSPROXY_cpBodySleepWithGroup, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodyUpdatePosition", JSPROXY_cpBodyUpdatePosition, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodyUpdateVelocity", JSPROXY_cpBodyUpdateVelocity, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "bodyWorld2Local", JSPROXY_cpBodyWorld2Local, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "boxShapeNew", JSPROXY_cpBoxShapeNew, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "boxShapeNew2", JSPROXY_cpBoxShapeNew2, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "circleShapeGetOffset", JSPROXY_cpCircleShapeGetOffset, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "circleShapeGetRadius", JSPROXY_cpCircleShapeGetRadius, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "circleShapeNew", JSPROXY_cpCircleShapeNew, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "constraintActivateBodies", JSPROXY_cpConstraintActivateBodies, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "constraintDestroy", JSPROXY_cpConstraintDestroy, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "constraintFree", JSPROXY_cpConstraintFree, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "constraintGetA", JSPROXY_cpConstraintGetA, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "constraintGetB", JSPROXY_cpConstraintGetB, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "constraintGetErrorBias", JSPROXY_cpConstraintGetErrorBias, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "constraintGetImpulse", JSPROXY_cpConstraintGetImpulse, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "constraintGetMaxBias", JSPROXY_cpConstraintGetMaxBias, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "constraintGetMaxForce", JSPROXY_cpConstraintGetMaxForce, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "constraintGetSpace", JSPROXY_cpConstraintGetSpace, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "constraintSetErrorBias", JSPROXY_cpConstraintSetErrorBias, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "constraintSetMaxBias", JSPROXY_cpConstraintSetMaxBias, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "constraintSetMaxForce", JSPROXY_cpConstraintSetMaxForce, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "dampedRotarySpringGetDamping", JSPROXY_cpDampedRotarySpringGetDamping, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "dampedRotarySpringGetRestAngle", JSPROXY_cpDampedRotarySpringGetRestAngle, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "dampedRotarySpringGetStiffness", JSPROXY_cpDampedRotarySpringGetStiffness, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "dampedRotarySpringNew", JSPROXY_cpDampedRotarySpringNew, 5, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "dampedRotarySpringSetDamping", JSPROXY_cpDampedRotarySpringSetDamping, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "dampedRotarySpringSetRestAngle", JSPROXY_cpDampedRotarySpringSetRestAngle, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "dampedRotarySpringSetStiffness", JSPROXY_cpDampedRotarySpringSetStiffness, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "dampedSpringGetAnchr1", JSPROXY_cpDampedSpringGetAnchr1, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "dampedSpringGetAnchr2", JSPROXY_cpDampedSpringGetAnchr2, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "dampedSpringGetDamping", JSPROXY_cpDampedSpringGetDamping, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "dampedSpringGetRestLength", JSPROXY_cpDampedSpringGetRestLength, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "dampedSpringGetStiffness", JSPROXY_cpDampedSpringGetStiffness, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "dampedSpringNew", JSPROXY_cpDampedSpringNew, 7, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "dampedSpringSetAnchr1", JSPROXY_cpDampedSpringSetAnchr1, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "dampedSpringSetAnchr2", JSPROXY_cpDampedSpringSetAnchr2, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "dampedSpringSetDamping", JSPROXY_cpDampedSpringSetDamping, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "dampedSpringSetRestLength", JSPROXY_cpDampedSpringSetRestLength, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "dampedSpringSetStiffness", JSPROXY_cpDampedSpringSetStiffness, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "gearJointGetPhase", JSPROXY_cpGearJointGetPhase, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "gearJointGetRatio", JSPROXY_cpGearJointGetRatio, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "gearJointNew", JSPROXY_cpGearJointNew, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "gearJointSetPhase", JSPROXY_cpGearJointSetPhase, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "gearJointSetRatio", JSPROXY_cpGearJointSetRatio, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "grooveJointGetAnchr2", JSPROXY_cpGrooveJointGetAnchr2, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "grooveJointGetGrooveA", JSPROXY_cpGrooveJointGetGrooveA, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "grooveJointGetGrooveB", JSPROXY_cpGrooveJointGetGrooveB, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "grooveJointNew", JSPROXY_cpGrooveJointNew, 5, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "grooveJointSetAnchr2", JSPROXY_cpGrooveJointSetAnchr2, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "grooveJointSetGrooveA", JSPROXY_cpGrooveJointSetGrooveA, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "grooveJointSetGrooveB", JSPROXY_cpGrooveJointSetGrooveB, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "initChipmunk", JSPROXY_cpInitChipmunk, 0, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "momentForBox", JSPROXY_cpMomentForBox, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "momentForBox2", JSPROXY_cpMomentForBox2, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "momentForCircle", JSPROXY_cpMomentForCircle, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "momentForSegment", JSPROXY_cpMomentForSegment, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "pinJointGetAnchr1", JSPROXY_cpPinJointGetAnchr1, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "pinJointGetAnchr2", JSPROXY_cpPinJointGetAnchr2, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "pinJointGetDist", JSPROXY_cpPinJointGetDist, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "pinJointNew", JSPROXY_cpPinJointNew, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "pinJointSetAnchr1", JSPROXY_cpPinJointSetAnchr1, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "pinJointSetAnchr2", JSPROXY_cpPinJointSetAnchr2, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "pinJointSetDist", JSPROXY_cpPinJointSetDist, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "pivotJointGetAnchr1", JSPROXY_cpPivotJointGetAnchr1, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "pivotJointGetAnchr2", JSPROXY_cpPivotJointGetAnchr2, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "pivotJointNew", JSPROXY_cpPivotJointNew, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "pivotJointNew2", JSPROXY_cpPivotJointNew2, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "pivotJointSetAnchr1", JSPROXY_cpPivotJointSetAnchr1, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "pivotJointSetAnchr2", JSPROXY_cpPivotJointSetAnchr2, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "polyShapeGetNumVerts", JSPROXY_cpPolyShapeGetNumVerts, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "polyShapeGetVert", JSPROXY_cpPolyShapeGetVert, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "ratchetJointGetAngle", JSPROXY_cpRatchetJointGetAngle, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "ratchetJointGetPhase", JSPROXY_cpRatchetJointGetPhase, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "ratchetJointGetRatchet", JSPROXY_cpRatchetJointGetRatchet, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "ratchetJointNew", JSPROXY_cpRatchetJointNew, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "ratchetJointSetAngle", JSPROXY_cpRatchetJointSetAngle, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "ratchetJointSetPhase", JSPROXY_cpRatchetJointSetPhase, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "ratchetJointSetRatchet", JSPROXY_cpRatchetJointSetRatchet, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "resetShapeIdCounter", JSPROXY_cpResetShapeIdCounter, 0, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "rotaryLimitJointGetMax", JSPROXY_cpRotaryLimitJointGetMax, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "rotaryLimitJointGetMin", JSPROXY_cpRotaryLimitJointGetMin, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "rotaryLimitJointNew", JSPROXY_cpRotaryLimitJointNew, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "rotaryLimitJointSetMax", JSPROXY_cpRotaryLimitJointSetMax, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "rotaryLimitJointSetMin", JSPROXY_cpRotaryLimitJointSetMin, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "segmentShapeGetA", JSPROXY_cpSegmentShapeGetA, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "segmentShapeGetB", JSPROXY_cpSegmentShapeGetB, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "segmentShapeGetNormal", JSPROXY_cpSegmentShapeGetNormal, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "segmentShapeGetRadius", JSPROXY_cpSegmentShapeGetRadius, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "segmentShapeNew", JSPROXY_cpSegmentShapeNew, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "segmentShapeSetNeighbors", JSPROXY_cpSegmentShapeSetNeighbors, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "shapeCacheBB", JSPROXY_cpShapeCacheBB, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "shapeDestroy", JSPROXY_cpShapeDestroy, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "shapeFree", JSPROXY_cpShapeFree, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "shapeGetBB", JSPROXY_cpShapeGetBB, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "shapeGetBody", JSPROXY_cpShapeGetBody, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "shapeGetCollisionType", JSPROXY_cpShapeGetCollisionType, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "shapeGetElasticity", JSPROXY_cpShapeGetElasticity, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "shapeGetFriction", JSPROXY_cpShapeGetFriction, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "shapeGetGroup", JSPROXY_cpShapeGetGroup, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "shapeGetLayers", JSPROXY_cpShapeGetLayers, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "shapeGetSensor", JSPROXY_cpShapeGetSensor, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "shapeGetSpace", JSPROXY_cpShapeGetSpace, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "shapeGetSurfaceVelocity", JSPROXY_cpShapeGetSurfaceVelocity, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "shapePointQuery", JSPROXY_cpShapePointQuery, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "shapeSetBody", JSPROXY_cpShapeSetBody, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "shapeSetCollisionType", JSPROXY_cpShapeSetCollisionType, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "shapeSetElasticity", JSPROXY_cpShapeSetElasticity, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "shapeSetFriction", JSPROXY_cpShapeSetFriction, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "shapeSetGroup", JSPROXY_cpShapeSetGroup, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "shapeSetLayers", JSPROXY_cpShapeSetLayers, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "shapeSetSensor", JSPROXY_cpShapeSetSensor, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "shapeSetSurfaceVelocity", JSPROXY_cpShapeSetSurfaceVelocity, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "shapeUpdate", JSPROXY_cpShapeUpdate, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "simpleMotorGetRate", JSPROXY_cpSimpleMotorGetRate, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "simpleMotorNew", JSPROXY_cpSimpleMotorNew, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "simpleMotorSetRate", JSPROXY_cpSimpleMotorSetRate, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "slideJointGetAnchr1", JSPROXY_cpSlideJointGetAnchr1, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "slideJointGetAnchr2", JSPROXY_cpSlideJointGetAnchr2, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "slideJointGetMax", JSPROXY_cpSlideJointGetMax, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "slideJointGetMin", JSPROXY_cpSlideJointGetMin, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "slideJointNew", JSPROXY_cpSlideJointNew, 6, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "slideJointSetAnchr1", JSPROXY_cpSlideJointSetAnchr1, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "slideJointSetAnchr2", JSPROXY_cpSlideJointSetAnchr2, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "slideJointSetMax", JSPROXY_cpSlideJointSetMax, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "slideJointSetMin", JSPROXY_cpSlideJointSetMin, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceActivateShapesTouchingShape", JSPROXY_cpSpaceActivateShapesTouchingShape, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceAddBody", JSPROXY_cpSpaceAddBody, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceAddConstraint", JSPROXY_cpSpaceAddConstraint, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceAddShape", JSPROXY_cpSpaceAddShape, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceAddStaticShape", JSPROXY_cpSpaceAddStaticShape, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceAlloc", JSPROXY_cpSpaceAlloc, 0, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceContainsBody", JSPROXY_cpSpaceContainsBody, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceContainsConstraint", JSPROXY_cpSpaceContainsConstraint, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceContainsShape", JSPROXY_cpSpaceContainsShape, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceDestroy", JSPROXY_cpSpaceDestroy, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceFree", JSPROXY_cpSpaceFree, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceGetCollisionBias", JSPROXY_cpSpaceGetCollisionBias, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceGetCollisionPersistence", JSPROXY_cpSpaceGetCollisionPersistence, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceGetCollisionSlop", JSPROXY_cpSpaceGetCollisionSlop, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceGetCurrentTimeStep", JSPROXY_cpSpaceGetCurrentTimeStep, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceGetDamping", JSPROXY_cpSpaceGetDamping, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceGetEnableContactGraph", JSPROXY_cpSpaceGetEnableContactGraph, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceGetGravity", JSPROXY_cpSpaceGetGravity, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceGetIdleSpeedThreshold", JSPROXY_cpSpaceGetIdleSpeedThreshold, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceGetIterations", JSPROXY_cpSpaceGetIterations, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceGetSleepTimeThreshold", JSPROXY_cpSpaceGetSleepTimeThreshold, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceGetStaticBody", JSPROXY_cpSpaceGetStaticBody, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceInit", JSPROXY_cpSpaceInit, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceIsLocked", JSPROXY_cpSpaceIsLocked, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceNew", JSPROXY_cpSpaceNew, 0, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spacePointQueryFirst", JSPROXY_cpSpacePointQueryFirst, 4, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceReindexShape", JSPROXY_cpSpaceReindexShape, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceReindexShapesForBody", JSPROXY_cpSpaceReindexShapesForBody, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceReindexStatic", JSPROXY_cpSpaceReindexStatic, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceRemoveBody", JSPROXY_cpSpaceRemoveBody, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceRemoveConstraint", JSPROXY_cpSpaceRemoveConstraint, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceRemoveShape", JSPROXY_cpSpaceRemoveShape, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceRemoveStaticShape", JSPROXY_cpSpaceRemoveStaticShape, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceSetCollisionBias", JSPROXY_cpSpaceSetCollisionBias, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceSetCollisionPersistence", JSPROXY_cpSpaceSetCollisionPersistence, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceSetCollisionSlop", JSPROXY_cpSpaceSetCollisionSlop, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceSetDamping", JSPROXY_cpSpaceSetDamping, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceSetEnableContactGraph", JSPROXY_cpSpaceSetEnableContactGraph, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceSetGravity", JSPROXY_cpSpaceSetGravity, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceSetIdleSpeedThreshold", JSPROXY_cpSpaceSetIdleSpeedThreshold, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceSetIterations", JSPROXY_cpSpaceSetIterations, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceSetSleepTimeThreshold", JSPROXY_cpSpaceSetSleepTimeThreshold, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceStep", JSPROXY_cpSpaceStep, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceUseSpatialHash", JSPROXY_cpSpaceUseSpatialHash, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "fabs", JSPROXY_cpfabs, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "fclamp", JSPROXY_cpfclamp, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "fclamp01", JSPROXY_cpfclamp01, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "flerp", JSPROXY_cpflerp, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "flerpconst", JSPROXY_cpflerpconst, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "fmax", JSPROXY_cpfmax, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "fmin", JSPROXY_cpfmin, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "v", JSPROXY_cpv, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "vadd", JSPROXY_cpvadd, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "vclamp", JSPROXY_cpvclamp, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "vcross", JSPROXY_cpvcross, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "vdist", JSPROXY_cpvdist, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "vdistsq", JSPROXY_cpvdistsq, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "vdot", JSPROXY_cpvdot, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "veql", JSPROXY_cpveql, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "vforangle", JSPROXY_cpvforangle, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "vlength", JSPROXY_cpvlength, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "vlengthsq", JSPROXY_cpvlengthsq, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "vlerp", JSPROXY_cpvlerp, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "vlerpconst", JSPROXY_cpvlerpconst, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "vmult", JSPROXY_cpvmult, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "vnear", JSPROXY_cpvnear, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "vneg", JSPROXY_cpvneg, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "vnormalize", JSPROXY_cpvnormalize, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "vnormalize_safe", JSPROXY_cpvnormalize_safe, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "vperp", JSPROXY_cpvperp, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "vproject", JSPROXY_cpvproject, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "vrotate", JSPROXY_cpvrotate, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "vrperp", JSPROXY_cpvrperp, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "vslerp", JSPROXY_cpvslerp, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "vslerpconst", JSPROXY_cpvslerpconst, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "vsub", JSPROXY_cpvsub, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "vtoangle", JSPROXY_cpvtoangle, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "vunrotate", JSPROXY_cpvunrotate, 2, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  
  // manual
  JS_DefineFunction(this->cx, chipmunk, "spaceAddCollisionHandler", JSPROXY_cpSpaceAddCollisionHandler, 8, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "spaceRemoveCollisionHandler", JSPROXY_cpSpaceRemoveCollisionHandler, 8, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "arbiterGetBodies", JSPROXY_cpArbiterGetBodies, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
  JS_DefineFunction(this->cx, chipmunk, "arbiterGetShapes", JSPROXY_cpArbiterGetShapes, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
}


bool ScriptingCore::evalString(const char *string, jsval *outVal)
{
  jsval rval;
  JSString *str;
  JSBool ok;
  const char *filename = "noname";
  uint32_t lineno = 0;
  if (outVal == NULL) {
    outVal = &rval;
  }
  ok = JS_EvaluateScript(cx, global, string, strlen(string), filename, lineno, outVal);
  if (ok == JS_FALSE) {
    CCLog("error evaluating script:\n%s", string);
  }
  str = JS_ValueToString(cx, rval);
  return ok;
}

void ScriptingCore::runScript(const char *path)
{
#ifdef DEBUG
  /**
   * dpath should point to the parent directory of the "JS" folder. If this is
   * set to "" (as it is now) then it will take the scripts from the app bundle.
   * By setting the absolute path you can iterate the development only by
   * modifying those scripts and reloading from the simulator (no recompiling/
   * relaunching)
   */
  //    std::string dpath("/Users/rabarca/Desktop/testjs/testjs/");
  std::string dpath("");
  dpath += path;
  const char *realPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(dpath.c_str());
#else
  const char *realPath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(path);
#endif
  const char* content = CCString::createWithContentsOfFile(realPath)->getCString();
  if (content && strlen(content) > 0) {
    JSBool ok;
    jsval rval;
    ok = JS_EvaluateScript(this->cx, this->global, (char *)content, strlen(content), path, 1, &rval);
    if (ok == JS_FALSE) {
      CCLog("error evaluating script:\n%s", content);
    }
  }
}

ScriptingCore::~ScriptingCore()
{
  JS_DestroyContext(cx);
  JS_DestroyRuntime(rt);
  JS_ShutDown();
}
