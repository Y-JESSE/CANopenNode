/**
 * Main CANopenNode file.
 *
 * @file        CANopen.h
 * @ingroup     CO_CANopen
 * @author      Janez Paternoster
 * @author      Uwe Kindler
 * @copyright   2010 - 2020 Janez Paternoster
 *
 * This file is part of CANopenNode, an opensource CANopen Stack.
 * Project home page is <https://github.com/CANopenNode/CANopenNode>.
 * For more information on CANopen see <http://www.can-cia.org/>.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#ifndef CANopen_H
#define CANopen_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup CO_CANopen CANopen
 * @{
 *
 * CANopenNode is free and open source implementation of CANopen communication
 * protocol.
 *
 * CANopen is the internationally standardized (EN 50325-4) (CiA DS-301)
 * CAN-based higher-layer protocol for embedded control system. For more
 * information on CANopen see http://www.can-cia.org/
 *
 * CANopenNode homepage is https://github.com/CANopenNode/CANopenNode
 *
 * CANopen.h file combines Object dictionary (CO_OD) and all other CANopen
 * source files. Configuration information are read from CO_OD.h file.
 * CO_OD.h/.c files defines CANopen Object Dictionary and are generated by
 * external tool.
 * CANopen.h file contains most common configuration of CANopenNode objects
 * and can also be a template for custom, more complex configurations.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * @}
 */

/**
 * @defgroup CO_CANopen_301 CANopen_301
 * @{
 *
 * CANopen application layer and communication profile.
 *
 * Definitions of data types, encoding rules, object dictionary objects and
 * CANopen communication services and protocols.
 * @}
 */

/**
 * @defgroup CO_CANopen_305 CANopen_305
 * @{
 *
 * CANopen layer setting services (LSS) and protocols.
 *
 * Inquire or change three parameters on a CANopen device with LSS slave
 * capability by a CANopen device with LSS master capability via the CAN
 * network: the settings of Node-ID of the CANopen device, bit timing
 * parameters of the physical layer (bit rate) or LSS address compliant to the
 * identity object (1018h).
 * @}
 */

/**
 * @defgroup CO_CANopen_extra CANopen_extra
 * @{
 *
 * Additional non-standard objects related to CANopenNode.
 * @}
 */

/**
 * @addtogroup CO_CANopen
 * @{
 */

    #include "301/CO_driver.h"
    #include "301/CO_SDOserver.h"
    #include "301/CO_Emergency.h"
    #include "301/CO_NMT_Heartbeat.h"
    #include "301/CO_SYNC.h"
    #include "301/CO_TIME.h"
    #include "301/CO_PDO.h"
    #include "301/CO_HBconsumer.h"
#if CO_NO_SDO_CLIENT != 0
    #include "301/CO_SDOclient.h"
#endif
#if CO_NO_LSS_SLAVE != 0
    #include "305/CO_LSSslave.h"
#endif
#if CO_NO_LSS_MASTER != 0
    #include "305/CO_LSSmaster.h"
#endif
#if CO_NO_TRACE != 0
    #include "extra/CO_trace.h"
#endif
    #include "CO_OD.h"


#ifdef CO_DOXYGEN
/**
 * @defgroup CO_NO_OBJ Number of CANopenNode communication objects.
 *
 * Definitions specify, which and how many CANopenNode communication objects
 * will be used in current configuration. Usage of some objects is mandatory and
 * is fixed. Others are defined in CO_OD.h.
 * @{
 */
/* Definitions valid only for documentation. */
/** Number of NMT objects, fixed to 1 (slave(CANrx) + master(CANtx)) */
#define CO_NO_NMT (1)
/** Number of SYNC objects, 0 or 1 (consumer(CANrx) + producer(CANtx)) */
#define CO_NO_SYNC (0...1)
/** Number of Emergency objects, fixed to 1 (consumer(CANrx) +
 * producer(CANtx)) */
