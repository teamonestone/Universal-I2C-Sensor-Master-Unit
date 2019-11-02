/**
 * @file ObjectManagementEngine.h
 * @brief The source file of the Object Management Engine class.
 * @author Jonas Merkle [JJM] <a href="mailto:jonas.merkle@tam-onestone.net">jonas.merkle@tam-onestone.net</a>
 * @author Dominik Authaler <a href="mailto:dominik.authaler@team-onestone.net">dominik.authaler@team-onestone.net</a>
 * @author
 * This library is maintained by <a href="https://team-onestone.net">Team Onestone</a>.
 * E-Mail: <a href="mailto:info@team-onestone.net">info@team-onestone.net</a>
 * @version 1.0.0
 * @date 31 October 2019
 * @copyright This project is released under the GNU General Public License v3.0
 */

// associated header
#include <ObjectManagementEngine.h>

///////////////////////
// private functions //
///////////////////////

/**
 * @brief Initialize the memory witch gets split into smaller memory slices.
 * 
 */
uint8_t OME::BytePool[OME_OBJ_POOL_SIZE_BYTES] = {0};

/**
 * @brief Initialize the Array with usage inforation.
 * 
 * @param argname desc
 * @return
 */
ObjInfo OME::ObjInfos[OME_OBJ_POOL_SIZE];

/**
 * @brief Main constructor of the class (private so no instance of this class can be created).
 * 
 */
OME::OME() {};

/**
 * @brief Main destructor of the class (private so no instance of this class can be created).
 * 
 */
OME::~OME() {};

/**
 * @brief Convert a pool object number in an actual pointer.
 * 
 * @param poolNo The pool object number.
 * @return The actual pointer as void*.
 */
void* OME::ConvertNoToPtr(int8_t poolNo, ERRORS::Code *errorCode) {
    if (!isInPoolRange(poolNo)) {
        if (errorCode != nullptr) {
            *errorCode = ERRORS::Code::OmePoolObjeOutOfRange;
        }
        return nullptr;
    }
    else {
        if (errorCode != nullptr) {
            *errorCode = ERRORS::Code::None;
        }
        return ObjInfos[poolNo].firstMemoryPtr;
    }
}

/**
 * @brief Convert an actual pointer in a pointer number.
 * 
 * @param objPtr The actual pointer.
 * @return The pointer number as int16_t.
 */
int8_t OME::ConvertPrtToNo(void *objPtr, ERRORS::Code *errorCode) {
    if(!isInMemoryRange(objPtr)) {
        if (errorCode != nullptr) {
            *errorCode = ERRORS::Code::OmeObjPtrOutOfRange;
        }
        return -1;
    }

    int8_t poolNo = -1;
    for (int16_t i = 0; i < OME_OBJ_POOL_SIZE; i++) {
        if (ConvertNoToPtr(i, nullptr) == objPtr) {
            poolNo = i;
            break;
        }
    }

    if (poolNo == -1) {
        if (errorCode != nullptr) {
            *errorCode = ERRORS::Code::OmeObjPtrIsNotPointingToTheFirstElementOfTheMemorySlice;
        }
    }
    else {
        if (errorCode != nullptr) {
            *errorCode = ERRORS::Code::None;
        }
    }

    return poolNo;
}

/**
 * @brief Checks if the given pool object number is in the avaliable memory space.
 * 
 * @param poolNo A pool object number to a memors location.
 * @return True if the given pool object number is in the avaliable memory space, else false.
 */
bool OME::isInPoolRange(int8_t poolNo) {
    if (poolNo >= OME_OBJ_POOL_SIZE || poolNo < 0) {
        return false;
    }
    else {
        return true;
    }
}

/**
 * @brief Checks if the given pointer is in the avaliable memory space.
 * 
 * @param objPtr A pointer to a memors location.
 * @return True if the given pointer is in the avaliable memory space, else false.
 */
bool OME::isInMemoryRange(void *objPtr) {
    if (objPtr < &BytePool[0] || objPtr > &BytePool[OME_OBJ_POOL_SIZE_BYTES - 1]) {
        return false;
    }
    else {
        return true;
    }
}

/**
 * @brief Check if a pointer is part of a used pool object.
 * 
 * @param The pointer to check for.
 * @return The pool object number to which the pointer belongs, or -1 if it doesn't belong to a pool object.
 */
