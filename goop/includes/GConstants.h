#ifndef __GConstants__
#define __GConstants__

// bitwise flags for class->flags
enum GObjClass_Flags {
    GObjClass_NONE = 0x00,
    GObjClass_FLAG_DIE_ON_THROW = 0x01, // if an exception is thrown, the process dies
    GObjClass_FLAG_QUIET_ON_THROW = 0x02, // don't write to stdout on thrown errors
    GObjClass_FLAG_SEARCH_AND_DESTROY = 0x04, // on destroy(), search the _freeStack for already destroyed pointer, if not set, the GObj_FLAG_DESTROYED flag is detected
} ;

#define GObjClass_FLAG_SEARCH_AND_DESTROY 0x04
// bitwise flags instance->flags
enum GObj_Flags {
    GObj_FLAG_NONE = 0x00,
    GObj_FLAG_AUTODESTROY = 0x01, // call destroy() when removed from queue/list
    GObj_FLAG_DESTROYED = 0x02, // destroyed - don't add to the _freeStack
    GTask_FLAG_STOP = 0x04, // stop task
} ;

#endif // __GConstants__