////////////////////////////////////////
//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
// Date: 2019/09/20
////////////////////////////////////////
// Student Name: Yu-Chen Hsiao
// Student ID: 0616221
// Student Email: ychsiao@gmail.com
//

#include "TutorialApplication.h"
#include "BasicTools.h"

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

#include<stdio.h>

using namespace Ogre;

const float PI = 3.141592654;

int robotIndex = 0;

/*! \brief Constructor */
/**
Initialize:
- remove cameraMan
- mouse press = false
- create sound
*/
BasicTutorial_00::BasicTutorial_00(void) {
    if (mCameraMan) delete mCameraMan;
	isMousePressed = false;
	mSound = new SOUND;
	mSound->init();
	ParticleOn=true;
}
/*! \brief Create SceneManager */
/** Setting two scene Manager */
void BasicTutorial_00::chooseSceneManager()
{
	mSceneMgrArr[0] = mRoot
		->createSceneManager(ST_GENERIC, "primary");
	mSceneMgrArr[1] = mRoot
		->createSceneManager(ST_GENERIC, "secondary");
}
/*! \brief Create MAJOR Camera */
/** Create the major camera at the point (0, 800, 500) */
void BasicTutorial_00::createCamera_00(void)
{
	mSceneMgr = mSceneMgrArr[0];
	mCamera = mCameraArr[0] = mSceneMgr->createCamera("PlayerCam");
	mCamera->setPosition(Ogre::Vector3(0,800,500));
	mCamera->lookAt(Ogre::Vector3(0,0,0));
	mCamera->setNearClipDistance(5);
	mCameraManArr[0] = new OgreBites::SdkCameraMan(mCamera);
}
/*! \brief Create minor Camera */
void BasicTutorial_00::createCamera_01(void)
{
	mSceneMgr = mSceneMgrArr[0];
	mCamera = mCameraArr[1] = mSceneMgr->createCamera("MapCam");
	mCamera->setPosition(Ogre::Vector3(0,1400,0.0001));
	mCamera->lookAt(Ogre::Vector3(0,0,0));
	mCamera->setNearClipDistance(5);
	mCameraManArr[1] = new OgreBites::SdkCameraMan(mCamera);
}
/*! \brief Create MAJOR viewport */
void BasicTutorial_00::createViewport_00(void)
{
	mCamera = mCameraArr[0];
	Ogre::Viewport *vp = mViewportArr[0] = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
	mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth())/Ogre::Real(vp->getActualHeight()));
}
/*! \brief Create minor viewport */
void BasicTutorial_00::createViewport_01(void)
{
	mCamera = mCameraArr[1];
	Ogre::Viewport *vp = mViewportArr[1] = mWindow->addViewport(mCamera, 1, 0.0, 0.0, 0.25, 0.25);
	vp->setBackgroundColour(Ogre::ColourValue(1,1,0));
	vp->setOverlaysEnabled(false);
	vp->setSkiesEnabled(false);
	mCamera->setAspectRatio(4*Ogre::Real(vp->getActualWidth())/Ogre::Real(vp->getActualHeight()));
}
/*! \brief Create light in MAJOR scene */
void BasicTutorial_00::createLight_00(){
	mSceneMgr = mSceneMgrArr[0];
	Light *light = mSceneMgr->createLight("Light_M");
	light->setType(Light::LT_POINT); 
	light->setPosition(Vector3(150, 250, 100)); 
	light->setDiffuseColour(0.4, 0.4, 0.4);
	light->setSpecularColour(0.6, 0.6, 0.6);
}
/*! \brief Create light in minor scene */
void BasicTutorial_00::createLight_01(){
	mSceneMgr = mSceneMgrArr[1];
	Light *light = mSceneMgr->createLight("Light_m");
	light->setType(Light::LT_POINT); 
	light->setPosition(Vector3(100, 150, 250)); 
	light->setDiffuseColour(0.4, 0.1, 0.4);
	light->setSpecularColour(0.5, 0.5, 0.5);
}
/*! \brief Create a circle of objects */
void BasicTutorial_00::createCircleOfObject(Ogre::String objectName, Ogre::String meshName, int objectNum, double radius)
{
	for (int i = 0; i < objectNum; ++i, robotIndex++) {
		String name;
		genNameUsingIndex(objectName, robotIndex, name);
		Entity *ent = mSceneMgr->createEntity(name, meshName);
		Ogre::AxisAlignedBox boundingBox = ent->getBoundingBox();
		SceneNode *node = mSceneMgr
			->getRootSceneNode()
			->createChildSceneNode();
		// attach robot ent
		mRobotEntArr[robotIndex]=ent;
		// attach robot node
		mRobotNodeArr[robotIndex]=node;
		// set false to robot walk
		isRobotWalk[robotIndex]=false;
		node->attachObject(ent);
		double fx = i/(double) (objectNum-1);
		node->scale(1,1,1);
		double x1 = radius*cos(fx*PI*2);
		double z1 = radius*sin(fx*PI*2);
		node->setPosition(x1, 0, z1);
		node->lookAt(Ogre::Vector3(0,0,0), Node::TransformSpace::TS_WORLD, Vector3::UNIT_X);
	}
}
/** \brief Create Scene */
void BasicTutorial_00::createScene_00(void)
{
	mSceneMgr = mSceneMgrArr[0];
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.4,0.4,0.4));
	Ogre::ColourValue fogColour(0.7,0.7,0.7);
	/** create Fog */
	mSceneMgr->setFog(Ogre::FOG_LINEAR, fogColour, 0.0, 1400, 1600);
	/** create sky with SkyBox */
	mSceneMgr->setSkyBox(true,"Examples/EveningSkyBox"); 
	/** create sky with SkyDome */
	//mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8);
	mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);

	createLight_00();
	/** create plane */
	Plane plane(Vector3::UNIT_Y, 0);

	MeshManager::getSingleton().createPlane(
		"playerPlane",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane,
		1500,1500,
		20,20,
		true,
		1,
		5,5,
		Vector3::UNIT_Z
	);
	
	Ogre::Entity *playerPlane = mSceneMgr->createEntity("playerPlane", "playerPlane");
	mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode("playerPlane_node")
		->attachObject(playerPlane);
	playerPlane->setMaterialName("Examples/Rocky");
	playerPlane->setCastShadows(false);
	playerPlane->setQueryFlags(0);

	/** create a circle of robots */
	createCircleOfObject("robot", "robot.mesh", 30, 200);
	createCircleOfObject("robot", "robot.mesh", 30, 300);

	// make one robot bigger
	mSceneMgr->getRootSceneNode()->getChild(0)->scale(2, 2, 2);

	/** create central sphere */
	Ogre::Entity* centralSphere = mSceneMgr->createEntity("centralSphere_ent", "sphere.mesh");
	centralSphere->setCastShadows(true);
	Ogre::SceneNode* centralSphere_node = mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode(Ogre::Vector3(0, 0, 0));
	centralSphere_node->setScale(Ogre::Vector3(0.7,0.7,0.7));
	centralSphere_node->attachObject(centralSphere);
	centralSphere->setQueryFlags(0);

	/** create rotation light */
	Ogre::Light* rotLight = mSceneMgr->createLight("rotLight");
	rotLight->setType(Light::LT_POINT);
	rotLight->setDiffuseColour(ColourValue(1,1,1));
	rotLight->setSpecularColour(ColourValue(1,1,1));
	rotLight->setCastShadows(true);

	mRotLightNode = mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode("rotLight_prim_n", Ogre::Vector3(0,0,0));
	Ogre::SceneNode* rotLight_node = mRotLightNode
		->createChildSceneNode("rotLight_n", Ogre::Vector3(0,0,0));
	rotLight_node->attachObject(rotLight);
	rotLight_node->translate(Ogre::Vector3(-1000,500,0));

	/** create selection rectangle */
	mSelectionRect = new SelectionRectangle("selectionRect");
	mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode()
		->attachObject(mSelectionRect);
	mSelectionRect->setLightMask(0);
	mSelectionRect->setCastShadows(false);

	/** bounding box & volume selection */
	PlaneBoundedVolumeList volList;
	mVolQuery = mSceneMgr->createPlaneBoundedVolumeQuery(volList);
	
	/** create particle system */
	addParticleSystem();
}
/*! \brief Create objects in minor scene */
void BasicTutorial_00::createScene_01(void) 
{
}
/*!
\brief Create viewports
Set aspect ratio:
- Viewport[0]:
- mCamera->setAspectRatio(Real(vp->getActualWidth())/Real(vp->getActualHeight()))
- Viewport[1]:
- mCamera->setAspectRatio(4*Real(vp->getActualWidth())/Real(vp->getActualHeight()))
*/
void BasicTutorial_00::createViewports(void)
{
	createViewport_00();
	createViewport_01();
}
/*! \brief Create cameras
using mSceneMgr to set 
- position: mCamera->setposition()
- lookat: mCamera->lookAt()
- next near clip distance: mCamera->nextNearClipDistance()
- create and set fog and skybox
*/
void BasicTutorial_00::createCamera(void) {
	createCamera_00();
	createCamera_01();
	mCameraMan = mCameraManArr[0];
}
/*!
\brief Create scenes
Scene_00
- AmbientLight: (0.4,0.4,0.4)
- Shadow: enable
- Light
- Plane
  - Vector: UNIT_Y(0,1,0)
  - width: 1500
  - height: 1500
  - x-segments: 20
  - y-segments: 20
  - normal: true
  - num texture sets: 1
  - x-tiles: 5
  - y-tiles: 5
  - vector: UNITZ(0,0,1)
- Inside Circle of robots
  - Entity: robots[0~59]
  - SceneNode: robotsNode[0~59]
  - Scale: (1,1,1)
  - Radius: 200
  - First robot[0] with scale (2,2,2)
  - Particle system
- Second circle of robots
  - Entity: robots[60~119]
  - SceneNode: robotsNode[60~119]
  - Scale: (1,1,1)
  - radius : 300
- central sphere (circle)
  - Cast shadow
  - Position: (0,0,0)
  - Scale: (0.7, 0.7, 0.7)
  - QueryFlags: 0
- Rotation Light
  - Rotation light prim
    - Diffuse: (1,1,1)
    - Specular: (1,1,1)
    - Cast shadow: true
  - Rotation light
    - Translate: (-1000, 500, 0)
  - Yaw Rotation light prim per frame
- Particle system
*/
void BasicTutorial_00::createScene( void ) {
	createScene_00();
	createScene_01();
	/** SceneManeger: Scene_00 */
	mSceneMgr = mSceneMgrArr[0];
	/** Camera: Camera_00 */
    mCamera = mCameraArr[0];
}
/*!
\brief Mouse Moved
- getCursorRay
- sceneToScreen
- setCorner ( left, top, right, bottom)
- setVisible if the mouse is pressed
*/
bool BasicTutorial_00::mouseMoved( const OIS::MouseEvent &arg ) {
	mCamera = mCameraArr[0];
    Ray mRay =mTrayMgr->getCursorRay(mCamera);

	Vector2 scn = mTrayMgr->sceneToScreen(mCamera, mRay.getOrigin());
	left = scn.x;
	top = scn.y;

	mSelectionRect->setCorners(left, top, right, bottom);
	// show the selected area
	mSelectionRect->setVisible(isMousePressed);

	return BaseApplication::mouseMoved(arg);
}
/*!
\brief Mouse Pressed
Activate mousePressed
Pressed Left Key
- Robot not walking -> showBoundingBox = false
- selectRect clear
- Initialize selectRect: setCorner (init_X, init_Y, init_X, init_Y)
*/
bool BasicTutorial_00::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
	isMousePressed = true;

	if (id == OIS::MB_Right) {
		return BaseApplication::mousePressed( arg, id );
	}
	else if (id == OIS::MB_Left) {
		for (int a=0; a<60; a++) {
			if (!isRobotWalk[a])
				mRobotNodeArr[a]->showBoundingBox(false);
		}
		mSelectionRect->clear();
		
		Ray mRay =mTrayMgr->getCursorRay(mCamera);

		RaySceneQuery *mRaySceneQuery = 
		mSceneMgr->createRayQuery ( Ray() ); 

		mRaySceneQuery->setRay(mRay);
		// Perform the scene query
		RaySceneQueryResult &result = 
			mRaySceneQuery->execute();
		RaySceneQueryResult::iterator itr = result.begin();

		// Init the corner point
		Vector2 scn = mTrayMgr->sceneToScreen(mCamera, mRay.getOrigin());
		float init_X = scn.x;
		float init_Y = scn.y;

		mSelectionRect->setCorners(init_X, init_Y, init_X, init_Y);
		left = init_X;
		top = init_Y;
		right = init_X;
		bottom = init_Y;
	}
	return BaseApplication::mousePressed( arg, id );
}
/*! \brief Mouse Released */
bool BasicTutorial_00::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id ) {
	isMousePressed = false;

	mCamera = mCameraArr[0];
	mSelectionRect->clear();
	/**
	Left Click Release
	- Handling one sudden click
	  - create ray query
	  - ray query execute
	  - check all ray query with iterator
	  - if movable
	    - get parentSceneNode
	    - show bounding box
	- Handling bounded volume
	  - Create bounded volume
	    - front plane
		- top plane
		- left plane
		- bottom plane
		- right plane
	  - create volume list
	  - set volume query
	  - volume query execute
	  - check all volume query with iterator
	  - if movable
	    - get parentSceneNode
	    - show bounding box
	*/
	if (id == OIS::MB_Left) {
		if (left==right && top==bottom){
			Ray mRay =mTrayMgr->getCursorRay(mCamera);

			RaySceneQuery *mRaySceneQuery = mSceneMgr->createRayQuery ( Ray() ); 

			mRaySceneQuery->setSortByDistance(true); 

			mRaySceneQuery->setRay(mRay);
			
			RaySceneQueryResult &result = mRaySceneQuery->execute();
			RaySceneQueryResult::iterator itr = result.begin();

			for (itr = result.begin(); itr != result.end(); itr++)
			{

				if (itr->movable && itr->movable->getName().substr(0, 5) != "tile[")
				{
					mCurrentObject = itr->movable->getParentSceneNode();
					bool flgShow = mCurrentObject->getShowBoundingBox();
					mCurrentObject->showBoundingBox(!flgShow);
					break;
				}
				else if (itr->worldFragment) {
					//
				}
			}
		    return BaseApplication::mouseReleased( arg, id );
		}
		// finish handling one click
		//USING mTrayMgr=============
		Real nleft = left;
		Real nright = right;
		Real ntop = 1+top;
		Real nbottom = 1+bottom;
		Ray topLeft = mTrayMgr->screenToScene(mCamera, Vector2(nleft, ntop));
		Ray topRight = mTrayMgr->screenToScene(mCamera, Vector2(nright, ntop));
		Ray bottomLeft = mTrayMgr->screenToScene(mCamera, Vector2(nleft, nbottom));
		Ray bottomRight = mTrayMgr->screenToScene(mCamera, Vector2(nright, nbottom));
		//End Using mTrayMgr=============

		// The plane faces the counter clockwise position.
		PlaneBoundedVolume vol;
		int np = 100;
		vol.planes.push_back(Plane(topLeft.getPoint(3), topRight.getPoint(3), bottomRight.getPoint(3))); // front plane
		vol.planes.push_back(Plane(topLeft.getOrigin(), topLeft.getPoint(np), topRight.getPoint(np))); // top plane
		vol.planes.push_back(Plane(topLeft.getOrigin(), bottomLeft.getPoint(np), topLeft.getPoint(np))); // left plane
		vol.planes.push_back(Plane(bottomLeft.getOrigin(), bottomRight.getPoint(np), bottomLeft.getPoint(np))); // bottom plane
		vol.planes.push_back(Plane(bottomRight.getOrigin(), topRight.getPoint(np), bottomRight.getPoint(np))); // right plane 
		
		PlaneBoundedVolumeList volList;
		volList.push_back(vol);
		mVolQuery->setVolumes(volList);

		SceneQueryResult result = mVolQuery->execute();

		SceneQueryResultMovableList::iterator itr = result.movables.begin();
		for (itr = result.movables.begin(); itr != result.movables.end(); ++itr)
		{
			if (*itr)
			{
				mCurrentObject = (*itr)->getParentSceneNode();
				bool flgShow = mCurrentObject->getShowBoundingBox();
				mCurrentObject->showBoundingBox(!flgShow);
			}
		}
		return BaseApplication::mouseReleased( arg, id );
	}
	/**
	Right Click Release
	- create mouseRay with camera to viewport
	- get mouseRay intersect value
	- get Destination
	- if robot is selected (show bounding box)
	  - animation: walked
	  - robot walk = true
	  - get direction
	  - get distance
	*/
	else if(id == OIS::MB_Right)
	{
		Real x = arg.state.X.abs;
		Real y = arg.state.Y.abs; 

		Ogre::Real screenWidth = Ogre::Root::getSingleton().getAutoCreatedWindow()->getWidth();
		Ogre::Real screenHeight = Ogre::Root::getSingleton().getAutoCreatedWindow()->getHeight();

		Ogre::Real offsetX = x / screenWidth;
		Ogre::Real offsetY = y / screenHeight;

		// set up the ray
		Ray mouseRay = mCamera->getCameraToViewportRay(offsetX, offsetY);

		Plane plane(Vector3::UNIT_Y,0);
		std::pair<bool, Real> result = mouseRay.intersects(plane);

		if(result.first) {
			mDestination = mouseRay.getPoint(result.second);

			for (int robotCounter=0; robotCounter<60; robotCounter++)
			{
				if (mRobotNodeArr[robotCounter]->getShowBoundingBox())
				{
					mAnimationState[robotCounter] = mRobotEntArr[robotCounter]->getAnimationState("Walk");
					mAnimationState[robotCounter]->setLoop(true);
					mAnimationState[robotCounter]->setEnabled(true);
					isRobotWalk[robotCounter] = true;
					mDirection[robotCounter] = mDestination - mRobotNodeArr[robotCounter]->getPosition();
					mDistance[robotCounter] = mDirection[robotCounter].normalise();
				}
			}
		}
	}
	return BaseApplication::mouseReleased( arg, id );

}
/*!
\brief Key Press \n
Detect for key press.
*/
bool BasicTutorial_00::keyPressed( const OIS::KeyEvent &arg )
{
	/**
	Press Key
	- M
	  - Open/Close particle system
	*/
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

        Vector3 pos = mCameraMan->getCamera()->getPosition();
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

	if (arg.key == OIS::KC_M ) {
		ParticleOn = !ParticleOn;
		for(int i=0; i<60; i++) {
			robotParticle[i]->setEmitting(ParticleOn);
		}
	}

    BaseApplication::keyPressed(arg);

    return flg;
}
/*!
\brief Key Released \n
Detect for key release.
*/
bool BasicTutorial_00::keyReleased( const OIS::KeyEvent &arg )
{
    bool flg = true;
    stringstream ss;
    ss << arg.key;
    String msg;
    ss >> msg;
    msg += ":*** keyReleased ***\n";
    
    Ogre::LogManager::getSingletonPtr()->logMessage( msg );

    BaseApplication::keyReleased(arg);

    return flg;
}
/*!
\brief Frame Started
*/
bool BasicTutorial_00::frameStarted(const Ogre::FrameEvent& evt)
{
	bool flg = Ogre::FrameListener::frameStarted(evt);

	/** light rotate */
	float rotAngle=40*evt.timeSinceLastFrame;
	mRotLightNode->yaw(Degree(rotAngle), Node::TS_PARENT);
	/**
	handling robots walking
	- if robot walk = true
	  - walk speed = 80
	  - If distance < 0
	    - Robot set position = destination
		- Direction = Zero
		- Robot walk = false
		- Show bounding box = false
		- If all robots is stopped
			- play sound
	  - Else
		- Robot walk
		- Collision handle
		  - if collision, walking reverse a little bit
	- Else
	  - robot walk = false
	  - robot animation = Idle
	*/
	for (int robotCounter=0; robotCounter<60; robotCounter++)
	{
		if (isRobotWalk[robotCounter])
		{
			mAnimationState[robotCounter] = mRobotEntArr[robotCounter]->getAnimationState("Walk");
			//determine how far to move this frame
			float mWalkSpeed = 80.0;
			float move = mWalkSpeed * evt.timeSinceLastFrame;
			mDistance[robotCounter] -= move;
			// robot stop
			if (mDistance[robotCounter] <= 0.0f)
			{
				//Check to see if we've arrived at a waypoint
				//set our node to the destination we've just reached & reset direction to 0
				mRobotNodeArr[robotCounter]->setPosition(mDestination);
				mDirection[robotCounter] = Vector3::ZERO;
				isRobotWalk[robotCounter] = false;          
				mRobotNodeArr[robotCounter]->showBoundingBox(false);
				//playSound
				int totalRobotIsWalking = 0;
				for (int a=0; a<60; a++)
				{
					if (isRobotWalk[a])
					{
						totalRobotIsWalking++;
					}
				}
				if (totalRobotIsWalking==0)
				{
					mSound->play();
				}
			}
			// robot walk
			else
			{
				//check if collide
				Real distanceBetweenRobotAndSphere = mRobotNodeArr[robotCounter]->getPosition().distance(Ogre::Vector3(0, 50, 0));
				Real distanceThreshold = 90.0;
				robotCollisionHandle();
				if (distanceBetweenRobotAndSphere < distanceThreshold)
				{
					mRobotNodeArr[robotCounter]->translate(mRobotNodeArr[robotCounter]->getPosition() * evt.timeSinceLastFrame);
				}
				else
				{
					//movement code goes here
					mRobotNodeArr[robotCounter]->translate(mDirection[robotCounter] * move);
				}
				mDirection[robotCounter] = mDestination - mRobotNodeArr[robotCounter]->getPosition();
				mDistance[robotCounter] = mDirection[robotCounter].normalise();

				//Rotation code goes here
				Vector3 src = mRobotNodeArr[robotCounter]->getOrientation() * Vector3::UNIT_X;
				src.y=0;
				mDirection[robotCounter].y=0;
				src.normalise();
				//mDistance[robotCounter] = mDirection[robotCounter].normalise();
				// fix the divide by zero error bug
				if (abs(1.0f + src.dotProduct(mDirection[robotCounter])) < 0.0001f)
				{
					mRobotNodeArr[robotCounter]->yaw(Degree(180));
				}
				else
				{
					Quaternion quat = src.getRotationTo(mDirection[robotCounter]);
					mRobotNodeArr[robotCounter]->rotate(quat);
				}
			}
		}
		else
		{	
			mAnimationState[robotCounter] = mRobotEntArr[robotCounter]->getAnimationState("Idle");
		}
		mAnimationState[robotCounter]->addTime(evt.timeSinceLastFrame);
		mAnimationState[robotCounter]->setLoop(true);
		mAnimationState[robotCounter]->setEnabled(true);
	}
    return flg;
}
/*! Robot Collision Handle */
void BasicTutorial_00::robotCollisionHandle(){
	for(int i=0; i<60; i++) {
		for(int j=i+1; j<60; j++) {
			Vector3 Dist = mRobotNodeArr[i]->getPosition() - mRobotNodeArr[j]->getPosition();
			Real collisionDist=40;
			if(mRobotNodeArr[i]->getName()=="robot0"||mRobotNodeArr[j]->getName()=="robot0")
				collisionDist=60;
			if(Dist.length() < collisionDist) {
				Real between = collisionDist-Dist.length();
				Dist.normalise();
				Dist.y=0;
				mRobotNodeArr[i]->translate(between*Dist*0.5);
				mRobotNodeArr[j]->translate(between*Dist*-0.5);
			}
		}
	}
}
/** Add Particle System */
void BasicTutorial_00::addParticleSystem(){
	for(int i=0; i<60; i++){
		String partName;
		genNameUsingIndex("robotPart", i, partName);
		robotParticle[i] = mSceneMgr->createParticleSystem(partName, "Examples/GreenyNimbus");
		mRobotNodeArr[i]->attachObject(robotParticle[i]);
	}
}

int main(int argc, char *argv[]) {
	BasicTutorial_00 app;
	app.go();  
	return 0;
}

////////////////////////////////////////
// DO NOT DELETE THIS LINE: 2018/09/20. 3D Game Programming
////////////////////////////////////////