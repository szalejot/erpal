<?php

define('MAX_PAGE_WIDTH', 570);



/**
 * Plugin to export as docx
 */
$plugin = array(
  'type' => 'Text-Document',
  'handler' => array(
    'class' => 'document_ooxml_export',
  ),
);
  
class document_ooxml_export extends document_export {
  
  /**
   * Constructor of the OOXML Exporter
   * Calls parent:__contruct, includes the htmltodocx libraries and then 
   * created the document.
   * @param $options
   *  an associative array with the following keys:
   *  - pages: (optional) An array with rendered html pages or a single
   *   string with a single rendered page
   *  - header: (optional) A string with rendered html for the header
   *  - footer: (optional) A string with rendered html for the footer   
   *  - frontpage: (optional) A string with rendered html for the frontpage
   *  - toc: (optional) Boolean if a Table of content should be attached to the document
   */
  function __construct($options){
    parent::__construct($options);
    if($this->require_htmltodocx()){ 
      $this->document = $this->create_document($options);  
    } else {
      throw new Exception("Error loading the htmltodocx libraries");
    }
  }
	
	/**
	 * Extension of file which generate this plugin.
	 */
	public function fileExtension(){
  	return 'docx';
  }

  /**
   * Saves the document to the disk and creates a file entity
   * @param $uri
   *   String with filepath to save the file
   * @param $filename
   *   String with filename to save the file with
   * @return
   *   stdClass FileApi file object
   */
  public function save($uri, $filename){
    if($this->require_htmltodocx()){
      	global $user;
    
	    $filepath = drupal_realpath($uri.$filename);
	    $filepath = file_destination($filepath, FILE_EXISTS_RENAME);
	    
	    $obj_writer = PHPWord_IOFactory::createWriter($this->document, 'Word2007');
	    $obj_writer->save($filepath);
	    
	    
	    // Begin building file object.
	    $file = new stdClass();
	    $file->uid      = $user->uid;
	    $file->status   = 1; //final!
	    $file->filename = $filename;
	    $file->uri      = $uri.basename($filepath);
	    $file->filemime = file_get_mimetype($filepath);
	    $file->filesize = filesize($filepath);   
	    file_save($file);
	    return $file;  	
	
    } else {
    	return false;
    }
      
  }
  
  /**
   * Streams the file to the browser as an OfficeOpenXML document
   * @param $filename
   *   String with filename of the document
   */
  public function stream($filename){
  	if($this->require_htmltodocx()){
  		$temp_file = tempnam(sys_get_temp_dir(), 'PHPWord');
	    $obj_writer = PHPWord_IOFactory::createWriter($this->document, 'Word2007');
	    $obj_writer->save($temp_file);
	    $this->stream_file($filename, $temp_file, 'application/vnd.openxmlformats-officedocument.wordprocessingml.document');
  	}else{
  		return FALSE;
  	}
    
  }
  
  /**
   * Builds up the document and saves it to $this->document
   */
  private function create_document($options){
    //Create a new OOXML Document and add a new Section  
    $phpword_object = new PHPWord();
    $section = $phpword_object->createSection();
    
    //Create configuration array for htmltodocx    
    $domain = (isset($GLOBALS['base_url']))
        ? $GLOBALS['base_url']
        : '';  
    // Settings 
    $settings = array(
      // Required parameters:
      'phpword_object' => &$phpword_object,
      'base_root' => $domain,
      'base_path' => '',
      
      // Optional parameters - showing the defaults if you don't set anything:
      'current_style' => array('size' => '11'), 
      'parents' => array(0 => 'body'),
      'list_depth' => 0,
      'context' => 'section',
      'pseudo_list' => TRUE, 
      'pseudo_list_indicator_font_name' => 'Verdana',
      'pseudo_list_indicator_font_size' => '10',
      'pseudo_list_indicator_character' => ' • ',
      'table_allowed' => TRUE,        
      'style_sheet' => $this->get_style(),
    );
    
    
    // Add frontpage if set
    if(isset($options['frontpage']) && $options['frontpage']){
      
      $html_dom = $this->prepare_page($options['frontpage'], $settings);
      $str = $html_dom;
      $html_dom_array = $html_dom->find('html', 0)->children();
      htmltodocx_insert_html($section, $html_dom_array[0]->nodes, $settings);
      $html_dom->clear();
      unset($html_dom);
      
      $section = $phpword_object->createSection(); 
    }
    
    
   
    if(isset($options['toc']) && ($options['toc'] == TRUE)){
      $settings += array(
        'structure_document' => TRUE, 
        'table_of_contents_id' => erpal_document_export_get_toc_id(),
      );
      $toc = '<h1>Table of contents:</h1><div id="'.erpal_document_export_get_toc_id().'"></div>';
      
      $html_dom = $this->prepare_page($toc, $settings);
      $html_dom_array = $html_dom->find('html', 0)->children();
      htmltodocx_insert_html($section, $html_dom_array[0]->nodes, $settings);
      $section->addPageBreak();
      $html_dom->clear();
      unset($html_dom); 
    } 
    

    
       
    // Set Footer if set
    if(isset($this->footer)){
      $new_settings = $settings;
      
      $new_settings['style_sheet']['elements']['table'] = array (
        'border' => 'none',
      );
      $new_settings['style_sheet']['elements']['th'] = array (
        'border' => 'none',
      );
      $new_settings['style_sheet']['elements']['td'] = array (
        'border' => 'none',
      );
      
      $new_settings['style_sheet']['default'] = array (
        'size' => 7,
        'name' => 'Verdana',
      );
      
      $new_settings['current_style'] = array('size' => '7');
      
      $footer = $section->createFooter();
      $html_dom = $this->prepare_page($this->footer, $settings);
      $html_dom_array = $html_dom->find('html', 0)->children();
      htmltodocx_insert_html($footer, $html_dom_array[0]->nodes, $new_settings);
      $html_dom->clear();
      unset($html_dom);
    } 
    
    // Set Header if set
    if(isset($this->header)){
     
      $header = $section->createHeader();
      
      $html_dom = $this->prepare_page($this->header['html'], $settings);
                  
      $html_dom_array = $html_dom->find('html', 0)->children();
      htmltodocx_insert_html($header, $html_dom_array[0]->nodes, $settings);
      $html_dom->clear();
      unset($html_dom);
    }
    
    // Add pages 
    foreach($this->pages as $page){
      // Parse our html with simple html dom
      $html_dom = $this->prepare_page($page, $settings);
      $html_dom_array = $html_dom->find('html', 0)->children();
      htmltodocx_insert_html($section, $html_dom_array[0]->nodes, $settings);
      
      if(isset($options['page_breaks']) && ($options['page_breaks'] == TRUE))
        $section->addPageBreak();
      
      $html_dom->clear();
      unset($html_dom);  
      
    }  
        
    return $phpword_object;   
  }
  
