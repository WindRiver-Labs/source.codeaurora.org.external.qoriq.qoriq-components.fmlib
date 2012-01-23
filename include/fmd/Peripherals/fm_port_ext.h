/******************************************************************************

 � 1995-2003, 2004, 2005-2011 Freescale Semiconductor, Inc.
 All rights reserved.

 This is proprietary source code of Freescale Semiconductor Inc.,
 and its use is subject to the NetComm Device Drivers EULA.
 The copyright notice above does not evidence any actual or intended
 publication of such source code.

 **************************************************************************/
/**************************************************************************//**
 @File          fm_port_ext.h

 @Description   FM-Port Application Programming Interface.
*//***************************************************************************/
#ifndef __FM_PORT_EXT
#define __FM_PORT_EXT

#include "error_ext.h"
#include "std_ext.h"
#include "fm_pcd_ext.h"
#include "fm_ext.h"
#include "net_ext.h"


/**************************************************************************//**

 @Group         lnx_usr_FM_grp Frame Manager API

 @Description   FM API functions, definitions and enums

 @{
*//***************************************************************************/

/**************************************************************************//**
 @Group         lnx_usr_FM_PORT_grp FM Port

 @Description   FM Port API

                The FM uses a general module called "port" to represent a Tx port
                (MAC), an Rx port (MAC), offline parsing flow or host command
                flow. There may be up to 17 (may change) ports in an FM - 5 Tx
                ports (4 for the 1G MACs, 1 for the 10G MAC), 5 Rx Ports, and 7
                Host command/Offline parsing ports. The SW driver manages these
                ports as sub-modules of the FM, i.e. after an FM is initialized,
                its ports may be initialized and operated upon.

                The port is initialized aware of its type, but other functions on
                a port may be indifferent to its type. When necessary, the driver
                verifies coherency and returns error if applicable.

                On initialization, user specifies the port type and it's index
                (relative to the port's type). Host command and Offline parsing
                ports share the same id range, I.e user may not initialized host
                command port 0 and offline parsing port 0.

 @{
*//***************************************************************************/

/**************************************************************************//**
 @Description   An enum for defining port PCD modes.
                This enum defines the superset of PCD engines support - i.e. not
                all engines have to be used, but all have to be enabled. The real
                flow of a specific frame depends on the PCD configuration and the
                frame headers and payload.
*//***************************************************************************/
typedef enum e_FmPortPcdSupport {
      e_FM_PORT_PCD_SUPPORT_NONE = 0                /**< BMI to BMI, PCD is not used */
    , e_FM_PORT_PCD_SUPPORT_PRS_ONLY                /**< Use only Parser */
    , e_FM_PORT_PCD_SUPPORT_PLCR_ONLY               /**< Use only Policer */
    , e_FM_PORT_PCD_SUPPORT_PRS_AND_PLCR            /**< Use Parser and Policer */
    , e_FM_PORT_PCD_SUPPORT_PRS_AND_KG              /**< Use Parser and Keygen */
    , e_FM_PORT_PCD_SUPPORT_PRS_AND_KG_AND_CC       /**< Use Parser, Keygen and Coarse Classification */
    , e_FM_PORT_PCD_SUPPORT_PRS_AND_KG_AND_CC_AND_PLCR
                                                    /**< Use all PCD engines */
    , e_FM_PORT_PCD_SUPPORT_PRS_AND_KG_AND_PLCR     /**< Use Parser, Keygen and Policer */
#if defined(FM_IPSEC_SUPPORT) || defined(FM_IP_FRAG_N_REASSEM_SUPPORT)
    , e_FM_PORT_PCD_SUPPORT_PRS_AND_CC              /**< Use Parser and Coarse Classification */
#endif /* defined(FM_IPSEC_SUPPORT) || defined(FM_IP_FRAG_N_REASSEM_SUPPORT) */
#ifdef FM_CAPWAP_SUPPORT
    , e_FM_PORT_PCD_SUPPORT_CC_ONLY                 /**< Use only Coarse Classification */
    , e_FM_PORT_PCD_SUPPORT_CC_AND_KG               /**< Use Coarse Classification,and Keygen */
    , e_FM_PORT_PCD_SUPPORT_CC_AND_KG_AND_PLCR      /**< Use Coarse Classification, Keygen and Policer */
#endif /* FM_CAPWAP_SUPPORT */
} e_FmPortPcdSupport;

