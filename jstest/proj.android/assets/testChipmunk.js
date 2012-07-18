try {//
// http://www.cocos2d-iphone.org
//
// Javascript + chipmunk tests
//


var cc = cc || {}
    cc.p = function(x, y)
{
    var floats = new Float32Array(2);
    floats[0] = x;
    floats[1] = y;

    return floats;
}

	cc.rect = function(x,y,w,h)
{
    var rect =  new Float32Array(4)
    rect[0] = x;
    rect[1] = y;
    rect[2] = w;
    rect[3] = h;
    return rect;
};

cc.size = function(w,h)
{
    var size = new Float32Array(2)
    size[0] = w;
    size[1] = h;
    return size;
};

cc.size_get_width = function (size )
{
    return size[0];
};

cc.size_get_height = function (size )
{
    return size[1];
};

try {
    var director = cc.Director.sharedDirector();
    cc.log("director: "+JSON.stringify(director));
    cc.log(director.winSize);
    var _winSize = director.winSize;
    cc.log(_winSize.width+"  "+_winSize.height);

    var winSize = {width: _winSize.width, height: _winSize.height};
    var centerPos = cc.p(winSize.width/2, winSize.height/2);

    var scenes = [];
    var currentScene = 0;

    var nextSpriteTestAction = function () {
	currentScene = currentScene + 1;
	if( currentScene >= scenes.length )
	    currentScene = 0;

	loadScene(currentScene);
    };

    var backSpriteTestAction = function () {
	currentScene = currentScene -1;
	if( currentScene < 0 )
	    currentScene = scenes.length -1;

	loadScene(currentScene);
    };

    var restartSpriteTestAction = function () {
	loadScene( currentScene );
    };

    var loadScene = function (sceneIdx)
	{
	    _winSize = director.winSiz;
	    winSize = {width:_winSize.width, height:_winSize.height};
	    centerPos = cc.p( winSize.width/2, winSize.height/2 );

	    var scene = new cc.Scene();
	    scene.init();
	    var layer = scenes[ sceneIdx ]();

	    scene.addChild( layer );

	    //scene.walkSceneGraph(0);

	    director.replaceScene( scene );
	    //    __jsc__.garbageCollect();
	};


    // ------------------------------------------------------------------

    // BaseLayer

    // ------------------------------------------------------------------

//     var BaseLayer = function() {
    
// 	//
// 	// VERY IMPORTANT
// 	//
// 	// Only subclasses of a native classes MUST call __associateObjectWithNative
// 	// Failure to do so, it will crash.
// 	//

// 	cc.log("entered base layer");
// 	//var parent = goog.base(this);
// 	cc.log("parent: "+parent+"  "+this.init);
// 	//__associateObjWithNative( this, parent );
// 	this.init();
// 	cc.log("inited base");
// 	this.title = function () {
// 	    return "No title";
// 	}
    
// 	this.subtitle = function () {
// 	    return "No Subtitle";
// 	}
    
//     };

//     goog.inherits(BaseLayer, cc.Layer);


    var Base = function() {

	var layer = new cc.Layer();
	layer.init();

 	layer.title = function () {
 	    return "No title";
 	};
    
 	layer.subtitle = function () {
 	    return "No Subtitle";
 	};


	layer.initialize = function() {

// 	    var label = cc.LabelTTF.create(layer.title(), "Arial", 28);
// 	    layer.addChild(label, 1);
// 	    label.setPosition( cc.p(winSize.width / 2, winSize.height - 50));
	    
// 	    var strSubtitle = layer.subtitle();
// 	    if (strSubtitle != "") {
// 		var l = cc.LabelTTF.create(strSubtitle, "Thonburi", 16);
// 		layer.addChild(l, 1);
// 		l.setPosition( cc.p(winSize.width / 2, winSize.height - 80));
// 	    }
	    
	    // Menu
	    try {

		var item1 = cc.MenuItemImage.itemWithNormalImage("b1.png", "b2.png", layer, layer.backCallback);
		var item2 = cc.MenuItemImage.create("r1.png", "r2.png", layer, layer.restartCallback);
		var item3 = cc.MenuItemImage.create("f1.png", "f2.png", layer, layer.nextCallback);
		var item4 = cc.MenuItemFont.create("back", layer, function() { require("javascript-spidermonkey/main.js"); } );
		item4.setFontSize( 22 );
		
		cc.log(item1+"  "+item2+"  "+item3+"  "+item4);
		
		var menu = cc.Menu.create(item1, item2, item3, item4 );
		
		menu.setPosition( cc.p(0,0) );
		item1.setPosition( cc.p(winSize.width / 2 - 100, 30));
		item2.setPosition( cc.p(winSize.width / 2, 30));
		item3.setPosition( cc.p(winSize.width / 2 + 100, 30));
		item4.setPosition( cc.p(winSize.width - 60, winSize.height - 30 ) );
		
		cc.log(menu);

		layer.addChild(menu);
	    } catch(e) {cc.log(e);}
	};
    
	layer.restartCallback = function (sender) {
	    cc.log("restart called");
	    restartSpriteTestAction();
	};
	
	layer.nextCallback = function (sender) {
	    cc.log("next called");
	    nextSpriteTestAction();
	};
	
	layer.backCallback = function (sender) {
	    cc.log("back called");
	    backSpriteTestAction();
	};
	
	
	return layer;
    }




    //
    // Instance 'base' methods
    // XXX: Should be defined after "goog.inherits"
//     //
//     BaseLayer.prototype.onEnter = function() {
// 	var label = cc.LabelTTF.create(this.title(), "Arial", 28);
// 	this.addChild(label, 1);
// 	label.setPosition( cc.p(winSize.width / 2, winSize.height - 50));

// 	var strSubtitle = this.subtitle();
// 	if (strSubtitle != "") {
// 	    var l = cc.LabelTTF.create(strSubtitle, "Thonburi", 16);
// 	    this.addChild(l, 1);
// 	    l.setPosition( cc.p(winSize.width / 2, winSize.height - 80));
// 	}

// 	// Menu
// 	var item1 = cc.MenuItemImage.create("b1.png", "b2.png", this, this.backCallback);
// 	var item2 = cc.MenuItemImage.create("r1.png", "r2.png", this, this.restartCallback);
// 	var item3 = cc.MenuItemImage.create("f1.png", "f2.png", this, this.nextCallback);
// 	var item4 = cc.MenuItemFont.create("back", this, function() { require("javascript-spidermonkey/main.js"); } );
// 	item4.setFontSize( 22 );

// 	var menu = cc.Menu.create(item1, item2, item3, item4 );

// 	menu.setPosition( cc.p(0,0) );
// 	item1.setPosition( cc.p(winSize.width / 2 - 100, 30));
// 	item2.setPosition( cc.p(winSize.width / 2, 30));
// 	item3.setPosition( cc.p(winSize.width / 2 + 100, 30));
// 	item4.setPosition( cc.p(winSize.width - 60, winSize.height - 30 ) );

// 	this.addChild(menu, 1);
//     };

//     BaseLayer.prototype.restartCallback = function (sender) {
// 	cc.log("restart called");
// 	restartSpriteTestAction();
//     };

//     BaseLayer.prototype.nextCallback = function (sender) {
// 	cc.log("next called");
// 	nextSpriteTestAction();
//     };

//     BaseLayer.prototype.backCallback = function (sender) {
// 	cc.log("back called");
// 	backSpriteTestAction();
//     };


    //------------------------------------------------------------------
    //
    // Chipmunk + Sprite
    //
    //------------------------------------------------------------------
    var ChipmunkSpriteTest = function() {

	cc.log("entering new chipmst");
	//goog.base(this);
	
	cc.log("creating");

	this.addSprite = function( pos ) {
	    try {
		var sprite =  this.createPhysicsSprite( pos );
	    } catch(e) {cc.log(e);}
	    // this.addChild( sprite );
	}

	this.title = function() {
	    return 'Chipmunk Sprite Test';
	}

	this.subtitle = function() {
	    return 'Chipmunk + cocos2d sprites tests. Tap screen.';
	}
	try {
	    this.initPhysics();

	    this.onEnter();
	    for(var i = 0; i < 1; i+=1/60) {
		this.update(1/60);
	    }
	} catch(e) {cc.log(e);}
    };

    //goog.inherits( ChipmunkSpriteTest, BaseLayer );

//
// Instance 'base' methods
// XXX: Should be defined after "goog.inherits"
//

// init physics
ChipmunkSpriteTest.prototype.initPhysics = function() {
    try {
	this.space =  cp.spaceNew();
	var staticBody = cp.spaceGetStaticBody( this.space );
	
	var walls = [cp.segmentShapeNew( staticBody, cp.v(0,0), cp.v(winSize.width,0), 0 ),// bottom
		     cp.segmentShapeNew( staticBody, cp.v(0,winSize.height), cp.v(winSize.width,winSize.height), 0),// top
		     cp.segmentShapeNew( staticBody, cp.v(0,0), cp.v(0,winSize.height), 0),// left
		     cp.segmentShapeNew( staticBody, cp.v(winSize.width,0), cp.v(winSize.width,winSize.height), 0)// right
		     ];
	
	for( var i=0; i < walls.length; i++ ) {
	    var wall = walls[i];
	    cp.shapeSetElasticity(wall, 1);
	    cp.shapeSetFriction(wall, 1);
	    cp.spaceAddStaticShape( this.space, wall );
	}
    
	// Gravity
	cp.spaceSetGravity( this.space, cp.v(0, -100) );
    } catch(e) {cc.log(e);}
};

ChipmunkSpriteTest.prototype.createPhysicsSprite = function( pos ) {

    var body = cp.bodyNew(1, cp.momentForBox(1, 48, 108));
    cp.bodySetPos(body, pos);
    cp.spaceAddBody( this.space, body );

    var shape = cp.boxShapeNew(body, 48, 108);
    cp.shapeSetElasticity( shape, 0.5 );
    cp.shapeSetFriction( shape, 0.5 );
    cp.spaceAddShape( this.space, shape );

    return null;
};

ChipmunkSpriteTest.prototype.onEnter = function () {

    try {
	cc.log("entered "+cp.v);
	
	for(var i=0; i<1; i++) {
	    this.addSprite( cp.v(winSize.width/2, winSize.height/2) );
	}
	
    } catch(e) {cc.log(e);}
};

ChipmunkSpriteTest.prototype.update = function( delta ) {    
    cc.log("step "+delta+"  "+this.space);
    cp.spaceStep(this.space, delta);
    cc.log("exited step");
};

ChipmunkSpriteTest.prototype.onMouseDown = function( event ) {
    pos = director.convertEventToGL( event );
    cc.log("Mouse Down:" + pos );
    this.addSprite( pos );
};

ChipmunkSpriteTest.prototype.onTouchesEnded = function( touches, event ) {
    var l = touches.length;
    for( var i=0; i < l; i++) {
	pos = director.convertTouchToGL( touches[i] );
	this.addSprite( pos );
    }
};

//------------------------------------------------------------------
//
// Chipmunk + Sprite + Batch
//
//------------------------------------------------------------------

var ChipmunkSpriteBatchTest = function() {

    this.addSprite = function( pos ) {
	var sprite =  this.createPhysicsSprite( pos );
	this.batch.addChild( sprite );
    }

    this.title = function() {
	return 'Chipmunk SpriteBatch Test';
    }

    this.subtitle = function() {
	return 'Chipmunk + cocos2d sprite batch tests. Tap screen.';
    }
};

// goog.inherits( ChipmunkSpriteBatchTest, ChipmunkSpriteTest );

var ChipmunkJointsTest = function() {

    // goog.base(this);

    var self = Base();
    self.spriteCount = 0;
    self.messageDisplayed = false;
    
    self.jointsCount = 0;

    self.bodies = [];

    self.title = function() {
	return 'Chipmunk Collision Test';
    };

    self.subtitle = function() {
	return 'Testing collision callback';
    };

    // init physics
    self.initPhysics = function() {
	self.space =  cp.spaceNew();
	var staticBody = cp.spaceGetStaticBody( self.space );

	// Walls
	var walls = [cp.segmentShapeNew( staticBody, cp.v(0,0), cp.v(winSize.width,0), 0 ),// bottom
		     cp.segmentShapeNew( staticBody, cp.v(0,winSize.height), cp.v(winSize.width,winSize.height), 0),// top
		     cp.segmentShapeNew( staticBody, cp.v(0,0), cp.v(0,winSize.height), 0),// left
		     cp.segmentShapeNew( staticBody, cp.v(winSize.width,0), cp.v(winSize.width,winSize.height), 0)// right
		     ];
	for( var i=0; i < walls.length; i++ ) {
	    var wall = walls[i];
	    cp.shapeSetElasticity(wall, 1);
	    cp.shapeSetFriction(wall, 1);
	    cp.spaceAddStaticShape( self.space, wall );
	}

	// Gravity
	cp.spaceSetGravity( self.space, cp.v(0, -30) );
    };

    var breakableJoint;

    self.joints = {};

    // Create the joints and set it's max force property.

    self.joints.createPinJoint = function (b1, b2) {
	breakableJoint = cp.spaceAddConstraint(self.space, cp.pinJointNew(b1, b2, cp.v(15,0), cp.v(-15,0)));
	cp.constraintSetMaxForce(breakableJoint, 4000);
    };

    self.joints.createSlideJoint = function (b1, b2) {
	try {
	    breakableJoint = cp.spaceAddConstraint(self.space, cp.slideJointNew(b1, b2, cp.v(15,0), cp.v(-15,0), 0.1, 2));
	    cp.constraintSetMaxForce(breakableJoint, 4000);
	} catch(e) { cc.log(e); }
    };

    self.joints.createPivotJoint = function (b1, b2) {
	try {
	    breakableJoint = cp.spaceAddConstraint(self.space, cp.pivotJointNew2(b1, b2, cp.v(15,0), cp.v(-15,0)));
	    cp.constraintSetMaxForce(breakableJoint, 4000);
	} catch(e) { cc.log(e); }
    };

    self.joints.createGrooveJoint = function (b1, b2) {
	try {
	    breakableJoint = cp.spaceAddConstraint(self.space, cp.grooveJointNew(b1, b2, cp.v(15,0), cp.v(30,0), cp.v(-15,0)));
	    cp.constraintSetMaxForce(breakableJoint, 4000);
	} catch(e) { cc.log(e); }
    };	


    self.joints.createDampedSpring = function(b1, b2) {
	breakableJoint = cp.spaceAddConstraint(self.space, cp.dampedSpringNew(b1, b2, cp.v(15,0),cp.v(-15,0),
									      0.9, 0.5, 0.6));
	cp.constraintSetMaxForce(breakableJoint, 4000);
    };

    self.joints.createDampedRotarySpring = function (b1, b2) {
	breakableJoint = cp.spaceAddConstraint(self.space, cp.dampedRotarySpringNew(b1, b2, 
										    0.9, 0.5, 0.6));
	cp.constraintSetMaxForce(breakableJoint, 4000);
    };	


    self.joints.createRotaryLimitJoint = function (b1, b2) {
	breakableJoint = cp.spaceAddConstraint(self.space, cp.rotaryLimitJointNew(b1, b2, 
										  0.2, 0.9));
	cp.constraintSetMaxForce(breakableJoint, 4000);
    };	


    self.joints.createRatchetJoint = function (b1, b2) {
	breakableJoint = cp.spaceAddConstraint(self.space, cp.ratchetJointNew(b1, b2, 
									      0.2, 0.9));
	cp.constraintSetMaxForce(breakableJoint, 4000);
    };	


    self.joints.createGearJoint = function (b1, b2) {
	breakableJoint = cp.spaceAddConstraint(self.space, cp.gearJointNew(b1, b2, 
									   0.2, 0.9));
	cp.constraintSetMaxForce(breakableJoint, 4000);
    };	


    self.joints.createSimpleMotor = function (b1, b2) {
	breakableJoint = cp.spaceAddConstraint(self.space, cp.simpleMotorNew(b1, b2, 
									     0.2));
	cp.constraintSetMaxForce(breakableJoint, 4000);
    };	

        
    var jointsList = ["createPinJoint", "createSlideJoint", "createPivotJoint", "createGrooveJoint",
		      "createDampedSpring", "createDampedRotarySpring", "createRotaryLimitJoint",
		      "createRatchetJoint", "createGearJoint", "createSimpleMotor"];

    

    function createBodyAndJoint(pos1, pos2) {

	var b1 = self.createPhysicsSprite(pos1, "grossini.png", self.spriteCount);
	var b2 = self.createPhysicsSprite(pos2, "grossinis_sister1.png", self.spriteCount);
	
	self.joints[jointsList[self.jointsCount]](b1, b2);
	
	++self.jointsCount;
	self.jointsCount %= jointsList.length;
	
	++self.spriteCount;

    }

    self.createPhysicsSprite = function( pos, file, collision_type ) {

	var body = cp.bodyNew(1, cp.momentForBox(1, 48, 108) );
	cp.bodySetPos( body, pos );
	cp.spaceAddBody( self.space, body );

	var shape = cp.boxShapeNew( body, 48, 108);
	cp.shapeSetElasticity( shape, 0.5 );
	cp.shapeSetFriction( shape, 0.5 );
	cp.shapeSetCollisionType( shape, collision_type );
	cp.spaceAddShape( self.space, shape );

	spriteList.addSprite(file);
	self.bodies[self.bodies.length] = body;

	return body;
    };

    
    function addDefinedCollisionHandlers(n, m) {
	cp.spaceAddCollisionHandler(self.space, n, m, self,
				    self.collisionBegin, self.collisionPre, 
				    self.collisionPost, self.collisionSeparate );
	
    }	
    
    function addAnonymousCollisionHandlers(id1, id2) {
	try {
	    cc.log(id1+" xcvxc "+id2);
	    cp.spaceAddCollisionHandler(self.space, id1, id2, self, function() {
		    cc.log("in collision Begin: ");
		    return true;
		}, function() {
		    cc.log("in collision Pre: ");
		    return true;
		}, function() {
		    cc.log("in collision Post: ");
		    return true;
		}, function() {
		    cc.log("in collision Separate: ");
		    return true;
		});
	} catch(e) { cc.log(e); }
    }

    self.onEnter = function () {
	
	//self.initialize();
	spriteList.setLayer(self);
        self.initPhysics();

	var body1, body2;

	for(var i = 50; i < winSize.width; i += winSize.width/10) {
	    try {

		createBodyAndJoint(cc.p(i, winSize.height-20), cc.p(i+60, winSize.height-20));
		addAnonymousCollisionHandlers(self.spriteCount-1, self.spriteCount);
	    } catch(e) { cc.log(e);}
	}


	//	addDefinedCollisionHandlers();

	self.scheduleUpdate();

	try {
	    var p = self.isTouchEnabled;
	    p = true;
	    self.isTouchEnabled = p;
	    
	    cc.log("Touches enabled: "+self.isTouchEnabled);
	} catch(e) { cc.log(e); }
	
    };

    self.onExit = function() {
	cp.spaceRemoveCollisionHandler( self.space, 1, 2 );
        cp.spaceFree( self.space );
    };

    self.update = function( delta ) {
	cp.spaceStep( self.space, delta );
	spriteList.updateSprites(self.bodies);
    };

    self.collisionBegin = function ( arbiter, space ) {

	cc.log('collision begin');
	var bodies = cp.arbiterGetBodies(arbiter );
	var shapes = cp.arbiterGetShapes(arbiter);
	var collTypeA = cp.shapeGetCollisionType( shapes[0] );
	var collTypeB = cp.shapeGetCollisionType( shapes[1] );
	cc.log( 'Collision Type A:' + collTypeA );
	cc.log( 'Collision Type B:' + collTypeB );

	return true
    };

    self.collisionPre = function ( arbiter, space ) {
	//	cc.log('collision pre');
	return true;
    };

    self.collisionPost = function ( arbiter, space ) {
	//cc.log('collision post');
	return true;
    };

    self.collisionSeparate = function ( arbiter, space ) {
	//	cc.log('collision separate');
	return true;
    };

    self.onMouseDown = function( event ) {
	pos = director.convertEventToGL( event );
	cc.log("Mouse Down:" + pos );
	self.addSprite( pos );
    };
    
    self.ccTouchesEnded = function( touches , event) {
	try {
	    var l = touches.length;
	    for( var i=0; i < l; i++) {

		var pos = self.convertTouchToNodeSpace( touches[i] );
		createBodyAndJoint(cc.p(pos.x, pos.y), cc.p(pos.x+30, pos.y));
	    }
	} catch(e) { cc.log("in handler: "+e); }
    };	
    
    return self;

};



//------------------------------------------------------------------
//
// Chipmunk Collision Test
//
//------------------------------------------------------------------
var ChipmunkCollisionTest = function() {

    // goog.base(this);

    var self = Base();
    self.spriteCount = 0;
    self.messageDisplayed = false;

    self.bodies = [];

    self.title = function() {
	return 'Chipmunk Collision Test';
    };

    self.subtitle = function() {
	return 'Testing collision callback';
    };

    // init physics
    self.initPhysics = function() {
	self.space =  cp.spaceNew();
	var staticBody = cp.spaceGetStaticBody( self.space );

	// Walls
	var walls = [cp.segmentShapeNew( staticBody, cp.v(0,0), cp.v(winSize.width,0), 0 ),// bottom
		     cp.segmentShapeNew( staticBody, cp.v(0,winSize.height), cp.v(winSize.width,winSize.height), 0),// top
		     cp.segmentShapeNew( staticBody, cp.v(0,0), cp.v(0,winSize.height), 0),// left
		     cp.segmentShapeNew( staticBody, cp.v(winSize.width,0), cp.v(winSize.width,winSize.height), 0)// right
		     ];
	for( var i=0; i < walls.length; i++ ) {
	    var wall = walls[i];
	    cp.shapeSetElasticity(wall, 1);
	    cp.shapeSetFriction(wall, 1);
	    cp.spaceAddStaticShape( self.space, wall );
	}

	// Gravity
	cp.spaceSetGravity( self.space, cp.v(0, -30) );
    };


    self.createPhysicsSprite = function( pos, file, collision_type ) {

	var body = cp.bodyNew(1, cp.momentForBox(1, 48, 108) );
	cp.bodySetPos( body, pos );
	cp.spaceAddBody( self.space, body );

	var shape = cp.boxShapeNew( body, 48, 108);
	cp.shapeSetElasticity( shape, 0.5 );
	cp.shapeSetFriction( shape, 0.5 );
	cp.shapeSetCollisionType( shape, collision_type );
	cp.spaceAddShape( self.space, shape );

	cc.log("Adding sprite");

	spriteList.addSprite(file);
	self.bodies[self.bodies.length] = body;

	return null;
    };

    self.onEnter = function () {
	
	self.initialize();
	spriteList.setLayer(self);
        self.initPhysics();

	var sprite1, sprite2;
	for(var i = 50; i < winSize.width; i += winSize.width/10) {
	    sprite1 = self.createPhysicsSprite( cc.p(i, winSize.height-20), "grossini.png", self.spriteCount);
	    sprite2 = self.createPhysicsSprite( cc.p(i+30, 50), "grossinis_sister1.png", self.spriteCount);
	    ++self.spriteCount;
	}

	cp.spaceAddCollisionHandler(self.space, 1, 2, self, function() {
		cc.log("in collision Begin: ");
	    }, function() {
		cc.log("in collision Pre: ");
	    }, function() {
		cc.log("in collision Post: ");
	    }, function() {
		cc.log("in collision Separate: ");
	    });
	    
	    //self.collisionBegin, self.collisionPre, self.collisionPost, self.collisionSeparate );

	self.scheduleUpdate();

	try {
	    var p = self.isTouchEnabled;
	    p = true;
	    self.isTouchEnabled = p;
	    
	    cc.log("Touches enabled: "+self.isTouchEnabled);
	} catch(e) { cc.log(e); }
	
    };

    self.onExit = function() {
	cp.spaceRemoveCollisionHandler( self.space, 1, 2 );
        cp.spaceFree( self.space );
    };

    self.update = function( delta ) {
	cp.spaceStep( self.space, delta );
	spriteList.updateSprites(self.bodies);
    };

    self.collisionBegin = function ( arbiter, space ) {

	cc.log('collision begin');
	var bodies = cp.arbiterGetBodies(arbiter );
	var shapes = cp.arbiterGetShapes(arbiter);
	var collTypeA = cp.shapeGetCollisionType( shapes[0] );
	var collTypeB = cp.shapeGetCollisionType( shapes[1] );
	cc.log( 'Collision Type A:' + collTypeA );
	cc.log( 'Collision Type B:' + collTypeB );

	return true
    };

    self.collisionPre = function ( arbiter, space ) {
	//	cc.log('collision pre');
	return true;
    };

    self.collisionPost = function ( arbiter, space ) {
	//cc.log('collision post');
	return true;
    };

    self.collisionSeparate = function ( arbiter, space ) {
	//	cc.log('collision separate');
	return true;
    };

    self.onMouseDown = function( event ) {
	pos = director.convertEventToGL( event );
	cc.log("Mouse Down:" + pos );
	self.addSprite( pos );
    };
    
    self.ccTouchesEnded = function( touches , event) {
	try {
	    var l = touches.length;
	    for( var i=0; i < l; i++) {
		pos = self.convertTouchToNodeSpace( touches[i] );
		self.createPhysicsSprite(cc.p(pos.x, pos.y), "grossini.png", self.spriteCount);
		++self.spriteCount;
	    }
	} catch(e) { cc.log("in handler: "+e); }
    };	
    
    return self;

};
// goog.inherits( ChipmunkCollisionTest, BaseLayer );

//------------------------------------------------------------------
//
// Chipmunk Collision Memory Leak Test
//
//------------------------------------------------------------------

var ChipmunkCollisionMemoryLeakTest = function() {

    // goog.base(this);

    var self = Base();

    self.title = function() {
	return 'Chipmunk Memory Leak Test';
    }

    self.subtitle = function() {
	return 'Testing possible memory leak on the collision handler. No visual feedback';
    }

    self.collisionBegin = function ( arbiter, space ) {
	return true
    }

    self.collisionPre = function ( arbiter, space ) {
	return true;
    }

    self.collisionPost = function ( arbiter, space ) {
	cc.log('collision post');
    }

    self.collisionSeparate = function ( arbiter, space ) {
	cc.log('collision separate');
    }

    self.onEnter = function() {
        //goog.base(self, 'onEnter');
	self.space =  cp.spaceNew();

        for( var i=1 ; i < 100 ; i++ )
            cp.spaceAddCollisionHandler( self.space, i, i+1, self, self.collisionBegin, self.collisionPre, self.collisionPost, self.collisionSeparate );

    }

    self.onExit = function() {

        for( var i=1 ; i < 100 ; i++ )
            cp.spaceRemoveCollisionHandler( self.space, i, i+1 );

        cp.spaceFree( self.space );
    }

    return self;
};

//goog.inherits( ChipmunkCollisionMemoryLeakTest, BaseLayer );
//
// Instance 'base' methods
// XXX: Should be defined after "goog.inherits"
//

var Sprites = function() { 
    
    var self = {};

    var director = cc.Director.sharedDirector();
    var _winSize = director.winSize;
    var winSize = {width:_winSize.width, height:_winSize.height};
    var centerPos = cc.p(winSize.width/2, winSize.height/2);
    var sprites = [];
    self.layer = null;

    function updatePosition(sprite, cv) {
	try {


	    var p = sprite.position;
	    p.x = cv[0];
	    p.y = cv[1];
	    sprite.position = p;
	    
	} catch(e) {cc.log(e);}
    }

    function radToDegree(a) {
	return a * 57.29577951;
    }

    function updateRotation(sprite, angle) {
	var r = sprite.rotation;
	r = -radToDegree(angle);
	sprite.rotation = r;
    }
	
    self.updateSprites = function(bodies) {
	for (var i = 0;  i < bodies.length; ++i) {
	    var cv = cp.bodyGetPos(bodies[i]);
	    updatePosition(sprites[i], cv);
	    try {
		var angle = cp.bodyGetAngle(bodies[i]);
		updateRotation(sprites[i], angle);
	    } catch(e) { cc.log(e);}
	}

    };
    
    self.setLayer = function(l) {
	layer = l;
    };
    
    self.addSprite = function(file) {	

	sprites[sprites.length] =  cc.Sprite.spriteWithFile(file);
	updatePosition(sprites[sprites.length-1], centerPos);
	layer.addChild(sprites[sprites.length-1]);

    };

    return self;
}

var spriteList = Sprites();
	


//
// Order of tests
//

scenes.push( ChipmunkSpriteTest ); 
scenes.push( ChipmunkSpriteBatchTest );
scenes.push( ChipmunkJointsTest );
scenes.push( ChipmunkCollisionTest );
scenes.push( ChipmunkCollisionMemoryLeakTest );

//------------------------------------------------------------------
//
// Main entry point
//
//------------------------------------------------------------------

function run()
{

    var scene = new cc.Scene();

    cc.log(currentScene);

    var cpTest = scenes[currentScene+2]();
    scene.addChild(cpTest);

    cc.log(currentScene);
    var runningScene = null;

    cc.log(runningScene+"   "+scene+"  ");
    
    if( runningScene == null )
        director.runWithScene(scene);
    else
        director.replaceScene(cc.TransitionFade.create(0.5, scene ) );

}

run();

cc.log("got through ");

} catch(e) {cc.log(e);}


} catch (e) { cc.log(e); }