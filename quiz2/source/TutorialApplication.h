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
My Email: aaa@cs.nctu.edu.tw
\n Date: 2019/10/28

This is an assignment of 3D Game Programming

*/

#ifndef __BasicTutorial_00_h_
#define __BasicTutorial_00_h_

#include "BaseApplication.h"

using namespace Ogre;

class BasicTutorial_00 : public BaseApplication
{
public:
	BasicTutorial_00(void);
	virtual void createViewports(void);
	virtual void createScene(void);
	virtual void createCamera(void);
	virtual void chooseSceneManager(void);
    //
	virtual bool frameStarted(const Ogre::FrameEvent& evt);
    //
protected:
	/*!
	\brief Create a viewport

	Create a viewport for the entire screen.

	\return The sum of two integers.
	*/
	void createViewport_00(void);
	void createViewport_01(void);
	//
	void createCamera_00();
	void createCamera_01();

	void createScene_00();
	void createScene_01();
    bool keyPressed( const OIS::KeyEvent &arg );
    bool keyReleased( const OIS::KeyEvent &arg );
    void createBarrelsWall();
	void createSpace();
	void recreateSpace(int num);
	
    void resolveCollisionSmallSpheres();
    void resolveCollisionLargeSphere();
	void resolveCollisionBarrels();
    void resolveCollision(
    SceneNode *nodeA, SceneNode *nodeB,
    float rA, float rB);
    void resolveCollision(
    SceneNode *nodeA, SceneNode *nodeB,
    float rA, float rB, float wA, float wB);
    void resolveCollision();
    void resolveCollisionPair(
    int robotA, int robotB, float rA, float rB);

    void reset();
protected:
    Ogre::Viewport* mViewportArr[8];
	Ogre::Camera* mCameraArr[8];
	Ogre::SceneManager* mSceneMgrArr[8];
	OgreBites::SdkCameraMan* mCameraManArr[8];
    //
    bool mFlg_Penguin_Jump;
    bool mFlg_Penguin_Dir;
    //
    bool mFlg_Root;
    bool mFlg_Root_Dir;
    bool mFlg_Arm;
    bool mFlg_Arm_Dir;
    //
    int mMoveDirection;
    SceneNode *mLargeSphereSceneNode;
    Entity *mLargeSphereEntity;
	// Big Sphere
	SceneNode *mSphere_node;
	Entity *mSphere_ent;
	// Small Spheres
    int mNumSpheres;
    SceneNode *mSpheresNode[1024];
    Entity *mSpheresEnt[1024];
	// Barrels
	int mNumBarrels;
	Real barrelRadius;
	SceneNode *mBarrelsNode[1024];
	Entity *mBarrelsEnt[1024];
};

#endif // #ifndef __BasicTutorial_00_h_