/**************************************************************************//**
 @Collection    General FM Port defines
*//***************************************************************************/
#define FM_PORT_PRS_RESULT_NUM_OF_WORDS     8   /**< Number of 4 bytes words in parser result */
/* @} */

/**************************************************************************//**
 @Collection   FM Frame error
*//***************************************************************************/
typedef uint32_t    fmPortFrameErrSelect_t;                         /**< typedef for defining Frame Descriptor errors */

#define FM_PORT_FRM_ERR_UNSUPPORTED_FORMAT              0x04000000  /**< Offline parsing only! Unsupported Format */
#define FM_PORT_FRM_ERR_LENGTH                          0x02000000  /**< Offline parsing only! Length Error */
#define FM_PORT_FRM_ERR_DMA                             0x01000000  /**< DMA Data error */
#ifdef FM_DISABLE_SEC_ERRORS
#define FM_PORT_FRM_ERR_NON_FM                          0x00400000  /**< non Frame-Manager error; probably come from SEC that
                                                                         was chained to FM */
#endif /* FM_DISABLE_SEC_ERRORS */
#ifdef FM_IP_FRAG_N_REASSEM_SUPPORT
#define FM_PORT_FRM_ERR_IPRE                            0x00200000
#define FM_PORT_FRM_ERR_IPFE                            0x00100000
#endif /* FM_IP_FRAG_N_REASSEM_SUPPORT */

#ifdef FM_CAPWAP_SUPPORT
#define FM_PORT_FRM_ERR_CRE                             0x00200000
#define FM_PORT_FRM_ERR_CHE                             0x00100000
#endif /* FM_CAPWAP_SUPPORT */

#define FM_PORT_FRM_ERR_PHYSICAL                        0x00080000  /**< Rx FIFO overflow, FCS error, code error, running disparity
                                                                         error (SGMII and TBI modes), FIFO parity error. PHY
                                                                         Sequence error, PHY error control character detected. */
#define FM_PORT_FRM_ERR_SIZE                            0x00040000  /**< Frame too long OR Frame size exceeds max_length_frame  */
#define FM_PORT_FRM_ERR_CLS_DISCARD                     0x00020000  /**< classification discard */
#define FM_PORT_FRM_ERR_EXTRACTION                      0x00008000  /**< Extract Out of Frame */
#define FM_PORT_FRM_ERR_NO_SCHEME                       0x00004000  /**< No Scheme Selected */
#define FM_PORT_FRM_ERR_KEYSIZE_OVERFLOW                0x00002000  /**< Keysize Overflow */
#define FM_PORT_FRM_ERR_COLOR_YELLOW                    0x00000400  /**< Frame color is yellow */
#define FM_PORT_FRM_ERR_COLOR_RED                       0x00000800  /**< Frame color is red */
#define FM_PORT_FRM_ERR_ILL_PLCR                        0x00000200  /**< Illegal Policer Profile selected */
#define FM_PORT_FRM_ERR_PLCR_FRAME_LEN                  0x00000100  /**< Policer frame length error */
#define FM_PORT_FRM_ERR_PRS_TIMEOUT                     0x00000080  /**< Parser Time out Exceed */
#define FM_PORT_FRM_ERR_PRS_ILL_INSTRUCT                0x00000040  /**< Invalid Soft Parser instruction */
#define FM_PORT_FRM_ERR_PRS_HDR_ERR                     0x00000020  /**< Header error was identified during parsing */
#define FM_PORT_FRM_ERR_BLOCK_LIMIT_EXCEEDED            0x00000008  /**< Frame parsed beyind 256 first bytes */
#define FM_PORT_FRM_ERR_PROCESS_TIMEOUT                 0x00000001  /**< FPM Frame Processing Timeout Exceeded */
/* @} */

