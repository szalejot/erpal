<?php
/**
 * @file
 * erpal_basic_ui.ds.inc
 */

/**
 * Implements hook_ds_custom_fields_info().
 */
function erpal_basic_ui_ds_custom_fields_info() {
  $export = array();

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'comment_count';
  $ds_field->label = 'comment_count';
  $ds_field->field_type = 7;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->properties = array(
    'default' => array(),
    'settings' => array(
      'show_title' => array(
        'type' => 'checkbox',
      ),
      'title_wrapper' => array(
        'type' => 'textfield',
        'description' => 'Eg: h1, h2, p',
      ),
      'ctools' => array(
        'type' => 'ctools',
      ),
    ),
  );
  $export['comment_count'] = $ds_field;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function erpal_basic_ui_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|erpal_contact|form';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'erpal_contact';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'erpal_forms';
  $ds_layout->settings = array(
    'hide_empty_regions' => 1,
    'hide_sidebars' => FALSE,
    'regions' => array(
      'left' => array(
        0 => 'field_contact_type',
        1 => 'field_gender',
        2 => 'field_company_name',
        3 => 'field_firstname',
        4 => 'field_lastname',
        5 => 'field_contact_image',
        6 => 'field_birthday',
        7 => 'field_contact_relations',
        8 => 'body',
        9 => '_add_existing_field',
      ),
      'advancedleft' => array(
        0 => 'field_vat_number',
        1 => 'field_legal_other',
        2 => 'group_legal',
        3 => 'field_bank_accounts',
        4 => 'field_activity_origin',
      ),
      'right' => array(
        0 => 'field_fax',
        1 => 'field_xing',
        2 => 'field_email',
        3 => 'field_website',
        4 => 'field_addresses',
        5 => 'field_phone',
        6 => 'group_communication',
        7 => 'field_skype',
        8 => 'field_facebook',
        9 => 'field_twitter',
        10 => 'group_weblinks',
        11 => 'field_google_plus',
      ),
      'advancedright' => array(
        0 => 'field_asset_files',
        1 => 'field_customer_category',
        2 => 'field_contact_tags',
      ),
      'hidden' => array(
        0 => 'title',
        1 => 'path',
      ),
    ),
    'fields' => array(
      'field_contact_type' => 'left',
      'field_gender' => 'left',
      'field_company_name' => 'left',
      'field_firstname' => 'left',
      'field_lastname' => 'left',
      'field_contact_image' => 'left',
      'field_birthday' => 'left',
      'field_contact_relations' => 'left',
      'field_vat_number' => 'advancedleft',
      'field_fax' => 'right',
      'body' => 'left',
      'field_legal_other' => 'advancedleft',
      'field_xing' => 'right',
      'field_email' => 'right',
      'field_website' => 'right',
      'field_addresses' => 'right',
      'field_phone' => 'right',
      'group_communication' => 'right',
      'field_skype' => 'right',
      'field_facebook' => 'right',
      'field_twitter' => 'right',
      'group_weblinks' => 'right',
      'field_google_plus' => 'right',
      'group_legal' => 'advancedleft',
      'field_bank_accounts' => 'advancedleft',
      'field_activity_origin' => 'advancedleft',
      'field_asset_files' => 'advancedright',
      'field_customer_category' => 'advancedright',
      'field_contact_tags' => 'advancedright',
      'title' => 'hidden',
      'path' => 'hidden',
      '_add_existing_field' => 'left',
    ),
    'classes' => array(),
  );
  $export['node|erpal_contact|form'] = $ds_layout;

  return $export;
}

/**
 * Implements hook_ds_view_modes_info().
 */
function erpal_basic_ui_ds_view_modes_info() {
  $export = array();

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'in_pane';
  $ds_view_mode->label = 'in-pane';
  $ds_view_mode->entities = array(
    'field_collection_item' => 'field_collection_item',
    'taxonomy_term' => 'taxonomy_term',
  );
  $export['in_pane'] = $ds_view_mode;

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'minimal';
  $ds_view_mode->label = 'minimal';
  $ds_view_mode->entities = array(
    'node' => 'node',
    'taxonomy_term' => 'taxonomy_term',
  );
  $export['minimal'] = $ds_view_mode;

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'view_row_details';
  $ds_view_mode->label = 'view row  details';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['view_row_details'] = $ds_view_mode;

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'visual';
  $ds_view_mode->label = 'visual';
  $ds_view_mode->entities = array(
    'taxonomy_term' => 'taxonomy_term',
  );
  $export['visual'] = $ds_view_mode;

  return $export;
}
