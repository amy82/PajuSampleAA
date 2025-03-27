/*****************************************************************************
* RapidIO Trade Association Confidential
******************************************************************************/

/*-----------------------------------------------------------------------------
* FILENAME: rio.h
*
* DESCRIPTION: Header file contains the RapidIO Capability, Command and Status
*              and Physical 8/16 LP-LVDS register offsets as well as bitfield 
*              masks compliant to the version 1.2 of the RapidIO Parallel 
*              specification and to the version 1.2 of the LP-Serial 
*              Specification. Serial specific defines are marked as SRIO.
*
* HISTORY:
*
*    Rev. Date       Author  Description
*    ---- ---------  ------  ------------------------------------------
*    0.02 Jul 24,02  nvo     copyright fixed
*    0.01 Jun 20,02  nvo     draft
*
*----------------------------------------------------------------------------*/

#ifndef _RIO_H_
#define _RIO_H_


/****************************************************************************** 
 *
 * RapidIO Capability registers 
 *
 *****************************************************************************/ 

#define RIO_DEV_ID_CAR               (0x00)  
#define RIO_DEV_INFO_CAR             (0x04)  
#define RIO_ASSEMBLY_ID_CAR          (0x08)  
#define RIO_ASSEMBLY_INFO_CAR        (0x0C)  
#define RIO_PE_FEATURES_CAR          (0x10)  /* PE == Processing Element */
#define RIO_SW_PORT_INFO_CAR         (0x14)  /* SW == Switch */
#define RIO_SOURCE_OP_CAR            (0x18)  /* OP == Operation */
#define RIO_DEST_OP_CAR              (0x1C)  


/****************************************************************************** 
 *
 * RapidIO Command and Status registers 
 *
 *****************************************************************************/ 

#define RIO_MAILBOX_CSR              (0x40)  
#define RIO_DOORBELL_WRITE_PORT_CSR  (0x44)  
#define RIO_PE_LL_CTL_CSR            (0x4c)  /* PE Logical Layer Control CSR */
#define RIO_CFG_HBAR_CSR             (0x58)  /* Local ConfigSpace BAR (High) */
#define RIO_CFG_LBAR_CSR             (0x5c)  /* Local ConfigSpace BAR (Low) */
#define RIO_BASE_DEV_ID_CSR          (0x60)  
#define RIO_HOST_BASE_DEV_ID_CSR     (0x68)  
#define RIO_COMP_TAG_CSR             (0x6C)  /* Component Tag CSR */


/****************************************************************************** 
 *
 * The Physical Layer 8/16 LP-LVDS registers 
 *
 *****************************************************************************/ 

/* Extended Feature's Block ID is field in Port Maintenance Block Header register 
 * and it defines what type of header (subset of registers and fields) should be 
 * used for given Extended Feature */

/* Parallel Extended Feature's Block IDs */
#define RIO_PORT_MBH_H_EF_BID_EP     (0x0001) /* Generic End Point */
#define RIO_PORT_MBH_H_EF_BID_EP_ER  (0x0002) /* EP with SW assisted error 
                                              recovery */
#define RIO_PORT_MBH_H_EF_BID_EPF    (0x0003) /* EP free device */

/* Serial Extended Feature's Block IDs */
#define SRIO_PORT_MBH_H_EF_BID_EP    (0x0004) /* Generic Serial EP */
#define SRIO_PORT_MBH_H_EF_BID_EP_ER (0x0005) /* Serial EP with SW assisted 
                                              error recovery */
#define SRIO_PORT_MBH_H_EF_BID_EPF   (0x0006) /* Serial EP free device */

/******************************************************************************
 * Extended Feature's register offsets. 
 * All offsets are defined from the begining of Extended features block.
 * Use RIO_EXT_FE macro to offset different extended feature register blocks.
 */
#define RIO_EF_PORT_MBH_H_CSR      (0x00)  /* Port Maintenance Block Header */                                               
#define RIO_EF_PORT_MBH_L_CSR      (0x04)  /* Port MBH Lower (reserved) */
#define RIO_EF_PORT_LT_CTL_CSR     (0x20)  /* Port Link Time-out Control */
#define RIO_EF_PORT_RT_CTL_CSR     (0x24)  /* Port Response Time-out Control */
#define RIO_EF_PORT_GEN_CTL_CSR    (0x3c)  /* Port General Control CSR */

/* Port x Link Maintenance Request CSR (only for end-point devices with 
 * software assisted error recovery option) */
