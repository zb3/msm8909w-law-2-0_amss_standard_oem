/* DIAG TOOL VERSION: 4.35 */
/*=============================================================================
                              D I A G _ S V C . C

GENERAL DESCRIPTION
  This is an AUTO GENERATED file that dispatches RPC requests targetting the
  diag api.

  ---------------------------------------------------------------------------
  Copyright (c) 2009 Qualcomm Technologies Incorporated.
  All Rights Reserved. QUALCOMM Proprietary and Confidential.
  ---------------------------------------------------------------------------
=============================================================================*/

/*=============================================================================

                              Edit History

                             AUTO GENERATED                                  */
/* Generated by following versions of Htorpc modules:
Id: //source/qcom/qct/core/mproc/tools/rel/04.07/htorpc/htorpc.pl#7 
Id: //source/qcom/qct/core/mproc/tools/rel/04.07/htorpc/lib/Htorpc/Start.pm#2 
Id: //source/qcom/qct/core/mproc/tools/rel/04.07/htorpc/lib/Htorpc/Htoxdr.pm#1 
Id: //source/qcom/qct/core/mproc/tools/rel/04.07/htorpc/lib/Htorpc/XDR.pm#2 
Id: //source/qcom/qct/core/mproc/tools/rel/04.07/htorpc/lib/Htorpc/Output.pm#6 
Id: //source/qcom/qct/core/mproc/tools/rel/04.07/htorpc/lib/Htorpc/Parser.pm#1 
Id: //source/qcom/qct/core/mproc/tools/rel/04.07/htorpc/lib/Htorpc/Metacomments.pm#4 
Id: //source/qcom/qct/core/mproc/tools/rel/04.07/htorpc/lib/Htorpc/SymbolTable.pm#2   

diag Definition File(s):
Id: //source/qcom/qct/core/services/diag/api/inc/main/latest/diag.h#10
=============================================================================*/
/*=============================================================================
$Header: //components/rel/tz.bf/2.5.c10/trustzone_images/core/api/rapi/services/src/diag_svc.c#1 $ 
=============================================================================*/


/* Include files */
#include "oncrpc.h"
#include "diag.h"
#include "diag_rpc.h"

/* Only one copy needed per API */
//static opaque_auth DiagCred = { ONCRPC_AUTH_NONE, 0, 0 };
static opaque_auth DiagVerf = { ONCRPC_AUTH_NONE, 0, 0 };

static opaque_auth DiagcbCred = { ONCRPC_AUTH_NONE, 0, 0 };
static opaque_auth DiagcbVerf = { ONCRPC_AUTH_NONE, 0, 0 };

/*=======================================================================
             Prototypes for the API's RPC Server Functions
=======================================================================*/

static void diagprog_0x00010001 ( struct svc_req *rqstp, xdr_s_type *srv );
static void diag_null_0x00010001( xdr_s_type *svc );
static void diag_rpc_glue_code_info_remote_0x00010001( xdr_s_type *svc );
static void diag_api_versions_0x00010001( xdr_s_type *srv );

static void diag_add_event_listener_0x00010001( xdr_s_type *srv );

static void diag_remove_event_listener_0x00010001( xdr_s_type *srv );

static void diag_add_log_listener_0x00010001( xdr_s_type *srv );

static void diag_remove_log_listener_0x00010001( xdr_s_type *srv );

static void diag_cmd_req_0x00010001( xdr_s_type *srv );


/*=======================================================================
             Prototypes for the API's Callback RPC clients
=======================================================================*/

static void diag_event_listener_clnt_0x00010001(uint32 seq_num,  const diag_event_type *event,  void *param);

static void diag_log_listener_clnt_0x00010001(
  uint32 seq_num,
  const byte *log,
  unsigned int length,
  void *param
);

static void diag_cmd_rsp_clnt_0x00010001(const byte *rsp,  unsigned int length,  void *param);

/******************************************************************************/
/*=======================================================================
             API RPC Server Implementation
=======================================================================*/
static uint32 diag_api_versions_table[] = { 0x00010001 };