/**************************************************************************//**
 @Description   structure representing FM initialization parameters
*//***************************************************************************/
typedef struct t_FmPortParams {
    t_Handle                    h_Fm;               /**< A handle to the FM object this port belongs to */
    t_Handle                    h_FmPcd;            /**< A handle to the FM PCD object used by this port */

    e_FmPortType                portType;           /**< Port type */
    uint8_t                     portId;             /**< Port Id - relative to type */
} t_FmPortParams;


t_Handle FM_PORT_Open(t_FmPortParams *p_FmPortParams);
void     FM_PORT_Close(t_Handle h_FmPort);

/**************************************************************************//**
 @Group         lnx_usr_FM_PORT_runtime_control_grp FM Port Runtime Control Unit

 @Description   FM Port Runtime control unit API functions, definitions and enums.

 @{
*//***************************************************************************/

/**************************************************************************//**
 @Description   struct for defining Dual Tx rate limiting scale
*//***************************************************************************/
typedef enum e_FmPortDualRateLimiterScaleDown {
    e_FM_PORT_DUAL_RATE_LIMITER_NONE = 0,           /**< Use only single rate limiter  */
    e_FM_PORT_DUAL_RATE_LIMITER_SCALE_DOWN_BY_2,    /**< Divide high rate limiter by 2 */
    e_FM_PORT_DUAL_RATE_LIMITER_SCALE_DOWN_BY_4,    /**< Divide high rate limiter by 4 */
    e_FM_PORT_DUAL_RATE_LIMITER_SCALE_DOWN_BY_8     /**< Divide high rate limiter by 8 */
} e_FmPortDualRateLimiterScaleDown;

/**************************************************************************//**
 @Description   struct for defining Tx rate limiting
*//***************************************************************************/
typedef struct t_FmPortRateLimit {
    uint16_t                            maxBurstSize;           /**< in KBytes for Tx ports, in frames
                                                                     for offline parsing ports. (note that
                                                                     for early chips burst size is
                                                                     rounded up to a multiply of 1000 frames).*/
    uint32_t                            rateLimit;              /**< in Kb/sec for Tx ports, in frame/sec for
                                                                     offline parsing ports. Rate limit refers to
                                                                     data rate (rather than line rate). */
    e_FmPortDualRateLimiterScaleDown    rateLimitDivider;       /**< For offline parsing ports only. Not-valid
                                                                     for some earlier chip revisions */
} t_FmPortRateLimit;

/**************************************************************************//**
 @Function      FM_PORT_Disable

 @Description   Gracefully disable an FM port. The port will not start new tasks after all
                tasks associated with the port are terminated.

 @Param[in]     h_FmPort    A handle to a FM Port module.

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_PORT_Init().
                This is a blocking routine, it returns after port is
                gracefully stopped, i.e. the port will not except new frames,
                but it will finish all frames or tasks which were already began
*//***************************************************************************/
t_Error FM_PORT_Disable(t_Handle h_FmPort);

/**************************************************************************//**
 @Function      FM_PORT_Enable

 @Description   A runtime routine provided to allow disable/enable of port.

 @Param[in]     h_FmPort    A handle to a FM Port module.

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_PORT_Init().
*//***************************************************************************/
t_Error FM_PORT_Enable(t_Handle h_FmPort);

/**************************************************************************//**
 @Function      FM_PORT_SetRateLimit

 @Description   Calling this routine enables rate limit algorithm.
                By default, this functionality is disabled.
                Note that rate-limit mechanism uses the FM time stamp.
                The selected rate limit specified here would be
                rounded DOWN to the nearest 16M.

                May be used for Tx and offline parsing ports only

 @Param[in]     h_FmPort        A handle to a FM Port module.
 @Param[in]     p_RateLimit     A structure of rate limit parameters

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_PORT_Init().
*//***************************************************************************/
t_Error FM_PORT_SetRateLimit(t_Handle h_FmPort, t_FmPortRateLimit *p_RateLimit);

