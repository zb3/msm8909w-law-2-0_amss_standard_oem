/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*

                Diagnostics Packet Processing Common Routines

General Description
  Core diagnostic packet processing routines that are common to all targets.

Copyright (c) 2000-2013, 2015 by QUALCOMM Technologies, Incorporated.  All Rights Reserved.
*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/*===========================================================================

                           Edit History

$Header: //components/rel/core.mpss/3.5.c12.3/services/diag/DCM/rtos/src/diagdiag.c#1 $

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
06/18/15   sa      Added support for time sync feature.
11/27/13   ph      Updated MSG 1.0 API references to MSG.2.0.
12/20/13   rs      Ported LLVM warning fix.
09/02/13   sa      Updated diag f3 listener tests to handle Qshrink3 f3s
04/03/13   sr      Replace memcpy() and memmove() with memscpy() and memsmove() 
12/13/12   rs      Added timeout mechanism to unblock diag in diagbuf_flush.
12/06/12   rs      Removed Obsolete command DIAG_RPC_F (100). 
10/12/12   ph      Removed the references of peek and poke code.
07/24/12   sa      Support for listener call backs for MSG_SPRINTF_* F3's
07/13/12   sa      Added testcode for extended Events/Logs new remove APIs
06/19/12   rs      Added testcode for Extended F3/Events/Logs Listeners
07/25/12   rs      Adding missing code due to merge error
06/19/12   rs      Added testcode for Extended F3/Events/Logs Listeners
05/16/12   rh      Support for F3 listeners
05/05/11   is      Remove support for PLT registrations
02/25/11   hm      Removed deprecated API hw_valid_addr 
09/28/10   sg      Moved diag_time_get to diag_cfg.h
09/17/10   is      Migrate from deprecated clk driver APIs
07/15/10   sg      Moving  diagdiag_memop_tbl_mutex to diagdiag_common.c 
07/10/10   vs      Added support for diagpeek/poke registration API.
06/22/10   is      Changed external flag FEATURE_VOC_TASK into internal flag
                   DIAG_VOC_TASK.
06/07/10   is      Mainlined T_MSM3.
06/03/10   sg      Added FEATURE_VOC_TASK back 
05/10/10   JV      Fix for compile error when FEATURE_DIAG_DISALLOW_MEM_OPS
                   is defined.
04/29/10   is      Removed functionality for ERR_HAS_NV_LOG_PACKET not defined
04/20/10   is      Remove support for DIAG_GET_PROPERTY_F, DIAG_PUT_PROPERTY_F,
                   DIAG_GET_PERM_PROPERTY_F, and DIAG_PUT_PERM_PROPERTY_F.
03/11/10   sg      Cleaning up FEATURE_VOC_TASK feature
12/28/09   ps      Fixed Klocwork errors & compiler warnings.
10/29/09   sg      Split file into diagdiag_common and diagdiag.c and moved common
                   functionality to diagdiag_common.c

===========================================================================*/

