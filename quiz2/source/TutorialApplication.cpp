//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
// Date: 2019/10/28
//
#include "TutorialApplication.h"
#include "BasicTools.h"

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace Ogre;

const float PI = 3.141592654;

#define mMoveDirection_NONE  0
#define mMoveDirection_DOWN  (1 << 0)
#define mMoveDirection_UP    (1 << 1)
#define mMoveDirection_LEFT  (1 << 2)
#define mMoveDirection_RIGHT (1 << 3)


BasicTutorial_00::BasicTutorial_00(void)
    : mMoveDirection(mMoveDirection_NONE) {}

void BasicTutorial_00::chooseSceneManager() {
	mSceneMgrArr[0] = mRoot
		->createSceneManager(ST_GENERIC, "primary");
	mSceneMgrArr[1] = mRoot
		->createSceneManager(ST_GENERIC, "secondary");
}

void BasicTutorial_00::createCamera_00(void) {
	mSceneMgr = mSceneMgrArr[0];
	mCamera = mCameraArr[0] = mSceneMgr->createCamera("PlayerCam");
	mCamera->setPosition(Ogre::Vector3(120,300,600));
	mCamera->lookAt(Ogre::Vector3(120,0,0));
	mCamera->setNearClipDistance(5);
	mCameraManArr[0] = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
}

void BasicTutorial_00::createCamera_01(void) {
	mSceneMgr = mSceneMgrArr[1];
	mCamera = mCameraArr[1] = mSceneMgr->createCamera("PlayerCam");
	mCamera->setPosition(Ogre::Vector3(0,350,0.0));
	mCamera->lookAt(Ogre::Vector3(0.00001,0,0));
	mCamera->setNearClipDistance(5);
	mCameraManArr[1] = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
}

void BasicTutorial_00::createViewport_00(void){
	mCamera = mCameraArr[0];
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0,0.0,1.0));
	mCamera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

    mViewportArr[0] = vp;
}

void BasicTutorial_00::createViewport_01(void){}

void BasicTutorial_00::resolveCollision(
    SceneNode *nodeA, SceneNode *nodeB,
    float rA, float rB, float wA, float wB)
{
    Vector3 posA = nodeA->getPosition();
    Vector3 posB = nodeB->getPosition();
    float R = rA + rB;
    ///////////////////////
    // add your own stuff
    ///////////////////////
    Vector3 Dist = posA - posB;
	if(Dist.length() < R) {
		Real overlap = R-Dist.length();
		Dist.normalise();
		Dist.y = 0;
		nodeA->translate(Dist*overlap*0.5);
		nodeB->translate(Dist*overlap*-0.5);
	}
}

void BasicTutorial_00::resolveCollisionLargeSphere(){
    float smallR = 15; // small sphere radius
    float largeR = 1.0/0.15*smallR; // large sphere radius
	// small spheres
	for (int i = 0; i < mNumSpheres; ++i){
        Vector3 Dist = mSpheresNode[i]->getPosition() - mSphere_node->getPosition();
		if(Dist.length() < smallR+largeR) {
			Real overlap = smallR+largeR-Dist.length();
			Dist.normalise();
			Dist.y = 0;
			mSpheresNode[i]->translate(Dist*overlap);
		}
    }
	// barrels wall
	for (int j = 0; j < mNumBarrels; ++j){
        Vector3 Dist = mSphere_node->getPosition() - mBarrelsNode[j]->getPosition();
		if(Dist.length() < largeR + barrelRadius) {
			Real overlap = largeR + barrelRadius - Dist.length();
			Dist.normalise();
			Dist.y = 0;
			mSphere_node->translate(Dist*overlap);
		}
    }
}

