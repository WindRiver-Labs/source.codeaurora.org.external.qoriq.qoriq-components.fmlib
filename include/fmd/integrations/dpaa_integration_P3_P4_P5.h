/* =====================================================================
 *
 *  Copyright 2009-2011, Freescale Semiconductor, Inc., All Rights Reserved.
 *
 *  This file contains copyrighted material. Use of this file is restricted
 *  by the provisions of a Freescale Software License Agreement, which has
 *  either accompanied the delivery of this software in shrink wrap
 *  form or been expressly executed between the parties.
 *
 * ===================================================================*/
/**

 @File          dpaa_integration_P3_P4_P5.h

 @Description   P4080/P5020/P3041 FM external definitions and structures.
*//***************************************************************************/
#ifndef __DPAA_INTEGRATION_P3_P4_P5_H
#define __DPAA_INTEGRATION_P3_P4_P5_H

#include "std_ext.h"

#ifdef P1023
#error "file for p3, p4, p5"
#endif

typedef enum {
    e_DPAA_SWPORTAL0 = 0,
    e_DPAA_SWPORTAL1,
    e_DPAA_SWPORTAL2,
    e_DPAA_SWPORTAL3,
    e_DPAA_SWPORTAL4,
    e_DPAA_SWPORTAL5,
    e_DPAA_SWPORTAL6,
    e_DPAA_SWPORTAL7,
    e_DPAA_SWPORTAL8,
    e_DPAA_SWPORTAL9,
    e_DPAA_SWPORTAL_DUMMY_LAST
} e_DpaaSwPortal;

typedef enum {
    e_DPAA_DCPORTAL0 = 0,
    e_DPAA_DCPORTAL1,
    e_DPAA_DCPORTAL2,
    e_DPAA_DCPORTAL3,
    e_DPAA_DCPORTAL4,
    e_DPAA_DCPORTAL_DUMMY_LAST
} e_DpaaDcPortal;

#define DPAA_MAX_NUM_OF_SW_PORTALS  10
#define DPAA_MAX_NUM_OF_DC_PORTALS   4

/*****************************************************************************
 QMan INTEGRATION-SPECIFIC DEFINITIONS
******************************************************************************/
#define QMAN_PM_DCP_COUNTERS_ERRATA_QMAN1
#define QMAN_FQD_AVOID_BLK_ERRATA_QMAN2
#define QMAN_DBG_TRC_EV_ERRATA_QMAN3
#define QMAN_WQ_CS_CFG_ERRATA_QMAN4
#define QMAN_SFDR_LEAK_ERRATA_QMAN5
#define QMAN_FQ_TD_THRESH_ERRATA_QMAN6
#define QMAN_FQ_INIT_ON_PARKED_ERRATA_QMAN7
#define QMAN_NESN_ORR_ERRATA_QMAN8
#define QMAN_ERN_REJ_CODE6_ERRATA_QMAN9
#define QMAN_ERN_MOULTI_CORE_ERRATA_QMAN10
#define QMAN_PERFMON_FOR_DCP_FQD_ERRATA_QMAN11

#define QM_MAX_NUM_OF_POOL_CHANNELS 15
#define QM_MAX_NUM_OF_WQ            8
#define QM_MAX_NUM_OF_SWP_AS        4
#define QM_MAX_NUM_OF_CGS           256

