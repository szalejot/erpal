<?php
/**
 * @file
 * Features integration hooks.
 */

/**
 * Implements hook_features_export_options().
 */
function field_conditional_state_features_export_options() {
  $dependencies = field_conditional_state_load_conditions();
  $entity_info = entity_get_info();
  $options = array();
  foreach ($dependencies as $data) {
      $option = $data['field_name'] . ':' . $data['control_field'] . ':' . $data['state'] . ':' . $data['bundle'] . ':' . $data['type'];  //this must be unique ID
      if (!isset($options[$option])) {
        $options[$option] = $entity_info[$data['type']]['bundles'][$data['bundle']]['label'] . ' (' . $data['type'] . ') - ' . $data['field_name'] . " by " . $data['control_field'];
      }
  }

  return $options;
}

/**
 * Retrieve all conditional states
 */
function field_conditional_state_load_conditions() {
  $conditions = array();
  $result = db_query("SELECT * FROM {field_conditional_state}");
  foreach ($result as $res) {
    $conditions["condition_$res->id"] = array(
      'id' => $res->id,
      'control_field' => $res->control_field,
      'field_name' => $res->field_name,
      'state' => $res->state,
      'trigger_values' => unserialize($res->trigger_values),
      'condition_type' => $res->condition_type,
      'bundle' => $res->bundle,
      'type' => $res->type,
    );
  }
  return $conditions;
}

/**
 * Implements hook_features_export().
 */
function field_conditional_state_features_export($data, &$export, $module_name = '') {
  $export['dependencies']['field_conditional_state'] = 'field_conditional_state';

  foreach ($data as $entity) {
    $export['features']['field_conditional_state'][$entity] = $entity;
  }
}

/**
 * Implements hook_features_export_render().
 */
function field_conditional_state_features_export_render($module_name, $data, $export = NULL) {
  $dependencies = field_conditional_state_load_conditions();
  if (empty($dependencies)) {
    return array();
  }

  $code = array();
  foreach ($data as $option) {
    $tokens = explode(':', $option);

    $field_name = $tokens[0];
    $control_field = $tokens[1];
    $state = $tokens[2];
    $bundle = $tokens[3];
    $type = $tokens[4];
    
    $info = field_conditional_state_get_field_conditions($field_name, $bundle, $type);

    if (!empty($info)) {
      foreach ($info as $field_conditions) {        
          $code[] = '';
          $code[] = '  $items[] = array(';
          $code[] = "    'type' => '" . $type . "',";
          $code[] = "    'bundle' => '" . $bundle . "',";
          $code[] = "    'field_name' => '" . $field_name . "',";
          $code[] = "    'control_field' => '" . $control_field . "',";
          $code[] = "    'state' => '" . $state . "',";
          $code[] = "    'condition_type' => '" . $field_conditions['condition_type'] . "',";
          $code[] = "    'trigger_values' => " . features_var_export($field_conditions['trigger_values'], '    ') . ",";
          $code[] = '  );';
      }
    }
  }
  if (empty($code)) {
    return array();
  }

  array_unshift($code, '  $items = array();');
  $code[] = '';
  $code[] = '  return $items;';
  $output = implode("\n", $code);
  
  return array('field_conditional_state_default_fields' => $output);
}

/**
 * Implements hook_features_rebuild().
 */
function field_conditional_state_features_rebuild($module) {
  $defaults = module_invoke($module, 'field_conditional_state_default_fields');
  
  $dependencies = field_conditional_state_load_conditions();
  $instances = field_info_instances();

  if (!empty($defaults)) {
      
    foreach ($defaults as $condition) {
      
      //insert if not exists
      $existing_conditions = field_conditional_state_get_field_conditions($condition['field_name'], $condition['bundle'], $condition['type']);
    
      if (empty($existing_conditions)) {
        db_insert('field_conditional_state')->fields(array(
          'field_name' => $condition['field_name'],
          'control_field' => $condition['control_field'],
          'state' => $condition['state'],
          'bundle' => $condition['bundle'],
          'type' => $condition['type'],
          'trigger_values' => serialize($condition['trigger_values']),
          'condition_type' => $condition['condition_type'],
        ))
        ->execute();
      }
    }
  }
}


/**
 * Implements hook_features_revert().
 */
function field_conditional_state_features_revert($module) {
  return field_conditional_state_features_rebuild($module);
}