#define RIO_EF_PORT_LM_REQ_CSR(port)       (0x40 + (port) * 0x20) 

/* Port x Link Maintenance Response CSR (only for end-point devices with 
 * software assisted error recovery option) */
#define RIO_EF_PORT_LM_RES_CSR(port)       (0x44 + (port) * 0x20) 

/* Port x Local ackID Status CSR (only for end-point devices with software 
 * assisted error recovery option) */
#define RIO_EF_PORT_LOCAL_ACKID_SCSR(port) (0x48 + (port) * 0x20) 

/* Port Error and Status CSR */
#define RIO_EF_PORT_ERR_STAT_CSR(port)     (0x58 + (port) * 0x20) 

/* Port Control CSR */
#define RIO_EF_PORT_CTL_CSR(port)          (0x5C + (port) * 0x20) 

/* Macro for ofsetting the Extended feature registers
 * base - Extended feature block pointer
 * offset - register offset from the begining of the block */
#define RIO_EXT_FE(base, offset)           ((base) + offset)  



/****************************************************************************** 
 *
 * RapidIO Capability registers bitfield masks
 *
 *****************************************************************************/ 

/* Device ID CAR */
#define RIO_DEV_ID_CAR_DID              (0xFFFF0000) 
#define RIO_DEV_ID_CAR_DVID             (0x0000FFFF) /* Device Vendor ID */

/* Assembly ID CAR */
#define RIO_ASSEMBLY_ID_CAR_ASSID       (0xFFFF0000) 
#define RIO_ASSEMBLY_ID_CAR_ASSVID      (0x0000FFFF) /* Assembly Vendor ID */

/* Assembly Information CAR */
#define RIO_ASSEMBLY_INFO_CAR_AREV      (0xFFFF0000) /* Assembly Rev. Level */
#define RIO_ASSEMBLY_INFO_CAR_EF_PTR    (0x0000FFFF) /* Extended Features 
                                                     Pointer */

/* PE Features CAR */
#define RIO_PE_FEATURES_CAR_BRIDGE      (0x80000000) 
#define RIO_PE_FEATURES_CAR_MEM         (0x40000000) 
#define RIO_PE_FEATURES_CAR_PROC        (0x20000000) 
#define RIO_PE_FEATURES_CAR_SWITCH      (0x10000000) 
#define RIO_PE_FEATURES_CAR_MBOX0       (0x00800000) 
#define RIO_PE_FEATURES_CAR_MBOX1       (0x00400000) 
#define RIO_PE_FEATURES_CAR_MBOX2       (0x00200000) 
#define RIO_PE_FEATURES_CAR_MBOX3       (0x00100000) 
#define RIO_PE_FEATURES_CAR_DOORBELL    (0x00080000) 
#define RIO_PE_FEATURES_CAR_CT_LS       (0x00000010) /* Common transport large 
                                                     systems support */
#define RIO_PE_FEATURES_EXT_F           (0x00000008) /* Extended Features */
#define RIO_PE_FEATURES_EXT_AS          (0x00000007) /* Extended Addressing 
                                                     Support */
                                                 
#define RIO_PE_FEATURES_EXT_AS_34       (0x00000001) /* PE supports 34-bit 
                                                     addressess */
#define RIO_PE_FEATURES_EXT_AS_34_50    (0x00000003) /* PE supports 34 and 
                                                     50-bit addressess */
#define RIO_PE_FEATURES_EXT_AS_34_66    (0x00000005) /* PE supports 34 and 
                                                     66-bit addressess */
#define RIO_PE_FEATURES_EXT_AS_34_50_66 (0x00000007) /* PE supports 34,50 and 
                                                     66-bit addressess */

/* Switch Port Information CAR  */
#define RIO_SW_PORT_INFO_CAR_PORT_TOTAL (0x0000ff00) /* Total number of RIO 
                                                     ports in the PE */
#define RIO_SW_PORT_INFO_CAR_PORT_NUM   (0x000000ff) /* Port number, from which 
                                                     this register was read */

