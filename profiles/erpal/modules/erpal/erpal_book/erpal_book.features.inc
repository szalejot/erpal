<?php
/**
 * @file
 * erpal_book.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function erpal_book_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_field_default_field_bases_alter().
 */
function erpal_book_field_default_field_bases_alter(&$data) {
  if (isset($data['field_parent'])) {
    $data['field_parent']['settings']['handler_settings']['target_bundles']['erpal_book'] = 'erpal_book'; /* WAS: '' */
    $data['field_parent']['settings']['handler_settings']['target_bundles']['erpal_book_page'] = 'erpal_book_page'; /* WAS: '' */
  }
}

/**
 * Implements hook_node_info().
 */
function erpal_book_node_info() {
  $items = array(
    'erpal_book' => array(
      'name' => t('Document'),
      'base' => 'node_content',
      'description' => t('A document representing a documentation or a proposal or a project specification'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'erpal_book_page' => array(
      'name' => t('Document page'),
      'base' => 'node_content',
      'description' => t('A page with subpages of a document'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
