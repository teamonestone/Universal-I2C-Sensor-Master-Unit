// associated header
#include <ObjectManagementEngine.h>

//////////////////////
// public functions //
//////////////////////

void* OME::GetFreeObjPrt(int16_t *poolNo) {
    for (int16_t i = 0; i < OME_OBJ_POOL_SIZE; i++) {
        if (!inUse[i]) {
            inUse[i] = true;
            if (poolNo != nullptr) {
                *poolNo = i;
            }
            return ConvertNoToPtr(i);
        }
    }
    if (poolNo != nullptr) {
        *poolNo = -1;
    }
    return nullptr;
}

bool OME::FreePtr(void *objPrt) {
    int16_t poolNo = ConvertPrtToNo(objPrt);
    if (poolNo >= OME_OBJ_POOL_SIZE || poolNo < 0) {
        return false;
    }
    inUse[poolNo] = false;
    return true;
}

bool OME::FreePtr(int16_t poolNo) {
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

uint8_t BytePool[OME_OBJ_POOL_SIZE * OME_OBJ_SIZE] = {0};
bool inUse[OME_OBJ_POOL_SIZE] = {0};

void* OME::ConvertNoToPtr(int16_t poolNo) {
    if (poolNo >= OME_OBJ_POOL_SIZE || poolNo < 0) {
        return nullptr;
    }
    else {
        return BytePool + (poolNo * OME_OBJ_SIZE);
    }
}

int16_t OME::ConvertPrtToNo(void *objPtr) {
    int16_t poolNo = -1;
    for (int16_t i = 0; i < OME_OBJ_POOL_SIZE; i++) {
        if (ConvertNoToPtr(i) == objPtr) {
            poolNo = i;
            break;
        }
    }
    return poolNo;
}