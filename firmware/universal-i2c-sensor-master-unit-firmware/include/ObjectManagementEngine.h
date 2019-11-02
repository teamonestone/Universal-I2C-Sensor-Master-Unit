/**
 * @file ObjectManagementEngine.h
 * @brief The header file of the Object Management Engine class.
 * @author Jonas Merkle [JJM] <a href="mailto:jonas.merkle@tam-onestone.net">jonas.merkle@tam-onestone.net</a>
 * @author Dominik Authaler <a href="mailto:dominik.authaler@team-onestone.net">dominik.authaler@team-onestone.net</a>
 * @author
 * This library is maintained by <a href="https://team-onestone.net">Team Onestone</a>.
 * E-Mail: <a href="mailto:info@team-onestone.net">info@team-onestone.net</a>
 * @version 1.0.0
 * @date 31 October 2019
 * @copyright This project is released under the GNU General Public License v3.0
 */

#ifndef OBJECTMANAGEMENTENGINE_h
#define OBJECTMANAGEMENTENGINE_h

//////////////
// Includes //
//////////////

// basic Includes
#include <inttypes.h>

// errors
#include "ERRORS.h"


/////////////
// Defines //
/////////////

//#define OME_OBJ_SIZE 438				///< Define for object size (in bytes).
#define OME_OBJ_POOL_SIZE 8				///< Define the maximun number of objects the OME has to handel (must be smaller than 128).
#define OME_OBJ_POOL_SIZE_BYTES 1024	///< Define the maximum size of the memory pool


///////////
// Types //
///////////

struct ObjInfo {
	bool inUse = false;

	void *firstMemoryPtr = nullptr;
	void *lastMemoryPtr = nullptr;

	uint16_t getSize() {
		return static_cast<uint8_t*>(lastMemoryPtr) - static_cast<uint8_t*>(firstMemoryPtr);
	}
};


///////////
// Class //
///////////

/**
 * @class OME
 * 
 * @brief This calls manages a given amout of memory that then can be used for other objects.
 */
class OME
{
// Begin PUBLIC ------------------------------------------------------------------
	public:
        
        // functions
        static void* GetFreeObjPrt(uint16_t size, int8_t *poolNo, ERRORS::Code *errorCode);		// Get a a pointer to the next free availiale memory slice.
        static bool FreePtr(void *objPrt);                	        							// Mark a blocked memory slice as free based on a given pointer.
        static bool FreePtr(int8_t poolNo);			        									// Mark a blocked memory slice as free based on the pointer number.

// End PUBLIC --------------------------------------------------------------------

// Begin PRIVATE -----------------------------------------------------------------
	private:
        
        // constructor
        OME();			// Main constructor of the class (private so no instance of this class can be created).
        ~OME();			// Main destructor of the class (private so no instance of this class can be created).
		
		// vars & objects
        static uint8_t BytePool[OME_OBJ_POOL_SIZE_BYTES];		// The memory witch gets split into smaller memory slices.
        static ObjInfo ObjInfos[OME_OBJ_POOL_SIZE];			    // The array with usage inforation.

        // functions
        static void* ConvertNoToPtr(int8_t poolNo, ERRORS::Code *errorCode);	// Convert a pointer number in an actual pointer.
        static int8_t ConvertPrtToNo(void *objPtr, ERRORS::Code *errorCode);	// Convert an actual pointer in a pointer number.
		static bool isInPoolRange(int8_t poolNo);								// Checks if the given pool object number is in the avaliable memory space.
		static bool isInMemoryRange(void *objPtr);								// Checks if the given pointer is in the avaliable memory space.
        static int8_t  ptrBelongsToPoolObj(void* objPtr);						// Check if a pointer is part of a used pool object.
		static void* findFreeMemorySlice(uint16_t size);						// Find a Free memory slices with a given size.

// End PRIVATE -------------------------------------------------------------------

};

#endif