uint32 * diag_api_versions(uint32 *size_entries)
{
  *size_entries = sizeof( diag_api_versions_table) / sizeof(uint32);
  return diag_api_versions_table;
}

void diag_app_init( void )
{
  (void) svc_register_auto_apiversions(DIAGPROG, DIAGVERS, diagprog_0x00010001, 
                                       diag_api_versions);
} /* diag_app_init */

void diag_app_lock( boolean lock )
{
  svc_lock( DIAGPROG, DIAGVERS, lock );
} /* diag_app_lock */

static void diagprog_0x00010001 ( struct svc_req *rqstp, xdr_s_type *srv )
{
  switch ( rqstp->rq_proc ) {
    case ONCRPC_DIAG_NULL_PROC:
      diag_null_0x00010001( srv );
      break;
    case ONCRPC_DIAG_RPC_GLUE_CODE_INFO_REMOTE_PROC:
      diag_rpc_glue_code_info_remote_0x00010001( srv );
      break;
    case ONCRPC_DIAG_ADD_EVENT_LISTENER_PROC:
      diag_add_event_listener_0x00010001( srv );
      break;
    case ONCRPC_DIAG_REMOVE_EVENT_LISTENER_PROC:
      diag_remove_event_listener_0x00010001( srv );
      break;
    case ONCRPC_DIAG_ADD_LOG_LISTENER_PROC:
      diag_add_log_listener_0x00010001( srv );
      break;
    case ONCRPC_DIAG_REMOVE_LOG_LISTENER_PROC:
      diag_remove_log_listener_0x00010001( srv );
      break;
    case ONCRPC_DIAG_CMD_REQ_PROC:
      diag_cmd_req_0x00010001( srv );
      break;
    case ONCRPC_DIAG_API_VERSIONS_PROC:
      diag_api_versions_0x00010001( srv );
      break;

    default:
      // invalid RPC procedure number
      (void) XDR_MSG_DONE( srv );
      svcerr_default_err( srv, rqstp, diag_api_versions  );
      break;
  }

  oncrpcxdr_mem_free( srv );
} /* diagprog_0x00010001 */

/******************************************************************************/

static void diag_null_0x00010001( xdr_s_type *srv )
{
  if ( ! XDR_MSG_DONE( srv ) ) {
    // send svcerr_decode reply
    svcerr_decode( srv );
    return;
  }

  if ( ! xdr_reply_msg_start( srv, &DiagVerf ) ) {
    // send svcerr_systemerr reply
    svcerr_systemerr( srv );
    return;
  }

  if ( ! XDR_MSG_SEND( srv, NULL ) ) {
    XDR_MSG_SEND_ERR( srv, NULL );
  }
} /* diag_null_0x00010001 */

static void diag_rpc_glue_code_info_remote_0x00010001( xdr_s_type *srv )
{
  uint32 toolvers   = DIAG_TOOLVERS; /* 4.35 */
  uint32 proghash   = 0x00010001; /* 0x00010001 */
  uint32 cbproghash = 0x00010001; /* 0x00010001 */
  uint32 features   = DIAG_FEATURES; /* ONCRPC Server Cleanup Support */
                      

  if ( ! XDR_MSG_DONE( srv ) ) {
    // send svcerr_decode reply
    svcerr_decode( srv );
    return;
  }

  if ( ! xdr_reply_msg_start( srv, &DiagVerf ) ||
       ! XDR_SEND_UINT32( srv, &toolvers ) ||
       ! XDR_SEND_UINT32( srv, &features ) ||
       ! XDR_SEND_UINT32( srv, &proghash ) ||
       ! XDR_SEND_UINT32( srv, &cbproghash ) )
  {
    // send svcerr_systemerr reply
    svcerr_systemerr( srv );
    return;
  }

  if ( ! XDR_MSG_SEND( srv, NULL ) ) {
    XDR_MSG_SEND_ERR( srv, NULL );
  }
} /* diag_rpc_glue_code_info_remote_0x00010001 */

