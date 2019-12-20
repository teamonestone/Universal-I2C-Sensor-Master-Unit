/**
 * @file OME.h
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
#include "OME.h"


///////////////////////
// private functions //
///////////////////////

/**
 * @brief Initialize the memory witch gets split into smaller memory slices.
 *
 */
uint8_t OME::BytePool[OME_OBJ_POOL_SIZE_BYTES] = {0};

/**
 * @brief Initialize the Array with usage information.
 *
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
void* OME::ConvertNoToPtr(int8_t poolNo) {
    if (!isInPoolRange(poolNo)) {
        return nullptr;
    }
    else {
        return ObjInfos[poolNo].firstMemoryPtr;
    }
}

/**
 * @brief Convert an actual pointer in a pointer number.
 *
 * @param objPtr The actual pointer.
 * @return The pointer number as int16_t.
 */
int8_t OME::ConvertPrtToNo(void *objPtr) {
    if(!isInMemoryRange(objPtr)) {
        return -1;
    }

    int8_t poolNo = -1;
    for (int16_t i = 0; i < OME_OBJ_POOL_SIZE; i++) {
        if (ConvertNoToPtr(i) == objPtr) {
            poolNo = i;
            break;
        }
    }
    return poolNo;
}

/**
 * @brief Checks if the given pool object number is in the available memory space.
 *
 * @param poolNo A pool object number to a memory location.
 * @return True if the given pool object number is in the available memory space, else false.
 */
bool OME::isInPoolRange(int8_t poolNo) {
    return !(poolNo >= OME_OBJ_POOL_SIZE || poolNo < 0);
}

/**
 * @brief Checks if the given pointer is in the available memory space.
 *
 * @param objPtr A pointer to a memory location.
 * @return True if the given pointer is in the available memory space, else false.
 */
bool OME::isInMemoryRange(void *objPtr) {
    return !(objPtr < &BytePool[0] || objPtr > &BytePool[OME_OBJ_POOL_SIZE_BYTES - 1]);
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
 * @return A pointer to the the begin of the free memory space, or null if no memory is available.
 */
void* OME::findFreeMemorySlice(uint16_t size) {
    if (size > OME_OBJ_POOL_SIZE_BYTES) {
        return nullptr;
    }
    uint16_t sizeCounter = 0;
    for (uint16_t i = 0; i < OME_OBJ_POOL_SIZE_BYTES; i++) {
        if (ptrBelongsToPoolObj(BytePool + i) != -1 ) {
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
 * @brief Get a a pointer to the next free available memory slice.
 *
 * @param poolNo int16_t pointer where the pointer number gets written to on success, else -1.
 * @return void pointer to the memory slice if there is one available, else nullptr.
 */
void* OME::GetFreeObjPrt(uint16_t size, int8_t *poolNo) {
    // check size
    if (size <= 0 || size > OME_OBJ_POOL_SIZE_BYTES) {
        if (poolNo != nullptr) {
            *poolNo = -3;
        }
        return nullptr;
    }
    // allocate memory slice
    for (int8_t i = 0; i < OME_OBJ_POOL_SIZE; i++) {
        if (!ObjInfos[i].inUse) {
            void *ptr = findFreeMemorySlice(size);
            // no such big memory slice available
            if (ptr == nullptr) {
                if (poolNo != nullptr) {
                    *poolNo = -2;
                }
                return nullptr;
            }
            // set obj info
            ObjInfos[i].inUse = true;
            ObjInfos[i].firstMemoryPtr = ptr;
            ObjInfos[i].lastMemoryPtr = static_cast<uint8_t *>(ptr) + size;
            if (poolNo != nullptr) {
                *poolNo = i;
            }
            return ptr;
        }
    }
    // pool has reached the maximum number ob used objects
    if (poolNo != nullptr) {
        *poolNo = -1;
    }
    return nullptr;
}

/**
 * @brief Mark a blocked memory slice as free based on a given pointer.
 *
 * @param objPrt The pointer to the object.
 * @return true on success, else false.
 */
bool OME::FreePtr(void *objPrt) {
    int8_t poolNo = ConvertPrtToNo(objPrt);
    if (poolNo >=  0 && poolNo < OME_OBJ_POOL_SIZE) {
        ObjInfos[poolNo].inUse = false;
        ObjInfos[poolNo].firstMemoryPtr = nullptr;
        ObjInfos[poolNo].lastMemoryPtr = nullptr;
        return true;
    }
    else {
        return false;
    }
}

/**
 * @brief Mark a blocked memory slice as free based on the pointer number.
 *
 * @param poolNo The number of the pointer.
 * @return true on success, else false.
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