/**************************************************************************//**
 @Function      FM_PORT_DeleteRateLimit

 @Description   Calling this routine disables and clears rate limit
                initialization.

                May be used for Tx and offline parsing ports only

 @Param[in]     h_FmPort        A handle to a FM Port module.

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_PORT_Init().
*//***************************************************************************/
t_Error FM_PORT_DeleteRateLimit(t_Handle h_FmPort);


/**************************************************************************//**
 @Function      FM_PORT_SetErrorsRoute

 @Description   Errors selected for this routine will cause a frame with that error
                to be enqueued to error queue.
                Errors not selected for this routine will cause a frame with that error
                to be enqueued to the one of the other port queues.
                By default all errors are defined to be enqueued to error queue.
                Errors that were configured to be discarded (at initialization)
                may not be selected here.

                May be used for Rx and offline parsing ports only

 @Param[in]     h_FmPort    A handle to a FM Port module.
 @Param[in]     errs        A list of errors to enqueue to error queue

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_PORT_Config() and before FM_PORT_Init().
*//***************************************************************************/
t_Error FM_PORT_SetErrorsRoute(t_Handle h_FmPort, fmPortFrameErrSelect_t errs);

#if defined(FM_IPSEC_SUPPORT) || defined(FM_IP_FRAG_N_REASSEM_SUPPORT)
/**************************************************************************//**
 @Function      FM_PORT_SetOpWorkarounds

 @Description   Calling this routine sets the required offline port workaround.

 @Param[in]     h_FmPort        FM PORT module descriptor.
 @Param[in]     workarounds)    Reuired workaround.

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_PORT_Init().
*//***************************************************************************/
t_Error FM_PORT_SetOpWorkarounds(t_Handle h_FmPort, fmOpPortWorkaroundsSelect_t workarounds);
#endif /* defined(FM_IPSEC_SUPPORT) || defined(FM_IP_FRAG_N_REASSEM_SUPPORT) */

/**************************************************************************//**
 @Group         lnx_usr_FM_PORT_pcd_runtime_control_grp FM Port PCD Runtime Control Unit

 @Description   FM Port PCD Runtime control unit API functions, definitions and enums.

 @{
*//***************************************************************************/

/**************************************************************************//**
 @Description   A structure defining the KG scheme after the parser.
                This is relevant only to change scheme selection mode - from
                direct to indirect and vice versa, or when the scheme is selected directly,
                to select the scheme id.

*//***************************************************************************/
typedef struct t_FmPcdKgSchemeSelect {
    bool        direct;                 /**< TRUE to use 'h_Scheme' directly, FALSE to use LCV. */
    t_Handle    h_DirectScheme;         /**< Scheme handle, selects the scheme after parser;
                                             Relevant only when 'direct' is TRUE. */
} t_FmPcdKgSchemeSelect;

/**************************************************************************//**
 @Description   A structure of scheme parameters
*//***************************************************************************/
typedef struct t_FmPcdPortSchemesParams {
    uint8_t     numOfSchemes;                           /**< Number of schemes for port to be bound to. */
    t_Handle    h_Schemes[FM_PCD_KG_NUM_OF_SCHEMES];    /**< Array of 'numOfSchemes' schemes for the
                                                             port to be bound to */
} t_FmPcdPortSchemesParams;