typedef enum {
    e_QM_FQ_CHANNEL_SWPORTAL0 = 0,              /**< Dedicated channels serviced by software portals 0 to 9 */
    e_QM_FQ_CHANNEL_SWPORTAL1,
    e_QM_FQ_CHANNEL_SWPORTAL2,
    e_QM_FQ_CHANNEL_SWPORTAL3,
    e_QM_FQ_CHANNEL_SWPORTAL4,
    e_QM_FQ_CHANNEL_SWPORTAL5,
    e_QM_FQ_CHANNEL_SWPORTAL6,
    e_QM_FQ_CHANNEL_SWPORTAL7,
    e_QM_FQ_CHANNEL_SWPORTAL8,
    e_QM_FQ_CHANNEL_SWPORTAL9,

    e_QM_FQ_CHANNEL_POOL1 = 0x21,               /**< Pool channels that can be serviced by any of the software portals */
    e_QM_FQ_CHANNEL_POOL2,
    e_QM_FQ_CHANNEL_POOL3,
    e_QM_FQ_CHANNEL_POOL4,
    e_QM_FQ_CHANNEL_POOL5,
    e_QM_FQ_CHANNEL_POOL6,
    e_QM_FQ_CHANNEL_POOL7,
    e_QM_FQ_CHANNEL_POOL8,
    e_QM_FQ_CHANNEL_POOL9,
    e_QM_FQ_CHANNEL_POOL10,
    e_QM_FQ_CHANNEL_POOL11,
    e_QM_FQ_CHANNEL_POOL12,
    e_QM_FQ_CHANNEL_POOL13,
    e_QM_FQ_CHANNEL_POOL14,
    e_QM_FQ_CHANNEL_POOL15,

    e_QM_FQ_CHANNEL_FMAN0_SP0 = 0x40,           /**< Dedicated channels serviced by Direct Connect Portal 0:
                                                     connected to FMan 0; assigned in incrementing order to
                                                     each sub-portal (SP) in the portal */
    e_QM_FQ_CHANNEL_FMAN0_SP1,
    e_QM_FQ_CHANNEL_FMAN0_SP2,
    e_QM_FQ_CHANNEL_FMAN0_SP3,
    e_QM_FQ_CHANNEL_FMAN0_SP4,
    e_QM_FQ_CHANNEL_FMAN0_SP5,
    e_QM_FQ_CHANNEL_FMAN0_SP6,
    e_QM_FQ_CHANNEL_FMAN0_SP7,
    e_QM_FQ_CHANNEL_FMAN0_SP8,
    e_QM_FQ_CHANNEL_FMAN0_SP9,
    e_QM_FQ_CHANNEL_FMAN0_SP10,
    e_QM_FQ_CHANNEL_FMAN0_SP11,
/* difference between 5020 and 4080 :) */
    e_QM_FQ_CHANNEL_FMAN1_SP0 = 0x60,
    e_QM_FQ_CHANNEL_FMAN1_SP1,
    e_QM_FQ_CHANNEL_FMAN1_SP2,
    e_QM_FQ_CHANNEL_FMAN1_SP3,
    e_QM_FQ_CHANNEL_FMAN1_SP4,
    e_QM_FQ_CHANNEL_FMAN1_SP5,
    e_QM_FQ_CHANNEL_FMAN1_SP6,
    e_QM_FQ_CHANNEL_FMAN1_SP7,
    e_QM_FQ_CHANNEL_FMAN1_SP8,
    e_QM_FQ_CHANNEL_FMAN1_SP9,
    e_QM_FQ_CHANNEL_FMAN1_SP10,
    e_QM_FQ_CHANNEL_FMAN1_SP11,

    e_QM_FQ_CHANNEL_CAAM = 0x80,                /**< Dedicated channel serviced by Direct Connect Portal 2:
                                                     connected to SEC 4.x */

    e_QM_FQ_CHANNEL_PME = 0xA0,                 /**< Dedicated channel serviced by Direct Connect Portal 3:
                                                     connected to PME */
    e_QM_FQ_CHANNEL_RAID = 0xC0                 /**< Dedicated channel serviced by Direct Connect Portal 4:
                                                     connected to RAID */
} e_QmFQChannel;

/* p4080-rev1 unique features */
#define QM_CGS_NO_FRAME_MODE

/*****************************************************************************
 BMan INTEGRATION-SPECIFIC DEFINITIONS
******************************************************************************/
#define BM_MAX_NUM_OF_POOLS         64          /**< Number of buffers pools */


/*****************************************************************************
 FM INTEGRATION-SPECIFIC DEFINITIONS
******************************************************************************/
#define INTG_MAX_NUM_OF_FM          2

/* Ports defines */
#define FM_MAX_NUM_OF_1G_RX_PORTS   5
#define FM_MAX_NUM_OF_10G_RX_PORTS  1
#define FM_MAX_NUM_OF_RX_PORTS      (FM_MAX_NUM_OF_10G_RX_PORTS+FM_MAX_NUM_OF_1G_RX_PORTS)
#define FM_MAX_NUM_OF_1G_TX_PORTS   5
#define FM_MAX_NUM_OF_10G_TX_PORTS  1
#define FM_MAX_NUM_OF_TX_PORTS      (FM_MAX_NUM_OF_10G_TX_PORTS+FM_MAX_NUM_OF_1G_TX_PORTS)
#define FM_MAX_NUM_OF_OH_PORTS      7
#define FM_MAX_NUM_OF_1G_MACS       (FM_MAX_NUM_OF_1G_RX_PORTS)
#define FM_MAX_NUM_OF_10G_MACS      (FM_MAX_NUM_OF_10G_RX_PORTS)
#define FM_MAX_NUM_OF_MACS          (FM_MAX_NUM_OF_1G_MACS+FM_MAX_NUM_OF_10G_MACS)