#define CO_NO_EMERGENCY (1)
/** Number of Time-stamp objects, 0 or 1 (consumer(CANrx) + producer(CANtx)) */
#define CO_NO_TIME (0...1)
/** Number of RPDO objects, 1 to 512 consumers (CANrx) */
#define CO_NO_RPDO (1...512)
/** Number of TPDO objects, 1 to 512 producers (CANtx) */
#define CO_NO_TPDO (1...512)
/** Number of SDO server objects, from 1 to 128 (CANrx + CANtx) */
#define CO_NO_SDO_SERVER (1...128)
/** Number of SDO client objects, from 0 to 128 (CANrx + CANtx) */
#define CO_NO_SDO_CLIENT (0...128)
/** Number of HB producer objects, fixed to 1 producer(CANtx) */
#define CO_NO_HB_PROD (1)
/** Number of HB consumer objects, from 0 to 127 consumers(CANrx) */
#define CO_NO_HB_CONS (0...127)
/** Number of LSS slave objects, 0 or 1 (CANrx + CANtx) */
#define CO_NO_LSS_SLAVE (0...1)
/** Number of LSS master objects, 0 or 1 (CANrx + CANtx) */
#define CO_NO_LSS_MASTER) (0...1)
/** Number of Trace objects, 0 to many */
#define CO_NO_TRACE) (0...)
/** @} */
#else  /* CO_DOXYGEN */

/* Valid Definitions for program. */
#define CO_NO_NMT     1             /* NMT master/slave count (fixed) */
#define CO_NO_HB_PROD 1             /* Heartbeat producer count (fixed) */
#ifdef ODL_consumerHeartbeatTime_arrayLength
    #define CO_NO_HB_CONS ODL_consumerHeartbeatTime_arrayLength
#else
    #define CO_NO_HB_CONS 0
#endif
#endif /* CO_DOXYGEN */


/**
 * CANopen object with pointers to all CANopenNode objects.
 */
typedef struct {
    CO_CANmodule_t *CANmodule[1];    /**< CAN module objects */
    CO_SDO_t *SDO[CO_NO_SDO_SERVER]; /**< SDO object */
    CO_EM_t *em;                     /**< Emergency report object */
    CO_EMpr_t *emPr;                 /**< Emergency process object */
    CO_NMT_t *NMT;                   /**< NMT object */
    CO_SYNC_t *SYNC;                 /**< SYNC object */
    CO_TIME_t *TIME;                 /**< TIME object */
    CO_RPDO_t *RPDO[CO_NO_RPDO];     /**< RPDO objects */
    CO_TPDO_t *TPDO[CO_NO_TPDO];     /**< TPDO objects */
    CO_HBconsumer_t *HBcons;         /**< Heartbeat consumer object*/
#if CO_NO_SDO_CLIENT != 0
    CO_SDOclient_t *SDOclient[CO_NO_SDO_CLIENT]; /**< SDO client object */
#endif
#if CO_NO_LSS_SERVER == 1
    CO_LSSslave_t *LSSslave;         /**< LSS slave object */
#endif
#if CO_NO_LSS_CLIENT == 1
    CO_LSSmaster_t *LSSmaster;       /**< LSS master object */
#endif
#if CO_NO_TRACE > 0
    CO_trace_t *trace[CO_NO_TRACE]; /**< Trace object for recording variables */
#endif
} CO_t;


/** CANopen object */
extern CO_t *CO;


/**
 * Allocate and initialize memory for CANopen object
 *
 * Function must be called the first time, after program starts.
 *
 * @return #CO_ReturnError_t: CO_ERROR_NO, CO_ERROR_ILLEGAL_ARGUMENT,
 * CO_ERROR_OUT_OF_MEMORY
 */
CO_ReturnError_t CO_new(void);


/**
 * Delete CANopen object and free memory. Must be called at program exit.
 *
 * @param CANptr Pointer to the user-defined CAN base structure, passed to
 *               CO_CANmodule_init().
 */
void CO_delete(void *CANptr);


