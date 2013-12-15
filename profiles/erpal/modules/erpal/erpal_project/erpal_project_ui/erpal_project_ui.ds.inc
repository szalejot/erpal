<?php
/**
 * @file
 * erpal_project_ui.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function erpal_project_ui_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|erpal_project|full';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'erpal_project';
  $ds_fieldsetting->view_mode = 'full';
  $ds_fieldsetting->settings = array(
    'budget_usage' => array(
      'weight' => '6',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'title' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'author' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'author',
    ),
    'post_date' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'ds_post_date_long',
    ),
  );
  $export['node|erpal_project|full'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|erpal_task|full';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'erpal_task';
  $ds_fieldsetting->view_mode = 'full';
  $ds_fieldsetting->settings = array(
    'budget_usage' => array(
      'weight' => '8',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'links' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'author' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'author',
    ),
    'post_date' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'ds_post_date_long',
    ),
  );
  $export['node|erpal_task|full'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|erpal_task|minimal';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'erpal_task';
  $ds_fieldsetting->view_mode = 'minimal';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'link' => '1',
        'wrapper' => 'h2',
        'class' => '',
      ),
    ),
  );
  $export['node|erpal_task|minimal'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|erpal_task|view_row_details';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'erpal_task';
  $ds_fieldsetting->view_mode = 'view_row_details';
  $ds_fieldsetting->settings = array(
    'comment_count' => array(
      'weight' => '12',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'show_title' => 0,
        'title_wrapper' => '',
        'ctools' => 'a:3:{s:4:"conf";a:5:{s:11:"admin_title";s:0:"";s:5:"title";s:0:"";s:4:"body";s:28:"%node:comment-count comments";s:6:"format";s:13:"filtered_html";s:10:"substitute";i:1;}s:4:"type";s:6:"custom";s:7:"subtype";s:6:"custom";}',
        'load_terms' => 0,
      ),
    ),
    'files_count' => array(
      'weight' => '11',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'show_title' => 0,
        'title_wrapper' => '',
        'ctools' => 'a:3:{s:4:"conf";a:2:{s:5:"types";a:0:{}s:10:"field_name";s:0:"";}s:4:"type";s:11:"files_count";s:7:"subtype";s:11:"files_count";}',
        'load_terms' => 0,
      ),
    ),
    'task_customer_node' => array(
      'weight' => '2',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'show_title' => 1,
        'title_wrapper' => '',
        'ctools' => 'a:3:{s:4:"conf";a:2:{s:5:"types";a:0:{}s:10:"field_name";s:0:"";}s:4:"type";s:13:"task_customer";s:7:"subtype";s:13:"task_customer";}',
        'load_terms' => 0,
      ),
    ),
    'task_title' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'show_title' => 0,
        'title_wrapper' => 'h2',
        'ctools' => 'a:3:{s:4:"conf";a:5:{s:11:"admin_title";s:10:"Task title";s:5:"title";s:0:"";s:4:"body";s:74:"<a href="/node/%node:nid">%node:field_is_ticket #%node:nid %node:title</a>";s:6:"format";s:13:"filtered_html";s:10:"substitute";i:1;}s:4:"type";s:6:"custom";s:7:"subtype";s:6:"custom";}',
        'load_terms' => 0,
      ),
    ),
    'author' => array(
      'weight' => '10',
      'label' => 'above',
      'format' => 'author_linked',
    ),
    'post_date' => array(
      'weight' => '11',
      'label' => 'above',
      'format' => 'ds_post_date_short',
    ),
  );
  $export['node|erpal_task|view_row_details'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'taxonomy_term|priority_terms|minimal';
  $ds_fieldsetting->entity_type = 'taxonomy_term';
  $ds_fieldsetting->bundle = 'priority_terms';
  $ds_fieldsetting->view_mode = 'minimal';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['taxonomy_term|priority_terms|minimal'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'taxonomy_term|task_status_terms|default';
  $ds_fieldsetting->entity_type = 'taxonomy_term';
  $ds_fieldsetting->bundle = 'task_status_terms';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['taxonomy_term|task_status_terms|default'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'taxonomy_term|task_status_terms|in_pane';
  $ds_fieldsetting->entity_type = 'taxonomy_term';
  $ds_fieldsetting->bundle = 'task_status_terms';
  $ds_fieldsetting->view_mode = 'in_pane';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['taxonomy_term|task_status_terms|in_pane'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'taxonomy_term|task_status_terms|minimal';
  $ds_fieldsetting->entity_type = 'taxonomy_term';
  $ds_fieldsetting->bundle = 'task_status_terms';
  $ds_fieldsetting->view_mode = 'minimal';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['taxonomy_term|task_status_terms|minimal'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'taxonomy_term|task_type_terms|minimal';
  $ds_fieldsetting->entity_type = 'taxonomy_term';
  $ds_fieldsetting->bundle = 'task_type_terms';
  $ds_fieldsetting->view_mode = 'minimal';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['taxonomy_term|task_type_terms|minimal'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_custom_fields_info().
 */
