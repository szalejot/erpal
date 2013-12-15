<?php
/**
 * @file
 * erpal_field_pricing.features.field_conditional_state.inc
 */

/**
 * Implements hook_field_conditional_state_default_fields().
 */
function erpal_field_pricing_field_conditional_state_default_fields() {
  $items = array();

  $items[] = array(
    'type' => 'field_collection_item',
    'bundle' => 'field_pricing',
    'field_name' => 'field_budget_time_billing',
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
    'field_name' => 'field_budgets',
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
    'field_name' => 'field_currency',
    'control_field' => 'field_price_mode',
    'state' => 'invisible',
    'condition_type' => 'or',
    'trigger_values' => array(
      'none' => 'none',
      'not_billable' => 'not_billable',
    ),
  );

  $items[] = array(
    'type' => 'field_collection_item',
    'bundle' => 'field_pricing',
    'field_name' => 'field_price',
    'control_field' => 'field_price_mode',
    'state' => 'visible',
    'condition_type' => 'or',
    'trigger_values' => array(
      'fixed_price' => 'fixed_price',
      'per_hour' => 'per_hour',
      'budget' => 'budget',
    ),
  );

  $items[] = array(
    'type' => 'field_collection_item',
    'bundle' => 'field_pricing',
    'field_name' => 'field_vat_rate',
    'control_field' => 'field_price_mode',
    'state' => 'invisible',
    'condition_type' => 'or',
    'trigger_values' => array(
      'none' => 'none',
      'not_billable' => 'not_billable',
    ),
  );

  return $items;
}