  /**
   * Wraps data in valid html and prepares private and public image urls 
   * to work with the htmltodocx libraries
   */
  private function prepare_page($data, &$settings){
    
    $html = 
      '<html><body>'
      .$data
      .'</body></html>';
      
      
    $html_dom = new simple_html_dom();
    $html_dom->load($html);
    
    $images = $html_dom->find('img');
    foreach($images as $image){
      $url = $image->attr['src'];
      $new_url = $this->prepare_image_url($url);
      $image->attr['src'] = $new_url;
      if(isset($_SERVER['HTTP_ORIGIN']) && isset($_SERVER['DOCUMENT_ROOT'])){
          
        $image_file = str_replace($_SERVER['HTTP_ORIGIN'], $_SERVER['DOCUMENT_ROOT'], $new_url);
        $image_size = getimagesize($image_file);
				debug($image_size,'siz',TRUE);
        
        if((isset($image->attr['class']) && ($image->attr['class'] == 'auto-scale'))
            || ($image_size[0] > MAX_PAGE_WIDTH)){
          
          $resize['height'] = intval($image_size[1] * MAX_PAGE_WIDTH / $image_size[0]);
          $resize['width'] = MAX_PAGE_WIDTH;  
          
          $class_name = 'c' . md5(uniqid(rand(), TRUE));
          $image->class = $class_name;
          
          $settings['style_sheet']['classes'][$class_name] = $resize;
        }
      }
    }
    
    // foreach($images as $image){
      // $image_url = $this->prepare_image_url($image->attr['src']);
    // }
    
    // Format tables
    $tables = $html_dom->find('table');
    foreach($tables as $table){
      // if no table with is set expand to maximum size
      $table_width = isset($table->attr['width']) 
        ? $table->attr['width'] : 620;
      // make shure that the table is not bigger than the page
      if($table_width > 620) $table_width = 620;
      
      // get first row of the table
      $first_row = $table->find('tr', 0);
      if($first_row){

        // Get the columns: Look for <th> first and if not set look for <td>
        $cols = $first_row->find('th');
        if(!$cols) $cols = $first_row->find('td');
        
        if($cols){
          // get all columns and look if width is set
          $cols_width = 0;
          $remaining_cols = count($cols);
          foreach($cols as $col){
            if(isset($col->attr['width'])){
              $cols_width += $col->attr['width'];
              $remaining_cols--;
            }
          }
          // make shure that remaining cells is not 0
          if ($remaining_cols > 0) {
            // Calculate average cell space for the remaining cells
            $remaining_col_size = ($table_width - $cols_width) / $remaining_cols;
            // Set the column size for each element if no size is set
            foreach ($cols as $col) {
              if(!isset($col->attr['width'])){
                $col->attr['width'] = $remaining_col_size;
              }  
            }
          }
        }
      }
    }
    return $html_dom;
  } 

  /**
   * Replaces the link to image file that are private with stream link
   * Sets a relative filepath from the public folder for public images
   */
  private function prepare_image_url($url){
    $new_url = $url;   
    $priv_path = '/system/files/';
    $private_file_dir_pos = strpos($url, $priv_path);
    if ($private_file_dir_pos !== false) {
      $end_pos = strlen($url) - ($private_file_dir_pos + strlen($priv_path));
      $file = substr($url, $private_file_dir_pos + strlen($priv_path), $end_pos); 
      $new_url = $GLOBALS['base_url'].'/'.variable_get('file_private_path').'/'.$file;               
    }
    return urldecode(preg_replace('/\?.*/', '', $new_url));    
  }
  
