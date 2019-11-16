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

class BasicTutorial_00 : public BaseApplication
{
public:
	BasicTutorial_00(void);
    virtual void chooseSceneManager(void);
    virtual void createCamera(void);
	virtual void createViewports(void);
	virtual void createScene(void);
	
	
    //
    virtual bool frameStarted(const Ogre::FrameEvent& evt);
    //
    // Add your own stuff.
    //
protected:
	void createViewport_00(void);
	void createViewport_01(void);
	/*!
	\brief Create a Camera
	Create a camera on a viewport
	*/
	void createCamera_00();
	void createCamera_01();
	/*!
	\brief Create a Scene
	\fn 
	*/
	void createScene_00();
	void createScene_01();
	/*!
	\brief Detect for key input
	
	*/
    bool keyPressed( const OIS::KeyEvent &arg );
    bool keyReleased( const OIS::KeyEvent &arg );
    /*!
	\brief Create Light
	Create a light on the Scene
	*/
	void lighting00();
	void lighting01();
protected:
    Ogre::Viewport* mViewportArr[8];
	Ogre::Camera* mCameraArr[8];
	Ogre::SceneManager* mSceneMgrArr[8];
	OgreBites::SdkCameraMan* mCameraManArr[8];
};


#endif // #ifndef __BasicTutorial_00_h_