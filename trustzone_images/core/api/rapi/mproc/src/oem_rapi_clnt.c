/* OEM_RAPI TOOL VERSION: 4.30 */
/*=============================================================================
                         O E M _ R A P I _ C L N T . C

GENERAL DESCRIPTION
  This is an AUTO GENERATED file that provides RPC client functionality for the
  oem_rapi API.

  ---------------------------------------------------------------------------
  Copyright (c) 2009 Qualcomm Technologies Incorporated.
  All Rights Reserved. QUALCOMM Proprietary and Confidential.
  ---------------------------------------------------------------------------
=============================================================================*/

/*=============================================================================

                              Edit History

                             AUTO GENERATED                                  */
/* Generated by following versions of Htorpc modules:
Id: //source/qcom/qct/core/mproc/tools/rel/04.01/htorpc/htorpc.pl#11 
Id: //source/qcom/qct/core/mproc/tools/rel/04.01/htorpc/lib/Htorpc/Start.pm#2 
Id: //source/qcom/qct/core/mproc/tools/rel/04.01/htorpc/lib/Htorpc/Htoxdr.pm#1 
Id: //source/qcom/qct/core/mproc/tools/rel/04.01/htorpc/lib/Htorpc/XDR.pm#6 
Id: //source/qcom/qct/core/mproc/tools/rel/04.01/htorpc/lib/Htorpc/Output.pm#20 
Id: //source/qcom/qct/core/mproc/tools/rel/04.01/htorpc/lib/Htorpc/Parser.pm#1 
Id: //source/qcom/qct/core/mproc/tools/rel/04.01/htorpc/lib/Htorpc/Metacomments.pm#3 
Id: //source/qcom/qct/core/mproc/tools/rel/04.01/htorpc/lib/Htorpc/SymbolTable.pm#2  
=============================================================================*/
/*=============================================================================
$Header: //components/rel/tz.bf/2.5.c10/trustzone_images/core/api/rapi/mproc/src/oem_rapi_clnt.c#1 $ 
=============================================================================*/


/* Include files */
#include "oncrpc.h"
#include "oem_rapi.h"
#include "oem_rapi_rpc.h"

/* Only one copy needed per API */
static opaque_auth Oem_rapiCred = { ONCRPC_AUTH_NONE, 0, 0 };
static opaque_auth Oem_rapiVerf = { ONCRPC_AUTH_NONE, 0, 0 };

//static opaque_auth Oem_rapicbCred = { ONCRPC_AUTH_NONE, 0, 0 };
static opaque_auth Oem_rapicbVerf = { ONCRPC_AUTH_NONE, 0, 0 };


/*=======================================================================
             Prototypes for the API Callbacks RPC Server Functions
=======================================================================*/
  
static void oem_rapicbprog_0x00010001 ( struct svc_req *rqstp, xdr_s_type *srv );

static void oem_rapi_streaming_cb_type_svc_0x00010001( xdr_s_type *srv );


/*=======================================================================
             API RPC Clients Implementation
=======================================================================*/

