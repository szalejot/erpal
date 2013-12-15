<?php
/**
 * @file
 * erpal_crm.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function erpal_crm_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'comment-comment_node_erpal_crm_activity-comment_body'
  $field_instances['comment-comment_node_erpal_crm_activity-comment_body'] = array(
    'bundle' => 'comment_node_erpal_crm_activity',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 1,
      ),
      'entityreference_view_widget' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'comment',
    'field_name' => 'comment_body',
    'label' => 'Comment',
    'required' => TRUE,
    'settings' => array(
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'comment-comment_node_erpal_crm_activity-field_asset_files'
  $field_instances['comment-comment_node_erpal_crm_activity-field_asset_files'] = array(
    'bundle' => 'comment_node_erpal_crm_activity',
    'comment_enabled' => 0,
    'default_value' => NULL,
    'default_value_function' => '',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'erpal_basic_helper',
        'settings' => array(),
        'type' => 'entityreference_file_node',
        'weight' => 3,
      ),
    ),
    'entity_type' => 'comment',
    'field_name' => 'field_asset_files',
    'label' => 'Files',
    'required' => 0,
    'settings' => array(
      'behaviors' => array(
        'prepopulate' => array(
          'status' => 0,
        ),
      ),
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'entityreference',
      'settings' => array(
        'match_operator' => 'CONTAINS',
        'path' => '',
        'references_dialog_add' => 1,
        'references_dialog_edit' => 1,
        'references_dialog_search' => 1,
        'references_dialog_search_view' => '',
        'references_dialog_send' => 1,
        'size' => 60,
      ),
      'type' => 'entityreference_autocomplete',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'comment-comment_node_erpal_crm_activity-field_comment_diff'
  $field_instances['comment-comment_node_erpal_crm_activity-field_comment_diff'] = array(
    'bundle' => 'comment_node_erpal_crm_activity',
    'comment_enabled' => 0,
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'erpal_basic_helper',
        'settings' => array(),
        'type' => 'erpal_diff_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'comment',
    'field_name' => 'field_comment_diff',
    'label' => 'Comment diff',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'field_extrawidgets',
      'settings' => array(),
      'type' => 'field_extrawidgets_hidden',
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'comment-comment_node_erpal_crm_activity-field_contacts_ref'
  $field_instances['comment-comment_node_erpal_crm_activity-field_contacts_ref'] = array(
    'bundle' => 'comment_node_erpal_crm_activity',
    'default_value' => NULL,
    'default_value_function' => '',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'erpal_basic_helper',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_typed_label',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'comment',
    'field_name' => 'field_contacts_ref',
    'label' => 'Contacts',
    'required' => 0,
    'settings' => array(
      'behaviors' => array(
        'prepopulate' => array(
          'action' => 'none',
          'fallback' => 'none',
          'skip_perm' => 0,
          'status' => 0,
        ),
      ),
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'entityreference',
      'settings' => array(
        'match_operator' => 'CONTAINS',
        'path' => '',
        'references_dialog_add' => 0,
        'references_dialog_edit' => 0,
        'references_dialog_search' => 0,
        'references_dialog_search_view' => '',
        'size' => 60,
      ),
      'type' => 'entityreference_autocomplete',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'node-erpal_crm_activity-body'
  $field_instances['node-erpal_crm_activity-body'] = array(
    'bundle' => 'erpal_crm_activity',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
      'entityreference_view_widget' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(
          'trim_length' => 600,
        ),
        'type' => 'text_summary_or_trimmed',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'body',
    'label' => 'Body',
    'required' => FALSE,
    'settings' => array(
      'display_summary' => TRUE,
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'text',
      'settings' => array(
        'rows' => 20,
        'summary_rows' => 5,
      ),
      'type' => 'text_textarea_with_summary',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'node-erpal_crm_activity-field_account_manager'
  $field_instances['node-erpal_crm_activity-field_account_manager'] = array(
    'bundle' => 'erpal_crm_activity',
    'default_value' => NULL,
    'default_value_function' => '',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'erpal_basic_helper',
        'settings' => array(
          'link' => TRUE,
        ),
        'type' => 'entityreference_typed_label',
        'weight' => 3,
      ),
      'entityreference_view_widget' => array(
        'label' => 'above',
        'module' => 'erpal_basic_helper',
        'settings' => array(
          'link' => TRUE,
        ),
        'type' => 'entityreference_typed_label',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'module' => 'erpal_basic_helper',
        'settings' => array(
          'link' => TRUE,
        ),
        'type' => 'entityreference_typed_label',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_account_manager',
    'label' => 'Account Manager',
    'required' => 0,
    'settings' => array(
      'behaviors' => array(
        'prepopulate' => array(
          'action' => 'none',
          'fallback' => 'none',
          'skip_perm' => 0,
          'status' => 0,
        ),
      ),
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'entityreference',
      'settings' => array(
        'match_operator' => 'CONTAINS',
        'path' => '',
        'references_dialog_add' => 0,
        'references_dialog_edit' => 0,
        'references_dialog_search' => 0,
        'references_dialog_search_view' => '',
        'size' => 60,
      ),
      'type' => 'entityreference_autocomplete',
      'weight' => 10,
    ),
  );

  // Exported field_instance: 'node-erpal_crm_activity-field_activity_origin'
  $field_instances['node-erpal_crm_activity-field_activity_origin'] = array(
    'bundle' => 'erpal_crm_activity',
    'comment_enabled' => 0,
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Where the activity started',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 19,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_activity_origin',
    'label' => 'Origin',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
      ),
      'type' => 'options_select',
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'node-erpal_crm_activity-field_activity_status_term'
  $field_instances['node-erpal_crm_activity-field_activity_status_term'] = array(
    'bundle' => 'erpal_crm_activity',
    'comment_enabled' => 1,
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 17,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_activity_status_term',
    'label' => 'Status',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 4,
    ),
  );

  // Exported field_instance: 'node-erpal_crm_activity-field_asset_files'
  $field_instances['node-erpal_crm_activity-field_asset_files'] = array(
    'bundle' => 'erpal_crm_activity',
    'comment_enabled' => 0,
    'default_value' => NULL,
    'default_value_function' => '',
    'deleted' => 0,
    'description' => 'Select or add files from / to the document management system',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'erpal_basic_helper',
        'settings' => array(
          'link' => TRUE,
        ),
        'type' => 'entityreference_typed_label',
        'weight' => 8,
      ),
      'entityreference_view_widget' => array(
        'label' => 'above',
        'module' => 'erpal_basic_helper',
        'settings' => array(
          'link' => TRUE,
        ),
        'type' => 'entityreference_typed_label',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'module' => 'erpal_basic_helper',
        'settings' => array(
          'link' => TRUE,
        ),
        'type' => 'entityreference_typed_label',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_asset_files',
    'label' => 'Attached files',
    'required' => 0,
    'settings' => array(
      'behaviors' => array(
        'prepopulate' => array(
          'status' => 0,
        ),
      ),
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'entityreference',
      'settings' => array(
        'match_operator' => 'CONTAINS',
        'path' => '',
        'references_dialog_add' => 1,
        'references_dialog_edit' => 1,
        'references_dialog_search' => 1,
        'references_dialog_search_view' => '',
        'size' => 60,
      ),
      'type' => 'entityreference_autocomplete',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'node-erpal_crm_activity-field_chance'
  $field_instances['node-erpal_crm_activity-field_chance'] = array(
    'bundle' => 'erpal_crm_activity',
    'comment_enabled' => 0,
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The chance to succeed.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 7,
      ),
      'entityreference_view_widget' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_chance',
    'label' => 'Chance',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
      ),
      'type' => 'options_select',
      'weight' => 7,
    ),
  );

  // Exported field_instance: 'node-erpal_crm_activity-field_contacts_ref'
  $field_instances['node-erpal_crm_activity-field_contacts_ref'] = array(
    'bundle' => 'erpal_crm_activity',
    'default_value' => NULL,
    'default_value_function' => '',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'erpal_basic_helper',
        'settings' => array(
          'link' => TRUE,
        ),
        'type' => 'entityreference_typed_label',
        'weight' => 14,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_contacts_ref',
    'label' => 'Contacts',
    'required' => 0,
    'settings' => array(
      'behaviors' => array(
        'prepopulate' => array(
          'action' => 'none',
          'fallback' => 'none',
          'skip_perm' => 0,
          'status' => 0,
        ),
      ),
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'entityreference',
      'settings' => array(
        'match_operator' => 'CONTAINS',
        'path' => '',
        'references_dialog_add' => 1,
        'references_dialog_edit' => 1,
        'references_dialog_search' => 1,
        'references_dialog_search_view' => '',
        'size' => 60,
      ),
      'type' => 'entityreference_autocomplete',
      'weight' => 7,
    ),
  );

  // Exported field_instance: 'node-erpal_crm_activity-field_customer_ref'
  $field_instances['node-erpal_crm_activity-field_customer_ref'] = array(
    'bundle' => 'erpal_crm_activity',
    'default_value' => NULL,
    'default_value_function' => 'entityreference_prepopulate_field_default_value',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'erpal_basic_helper',
        'settings' => array(
          'link' => TRUE,
        ),
        'type' => 'entityreference_typed_label',
        'weight' => 13,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_customer_ref',
    'label' => 'Customer',
    'required' => 1,
    'settings' => array(
      'behaviors' => array(
        'prepopulate' => array(
          'action' => 'disable',
          'fallback' => 'none',
          'skip_perm' => 0,
          'status' => 1,
        ),
      ),
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'entityreference',
      'settings' => array(
        'match_operator' => 'CONTAINS',
        'path' => '',
        'references_dialog_add' => 1,
        'references_dialog_edit' => 1,
        'references_dialog_search' => 1,
        'references_dialog_search_view' => '',
        'size' => 60,
      ),
      'type' => 'entityreference_autocomplete',
      'weight' => 3,
    ),
  );

  // Exported field_instance: 'node-erpal_crm_activity-field_expected_date'
  $field_instances['node-erpal_crm_activity-field_expected_date'] = array(
    'bundle' => 'erpal_crm_activity',
    'comment_enabled' => 0,
    'date_item' => array(
      'create_date_item' => 0,
      'date_item_type' => 'simple_date',
      'handle_range' => 'range',
    ),
    'deleted' => 0,
    'description' => 'When do you expect the order',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'date',
        'settings' => array(
          'format_type' => 'long',
          'fromto' => 'both',
          'multiple_from' => '',
          'multiple_number' => '',
          'multiple_to' => '',
          'show_repeat_rule' => 'show',
        ),
        'type' => 'date_default',
        'weight' => 15,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_expected_date',
    'label' => 'Expected date',
    'required' => 0,
    'settings' => array(
      'default_value' => 'blank',
      'default_value2' => 'same',
      'default_value_code' => '',
      'default_value_code2' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'date',
      'settings' => array(
        'increment' => 15,
        'input_format' => 'm/d/Y - H:i:s',
        'input_format_custom' => '',
        'label_position' => 'above',
        'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
        'repeat_collapsed' => 0,
        'text_parts' => array(),
        'year_range' => '-3:+3',
      ),
      'type' => 'date_popup',
      'weight' => 8,
    ),
  );

  // Exported field_instance: 'node-erpal_crm_activity-field_next_contact'
  $field_instances['node-erpal_crm_activity-field_next_contact'] = array(
    'bundle' => 'erpal_crm_activity',
    'comment_enabled' => 1,
    'date_item' => array(
      'create_date_item' => 1,
      'date_item_type' => 'simple_date',
      'handle_range' => 'range',
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'date',
        'settings' => array(
          'format_type' => 'long',
          'fromto' => 'both',
          'multiple_from' => '',
          'multiple_number' => '',
          'multiple_to' => '',
          'show_repeat_rule' => 'show',
        ),
        'type' => 'date_default',
        'weight' => 4,
      ),
      'entityreference_view_widget' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_next_contact',
    'label' => 'Next Contact',
    'required' => 0,
    'settings' => array(
      'default_value' => 'strtotime',
      'default_value2' => 'same',
      'default_value_code' => '+14 days',
      'default_value_code2' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'date',
      'settings' => array(
        'increment' => 15,
        'input_format' => 'm/d/Y - H:i:s',
        'input_format_custom' => '',
        'label_position' => 'above',
        'repeat_collapsed' => 0,
        'text_parts' => array(),
        'year_range' => '-3:+3',
      ),
      'type' => 'date_popup',
      'weight' => 5,
    ),
  );

  // Exported field_instance: 'node-erpal_crm_activity-field_order_number_extern'
  $field_instances['node-erpal_crm_activity-field_order_number_extern'] = array(
    'bundle' => 'erpal_crm_activity',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The number that identifies this order at your customer',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 12,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_order_number_extern',
    'label' => 'Order number extern',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 9,
    ),
  );

  // Exported field_instance: 'node-erpal_crm_activity-field_order_number_intern'
  $field_instances['node-erpal_crm_activity-field_order_number_intern'] = array(
    'bundle' => 'erpal_crm_activity',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Your internal number that identifies the order',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 11,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_order_number_intern',
    'label' => 'Order number intern',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 8,
    ),
  );

  // Exported field_instance: 'node-erpal_crm_activity-field_volume'
  $field_instances['node-erpal_crm_activity-field_volume'] = array(
    'bundle' => 'erpal_crm_activity',
    'comment_enabled' => 0,
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'The suggested volume',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 2,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_decimal',
        'weight' => 6,
      ),
      'entityreference_view_widget' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_volume',
    'label' => 'Volume',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(
        'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
      ),
      'type' => 'number',
      'weight' => 6,
    ),
  );

  // Exported field_instance: 'relation-works_at-endpoints'
  $field_instances['relation-works_at-endpoints'] = array(
    'bundle' => 'works_at',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'relation_endpoint',
        'settings' => array(
          'view_modes' => array(
            'billable' => 'default',
            'budget' => 'default',
            'comment' => 'default',
            'field_collection_item' => 'default',
            'file' => 'default',
            'node' => 'default',
            'profile2' => 'default',
            'profile2_type' => 'default',
            'relation' => 'default',
            'taxonomy_term' => 'default',
            'taxonomy_vocabulary' => 'default',
            'user' => 'default',
          ),
        ),
        'type' => 'relation_endpoint',
        'weight' => 0,
      ),
      'entityreference_view_widget' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'relation',
    'field_name' => 'endpoints',
    'label' => 'endpoints',
    'required' => FALSE,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'module' => 'relation_endpoint',
      'settings' => array(),
      'type' => 'relation_endpoint',
      'weight' => 0,
    ),
  );

  // Exported field_instance: 'relation-works_at-field_date'
  $field_instances['relation-works_at-field_date'] = array(
    'bundle' => 'works_at',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'date',
        'settings' => array(
          'format_type' => 'long',
          'fromto' => 'both',
          'multiple_from' => '',
          'multiple_number' => '',
          'multiple_to' => '',
          'show_repeat_rule' => 'show',
        ),
        'type' => 'date_default',
        'weight' => 1,
      ),
      'entityreference_view_widget' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'relation',
    'field_name' => 'field_date',
    'label' => 'Period',
    'required' => 0,
    'settings' => array(
      'default_value' => 'blank',
      'default_value2' => 'blank',
      'default_value_code' => '',
      'default_value_code2' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'date',
      'settings' => array(
        'increment' => 15,
        'input_format' => 'm/d/Y - H:i:s',
        'input_format_custom' => '',
        'label_position' => 'above',
        'repeat_collapsed' => 0,
        'text_parts' => array(),
        'year_range' => '-3:+3',
      ),
      'type' => 'date_popup',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'relation-works_at-field_work_at_rel_tags'
  $field_instances['relation-works_at-field_work_at_rel_tags'] = array(
    'bundle' => 'works_at',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'taxonomy',
        'settings' => array(),
        'type' => 'taxonomy_term_reference_link',
        'weight' => 2,
      ),
      'entityreference_view_widget' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'relation',
    'field_name' => 'field_work_at_rel_tags',
    'label' => 'Relation Tags',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'taxonomy',
      'settings' => array(
        'autocomplete_path' => 'taxonomy/autocomplete',
        'size' => 60,
      ),
      'type' => 'taxonomy_autocomplete',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'taxonomy_term-activity_origin-field_is_default_term'
  $field_instances['taxonomy_term-activity_origin-field_is_default_term'] = array(
    'bundle' => 'activity_origin',
    'comment_enabled' => 0,
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'taxonomy_term',
    'field_name' => 'field_is_default_term',
    'label' => 'Is default',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 0,
        'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
      ),
      'type' => 'options_onoff',
      'weight' => 32,
    ),
  );

  // Exported field_instance: 'taxonomy_term-activity_status_terms-field_activity_actions'
  $field_instances['taxonomy_term-activity_status_terms-field_activity_actions'] = array(
    'bundle' => 'activity_status_terms',
    'comment_enabled' => 0,
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 3,
      ),
    ),
    'entity_type' => 'taxonomy_term',
    'field_name' => 'field_activity_actions',
    'label' => 'Activity actions',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'maxlength_js_label' => 'Content limited to @limit characters, remaining: <strong>@remaining</strong>',
      ),
      'type' => 'options_buttons',
      'weight' => 33,
    ),
  );

  // Exported field_instance: 'taxonomy_term-activity_status_terms-field_is_default_term'
  $field_instances['taxonomy_term-activity_status_terms-field_is_default_term'] = array(
    'bundle' => 'activity_status_terms',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => 'Check, if this is the default value on fields where to select on of the terms in this vocabulary',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'taxonomy_term',
    'field_name' => 'field_is_default_term',
    'label' => 'Is default',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 0,
      ),
      'type' => 'options_onoff',
      'weight' => 2,
    ),
  );

  // Exported field_instance: 'taxonomy_term-activity_status_terms-field_simple_process_status'
  $field_instances['taxonomy_term-activity_status_terms-field_simple_process_status'] = array(
    'bundle' => 'activity_status_terms',
    'default_value' => array(
      0 => array(
        'value' => 'in_progress',
      ),
    ),
    'deleted' => 0,
    'description' => 'This gives the status tag a semantic meaning',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'taxonomy_term',
    'field_name' => 'field_simple_process_status',
    'label' => 'Semantic process',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 1,
    ),
  );

  // Exported field_instance: 'taxonomy_term-activity_status_terms-field_term_image'
  $field_instances['taxonomy_term-activity_status_terms-field_term_image'] = array(
    'bundle' => 'activity_status_terms',
    'comment_enabled' => 0,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => '',
        ),
        'type' => 'image',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'taxonomy_term',
    'field_name' => 'field_term_image',
    'label' => 'Term image',
    'required' => 0,
    'settings' => array(
      'alt_field' => 0,
      'default_image' => 0,
      'file_directory' => 'term_images',
      'file_extensions' => 'png gif jpg jpeg',
      'max_filesize' => '',
      'max_resolution' => '',
      'min_resolution' => '',
      'title_field' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'image',
      'settings' => array(
        'preview_image_style' => 'thumbnail',
        'progress_indicator' => 'throbber',
      ),
      'type' => 'image_image',
      'weight' => 32,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Account Manager');
  t('Activity actions');
  t('Attached files');
  t('Body');
  t('Chance');
  t('Check, if this is the default value on fields where to select on of the terms in this vocabulary');
  t('Comment');
  t('Comment diff');
  t('Contacts');
  t('Customer');
  t('Expected date');
  t('Files');
  t('Is default');
  t('Next Contact');
  t('Order number extern');
  t('Order number intern');
  t('Origin');
  t('Period');
  t('Relation Tags');
  t('Select or add files from / to the document management system');
  t('Semantic process');
  t('Status');
  t('Term image');
  t('The chance to succeed.');
  t('The number that identifies this order at your customer');
  t('The suggested volume');
  t('This gives the status tag a semantic meaning');
  t('Volume');
  t('When do you expect the order');
  t('Where the activity started');
  t('Your internal number that identifies the order');
  t('endpoints');

  return $field_instances;
}
