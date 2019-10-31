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

// Includes
#include <inttypes.h>

// Defines
#define OME_OBJ_SIZE 64			///< Define for object size (in bytes).
#define OME_OBJ_POOL_SIZE 8		///< Definie for pool size.

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
        static void* GetFreeObjPrt(int16_t *poolNo);		// Get a a pointer to the next free availiale memory slice.
        static bool FreePtr(void *objPrt);                	// Mark a blocked memory slice as free based on a given pointer.
        static bool FreePtr(int16_t poolNo);				// Mark a blocked memory slice as free based on the pointer number.

// End PUBLIC --------------------------------------------------------------------

// Begin PRIVATE -----------------------------------------------------------------
	private:
        
        // constructor
        OME();			// Main constructor of the class (private so no instance of this class can be created).
        ~OME();			// Main destructor of the class (private so no instance of this class can be created).
		
		// vars & objects
        static uint8_t BytePool[OME_OBJ_POOL_SIZE * OME_OBJ_SIZE];		// The memory witch gets split into smaller memory slices.
        static bool inUse[OME_OBJ_POOL_SIZE];							// The array with usage inforation.

        // functions
        static void* ConvertNoToPtr(int16_t poolNo);					// Convert a pointer number in an actual pointer.
        static int16_t ConvertPrtToNo(void *objPtr);					// Convert an actual pointer in a pointer number.

// End PRIVATE -------------------------------------------------------------------

};

#endif
