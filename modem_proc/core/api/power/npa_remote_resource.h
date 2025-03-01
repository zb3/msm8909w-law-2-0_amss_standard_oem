/*==========================================================================
@file npa_remote_resource.h

NPA Remoting API

Copyright (c) 2010-2013 Qualcomm Technologies Incorporated.
All Rights Reserved.
Qualcomm Confidential and Proprietary

$Header: //components/rel/core.mpss/3.5.c12.3/api/power/npa_remote_resource.h#1 $
============================================================================*/
#ifndef NPA_REMOTE_RESOURCE_H
#define NPA_REMOTE_RESOURCE_H

#include "npa_resource.h"

#ifdef __cplusplus
extern "C" {
#endif

/* NPA Remoting supports the fol. attributes in remote_resource definitions.
 * 
 * NPA_RESOURCE_REMOTE indicates that the resource is hosted remotely
 * and need not be explicitly specified. The attribute is set internally
 * by the framework within npa_remote_define_resource.
 *
 * NPA_RESOURCE_REMOTE_PROXY needs to be explicitly set in the remote
 * resource definition. All resources created via npa_remote_define_resource
 * are local proxies to remote resources. Although it is ultimately the
 * individual protocol that determines what to do when this attribute is set,
 * NPA recommends that this attribute be used to mean that the local proxy
 * mirrors the state of the remote resource. So, when a client issues a state
 * query, the protocol does something protocol-specific to read the actual
 * remote state, at the time of query. This is not required or enforced by NPA.
 *
 * NPA_RESOURCE_REMOTE_NO_INIT may be specified explicitly or is set
 * internally by the framework when local_aggregation_no_initial_request is
 * specified as the driver function. The protocol implementation is expected
 * to check for this attribute when client->type is NPA_CLIENT_INITIALIZE
 * and not issue an initial request to the remote resource, if set.
 */

/* Definition of a remote resource */
typedef struct npa_remote_resource_definition
{
  char                      *local_resource_name;
  char                      *remote_resource_name;
  char                      *protocol_type;
  const npa_resource_plugin *plugin;
  npa_resource_driver_fcn    driver_fcn; 
  const char                *units;
  npa_resource_state         max;           
  unsigned int               attributes;
  /* Data field for resource authors, access via resource->definition->data */
  npa_user_data              data;

 /* Handle to this resource; the field will be initialized in the framework
    when the node is created. Do not define or define as NULL */
  npa_resource              *handle;
} npa_remote_resource_definition;

/* The continuation structure that is passed around from routine to routine
   during remote resource definition. The protocol query routine, when invoked
   with NPA_QUERY_REMOTE_RESOURCE_AVAILABLE, must cast 
   'npa_query_type->data.reference' into this type and use
   'npa_remote_node_continuation->node->name' as name of the remote resource
   whose availability is being sought.
 */
typedef struct npa_remote_node_continuation
{
  npa_node_definition *node;
  npa_resource_state   initial_state;
  npa_callback         callback;
  npa_user_data        cb_data;
  npa_remote_resource_definition *definition;
} npa_remote_node_continuation;


/**
 * <!-- npa_remote_define_resource_cb -->
 *
 * @brief Define a local proxy to a remote resource.
 *
 * This function will construct all NPA structures needed to create
 * a remoted resource and add it to the local resource graph.
 *
 * The local proxy will not be created until both the protocol
 * used to talk to the remote resource and the remote resource
 * is available. The define_callback may be used to determine
 * when clients may be created to the local proxy/remote resource.
 *
 * If the remote resource is not remotely accessible (does not
 * define NPA_RESOURCE_REMOTE_ACCESS_ALLOWED), the local proxy
 * will not be created.
 *
 * @param remote_defn: An instance of npa_remote_resource_definition that
 * describes the remoted resource.
 * @param initial_state: initial state of the local proxy
 * @param define_callback: optional callback that will be invoked when
 * the local proxy (and hence the remote resource) is available.
 * @param define_context: optional context argument to define_callback
 *
 * @return None
 */
void npa_remote_define_resource_cb( npa_remote_resource_definition *resource, 
                                    npa_resource_state              initial_state,
                                    npa_callback                    define_callback,
                                    npa_user_data                   define_context );


/* Stubbed driver functions used to define aggregation semantics.
 * In the future, these may be deprecated and attributes may be used
 * to specify the same semantics.
 *
 * Internally, we set the resource driver function to the protocol driver
 * function in all 3 cases, but perform some setup to cater to the different
 * semantics.
 *
 * Resources that specify local_aggregation_driver need no setup.
 *
 * Resources that specify remote_aggregation_driver are configured to invoke
 * the protocol's custom client_create and destroy functions. They MUST
 * have their plugin field set to npa_identity_plugin
 *
 * Resources that specify local_aggregation_no_initial_request get the
 * NPA_REMOTE_RESOURCE_NO_INIT attribute set. The protocol/resource driver
 * function should check for this attribute, when client->type is
 * NPA_CLIENT_INITIALIZE, and not forward the initial state to the
 * remote resource, if true.
*/

npa_resource_state 
npa_remote_resource_local_aggregation_driver_fcn( 
  struct npa_resource *resource,
  npa_client_handle    client,
  npa_resource_state   state 
  );

npa_resource_state 
npa_remote_resource_local_aggregation_no_initial_request_driver_fcn (
  struct npa_resource *resource,
  npa_client_handle    client,
  npa_resource_state   state 
  );

npa_resource_state 
npa_remote_resource_remote_aggregation_driver_fcn (
  struct npa_resource *resource,
  npa_client_handle    client,
  npa_resource_state   state 
  );


/**
 * <!-- npa_remote_resource_available -->
 *
 * The remote protocol's query function must respond to a query of
 * type NPA_QUERY_REMOTE_RESOURCE_AVAILABLE, by invoking this function
 * with 'query_result.reference' as context, whenever it is that
 * the remote resource is available.
 */
void npa_remote_resource_available( void *context );

typedef enum
{
  NPA_PD_0 = 0,        /* Reserved */
  NPA_PD_1 = (1 << 0),
  NPA_PD_2 = (1 << 1),

  NPA_ALL_PDS = (int)0xFFFFFFFF
} npa_remote_domain_id;

/* DEPRECATED - Old domain IDs without the NPA_ prefix;
   New code must use the above enums */
#define DOMAIN_1 NPA_PD_1
#define DOMAIN_2 NPA_PD_2

/* DEPRECATED - Old domain ID aliases for QuRT-MPD;
   New code must use the enums directly */
#define SENSOR_PD     DOMAIN_1
#define AUDIO_PD      DOMAIN_2
#define ALL_USER_PDS  ALL_DOMAINS 

/**
 * <!-- npa_remote_publish_resource -->
 *
 * @brief Publish a resource to one or more domains
 *
 * This function will publish a resource, when available, to
 * the specified domains. You may call the API again to 
 * publish a previously published resource to more domains.
 * NPA Remoting, in the guest PD, will create proxies for
 * resources published to that PD. All such proxies use
 * remote aggregation.
 *
 * @param remote_domains: domains to publish to; bitwise-ORd
 * @param resource_name: name of the NPA resource to publish
 */
void npa_remote_publish_resource( unsigned int remote_domains,
                                 const char *resource_name );

/**
 * <! --npa_remote_publish_resources -->
 *
 * @brief Publish an array of resources to one or more domains
 *
 * This is a convenience routine that calls npa_remote_publish_resource
 * for every resource in the given array.
 *
 * @param remote_domains: domains to publish to; bitwise-ORd
 * @param num_resources: number of NPA resources to publish
 * @param resources: array of resources to publish
 */
void npa_remote_publish_resources( unsigned int remote_domains,
                                  unsigned int num_resources,
                                  const char *resources[] );


/* DEPRECATED API - invoke callback functions with dal_event callback.
   These calls are deprecated and should not be used by new code */
#define npa_remote_define_resource_dal( remote_defn, initial_state, define_event ) \
  npa_remote_define_resource_cb( remote_defn,                                      \
                                 initial_state,                                    \
                                 NPA_DAL_CALLBACK( define_event ) )


/**
 * <!-- npa_remote_define_resource -->
 *
 * @brief Compatibility wrapper for npa_remote_define_resource_dal
 */
#define npa_remote_define_resource    npa_remote_define_resource_dal

#ifdef __cplusplus
}
#endif

#endif /* NPA_REMOTE_RESOURCE_H */
