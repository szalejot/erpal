<?php

/**
* @file all functions handling with field formatters
*/


/**
 * Implements hook_field_formatter_info().
 */
function erpal_basic_helper_field_formatter_info() {
  return array(
    'entityreference_typed_label' => array(
      'label' => t('Typed label'),
      'description' => t('Display the label of the referenced entities and add the entity type and bundle as css class.'),
      'field types' => array('entityreference'),
      'settings' => array(
        'link' => FALSE,
      ),
    ),
    'relation_endpoint_simple_table' => array(
      'label' => t('Endpoints simple table'),
      'field types' => array('relation_endpoint'),
    ),
    'entityreference_file_node' => array(
      'label' => t('File node file link'),
      'description' => t('Display the title of a file node and click downloads the file'),
      'field types' => array('entityreference'),     
    ),
    'erpal_diff_default' => array(
      'label' => t('ERPAL comment diff'),
      'field types' => array(
        'nodechanges_revision_diff',
      ),
    ),
  );
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function erpal_basic_helper_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  if ($display['type'] == 'entityreference_typed_label') {
    $element['link'] = array(
      '#title' => t('Link label to the referenced entity'),
      '#type' => 'checkbox',
      '#default_value' => $settings['link'],
    );
  }

  return $element;
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function erpal_basic_helper_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $summary = array();

  if ($display['type'] == 'entityreference_typed_label') {
    $summary[] = $settings['link'] ? t('Link to the referenced entity') : t('No link');
  }

  return implode('<br />', $summary);
}

/**
 * Implements hook_field_formatter_prepare_view().
 */
function erpal_basic_helper_field_formatter_prepare_view($entity_type, $entities, $field, $instances, $langcode, &$items, $displays) {
  $target_ids = array();

  // Collect every possible entity attached to any of the entities.
  foreach ($entities as $id => $entity) {
    
    //check display of each entity    
    
      foreach ($items[$id] as $delta => $item) {
        if (isset($item['target_id'])) {
          $target_ids[] = $item['target_id'];
        }
      }
      
    
  }

  if ($target_ids) {
    $target_entities = entity_load($field['settings']['target_type'], $target_ids);
  }
  else {
    $target_entities = array(); //no entites, no data returned
  }

  // Iterate through the fieldable entities again to attach the loaded data.
  foreach ($entities as $id => $entity) {
    $rekey = FALSE;
    
    foreach ($items[$id] as $delta => $item) {
      // Check whether the referenced entity could be loaded.
      if (isset($item['target_id']) && isset($target_entities[$item['target_id']])) {
        // Replace the instance value with the term data.
        $items[$id][$delta]['entity'] = $target_entities[$item['target_id']];
        // Check whether the user has access to the referenced entity.
        $items[$id][$delta]['access'] = entity_access('view', $field['settings']['target_type'], $target_entities[$item['target_id']]);
      }
      // Otherwise, unset the instance value, since the entity does not exist.
      else {
        if ($displays[$id] == 'relation_endpoint_simple_table') {
          unset($items[$id][$delta]);
          $rekey = TRUE;
        }
      }
    }

    if ($rekey) {
      // Rekey the items array.
      $items[$id] = array_values($items[$id]);
    }
  }
}

/**
 * Implements hook_field_formatter_view().
 */

function erpal_basic_helper_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $display_type = $display['type'];
  
  if ($display_type == 'relation_endpoint_simple_table') {
    return _erpal_basic_helper_formatter_view_relation_endpoint_simple_table($entity_type, $entity, $field, $instance, $langcode, $items, $display);
  } elseif ($display_type == 'entityreference_typed_label') {
    return _erpal_basic_helper_formatter_view_entityreference_typed_label($entity_type, $entity, $field, $instance, $langcode, $items, $display);
  } elseif ($display_type == 'entityreference_file_node') {
    return _erpal_basic_helper_formatter_view_entityreference_file_node($entity_type, $entity, $field, $instance, $langcode, $items, $display);
  } elseif ($display_type == 'erpal_diff_default') {
    return _erpal_basic_helper_formatter_view_erpal_diff_default($entity_type, $entity, $field, $instance, $langcode, $items, $display);
  }
}


/**
* Renders the diff between two values
*/
function _erpal_basic_helper_formatter_nodechange_diff($field_name, $values, $entity, $instance) {
  //handle some ERPAL special fields, for all other fields, take the nodechanges default formatter
  static $nodes = array();
  
  // Remove  'comment_node_'.
  $bundle = substr($instance['bundle'], 13);
  
  $nid = $entity->nid;
  if (isset($nodes[$nid]))
    $node = $nodes[$nid];
  else
    $node = node_load($nid);
  
  $field_info = field_info_field($field_name);
  $field_type = $field_info['type'];

  $out = false;
  if ($field_type == 'taxonomy_term_reference') {
    //render terms    
    foreach (array('old_value', 'new_value') as $key) {
      
      if ($out)
        $out .= ' &raquo; ';
      if (is_array($values[$key])) {
        foreach ($values[$key] as $delta => $value) {
          $tid = $value['tid'];
          $term = taxonomy_term_load($tid);
          $name = $term->name;

          $image_uri = isset($term->field_term_image[LANGUAGE_NONE][0]['uri']) ? $term->field_term_image[LANGUAGE_NONE][0]['uri'] : false;
          $url = '';
          if ($image_uri)
            $url = image_style_url('icon16x16', $image_uri);
   
          $rendered = '<img src="'.$url.'" title="'.$name.'" alt="'.$name.'"/>';
          $out .= $rendered;
        }
      }
    }
    
    return $out;
    
  } elseif ($field_type == 'entityreference') {
    //render users and other entities, just linkt toe title to the entity
    $settings = $field_info['settings'];
    $target_type = $settings['target_type'];
    foreach (array('old_value', 'new_value') as $key) {
      
      if ($out)
        $out .= ' &raquo; ';

      if (isset($values[$key]) && is_array($values[$key])) {
        foreach ($values[$key] as $delta => $value) {
          $id = $value['target_id'];
          $ref_entity = entity_load($target_type, array($id));
          
          if (empty($ref_entity[$id]))
            continue;
            
          $ref_entity = $ref_entity[$id];
          $label = entity_label($target_type, $ref_entity);
          $uri = entity_uri($target_type, $ref_entity);

          $rendered = "<span class='nodechange user'>".l($label, $uri['path'])."</span>";
          $out .= $rendered;
        }
      }
    }
    
    return $out;
  } else {    
    foreach (array('old_value', 'new_value') as $key) {
      
      if ($out)
        $out .= ' &raquo; ';
      if (isset($values[$key]) && is_array($values[$key])) {
        foreach ($values[$key] as $delta => $value) {        
          $rendered = _nodechanges_view_field($entity->nid, $bundle, $field_name, array($delta => $value));
          $out .= $rendered;
        }
      }
    }
    
    return $out;
  }
  
  return false; //handle normal nodechage formatter
}

