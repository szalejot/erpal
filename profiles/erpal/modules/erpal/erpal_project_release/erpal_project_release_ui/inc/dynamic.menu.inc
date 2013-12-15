<?php

/**
* @file provide functions for dynamic menu items in project releases context
*/
//define some contexts
define('ERPAL_CONTEXT_RELEASES', 'releases'); //releases list
define('ERPAL_CONTEXT_RELEASES_GLOBAL', 'releases_global'); //we are in releases view or in a tab that belongs to the release
define('ERPAL_CONTEXT_RELEASE', 'release');
define('ERPAL_CONTEXT_RELEASE_ADD', 'release_add');

/**
* Implement hook_erpal_contexts definied in erpal_basic_helper module
*/
function erpal_project_release_ui_erpal_contexts($router_item) {

  $path = $router_item['path'];
  $contexts = array();

  $node = _erpal_basic_helper_router_object(1, $router_item);
  
  //do we have node add form
  if (drupal_match_path($path, 'node/add/erpal-project-release*')) { 
    $contexts[ERPAL_CONTEXT_RELEASE_ADD] = true;   
  }
  
  //do we have an edit form?
  if ($path == 'node/%/edit') {
    if ($node->type == 'erpal_project_release') {
      $contexts[ERPAL_CONTEXT_RELEASE] = true;
    } 
  }
     
  if (drupal_match_path($path, 'node/%*') ) {    
    if (!$node || !is_object($node))
      return $contexts;
    
    //check if we have a subpath like node/23/invoices or something like this
    $is_crm_context_node = false;
   
    switch ($node->type) {
      case 'erpal_project_release':  
        $contexts[ERPAL_CONTEXT_RELEASE] = true;  
        break;            
    }
  }
  
  //CHECK releases list CONTEXT
  if ($path == 'node/%/releases') { 
    $contexts[ERPAL_CONTEXT_RELEASES] = true;       
  }

  return $contexts;  

}

/**
* Implements hook_dynamic_menu_items_alter provided by erpal_basic_helper
* Returns all dynamic contextual menu items, @see erpal_basic_helper.module
*/
function erpal_project_release_ui_dynamic_menu_items_alter(&$data, $router_item, $root_path) {
  $node = _erpal_basic_helper_router_object(1, $router_item);
  $is_node_view = !isset($router_item['original_map'][2]) || $router_item['original_map'][2] == 'view'; 
  
  //releases list context
  if (_erpal_basic_helper_has_context(ERPAL_CONTEXT_RELEASES, $router_item)) {  
    _erpal_project_release_ui_releases_links($data, $node);       
  }
  
  //Node Release Context
  if (_erpal_basic_helper_has_context(ERPAL_CONTEXT_RELEASE, $router_item)) {  
    _erpal_project_release_ui_node_release_links($data, $node, $is_node_view); 
    _erpal_project_release_ui_projects_global_links($data, $node, array('releases'));
  }
  
  //Node Release Context
  if (_erpal_basic_helper_has_context(ERPAL_CONTEXT_RELEASE_ADD, $router_item)) {  
    _erpal_project_release_ui_node_add_release_links($data, $node, $is_node_view);   

  }

  //show the links in projects context
  $show_global_links = _erpal_basic_helper_has_context(ERPAL_CONTEXT_PROJECTS_GLOBAL, $router_item) ||
    (_erpal_basic_helper_has_context(ERPAL_CONTEXT_PROJECT, $router_item) && $router_item['path'] == 'node/%') ||
    _erpal_basic_helper_has_context(ERPAL_CONTEXT_TIMETRACKING_EDIT, $router_item) ||
    _erpal_basic_helper_has_context(ERPAL_CONTEXT_PROJECT_EDIT, $router_item) ||
    _erpal_basic_helper_has_context(ERPAL_CONTEXT_TASK_EDIT, $router_item) ||
    _erpal_basic_helper_has_context(ERPAL_CONTEXT_TIMETRACKING, $router_item) ||
    _erpal_basic_helper_has_context(ERPAL_CONTEXT_TICKET, $router_item);
    
    
  if ($show_global_links) {    
    _erpal_project_release_ui_projects_global_links($data, $node);
  }
 
}

/**
* Implements hook_erpal_menu_parents provided by erpal_basic_helper
*/
function erpal_project_release_ui_erpal_menu_parents($router_item) {
  return _erpal_project_release_ui_get_menu_parents($router_item);
}

/**
* returns the menu parents for a given router item, according to its context
*/
function _erpal_project_release_ui_get_menu_parents($router_item) {
  $releases = _erpal_basic_helper_has_context(ERPAL_CONTEXT_RELEASES, $router_item);
  $release = _erpal_basic_helper_has_context(ERPAL_CONTEXT_RELEASE, $router_item);
  
  if ($releases || $release) {
    return 'projects';
  }

}

/**
* Adds all activities context links
*/
function _erpal_project_release_ui_releases_links(&$data, $current_node) {
  //releases by project list context
  $project_nid = _erpal_projects_helper_has_project($current_node);

  $query = array('destination' => $_GET['q'], 'field_project_ref' => $project_nid);
  erpal_make_action($data, t('Create a new release'), 'node/add/erpal-project-release', $query);
}

/**
* Adds all activity contact links
*/
function _erpal_project_release_ui_node_release_links(&$data, $release_node, $is_node_view=false) {
  //single activity context
  if ($is_node_view) {
    $query = array();
    erpal_make_action($data, t('Edit this release'), 'node/'.$release_node->nid.'/edit', $query);
    
    //and a link to add more task nodes to a release
    $project_nid = _erpal_projects_helper_has_project($release_node);
    erpal_make_action($data, t('Add tasks to this release'), 'node/'.$release_node->nid.'/addtasks/'.$project_nid, $query);
    erpal_make_action($data, t('Create release documentation'), 'project/release/'.$release_node->nid.'/export', $query);
    
  }
  
}

/**
* Show links on release add page 
*/
function _erpal_project_release_ui_node_add_release_links(&$data, $node, $is_node_view) {
  //the project should already be referenced in the  url. Get it and show the navigation of project view
  $project_nid = isset($_GET['field_project_ref']) ? $_GET['field_project_ref'] : false;

  //if we edit the release, there is no project id in url but on the task
  if (is_numeric(arg(1))) {
    //load the task
    $release_node = node_load(arg(1));
    $project_nid = isset($release_node->field_project_ref[LANGUAGE_NONE][0]['target_id']) ? $release_node->field_project_ref[LANGUAGE_NONE][0]['target_id'] : false;
  }

  if (!$project_nid)
    return;
  
  $project_node = node_load($project_nid);
  _erpal_project_helper_project_global_menu_tabs($data, $project_nid, false, array('releases'));
  _erpal_project_release_ui_projects_global_links($data, $project_node, array('releases'));
 
}


/**
* Adds all projects global context links
*/
function _erpal_project_release_ui_projects_global_links(&$data, $current_node, $active_tabs=array()) {
  $has_node = $current_node;
  
  $options = array('class' => array('releases'));
  if ($has_node && is_object($current_node)) {
    $project_nid = _erpal_projects_helper_has_project($current_node);
 
    _erpal_project_helper_project_global_menu_tabs($data, $project_nid, false, array('releases')); //show all the other project links, too and use the release referenced project as "current node"
    erpal_make_local_tab($data, t('Releases'), 'node/'.$project_nid.'/releases', array(), in_array('releases', $active_tabs),$options);        
  }

}