boolean oem_rapi_null(void)
{
  xdr_s_type       *clnt;
  rpc_reply_header  reply_header;
  boolean           xdr_status = TRUE;
  int               xdr_op_number = 0;

  clnt = rpc_clnt_lookup2(OEM_RAPIPROG, OEM_RAPI_NULL_VERS, 0);

  if ( clnt == NULL ) {
    XDR_CLNT_LOOKUP2_ERR(OEM_RAPIPROG, OEM_RAPI_NULL_VERS, 0);
    return FALSE;
  }

  oncrpcxdr_mem_free( clnt );

  /* XDR OP NUMBER = 1 */
  xdr_op_number = 1;
  if ( ! xdr_call_msg_start( clnt,
                             OEM_RAPIPROG, OEM_RAPI_NULL_VERS,
                             ONCRPC_OEM_RAPI_NULL_PROC, &Oem_rapiCred, &Oem_rapiVerf ) ) {
    XDR_OP_ERR( clnt, xdr_op_number );
    return FALSE;
  }

  /* Send the RPC message and block waiting for a reply */
  if ( ! XDR_MSG_SEND( clnt, &reply_header ) )
  {
    XDR_MSG_SEND_ERR( clnt, &reply_header );
    return FALSE;
  }
  /* XDR OP NUMBER = 1 */

  if ( reply_header.stat != RPC_MSG_ACCEPTED )
  {
    XDR_CALL_REJECTED_ERR( clnt, &reply_header );
    xdr_status = FALSE;
  }
  else if ( reply_header.u.ar.stat != RPC_ACCEPT_SUCCESS )
  {
    XDR_ERR_ON_SERVER_ERR( clnt, &reply_header );
    xdr_status = FALSE;
  }

  if ( xdr_status )
  {
    /* XDR OP NUMBER = 2 */
    xdr_op_number = 2;
  }

  if ( ! XDR_MSG_DONE( clnt ) || ! xdr_status )
  {
    XDR_OP_ERR( clnt, xdr_op_number );
    return FALSE;
  }
  else
  {
    return TRUE;
  }
} /* oem_rapi_null */

boolean oem_rapi_rpc_glue_code_info_remote
(
  uint32 *toolvers,
  uint32 *features,
  uint32 *proghash,
  uint32 *cbproghash
)
{
  xdr_s_type       *clnt;
  rpc_reply_header  reply_header;
  uint32            result;
  boolean           xdr_status = TRUE;
  int               xdr_op_number = 0;

  clnt = rpc_clnt_lookup2(OEM_RAPIPROG, OEM_RAPI_RPC_GLUE_CODE_INFO_REMOTE_VERS, 0);

  if ( clnt == NULL ) {
    XDR_CLNT_LOOKUP2_ERR(OEM_RAPIPROG, OEM_RAPI_RPC_GLUE_CODE_INFO_REMOTE_VERS, 0);
    return FALSE;
  }
  oncrpcxdr_mem_free( clnt );

  /* XDR OP NUMBER = 1 */
  xdr_op_number = 1;
  if ( ! xdr_call_msg_start( clnt,
                             OEM_RAPIPROG, OEM_RAPI_RPC_GLUE_CODE_INFO_REMOTE_VERS,
                             ONCRPC_OEM_RAPI_RPC_GLUE_CODE_INFO_REMOTE_PROC, &Oem_rapiCred, &Oem_rapiVerf ) ) {
    XDR_OP_ERR( clnt, xdr_op_number );
    return FALSE;
  }

  /* Send the RPC message and block waiting for a reply */
  if ( ! XDR_MSG_SEND( clnt, &reply_header ) )
  {
    XDR_MSG_SEND_ERR( clnt, &reply_header );
    // return here without calling XDR_MSG_DONE
    return FALSE;
  }
  /* XDR OP NUMBER = 1 */
  xdr_op_number = 1;
  if ( reply_header.stat != RPC_MSG_ACCEPTED )
  {
    XDR_CALL_REJECTED_ERR( clnt, &reply_header );
    xdr_status = FALSE;
  }
  else if ( reply_header.u.ar.stat != RPC_ACCEPT_SUCCESS )
  {
    XDR_ERR_ON_SERVER_ERR( clnt, &reply_header );
    xdr_status = FALSE;
  }

  if ( xdr_status )
  {
    /* XDR OP NUMBER = 2 */
    xdr_op_number = 2;
    xdr_status = XDR_RECV_UINT32( clnt, &result );
  }

  if ( xdr_status )
  {
    if ( toolvers != NULL )
    {
      *toolvers = result;
    }
    /* XDR OP NUMBER = 3 */
    xdr_op_number = 3;
    xdr_status = XDR_RECV_UINT32( clnt, &result );
  }
  if ( xdr_status )
  {
    if ( features != NULL )
    {
      *features = result;
    }
    /* XDR OP NUMBER = 4 */
    xdr_op_number = 4;
    xdr_status = XDR_RECV_UINT32( clnt, &result );
  }

  if ( xdr_status )
  {
    if ( proghash != NULL )
    {
      *proghash = result;
    }
    /* XDR OP NUMBER = 5 */
    xdr_op_number = 5;
    xdr_status = XDR_RECV_UINT32( clnt, &result );
  }
  if ( xdr_status )
  {
    if ( cbproghash != NULL )
    {
      *cbproghash = result;
    }
    /* XDR OP NUMBER = 6 */
    xdr_op_number = 6;
  }

  if ( xdr_status )
  {
    /* XDR OP NUMBER = 7 */
    xdr_op_number = 7;
  }

  if ( ! XDR_MSG_DONE( clnt ) || ! xdr_status )
  {
    XDR_OP_ERR( clnt, xdr_op_number );
    return FALSE;
  }
  else
  {
    return TRUE;
  }
} /* oem_rapi_rpc_glue_code_info_remote */

