//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
/*!
\brief 3D Game Programming
\n
My Name: Yu-Chen Hsiao
\n
My ID: 0616221
\n
My Email: ychsiao@cs.nctu.edu.tw
\n Date: 2019/09/20
This is an assignment of 3D Game Programming
*/

////////////////////////////////////////
// You can delete or add some functions to do the assignment.
////////////////////////////////////////

#ifndef __BasicTutorial_00_h_
#define __BasicTutorial_00_h_

#include "BaseApplication.h"
#include "selection_rectangle.h"
#include "sound.h"

using namespace Ogre;

class BasicTutorial_00 : public BaseApplication
{
public:
	BasicTutorial_00(void);
    virtual void chooseSceneManager(void);
    virtual void createCamera(void);
	virtual void createViewports(void);
	virtual void createScene(void);	
    //
	virtual bool mouseMoved( const OIS::MouseEvent &arg );
	virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
	virtual bool keyPressed( const OIS::KeyEvent &arg );
	virtual bool keyReleased( const OIS::KeyEvent &arg );
	virtual bool frameStarted(const Ogre::FrameEvent& evt);

protected:
	void createViewport_00(void);
	void createViewport_01(void);
	void createCamera_00();
	void createCamera_01();
	void createLight_00();
	void createLight_01();
	void createCircleOfObject(Ogre::String, Ogre::String, int, double);
	void createScene_00();
	void createScene_01();
private:
    Ogre::Viewport* mViewportArr[8];
	Ogre::Camera* mCameraArr[8];
	Ogre::SceneManager* mSceneMgrArr[8];
	OgreBites::SdkCameraMan* mCameraManArr[8];
	Ogre::SceneNode* mRotLightNode;
	Ogre::SceneNode* mRobotNodeArr[128];
	Ogre::Entity* mRobotEntArr[128];
	float mDistance[128];
	Vector3 mDirection[128];
	Vector3 mDestination;
	bool isRobotWalk[128];
	/* Volume Select */
	PlaneBoundedVolumeListSceneQuery *mVolQuery;
	Real left,right,top,bottom;
	SelectionRectangle* mSelectionRect;
	SceneNode *mCurrentObject;
	/* Animation */
	AnimationState* mAnimationState[128];
	bool isMousePressed;
	/* Collision Handle */
	void robotCollisionHandle();
	/* Partical system */
	ParticleSystem* robotParticle[128];
	void addParticleSystem();
	bool ParticleOn;
	/*! Sound */
	SOUND *mSound;
};


#endif // #ifndef __BasicTutorial_00_h_