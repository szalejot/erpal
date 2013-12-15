<?php

/**
* Returns all the menu path for config of book feature
*/
function _erpal_book_helper_config_menu(){
  
  $items['admin/erpal/book'] = array(
    'title' => 'ERPAL Book',
    'page callback' => '_erpal_book_helper_config_basic',    
    'access arguments' => array('config erpal book'),
    'file' => 'inc/config.inc',
    'type' => MENU_LOCAL_TASK,
  );
  
  return $items;
}

/**
* Settings for the ERPAL book Feature
*/
function _erpal_book_helper_config_basic(){
  $form = drupal_get_form('erpal_book_helper_config_form');
  return $form;
}

/**
* Form to show all settings to configure ERPAL book feature
*/
function erpal_book_helper_config_form($form, &$form_state){
    
  $allowed_extensions = array('png', 'jpg', 'jpeg', 'gif');
  $form = array();
  
  $form['frontpage'] = array(
    '#type' => 'fieldset',
    '#title' => t('Settings for the document frontpage'),
    
  );
  
  $frontpage_logo_fid = variable_get('erpal_book_helper_frontpage_logo', false);  
  $frontpage_logo_file = ($frontpage_logo_fid) ? file_load($frontpage_logo_fid) : FALSE;
  
  $form['frontpage']['frontpage_logo'] = array(
    '#type' => 'managed_file',
    '#title' => t('Logo for the frontpage'),
    '#description' => t('Upload your logo that will be used at the frontpage of your document exports. Allowed file extensions: !extensions', array('!extensions' => implode(',', $allowed_extensions))),
    '#upload_validators' => array('file_validate_extensions' => array(implode(' ', $allowed_extensions))),
    '#upload_location' => _erpal_book_helper_logo_documents_upload_dir(),
    '#default_value' => $frontpage_logo_file ? $frontpage_logo_file->fid : false,
  );
  
  
  $form['overwrite'] = array(
    '#type' => 'checkbox',
    '#title' => t('Overwrite document logo and footer from ERPAL BASIC settings'),
    '#default_value' => variable_get('erpal_book_helper_overwrite_logo_and_footer', FALSE),
  );
  
  $form['header_footer'] = array(
    '#type' => 'fieldset',
    '#title' => t('Custom header and footer for book export:'),
    '#states' => array(
      // Hide the settings when the cancel notify checkbox is disabled.
      'invisible' => array(
       ':input[name="overwrite"]' => array('checked' => FALSE),
      ),
    ),
  );
  
  $document_fid = variable_get('erpal_book_helper_document_logo', false);  
  $file = ($document_fid) ? file_load($document_fid) : FALSE;
 
  $form['header_footer']['company_logo_document'] = array(
    
    '#type' => 'managed_file',
    '#title' => t('Company logo for documents'),
    '#description' => t('Upload your logo that will be used in documents. Allowed file extensions: !extensions', array('!extensions' => implode(',', $allowed_extensions))),
    '#upload_validators' => array('file_validate_extensions' => array(implode(' ', $allowed_extensions))),
    '#upload_location' => _erpal_book_helper_logo_documents_upload_dir(),
    '#default_value' => $file ? $file->fid : false,
  ); 
  
  $form['header_footer']['document_footer'] = array(

    '#type' => 'textarea',
    '#title' => t('Document footer'),
    '#description' => t('This html will be displayed as a footer in your documents'), 
    '#default_value' => variable_get('erpal_book_helper_document_footer', ' '),
  );
  
  $types = array('erpal_basic');
  $tokens = theme('token_tree', array('global_types' => FALSE, 'token_types' => $types));
  $form['header_footer']['document_footer']['#suffix'] = $tokens;
  
  $form['submit'] = array(
    '#value' => t('Save'),
    '#type' => 'submit',
  );

  return $form;
}

/**
* submit handler of erpal book config form
*/
function erpal_book_helper_config_form_submit($form, $form_state){

  $values = $form_state['values'];
  variable_set('erpal_book_helper_overwrite_logo_and_footer', $values['overwrite']);
  
  $document_fid = $values['company_logo_document'];
  variable_set('erpal_book_helper_document_logo', $document_fid);
  if ($document_fid){  
    //finalise the file!
    $file = file_load($document_fid);
    $file->status = FILE_STATUS_PERMANENT;
    file_save($file);
    file_usage_add($file, 'erpal_book_helper', 'config', $file->fid); 
  }
  
  $frontpage_logo_fid = $values['frontpage_logo'];
  variable_set('erpal_book_helper_frontpage_logo', $frontpage_logo_fid);
  if ($frontpage_logo_fid){  
    //finalise the file!
    $file = file_load($frontpage_logo_fid);
    $file->status = FILE_STATUS_PERMANENT;
    file_save($file);
    file_usage_add($file, 'erpal_book_helper', 'config', $file->fid); 
  }
  
  //save document footer  
  $document_footer = $values['document_footer'];
  variable_set('erpal_book_helper_document_footer', $document_footer);
    
}

function _erpal_book_helper_logo_documents_upload_dir(){
  
  $uri = "public://erpal_res";
  
  //prepare the folder
  file_prepare_directory($uri,  FILE_CREATE_DIRECTORY);
  return $uri;
}