boolean oem_rapi_rpc_glue_code_info_local
(
  uint32 *toolvers,
  uint32 *features,
  uint32 *proghash,
  uint32 *cbproghash
)
{
  if ( toolvers != NULL )
  {
    *toolvers = OEM_RAPI_TOOLVERS; /* 4.30 */
  }

  if ( features != NULL )
  {
    *features = OEM_RAPI_FEATURES; /* ONCRPC Server Cleanup Support */
                
  }

  if ( proghash != NULL )
  {
    *proghash = 0x00010001; /* 0x00010001 */
  }

  if ( cbproghash != NULL )
  {
    *cbproghash = 0x00010001; /* 0x00010001 */
  }

  return TRUE;
} /* oem_rapi_rpc_glue_code_info_local */

void oem_rapi_streaming_function(
  oem_rapi_client_event_e_type event,
  oem_rapi_streaming_cb_type *callback,
  void *handle,
  uint32 in_len,
  byte *input,
  uint32 *out_len,
  byte *output
)
{
  xdr_s_type *clnt;
  rpc_reply_header reply_header;

  uint32 cb_id;
  uint32 length_uint32;
  boolean output_pointer_not_null;
  boolean xdr_status = TRUE;
  int xdr_op_number = 0;

  clnt = rpc_clnt_lookup2(OEM_RAPIPROG, OEM_RAPI_STREAMING_FUNCTION_VERS, RPC_CLNT_LOOKUP_TIMEOUT);

  if ( clnt == NULL ) {
    XDR_CLNT_LOOKUP2_ERR(OEM_RAPIPROG, OEM_RAPI_STREAMING_FUNCTION_VERS, RPC_CLNT_LOOKUP_TIMEOUT);
    return;
  }

  oncrpcxdr_mem_free( clnt );

  /* XDR OP NUMBER = 1 */
  xdr_op_number = 1;
  xdr_status = xdr_call_msg_start( clnt,
                                   OEM_RAPIPROG, OEM_RAPI_STREAMING_FUNCTION_VERS,
                                   ONCRPC_OEM_RAPI_STREAMING_FUNCTION_PROC, &Oem_rapiCred, &Oem_rapiVerf );

  /* XDR OP NUMBER = 2 */
  if ( xdr_status )
  {
    xdr_op_number = 2;
    xdr_status = XDR_SEND_ENUM( clnt, &event );
  }

  /*lint -save -e611*/
  cb_id = rpc_clnt_callback_register( (void *) callback );
  /*lint -restore */

  /* XDR OP NUMBER = 3 */
  if ( xdr_status )
  {
    xdr_op_number = 3;
    xdr_status = XDR_SEND_UINT32( clnt, &cb_id );
  }

  /* XDR OP NUMBER = 4 */
  if ( xdr_status )
  {
    xdr_op_number = 4;
    xdr_status = XDR_SEND_HANDLE( clnt, &handle );
  }

  /* XDR OP NUMBER = 5 */
  if ( xdr_status )
  {
    xdr_op_number = 5;
    xdr_status = XDR_SEND_UINT32( clnt, &in_len );
  }

  /* XDR OP NUMBER = 6 */
  if ( xdr_status )
  {
    xdr_op_number = 6;
    if ( input != NULL ) {
      length_uint32 = in_len;
      length_uint32 = ( length_uint32 > OEM_RAPI_MAX_CLIENT_INPUT_BUFFER_SIZE ? OEM_RAPI_MAX_CLIENT_INPUT_BUFFER_SIZE : length_uint32 );

      xdr_status = XDR_SEND_UINT32( clnt, &length_uint32 );

      /* XDR OP NUMBER = 7 */
      if ( xdr_status )
      {
        xdr_op_number  = 7;
        xdr_status = XDR_SEND_BYTES(clnt, input, length_uint32);
      }
    } else {
      length_uint32 = 0;

      xdr_status = XDR_SEND_UINT32( clnt, &length_uint32 );
    }
  }

  /* XDR OP NUMBER = 8 */
  if ( xdr_status )
  {
    xdr_op_number = 8;
    /* Send TRUE if out_len is not NULL and FALSE otherwise so that the server
     * can correctly allocate memory for the service to use
     */
    output_pointer_not_null = (out_len != NULL);

    xdr_status = XDR_SEND_UINT8( clnt, &output_pointer_not_null );
  }

  /* XDR OP NUMBER = 9 */
  if ( xdr_status )
  {
    xdr_op_number = 9;
    /* Send TRUE if output is not NULL and FALSE otherwise so that the server
     * can correctly allocate memory for the service to use. Also since this is
     * a pointer to a variable array, we need to send the maximum size of the
     * array too.
     */
    output_pointer_not_null = (output != NULL);

    xdr_status = XDR_SEND_UINT8( clnt, &output_pointer_not_null );

    if ( xdr_status && output_pointer_not_null ) {
      length_uint32 = OEM_RAPI_MAX_CLIENT_OUTPUT_BUFFER_SIZE;

      xdr_status = XDR_SEND_UINT32( clnt, &length_uint32 );

    }
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

  /* XDR OP NUMBER = 2 */
  if ( xdr_status )
  {
    xdr_op_number = 2;
    /*lint -save -e123*/
    XDR_RECV_POINTER( clnt, &out_len, XDR_RECV_UINT32, xdr_status );
    /*lint -restore */
  }

  /* XDR OP NUMBER = 3 */
  if ( xdr_status )
  {
    xdr_op_number = 3;
    xdr_status = XDR_RECV_UINT32( clnt, &length_uint32 );

    /* XDR OP NUMBER = 4 */
    if ( xdr_status && length_uint32 > 0 )
    {
      xdr_op_number  = 4;
      if ( output != NULL ) {
        xdr_status = XDR_RECV_BYTES(clnt, output, length_uint32);
      }
    }
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
} /* oem_rapi_streaming_function */


/*=======================================================================
             API Standard Functions for version info
=======================================================================*/

uint32 *oem_rapi_api_versions(uint32 *len)
{
  xdr_s_type *clnt;
  rpc_reply_header reply_header;

  uint32 i;
  boolean output_pointer_not_null;
  void *memset_temp;
  uint32 length_uint32;
  uint32 *oem_rapi_api_versions_result = NULL;

  do {
    clnt = rpc_clnt_lookup2(OEM_RAPIPROG, OEM_RAPI_API_VERSIONS_VERS, RPC_CLNT_LOOKUP_TIMEOUT);

    if ( clnt == NULL ) {
      XDR_CLNT_LOOKUP2_ERR_FATAL(OEM_RAPIPROG, OEM_RAPI_API_VERSIONS_VERS, RPC_CLNT_LOOKUP_TIMEOUT);
    }

    oncrpcxdr_mem_free( clnt );

    XDR_ERRCHK( clnt, ON );

    (void) xdr_call_msg_start( clnt,
                               OEM_RAPIPROG, OEM_RAPI_API_VERSIONS_VERS,
                               ONCRPC_OEM_RAPI_API_VERSIONS_PROC, &Oem_rapiCred, &Oem_rapiVerf );

    /* Send TRUE if len is not NULL and FALSE otherwise so that the server
     * can correctly allocate memory for the service to use
     */
    output_pointer_not_null = (len != NULL);

    (void) XDR_SEND_UINT8( clnt, &output_pointer_not_null );


    /* Send the RPC message and block waiting for a reply */
  } while ( ! XDR_MSG_SEND( clnt, &reply_header ) );

  if ( reply_header.stat != RPC_MSG_ACCEPTED ) {
    XDR_CALL_REJECTED_ERR_FATAL( clnt, &reply_header );
  }

  if ( reply_header.u.ar.stat != RPC_ACCEPT_SUCCESS ) {
    XDR_ERR_ON_SERVER_ERR_FATAL( clnt, &reply_header );
  }

  (void) XDR_RECV_UINT32( clnt, &length_uint32 );

  if ( length_uint32 > 0 )
  {
    memset_temp = oncrpcxdr_mem_alloc( clnt, length_uint32 * sizeof( *oem_rapi_api_versions_result ));
    memset(memset_temp, 0, length_uint32 * sizeof( *oem_rapi_api_versions_result ));
    oem_rapi_api_versions_result = memset_temp;


    /* Calling array of XDR routines */
    for ( i = 0; i < (length_uint32); i++ ) {
      /*lint -save -e545*/
      (void) XDR_RECV_UINT32( clnt, &(oem_rapi_api_versions_result[i]) );
      /*lint -restore */
    }
  }

  /*lint -save -e123*/
  XDR_RECV_POINTER_NO_ERRCHK( clnt, &len, XDR_RECV_UINT32 );
  /*lint -restore */


  if ( ! XDR_MSG_DONE( clnt ) )
  {
    XDR_OP_ERR_FATAL( clnt, 0 );
  }

  XDR_ERRCHK( clnt, OFF );

  return oem_rapi_api_versions_result;
} /* oem_rapi_api_versions */




/*=======================================================================
             API Callbacks RPC Server Implementation
=======================================================================*/

void oem_rapicb_app_init( void )
{
  (void) svc_register_auto(OEM_RAPICBPROG, OEM_RAPICBVERS, oem_rapicbprog_0x00010001);
} /* oem_rapicb_app_init */

void oem_rapicb_app_lock( boolean lock )
{
  svc_lock( OEM_RAPICBPROG, OEM_RAPICBVERS, lock );
} /* oem_rapicb_app_enable */

static void oem_rapicbprog_0x00010001( struct svc_req *rqstp, xdr_s_type *srv )
{
  switch( rqstp->rq_proc ) {
    case ONCRPC_OEM_RAPI_STREAMING_CB_TYPE_PROC:
      oem_rapi_streaming_cb_type_svc_0x00010001( srv );
      break;
    default:
      // invalid RPC procedure number
      (void) XDR_MSG_DONE( srv );
      svcerr_default_err( srv, rqstp, oem_rapi_api_versions  );
      break;
  }

  oncrpcxdr_mem_free( srv );
} /* oem_rapicbprog_0x00010001 */

static void oem_rapi_streaming_cb_type_svc_0x00010001( xdr_s_type *srv )
{
  oem_rapi_streaming_cb_type *cmd_cb_func;
  uint32  cb_id;
  boolean xdr_status = TRUE;
  int     xdr_op_number = 0;

  void *memset_temp;
  unsigned long int length_unsigned_long_int;
  boolean output_pointer_not_null;
  uint32 length_uint32;
  oem_rapi_server_event_e_type event = OEM_RAPI_SERVER_EVENT_NONE;
  void *handle;
  uint32 in_len;
  byte *input = NULL;
  uint32 *out_len = NULL;
  byte *output = NULL;


  /* XDR OP NUMBER = 1 */
  xdr_op_number = 1;
  xdr_status = XDR_RECV_UINT32( srv, &cb_id );

  /* XDR OP NUMBER = 2 */
  if ( xdr_status )
  {
    xdr_op_number = 2;
    xdr_status = XDR_RECV_ENUM( srv, &event );
  }

  /* XDR OP NUMBER = 3 */
  if ( xdr_status )
  {
    xdr_op_number = 3;
    xdr_status = XDR_RECV_HANDLE( srv, &handle );
  }

  /* XDR OP NUMBER = 4 */
  if ( xdr_status )
  {
    xdr_op_number = 4;
    xdr_status = XDR_RECV_UINT32( srv, &in_len );
  }

  /* XDR OP NUMBER = 5 */
  if ( xdr_status )
  {
    xdr_op_number = 5;
    xdr_status = XDR_RECV_UINT32( srv, &length_unsigned_long_int );

    /* XDR OP NUMBER = 6 */
    if ( xdr_status && length_unsigned_long_int > 0 )
    {
      xdr_op_number  = 6;
      memset_temp = oncrpcxdr_mem_alloc( srv, length_unsigned_long_int * sizeof( *input ));
      memset(memset_temp, 0, length_unsigned_long_int * sizeof( *input ));
      input = memset_temp;

      xdr_status = XDR_RECV_BYTES(srv, input, length_unsigned_long_int);
    }
  }

  /* XDR OP NUMBER = 7 */
  if ( xdr_status )
  {
    xdr_op_number = 7;
    /* The server must know whether to allocate memory for the output parameter
     * out_len or not. A boolean is received to indicate that.
     */
    xdr_status = XDR_RECV_UINT8( srv, &output_pointer_not_null );

    if ( xdr_status && output_pointer_not_null ) {
      out_len = oncrpcxdr_mem_alloc( srv, sizeof(*out_len) );
    }
  }

  /* XDR OP NUMBER = 8 */
  if ( xdr_status )
  {
    xdr_op_number = 8;
    /* The server must know whether to allocate memory for the output parameter
     * output or not. A boolean is received to indicate that. The maximum number
     * of objects that could be pointed to by this pointer is also received.
     */
    xdr_status = XDR_RECV_UINT8( srv, &output_pointer_not_null );

    if ( xdr_status && output_pointer_not_null ) {

      xdr_status = XDR_RECV_UINT32( srv, &length_uint32 );

      output = oncrpcxdr_mem_alloc( srv, length_uint32 * sizeof(*output) );
    }
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

  /*lint -save -e611*/
  cmd_cb_func = (oem_rapi_streaming_cb_type *) rpc_clnt_callback_lookup( cb_id );
  /*lint -restore */

  if ( cmd_cb_func == NULL ) {
    // send svcerr_systemerr reply
    svcerr_systemerr( srv );
    return;
  }

  cmd_cb_func(event, handle, in_len, input, out_len, output);

  /* XDR OP NUMBER = 1 */
  xdr_op_number = 1;
  xdr_status = xdr_reply_msg_start( srv, &Oem_rapicbVerf );

  /* XDR OP NUMBER = 2 */
  if ( xdr_status )
  {
    xdr_op_number = 2;
    /*lint -save -e123*/
    XDR_SEND_POINTER( srv, &out_len, XDR_SEND_UINT32, xdr_status );
    /*lint -restore */
  }

  /* XDR OP NUMBER = 3 */
  if ( xdr_status )
  {
    xdr_op_number = 3;
    if ( output != NULL ) {
      length_unsigned_long_int = *out_len;
      length_unsigned_long_int = ( length_unsigned_long_int > OEM_RAPI_MAX_SERVER_OUTPUT_BUFFER_SIZE ? OEM_RAPI_MAX_SERVER_OUTPUT_BUFFER_SIZE : length_unsigned_long_int );

      xdr_status = XDR_SEND_UINT32( srv, &length_unsigned_long_int );

      /* XDR OP NUMBER = 4 */
      if ( xdr_status )
      {
        xdr_op_number  = 4;
        xdr_status = XDR_SEND_BYTES(srv, output, length_unsigned_long_int);
      }
    } else {
      length_unsigned_long_int = 0;

      xdr_status = XDR_SEND_UINT32( srv, &length_unsigned_long_int );
    }
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
} /* oem_rapi_streaming_cb_type_svc_0x00010001 */