#define FM_PORT_MAX_NUM_OF_EXT_POOLS            8           /**< Number of external BM pools per Rx port */
#define FM_PORT_NUM_OF_CONGESTION_GRPS          256         /**< Total number of congestion groups in QM */
#define FM_MAX_NUM_OF_SUB_PORTALS               12
#define FM_PORT_MAX_NUM_OF_OBSERVED_EXT_POOLS   0


#define FM_IPSEC_SUPPORT
#define FM_IP_FRAG_N_REASSEM_SUPPORT

/* Rams defines */
#define FM_MURAM_SIZE                   (160*KILOBYTE)
#define FM_IRAM_SIZE                    (64*KILOBYTE)

/* PCD defines */
#define FM_PCD_PLCR_NUM_ENTRIES         256                 /**< Total number of policer profiles */
#define FM_PCD_KG_NUM_OF_SCHEMES        32                  /**< Total number of KG schemes */
#define FM_PCD_MAX_NUM_OF_CLS_PLANS     256                 /**< Number of classification plan entries. */

/* RTC defines */
#define FM_RTC_NUM_OF_ALARMS            2
#define FM_RTC_NUM_OF_PERIODIC_PULSES   2
#define FM_RTC_NUM_OF_EXT_TRIGGERS      2

/* QMI defines */
#define QMI_MAX_NUM_OF_TNUMS            64
#define MAX_QMI_DEQ_SUBPORTAL           12
#define QMI_DEF_TNUMS_THRESH            48

/* FPM defines */
#define FM_NUM_OF_FMAN_CTRL_EVENT_REGS  4

/* DMA defines */
#define DMA_THRESH_MAX_COMMQ            31
#define DMA_THRESH_MAX_BUF              127

/* BMI defines */
#define BMI_MAX_NUM_OF_TASKS            128
#define BMI_MAX_NUM_OF_DMAS             32
#define BMI_MAX_FIFO_SIZE               (FM_MURAM_SIZE)
#define PORT_MAX_WEIGHT                 16


/**************************************************************************//**
 @Description   Enum for inter-module interrupts registration
*//***************************************************************************/
typedef enum e_FmEventModules{
    e_FM_MOD_PRS,                   /**< Parser event */
    e_FM_MOD_KG,                    /**< Keygen event */
    e_FM_MOD_PLCR,                  /**< Policer event */
    e_FM_MOD_10G_MAC,               /**< 10G MAC  error event */
    e_FM_MOD_1G_MAC,                /**< 1G MAC  error event */
    e_FM_MOD_TMR,                   /**< Timer event */
    e_FM_MOD_1G_MAC_TMR,            /**< 1G MAC  Timer event */
    e_FM_MOD_FMAN_CTRL,             /**< FMAN Controller  Timer event */
    e_FM_MOD_DUMMY_LAST
} e_FmEventModules;

/**************************************************************************//**
 @Description   Enum for interrupts types
*//***************************************************************************/
typedef enum e_FmIntrType {
    e_FM_INTR_TYPE_ERR,
    e_FM_INTR_TYPE_NORMAL
} e_FmIntrType;

/**************************************************************************//**
 @Description   Enum for inter-module interrupts registration
*//***************************************************************************/
typedef enum e_FmInterModuleEvent {
    e_FM_EV_PRS,                    /**< Parser event */
    e_FM_EV_ERR_PRS,                /**< Parser error event */
    e_FM_EV_KG,                     /**< Keygen event */
    e_FM_EV_ERR_KG,                 /**< Keygen error event */
    e_FM_EV_PLCR,                   /**< Policer event */
    e_FM_EV_ERR_PLCR,               /**< Policer error event */
    e_FM_EV_ERR_10G_MAC0,           /**< 10G MAC 0 error event */
    e_FM_EV_ERR_1G_MAC0,            /**< 1G MAC 0 error event */
    e_FM_EV_ERR_1G_MAC1,            /**< 1G MAC 1 error event */
    e_FM_EV_ERR_1G_MAC2,            /**< 1G MAC 2 error event */
    e_FM_EV_ERR_1G_MAC3,            /**< 1G MAC 3 error event */
    e_FM_EV_ERR_1G_MAC4,            /**< 1G MAC 4 error event */
    e_FM_EV_TMR,                    /**< Timer event */
    e_FM_EV_1G_MAC1,                /**< 1G MAC 1 event */
    e_FM_EV_1G_MAC2,                /**< 1G MAC 2 event */
    e_FM_EV_1G_MAC3,                /**< 1G MAC 3 event */
    e_FM_EV_1G_MAC4,                /**< 1G MAC 3 event */
    e_FM_EV_1G_MAC0_TMR,            /**< 1G MAC 0 Timer event */
    e_FM_EV_1G_MAC1_TMR,            /**< 1G MAC 1 Timer event */
    e_FM_EV_1G_MAC2_TMR,            /**< 1G MAC 2 Timer event */
    e_FM_EV_1G_MAC3_TMR,            /**< 1G MAC 3 Timer event */
    e_FM_EV_1G_MAC4_TMR,            /**< 1G MAC 4 Timer event */
    e_FM_EV_FMAN_CTRL_0,            /**< Fman controller event 0 */
    e_FM_EV_FMAN_CTRL_1,            /**< Fman controller event 1 */
    e_FM_EV_FMAN_CTRL_2,            /**< Fman controller event 2 */
    e_FM_EV_FMAN_CTRL_3,            /**< Fman controller event 3 */
    e_FM_EV_DUMMY_LAST
} e_FmInterModuleEvent;

