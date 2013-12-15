<?php
/**
 * @file
 * erpal_basic.features.field_conditional_state.inc
 */

/**
 * Implements hook_field_conditional_state_default_fields().
 */
function erpal_basic_field_conditional_state_default_fields() {
  $items = array();

  $items[] = array(
    'type' => 'node',
    'bundle' => 'erpal_contact',
    'field_name' => 'field_company_name',
    'control_field' => 'field_contact_type',
    'state' => 'invisible',
    'condition_type' => 'or',
    'trigger_values' => array(
      'person' => 'person',
    ),
  );

  $items[] = array(
    'type' => 'node',
    'bundle' => 'erpal_contact',
    'field_name' => 'field_firstname',
    'control_field' => 'field_contact_type',
    'state' => 'invisible',
    'condition_type' => 'or',
    'trigger_values' => array(
      'company' => 'company',
    ),
  );

  $items[] = array(
    'type' => 'node',
    'bundle' => 'erpal_contact',
    'field_name' => 'field_gender',
    'control_field' => 'field_contact_type',
    'state' => 'invisible',
    'condition_type' => 'or',
    'trigger_values' => array(
      'company' => 'company',
    ),
  );

  $items[] = array(
    'type' => 'node',
    'bundle' => 'erpal_contact',
    'field_name' => 'field_lastname',
    'control_field' => 'field_contact_type',
    'state' => 'invisible',
    'condition_type' => 'or',
    'trigger_values' => array(
      'company' => 'company',
    ),
  );

  return $items;
}
