<?php
/**
 * @file
 * erpal_calendar_ui.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function erpal_calendar_ui_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-erpal-menu:calendar
  $menu_links['menu-erpal-menu:calendar'] = array(
    'menu_name' => 'menu-erpal-menu',
    'link_path' => 'calendar',
    'router_path' => 'calendar',
    'link_title' => 'Calendar',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => 'erpal_menu_calendar',
        'class' => 'calendar',
        'style' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -44,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Calendar');


  return $menu_links;
}
