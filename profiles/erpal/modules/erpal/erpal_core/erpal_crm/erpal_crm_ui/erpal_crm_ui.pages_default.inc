<?php
/**
 * @file
 * erpal_crm_ui.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_handlers().
 */
function erpal_crm_ui_default_page_manager_handlers() {
  $export = array();

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view_panel_context_3';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = 2;
  $handler->conf = array(
    'title' => 'Contact Node Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'erpal_contact' => 'erpal_contact',
            ),
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'erpal_content_layout';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'left' => NULL,
      'right' => NULL,
      'middle' => NULL,
      'top' => NULL,
      'bottom' => NULL,
      'sidebar_first_left' => NULL,
      'sidebar_first_right' => NULL,
      'sidebar_second_left' => NULL,
      'sidebar_second_right' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '%node:title';
  $display->uuid = '84eb2c44-660d-8224-31c9-1210f69b6f89';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-201c69ab-2512-2d54-1980-f42ae24eb63a';
    $pane->panel = 'sidebar_first_right';
    $pane->type = 'page_actions';
    $pane->subtype = 'page_actions';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '201c69ab-2512-2d54-1980-f42ae24eb63a';
    $display->content['new-201c69ab-2512-2d54-1980-f42ae24eb63a'] = $pane;
    $display->panels['sidebar_first_right'][0] = 'new-201c69ab-2512-2d54-1980-f42ae24eb63a';
    $pane = new stdClass();
    $pane->pid = 'new-da2aa584-b15e-dd74-5942-fa7506ec8adf';
    $pane->panel = 'sidebar_second_left';
    $pane->type = 'block';
    $pane->subtype = 'quicktabs-contact_content_tabs';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '<none>',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'da2aa584-b15e-dd74-5942-fa7506ec8adf';
    $display->content['new-da2aa584-b15e-dd74-5942-fa7506ec8adf'] = $pane;
    $display->panels['sidebar_second_left'][0] = 'new-da2aa584-b15e-dd74-5942-fa7506ec8adf';
    $pane = new stdClass();
    $pane->pid = 'new-83f6c9c9-993b-0b34-b16f-6b9a21efa2dd';
    $pane->panel = 'sidebar_second_right';
    $pane->type = 'custom_node_content';
    $pane->subtype = 'custom_node_content';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'types' => array(),
      'field_name' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '83f6c9c9-993b-0b34-b16f-6b9a21efa2dd';
    $display->content['new-83f6c9c9-993b-0b34-b16f-6b9a21efa2dd'] = $pane;
    $display->panels['sidebar_second_right'][0] = 'new-83f6c9c9-993b-0b34-b16f-6b9a21efa2dd';
    $pane = new stdClass();
    $pane->pid = 'new-1038d58a-82a1-4b04-e51a-126df21be40f';
    $pane->panel = 'sidebar_second_right';
    $pane->type = 'panels_mini';
    $pane->subtype = 'contact_general_fields';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'argument_entity_id:node_1',
      ),
      'override_title' => 1,
      'override_title_text' => 'General',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => array(
        'pane_collapsed' => 0,
      ),
      'style' => 'collapsible',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '1038d58a-82a1-4b04-e51a-126df21be40f';
    $display->content['new-1038d58a-82a1-4b04-e51a-126df21be40f'] = $pane;
    $display->panels['sidebar_second_right'][1] = 'new-1038d58a-82a1-4b04-e51a-126df21be40f';
    $pane = new stdClass();
    $pane->pid = 'new-01e445a1-b913-ba94-79e5-0d40f0522ffd';
    $pane->panel = 'sidebar_second_right';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_contact_image';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'title',
      'formatter' => 'image',
      'delta_limit' => 0,
      'delta_offset' => '0',
      'delta_reversed' => FALSE,
      'formatter_settings' => array(
        'image_style' => 'medium',
        'image_link' => '',
      ),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 1,
      'override_title_text' => 'Image',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => array(
        'pane_collapsed' => 0,
      ),
      'style' => 'collapsible',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '01e445a1-b913-ba94-79e5-0d40f0522ffd';
    $display->content['new-01e445a1-b913-ba94-79e5-0d40f0522ffd'] = $pane;
    $display->panels['sidebar_second_right'][2] = 'new-01e445a1-b913-ba94-79e5-0d40f0522ffd';
    $pane = new stdClass();
    $pane->pid = 'new-bde3b4b9-b45f-dae4-091b-ea2bf4b5fea9';
    $pane->panel = 'sidebar_second_right';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_asset_files';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'title',
      'formatter' => 'entityreference_file_node',
      'delta_limit' => '0',
      'delta_offset' => '0',
      'delta_reversed' => 0,
      'formatter_settings' => array(
        'link' => 1,
      ),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => array(
        'pane_collapsed' => 0,
      ),
      'style' => 'collapsible',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = 'bde3b4b9-b45f-dae4-091b-ea2bf4b5fea9';
    $display->content['new-bde3b4b9-b45f-dae4-091b-ea2bf4b5fea9'] = $pane;
    $display->panels['sidebar_second_right'][3] = 'new-bde3b4b9-b45f-dae4-091b-ea2bf4b5fea9';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['node_view_panel_context_3'] = $handler;

  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'node_view_panel_context_8';
  $handler->task = 'node_view';
  $handler->subtask = '';
  $handler->handler = 'panel_context';
  $handler->weight = 7;
  $handler->conf = array(
    'title' => 'Activity Node Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'erpal_crm_activity' => 'erpal_crm_activity',
            ),
          ),
          'context' => 'argument_entity_id:node_1',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'erpal_content_layout';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'middle' => NULL,
      'top' => NULL,
      'left' => NULL,
      'right' => NULL,
      'bottom' => NULL,
      'sidebar_first_left' => NULL,
      'sidebar_first_right' => NULL,
      'sidebar_second_left' => NULL,
      'sidebar_second_right' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '%node:title';
  $display->uuid = '4af7f671-1637-da94-3120-b4e6524f6d96';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-08157855-6de5-e4f4-89a6-18d3f284e5f0';
    $pane->panel = 'sidebar_first_left';
    $pane->type = 'panels_mini';
    $pane->subtype = 'activity_status_panel';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'argument_entity_id:node_1',
      ),
      'override_title' => 1,
      'override_title_text' => '<none>',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '08157855-6de5-e4f4-89a6-18d3f284e5f0';
    $display->content['new-08157855-6de5-e4f4-89a6-18d3f284e5f0'] = $pane;
    $display->panels['sidebar_first_left'][0] = 'new-08157855-6de5-e4f4-89a6-18d3f284e5f0';
    $pane = new stdClass();
    $pane->pid = 'new-0f697b15-1538-11f4-c55b-5c65230e7ab3';
    $pane->panel = 'sidebar_first_right';
    $pane->type = 'page_actions';
    $pane->subtype = 'page_actions';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '0f697b15-1538-11f4-c55b-5c65230e7ab3';
    $display->content['new-0f697b15-1538-11f4-c55b-5c65230e7ab3'] = $pane;
    $display->panels['sidebar_first_right'][0] = 'new-0f697b15-1538-11f4-c55b-5c65230e7ab3';
    $pane = new stdClass();
    $pane->pid = 'new-2932c5e7-f507-d854-610b-95cc80d9e634';
    $pane->panel = 'sidebar_second_left';
    $pane->type = 'block';
    $pane->subtype = 'quicktabs-activity_content_tabs';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '<none>',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '2932c5e7-f507-d854-610b-95cc80d9e634';
    $display->content['new-2932c5e7-f507-d854-610b-95cc80d9e634'] = $pane;
    $display->panels['sidebar_second_left'][0] = 'new-2932c5e7-f507-d854-610b-95cc80d9e634';
    $pane = new stdClass();
    $pane->pid = 'new-4d5905a7-af24-af44-69f7-b1a575510b85';
    $pane->panel = 'sidebar_second_right';
    $pane->type = 'custom_node_content';
    $pane->subtype = 'custom_node_content';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'types' => array(),
      'field_name' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '4d5905a7-af24-af44-69f7-b1a575510b85';
    $display->content['new-4d5905a7-af24-af44-69f7-b1a575510b85'] = $pane;
    $display->panels['sidebar_second_right'][0] = 'new-4d5905a7-af24-af44-69f7-b1a575510b85';
    $pane = new stdClass();
    $pane->pid = 'new-c6491aed-2375-34b4-c9b8-3346b2639cb8';
    $pane->panel = 'sidebar_second_right';
    $pane->type = 'panels_mini';
    $pane->subtype = 'activity_general_fields';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => array(
        0 => 'argument_entity_id:node_1',
      ),
      'override_title' => 1,
      'override_title_text' => 'General',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => array(
        'pane_collapsed' => 0,
      ),
      'style' => 'collapsible',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = 'c6491aed-2375-34b4-c9b8-3346b2639cb8';
    $display->content['new-c6491aed-2375-34b4-c9b8-3346b2639cb8'] = $pane;
    $display->panels['sidebar_second_right'][1] = 'new-c6491aed-2375-34b4-c9b8-3346b2639cb8';
    $pane = new stdClass();
    $pane->pid = 'new-089cf7ac-8c9f-4364-ad7e-d147a1c21e11';
    $pane->panel = 'sidebar_second_right';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_contacts_ref';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'title',
      'formatter' => 'entityreference_entity_view',
      'delta_limit' => '0',
      'delta_offset' => '0',
      'delta_reversed' => 0,
      'formatter_settings' => array(
        'link' => 1,
        'view_mode' => 'in_activity',
        'links' => 1,
      ),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => array(
        'pane_collapsed' => 0,
      ),
      'style' => 'collapsible',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = '089cf7ac-8c9f-4364-ad7e-d147a1c21e11';
    $display->content['new-089cf7ac-8c9f-4364-ad7e-d147a1c21e11'] = $pane;
    $display->panels['sidebar_second_right'][2] = 'new-089cf7ac-8c9f-4364-ad7e-d147a1c21e11';
    $pane = new stdClass();
    $pane->pid = 'new-1a81ef59-4f4a-3a84-7964-d55a19de48ad';
    $pane->panel = 'sidebar_second_right';
    $pane->type = 'views_panes';
    $pane->subtype = 'projects-panel_pane_1';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => array(
        'pane_collapsed' => 0,
      ),
      'style' => 'collapsible',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = '1a81ef59-4f4a-3a84-7964-d55a19de48ad';
    $display->content['new-1a81ef59-4f4a-3a84-7964-d55a19de48ad'] = $pane;
    $display->panels['sidebar_second_right'][3] = 'new-1a81ef59-4f4a-3a84-7964-d55a19de48ad';
    $pane = new stdClass();
    $pane->pid = 'new-b7cc9cc7-d02b-f884-5d6f-7c65409cee7d';
    $pane->panel = 'sidebar_second_right';
    $pane->type = 'entity_field';
    $pane->subtype = 'node:field_asset_files';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'label' => 'title',
      'formatter' => 'entityreference_file_node',
      'delta_limit' => '0',
      'delta_offset' => '0',
      'delta_reversed' => 0,
      'formatter_settings' => array(
        'link' => 1,
      ),
      'context' => 'argument_entity_id:node_1',
      'override_title' => 1,
      'override_title_text' => 'Documents',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => array(
        'pane_collapsed' => 0,
      ),
      'style' => 'collapsible',
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 4;
    $pane->locks = array();
    $pane->uuid = 'b7cc9cc7-d02b-f884-5d6f-7c65409cee7d';
    $display->content['new-b7cc9cc7-d02b-f884-5d6f-7c65409cee7d'] = $pane;
    $display->panels['sidebar_second_right'][4] = 'new-b7cc9cc7-d02b-f884-5d6f-7c65409cee7d';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $export['node_view_panel_context_8'] = $handler;

  return $export;
}

