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
uint8_t OME::BytePool[OME_OBJ_POOL_SIZE * OME_OBJ_SIZE] = {0};

/**
 * @brief Initialize the Array with usage inforation.
 * 
 * @param argname desc
 * @return
 */
bool OME::inUse[OME_OBJ_POOL_SIZE] = {0};

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
 * @brief Convert a pointer number in an actual pointer.
 * 
 * @param poolNo The pointer number.
 * @return The actual pointer as void*.
 */
void* OME::ConvertNoToPtr(int16_t poolNo) {
    if (poolNo >= OME_OBJ_POOL_SIZE || poolNo < 0) {
        return nullptr;
    }
    else {
        return BytePool + (poolNo * OME_OBJ_SIZE);
    }
}

/**
 * @brief Convert an actual pointer in a pointer number.
 * 
 * @param objPtr The actual pointer.
 * @return The pointer number as int16_t.
 */
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


//////////////////////
// public functions //
//////////////////////

/**
 * @brief Get a a pointer to the next free availiale memory slice.
 * 
 * @param poolNo int16_t pointer where the pointer number gets written to on succes, else -1.
 * @return void pointer to the memory slice if there is one avaliable, else nullptr.
 */
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

/**
 * @brief Mark a blocked memory slice as free based on a given pointer.
 * 
 * @param objPrt The pointer to the object.
 * @return true on succes, else false.
 */
bool OME::FreePtr(void *objPrt) {
    int16_t poolNo = ConvertPrtToNo(objPrt);
    if (poolNo >= OME_OBJ_POOL_SIZE || poolNo < 0) {
        return false;
    }
    inUse[poolNo] = false;
    return true;
}

/**
 * @brief Mark a blocked memory slice as free based on the pointer number.
 * 
 * @param poolNo The number of the pointer.
 * @return true on succes, else false.
 */
bool OME::FreePtr(int16_t poolNo) {
    if (poolNo >= OME_OBJ_POOL_SIZE || poolNo < 0) {
        return false;
    }
    inUse[poolNo] = false;
    return true;
}