function erpal_project_ui_ds_custom_fields_info() {
  $export = array();

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'budget_usage';
  $ds_field->label = 'Budget usage';
  $ds_field->field_type = 3;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->properties = array();
  $export['budget_usage'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'task_customer_node';
  $ds_field->label = 'Task customer node';
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
  $export['task_customer_node'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'task_title';
  $ds_field->label = 'Task title';
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
  $export['task_title'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'time_used';
  $ds_field->label = 'time used';
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
  $export['time_used'] = $ds_field;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function erpal_project_ui_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|erpal_project|form';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'erpal_project';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'erpal_forms';
  $ds_layout->settings = array(
    'hide_empty_regions' => 0,
    'hide_sidebars' => FALSE,
    'regions' => array(
      'left' => array(
        0 => 'title',
        1 => 'body',
        2 => 'field_asset_files',
      ),
      'right' => array(
        0 => 'field_customer_ref',
        1 => 'field_project_tags',
        2 => 'field_project_status_term',
        3 => 'field_priority_term',
        4 => 'field_pricing',
      ),
      'advancedleft' => array(
        0 => 'field_project_team',
        1 => 'field_depends_on_tasks',
        2 => 'path',
        3 => 'field_project_contacts',
        4 => 'field_activity_ref',
        5 => 'group_urls',
        6 => 'field_repository_url',
        7 => 'field_commit_deeplink_url',
        8 => 'field_development_url',
        9 => 'field_stage_url',
        10 => 'field_live_url',
      ),
      'advancedright' => array(
        0 => 'field_estimated_time',
        1 => 'field_books_ref',
        2 => 'field_date',
      ),
      'hidden' => array(
        0 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'title' => 'left',
      'body' => 'left',
      'field_asset_files' => 'left',
      'field_customer_ref' => 'right',
      'field_project_tags' => 'right',
      'field_project_status_term' => 'right',
      'field_priority_term' => 'right',
      'field_pricing' => 'right',
      'field_project_team' => 'advancedleft',
      'field_depends_on_tasks' => 'advancedleft',
      'path' => 'advancedleft',
      'field_project_contacts' => 'advancedleft',
      'field_activity_ref' => 'advancedleft',
      'group_urls' => 'advancedleft',
      'field_estimated_time' => 'advancedright',
      'field_books_ref' => 'advancedright',
      'field_date' => 'advancedright',
      'field_repository_url' => 'advancedleft',
      'field_commit_deeplink_url' => 'advancedleft',
      'field_development_url' => 'advancedleft',
      'field_stage_url' => 'advancedleft',
      'field_live_url' => 'advancedleft',
      '_add_existing_field' => 'hidden',
    ),
    'classes' => array(),
  );
  $export['node|erpal_project|form'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|erpal_project|full';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'erpal_project';
  $ds_layout->view_mode = 'full';
  $ds_layout->layout = 'ds_2col';
  $ds_layout->settings = array(
    'hide_empty_regions' => 0,
    'hide_sidebars' => 0,
    'regions' => array(
      'left' => array(
        0 => 'title',
        1 => 'author',
        2 => 'post_date',
        3 => 'field_project_tags',
        4 => 'field_project_status_term',
        5 => 'field_date',
        6 => 'budget_usage',
      ),
      'right' => array(
        0 => 'field_customer_ref',
        1 => 'field_project_contacts',
        2 => 'field_activity_ref',
        3 => 'body',
        4 => 'field_asset_files',
      ),
    ),
    'fields' => array(
      'title' => 'left',
      'author' => 'left',
      'post_date' => 'left',
      'field_project_tags' => 'left',
      'field_project_status_term' => 'left',
      'field_date' => 'left',
      'budget_usage' => 'left',
      'field_customer_ref' => 'right',
      'field_project_contacts' => 'right',
      'field_activity_ref' => 'right',
      'body' => 'right',
      'field_asset_files' => 'right',
    ),
    'classes' => array(),
  );
  $export['node|erpal_project|full'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|erpal_task|form';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'erpal_task';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'erpal_forms';
  $ds_layout->settings = array(
    'hide_empty_regions' => 0,
    'hide_sidebars' => FALSE,
    'regions' => array(
      'left' => array(
        0 => 'field_date',
        1 => 'field_estimated_time',
        2 => 'title',
        3 => 'field_is_ticket',
        4 => 'group_task_time_group',
        5 => 'body',
        6 => 'field_asset_files',
      ),
      'right' => array(
        0 => 'field_project_ref',
        1 => 'field_project_tags',
        2 => 'field_task_status_term',
        3 => 'field_priority_term',
        4 => 'field_task_type_term',
        5 => 'field_task_assigned_users',
        6 => 'field_pricing',
      ),
      'advancedleft' => array(
        0 => 'field_parent',
        1 => 'field_progress_percent',
        2 => 'field_task_exclude_from',
        3 => 'path',
        4 => 'field_timetracking_button',
        5 => 'field_weight',
        6 => 'field_depends_on_tasks',
      ),
      'hidden' => array(
        0 => 'group_group',
        1 => 'field_release_ref',
        2 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'field_date' => 'left',
      'field_estimated_time' => 'left',
      'title' => 'left',
      'field_is_ticket' => 'left',
      'group_task_time_group' => 'left',
      'body' => 'left',
      'field_asset_files' => 'left',
      'field_project_ref' => 'right',
      'field_project_tags' => 'right',
      'field_task_status_term' => 'right',
      'field_priority_term' => 'right',
      'field_task_type_term' => 'right',
      'field_task_assigned_users' => 'right',
      'field_pricing' => 'right',
      'field_parent' => 'advancedleft',
      'field_progress_percent' => 'advancedleft',
      'field_task_exclude_from' => 'advancedleft',
      'path' => 'advancedleft',
      'field_timetracking_button' => 'advancedleft',
      'field_weight' => 'advancedleft',
      'field_depends_on_tasks' => 'advancedleft',
      'group_group' => 'hidden',
      'field_release_ref' => 'hidden',
      '_add_existing_field' => 'hidden',
    ),
    'classes' => array(),
  );
  $export['node|erpal_task|form'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|erpal_task|full';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'erpal_task';
  $ds_layout->view_mode = 'full';
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'hide_empty_regions' => 0,
    'hide_sidebars' => 0,
    'regions' => array(
      'header' => array(
        0 => 'links',
        1 => 'post_date',
        2 => 'author',
        3 => 'body',
        4 => 'field_asset_files',
        5 => 'field_project_tags',
        6 => 'field_task_type_term',
        7 => 'field_task_status_term',
      ),
      'left' => array(
        0 => 'budget_usage',
        1 => 'field_date',
        2 => 'field_task_assigned_users',
        3 => 'field_parent',
        4 => 'field_task_exclude_from',
      ),
      'right' => array(
        0 => 'field_estimated_time',
        1 => 'field_project_ref',
        2 => 'field_progress_percent',
      ),
    ),
    'fields' => array(
      'links' => 'header',
      'post_date' => 'header',
      'author' => 'header',
      'body' => 'header',
      'field_asset_files' => 'header',
      'field_project_tags' => 'header',
      'field_task_type_term' => 'header',
      'field_task_status_term' => 'header',
      'budget_usage' => 'left',
      'field_date' => 'left',
      'field_task_assigned_users' => 'left',
      'field_parent' => 'left',
      'field_task_exclude_from' => 'left',
      'field_estimated_time' => 'right',
      'field_project_ref' => 'right',
      'field_progress_percent' => 'right',
    ),
    'classes' => array(),
  );
  $export['node|erpal_task|full'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|erpal_task|in_activity';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'erpal_task';
  $ds_layout->view_mode = 'in_activity';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'hide_empty_regions' => 1,
    'hide_sidebars' => 1,
    'regions' => array(
      'ds_content' => array(
        0 => 'field_timetracking_button',
        1 => 'field_project_tags',
      ),
    ),
    'fields' => array(
      'field_timetracking_button' => 'ds_content',
      'field_project_tags' => 'ds_content',
    ),
    'classes' => array(),
  );
  $export['node|erpal_task|in_activity'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|erpal_task|minimal';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'erpal_task';
  $ds_layout->view_mode = 'minimal';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'hide_empty_regions' => 1,
    'hide_sidebars' => 1,
    'regions' => array(
      'ds_content' => array(
        0 => 'field_task_status_term',
        1 => 'title',
      ),
    ),
    'fields' => array(
      'field_task_status_term' => 'ds_content',
      'title' => 'ds_content',
    ),
    'classes' => array(),
  );
  $export['node|erpal_task|minimal'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|erpal_task|view_row_details';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'erpal_task';
  $ds_layout->view_mode = 'view_row_details';
  $ds_layout->layout = 'panels-erpal_task_view_row_layout';
  $ds_layout->settings = array(
    'hide_empty_regions' => 0,
    'hide_sidebars' => 0,
    'regions' => array(
      'sidebar_first_left' => array(
        0 => 'task_title',
      ),
      'sidebar_first_right' => array(
        0 => 'field_project_ref',
        1 => 'task_customer_node',
        2 => 'field_project_tags',
      ),
      'sidebar_second_left' => array(
        0 => 'field_parent',
        1 => 'group_submitted_information',
        2 => 'group_time_information',
        3 => 'field_date',
        4 => 'group_status_information',
        5 => 'field_estimated_time',
        6 => 'field_task_assigned_users',
        7 => 'field_progress_percent',
        8 => 'field_task_status_term',
        9 => 'author',
        10 => 'field_priority_term',
        11 => 'post_date',
      ),
      'sidebar_second_right' => array(
        0 => 'body',
      ),
      'sidebar_third_left' => array(
        0 => 'field_pricing',
      ),
      'sidebar_third_right' => array(
        0 => 'files_count',
        1 => 'comment_count',
      ),
    ),
    'fields' => array(
      'task_title' => 'sidebar_first_left',
      'field_project_ref' => 'sidebar_first_right',
      'task_customer_node' => 'sidebar_first_right',
      'field_project_tags' => 'sidebar_first_right',
      'field_parent' => 'sidebar_second_left',
      'group_submitted_information' => 'sidebar_second_left',
      'group_time_information' => 'sidebar_second_left',
      'field_date' => 'sidebar_second_left',
      'group_status_information' => 'sidebar_second_left',
      'field_estimated_time' => 'sidebar_second_left',
      'field_task_assigned_users' => 'sidebar_second_left',
      'field_progress_percent' => 'sidebar_second_left',
      'field_task_status_term' => 'sidebar_second_left',
      'body' => 'sidebar_second_right',
      'author' => 'sidebar_second_left',
      'field_priority_term' => 'sidebar_second_left',
      'field_pricing' => 'sidebar_third_left',
      'files_count' => 'sidebar_third_right',
      'post_date' => 'sidebar_second_left',
      'comment_count' => 'sidebar_third_right',
    ),
    'classes' => array(),
  );
  $export['node|erpal_task|view_row_details'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'taxonomy_term|priority_terms|default';
  $ds_layout->entity_type = 'taxonomy_term';
  $ds_layout->bundle = 'priority_terms';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'hide_empty_regions' => 1,
    'hide_sidebars' => 1,
    'regions' => array(
      'ds_content' => array(
        0 => 'field_is_default_term',
        1 => 'description',
        2 => 'field_term_image',
      ),
    ),
    'fields' => array(
      'field_is_default_term' => 'ds_content',
      'description' => 'ds_content',
      'field_term_image' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(),
    'layout_wrapper' => 'div',
  );
  $export['taxonomy_term|priority_terms|default'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'taxonomy_term|priority_terms|minimal';
  $ds_layout->entity_type = 'taxonomy_term';
  $ds_layout->bundle = 'priority_terms';
  $ds_layout->view_mode = 'minimal';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'hide_empty_regions' => 1,
    'hide_sidebars' => 1,
    'regions' => array(
      'ds_content' => array(
        0 => 'field_term_image',
        1 => 'title',
      ),
    ),
    'fields' => array(
      'field_term_image' => 'ds_content',
      'title' => 'ds_content',
    ),
    'classes' => array(),
  );
  $export['taxonomy_term|priority_terms|minimal'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'taxonomy_term|task_status_terms|default';
  $ds_layout->entity_type = 'taxonomy_term';
  $ds_layout->bundle = 'task_status_terms';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'hide_empty_regions' => 1,
    'hide_sidebars' => 1,
    'regions' => array(
      'ds_content' => array(
        0 => 'field_term_image',
        1 => 'title',
      ),
    ),
    'fields' => array(
      'field_term_image' => 'ds_content',
      'title' => 'ds_content',
    ),
    'classes' => array(),
  );
  $export['taxonomy_term|task_status_terms|default'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'taxonomy_term|task_status_terms|in_pane';
  $ds_layout->entity_type = 'taxonomy_term';
  $ds_layout->bundle = 'task_status_terms';
  $ds_layout->view_mode = 'in_pane';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'hide_empty_regions' => 1,
    'hide_sidebars' => 1,
    'regions' => array(
      'ds_content' => array(
        0 => 'title',
        1 => 'field_term_image',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'field_term_image' => 'ds_content',
    ),
    'classes' => array(),
  );
  $export['taxonomy_term|task_status_terms|in_pane'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'taxonomy_term|task_status_terms|minimal';
  $ds_layout->entity_type = 'taxonomy_term';
  $ds_layout->bundle = 'task_status_terms';
  $ds_layout->view_mode = 'minimal';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'hide_empty_regions' => 1,
    'hide_sidebars' => 1,
    'regions' => array(
      'ds_content' => array(
        0 => 'field_term_image',
        1 => 'title',
      ),
    ),
    'fields' => array(
      'field_term_image' => 'ds_content',
      'title' => 'ds_content',
    ),
    'classes' => array(),
  );
  $export['taxonomy_term|task_status_terms|minimal'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'taxonomy_term|task_status_terms|visual';
  $ds_layout->entity_type = 'taxonomy_term';
  $ds_layout->bundle = 'task_status_terms';
  $ds_layout->view_mode = 'visual';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'hide_empty_regions' => 1,
    'hide_sidebars' => 1,
    'regions' => array(
      'ds_content' => array(
        0 => 'field_term_image',
      ),
    ),
    'fields' => array(
      'field_term_image' => 'ds_content',
    ),
    'classes' => array(),
  );
  $export['taxonomy_term|task_status_terms|visual'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'taxonomy_term|task_type_terms|default';
  $ds_layout->entity_type = 'taxonomy_term';
  $ds_layout->bundle = 'task_type_terms';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'hide_empty_regions' => 1,
    'hide_sidebars' => 1,
    'regions' => array(
      'ds_content' => array(
        0 => 'field_is_default_term',
        1 => 'description',
        2 => 'field_term_image',
      ),
    ),
    'fields' => array(
      'field_is_default_term' => 'ds_content',
      'description' => 'ds_content',
      'field_term_image' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(),
    'layout_wrapper' => 'div',
  );
  $export['taxonomy_term|task_type_terms|default'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'taxonomy_term|task_type_terms|minimal';
  $ds_layout->entity_type = 'taxonomy_term';
  $ds_layout->bundle = 'task_type_terms';
  $ds_layout->view_mode = 'minimal';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'hide_empty_regions' => 1,
    'hide_sidebars' => 1,
    'regions' => array(
      'ds_content' => array(
        0 => 'field_term_image',
        1 => 'title',
      ),
    ),
    'fields' => array(
      'field_term_image' => 'ds_content',
      'title' => 'ds_content',
    ),
    'classes' => array(),
  );
  $export['taxonomy_term|task_type_terms|minimal'] = $ds_layout;

  return $export;
}
