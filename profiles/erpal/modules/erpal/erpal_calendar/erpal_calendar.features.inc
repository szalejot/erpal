<?php
/**
 * @file
 * erpal_calendar.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function erpal_calendar_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function erpal_calendar_node_info() {
  $items = array(
    'erpal_date' => array(
      'name' => t('Date'),
      'base' => 'node_content',
      'description' => t('A content type for calendar dates in ERPAL'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implements hook_default_date_item_type().
 */
function erpal_calendar_default_date_item_type() {
  $items = array();
  $items['simple_date'] = entity_import('date_item_type', '{
    "name" : "simple_date",
    "label" : "simple date",
    "locked" : "0",
    "weight" : "0",
    "data" : null
  }');
  return $items;
}