static void diag_add_event_listener_0x00010001( xdr_s_type *srv )
{
  boolean xdr_status = TRUE;
  int xdr_op_number = 0;
  uint32 cb_id1;
  unsigned int event_id;
  diag_event_listener cb1;
  void *param;

  boolean diag_add_event_listener_result;

  /* XDR OP NUMBER = 1 */
  xdr_op_number = 1;
  xdr_status = XDR_RECV_UINT( srv, &event_id );

  /* XDR OP NUMBER = 2 */
  if ( xdr_status )
  {
    xdr_op_number = 2;
    xdr_status = XDR_RECV_UINT32( srv, &cb_id1 );
  }

  /*lint -save -e611*/
  cb1 = (diag_event_listener) rpc_svc_callback_register( (void *) diag_event_listener_clnt_0x00010001, srv, cb_id1 ); 
  /*lint -restore */

  /* XDR OP NUMBER = 3 */
  if ( xdr_status )
  {
    xdr_op_number = 3;
    xdr_status = XDR_RECV_HANDLE( srv, &param );
  }

  if ( xdr_status )
  {
    xdr_op_number++;
  }

  if ( ! XDR_MSG_DONE( srv ) || ! xdr_status ) {
    XDR_OP_ERR( srv, xdr_op_number );
    // send svcerr_decode reply
    svcerr_decode( srv );
    return;
  }

  diag_add_event_listener_result = diag_add_event_listener(event_id, cb1, param);

  /* XDR OP NUMBER = 1 */
  xdr_op_number = 1;
  xdr_status = xdr_reply_msg_start( srv, &DiagVerf );

  /* XDR OP NUMBER = 2 */
  if ( xdr_status )
  {
    xdr_op_number = 2;
    xdr_status = XDR_SEND_BOOLEAN( srv, &diag_add_event_listener_result );
  }

  if ( ! xdr_status )
  {
    XDR_OP_ERR( srv, xdr_op_number );
    // send svcerr_systemerr reply
    svcerr_systemerr( srv );
    return;
  }

  if ( ! XDR_MSG_SEND( srv, NULL ) ) {
    XDR_MSG_SEND_ERR( srv, NULL );
  }
} /* diag_add_event_listener_0x00010001 */

static void diag_remove_event_listener_0x00010001( xdr_s_type *srv )
{
  boolean xdr_status = TRUE;
  int xdr_op_number = 0;
  uint32 cb_id1;
  unsigned int event_id;
  diag_event_listener cb1;
  void *param;

  boolean diag_remove_event_listener_result;

  /* XDR OP NUMBER = 1 */
  xdr_op_number = 1;
  xdr_status = XDR_RECV_UINT( srv, &event_id );

  /* XDR OP NUMBER = 2 */
  if ( xdr_status )
  {
    xdr_op_number = 2;
    xdr_status = XDR_RECV_UINT32( srv, &cb_id1 );
  }

  /*lint -save -e611*/
  cb1 = (diag_event_listener) rpc_svc_callback_register( (void *) diag_event_listener_clnt_0x00010001, srv, cb_id1 ); 
  /*lint -restore */

  /* XDR OP NUMBER = 3 */
  if ( xdr_status )
  {
    xdr_op_number = 3;
    xdr_status = XDR_RECV_HANDLE( srv, &param );
  }

  if ( xdr_status )
  {
    xdr_op_number++;
  }

  if ( ! XDR_MSG_DONE( srv ) || ! xdr_status ) {
    XDR_OP_ERR( srv, xdr_op_number );
    // send svcerr_decode reply
    svcerr_decode( srv );
    return;
  }

  diag_remove_event_listener_result = diag_remove_event_listener(event_id, cb1, param);

  /* XDR OP NUMBER = 1 */
  xdr_op_number = 1;
  xdr_status = xdr_reply_msg_start( srv, &DiagVerf );

  /* XDR OP NUMBER = 2 */
  if ( xdr_status )
  {
    xdr_op_number = 2;
    xdr_status = XDR_SEND_BOOLEAN( srv, &diag_remove_event_listener_result );
  }

  if ( ! xdr_status )
  {
    XDR_OP_ERR( srv, xdr_op_number );
    // send svcerr_systemerr reply
    svcerr_systemerr( srv );
    return;
  }

  if ( ! XDR_MSG_SEND( srv, NULL ) ) {
    XDR_MSG_SEND_ERR( srv, NULL );
  }
} /* diag_remove_event_listener_0x00010001 */

