<?php

// /**
 // * Plugin to export as html
 // */
// $plugin = array(
  // 'type' => 'Html',
  // 'handler' => array(
    // 'class' => 'document_html_export',
  // ),
// );
 
  
class document_html_export extends document_export {
  function __construct($options){
    parent::__construct($options);
    
    $this->document = $this->create_document($options);  
    
  }
  private function create_document($options){
    // dpm($options);
    
  }
  
  public function save($uri, $filename){
    // save the document to the disk
  }
  
  public function stream($filename){
    // stream the document to the user and die()
  }
}
