<?php
/**
 * @file
 * erpal_basic.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function erpal_basic_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_communication|node|erpal_contact|form';
  $field_group->group_name = 'group_communication';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'erpal_contact';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Communications',
    'weight' => '11',
    'children' => array(
      0 => 'field_email',
      1 => 'field_fax',
      2 => 'field_phone',
      3 => 'field_skype',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Communications',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_communication|node|erpal_contact|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_legal|node|erpal_contact|form';
  $field_group->group_name = 'group_legal';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'erpal_contact';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Legal information',
    'weight' => '13',
    'children' => array(
      0 => 'field_legal_other',
      1 => 'field_vat_number',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_legal|node|erpal_contact|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_weblinks|node|erpal_contact|form';
  $field_group->group_name = 'group_weblinks';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'erpal_contact';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Weblinks',
    'weight' => '12',
    'children' => array(
      0 => 'field_facebook',
      1 => 'field_twitter',
      2 => 'field_website',
      3 => 'field_xing',
      4 => 'field_google_plus',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Weblinks',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_weblinks|node|erpal_contact|form'] = $field_group;

  return $export;
}