#define GET_FM_MODULE_EVENT(mod, id, intrType, event)                                               \
    switch(mod){                                                                                    \
        case e_FM_MOD_PRS:                                                                          \
            if (id) event = e_FM_EV_DUMMY_LAST;                                                     \
            else event = (intrType == e_FM_INTR_TYPE_ERR) ? e_FM_EV_ERR_PRS : e_FM_EV_PRS;          \
            break;                                                                                  \
        case e_FM_MOD_KG:                                                                           \
            if (id) event = e_FM_EV_DUMMY_LAST;                                                     \
            else event = (intrType == e_FM_INTR_TYPE_ERR) ? e_FM_EV_ERR_KG : e_FM_EV_DUMMY_LAST;    \
            break;                                                                                  \
        case e_FM_MOD_PLCR:                                                                         \
            if (id) event = e_FM_EV_DUMMY_LAST;                                                     \
            else event = (intrType == e_FM_INTR_TYPE_ERR) ? e_FM_EV_ERR_PLCR : e_FM_EV_PLCR;        \
            break;                                                                                  \
        case e_FM_MOD_10G_MAC:                                                                      \
            if (id) event = e_FM_EV_DUMMY_LAST;                                                     \
            else event = (intrType == e_FM_INTR_TYPE_ERR) ? e_FM_EV_ERR_10G_MAC0 : e_FM_EV_DUMMY_LAST;\
            break;                                                                                  \
        case e_FM_MOD_1G_MAC:                                                                       \
            switch(id){                                                                             \
                 case(0): event = (intrType == e_FM_INTR_TYPE_ERR) ? e_FM_EV_ERR_1G_MAC0 : e_FM_EV_DUMMY_LAST; break; \
                 case(1): event = (intrType == e_FM_INTR_TYPE_ERR) ? e_FM_EV_ERR_1G_MAC1 : e_FM_EV_DUMMY_LAST; break; \
                 case(2): event = (intrType == e_FM_INTR_TYPE_ERR) ? e_FM_EV_ERR_1G_MAC2 : e_FM_EV_DUMMY_LAST; break; \
                 case(3): event = (intrType == e_FM_INTR_TYPE_ERR) ? e_FM_EV_ERR_1G_MAC3 : e_FM_EV_DUMMY_LAST; break; \
                 case(4): event = (intrType == e_FM_INTR_TYPE_ERR) ? e_FM_EV_ERR_1G_MAC4 : e_FM_EV_DUMMY_LAST; break; \
                 }                                                                                  \
            break;                                                                                  \
        case e_FM_MOD_TMR:                                                                          \
            if (id) event = e_FM_EV_DUMMY_LAST;                                                     \
            else event = (intrType == e_FM_INTR_TYPE_ERR) ? e_FM_EV_DUMMY_LAST : e_FM_EV_TMR;       \
            break;                                                                                  \
        case e_FM_MOD_1G_MAC_TMR:                                                                   \
            switch(id){                                                                             \
                 case(0): event = (intrType == e_FM_INTR_TYPE_ERR) ? e_FM_EV_DUMMY_LAST : e_FM_EV_1G_MAC0_TMR; break;\
                 case(1): event = (intrType == e_FM_INTR_TYPE_ERR) ? e_FM_EV_DUMMY_LAST : e_FM_EV_1G_MAC1_TMR; break;\
                 case(2): event = (intrType == e_FM_INTR_TYPE_ERR) ? e_FM_EV_DUMMY_LAST : e_FM_EV_1G_MAC2_TMR; break;\
                 case(3): event = (intrType == e_FM_INTR_TYPE_ERR) ? e_FM_EV_DUMMY_LAST : e_FM_EV_1G_MAC3_TMR; break;\
                 case(4): event = (intrType == e_FM_INTR_TYPE_ERR) ? e_FM_EV_DUMMY_LAST : e_FM_EV_1G_MAC4_TMR; break;\
                 }                                                                                  \
            break;                                                                                  \
        case e_FM_MOD_FMAN_CTRL:                                                                    \
            if (intrType == e_FM_INTR_TYPE_ERR) event = e_FM_EV_DUMMY_LAST;                         \
            else switch(id){                                                                        \
                 case(0): event = e_FM_EV_FMAN_CTRL_0; break;                                       \
                 case(1): event = e_FM_EV_FMAN_CTRL_1; break;                                       \
                 case(2): event = e_FM_EV_FMAN_CTRL_2; break;                                       \
                 case(3): event = e_FM_EV_FMAN_CTRL_3; break;                                       \
                 }                                                                                  \
            break;                                                                                  \
        default: event = e_FM_EV_DUMMY_LAST;                                                        \
        break;}

