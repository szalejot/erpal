<?php
/**
 * @file
 * erpal_project.features.field_conditional_state.inc
 */

/**
 * Implements hook_field_conditional_state_default_fields().
 */
function erpal_project_field_conditional_state_default_fields() {
  $items = array();

  $items[] = array(
    'type' => 'field_collection_item',
    'bundle' => 'field_pricing',
    'field_name' => 'field_budget_low_limit',
    'control_field' => 'field_price_mode',
    'state' => 'visible',
    'condition_type' => 'or',
    'trigger_values' => array(
      'budget' => 'budget',
    ),
  );

  $items[] = array(
    'type' => 'field_collection_item',
    'bundle' => 'field_pricing',
    'field_name' => 'field_users',
    'control_field' => 'field_price_mode',
    'state' => 'visible',
    'condition_type' => 'or',
    'trigger_values' => array(
      'budget' => 'budget',
    ),
  );

  return $items;
}