/**
 * Implements hook_default_page_manager_pages().
 */
function erpal_crm_ui_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'crm';
  $page->task = 'page';
  $page->admin_title = 'Activities';
  $page->admin_description = '';
  $page->path = 'activities';
  $page->access = array(
    'plugins' => array(
      0 => array(
        'name' => 'perm',
        'settings' => array(
          'perm' => 'access activities view',
        ),
        'context' => 'logged-in-user',
        'not' => FALSE,
      ),
    ),
    'logic' => 'and',
  );
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_crm_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'crm';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'CRM Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
    'access' => array(
      'logic' => 'and',
    ),
  );
  $display = new panels_display();
  $display->layout = 'erpal_content_layout';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'top' => NULL,
      'left' => NULL,
      'right' => NULL,
      'bottom' => NULL,
      'sidebar_first_left' => NULL,
      'sidebar_first_right' => NULL,
      'sidebar_second_left' => NULL,
      'sidebar_second_right' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = 'Activities';
  $display->uuid = '81b143a2-b8be-3da4-89b9-e2f6643ceac7';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-cc397cb5-ea74-4df4-f925-c30c03741c41';
    $pane->panel = 'sidebar_first_right';
    $pane->type = 'page_actions';
    $pane->subtype = 'page_actions';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'cc397cb5-ea74-4df4-f925-c30c03741c41';
    $display->content['new-cc397cb5-ea74-4df4-f925-c30c03741c41'] = $pane;
    $display->panels['sidebar_first_right'][0] = 'new-cc397cb5-ea74-4df4-f925-c30c03741c41';
    $pane = new stdClass();
    $pane->pid = 'new-33f0cbce-1c39-77d4-31d4-d9749804da0c';
    $pane->panel = 'sidebar_second_left';
    $pane->type = 'block';
    $pane->subtype = 'quicktabs-all_activities_tabs';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '<none>',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '33f0cbce-1c39-77d4-31d4-d9749804da0c';
    $display->content['new-33f0cbce-1c39-77d4-31d4-d9749804da0c'] = $pane;
    $display->panels['sidebar_second_left'][0] = 'new-33f0cbce-1c39-77d4-31d4-d9749804da0c';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['crm'] = $page;

  return $pages;

}