/**
 * Called in @see erpal_basic_helper_field_formatter_view
 */
function _erpal_basic_helper_formatter_view_erpal_diff_default($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $fields = field_info_fields();
  // Remove  'comment_node_'.
  $bundle = substr($instance['bundle'], 13);
  $instances = field_info_instances('node', $bundle);
  $list = array();

  foreach ($items as $item) {
    $field_name = $item['field_name'];

    if ($field_name == 'field_asset_files')
      continue; //file changes are attached to the comment anyway.
   
    $rendered = _erpal_basic_helper_formatter_nodechange_diff($field_name, $item, $entity, $instance);
    
      
    $list[] = $rendered;    
  }

  if ($list && count($list)) {
    $return =  array(
      '#theme' => 'item_list',
      '#items' => $list,
    );
  } else {
    $return = false;
  }
  
  if ($display['label'] == 'hidden') {
    $return['#title'] = false;
  }
    
  return $return;
}

/**
* Callback used in hook_field_formatter_info to view entityreference_file_node with link to the direct file and to the node
*/
function _erpal_basic_helper_formatter_view_entityreference_file_node($entity_type, $entity, $field, $instance, $langcode, $items, $display) {  
  
  $result = array();
  $settings = $display['settings'];

  // Rebuild the items list to contain only those with access.
  foreach ($items as $key => $item) {
    if (empty($item['access'])) {
      unset($items[$key]);
    }
  }

  $handler = entityreference_get_selection_handler($field, $instance, $entity_type, $entity);

  foreach ($items as $delta => $item) {
    $label = $handler->getLabel($item['entity']);
    // If the link is to be displayed and the entity has a uri, display a link.
    // Note the assignment ($url = ) here is intended to be an assignment.

    if ($uri = entity_uri($field['settings']['target_type'], $item['entity'])) {      
      $download_uri = $item['entity']->field_docs_file[LANGUAGE_NONE][0]['uri'];
      $download_url = file_create_url($download_uri);
      
      $bundle = _erpal_basic_helper_entity_bundle($item['entity'], $field['settings']['target_type']);
      $reference_class = $entity_type."_".$bundle;
      $link = '<span class="file_download_link"><a href="'.$download_url.'">'.$item['entity']->title.'</a></span><span class="file_node_link">'.l(t('view'), $uri['path'], $uri['options']).'</span>';
      
      $result[$delta] = array('#markup' => '<span class="entityreference '.$reference_class.'">'.$link.'</span>');
    }
    else {
      $result[$delta] = array('#markup' => check_plain($label));
    }
  }

  return $result;
}

/**
* Callback used in hook_field_formatter_info to view entityreferences with entity type and bundle class
*/
function _erpal_basic_helper_formatter_view_entityreference_typed_label($entity_type, $entity, $field, $instance, $langcode, $items, $display) {  
  
  $result = array();
  $settings = $display['settings'];

  // Rebuild the items list to contain only those with access.
  foreach ($items as $key => $item) {
    if (empty($item['access'])) {
      unset($items[$key]);
    }
  }

  $handler = entityreference_get_selection_handler($field, $instance, $entity_type, $entity);

  foreach ($items as $delta => $item) {
    $label = $handler->getLabel($item['entity']);
    // If the link is to be displayed and the entity has a uri, display a link.
    // Note the assignment ($url = ) here is intended to be an assignment.

    if ($display['settings']['link'] && ($uri = entity_uri($field['settings']['target_type'], $item['entity']))) {
      $bundle = _erpal_basic_helper_entity_bundle($item['entity'], $field['settings']['target_type']);
      $reference_class = $entity_type."_".$bundle;
      $result[$delta] = array('#markup' => '<span class="entityreference '.$reference_class.'">'.l($label, $uri['path'], $uri['options']).'</span>');
    }
    else {
      $result[$delta] = array('#markup' => check_plain($label));
    }
  }

  return $result;
}

/**
* returns the bundle name of an entity
*/
function _erpal_basic_helper_entity_bundle($entity, $entity_type) {
  $entity_info = entity_get_info($entity_type);
  
  if (isset($entity_info['bundle keys']['bundle']) && isset($entity->{$entity_info['bundle keys']['bundle']}))
    $type = $entity->{$entity_info['bundle keys']['bundle']};
  else
    return false; 
    
  return $type;
}