/* Source and Destination Operations CAR */
#define RIO_OP_CAR_READ                 (0x00008000) 
#define RIO_OP_CAR_WRITE                (0x00004000) 
#define RIO_OP_CAR_SWRITE               (0x00002000) /* Streaming write */
#define RIO_OP_CAR_NWRITE_R             (0x00001000) /* Write with response */
#define RIO_OP_CAR_DATA_MSG             (0x00000800) /* Data message */
#define RIO_OP_CAR_DOORBELL             (0x00000400) 
#define RIO_OP_CAR_ATOMIC_CS            (0x00000200) /* Atomic Compare and Swap */
#define RIO_OP_CAR_ATOMIC_TS            (0x00000100) /* Atomic Test and Swap */
#define RIO_OP_CAR_ATOMIC_I             (0x00000080) /* Atomic Increment */
#define RIO_OP_CAR_ATOMIC_D             (0x00000040) /* Atomic Decrement */
#define RIO_OP_CAR_ATOMIC_S             (0x00000020) /* Atomic Set */
#define RIO_OP_CAR_ATOMIC_C             (0x00000010) /* Atomic Clear */
#define RIO_OP_CAR_ATOMIC_SW            (0x00000008) /* Atomic Swap */
#define RIO_OP_CAR_PORT_W               (0x00000004) /* Port Write */


/****************************************************************************** 
 *
 * RapidIO Command and Status registers bitfield masks
 *
 *****************************************************************************/

/* Mailbox CSR */
#define RIO_MAILBOX_CSR_AVAIL(mBoxNum)  (0x80000000 >> 8*(mBoxNum)) 
#define RIO_MAILBOX_CSR_FULL(mBoxNum)   (0x40000000 >> 8*(mBoxNum)) 
#define RIO_MAILBOX_CSR_EMPTY(mBoxNum)  (0x20000000 >> 8*(mBoxNum)) 
#define RIO_MAILBOX_CSR_BUSY(mBoxNum)   (0x10000000 >> 8*(mBoxNum)) 
#define RIO_MAILBOX_CSR_FAIL(mBoxNum)   (0x08000000 >> 8*(mBoxNum)) 
#define RIO_MAILBOX_CSR_ERR(mBoxNum)    (0x04000000 >> 8*(mBoxNum)) 

/* Doorbell CSR */
#define RIO_DOORBELL_CSR_AVAIL          (0x80000000) 
#define RIO_DOORBELL_CSR_FULL           (0x40000000) 
#define RIO_DOORBELL_CSR_EMPTY          (0x20000000) 
#define RIO_DOORBELL_CSR_BUSY           (0x10000000) 
#define RIO_DOORBELL_CSR_FAILED         (0x08000000) 
#define RIO_DOORBELL_CSR_ERROR          (0x04000000) 

/* Write Port CSR */
#define RIO_WRITE_PORT_CSR_AVAIL        (0x00000080) 
#define RIO_WRITE_PORT_CSR_FULL         (0x00000040) 
#define RIO_WRITE_PORT_CSR_EMPTY        (0x00000020) 
#define RIO_WRITE_PORT_CSR_BUSY         (0x00000010) 
#define RIO_WRITE_PORT_CSR_FAILED       (0x00000008) 
#define RIO_WRITE_PORT_CSR_ERROR        (0x00000004) 

/* PE Logical Layer Control CSR */
#define RIO_PE_LL_CTL_EXT_ADD_CTL       (0x00000007) /* Extended Addressing 
                                                     Control */
#define RIO_PE_LL_CTL_EXT_ADD_66        (0x00000004) /* Supports 66-bit */
#define RIO_PE_LL_CTL_EXT_ADD_50        (0x00000002) /* Supports 50-bit */
#define RIO_PE_LL_CTL_EXT_ADD_34        (0x00000001) /* Supports 34-bit */

/* Base Device ID CSR */
#define RIO_BASE_DEV_ID_CSR_DID         (0x00FF0000) /* Base Device ID */
#define RIO_BASE_DEV_ID_CSR_LDID        (0x0000FFFF) /* Large Base Device ID */

/* Host Base Device ID CSR */
#define RIO_HOST_BASE_DEV_ID_CSR_DID    (0x0000FFFF) /* Host Base Device ID */


/****************************************************************************** 
 *
 * RapidIO Extended registers bitfield masks
 *
 *****************************************************************************/

/* Port Maintenance Block Header CSR */
#define RIO_PORT_MBH_H_EF_PTR           (0xFFFF0000) /* Next block in the  
                                                     data structure */
#define RIO_PORT_MBH_H_EF_ID            (0x0000FFFF) /* Extended feature ID */

/* Port Link Time-out Control CSR */
#define RIO_PORT_LT_CTL_TVAL            (0xFFFFFF00) /* Time-out value */

/* Port Response Time-out Control CSR (only for end-points) */
#define RIO_PORT_RT_CTL_TVAL            (0xFFFFFF00) /* Time-out value */

