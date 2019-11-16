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

using namespace Ogre;

/*!
 \brief Variable
 \param [in] action Trigger the rotation of small penguin
 \param [in] radius Radius of rotation of small penguin
 \param [in] mAngle Initial rotation angle of small penguin
 \param [in] mAngularSpeed Initial rotation speed of small penguin
 \param [in] mAngularAcceleration Rotation acceleration of small penguin
 \param [in] clockwise  Rotation in clockwise(-1) or counterClockwise(1)
 */

const float PI = 3.141592654;
int action = false;
// small Penguin action variable
double radius = 150;
double mAngle = 0;
double mAngularSpeed = 0;
double mAngularAcceleration = 5;
int clockwise = 1;

/*!
 \brief Function
 */

/*! \brief Constructor */
BasicTutorial_00::BasicTutorial_00(void) {}
/*! \brief Create SceneManager */
void BasicTutorial_00::chooseSceneManager()
{
	/**
	SceneMgr[0]\n
	SceneMgr[1]
	*/
	mSceneMgrArr[0] = mRoot
		->createSceneManager(ST_GENERIC, "primary");
	
	mSceneMgrArr[1] = mRoot
		->createSceneManager(ST_GENERIC, "secondary");
}
/*!
\brief Create Camera_00 \n
Create Camera on Scene_00
*/
void BasicTutorial_00::createCamera_00(void)
{
	/*
	Camera_00
	- Name: PlayerCam
	- Position: (120,300,600)
	- lookAt: (120,0,0)
	- NearClipDistance: 5
	- create a default camera controller
	*/
	mSceneMgr = mSceneMgrArr[0];
	mCamera = mCameraArr[0] = mSceneMgr->createCamera("PlayerCam");
	mCamera->setPosition(Ogre::Vector3(120,300,600));
	mCamera->lookAt(Ogre::Vector3(120,0,0));
	mCamera->setNearClipDistance(5);
	mCameraManArr[0] = new OgreBites::SdkCameraMan(mCamera);
}
/*!
\brief Create Camera_01 \n
Create Camera on Scene_01
*/
void BasicTutorial_00::createCamera_01(void)
{
	/**
	create Camera_01
	- Name: PlayerCam
	- Position: (0,350,0.001)
	- lookAt: (0,0,0)
	- NearClipDistance: 5
	- create a default camera controller
	*/
	mSceneMgr = mSceneMgrArr[1];
	mCamera = mCameraArr[1] = mSceneMgr->createCamera("PlayerCam2");
	mCamera->setPosition(Ogre::Vector3(0,350,0.001));
	mCamera->lookAt(Ogre::Vector3(0,0,0));
	mCamera->setNearClipDistance(5);
	mCameraManArr[1] = new OgreBites::SdkCameraMan(mCamera);
}
/*!
\brief Create Viewport_00 \n
Create viewport[0] for the entire screen.
*/
void BasicTutorial_00::createViewport_00(void)
{
	/**
	ViewPort_00
	- Camera: camera[0]
	- Z-order: 0
	- left: 0
	- top: 0
	- width: 100%
	- height: 100%
	- background color: blue(0,0,1)
	- aspect ratio: Viewport actual width / Viewport actual height
	*/
	mCamera = mCameraArr[0];
	Ogre::Viewport *vp = mViewportArr[0] = mWindow->addViewport(mCamera, 0, 0.0, 0.0, 1.0, 1.0);
	vp->setBackgroundColour(Ogre::ColourValue(0,0,1));
	mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth())/Ogre::Real(vp->getActualHeight()));
}
/*!
\brief Create Viewport_01 \n
Create viewport[1] for the entire screen.
*/
void BasicTutorial_00::createViewport_01(void)
{
	/**
	ViewPort_01
	- Camera: camera[1]
	- Z-order: 1
	- left: 0
	- top: 0
	- width: 25%
	- height: 25%
	- background color: white(1,1,1)
	- overlays: false
	- aspect ratio: Viewport actual width / Viewport actual height
	*/
	mCamera = mCameraArr[1];
	Ogre::Viewport *vp = mViewportArr[1] = mWindow->addViewport(mCamera, 1, 0.0, 0.0, 0.25, 0.25);
	vp->setBackgroundColour(Ogre::ColourValue(1,1,1));
	vp->setOverlaysEnabled(false);
	mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth())/Ogre::Real(vp->getActualHeight()));
}
/*!
\brief Create light_00 \n
Create two light on the entire screen1.
*/
void BasicTutorial_00::lighting00(){
	/**
	Light at right
	- Name: Light1
	- type: LT_POINT
	- Position: (150,250,100)
	- Diffuse: green(0,1,0)
	- Specular: green(0,1,0)
	*/
	mSceneMgr = mSceneMgrArr[0];
	Light *light = mSceneMgr->createLight("Light1");
	light->setType(Light::LT_POINT); 
	light->setPosition(Vector3(150, 250, 100)); 
	light->setDiffuseColour(0, 1, 0);
	light->setSpecularColour(0, 1, 0);
	/**
	Light at left
	- Name: Light2
	- type: LT_POINT
	- Position: (-150,300,250)
	- Diffuse: white(0.9,0.9,0.9)
	- Specular: pink(0.7,0,1)
	*/
	Light *light2 = mSceneMgr->createLight("Light2");
	light2->setType(Light::LT_POINT);
	light2->setPosition(Vector3(-150, 300, 250));
	light2->setDiffuseColour(0.9, 0.9, 0.9);
	light2->setSpecularColour(0.7, 0, 1);
}
/*!
\brief Create light_01 \n
Create a blue light on the entire screen2.
*/
void BasicTutorial_00::lighting01(){
	/**
	Light
	- Name: Light2
	- type: LT_POINT
	- Position: (100,150,250)
	- Diffuse: blue(0,0,1)
	- Specular: blue(0,0,1)
	*/
	mSceneMgr = mSceneMgrArr[1];
	Light *light = mSceneMgr->createLight("Light1");
	light->setType(Light::LT_POINT); 
	light->setPosition(Vector3(100, 150, 250)); 
	light->setDiffuseColour(0, 0, 1);
	light->setSpecularColour(0, 0, 1);
}
/*!
\brief Create Scene_00 \n
Create a Scene with two Penguin and some cubes.
*/
void BasicTutorial_00::createScene_00(void) 
{
	/**
	Scene_00 \n
	AmbientLight: (0.4,0.4,0.4) \n
	Shadow: enable \n
	Light: light_00 \n
	Plane
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
	*/
	mSceneMgr = mSceneMgrArr[0];
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.4,0.4,0.4));
	mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);

	lighting00();

	Plane plane(Vector3::UNIT_Y, 0);

	MeshManager::getSingleton().createPlane(
		"ground",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane,
		1500,1500,
		20,20,
		true,
		1,
		5,5,
		Vector3::UNIT_Z
	);

	Ogre::Entity *ent_plane = mSceneMgr->createEntity("Ground", "ground");
	mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode("PlaneNode")
		->attachObject(ent_plane);
	/*! Penguins */
	/**
	 - Large Penguins
	 * - Entity: largePenguin
	 * - SceneNode: LargePenguinNode
	 * - Scale: (2,3,2)
	 * - Position: (0, 50, 0)
	 */
	Vector3 largePenguin_pos(0, 50, 0);
	Ogre::Entity *largePenguin_ent = mSceneMgr->createEntity("largePenguin", "penguin.mesh");
	Ogre::SceneNode *largePenguin_node = mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode("LargePenguinNode");
	largePenguin_node->setScale(2,3,2);
	largePenguin_node->setPosition(largePenguin_pos);
	largePenguin_node->attachObject(largePenguin_ent);
	/**
	 - Small Penguin
	 * - Entity: smallPenguin
	 * - SceneNode: SmallPenguinNode
	 * - Scale: (1,1,1)
	 * - Position: (radius,20,0)  // radius = 150
	 * - yaw: -90 deg
	 */
	Vector3 smallPenguin_pos(radius, 20, 0);
	Radian angle(PI/2.0);
	Ogre::Entity *smallPenguin_ent = mSceneMgr->createEntity("smallPenguin", "penguin.mesh");
	Ogre::SceneNode *smallPenguin_node = mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode("SmallPenguinNode");
	smallPenguin_node->setScale(1,1,1);
	smallPenguin_node->setPosition(smallPenguin_pos);
	smallPenguin_node->yaw(-1*angle);
	smallPenguin_node->attachObject(smallPenguin_ent);

	/*! Cubes */
	int numCubes = 72;
	double L = 255;
	/**
	 - Circle
	   - i from 0 to numCubes-1
	   - fx: i/(numCubes-1)
	   - range: [0,1]
	   - height: (1+sin(fx*PI*4))*50
	   - circle radius: 100
	   - position x: circle_radius*cos(fx*PI*2)
	   - position z: circle_radius*sin(fx*PI*2)
	   - size of cube: 1.0/cubeSize/numCubes*L*0.8
	   - scaling: (unitF, h/cubeSize, unitF)
	   - set position: (x1, 50, z1)
	 */
	for (int i = 0; i < numCubes; ++i) {
		String name;
		genNameUsingIndex("c_circle", i, name);
		Entity *ent = mSceneMgr->createEntity(name, "cube.mesh");
		ent->setMaterialName("Examples/SphereMappedRustySteel");
		AxisAlignedBox bb =  ent->getBoundingBox();
		double cubeSize = bb.getMaximum().x - bb.getMinimum().x;
		SceneNode *snode = mSceneMgr
			->getRootSceneNode()
			->createChildSceneNode();
		snode->attachObject(ent);
		double fx = i/(double) (numCubes-1);
		double h = (1+sin(fx*PI*4))*50;
		double circle_radius = 100;
		double x1 = circle_radius*cos(fx*PI*2);
		double z1 = circle_radius*sin(fx*PI*2);
		double unitF = 1.0/cubeSize/numCubes*L*0.8;
		snode->scale(unitF, h/cubeSize, unitF);
		snode->setPosition(x1, 50, z1);
	}
	/**
	 - Row
	   - i from 0 to numCubes-1
	   - unitF = 1.0/cubeSize/numCubes*L*0.8
	   - fx: i/(numCubes-1)
	   - height: (1+cos(fx*3.1415*2.0))*20
	   - position x: fx*L - L/2.0
	   - position z: 150
	   - size of cube: 1.0/cubeSize/numCubes*L*0.8
	   - scaling: (unitF, h/cubeSize, unitF)
	   - set position: (x, 20, z)
	 */
	for (int i = 0; i < numCubes; ++i) {
		String name;
		genNameUsingIndex("c_row", i, name);
		Entity *ent = mSceneMgr->createEntity(name, "cube.mesh");
		ent->setMaterialName("Examples/Chrome");
		AxisAlignedBox bb =  ent->getBoundingBox();
		double cubeSize = bb.getMaximum().x - bb.getMinimum().x;
		SceneNode *snode = mSceneMgr
			->getRootSceneNode()
			->createChildSceneNode();
		snode->attachObject(ent);
		double fx = 2*i/(double) (numCubes-1);
		double h = (1+cos(fx*3.1415*2.0))*20;
		double x = fx*L - L/2.0;
		double z = 150;
		Real unitF = 1.0/cubeSize/numCubes*L*0.8;
		snode->scale(unitF, h/cubeSize, unitF);
		snode->setPosition(x, 20, z);
	}
}
/*!
\brief Create Scene_01 \n
Create a Scene with a sphere.
*/
void BasicTutorial_00::createScene_01(void) 
{
	/**
	Scene_01 \n
	AmbientLight: (0,0,0) \n
	Shadow: enable \n
	Light: light_01 \n
	\param [out] Plane plane
	- Name: Ground2
	- width: 500
	- height: 500
	- x-segments: 20
	- y-segments: 20
	- normal: true
	- num texture sets: 1
	- x-tiles: 5
	- y-tiles: 5
	- vector: UNITZ(0,0,1)
	*/
    mSceneMgr = mSceneMgrArr[1];
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0,0,0));
	mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);
	lighting01();
	/**
	Plane
	- Entity: gournd2(Ground2)
	- SceneNode: PlaneNode2
	*/
	Plane plane(Vector3::UNIT_Y, 0);
	MeshManager::getSingleton().createPlane(
		"ground2", 										
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, 
		plane, 
		500,500,
		20,20,
		true,
		1,
		5,5,
		Vector3::UNIT_Z
	);
	Ogre::Entity *ent_plane2 = mSceneMgr->createEntity("Ground2", "ground2");
	mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode("PlaneNode2")
		->attachObject(ent_plane2);
	/**
	Sphere
	- Entity: Sphere(sphere.mesh)
	- Material: Examples/green
	- SceneNode: sphereNode
	- Position: (0,50,0)
	- Scale: (0.25,0.25,0.25)
	*/
	Vector3 pos(0, 50, 0);
	Ogre::Entity *sphere_ent = mSceneMgr->createEntity("Sphere", "sphere.mesh");
	sphere_ent->setMaterialName("Examples/green");
	Ogre::SceneNode *sphere_node = mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode("SphereNode",pos);
	sphere_node->setScale(0.25,0.25,0.25);
	sphere_node->attachObject(sphere_ent);
}
/*! \brief Create Viewports*/
void BasicTutorial_00::createViewports(void)
{
	/**
	- Viewport_00
	- Viewport_01
	*/
	createViewport_00();
	createViewport_01();
}
/*! \brief Create Cameras*/
void BasicTutorial_00::createCamera(void) {
	/*
	- Camera_00
	- Camera_01
	CameraMan: Camera_00
	*/
	createCamera_00();
	createCamera_01();
	mCameraMan = mCameraManArr[0];
	//mCameraMan = mCameraManArr[1];
}
/*! \brief Create Scene*/
void BasicTutorial_00::createScene( void ) {
	/**
	- Scene_00
	- Scene_01
	*/
	createScene_00();
	createScene_01();
	/** SceneManeger: Scene_00 */
	mSceneMgr = mSceneMgrArr[0];
	/** Camera: Camera_00 */
    mCamera = mCameraArr[0];
}
/*!
\brief Key Press \n
Detect for key press.
*/
bool BasicTutorial_00::keyPressed( const OIS::KeyEvent &arg )
{
	/**
	Press Key
	- 1
	  - Camera Position: (98.14, 450.69, 964.20)
	  - Camera Direction: (-0.01, -0.30, -0.95)
	- 2
	  - Camera Position: (-1463.00, 606.45, -513.24)
	  - Camera Direction: (0.88, -0.47, 0.10)
	- 3
	  - Camera Position: (-1356.16, 634.32, -964.51)
	  - Camera Direction: (0.71, -0.44, 0.55)
	- 4
	  - Camera Position: (40.39, 155.23, 251.20)
	  - Camera Direction: (-0.02, -0.41, -0.91)
	- 5
	  - Camera Position: (19.94, 822.63, 30.79)
	  - Camera Direction: (0.00, -0.99, -0.11)
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
    if (arg.key == OIS::KC_1 ) {
        mCameraMan->getCamera()
            ->setPosition(Vector3(98.14, 450.69, 964.20));
        mCameraMan->getCamera()
            ->setDirection(Vector3(-0.01, -0.30, -0.95));
    }
    if (arg.key == OIS::KC_2 ) {
        mCameraMan->getCamera()
            ->setPosition(Vector3(-1463.00, 606.45, -513.24));
        mCameraMan->getCamera()
            ->setDirection(Vector3(0.88, -0.47, 0.10));
    }
    if (arg.key == OIS::KC_3 ) {
        mCameraMan->getCamera()
            ->setPosition(Vector3(-1356.16, 634.32, -964.51));
        mCameraMan->getCamera()
            ->setDirection(Vector3(0.71, -0.44, 0.55));
    }
    if (arg.key == OIS::KC_4 ) {
        mCameraMan->getCamera()
            ->setPosition(Vector3(40.39, 155.23, 251.20));
        mCameraMan->getCamera()
            ->setDirection(Vector3(-0.02, -0.41, -0.91));
    }
    if (arg.key == OIS::KC_5 ) {
        mCameraMan->getCamera()
            ->setPosition(Vector3(19.94, 822.63, 30.79));
        mCameraMan->getCamera()
            ->setDirection(Vector3(0.00, -0.99, -0.11));
    }
	/**
	  - M
	    - remove viewports z-order
	    - set Viewport_01 z-order to 0
	    - set Viewport_00 z-order to 1
	    - set Viewport_00 background color to green(0,1,0)
	  */
    if (arg.key == OIS::KC_M ) {
    	// remove viewports z-order
		mWindow->removeViewport(mViewportArr[0]->getZOrder());
		mWindow->removeViewport(mViewportArr[1]->getZOrder());
		// set Viewport_01 z-order to 0
		Ogre::Viewport *vp;
		mCamera = mCameraArr[1];
		vp = mWindow->addViewport(mCamera, 0, 0.0, 0.0, 1.0, 1.0);
		vp->setBackgroundColour(Ogre::ColourValue(1,1,1));
		mCamera->setAspectRatio(
			Ogre::Real(vp->getActualWidth())/Ogre::Real(vp->getActualHeight()));
		mViewportArr[1] = vp;
		// set Viewport_00 z-order to 1
		mCamera = mCameraArr[0];
		vp = mWindow->addViewport(mCamera, 1, 0, 0, 0.25, 0.25);
		// set Viewport_00 background color to green(0,1,0)
		vp->setBackgroundColour(Ogre::ColourValue(0,1,0));
		mCamera->setAspectRatio(
			Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
		// save pointer
		mViewportArr[0] = vp;

		mCameraMan = mCameraManArr[1];
    }
    /**
  	  - N
		- delete viewports z-order
  	    - set Viewport_00 z-order to 0
	    - set Viewport_01 z-order to 1
	    - set Viewport_00 background color to red(1,0,0)
	    - set Viewport_01 posistion
	      - left: 75%
	      - top: 25%
	      - width: 0.25
	      - height: 0.25
	    - Viewport_01 disable overlay
  	  */
    if (arg.key == OIS::KC_N ) {
    	// delete viewports z-order
		mWindow->removeViewport(mViewportArr[0]->getZOrder());
		mWindow->removeViewport(mViewportArr[1]->getZOrder());
		// set Viewport_00 z-order to 0
		Ogre::Viewport *vp;
		mCamera = mCameraArr[0];
		vp = mWindow->addViewport(mCamera, 0, 0.0, 0.0, 1.0, 1.0);
		// set backgroundColour as red
		vp->setBackgroundColour(Ogre::ColourValue(1,0,0));
		mCamera->setAspectRatio(
			Ogre::Real(vp->getActualWidth())/Ogre::Real(vp->getActualHeight()));
		mViewportArr[0] = vp;
		// set Viewport_01 position
		vp = mWindow->addViewport(mCamera, 1, 0.75, 0.25, 0.25, 0.25);
		// disable overlay
		vp->setOverlaysEnabled(false);
		vp->setBackgroundColour(Ogre::ColourValue(1,1,1));
		mCamera->setAspectRatio(
			Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
		// save pointer
		mViewportArr[1] = vp;
		
		mCameraMan = mCameraManArr[0];
    }
	/**
	 - P
	   - action = !action
	*/
	if (arg.key == OIS::KC_P ) {
		action = !action;
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
/*
\brief Frame Started \n
Small penguin spin start.
*/
bool BasicTutorial_00::frameStarted(const Ogre::FrameEvent& evt)
{
	bool flg = Ogre::FrameListener::frameStarted(evt);

	/**
	Small Penguin Action
	- Radius: 150
	- initial angle: 0
	- initial angularSpeed: 0
	- angularAccelerate: 20
	- situation
	  - angle accelerate
	    - angle < PI -> angularSpeed up
	    - angle >= PI -> angularSpeed down
	  - clockwise
	    - angle >= 2*PI -> clockwise
	    - angle <= 0 -> counter-clockwise
	*/
	if(action){
		mSceneMgr = mSceneMgrArr[0];
		Ogre::SceneNode *largePenguin_node = mSceneMgr->getSceneNode("LargePenguinNode");
		Ogre::SceneNode *smallPenguin_node = mSceneMgr->getSceneNode("SmallPenguinNode");

		// small penguin spin
		double x = radius * cos(mAngle);
		double z = radius * sin(mAngle);
		smallPenguin_node->setPosition(x, 20, z);
		largePenguin_node->lookAt(Ogre::Vector3(-x,50,-z), Node::TransformSpace::TS_WORLD);
		// Angle accelerate
		if(mAngle < PI){
			mAngularSpeed += clockwise*mAngularAcceleration*evt.timeSinceLastFrame;
		}
		else if(mAngle >= PI) {
			mAngularSpeed -= clockwise*mAngularAcceleration*evt.timeSinceLastFrame;
		}
		// clockwise | counter-clockwise
		if(mAngle >= 2*PI){
			clockwise = -1;
		}
		else if(mAngle <= 0){
			clockwise = 1;
		}
		// Angle change
		mAngle += clockwise*mAngularSpeed*evt.timeSinceLastFrame;
	}
    return flg;
}
int main(int argc, char *argv[]) {
	BasicTutorial_00 app;
	app.go();  
	return 0;
}

////////////////////////////////////////
// DO NOT DELETE THIS LINE: 2018/09/20. 3D Game Programming
////////////////////////////////////////