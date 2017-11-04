/* Automatically generated nanopb constant definitions */
/* Generated by nanopb-0.3.6 at Mon Sep 26 23:18:02 2016. */

#include "grSim_Commands.pb.h"

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif



const pb_field_t grSim_Robot_Command_fields[13] = {
    PB_FIELD(  1, UINT32  , REQUIRED, STATIC  , FIRST, grSim_Robot_Command, id, id, 0),
    PB_FIELD(  2, FLOAT   , REQUIRED, STATIC  , OTHER, grSim_Robot_Command, kickspeedx, id, 0),
    PB_FIELD(  3, FLOAT   , REQUIRED, STATIC  , OTHER, grSim_Robot_Command, kickspeedz, kickspeedx, 0),
    PB_FIELD(  4, FLOAT   , REQUIRED, STATIC  , OTHER, grSim_Robot_Command, veltangent, kickspeedz, 0),
    PB_FIELD(  5, FLOAT   , REQUIRED, STATIC  , OTHER, grSim_Robot_Command, velnormal, veltangent, 0),
    PB_FIELD(  6, FLOAT   , REQUIRED, STATIC  , OTHER, grSim_Robot_Command, velangular, velnormal, 0),
    PB_FIELD(  7, BOOL    , REQUIRED, STATIC  , OTHER, grSim_Robot_Command, spinner, velangular, 0),
    PB_FIELD(  8, BOOL    , REQUIRED, STATIC  , OTHER, grSim_Robot_Command, wheelsspeed, spinner, 0),
    PB_FIELD(  9, FLOAT   , OPTIONAL, STATIC  , OTHER, grSim_Robot_Command, wheel1, wheelsspeed, 0),
    PB_FIELD( 10, FLOAT   , OPTIONAL, STATIC  , OTHER, grSim_Robot_Command, wheel2, wheel1, 0),
    PB_FIELD( 11, FLOAT   , OPTIONAL, STATIC  , OTHER, grSim_Robot_Command, wheel3, wheel2, 0),
    PB_FIELD( 12, FLOAT   , OPTIONAL, STATIC  , OTHER, grSim_Robot_Command, wheel4, wheel3, 0),
    PB_LAST_FIELD
};

const pb_field_t grSim_Commands_fields[4] = {
    PB_FIELD(  1, DOUBLE  , REQUIRED, STATIC  , FIRST, grSim_Commands, timestamp, timestamp, 0),
    PB_FIELD(  2, BOOL    , REQUIRED, STATIC  , OTHER, grSim_Commands, isteamyellow, timestamp, 0),
    PB_FIELD(  3, MESSAGE , REPEATED, CALLBACK, OTHER, grSim_Commands, robot_commands, isteamyellow, &grSim_Robot_Command_fields),
    PB_LAST_FIELD
};


/* Check that field information fits in pb_field_t */
#if !defined(PB_FIELD_32BIT)
/* If you get an error here, it means that you need to define PB_FIELD_32BIT
 * compile-time option. You can do that in pb.h or on compiler command line.
 * 
 * The reason you need to do this is that some of your messages contain tag
 * numbers or field sizes that are larger than what can fit in 8 or 16 bit
 * field descriptors.
 */
PB_STATIC_ASSERT((pb_membersize(grSim_Commands, robot_commands) < 65536), YOU_MUST_DEFINE_PB_FIELD_32BIT_FOR_MESSAGES_grSim_Robot_Command_grSim_Commands)
#endif

#if !defined(PB_FIELD_16BIT) && !defined(PB_FIELD_32BIT)
/* If you get an error here, it means that you need to define PB_FIELD_16BIT
 * compile-time option. You can do that in pb.h or on compiler command line.
 * 
 * The reason you need to do this is that some of your messages contain tag
 * numbers or field sizes that are larger than what can fit in the default
 * 8 bit descriptors.
 */
PB_STATIC_ASSERT((pb_membersize(grSim_Commands, robot_commands) < 256), YOU_MUST_DEFINE_PB_FIELD_16BIT_FOR_MESSAGES_grSim_Robot_Command_grSim_Commands)
#endif


/* On some platforms (such as AVR), double is really float.
 * These are not directly supported by nanopb, but see example_avr_double.
 * To get rid of this error, remove any double fields from your .proto.
 */
PB_STATIC_ASSERT(sizeof(double) == 8, DOUBLE_MUST_BE_8_BYTES)

/* @@protoc_insertion_point(eof) */