/* Port General Control CSR */
#define RIO_PORT_GEN_CTL_CSR_HOST       (0x80000000) /* Host Device */
#define RIO_PORT_GEN_CTL_CSR_MSTR_EN    (0x40000000) /* Master Enable */
#define RIO_PORT_GEN_CTL_CSR_DISCOV     (0x20000000) /* Discovered */

/* Port Link Maintenance Request CSR (only for end-point devices with 
 * software assisted error recovery option)  */
#define RIO_PORT_LM_REQ_CSR_CMD         (0x00000007) /* Command to send */
#define RIO_PORT_LM_REQ_CSR_CMD_ST      (0x00000000) /* Send training */
#define RIO_PORT_LM_REQ_CSR_CMD_RS      (0x00000003) /* Reset */
#define RIO_PORT_LM_REQ_CSR_CMD_IS      (0x00000004) /* Input status */

/* Port Link Maintenance Response CSR (only for end-point devices with 
 * software assisted error recovery option)  */
#define RIO_PORT_LM_RES_CSR_VALID        (0x80000000) /* Validity bit */
#define RIO_PORT_LM_RES_CSR_ACKID_STATUS (0x00000070) /* ackID Status */
#define SRIO_PORT_LM_RES_CSR_ACKID_STATUS (0x00003e00) /* Serial ackID Status */
#define RIO_PORT_LM_RES_CSR_LINK_STATUS  (0x0000000F) /* Link Status */
#define SRIO_PORT_LM_RES_CSR_LINK_STATUS (0x0000001F) /* Serial Link Status */
#define RIO_PORT_LM_RES_CSR_LS_UNIN      (0x00000000) /* Uninitialized */
#define RIO_PORT_LM_RES_CSR_LS_IN        (0x00000001) /* Initializing */
#define RIO_PORT_LM_RES_CSR_LS_ERR       (0x00000002) 
#define RIO_PORT_LM_RES_CSR_LS_STOP      (0x00000003) /* Stopped */
#define RIO_PORT_LM_RES_CSR_LS_RTRY_STOP (0x00000004) /* Retry-Stopped */
#define RIO_PORT_LM_RES_CSR_LS_ERR_STOP  (0x00000005) /* Error-Stopped */
#define RIO_PORT_LM_RES_CSR_LS_OK0       (0x00000008) /* OK, expect ackID0 */
#define RIO_PORT_LM_RES_CSR_LS_OK1       (0x00000009) /* OK, expect ackID1 */
#define RIO_PORT_LM_RES_CSR_LS_OK2       (0x0000000a) /* OK, expect ackID2 */
#define RIO_PORT_LM_RES_CSR_LS_OK3       (0x0000000b) /* OK, expect ackID3 */
#define RIO_PORT_LM_RES_CSR_LS_OK4       (0x0000000c) /* OK, expect ackID4 */
#define RIO_PORT_LM_RES_CSR_LS_OK5       (0x0000000d) /* OK, expect ackID5 */
#define RIO_PORT_LM_RES_CSR_LS_OK6       (0x0000000e) /* OK, expect ackID6 */
#define RIO_PORT_LM_RES_CSR_LS_OK7       (0x0000000f) /* OK, expect ackID7 */

/* Port Local ackID Status CSR (only for end-point devices with software 
 * assisted error recovery option) */
#define RIO_PORT_LOCAL_ACKID_SCSR_INB   (0x07000000) /* Inbound ackID */  
#define SRIO_PORT_LOCAL_ACKID_SCSR_INB  (0x1f000000) /* Serial Inbound ackID */  
#define RIO_PORT_LOCAL_ACKID_SCSR_OUTST (0x0000FF00) /* Outstanding ackID */  
#define SRIO_PORT_LOCAL_ACKID_SCSR_OUTST (0x00001f00) /* Serial Outstanding 
                                                      ackID */  
#define RIO_PORT_LOCAL_ACKID_SCSR_OUTB  (0x00000007) /* Outbound ackID */  
#define SRIO_PORT_LOCAL_ACKID_SCSR_OUTB (0x0000001f) /* Serial Outbound ackID */  

/* Port Error and Status CSR */
#define RIO_PORT_ERR_STAT_OUT_BLOCK_ENC (0x00100000) /* Output Blocked
                                                     encountered */
#define RIO_PORT_ERR_STAT_OUT_BLOCKED   (0x00080000) /* Output Blocked */
#define RIO_PORT_ERR_STAT_OUT_R_STOP    (0x00040000) /* Output Retry-stopped */
#define RIO_PORT_ERR_STAT_OUT_ERR_ENC   (0x00020000) /* Output Error
                                                     encountered */