/**************************************************************************//**
 @Description   Union for defining port protocol parameters for parser
*//***************************************************************************/
typedef union u_FmPcdHdrPrsOpts {
    /* MPLS */
    struct {
        bool            labelInterpretationEnable;  /**< When this bit is set, the last MPLS label will be
                                                         interpreted as described in HW spec table. When the bit
                                                         is cleared, the parser will advance to MPLS next parse */
        e_NetHeaderType nextParse;                  /**< must be equal or higher than IPv4 */
    } mplsPrsOptions;
    /* VLAN */
    struct {
        uint16_t        tagProtocolId1;             /**< User defined Tag Protocol Identifier, to be recognized
                                                         on VLAN TAG on top of 0x8100 and 0x88A8 */
        uint16_t        tagProtocolId2;             /**< User defined Tag Protocol Identifier, to be recognized
                                                         on VLAN TAG on top of 0x8100 and 0x88A8 */
    } vlanPrsOptions;
    /* PPP */
    struct{
        bool            enableMTUCheck;             /**< Check validity of MTU according to RFC2516 */
    } pppoePrsOptions;

    /* IPV6 */
    struct{
        bool            routingHdrDisable;          /**< Disable routing header */
    } ipv6PrsOptions;

    /* UDP */
    struct{
        bool            padIgnoreChecksum;          /**< TRUE to ignore pad in checksum */
    } udpPrsOptions;

    /* TCP */
    struct {
        bool            padIgnoreChecksum;          /**< TRUE to ignore pad in checksum */
    } tcpPrsOptions;
} u_FmPcdHdrPrsOpts;

/**************************************************************************//**
 @Description   A structure for defining each header for the parser
*//***************************************************************************/
typedef struct t_FmPcdPrsAdditionalHdrParams {
    e_NetHeaderType         hdr;            /**< Selected header */
    bool                    errDisable;     /**< TRUE to disable error indication */
    bool                    swPrsEnable;    /**< Enable jump to SW parser when this
                                                 header is recognized by the HW parser. */
    uint8_t                 indexPerHdr;    /**< Normally 0, if more than one sw parser
                                                 attachments exists for the same header,
                                                 (in the main sw parser code) use this
                                                 index to distinguish between them. */
    bool                    usePrsOpts;     /**< TRUE to use parser options. */
    u_FmPcdHdrPrsOpts       prsOpts;        /**< A union according to header type,
                                                 defining the parser options selected.*/
} t_FmPcdPrsAdditionalHdrParams;

/**************************************************************************//**
 @Description   struct for defining port PCD parameters
*//***************************************************************************/
typedef struct t_FmPortPcdPrsParams {
    uint8_t                         prsResultPrivateInfo;           /**< The private info provides a method of inserting
                                                                         port information into the parser result. This information
                                                                         may be extracted by Keygen and be used for frames
                                                                         distribution when a per-port distinction is required,
                                                                         it may also be used as a port logical id for analyzing
                                                                         incoming frames. */
    uint8_t                         parsingOffset;                  /**< Number of bytes from beginning of packet to start parsing */
    e_NetHeaderType                 firstPrsHdr;                    /**< The type of the first header expected at 'parsingOffset' */
    bool                            includeInPrsStatistics;         /**< TRUE to include this port in the parser statistics;
                                                                         NOTE: this field is not valid when the FN is in "guest" mode. */
    uint8_t                         numOfHdrsWithAdditionalParams;  /**< Normally 0, some headers may get
                                                                         special parameters */
    t_FmPcdPrsAdditionalHdrParams   additionalParams[FM_PCD_PRS_NUM_OF_HDRS];
                                                                    /**< 'numOfHdrsWithAdditionalParams'  structures
                                                                         of additional parameters
                                                                         for each header that requires them */
    bool                            setVlanTpid1;                   /**< TRUE to configure user selection of Ethertype to
                                                                         indicate a VLAN tag (in addition to the TPID values
                                                                         0x8100 and 0x88A8). */
    uint16_t                        vlanTpid1;                      /**< extra tag to use if setVlanTpid1=TRUE. */
    bool                            setVlanTpid2;                   /**< TRUE to configure user selection of Ethertype to
                                                                         indicate a VLAN tag (in addition to the TPID values
                                                                         0x8100 and 0x88A8). */
    uint16_t                        vlanTpid2;                      /**< extra tag to use if setVlanTpid1=TRUE. */
} t_FmPortPcdPrsParams;