  /**
   * Includes the htmltodocx libraries if available
   * @return boolean TRUE/FALSE If libraries are sucessfully loaded
   */
  private function require_htmltodocx(){
  	$path = libraries_get_path('htmltodocx');
  	if(
  	  file_exists($path . '/phpword/PHPWord.php')
  	  && file_exists($path . '/simplehtmldom/simple_html_dom.php')
  	  && file_exists($path . '/htmltodocx_converter/h2d_htmlconverter.php')
  	){
  	  require_once($path . '/phpword/PHPWord.php');
  	  require_once($path . '/simplehtmldom/simple_html_dom.php');
  	  require_once($path . '/htmltodocx_converter/h2d_htmlconverter.php');
  	  return true;
  	} else {
  	  $link = l('htmltodocx', 'http://htmltodocx.codeplex.com/downloads/get/615101');
  	  drupal_set_message(t('The libraries are not installed correctly. Please download and extract !link to your libraries folder', array('!link' => $link)), 'warning');
  	  return false;
  	}
  }
  
  /**
   * Returns an array with style information for the htmltodocx library
   */
  private function get_style(){

	$styles['default'] = 
	  array (
	    'size' => 10,
	    'name' => 'Verdana',
	  );
	  
    $styles['elements'] = 
	  array (
	    'h1' => array (
	      'name' => 'Sensation',
	      'bold' => TRUE,
	      'size' => 16,
	      'spaceAfter' => 100,
	      ),
	    'h2' => array (
	      'name' => 'Sensation',
	      'bold' => TRUE,
	      'size' => 14,
	      'spaceAfter' => 100,
	      ),
	    'h3' => array (
	      'name' => 'Sensation',
        'bold' => TRUE,
        'size' => 14,
        'spaceAfter' => 100,
	      ),
	    'h4' => array (
	      'name' => 'Sensation',
        'bold' => TRUE,
        'size' => 14,
        'spaceAfter' => 100,
	      ),
	    'h5' => array (
	      'name' => 'Sensation',
        'bold' => TRUE,
        'size' => 14,
        'spaceAfter' => 100,
	      ),
	    'h6' => array (
	      'name' => 'Sensation',
        'bold' => TRUE,
        'size' => 14,
        'spaceAfter' => 100,
	      ),
	    'p' => array (
	      'spaceBefore' => 15,
	      'spaceAfter' => 45,
	      ),
	    'li' => array (
	      ),
	    'ol' => array (
	      'spaceBefore' => 200,
	      ),
	    'ul' => array (
	      'spaceAfter' => 150,
	      ),
	    'b' => array (
	      'bold' => TRUE,
	      ),
	    'em' => array (
	      'italic' => TRUE,
	      ),
	    'i' => array (
	      'italic' => TRUE,
	      ),
	    'strong' => array (
	      'bold' => TRUE,
	      ),
	    'b' => array (
	      'bold' => TRUE,
	      ),
	    'code' => array (
	      'name' => 'Courier New',
	      ),
	    'sup' => array (
	      'superScript' => TRUE,
	      'size' => 6,
	      ), // Superscript not working in PHPWord 
	    'u' => array (
	      'underline' => PHPWord_Style_Font::UNDERLINE_SINGLE,
	      ),
	    'a' => array (
	      'color' => '0000FF',
	      'underline' => PHPWord_Style_Font::UNDERLINE_SINGLE,
	      ),
	    'table' => array (
	      'borderColor' => '000000',  
	      'borderSize' => 2,
	      ),
	    'th' => array (
	      'borderColor' => '000000',
	      'borderSize' => 2,
	      'bold' => TRUE,
	      ),
	    'td' => array (
	      'borderColor' => '000000',
	      'borderSize' => 2,
	      ),
	    );
	      
	$styles['classes'] = 
	  array (
	    'underline' => array (
	      'underline' => PHPWord_Style_Font::UNDERLINE_SINGLE,
	    ),
	    'row-heading' => array (
	      'bold' => TRUE,
	    ),
	    'table-of-contents' => array (
	      'tabLeader' => 'underscore',
	    ),
	    'medium-image-size' => array (
	      'width' => 150,
	      'height' => 150,
	    ),
	    'small-image-size' => array (
	      'width' => 80,
	      'height' => 80,
	    ),
	    'comment-header' => array (
        'name' => 'Sensation',
        'bold' => TRUE,
        'size' => 12,
        'spaceAfter' => 50,
      ),
	  );
	  
	$styles['inline'] = 
	  array(
	    'text-decoration: underline' => array (
	      'underline' => PHPWord_Style_Font::UNDERLINE_SINGLE,
	    ),
	    'float: left' => array (
	      'align' => 'left',
	    ),
	    'float: none' => array (
	      'align' => 'center',
	    ),
	    'float: right' => array (
	      'align' => 'right',
	    ),
	  );
	    
	return $styles;
  }
}  