// perform collision handling for all pairs
void BasicTutorial_00::resolveCollisionSmallSpheres(){
    float ri = 15; // sphere radius
    float rj = 15; // sphere radius
    for (int i = 0; i < mNumSpheres; ++i){
		// other spheres
		for (int j = i+1; j < mNumSpheres; ++j){
            Vector3 Dist = mSpheresNode[i]->getPosition() - mSpheresNode[j]->getPosition();
			if(Dist.length() < ri+rj) {
				Real overlap = ri+rj-Dist.length();
				Dist.normalise();
				Dist.y = 0;
				mSpheresNode[i]->translate(Dist*overlap*0.5);
				mSpheresNode[j]->translate(Dist*overlap*-0.5);
			}
        }
		// barrels
		for (int j = 0; j < mNumBarrels; ++j){
            Vector3 Dist = mSpheresNode[i]->getPosition() - mBarrelsNode[j]->getPosition();
			if(Dist.length() < ri+barrelRadius) {
				Real overlap = ri + barrelRadius - Dist.length();
				Dist.normalise();
				Dist.y = 0;
				mSpheresNode[i]->translate(Dist*overlap);
			}
        }
	}
}

void BasicTutorial_00::resolveCollision(){
    resolveCollisionSmallSpheres();
    resolveCollisionLargeSphere();
}

// reset positions of all small spheres
void BasicTutorial_00::reset(){
	mSphere_node->setPosition(0,0,0);
    for (int i = 0; i < mNumSpheres; ++i ) {
        Real x = rand()%10000/10000.0 * 800.0;
		Real y = 0;
		Real z = rand()%10000/10000.0 * 800.0;
		Vector3 pos = Vector3(x,y,z) - Vector3(400.0,0,400.0);
		
		mSpheresNode[i]->setPosition(pos);
    }
}

void BasicTutorial_00::createBarrelsWall(){
	// Create Barrels Wall
	String name_en, name_sn;
	int barrelsCnt = 0;
	genNameUsingIndex("barrel", 0, name_en);
	genNameUsingIndex("barrel", 0, name_sn);
	mBarrelsEnt[barrelsCnt] = mSceneMgr->createEntity(name_en, "barrel.mesh");
	AxisAlignedBox bb =  mBarrelsEnt[barrelsCnt]->getBoundingBox();
	// set diameter
	mBarrelsNode[barrelsCnt] = mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode(name_sn);
	mBarrelsNode[barrelsCnt]->attachObject(mBarrelsEnt[barrelsCnt]);
	Real x = -600.0;
	Real y = 20;
	Real z = -600.0;
	mBarrelsNode[barrelsCnt]->scale(10,10,10);
	mBarrelsNode[barrelsCnt]->setPosition(x, y, z);
	int diameter = (bb.getMaximum().x - bb.getMinimum().x)*10;
	barrelRadius = diameter/2;
    mNumBarrels = 300;
	barrelsCnt++;
	// x = -600 ~ 600; z = -600
    for (x+=diameter ; x <= 600; x+=diameter, barrelsCnt++) {
		String name_en, name_sn;
	    genNameUsingIndex("barrels", barrelsCnt, name_en);
	    genNameUsingIndex("barrels", barrelsCnt, name_sn);
        mBarrelsEnt[barrelsCnt] = mSceneMgr
			->createEntity( name_en, "barrel.mesh" );

		mBarrelsNode[barrelsCnt] = mSceneMgr
			->getRootSceneNode()
			->createChildSceneNode(name_sn);
		mBarrelsNode[barrelsCnt]->scale(10,10,10);
		mBarrelsNode[barrelsCnt]->setPosition(x,y,z);
		mBarrelsNode[barrelsCnt]->attachObject(mBarrelsEnt[barrelsCnt]);
    }
	// x = 600; z = -600 ~ 600
    for (x-=diameter, z+=diameter ; z <= 600; z += diameter, barrelsCnt++) {
		String name_en, name_sn;
	    genNameUsingIndex("barrels", barrelsCnt, name_en);
	    genNameUsingIndex("barrels", barrelsCnt, name_sn);
        mBarrelsEnt[barrelsCnt] = mSceneMgr
			->createEntity( name_en, "barrel.mesh" );

		mBarrelsNode[barrelsCnt] = mSceneMgr
			->getRootSceneNode()
			->createChildSceneNode(name_sn);
		mBarrelsNode[barrelsCnt]->scale(10,10,10);
		mBarrelsNode[barrelsCnt]->setPosition(x,y,z);
		mBarrelsNode[barrelsCnt]->attachObject(mBarrelsEnt[barrelsCnt]);
    }
	// x = 600 ~ -600; z = 600
    for (z-=diameter, x-=diameter ; x >= -600; x -= diameter, barrelsCnt++) {
		String name_en, name_sn;
	    genNameUsingIndex("barrels", barrelsCnt, name_en);
	    genNameUsingIndex("barrels", barrelsCnt, name_sn);
        mBarrelsEnt[barrelsCnt] = mSceneMgr
			->createEntity( name_en, "barrel.mesh" );

		mBarrelsNode[barrelsCnt] = mSceneMgr
			->getRootSceneNode()
			->createChildSceneNode(name_sn);
		mBarrelsNode[barrelsCnt]->scale(10,10,10);
		mBarrelsNode[barrelsCnt]->setPosition(x,y,z);
		mBarrelsNode[barrelsCnt]->attachObject(mBarrelsEnt[barrelsCnt]);
    }
	// x = -600; z = 600 ~ -600
    for (z-=diameter, x+=diameter ; z >= -600; z -= diameter, barrelsCnt++) {
		String name_en, name_sn;
	    genNameUsingIndex("barrels", barrelsCnt, name_en);
	    genNameUsingIndex("barrels", barrelsCnt, name_sn);
        mBarrelsEnt[barrelsCnt] = mSceneMgr
			->createEntity( name_en, "barrel.mesh" );

		mBarrelsNode[barrelsCnt] = mSceneMgr
			->getRootSceneNode()
			->createChildSceneNode(name_sn);
		mBarrelsNode[barrelsCnt]->scale(10,10,10);
		mBarrelsNode[barrelsCnt]->setPosition(x,y,z);
		mBarrelsNode[barrelsCnt]->attachObject(mBarrelsEnt[barrelsCnt]);
    }
	mNumBarrels = barrelsCnt-1;
	printf("There are %d barrels\n", mNumBarrels);
}