/**
 * Initialize CAN driver
 *
 * Function must be called in the communication reset section.
 *
 * @param CANptr Pointer to the user-defined CAN base structure, passed to
 *               CO_CANmodule_init().
 * @param bitRate CAN bit rate.
 * @return #CO_ReturnError_t: CO_ERROR_NO, CO_ERROR_ILLEGAL_ARGUMENT,
 * CO_ERROR_ILLEGAL_BAUDRATE, CO_ERROR_OUT_OF_MEMORY
 */
CO_ReturnError_t CO_CANinit(void *CANptr,
                            uint16_t bitRate);


#if CO_NO_LSS_SERVER == 1
/**
 * Initialize CANopen LSS slave
 *
 * Function must be called in the communication reset section.
 *
 * @param nodeId Node ID of the CANopen device (1 ... 127) or
 *               CO_LSS_NODE_ID_ASSIGNMENT
 * @param bitRate CAN bit rate.
 * @return #CO_ReturnError_t: CO_ERROR_NO, CO_ERROR_ILLEGAL_ARGUMENT
 */
CO_ReturnError_t CO_LSSinit(uint8_t nodeId,
                            uint16_t bitRate);
#endif /* CO_NO_LSS_SERVER == 1 */


/**
 * Initialize CANopenNode.
 *
 * Function must be called in the communication reset section.
 *
 * @param nodeId Node ID of the CANopen device (1 ... 127).
 * @return #CO_ReturnError_t: CO_ERROR_NO, CO_ERROR_ILLEGAL_ARGUMENT
 */
CO_ReturnError_t CO_CANopenInit(uint8_t nodeId);


/**
 * Process CANopen objects.
 *
 * Function must be called cyclically. It processes all "asynchronous" CANopen
 * objects.
 *
 * @param co CANopen object.
 * @param timeDifference_us Time difference from previous function call in
 *                          microseconds.
 * @param timerNext_us [out] info to OS - maximum delay after function
 *        should be called next time in [microseconds]. Value can be used for OS
 *        sleep time. Initial value must be set to something, 50000us typically.
 *        Output will be equal or lower to initial value. If there is new object
 *        to process, delay should be suspended and this function should be
 *        called immediately. Parameter is ignored if NULL.
 *
 * @return #CO_NMT_reset_cmd_t from CO_NMT_process().
 */
CO_NMT_reset_cmd_t CO_process(CO_t *co,
                              uint32_t timeDifference_us,
                              uint32_t *timerNext_us);


#if CO_NO_SYNC == 1
/**
 * Process CANopen SYNC objects.
 *
 * Function must be called cyclically from real time thread with constant
 * interval (1ms typically). It processes SYNC CANopen objects.
 *
 * @param co CANopen object.
 * @param timeDifference_us Time difference from previous function call in
 * microseconds.
 * @param timerNext_us [out] info to OS - see CO_process().
 *
 * @return True, if CANopen SYNC message was just received or transmitted.
 */
bool_t CO_process_SYNC(CO_t *co,
                       uint32_t timeDifference_us,
                       uint32_t *timerNext_us);
#endif /* CO_NO_SYNC == 1 */


/**
 * Process CANopen RPDO objects.
 *
 * Function must be called cyclically from real time thread with constant.
 * interval (1ms typically). It processes receive PDO CANopen objects.
 *
 * @param co CANopen object.
 * @param syncWas True, if CANopen SYNC message was just received or
 * transmitted.
 */
void CO_process_RPDO(CO_t *co, bool_t syncWas);


/**
 * Process CANopen TPDO objects.
 *
 * Function must be called cyclically from real time thread with constant.
 * interval (1ms typically). It processes transmit PDO CANopen objects.
 *
 * @param co CANopen object.
 * @param syncWas True, if CANopen SYNC message was just received or
 * transmitted.
 * @param timeDifference_us Time difference from previous function call in
 * microseconds.
 * @param timerNext_us [out] info to OS - see CO_process().
 */
void CO_process_TPDO(CO_t *co,
                     bool_t syncWas,
                     uint32_t timeDifference_us,
                     uint32_t *timerNext_us);


/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CANopen_H */