static void diag_add_log_listener_0x00010001( xdr_s_type *srv )
{
  boolean xdr_status = TRUE;
  int xdr_op_number = 0;
  uint32 cb_id1;
  unsigned int log_code;
  diag_log_listener cb1;
  void *param;

  boolean diag_add_log_listener_result;

  /* XDR OP NUMBER = 1 */
  xdr_op_number = 1;
  xdr_status = XDR_RECV_UINT( srv, &log_code );

  /* XDR OP NUMBER = 2 */
  if ( xdr_status )
  {
    xdr_op_number = 2;
    xdr_status = XDR_RECV_UINT32( srv, &cb_id1 );
  }

  /*lint -save -e611*/
  cb1 = (diag_log_listener) rpc_svc_callback_register( (void *) diag_log_listener_clnt_0x00010001, srv, cb_id1 ); 
  /*lint -restore */

  /* XDR OP NUMBER = 3 */
  if ( xdr_status )
  {
    xdr_op_number = 3;
    xdr_status = XDR_RECV_HANDLE( srv, &param );
  }

  if ( xdr_status )
  {
    xdr_op_number++;
  }

  if ( ! XDR_MSG_DONE( srv ) || ! xdr_status ) {
    XDR_OP_ERR( srv, xdr_op_number );
    // send svcerr_decode reply
    svcerr_decode( srv );
    return;
  }

  diag_add_log_listener_result = diag_add_log_listener(log_code, cb1, param);

  /* XDR OP NUMBER = 1 */
  xdr_op_number = 1;
  xdr_status = xdr_reply_msg_start( srv, &DiagVerf );

  /* XDR OP NUMBER = 2 */
  if ( xdr_status )
  {
    xdr_op_number = 2;
    xdr_status = XDR_SEND_BOOLEAN( srv, &diag_add_log_listener_result );
  }

  if ( ! xdr_status )
  {
    XDR_OP_ERR( srv, xdr_op_number );
    // send svcerr_systemerr reply
    svcerr_systemerr( srv );
    return;
  }

  if ( ! XDR_MSG_SEND( srv, NULL ) ) {
    XDR_MSG_SEND_ERR( srv, NULL );
  }
} /* diag_add_log_listener_0x00010001 */

static void diag_remove_log_listener_0x00010001( xdr_s_type *srv )
{
  boolean xdr_status = TRUE;
  int xdr_op_number = 0;
  uint32 cb_id1;
  unsigned int log_code;
  diag_log_listener cb1;
  void *param;

  boolean diag_remove_log_listener_result;

  /* XDR OP NUMBER = 1 */
  xdr_op_number = 1;
  xdr_status = XDR_RECV_UINT( srv, &log_code );

  /* XDR OP NUMBER = 2 */
  if ( xdr_status )
  {
    xdr_op_number = 2;
    xdr_status = XDR_RECV_UINT32( srv, &cb_id1 );
  }

  /*lint -save -e611*/
  cb1 = (diag_log_listener) rpc_svc_callback_register( (void *) diag_log_listener_clnt_0x00010001, srv, cb_id1 ); 
  /*lint -restore */

  /* XDR OP NUMBER = 3 */
  if ( xdr_status )
  {
    xdr_op_number = 3;
    xdr_status = XDR_RECV_HANDLE( srv, &param );
  }

  if ( xdr_status )
  {
    xdr_op_number++;
  }

  if ( ! XDR_MSG_DONE( srv ) || ! xdr_status ) {
    XDR_OP_ERR( srv, xdr_op_number );
    // send svcerr_decode reply
    svcerr_decode( srv );
    return;
  }

  diag_remove_log_listener_result = diag_remove_log_listener(log_code, cb1, param);

  /* XDR OP NUMBER = 1 */
  xdr_op_number = 1;
  xdr_status = xdr_reply_msg_start( srv, &DiagVerf );

  /* XDR OP NUMBER = 2 */
  if ( xdr_status )
  {
    xdr_op_number = 2;
    xdr_status = XDR_SEND_BOOLEAN( srv, &diag_remove_log_listener_result );
  }

  if ( ! xdr_status )
  {
    XDR_OP_ERR( srv, xdr_op_number );
    // send svcerr_systemerr reply
    svcerr_systemerr( srv );
    return;
  }

  if ( ! XDR_MSG_SEND( srv, NULL ) ) {
    XDR_MSG_SEND_ERR( srv, NULL );
  }
} /* diag_remove_log_listener_0x00010001 */

