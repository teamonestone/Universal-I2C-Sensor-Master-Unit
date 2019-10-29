#ifndef ObjectManagmentEngine_h
#define ObjectManagmentEngine_h

//////////////
// Includes //
//////////////
#include <inttypes.h>

/////////////
// Defines //
/////////////

// define for object size (in bytes)
#ifndef OME_OBJ_SIZE
    #define OME_OBJ_SIZE 512
#endif

// definie for pool size 
#ifndef OME_OBJ_POOL_SIZE
    #define OME_OBJ_POOL_SIZE 8
#endif

///////////////
// OME-Class //
///////////////

class OME
{
// Begin PUBLIC ------------------------------------------------------------------
	public:
        
        // get a free ptr
        static void* GetFreeObjPrt(int16_t *poolNo);
        
        static bool FreePtr(void *objPrt);
        static bool FreePtr(int16_t poolNo);
        


// End PUBLIC --------------------------------------------------------------------

// Begin PRIVATE -----------------------------------------------------------------
	private:

        ///////////////////////
        // "private" members //
        ///////////////////////
        
        // reserved memeory to store the objects in
        static uint8_t BytePool[OME_OBJ_POOL_SIZE * OME_OBJ_SIZE];

        // managment stuff
        static bool inUse[OME_OBJ_POOL_SIZE];


        /////////////////////////
        // "private" functions //
        /////////////////////////

        // constructor -> no instance can be created
        OME();
        ~OME();

        static void* ConvertNoToPtr(int16_t poolNo);
        static int16_t ConvertPrtToNo(void *objPtr);


// End PRIVATE -------------------------------------------------------------------

};

/*
//////////////////////////////////////
// ObjectManagmentEngine namespaace //
//////////////////////////////////////

namespace OME {

    // anonymous namespace to hide the reserved memory and private stuff
    namespace {
        
        ///////////////////////
        // "private" members //
        ///////////////////////
        
        // reserved memeory to store the objects in
        uint8_t BytePool[OME_OBJ_POOL_SIZE * OME_OBJ_SIZE];
        void *ObjectPoolPtr = &BytePool;

        // managment stuff
        bool inUse[OME_OBJ_POOL_SIZE] = {0};


        /////////////////////////
        // "private" functions //
        /////////////////////////

        void* ConvertNoToPtr(int16_t poolNo) {

            // check if out of bonds
            if (poolNo >= OME_OBJ_POOL_SIZE || poolNo < 0) {
                return nullptr;
            }
            else {
                return ObjectPoolPtr + (poolNo * OME_OBJ_SIZE);
            }
        }

        int16_t ConvertPrtToNo(void *objPtr) {

            int16_t poolNo = -1;
            
            for (int16_t i = 0; i < OME_OBJ_POOL_SIZE; i++) {
                if (ConvertNoToPtr(i) == objPtr) {
                    poolNo = i;
                    break;
                }
            }

            return poolNo;
        }
    }

    // get a free ptr
    void* GetFreeObjPrt(int16_t *poolNo) {

        for (int16_t i = 0; i < OME_OBJ_POOL_SIZE; i++) {
            if (!inUse[i]) {
                inUse[i] = true;
                *poolNo = i;
                return ConvertNoToPtr(i);
            }
        }

        *poolNo = -1;
        return nullptr;
    }

    bool FreePtr(void *objPrt) {

        int16_t poolNo = ConvertPrtToNo(objPrt);

        // check if out of bonds
        if (poolNo >= OME_OBJ_POOL_SIZE || poolNo < 0) {
            return false;
        }

        inUse[poolNo] = false;
        return true;
    }

    bool FreePtr(int16_t poolNo) {

        // check if out of bonds
        if (poolNo >= OME_OBJ_POOL_SIZE || poolNo < 0) {
            return false;
        }

        inUse[poolNo] = false;
        return true;
    }
}
*/

#endif