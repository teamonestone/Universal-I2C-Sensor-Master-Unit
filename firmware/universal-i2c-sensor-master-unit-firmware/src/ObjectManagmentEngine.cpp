// associated header
#include <ObjectManagmentEngine.h>

//////////////////////
// public functions //
//////////////////////

static void* OME::GetFreeObjPrt(int16_t *poolNo) {

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

static bool OME::FreePtr(void *objPrt) {

    int16_t poolNo = ConvertPrtToNo(objPrt);

    // check if out of bonds
    if (poolNo >= OME_OBJ_POOL_SIZE || poolNo < 0) {
        return false;
    }

    inUse[poolNo] = false;
    return true;
}

static bool OME::FreePtr(int16_t poolNo) {

    // check if out of bonds
    if (poolNo >= OME_OBJ_POOL_SIZE || poolNo < 0) {
        return false;
    }

    inUse[poolNo] = false;
    return true;
}

///////////////////////
// private functions //
///////////////////////

OME::OME() {};
OME::~OME() {};

static void* OME::ConvertNoToPtr(int16_t poolNo) {

    // check if out of bonds
    if (poolNo >= OME_OBJ_POOL_SIZE || poolNo < 0) {
        return nullptr;
    }
    else {
        return BytePool + (poolNo * OME_OBJ_SIZE);
    }
}

static int16_t OME::ConvertPrtToNo(void *objPtr) {

    int16_t poolNo = -1;
    
    for (int16_t i = 0; i < OME_OBJ_POOL_SIZE; i++) {
        if (ConvertNoToPtr(i) == objPtr) {
            poolNo = i;
            break;
        }
    }

    return poolNo;
}