static void diag_cmd_req_0x00010001( xdr_s_type *srv )
{
  boolean xdr_status = TRUE;
  int xdr_op_number = 0;
  uint32 cb_id1;
  void *memset_temp;
  unsigned int length_unsigned_int;
  byte *req = NULL;
  unsigned int length;
  diag_cmd_rsp cb1;
  void *param;

  boolean diag_cmd_req_result;

  /* XDR OP NUMBER = 1 */
  xdr_op_number = 1;
  xdr_status = XDR_RECV_UINT( srv, &length_unsigned_int );

  /* XDR OP NUMBER = 2 */
  if ( xdr_status && length_unsigned_int > 0 )
  {
    xdr_op_number  = 2;
    memset_temp = oncrpcxdr_mem_alloc( srv, length_unsigned_int * sizeof( *req ));
    memset(memset_temp, 0, length_unsigned_int * sizeof( *req ));
    req = memset_temp;

    xdr_status = XDR_RECV_BYTES(srv, req, length_unsigned_int);
  }

  /* XDR OP NUMBER = 3 */
  if ( xdr_status )
  {
    xdr_op_number = 3;
    xdr_status = XDR_RECV_UINT( srv, &length );
  }

  /* XDR OP NUMBER = 4 */
  if ( xdr_status )
  {
    xdr_op_number = 4;
    xdr_status = XDR_RECV_UINT32( srv, &cb_id1 );
  }

  /*lint -save -e611*/
  cb1 = (diag_cmd_rsp) rpc_svc_callback_register( (void *) diag_cmd_rsp_clnt_0x00010001, srv, cb_id1 ); 
  /*lint -restore */

  /* XDR OP NUMBER = 5 */
  if ( xdr_status )
  {
    xdr_op_number = 5;
    xdr_status = XDR_RECV_HANDLE( srv, &param );
  }

  if ( xdr_status )
  {
    xdr_op_number++;
  }

  if ( ! XDR_MSG_DONE( srv ) || ! xdr_status ) {
    XDR_OP_ERR( srv, xdr_op_number );
    // send svcerr_decode reply
    svcerr_decode( srv );
    return;
  }

  diag_cmd_req_result = diag_cmd_req(req, length, cb1, param);

  /* XDR OP NUMBER = 1 */
  xdr_op_number = 1;
  xdr_status = xdr_reply_msg_start( srv, &DiagVerf );

  /* XDR OP NUMBER = 2 */
  if ( xdr_status )
  {
    xdr_op_number = 2;
    xdr_status = XDR_SEND_BOOLEAN( srv, &diag_cmd_req_result );
  }

  if ( ! xdr_status )
  {
    XDR_OP_ERR( srv, xdr_op_number );
    // send svcerr_systemerr reply
    svcerr_systemerr( srv );
    return;
  }

  if ( ! XDR_MSG_SEND( srv, NULL ) ) {
    XDR_MSG_SEND_ERR( srv, NULL );
  }
} /* diag_cmd_req_0x00010001 */

/*=========================================================================== 
              API Standard function for api versioning
===========================================================================*/