/**************************************************************************//**
 @Description   struct for defining coarse alassification parameters
*//***************************************************************************/
typedef struct t_FmPortPcdCcParams {
    t_Handle            h_CcTree;                       /**< A handle to a CC tree */
} t_FmPortPcdCcParams;

/**************************************************************************//**
 @Description   struct for defining keygen parameters
*//***************************************************************************/
typedef struct t_FmPortPcdKgParams {
    uint8_t             numOfSchemes;                   /**< Number of schemes for port to be bound to. */
    t_Handle            h_Schemes[FM_PCD_KG_NUM_OF_SCHEMES];
                                                        /**< Array of 'numOfSchemes' schemes handles for the
                                                             port to be bound to */
    bool                directScheme;                   /**< TRUE for going from parser to a specific scheme,
                                                             regardless of parser result */
    t_Handle            h_DirectScheme;                 /**< relevant only if direct == TRUE, Scheme handle,
                                                             as returned by FM_PCD_KgSetScheme */
} t_FmPortPcdKgParams;

/**************************************************************************//**
 @Description   struct for defining policer parameters
*//***************************************************************************/
typedef struct t_FmPortPcdPlcrParams {
    t_Handle                h_Profile;          /**< Selected profile handle; Relevant for one of
                                                     following cases:
                                                     e_FM_PORT_PCD_SUPPORT_PLCR_ONLY or
                                                     e_FM_PORT_PCD_SUPPORT_PRS_AND_PLCR were selected,
                                                     or if any flow uses a KG scheme were policer
                                                     profile is not generated
                                                     (bypassPlcrProfileGeneration selected) */
} t_FmPortPcdPlcrParams;

/**************************************************************************//**
 @Description   struct for defining port PCD parameters
*//***************************************************************************/
typedef struct t_FmPortPcdParams {
    e_FmPortPcdSupport      pcdSupport;         /**< Relevant for Rx and offline ports only.
                                                     Describes the active PCD engines for this port. */
    t_Handle                h_NetEnv;           /**< HL Unused in PLCR only mode */
    t_FmPortPcdPrsParams    *p_PrsParams;       /**< Parser parameters for this port */
    t_FmPortPcdCcParams     *p_CcParams;        /**< Coarse classification parameters for this port */
    t_FmPortPcdKgParams     *p_KgParams;        /**< Keygen parameters for this port */
    t_FmPortPcdPlcrParams   *p_PlcrParams;      /**< Policer parameters for this port */
} t_FmPortPcdParams;

/**************************************************************************//**
 @Description   A structure for defining the Parser starting point
*//***************************************************************************/
typedef struct t_FmPcdPrsStart {
    uint8_t             parsingOffset;  /**< Number of bytes from beginning of packet to
                                             start parsing */
    e_NetHeaderType     firstPrsHdr;    /**< The type of the first header axpected at
                                             'parsingOffset' */
} t_FmPcdPrsStart;


/**************************************************************************//**
 @Function      FM_PORT_SetPCD

 @Description   Calling this routine defines the port's PCD configuration.
                It changes it from its default configuration which is PCD
                disabled (BMI to BMI) and configures it according to the passed
                parameters.

                May be used for Rx and offline parsing ports only

 @Param[in]     h_FmPort        A handle to a FM Port module.
 @Param[in]     p_FmPortPcd     A Structure of parameters defining the port's PCD
                                configuration.

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_PORT_Init().
*//***************************************************************************/
t_Error FM_PORT_SetPCD(t_Handle h_FmPort, t_FmPortPcdParams *p_FmPortPcd);

/**************************************************************************//**
 @Function      FM_PORT_DeletePCD

 @Description   Calling this routine releases the port's PCD configuration.
                The port returns to its default configuration which is PCD
                disabled (BMI to BMI) and all PCD configuration is removed.

                May be used for Rx and offline parsing ports which are
                in PCD mode  only

 @Param[in]     h_FmPort        A handle to a FM Port module.

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_PORT_Init().
*//***************************************************************************/
t_Error FM_PORT_DeletePCD(t_Handle h_FmPort);

