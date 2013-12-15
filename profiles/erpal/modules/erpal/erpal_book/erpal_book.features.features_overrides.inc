<?php
/**
 * @file
 * erpal_book.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function erpal_book_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: field_base
  $overrides["field_base.field_parent.settings|handler_settings|target_bundles|erpal_book"] = 'erpal_book';
  $overrides["field_base.field_parent.settings|handler_settings|target_bundles|erpal_book_page"] = 'erpal_book_page';

 return $overrides;
}
