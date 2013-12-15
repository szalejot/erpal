<?php
/**
 * @file
 * erpal_project.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function erpal_project_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: field_base
  $overrides["field_base.field_parent.settings|handler_settings|target_bundles|erpal_project"] = 'erpal_project';
  $overrides["field_base.field_parent.settings|handler_settings|target_bundles|erpal_task"] = 'erpal_task';

 return $overrides;
}