/**************************************************************************//**
 @Function      FM_PORT_AttachPCD

 @Description   This routine may be called after FM_PORT_DetachPCD was called,
                to return to the originally configured PCD support flow.
                The couple of routines are used to allow PCD configuration changes
                that demand that PCD will not be used while changes take place.

                May be used for Rx and offline parsing ports which are
                in PCD mode only

 @Param[in]     h_FmPort        A handle to a FM Port module.

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_PORT_Init().
*//***************************************************************************/
t_Error FM_PORT_AttachPCD(t_Handle h_FmPort);

/**************************************************************************//**
 @Function      FM_PORT_DetachPCD

 @Description   Calling this routine detaches the port from its PCD functionality.
                The port returns to its default flow which is BMI to BMI.

                May be used for Rx and offline parsing ports which are
                in PCD mode only

 @Param[in]     h_FmPort        A handle to a FM Port module.

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_PORT_AttachPCD().
*//***************************************************************************/
t_Error FM_PORT_DetachPCD(t_Handle h_FmPort);

/**************************************************************************//**
 @Function      FM_PORT_PcdPlcrAllocProfiles

 @Description   This routine may be called only for ports that use the Policer in
                order to allocate private policer profiles.

 @Param[in]     h_FmPort            A handle to a FM Port module.
 @Param[in]     numOfProfiles       The number of required policer profiles

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_PORT_Init() and FM_PCD_Init(), and before FM_PORT_SetPCD().
*//***************************************************************************/
t_Error FM_PORT_PcdPlcrAllocProfiles(t_Handle h_FmPort, uint16_t numOfProfiles);

/**************************************************************************//**
 @Function      FM_PORT_PcdPlcrFreeProfiles

 @Description   This routine should be called for freeing private policer profiles.

 @Param[in]     h_FmPort            A handle to a FM Port module.

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_PORT_Init() and FM_PCD_Init(), and before FM_PORT_SetPCD().
*//***************************************************************************/
t_Error FM_PORT_PcdPlcrFreeProfiles(t_Handle h_FmPort);

/**************************************************************************//**
 @Function      FM_PORT_PcdKgModifyInitialScheme

 @Description   This routine may be called only for ports that use the keygen in
                order to change the initial scheme frame should be routed to.
                The change may be of a scheme id (in case of direct mode),
                from direct to indirect, or from indirect to direct - specifying the scheme id.

 @Param[in]     h_FmPort            A handle to a FM Port module.
 @Param[in]     p_FmPcdKgScheme     A structure of parameters for defining whether
                                    a scheme is direct/indirect, and if direct - scheme id.

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_PORT_Init() and FM_PORT_SetPCD().
*//***************************************************************************/
t_Error FM_PORT_PcdKgModifyInitialScheme (t_Handle h_FmPort, t_FmPcdKgSchemeSelect *p_FmPcdKgScheme);

/**************************************************************************//**
 @Function      FM_PORT_PcdPlcrModifyInitialProfile

 @Description   This routine may be called for ports with flows
                e_FM_PORT_PCD_SUPPORT_PLCR_ONLY or e_FM_PORT_PCD_SUPPORT_PRS_AND_PLCR
                only, to change the initial Policer profile frame should be
                routed to. The change may be of a profile and/or absolute/direct
                mode selection.

 @Param[in]     h_FmPort                A handle to a FM Port module.
 @Param[in]     h_Profile               Policer profile handle

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_PORT_Init() and FM_PORT_SetPCD().
*//***************************************************************************/
t_Error FM_PORT_PcdPlcrModifyInitialProfile (t_Handle h_FmPort, t_Handle h_Profile);

