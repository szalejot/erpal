<?php

// /**
 // * Plugin to export as pdf
 // */
// $plugin = array(
  // 'type' => 'Pdf',
  // 'handler' => array(
    // 'class' => 'document_pdf_export',
  // ),
// );
 
 
 
  
class document_pdf_export extends document_export {
  public function save($uri, $filename){
    // save the document to the disk
  }
  
  public function stream($filename){
    // stream the document to the user and die()
  }
}