// create all spheres
// "Examples/red"
// "Examples/green"
// "Examples/blue"
// "Examples/yellow"
void BasicTutorial_00::createSpace(){
	// Create Big Sphere
	Vector3 mSphere_pos(0, 0, 0);
	mSphere_ent = mSceneMgr->createEntity("SphereEnt", "sphere.mesh");
	mSphere_ent->setMaterialName("Examples/yellow");
	mSphere_node = mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode("SphereNode");
	mSphere_node->setScale(1,1,1);
	mSphere_node->setPosition(mSphere_pos);
	mSphere_node->attachObject(mSphere_ent);
	
	// Create small Spheres
    
    for (int i = 0; i < 500; ++i ) {
		String name_en, name_sn;
	    genNameUsingIndex("spheres", i, name_en);
	    genNameUsingIndex("spheres", i, name_sn);
        mSpheresEnt[i] = mSceneMgr
			->createEntity( name_en, "sphere.mesh" );

		switch(rand()%3) {
			case 0:
				mSpheresEnt[i]->setMaterialName("Examples/red");
				break;
			case 1:
				mSpheresEnt[i]->setMaterialName("Examples/green");
				break;
			case 2:
				mSpheresEnt[i]->setMaterialName("Examples/blue");
				break;
		}

		Real x = rand()%10000/10000.0 * 800.0;
		Real y = 0;
		Real z = rand()%10000/10000.0 * 800.0;
		Vector3 pos = Vector3(x,y,z) - Vector3(400.0,0,400.0);
		//scale the small spheres
		mSpheresNode[i] = mSceneMgr
			->getRootSceneNode()
			->createChildSceneNode(name_sn);
		mSpheresNode[i]->scale(0.15, 0.15, 0.15);
		mSpheresNode[i]->setPosition(pos);
		mSpheresNode[i]->attachObject(mSpheresEnt[i]);
    }
}

void BasicTutorial_00::recreateSpace(int num){
	mNumSpheres = num;
	for(int i=0; i<500; i++)
		mSpheresNode[i]->detachObject(mSpheresEnt[i]);
	for(int i = 0; i<mNumSpheres; i++)
		mSpheresNode[i]->attachObject(mSpheresEnt[i]);
}