/**************************************************************************//**
 @Function      FM_PORT_PcdCcModifyTree

 @Description   This routine may be called for ports that use coarse classification tree
                if the user wishes to replace the tree. The routine may not be called while port
                receives packets using the PCD functionalities, therefor port must be first detached
                from the PCD, only than the routine may be called, and than port be attached to PCD again.

 @Param[in]     h_FmPort            A handle to a FM Port module.
 @Param[in]     h_CcTree            A CC tree that was already built. The tree id as returned from
                                    the BuildTree routine.

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_PORT_Init(), FM_PORT_SetPCD() and FM_PORT_DetachPCD()
*//***************************************************************************/
t_Error FM_PORT_PcdCcModifyTree (t_Handle h_FmPort, t_Handle h_CcTree);

/**************************************************************************//**
 @Function      FM_PORT_PcdKgBindSchemes

 @Description   These routines may be called for adding more schemes for the
                port to be bound to. The selected schemes are not added,
                just this specific port starts using them.

 @Param[in]     h_FmPort        A handle to a FM Port module.
 @Param[in]     p_PortScheme    A structure defining the list of schemes to be added.

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_PORT_Init() and FM_PORT_SetPCD().
*//***************************************************************************/
t_Error FM_PORT_PcdKgBindSchemes (t_Handle h_FmPort, t_FmPcdPortSchemesParams *p_PortScheme);

/**************************************************************************//**
 @Function      FM_PORT_PcdKgUnbindSchemes

 @Description   These routines may be called for adding more schemes for the
                port to be bound to. The selected schemes are not removed or invalidated,
                just this specific port stops using them.

 @Param[in]     h_FmPort        A handle to a FM Port module.
 @Param[in]     p_PortScheme    A structure defining the list of schemes to be added.

 @Return        E_OK on success; Error code otherwise.

 @Cautions      Allowed only following FM_PORT_Init() and FM_PORT_SetPCD().
*//***************************************************************************/
t_Error FM_PORT_PcdKgUnbindSchemes (t_Handle h_FmPort, t_FmPcdPortSchemesParams *p_PortScheme);


/** @} */ /* end of lnx_usr_FM_PORT_pcd_runtime_control_grp group */


/**************************************************************************//**
 @Group         lnx_usr_FM_PORT_runtime_data_grp FM Port Runtime Data-path Unit

 @Description   FM Port Runtime data unit API functions, definitions and enums.
                This API is valid only if working in Independent-Mode.

 @{
*//***************************************************************************/

/**************************************************************************//**
 @Function      FM_PORT_AllocPCDFqids

 @Description   Allocates a sequence of consecutive FQIDs for this port's use.

 @Param[in]     h_FmPort            A handle to a FM Port module.
 @Param[in]     num_Fqids           # of FQIDs to allocate
 @Param[in]     alignment           First FQID may need to be aligned
                                    to this value (watch out, as passing in
                                    a zero here can spell "trouble"!)

 @Return        The first of the allocated consecutive FQIDs;
                0 on error (0 is an invalid FQID, too)

 @Cautions      Try not to pass in zero for alignment!
*//***************************************************************************/
uint32_t FM_PORT_AllocPCDFqids (t_Handle h_FmPort, uint32_t numFqids, uint8_t alignment);

/**************************************************************************//**
 @Function      FM_PORT_FreePCDFqids

 @Description   Frees a previously-allocated range of consecutive FQIDs
                for this port's use.

 @Param[in]     h_FmPort            A handle to a FM Port module.
 @Param[in]     base_fqid           Base FQID of previously-allocated range.

 @Return        Error code, or 0 on success.
*//***************************************************************************/
t_Error FM_PORT_FreePCDFqids (t_Handle h_FmPort, uint32_t base_fqid);

/** @} */ /* end of lnx_usr_FM_PORT_runtime_data_grp group */
/** @} */ /* end of lnx_usr_FM_PORT_grp group */
/** @} */ /* end of lnx_usr_FM_grp group */

#endif /* __FM_PORT_EXT */