static void diag_api_versions_0x00010001( xdr_s_type *srv )
{
  boolean xdr_status = TRUE;
  int xdr_op_number = 0;
  uint32 i;
  boolean output_pointer_not_null;
  uint32 length_uint32;
  uint32 *len = NULL;

  uint32 *diag_api_versions_result = NULL;

  /* XDR OP NUMBER = 1 */
  xdr_op_number = 1;
  /* The server must know whether to allocate memory for the output parameter
   * len or not. A boolean is received to indicate that.
   */
  xdr_status = XDR_RECV_UINT8( srv, &output_pointer_not_null );

  if ( xdr_status && output_pointer_not_null ) {
    len = oncrpcxdr_mem_alloc( srv, sizeof(*len) );
  }

  if ( xdr_status )
  {
    xdr_op_number++;
  }

  if ( ! XDR_MSG_DONE( srv ) || ! xdr_status ) {
    XDR_OP_ERR( srv, xdr_op_number );
    // send svcerr_decode reply
    svcerr_decode( srv );
    return;
  }

  diag_api_versions_result = diag_api_versions(len);

  /* XDR OP NUMBER = 1 */
  xdr_op_number = 1;
  xdr_status = xdr_reply_msg_start( srv, &DiagVerf );

  /* XDR OP NUMBER = 2 */
  if ( xdr_status )
  {
    xdr_op_number = 2;
    if ( diag_api_versions_result != NULL ) {
      length_uint32 = *len;

      xdr_status = XDR_SEND_UINT32( srv, &length_uint32 );

      /* XDR OP NUMBER = 3 */
      if ( xdr_status )
      {
        xdr_op_number  = 3;

        /* Calling array of XDR routines */
        for ( i = 0; xdr_status && i < (length_uint32); i++ ) {
          /*lint -save -e545*/
          xdr_status = XDR_SEND_UINT32( srv, &(diag_api_versions_result[i]) );
          /*lint -restore */
        }
      }
    } else {
      length_uint32 = 0;

      xdr_status = XDR_SEND_UINT32( srv, &length_uint32 );
    }
  }

  /* XDR OP NUMBER = 3 */
  if ( xdr_status )
  {
    xdr_op_number = 3;
    /*lint -save -e123*/
    XDR_SEND_POINTER( srv, &len, XDR_SEND_UINT32, xdr_status );
    /*lint -restore */
  }

  if ( ! xdr_status )
  {
    XDR_OP_ERR( srv, xdr_op_number );
    // send svcerr_systemerr reply
    svcerr_systemerr( srv );
    return;
  }

  if ( ! XDR_MSG_SEND( srv, NULL ) ) {
    XDR_MSG_SEND_ERR( srv, NULL );
  }
} /* diag_api_versions_0x00010001 */

/*=========================================================================== 
              API Callback Clients
===========================================================================*/

static void diag_event_listener_clnt_0x00010001(uint32 seq_num,  const diag_event_type *event,  void *param)
{
  xdr_s_type       *clnt          = NULL;
  rpc_reply_header  reply_header;
  rpc_cb_data_type *rpc_cb_data   = NULL;
  boolean           xdr_status    = TRUE;
  int               xdr_op_number = 0;

  rpc_cb_data = rpc_svc_cb_data_lookup();

  if ( rpc_cb_data == NULL )
  {
    RPC_SVC_CB_DATA_LOOKUP_ERR();
    return;
  }

  clnt = rpc_clnt_for_callback( rpc_cb_data );

  oncrpcxdr_mem_free( clnt );

  /* XDR OP NUMBER = 1 */
  xdr_op_number = 1;
  xdr_status = xdr_call_msg_start( clnt,
                                   DIAGCBPROG, DIAG_EVENT_LISTENER_VERS,
                                   ONCRPC_DIAG_EVENT_LISTENER_PROC, &DiagcbCred, &DiagcbVerf );

  /* XDR OP NUMBER = 2 */
  if ( xdr_status )
  {
    xdr_op_number = 2;
    xdr_status = XDR_SEND_UINT32( clnt, &rpc_cb_data->cb_id );
  }

  /* XDR OP NUMBER = 3 */
  if ( xdr_status )
  {
    xdr_op_number = 3;
    xdr_status = XDR_SEND_UINT32( clnt, &seq_num );
  }

  /* XDR OP NUMBER = 4 */
  if ( xdr_status )
  {
    xdr_op_number = 4;
    XDR_SEND_POINTER( clnt, &event, xdr_diag_send_diag_event_type, xdr_status );
  }

  /* XDR OP NUMBER = 5 */
  if ( xdr_status )
  {
    xdr_op_number = 5;
    xdr_status = XDR_SEND_HANDLE( clnt, &param );
  }

  if ( ! xdr_status )
  {
    XDR_OP_ERR(clnt, xdr_op_number);
    return;
  }

  /* Send the RPC message and block waiting for a reply */
  if ( ! XDR_MSG_SEND( clnt, &reply_header ) )
  {
    XDR_MSG_SEND_ERR( clnt, &reply_header );
    return;
  }
  /* XDR OP NUMBER = 1 */
  xdr_op_number = 1;

  if ( reply_header.stat != RPC_MSG_ACCEPTED ) {
    XDR_CALL_REJECTED_ERR( clnt, &reply_header );
    xdr_status = FALSE;
  }

  if ( reply_header.u.ar.stat != RPC_ACCEPT_SUCCESS ) {
    XDR_ERR_ON_SERVER_ERR( clnt, &reply_header );
    xdr_status = FALSE;
  }

  if ( xdr_status )
  {
    xdr_op_number++;
  }

  if ( ! XDR_MSG_DONE( clnt ) || ! xdr_status )
  {
        XDR_OP_ERR( clnt, xdr_op_number );
    return;
  }
} /* diag_event_listener_clnt_0x00010001 */