#include "core_variation.h"
#if defined __cplusplus
  extern "C" {
#endif

#include "comdef.h"

#include "feature.h"

#include "diagcmd.h"
#include "diag_v.h"
#include "diagi_v.h"
#include "diagdiag_v.h"
#include "diagbuf.h" /* For diagbuf_flush */
#include "diagtarget.h"

//#include "hw.h"
#include "assert.h"
#include "msg.h"
#include "qw.h"

#include "osal.h"
#include "diagpkt.h"
#include "diag_cfg.h"
#include "stringl.h"

/* Time Get Function Pointer from diag.c */
extern uint8 (*diag_time_get)(qword time);

/*===========================================================================
          Stubs for diagdiag.h
These APIs are obsolete and stubbed to return FALSE everytime.

===========================================================================*/

boolean diag_unregister_memory_address_cb (uint32 start, uint32 end,  
                                       const diagpkt_user_table_entry_type * tbl)
{
    return FALSE;
      }
        
boolean diag_register_memory_address_cb (uint32 start, uint32 end,  
                                       const diagpkt_user_table_entry_type * tbl,int count)
    {
    return FALSE;
  }

/*===========================================================================

FUNCTION DIAGDIAG_VER

DESCRIPTION
  Return the diag version

===========================================================================*/
PACK(void *) diagdiag_ver (
  PACK(void *) req_pkt,
  uint16 pkt_len
)
{
  DIAG_DIAG_VER_F_rsp_type *rsp;
  const int rsp_len = sizeof (DIAG_DIAG_VER_F_rsp_type);

  (void) req_pkt; /* suppress compiler warning */
  (void) pkt_len; /* suppress compiler warning */

  rsp = (DIAG_DIAG_VER_F_rsp_type *)diagpkt_alloc(DIAG_DIAG_VER_F, rsp_len);

  /*-------------------------------------------------------------------------
    Return diag source code version
  -------------------------------------------------------------------------*/
  if (rsp)
  {
    rsp->ver = DIAG_DIAGVER;
  }
  return (rsp);

} /* diagdiag_diag_ver */



/*===========================================================================

FUNCTION DIAGDIAG_FEATURE_QUERY

DESCRIPTION
  This procedure processes a request to query for features in the current
  build.  It returns a variable length bit mask where each bit corresponds to
  a particular feature defined in diagpkt.h in feature_query_enum_type.

============================================================================*/
PACK(void *) diagdiag_feature_query (
  PACK(void *) req_pkt,
  uint16 pkt_len
)
{

  DIAG_FEATURE_QUERY_F_rsp_type *rsp;
  const int rsp_len = sizeof(DIAG_FEATURE_QUERY_F_rsp_type);

  (void) req_pkt; /* suppress compiler warning */
  (void) pkt_len; /* suppress compiler warning */

  rsp =(DIAG_FEATURE_QUERY_F_rsp_type *)diagpkt_alloc(DIAG_FEATURE_QUERY_F, rsp_len);
  if (rsp)
  {
  	rsp->feature_mask_size = FEATURE_MASK_LENGTH;

  	/* Copy the current mask into the diag pkt */
  	memscpy( (void *) rsp->feature_mask,FEATURE_MASK_LENGTH,
          diag_feature_mask,
          FEATURE_MASK_LENGTH
        );
  }
  /* return the size of the variable length packet.  command_code and
  ** feature_mask_size is constant.  FEATURE_MASK_LENGTH changes
  ** as more features are added
  */
  return (rsp);


} /* diagdiag_feature_query */



/*===========================================================================

FUNCTION DIAGDIAG_PASSWORD

DESCRIPTION
  Processes an entry of the Security Password.
  This function compares the password in the phone to what was sent in
  the packet.  If they are the same, the successful Security unlock is
  noted (setting the diag_get_security_state() mask to UNLOCKED), and a value of TRUE
  is returned to the external device.
  If they are NOT the same, Security remains locked, a value of FALSE is
  returned to the external device, and the phone is powered off,
  to deter hackers.

SIDE EFFECTS
  May cause the phone to power off!  (After returning from this routine).

===========================================================================*/
PACK(void *) diagdiag_password (
  PACK(void *) req_pkt,
  uint16 pkt_len
)
{
  DIAG_PASSWORD_F_req_type *req = (DIAG_PASSWORD_F_req_type *) req_pkt;
  DIAG_PASSWORD_F_rsp_type *rsp;
  const int rsp_len = sizeof(DIAG_PASSWORD_F_rsp_type);
  (void) pkt_len; /* suppress compiler warning */

  rsp = (DIAG_PASSWORD_F_rsp_type *) diagpkt_alloc (DIAG_PASSWORD_F, rsp_len);

/*------------------------------------------------------------------------*/

  MSG(MSG_SSID_DIAG, MSG_LEGACY_LOW,"Security Password given");

  /* If the security is already unlocked, then it doesn't matter what
  ** you give as the security code.  Otherwise we need to compare
  ** the given security code with the one in the phone.
  */
  if (rsp)
  {
	  if ((diag_get_security_state() == DIAG_SEC_UNLOCKED) ||
	      (diag_check_password((void *) req->password))) {

	    rsp->password_ok = TRUE;
	    (void) diag_set_security_state(DIAG_SEC_UNLOCKED);
	  }
	  /* Otherwise, the code was incorrect.  Diag will now powerdown the phone.
	  */
	  else {
	    rsp->password_ok = FALSE;
	    (void) diag_set_security_state(DIAG_SEC_LOCKED);

	    diagpkt_commit(rsp);
	    rsp = NULL;

	    /* Flush DIAG's TX buffer */
	    diagbuf_flush_timeout(DIAG_SIO_TIMEOUT_TIMER_LEN);

	    /* Power down the phone.  This function does not return.
	    */
	    diag_powerdown();
	  }
  	}
  return (rsp);

} /* diagdiag_password */



/*===========================================================================
FUNCTION DIAGDIAG_TS

DESCRIPTION
  Return an IS-95/IS-2000 timestamp

DEPENDENCIES
  None.

RETURN VALUE
  Pointer to response packet.

SIDE EFFECTS
  None.
===========================================================================*/
PACK(void *) diagdiag_ts (
  PACK(void *) req_pkt,
  uint16 pkt_len
)
{
  qword ts_time;                 /* time stamp */
  DIAG_TS_F_rsp_type *rsp;
  const int rsp_len = sizeof( DIAG_TS_F_rsp_type );

  (void) req_pkt; /* suppress compiler warning */
  (void) pkt_len; /* suppress compiler warning */

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
  /*------------------------------------------------------------------------
    Get the time, stuff the packet.
  -------------------------------------------------------------------------*/

  (void)diag_time_get (ts_time);


  rsp = (DIAG_TS_F_rsp_type *) diagpkt_alloc (DIAG_TS_F, rsp_len);

  qw_equ_misaligned (rsp->ts, ts_time);

  return (rsp);

} /* diagdiag_ts */

#if 1 //For now, use a fake GUID. -LD
/* Default GUID (since it was unspecified) */
static const diag_guid_type diag_guid =
{
   0xDEADD00DU,
   0xDEADD00DU,
   0xDEADD00DU,
   0x06101975
};
#endif


LOCAL diag_prop_struct_type diag_prop_table[DIAG_MAX_NUM_PROPS];

/*===========================================================================

FUNCTION DIAG_LOOKUP_PROP

DESCRIPTION
  Looks up the address of a callback function given its name.

DEPENDENCIES
  None.

RETURN VALUE
  The address of the function or NULL if the function is not found in the
  function table.

SIDE EFFECTS
  None.

===========================================================================*/
void *diag_lookup_prop
(
  char *prop_name
)
{
  int i = 0;

  if ( prop_name == NULL )
  {
    return (void *) NULL;
  }

  while ( diag_prop_table[ i ].name != NULL )
  {
    if ( strncmp(
                 diag_prop_table[ i ].name,
                 prop_name,
                 DIAG_MAX_PROPERTY_NAME_SIZE
         ) == 0 )
    {
      return diag_prop_table[ i ].address;
    }
    i++;
    if ( i >= DIAG_MAX_NUM_PROPS )
    {
      /*
      ** Will get here only if the properties table has been corrupted.
      */
      break;
    }
  }
  return (void *) NULL;
} /* diag_lookup_prop */



/*===========================================================================

FUNCTION DIAG_GUID_IS_VALID

DESCRIPTION
  This static function returns true or false depending on whether the
  input guid (globally unique identifier) matches that of the current build.

DEPENDENCIES
  None.

RETURN VALUE
  TRUE if the input guid is valid, FALSE otherwise.

SIDE EFFECTS
  None.

===========================================================================*/
LOCAL boolean diag_guid_is_valid
(
  diag_guid_type guid
)
{
  if ( ( guid[ 0 ] == diag_guid[ 0 ] ) &&
       ( guid[ 1 ] == diag_guid[ 1 ] ) &&
       ( guid[ 2 ] == diag_guid[ 2 ] ) &&
       ( guid[ 3 ] == diag_guid[ 3 ] ) )
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
} /* diag_guid_is_valid */


/*===========================================================================

FUNCTION DIAGDIAG_GET_GUID

DESCRIPTION
  This procedure processes a get_guid request. The GUID (globally unique
  identifier) for this build is retrieved and returned in the response
  packet. The GUID is stored during the build process.

===========================================================================*/
PACK(void *) diagdiag_get_guid
(
  PACK(void *) req_pkt, /* pointer to request packet  */
  uint16 pkt_len            /* length of request packet  */
)
{
  DIAG_GET_GUID_F_rsp_type *rsp;
  const unsigned int rsp_len = sizeof (DIAG_GET_GUID_F_rsp_type);

  (void) req_pkt; /* suppress compiler warning */
  (void) pkt_len; /* suppress compiler warning */

  /*--------------------------------------------
    Allocate buffer space for response packet.
  --------------------------------------------*/
  rsp = (DIAG_GET_GUID_F_rsp_type *) diagpkt_alloc (DIAG_GET_GUID_F, rsp_len);

  memscpy((void *) &rsp->guid[0],sizeof(diag_guid_type),
         (const void *) &diag_guid[0],
         sizeof(diag_guid_type));

  return rsp;

} /* diagdiag_get_guid */



/*===========================================================================
FUNCTION DIAGDIAG_EVENT_LISTENER

DESCRIPTION The event has been added to listen
============================================================================*/
void
diagdiag_event_listener (uint32 seq_num, const diag_event_type * event, void * param)
{
  MSG_3 (MSG_SSID_DIAG, MSG_LEGACY_HIGH,
            "Event listener 0x%04X param:0x%08X seq:%d", 
            event->event_id, (uint32) param, seq_num);
}

/*===========================================================================
FUNCTION DIAGDIAG_EVENT_LISTENER_EXT

DESCRIPTION The event has been added to listen
============================================================================*/
void
diagdiag_event_listener_ext (const diag_event_type * event, void * param)
{
	MSG_2 (MSG_SSID_DIAG, MSG_LEGACY_HIGH,
			  "Extended Event listener 0x%04X param:0x%08X",
			  event->event_id, (uint32) param);
}

/*===========================================================================
FUNCTION DIAGDIAG_LOG_LISTENER

DESCRIPTION The log has been added to listen
============================================================================*/
void
diagdiag_log_listener (uint32 seq_num, const byte * log, unsigned int length,
                       void * param)
{
  MSG_3 (MSG_SSID_DIAG, MSG_LEGACY_HIGH,
         "Log listener 0x%04X param:0x%08X seq:%d", 
         log_get_code ((void *) log), (uint32) param, seq_num);
}

/*===========================================================================
FUNCTION DIAGDIAG_LOG_LISTENER_EXT

DESCRIPTION The log has been added to listen
============================================================================*/

void
diagdiag_log_listener_ext (const byte * log, unsigned int length,
                       void * param)
{
	MSG_2 (MSG_SSID_DIAG, MSG_LEGACY_HIGH,
		   "Extended Log listener 0x%04X param:0x%08X",
		   log_get_code ((void *) log), (uint32) param);
}


/*===========================================================================
FUNCTION DIAGDIAG_F3_LISTENER

DESCRIPTION The F3 has been added to listen
============================================================================*/
void
diagdiag_f3_listener (uint32 seq_num, const diag_msg_type * msg, void * param)
{
  msg_v3_store_type * msg_store_qsr = NULL;
  msg_ext_store_type * msg_store_ext = NULL;
  msg_ext_type *ext_sprintf_msg = NULL;
    
  if( msg )
  {
    if( msg->cmd_code == DIAG_EXT_MSG_TERSE_F )
    {
      msg_store_ext = msg->msg_store.ext_msg;

      if( msg_store_ext && msg_store_ext->const_data_ptr )
      {
        MSG_5 (MSG_SSID_LEGACY, MSG_LEGACY_HIGH,
               "F3 listener cmd_code:%d ssid:%d ss_mask:%d param:0x%08X seq:%d", 
               msg->cmd_code, msg_store_ext->const_data_ptr->desc.ss_id, 
               msg_store_ext->const_data_ptr->desc.ss_mask, (uint32) param, seq_num);
      }
    }
    else if( msg->cmd_code == DIAG_QSR_EXT_MSG_TERSE_F )
    {
      msg_store_qsr = msg->msg_store.qsr_v3_msg;
	  
      if( msg_store_qsr && msg_store_qsr->qsr_const_data_ptr.v3_index )
      {

         if ( msg_store_qsr->qsr_flag & QSR_BITFLAG_IS_V3 )
				{
					uint16 msg_ssid;
					uint32 msg_mask;
					if(msg_get_qsr_table_entry(msg_store_qsr->qsr_const_data_ptr.v3_index->ssid_index,
																		 &msg_ssid, &msg_mask))
					{
						MSG_5 (MSG_SSID_LEGACY, MSG_LEGACY_HIGH,
									 "F3 listener cmd_code:%d ssid:%d ss_mask:%d param:0x%08X seq:%d", 
									 msg->cmd_code, msg_ssid, msg_mask, (uint32) param, seq_num);
					}
					else
					{
						MSG_2 (MSG_SSID_LEGACY, MSG_LEGACY_HIGH,
									 "F3 Listener unidentified QSR message cmd_code:%d ssid_index:%d",
									 msg->cmd_code, msg_store_qsr->qsr_const_data_ptr.v3_index->ssid_index);
					}
         }
         else if ( msg_store_qsr->qsr_flag & QSR_BITFLAG_IS_HASH )
         {
          MSG_5 (MSG_SSID_LEGACY, MSG_LEGACY_HIGH,
                 "F3 listener cmd_code:%d ssid:%d ss_mask:%d param:0x%08X seq:%d", 
                 msg->cmd_code, msg_store_qsr->qsr_const_data_ptr.msg_desc->desc.ss_id, 
                 msg_store_qsr->qsr_const_data_ptr.msg_desc->desc.ss_mask,
                         (uint32) param, seq_num);
				}
      }
    }
    else if(msg->cmd_code == DIAG_EXT_MSG_F)
    {
      ext_sprintf_msg = msg->msg_store.ext_sprintf_msg;
      if(ext_sprintf_msg && ext_sprintf_msg->args)
      {
        MSG_4 (MSG_SSID_LEGACY, MSG_LEGACY_HIGH,
               "F3 listener cmd_code:%d ssid:%d ss_mask:%d param:0x%08X", 
               msg->cmd_code,ext_sprintf_msg->desc.ss_id, 
               ext_sprintf_msg->desc.ss_mask, (uint32) param);
      }		
    }
  }
} /* diagdiag_f3_listener */


/*===========================================================================
FUNCTION DIAGDIAG_F3_LISTENER_EXT

DESCRIPTION The F3 has been added to listen
============================================================================*/
void
diagdiag_f3_listener_ext (const diag_msg_type * msg, void *param)
{
  msg_v3_store_type * msg_store_qsr = NULL;
  msg_ext_store_type * msg_store_ext = NULL;
  msg_ext_type *ext_sprintf_msg = NULL;
    
  if( msg )
  {
    if( msg->cmd_code == DIAG_EXT_MSG_TERSE_F )
	{
	  msg_store_ext = (msg_ext_store_type *)msg->msg_store.ext_msg;
	  
	  if( msg_store_ext && msg_store_ext->const_data_ptr )
	  {
        MSG_4 (MSG_SSID_LEGACY, MSG_LEGACY_HIGH,
               "F3 Extended listener cmd_code:%d ssid:%d ss_mask:%d param:0x%08X", 
               msg->cmd_code, msg_store_ext->const_data_ptr->desc.ss_id, 
			   msg_store_ext->const_data_ptr->desc.ss_mask, (uint32) param);
	  }
    }
   else if( msg->cmd_code == DIAG_QSR_EXT_MSG_TERSE_F )
	{
		msg_store_qsr = msg->msg_store.qsr_v3_msg;
	  
     if( msg_store_qsr && msg_store_qsr->qsr_const_data_ptr.v3_index )
	  {
        if ( msg_store_qsr->qsr_flag & QSR_BITFLAG_IS_V3 )
        {
           uint16 msg_ssid;
           uint32 msg_mask;
           if(msg_get_qsr_table_entry(msg_store_qsr->qsr_const_data_ptr.v3_index->ssid_index,
                                                   &msg_ssid, &msg_mask))
           {
	    MSG_4 (MSG_SSID_LEGACY, MSG_LEGACY_HIGH,
               "F3 Extended listener cmd_code:%d ssid:%d ss_mask:%d param:0x%08X", 
                        msg->cmd_code, msg_ssid, msg_mask, (uint32) param);
           }
           else
           {
              MSG_2 (MSG_SSID_LEGACY, MSG_LEGACY_HIGH,
                        "F3 Listener unidentified QSR message cmd_code:%d ssid_index:%d",
                        msg->cmd_code, msg_store_qsr->qsr_const_data_ptr.v3_index->ssid_index);
           }
        }
        else if ( msg_store_qsr->qsr_flag & QSR_BITFLAG_IS_HASH )
        {
         MSG_4 (MSG_SSID_LEGACY, MSG_LEGACY_HIGH,
                "F3 Extended listener cmd_code:%d ssid:%d ss_mask:%d param:0x%08X", 
                msg->cmd_code, msg_store_qsr->qsr_const_data_ptr.msg_desc->desc.ss_id, 
                msg_store_qsr->qsr_const_data_ptr.msg_desc->desc.ss_mask,
                        (uint32) param);
        }        
	  }
	}

	else if(msg->cmd_code == DIAG_EXT_MSG_F)
	{
		ext_sprintf_msg = (msg_ext_type*)msg->msg_store.ext_sprintf_msg;
		if(ext_sprintf_msg && ext_sprintf_msg->args)
		{
				    MSG_4 (MSG_SSID_LEGACY, MSG_LEGACY_HIGH,
               "F3 Extended listener cmd_code:%d ssid:%d ss_mask:%d param:0x%08X", 
               msg->cmd_code,ext_sprintf_msg->desc.ss_id, 
			   ext_sprintf_msg->desc.ss_mask, (uint32) param);
		}		
	}
  }
} 

/*===========================================================================
FUNCTION DIAGDIAG_LISTENER_PKT

DESCRIPTION   
  This procedure tests the following:
  1) Add log listener
  2) Remove log listener
  3) Add event listener
  4) Remove event listener

RETURN VALUE
  Pointer to response packet.

============================================================================*/
PACK(void *)
diagdiag_listener_pkt (PACK(void *) req_pkt, uint16 pkt_len)
{
  diag_log_event_listener_rsp_type *rsp;
  diag_log_event_listener_req_type *req = 
    (diag_log_event_listener_req_type *) req_pkt;

  diagpkt_subsys_cmd_code_type cmd_code =  0xFF;

  const int rsp_len = pkt_len;

  if( req == NULL )
  {
    return diagpkt_err_rsp( DIAG_BAD_PARM_F, req_pkt, pkt_len );
  }

  cmd_code = diagpkt_subsys_get_cmd_code (req);

  /* Allocate the same length as the request */
  rsp = (diag_log_event_listener_rsp_type *) 
    diagpkt_subsys_alloc (DIAG_SUBSYS_DIAG_SERV, cmd_code, rsp_len);

  /* Send the response acknowledging that the packet has been started */
  if (rsp != NULL)
  {
    memscpy ((void *) rsp, rsp_len, (void *) req, rsp_len);

    switch (cmd_code)
    {
      case DIAGDIAG_ADD_EVENT_LISTENER_F:
        (void) diag_add_event_listener (req->id, diagdiag_event_listener, (void *) req->param);
        break;
      case DIAGDIAG_REMOVE_EVENT_LISTENER_F:
        (void) diag_remove_event_listener (req->id, diagdiag_event_listener, (void *) req->param);
        break;
      case DIAGDIAG_ADD_LOG_LISTENER_F:
        (void) diag_add_log_listener (req->id, diagdiag_log_listener, (void *) req->param);
        break;
      case DIAGDIAG_REMOVE_LOG_LISTENER_F:
        (void) diag_remove_log_listener (req->id, diagdiag_log_listener, (void *) req->param);
        break;  
      default:
		diagpkt_free(rsp);
        return diagpkt_err_rsp( DIAG_BAD_PARM_F, req_pkt, pkt_len );
        break;
    }
  }
  
  return rsp;

} /* diagdiag_listener_pkt */

/*===========================================================================
FUNCTION DIAGDIAG_LISTENER_EXT_PKT

DESCRIPTION   
  This procedure tests the following:
  1) Add extended log listener
  2) Remove extended log listener
  3) Add extended event listener
  4) Remove extended event listener

RETURN VALUE
  Pointer to response packet.

============================================================================*/
PACK(void *)
diagdiag_listener_ext_pkt (PACK(void *) req_pkt, uint16 pkt_len)
{
  diag_log_event_ext_listener_rsp_type *rsp;
  diag_log_event_ext_listener_req_type *req = 
    (diag_log_event_ext_listener_req_type *) req_pkt;

  diagpkt_subsys_cmd_code_type cmd_code = 0xFF;

  const int rsp_len = pkt_len;

  if( req == NULL )
  {
	return diagpkt_err_rsp( DIAG_BAD_PARM_F, req_pkt, pkt_len );
  }

  cmd_code = diagpkt_subsys_get_cmd_code (req);


  /* Allocate the same length as the request */
  rsp = (diag_log_event_ext_listener_rsp_type *) 
    diagpkt_subsys_alloc (DIAG_SUBSYS_DIAG_SERV, cmd_code, rsp_len);

  /* Send the response acknowledging that the packet has been started */
  if (rsp != NULL)
  {
    memscpy ((void *) rsp, rsp_len, (void *) req, rsp_len);

    switch (cmd_code)
    {
      case DIAGDIAG_ADD_EVENT_EXT_LISTENER_F:
         rsp->success = (uint16)diag_add_event_listener_ext (req->codes,req->num_codes, diagdiag_event_listener_ext, (void *) req->param);
        break;
      case DIAGDIAG_REMOVE_EVENT_EXT_LISTENER_F:
        rsp->success = (uint16)diag_remove_event_listener_ext (diagdiag_event_listener_ext);
        break;
      case DIAGDIAG_REMOVE_EVENT_EXTP_LISTENER_F:
        rsp->success = (uint16)diag_remove_event_listener_extp(diagdiag_event_listener_ext, (void*)req->param);
        break;
      case DIAGDIAG_ADD_LOG_EXT_LISTENER_F:
        rsp->success = (uint16)diag_add_log_listener_ext (req->codes,req->num_codes, diagdiag_log_listener_ext, (void *) req->param);
        break;
      case DIAGDIAG_REMOVE_LOG_EXT_LISTENER_F:
        rsp->success = (uint16)diag_remove_log_listener_ext(diagdiag_log_listener_ext);
        break;
      case DIAGDIAG_REMOVE_LOG_EXTP_LISTENER_F:
        rsp->success = (uint16)diag_remove_log_listener_extp(diagdiag_log_listener_ext, (void*)req->param);
        break;
	  default:
		diagpkt_free(rsp);
        return diagpkt_err_rsp( DIAG_BAD_PARM_F, req_pkt, pkt_len );
        break;
    }
  }
  else
  {
      MSG(MSG_SSID_DIAG, MSG_LEGACY_ERROR, 
            "Cannot allocate memory for extended listener response packet");
  }
  
  return rsp;

} /* diagdiag_listener_ext_pkt */

/*===========================================================================
FUNCTION DIAGDIAG_F3_LISTENER_PKT

DESCRIPTION   
  This procedure tests the following:
  1) Add F3 listener
  2) Remove F3 listener

RETURN VALUE
  Pointer to response packet.

============================================================================*/
PACK(void *)
diagdiag_f3_listener_pkt (PACK(void *) req_pkt, uint16 pkt_len)
{
  diag_f3_listener_req_type *rsp = NULL;
  diag_f3_listener_req_type *req = (diag_f3_listener_req_type *) req_pkt;
  const int rsp_len = pkt_len;
  
  diagpkt_subsys_cmd_code_type cmd_code = 0xFF;

  if( req == NULL )
  {
    return diagpkt_err_rsp( DIAG_BAD_PARM_F, req_pkt, pkt_len );
  }
  
  cmd_code = diagpkt_subsys_get_cmd_code (req);

  /* Listener for Legacy F3s not allowed. */
  if( req->id == 0 )
  {
    MSG( MSG_SSID_LEGACY, MSG_LEGACY_ERROR, "diagdiag_f3_listener_pkt: Listener for Legacy F3s not allowed." );
    return diagpkt_err_rsp( DIAG_BAD_PARM_F, req_pkt, pkt_len );
  }
  
  /* Allocate the same length as the request */
  rsp = (diag_f3_listener_req_type *) 
    diagpkt_subsys_alloc (DIAG_SUBSYS_DIAG_SERV, cmd_code, rsp_len);

  /* Send the response acknowledging that the packet has been started */
  if (rsp != NULL)
  {
    memscpy ((void *) rsp, rsp_len,(void *) req, rsp_len);

    switch (cmd_code)
    {
	  case DIAGDIAG_ADD_F3_LISTENER_F:
	    (void) diag_add_f3_listener (req->id, req->mask, diagdiag_f3_listener, (void *) req->param);
	    break;
      case DIAGDIAG_REMOVE_F3_LISTENER_F:
	    (void) diag_remove_f3_listener (req->id, req->mask, diagdiag_f3_listener, (void *) req->param);
        break;	  
      default:
		diagpkt_free(rsp);
		return diagpkt_err_rsp( DIAG_BAD_PARM_F, req_pkt, pkt_len );
        break;
    }
  }
  
  return rsp;

} /* diagdiag_f3_listener_pkt */

/*===========================================================================
FUNCTION DIAGDIAG_F3_LISTENER_EXT_PKT

DESCRIPTION   
  This procedure tests the following:
  1) Add extended F3 listener
  2) Remove extended F3 listener

RETURN VALUE
  Pointer to response packet.

============================================================================*/

PACK(void *)
diagdiag_f3_listener_ext_pkt (PACK(void *) req_pkt, uint16 pkt_len)
{
  diag_f3_ext_listener_rsp_type *rsp = NULL;
  diag_f3_ext_listener_req_type *req = (diag_f3_ext_listener_req_type *) req_pkt;
  const int rsp_len = pkt_len;
  
  diagpkt_subsys_cmd_code_type cmd_code = 0xFF;

  if( req == NULL )
  {
    return diagpkt_err_rsp( DIAG_BAD_PARM_F, req_pkt, pkt_len );
  }

  cmd_code = diagpkt_subsys_get_cmd_code (req);
  
  /* Allocate the same length as the request */
  rsp = (diag_f3_ext_listener_rsp_type *) 
    diagpkt_subsys_alloc (DIAG_SUBSYS_DIAG_SERV, cmd_code, rsp_len);

  /* Send the response acknowledging that the packet has been started */
  if (rsp != NULL)
  {
    memscpy ((void *) rsp, rsp_len,(void *) req, rsp_len);

    switch (cmd_code)
    {
		case DIAGDIAG_ADD_F3_EXT_LISTENER_F:
			rsp->success = (uint16)diag_add_f3_listener_ext (req->keys, req->num_keys, diagdiag_f3_listener_ext, (void *) req->param);
	    break;
		case DIAGDIAG_REMOVE_F3_EXT_LISTENER_F:
			rsp->success = (uint16)diag_remove_f3_listener_ext (diagdiag_f3_listener_ext, (void *) req->param);
        break;
		default:
			diagpkt_free(rsp);
            return diagpkt_err_rsp( DIAG_BAD_PARM_F, req_pkt, pkt_len );
        break;
    }
  }
  else
  {
      MSG(MSG_SSID_DIAG, MSG_LEGACY_ERROR,
            "Cannot allocate memory for extended listener response packet");
  }
  
  return rsp;

} /* diagdiag_f3_listener_pkt */

static const diagpkt_user_table_entry_type diagdiag_tbl_ts[]=
{
  {DIAG_TS_F, DIAG_TS_F, diagdiag_ts},

};

static const diagpkt_user_table_entry_type diagdiag_tbl_feature[]=
{
 {DIAG_FEATURE_QUERY_F, DIAG_FEATURE_QUERY_F, diagdiag_feature_query},
};

static const diagpkt_user_table_entry_type diagdiag_tbl_misc[]=
{
  {DIAG_DIAG_VER_F, DIAG_DIAG_VER_F, diagdiag_ver},
  {DIAG_PASSWORD_F, DIAG_PASSWORD_F, diagdiag_password},
  {DIAG_GET_GUID_F, DIAG_GET_GUID_F, diagdiag_get_guid },
};

static const diagpkt_user_table_entry_type diagdiag_tbl_listener[] =
{  
  {DIAGDIAG_ADD_EVENT_LISTENER_F, DIAGDIAG_REMOVE_LOG_LISTENER_F, diagdiag_listener_pkt},
  {DIAGDIAG_ADD_EVENT_EXT_LISTENER_F, DIAGDIAG_REMOVE_LOG_EXT_LISTENER_F, diagdiag_listener_ext_pkt},
  {DIAGDIAG_ADD_F3_LISTENER_F, DIAGDIAG_REMOVE_F3_LISTENER_F, diagdiag_f3_listener_pkt},
  {DIAGDIAG_ADD_F3_EXT_LISTENER_F, DIAGDIAG_REMOVE_F3_EXT_LISTENER_F, diagdiag_f3_listener_ext_pkt},
  {DIAGDIAG_REMOVE_EVENT_EXTP_LISTENER_F, DIAGDIAG_REMOVE_LOG_EXTP_LISTENER_F, diagdiag_listener_ext_pkt},
};


void diagdiag_tbl_init()
{
	DIAGPKT_DISPATCH_TABLE_REGISTER_PROC (DIAG_MODEM_PROC, DIAGPKT_NO_SUBSYS_ID, diagdiag_tbl_feature);
	DIAGPKT_DISPATCH_TABLE_REGISTER_PROC (DIAG_MODEM_PROC, DIAGPKT_NO_SUBSYS_ID, diagdiag_tbl_ts);
	DIAGPKT_DISPATCH_TABLE_REGISTER_PROC (DIAG_MODEM_PROC, DIAGPKT_NO_SUBSYS_ID, diagdiag_tbl_misc);

#if defined(DIAG_IMAGE_APPS_PROC)
	DIAGPKT_DISPATCH_TABLE_REGISTER_PROC( DIAG_APP_PROC, DIAG_SUBSYS_DIAG_SERV, diagdiag_tbl_listener);
#else
#if defined(DIAG_IMAGE_MODEM_PROC)|| defined(DIAG_SINGLE_PROC)
	DIAGPKT_DISPATCH_TABLE_REGISTER_PROC( DIAG_MODEM_PROC, DIAG_SUBSYS_DIAG_SERV, diagdiag_tbl_listener);
#endif
#endif 
}

#if defined __cplusplus
  }
#endif
