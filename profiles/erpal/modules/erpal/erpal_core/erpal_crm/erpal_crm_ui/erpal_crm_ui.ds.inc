<?php
/**
 * @file
 * erpal_crm_ui.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function erpal_crm_ui_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|erpal_contact|in_activity';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'erpal_contact';
  $ds_fieldsetting->view_mode = 'in_activity';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'link' => '1',
        'wrapper' => 'h2',
        'class' => 'entityreference node_erpal_contact',
      ),
    ),
  );
  $export['node|erpal_contact|in_activity'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function erpal_crm_ui_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|erpal_contact|in_activity';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'erpal_contact';
  $ds_layout->view_mode = 'in_activity';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'hide_empty_regions' => 1,
    'hide_sidebars' => 1,
    'regions' => array(
      'ds_content' => array(
        0 => 'title',
        1 => 'field_phone',
        2 => 'field_email',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'field_phone' => 'ds_content',
      'field_email' => 'ds_content',
    ),
    'classes' => array(),
  );
  $export['node|erpal_contact|in_activity'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|erpal_crm_activity|form';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'erpal_crm_activity';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'erpal_forms';
  $ds_layout->settings = array(
    'hide_empty_regions' => 1,
    'hide_sidebars' => FALSE,
    'regions' => array(
      'left' => array(
        0 => 'title',
        1 => 'body',
        2 => 'field_asset_files',
      ),
      'right' => array(
        0 => 'field_customer_ref',
        1 => 'field_activity_status_term',
        2 => 'field_next_contact',
        3 => 'field_activity_origin',
      ),
      'advancedright' => array(
        0 => 'field_volume',
        1 => 'field_chance',
        2 => 'field_expected_date',
        3 => 'group_chance',
      ),
      'advancedleft' => array(
        0 => 'field_contacts_ref',
        1 => 'field_order_number_intern',
        2 => 'field_order_number_extern',
        3 => 'field_account_manager',
        4 => 'field_task_ref',
      ),
      'hidden' => array(
        0 => 'path',
        1 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'title' => 'left',
      'body' => 'left',
      'field_asset_files' => 'left',
      'field_customer_ref' => 'right',
      'field_activity_status_term' => 'right',
      'field_next_contact' => 'right',
      'field_activity_origin' => 'right',
      'field_volume' => 'advancedright',
      'field_contacts_ref' => 'advancedleft',
      'field_chance' => 'advancedright',
      'field_order_number_intern' => 'advancedleft',
      'field_expected_date' => 'advancedright',
      'field_order_number_extern' => 'advancedleft',
      'field_account_manager' => 'advancedleft',
      'field_task_ref' => 'advancedleft',
      'group_chance' => 'advancedright',
      'path' => 'hidden',
      '_add_existing_field' => 'hidden',
    ),
    'classes' => array(),
  );
  $export['node|erpal_crm_activity|form'] = $ds_layout;

  return $export;
}
