<?php
/**
 * @file
 * erpal_invoice_ui.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function erpal_invoice_ui_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|erpal_invoice|form';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'erpal_invoice';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'erpal_forms';
  $ds_layout->settings = array(
    'hide_empty_regions' => 0,
    'hide_sidebars' => FALSE,
    'regions' => array(
      'left' => array(
        0 => 'field_contractor_ref',
        1 => 'field_customer_ref',
        2 => 'field_invoice_address_id',
        3 => 'field_shipping_address_id',
        4 => 'field_billables_ref',
      ),
      'hidden' => array(
        0 => 'title',
        1 => 'path',
        2 => 'field_invoice_total',
        3 => 'field_invoice_vat',
        4 => 'field_auto_note',
        5 => 'field_price_no_vat',
        6 => 'field_payment_date',
        7 => 'group_invoice_addresses',
        8 => '_add_existing_field',
        9 => 'group_invoice_sonstiges',
      ),
      'right' => array(
        0 => 'field_invoice_number',
        1 => 'field_invoice_date',
        2 => 'group_order_numbers',
        3 => 'field_order_number_extern',
        4 => 'field_credit_period',
        5 => 'field_order_number_intern',
        6 => 'field_payed',
      ),
      'advancedleft' => array(
        0 => 'field_skonto',
        1 => 'field_currency',
        2 => 'field_asset_files',
        3 => 'field_note',
        4 => 'group_notes',
        5 => 'field_invoice_exported',
      ),
    ),
    'fields' => array(
      'field_contractor_ref' => 'left',
      'field_customer_ref' => 'left',
      'field_invoice_address_id' => 'left',
      'field_shipping_address_id' => 'left',
      'title' => 'hidden',
      'field_billables_ref' => 'left',
      'path' => 'hidden',
      'field_invoice_total' => 'hidden',
      'field_invoice_number' => 'right',
      'field_invoice_date' => 'right',
      'field_invoice_vat' => 'hidden',
      'group_order_numbers' => 'right',
      'field_order_number_extern' => 'right',
      'field_auto_note' => 'hidden',
      'field_credit_period' => 'right',
      'field_order_number_intern' => 'right',
      'field_price_no_vat' => 'hidden',
      'field_payed' => 'right',
      'field_payment_date' => 'hidden',
      'field_skonto' => 'advancedleft',
      'field_currency' => 'advancedleft',
      'field_asset_files' => 'advancedleft',
      'field_note' => 'advancedleft',
      'group_notes' => 'advancedleft',
      'field_invoice_exported' => 'advancedleft',
      'group_invoice_addresses' => 'hidden',
      '_add_existing_field' => 'hidden',
      'group_invoice_sonstiges' => 'hidden',
    ),
    'classes' => array(),
  );
  $export['node|erpal_invoice|form'] = $ds_layout;

  return $export;
}