int8_t OME::ptrBelongsToPoolObj(void* objPtr) {
    if (!isInMemoryRange(objPtr)) {
        return -1;
    }

    for (int8_t i = 0; i < OME_OBJ_POOL_SIZE; i++) {
        if (!ObjInfos[i].inUse) {
            continue;
        }

        if (objPtr >= ObjInfos[i].firstMemoryPtr && objPtr <= ObjInfos[i].lastMemoryPtr) {
            return i;
        }
    }

    return -1;
}

/**
 * @brief Find a Free memory slices with a given size.
 * 
 * @param size The size.
 * @return A pointer to the begining of the free memory space, or null if no memory is avaliavle.
 */
void* OME::findFreeMemorySlice(uint16_t size) {
    if (size > OME_OBJ_POOL_SIZE_BYTES) {
        return nullptr;
    }

    uint16_t sizeCounter = 0;

    for (uint16_t i = 0; i < OME_OBJ_POOL_SIZE_BYTES; i++) {
        if (ptrBelongsToPoolObj(BytePool + i)) {
            sizeCounter = 0;
        }
        else
        {
            sizeCounter++;
            if (sizeCounter == size) {
                return BytePool + (i - sizeCounter);
            }
        }
    }

    return nullptr;
}


//////////////////////
// public functions //
//////////////////////

/**
 * @brief Get a a pointer to the next free availiale memory slice.
 * 
 * @param poolNo int16_t pointer where the pointer number gets written to on succes, else -1.
 * @return void pointer to the memory slice if there is one avaliable, else nullptr.
 */
void* OME::GetFreeObjPrt(uint16_t size, int8_t *poolNo, ERRORS::Code *errorCode) {

    // check size
    if (size <= 0 || size > OME_OBJ_POOL_SIZE_BYTES) {
        if (poolNo != nullptr) {
            *poolNo = -1;
        }
        if (errorCode != nullptr) {
            *errorCode = ERRORS::Code::OmeInvalidObjSize;
        }
        return nullptr;
    }

    // allocate memory slice
    for (int8_t i = 0; i < OME_OBJ_POOL_SIZE; i++) {
        if (!ObjInfos[i].inUse) {

            void *ptr = findFreeMemorySlice(size);

            // no such big memory slice avaliable
            if (ptr == nullptr) {
                if (poolNo != nullptr) {
                    *poolNo = -1;
                }
                if (errorCode != nullptr) {
                    *errorCode = ERRORS::Code::OmeNoMemorSliceInWishedSizeAvaliable;
                }
                return nullptr;
            }

            // set obj info
            ObjInfos[i].inUse = true;
            ObjInfos[i].firstMemoryPtr = ptr;
            ObjInfos[i].firstMemoryPtr = ptr + (size - 1);
            if (poolNo != nullptr) {
                *poolNo = i;
            }
            if (errorCode != nullptr) {
                *errorCode = ERRORS::Code::None;
            }
            return ptr;
        }
    }

    // pool has reached the maximum number ob used objects
    if (poolNo != nullptr) {
        *poolNo = -1;
        if (errorCode != nullptr) {
            *errorCode = ERRORS::Code::OmeMaxNumberOfObjInPoolReached;
        }
    }
    return nullptr;
}

/**
 * @brief Mark a blocked memory slice as free based on a given pointer.
 * 
 * @param objPrt The pointer to the object.
 * @return true on succes, else false.
 */
bool OME::FreePtr(void *objPrt) {
    ERRORS::Code errorCode = ERRORS::Code::None;
    int8_t poolNo = ConvertPrtToNo(objPrt, &errorCode);

    if (errorCode != ERRORS::Code::None) {
        return false;
    }
    else {
        ObjInfos[poolNo].inUse = false;
        ObjInfos[poolNo].firstMemoryPtr = nullptr;
        ObjInfos[poolNo].lastMemoryPtr = nullptr;
        return true;
    }
}

/**
 * @brief Mark a blocked memory slice as free based on the pointer number.
 * 
 * @param poolNo The number of the pointer.
 * @return true on succes, else false.
 */
bool OME::FreePtr(int8_t poolNo) {
    if (!isInPoolRange(poolNo)) {
        return false;
    }
    else {
        ObjInfos[poolNo].inUse = false;
        ObjInfos[poolNo].firstMemoryPtr = nullptr;
        ObjInfos[poolNo].lastMemoryPtr = nullptr;
        return true;
    }
}