#define RIO_PORT_ERR_STAT_OUT_ERR_STOP  (0x00010000) /* Output Error-stopped */
#define RIO_PORT_ERR_STAT_IN_R_STOP     (0x00000400) /* Input Retry-stopped */
#define RIO_PORT_ERR_STAT_IN_ERR_ENC    (0x00000200) /* Input Error
                                                     encountered */
#define RIO_PORT_ERR_STAT_IN_ERR_STOP   (0x00000100) /* Input Error-stopped */
#define RIO_PORT_ERR_STAT_PORT_W_PEND   (0x00000010) /* Port Write Pending */
#define RIO_PORT_ERR_STAT_PORT_PRES     (0x00000008) /* Port Present */
#define RIO_PORT_ERR_STAT_PORT_ERR      (0x00000004) /* Port Error */
#define RIO_PORT_ERR_STAT_PORT_OK       (0x00000002) /* Port OK */
#define RIO_PORT_ERR_STAT_PORT_UNIT     (0x00000001) /* Port Uninitialized */

/* Port Control CSR */
#define RIO_PORT_CTL_CSR_OUT_WIDTH      (0x80000000) /* Output Port width */
#define RIO_PORT_CTL_CSR_OUT_EN         (0x40000000) /* Output Port Transmit 
                                                     Enable */
#define RIO_PORT_CTL_CSR_OUT_DDIS       (0x20000000) /* Output Port Driver 
                                                     Disable */
#define RIO_PORT_CTL_CSR_IN_WIDTH       (0x08000000) /* Input Port width */
#define RIO_PORT_CTL_CSR_IN_EN          (0x04000000) /* Input Port Receive 
                                                     Enable */
#define RIO_PORT_CTL_CSR_IN_RDIS        (0x02000000) /* Input Port Receiver 
                                                     Disable */
#define RIO_PORT_CTL_CSR_ERR_CHK_DIS    (0x00800000) /* Errors Checking 
                                                     Disable */
#define RIO_PORT_CTL_CSR_TOD            (0x00400000) /* TOD Participant */

#define SRIO_PORT_CTL_CSR_PORT_WIDTH    (0xc0000000) /* Port width */
#define SRIO_PORT_CTL_CSR_PORT_WIDTH_IN (0x38000000) /* Initialized Port        
                                                     width */
#define SRIO_PORT_CTL_CSR_PORT_WIDTH_OR (0x07000000) /* Port width override */   
#define SRIO_PORT_CTL_CSR_PORT_DIS      (0x00800000) /* Port disable */
#define SRIO_PORT_CTL_CSR_OUT_PORT_EN   (0x00400000) /* Output Port enable */
#define SRIO_PORT_CTL_CSR_IN_PORT_EN    (0x00200000) /* Input Port enable */
#define SRIO_PORT_CTL_CSR_ERR_CHK_DIS   (0x00100000) /* Error Checking 
                                                     Disable */
#define SRIO_PORT_CTL_CSR_MCE_P         (0x00080000) /* Multi-cast event 
                                                     participant */
#define SRIO_PORT_CTL_CSR_PORT_TYPE     (0x00000001) /* Port type */

#define TSI_568_SP0_CTL					 (0x15C)

#endif  /* _RIO_H_ */


  //Ftype definition
#define   FT_2   0x2
#define   FT_5   0x5
#define   FT_6   0x6
#define   FT_8   0x8
#define   FT_10  0xA
#define   FT_11  0XB
#define   FT_13  0XD

//priority fields
#define LOWEST_PRIO 	0x0
#define MED_PRIO		0x1
#define HIGH_PRIO   	0x2
#define HIGHEST_PRIO 	0x3

  //Ttype definition
#define   TT_NREAD  		0x4
#define   TT_ATOMIC_INC     0xC
#define   TT_ATOMIC_DEC     0xD
#define   TT_ATOMIC_SET     0xE
#define   TT_ATOMIC_CLR     0xF
#define   TT_NWRITE         0x4
#define   TT_NWRITE_R       0x5
#define   TT_ATOMIC_TS      0xC
#define   TT_M_READ_REQ     0x0
#define   TT_M_WRITE_REQ    0x1
#define   TT_M_READ_RESP    0x2
#define   TT_M_WRITE_RESP   0x3
#define   TT_PORT_WRITE_REQ 0x4
#define   TT_W_DATA         0x8