#define FM_CHECK_PORT_RESTRICTIONS(__validPorts, __newPortIndx)   TRUE

/* p4080-rev1 unique features */
#define FM_PARTITION_ARRAY
#define FM_PPPOE_NO_MTU_CHECK
#define FM_NO_THRESHOLD_REG

/* p4080 unique features */
#define FM_QMI_DEQ_OPTIONS_SUPPORT
#define FM_NO_DISPATCH_RAM_ECC

/* FM erratas */

#define FM_TX_ECC_FRMS_ERRATA_10GMAC_A004
#define FM_TX_SHORT_FRAME_BAD_TS_ERRATA_10GMAC_A006     /* No implementation, Out of LLD scope */
#define FM_TX_FIFO_CORRUPTION_ERRATA_10GMAC_A007
#define FM_ECC_HALT_NO_SYNC_ERRATA_10GMAC_A008
#define FM_BAD_VLAN_DETECT_ERRATA_10GMAC_A010

//TODO!!! #define FM_NO_RX_PREAM_ERRATA_DTSECx1
#define FM_RX_PREAM_4_ERRATA_DTSEC_A001
#define FM_MAGIC_PACKET_UNRECOGNIZED_ERRATA_DTSEC2              /* No implementation, Out of LLD scope */
#define FM_GRS_ERRATA_DTSEC_A002
#define FM_BAD_TX_TS_IN_B_2_B_ERRATA_DTSEC_A003
#define FM_GTS_ERRATA_DTSEC_A004
#define FM_GTS_AFTER_MAC_ABORTED_FRAME_ERRATA_DTSEC_A0012
#define FM_GTS_UNDERRUN_ERRATA_DTSEC_A0014

#define FM_MAGIC_PACKET_UNRECOGNIZED_ERRATA_DTSEC2          /* No implementation, Out of LLD scope */
//TODO!!! #define FM_10_100_SGMII_NO_TS_ERRATA_DTSEC3
#define FM_TX_LOCKUP_ERRATA_DTSEC6

#define FM_HC_DEF_FQID_ONLY_ERRATA_FMAN_A003                /* Implemented by ucode */
#define FM_DEBUG_TRACE_FMAN_A004                            /* No implementation, Out of LLD scope */

#define FM_UCODE_NOT_RESET_ERRATA_BUGZILLA6173

#define FM_LEN_CHECK_ERRATA_FMAN_SW002
#define FM_PRS_MEM_ERRATA_FMAN_SW003
#define FM_10G_REM_N_LCL_FLT_EX_10GMAC_ERRATA_SW005

#if defined(FM_IPSEC_SUPPORT) || defined(FM_IP_FRAG_N_REASSEM_SUPPORT)
#define FM_NO_CTXA_COPY_ERRATA_FMAN_SW001
#define FM_KG_ERASE_FLOW_ID_ERRATA_FMAN_SW004
#ifdef FM_IPSEC_SUPPORT
#define FM_DISABLE_UDP_CHECKSUM_AFTER_SEC
#define FM_UPDATE_UDP_LENGTH_AFTER_SEC
#define FM_ETH_TYPE_FIX
#define FM_DISABLE_SEC_ERRORS
#endif /* FM_IPSEC_SUPPORT */
#endif /* defined(FM_IPSEC_SUPPORT) || ... */


#endif /* __DPAA_INTEGRATION_P3_P4_P5_H */