static void diag_log_listener_clnt_0x00010001(
  uint32 seq_num,
  const byte *log,
  unsigned int length,
  void *param
)
{
  xdr_s_type       *clnt          = NULL;
  rpc_reply_header  reply_header;
  rpc_cb_data_type *rpc_cb_data   = NULL;
  boolean           xdr_status    = TRUE;
  int               xdr_op_number = 0;

  unsigned int length_unsigned_int;
  rpc_cb_data = rpc_svc_cb_data_lookup();

  if ( rpc_cb_data == NULL )
  {
    RPC_SVC_CB_DATA_LOOKUP_ERR();
    return;
  }

  clnt = rpc_clnt_for_callback( rpc_cb_data );

  oncrpcxdr_mem_free( clnt );

  /* XDR OP NUMBER = 1 */
  xdr_op_number = 1;
  xdr_status = xdr_call_msg_start( clnt,
                                   DIAGCBPROG, DIAG_LOG_LISTENER_VERS,
                                   ONCRPC_DIAG_LOG_LISTENER_PROC, &DiagcbCred, &DiagcbVerf );

  /* XDR OP NUMBER = 2 */
  if ( xdr_status )
  {
    xdr_op_number = 2;
    xdr_status = XDR_SEND_UINT32( clnt, &rpc_cb_data->cb_id );
  }

  /* XDR OP NUMBER = 3 */
  if ( xdr_status )
  {
    xdr_op_number = 3;
    xdr_status = XDR_SEND_UINT32( clnt, &seq_num );
  }

  /* XDR OP NUMBER = 4 */
  if ( xdr_status )
  {
    xdr_op_number = 4;
    if ( log != NULL ) {
      length_unsigned_int = length;

      xdr_status = XDR_SEND_UINT( clnt, &length_unsigned_int );

      /* XDR OP NUMBER = 5 */
      if ( xdr_status )
      {
        xdr_op_number  = 5;
        xdr_status = XDR_SEND_BYTES(clnt, log, length_unsigned_int);
      }
    } else {
      length_unsigned_int = 0;

      xdr_status = XDR_SEND_UINT( clnt, &length_unsigned_int );
    }
  }

  /* XDR OP NUMBER = 6 */
  if ( xdr_status )
  {
    xdr_op_number = 6;
    xdr_status = XDR_SEND_UINT( clnt, &length );
  }

  /* XDR OP NUMBER = 7 */
  if ( xdr_status )
  {
    xdr_op_number = 7;
    xdr_status = XDR_SEND_HANDLE( clnt, &param );
  }

  if ( ! xdr_status )
  {
    XDR_OP_ERR(clnt, xdr_op_number);
    return;
  }

  /* Send the RPC message and block waiting for a reply */
  if ( ! XDR_MSG_SEND( clnt, &reply_header ) )
  {
    XDR_MSG_SEND_ERR( clnt, &reply_header );
    return;
  }
  /* XDR OP NUMBER = 1 */
  xdr_op_number = 1;

  if ( reply_header.stat != RPC_MSG_ACCEPTED ) {
    XDR_CALL_REJECTED_ERR( clnt, &reply_header );
    xdr_status = FALSE;
  }

  if ( reply_header.u.ar.stat != RPC_ACCEPT_SUCCESS ) {
    XDR_ERR_ON_SERVER_ERR( clnt, &reply_header );
    xdr_status = FALSE;
  }

  if ( xdr_status )
  {
    xdr_op_number++;
  }

  if ( ! XDR_MSG_DONE( clnt ) || ! xdr_status )
  {
        XDR_OP_ERR( clnt, xdr_op_number );
    return;
  }
} /* diag_log_listener_clnt_0x00010001 */


