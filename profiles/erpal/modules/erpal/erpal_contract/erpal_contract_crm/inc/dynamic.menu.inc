<?php

/**
* @file provide functions for dynamic menu items in CRM context
*/

/**
* Implements hook_dynamic_menu_items_alter provided by erpal_basic_helper
* Returns all dynamic contextual menu items, @see erpal_basic_helper.module
*/
function erpal_contract_crm_dynamic_menu_items_alter(&$data, $router_item, $root_path) {
  $node = _erpal_basic_helper_router_object(1, $router_item);
  $is_node_view = !isset($router_item['original_map'][2]) || $router_item['original_map'][2] == 'view'; 
  
  //CRM contacts context
  if (_erpal_basic_helper_has_context(ERPAL_CONTEXT_CONTACT, $router_item)) {    
    _erpal_contract_crm_contact_links($data, $node, $is_node_view); 
  }
  
  //Node Activity Context
  if (_erpal_basic_helper_has_context(ERPAL_CONTEXT_ACTIVITY, $router_item)) {  
    _erpal_contract_crm_node_activity_links($data, $node, $is_node_view); 
  }
 
}


/**
* Adds activity links
*/
function _erpal_contract_crm_node_activity_links(&$data, $activity_node, $is_node_view=false) {
  //single activity context
  if ($is_node_view) {
    $query = array('field_activity_ref' => $activity_node->nid, 'destination' => $_GET['q']);
    erpal_make_action($data, t('Create a new contract from this activity'), 'node/add/erpal-contract', $query);
  }
  
}

/**
* Adds all contact context links
*/
function _erpal_contract_crm_contact_links(&$data, $contact_node, $is_node_view=false) {
  //single contact context
  if ($is_node_view) {    
    $query = array('field_customer_ref' => $contact_node->nid);
    erpal_make_action($data, t('Create a new contract'), 'node/add/erpal-contract', $query);    
  }
}