void BasicTutorial_00::createScene_00(void) 
{
	mSceneMgr = mSceneMgrArr[0];
	//mSceneMgr->setAmbientLight( ColourValue( 0.25, 0.25, 0.25 ) ); 
	mSceneMgr->setAmbientLight( ColourValue( 0.5, 0.5, 0.5 ) ); 
	//mSceneMgr->setAmbientLight( ColourValue( 1, 1, 1 ) );  
	mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE); 

	Light *light;
	light = mSceneMgr->createLight("Light1"); 
	light->setType(Light::LT_POINT); 
	light->setPosition(Vector3(150, 250, 100)); 
	light->setDiffuseColour(0.3, 0.3, 0.3);		
	light->setSpecularColour(0.5, 0.5, 0.5);	

	light = mSceneMgr->createLight("Light2"); 
	light->setType(Light::LT_POINT); 
	light->setPosition(Vector3(-150, 300, 250)); 
	light->setDiffuseColour(0.25, 0.25, 0.25);		
	light->setSpecularColour(0.35, 0.35, 0.35);	

	Plane plane(Vector3::UNIT_Y, 0); 
	MeshManager::getSingleton().createPlane(
		"ground", 						ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
		plane, 
		1500,1500, 	// width, height
		20,20, 		// x- and y-segments
		true, 		// normal
		1, 			// num texture sets
		5,5, 		// x- and y-tiles
		Vector3::UNIT_Z	// upward vector
		); 

	Entity *ent = mSceneMgr->createEntity("GroundEntity", "ground"); 
	ent->setMaterialName("Examples/BeachStones");
	// ent->setMaterialName("Examples/Rockwall");


	mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode()
		->attachObject(ent); 

    ent = mSceneMgr->createEntity(
		"Background", "ground"); 
	//ent->setMaterialName("Examples/BeachStones");
	ent->setMaterialName("Examples/Rockwall");

    //Radian angle((45/180.0)*3.141592654);
    Radian angle(3.141952654/2.0);

    Vector3 axis(1.0, 0.0, 0.0);
    mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode(
            Vector3(0.0, 0.0, -750.0),
            Quaternion( angle, axis))
		->attachObject(ent);

    createSpace();	
	mNumSpheres = 500;
	recreateSpace(500);
	
	createBarrelsWall();
    
    resolveCollision();
}

void BasicTutorial_00::createScene_01(void) {}

void BasicTutorial_00::createViewports(void)
{
	createViewport_00();
	//createViewport_01();
}

void BasicTutorial_00::createCamera(void) {
	createCamera_00();
	//createCamera_01();
	mCameraMan = mCameraManArr[0];
	//mCameraMan = mCameraManArr[1];
}

void BasicTutorial_00::createScene( void ) {
	createScene_00();
	//createScene_01();
	mSceneMgr = mSceneMgrArr[0]; // active SceneManager
	//mSceneMgr = mSceneMgrArr[1]; // active SceneManager
    //
    mCamera = mCameraArr[0];
    //mCamera = mCameraArr[1];
    //
    mCameraMan->getCamera()
            ->setPosition(Vector3(-22.30,	409.24,	816.74));
    mCameraMan->getCamera()
            ->setDirection(Vector3(0.02,	-0.23,	-0.97));
}