static void diag_cmd_rsp_clnt_0x00010001(const byte *rsp,  unsigned int length,  void *param)
{
  xdr_s_type       *clnt          = NULL;
  rpc_reply_header  reply_header;
  rpc_cb_data_type *rpc_cb_data   = NULL;
  boolean           xdr_status    = TRUE;
  int               xdr_op_number = 0;

  unsigned int length_unsigned_int;
  rpc_cb_data = rpc_svc_cb_data_lookup();

  if ( rpc_cb_data == NULL )
  {
    RPC_SVC_CB_DATA_LOOKUP_ERR();
    return;
  }

  clnt = rpc_clnt_for_callback( rpc_cb_data );

  oncrpcxdr_mem_free( clnt );

  /* XDR OP NUMBER = 1 */
  xdr_op_number = 1;
  xdr_status = xdr_call_msg_start( clnt,
                                   DIAGCBPROG, DIAG_CMD_RSP_VERS,
                                   ONCRPC_DIAG_CMD_RSP_PROC, &DiagcbCred, &DiagcbVerf );

  /* XDR OP NUMBER = 2 */
  if ( xdr_status )
  {
    xdr_op_number = 2;
    xdr_status = XDR_SEND_UINT32( clnt, &rpc_cb_data->cb_id );
  }

  /* XDR OP NUMBER = 3 */
  if ( xdr_status )
  {
    xdr_op_number = 3;
    if ( rsp != NULL ) {
      length_unsigned_int = length;

      xdr_status = XDR_SEND_UINT( clnt, &length_unsigned_int );

      /* XDR OP NUMBER = 4 */
      if ( xdr_status )
      {
        xdr_op_number  = 4;
        xdr_status = XDR_SEND_BYTES(clnt, rsp, length_unsigned_int);
      }
    } else {
      length_unsigned_int = 0;

      xdr_status = XDR_SEND_UINT( clnt, &length_unsigned_int );
    }
  }

  /* XDR OP NUMBER = 5 */
  if ( xdr_status )
  {
    xdr_op_number = 5;
    xdr_status = XDR_SEND_UINT( clnt, &length );
  }

  /* XDR OP NUMBER = 6 */
  if ( xdr_status )
  {
    xdr_op_number = 6;
    xdr_status = XDR_SEND_HANDLE( clnt, &param );
  }

  if ( ! xdr_status )
  {
    XDR_OP_ERR(clnt, xdr_op_number);
    return;
  }

  /* Send the RPC message and block waiting for a reply */
  if ( ! XDR_MSG_SEND( clnt, &reply_header ) )
  {
    XDR_MSG_SEND_ERR( clnt, &reply_header );
    return;
  }
  /* XDR OP NUMBER = 1 */
  xdr_op_number = 1;

  if ( reply_header.stat != RPC_MSG_ACCEPTED ) {
    XDR_CALL_REJECTED_ERR( clnt, &reply_header );
    xdr_status = FALSE;
  }

  if ( reply_header.u.ar.stat != RPC_ACCEPT_SUCCESS ) {
    XDR_ERR_ON_SERVER_ERR( clnt, &reply_header );
    xdr_status = FALSE;
  }

  if ( xdr_status )
  {
    xdr_op_number++;
  }

  if ( ! XDR_MSG_DONE( clnt ) || ! xdr_status )
  {
        XDR_OP_ERR( clnt, xdr_op_number );
    return;
  }
} /* diag_cmd_rsp_clnt_0x00010001 */


