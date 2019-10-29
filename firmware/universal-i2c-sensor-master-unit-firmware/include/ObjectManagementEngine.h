#ifndef ObjectManagementEngine_h
#define ObjectManagementEngine_h

//////////////
// Includes //
//////////////
#include <inttypes.h>

/////////////
// Defines //
/////////////

// define for object size (in bytes)
#define OME_OBJ_SIZE 64

// definie for pool size 
#define OME_OBJ_POOL_SIZE 8

///////////////
// OME-Class //
///////////////

class OME
{
// Begin PUBLIC ------------------------------------------------------------------
	public:
        
        // get a free ptr
        static void* GetFreeObjPrt(int16_t *poolNo);
        
        // free a used ptr
        static bool FreePtr(void *objPrt);
        static bool FreePtr(int16_t poolNo);

// End PUBLIC --------------------------------------------------------------------

// Begin PRIVATE -----------------------------------------------------------------
	private:
        
        // reserved memeory to store the objects in
        static uint8_t BytePool[OME_OBJ_POOL_SIZE * OME_OBJ_SIZE];

        // managment stuff
        static bool inUse[OME_OBJ_POOL_SIZE];

        // constructor -> no instance can be created
        OME();
        ~OME();

        static void* ConvertNoToPtr(int16_t poolNo);
        static int16_t ConvertPrtToNo(void *objPtr);

// End PRIVATE -------------------------------------------------------------------

};

#endif