bool BasicTutorial_00::keyPressed( const OIS::KeyEvent &arg )
{
    bool flg = true;
    stringstream ss;
    ss << arg.key;
    String msg;
    ss >> msg;
    msg += ":*** keyPressed ***\n";
    Ogre::LogManager::getSingletonPtr()->logMessage( msg );

    if (arg.key == OIS::KC_C ) {
        ss.str("");
        ss.clear();
        
        Vector3 pos = mCameraMan->getCamera()->getPosition(); //Correct
        ss << std::fixed << std::setprecision(2) 
            << "CameraPosition:" 
            << pos.x << "\t" 
            << pos.y << "\t" 
            << pos.z << "\n";
        Ogre::LogManager::getSingletonPtr()
            ->logMessage( ss.str() );
        ss.str("");
        ss.clear();
        Vector3 dir = mCameraMan->getCamera()->getDirection();
        ss << std::fixed << std::setprecision(2) 
            << "CameraDirection:" 
            << dir.x << "\t" 
            << dir.y << "\t" 
            << dir.z << "\n";
        Ogre::LogManager::getSingletonPtr()
            ->logMessage( ss.str() );
    }

    if (arg.key == OIS::KC_1 ) {
        mCameraMan->getCamera()
            ->setPosition(Vector3(-22.30,	409.24,	1220.74));
        mCameraMan->getCamera()
            ->setDirection(Vector3(0.02,	-0.23,	-0.97));
    }

    if (arg.key == OIS::KC_2 ) {
        mCameraMan->getCamera()
            ->setPosition(Vector3(-1463.00,	606.45, 0.0));
        mCameraMan->getCamera()
            ->setDirection(Vector3(0.88, -0.47, 0.10));

        //-1463.00	606.45	-513.24
        //0.88	-0.47	0.10
    }


    if (arg.key == OIS::KC_3 ) {
        mCameraMan->getCamera()
            ->setPosition(Vector3(19.94, 1600.63, 30.79));
        mCameraMan->getCamera()
            ->setDirection(Vector3(0.00, -0.99, -0.11));
        //19.94	822.63	30.79
        //0.00	-0.99	-0.11
    }

    if (arg.key == OIS::KC_U ) {
		mMoveDirection |= mMoveDirection_UP;
    }
	if (arg.key == OIS::KC_J ) {
		mMoveDirection |= mMoveDirection_DOWN;
    }
	if (arg.key == OIS::KC_H ) {
		mMoveDirection |= mMoveDirection_LEFT;
    }
	if (arg.key == OIS::KC_K ) {
		mMoveDirection |= mMoveDirection_RIGHT;
    }

	if (arg.key == OIS::KC_7 ) {
		recreateSpace(100);
    }
	if (arg.key == OIS::KC_8 ) {
		recreateSpace(200);
    }
	if (arg.key == OIS::KC_9 ) {
		recreateSpace(300);
    }
	if (arg.key == OIS::KC_0 ) {
		recreateSpace(500);
    }


    if (arg.key == OIS::KC_B ) {
		reset();
    }

    BaseApplication::keyPressed(arg);

    return flg;
}

bool BasicTutorial_00::keyReleased( const OIS::KeyEvent &arg ){
    bool flg = true;
    stringstream ss;
    ss << arg.key;
    String msg;
    ss >> msg;
    msg += ":*** keyReleased ***\n";
    
    Ogre::LogManager::getSingletonPtr()->logMessage( msg );

	if (arg.key == OIS::KC_U ) {
		mMoveDirection &= ~mMoveDirection_UP;
    }
	if (arg.key == OIS::KC_J ) {
		mMoveDirection &= ~mMoveDirection_DOWN;
    }
	if (arg.key == OIS::KC_H ) {
		mMoveDirection &= ~mMoveDirection_LEFT;
    }
	if (arg.key == OIS::KC_K ) {
		mMoveDirection &= ~mMoveDirection_RIGHT;
    }

    BaseApplication::keyReleased(arg);

    return flg;
}

bool BasicTutorial_00::frameStarted(const Ogre::FrameEvent& evt){
	bool flg = Ogre::FrameListener::frameStarted(evt);
    //
    Vector3 mdir;
	if (mMoveDirection & mMoveDirection_DOWN) {
        mdir += Vector3(0.0, 0.0, 1.0);
    }
    if (mMoveDirection & mMoveDirection_UP) {
        mdir += Vector3(0.0, 0.0, -1.0);
    }
	if (mMoveDirection & mMoveDirection_LEFT) {
        mdir += Vector3(-1.0, 0.0, 0.0);
    }
	if (mMoveDirection & mMoveDirection_RIGHT) {
        mdir += Vector3(1.0, 0.0, 0.0);
    }
	mSphere_node->translate(mdir*10);

    resolveCollision();
    //
    return flg;
}

int main(int argc, char *argv[]) {
	BasicTutorial_00 app;
	app.go();  
	return 0;
}
