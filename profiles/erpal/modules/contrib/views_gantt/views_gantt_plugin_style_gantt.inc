<?php

/**
 * @file
 * Contains the list style plugin.
 */

/**
 * Style plugin to render Gantt charts.
 *
 * @ingroup views_style_plugins
 */
class views_gantt_plugin_style_gantt extends views_plugin_style_list {
  private $option_fields;
  private $options_node;

  private $project;
  private $tasks = array();
  /**
   * Set default options.
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['height'] = array('default' => '');
    $options['class'] = array('default' => '');
    $options['wrapper_class'] = array('default' => 'item-list');
    $options['id_field'] = array('default' => '');
    $options['name_field'] = array('default' => '');
    $options['parent_field'] = array('default' => '');
    $options['date_field'] = array('default' => '');
    $options['end_date_field'] = array('default' => '');
    $options['progress_field'] = array('default' => '');
    $options['project_id_field'] = array('default' => '');
    $options['project_node_type'] = array('default' => '');
    $options['project_date_field'] = array('default' => '');
    $options['parent_id_field'] = array('default' => '');
    $options['predecessor_id_field'] = array('default' => '');
    return $options;
  }
  /**
   * Style option form.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $fields = array('' => t('<None>'));

    foreach ($this->display->handler->get_handlers('field') as $field => $handler) {
      if ($label = $handler->label()) {
        $fields[$field] = $label;
      }
      else {
        $fields[$field] = $handler->ui_name();
      }
    }

    $form['height'] = array(
      '#type' => 'textfield',
      '#title' => t('Height of Gantt Chart'),
      '#default_value' => $this->options['height'],
      '#description' => t('Height of Gantt Chart (in px).'),
      '#size' => '5',
    );
    $form['id_field'] = array(
      '#type' => 'select',
      '#title' => t('ID field'),
      '#options' => $fields,
      '#default_value' => $this->options['id_field'],
      '#description' => t('Select the field that contains nid of each record.'),
      '#required' => TRUE,
    );
    $form['name_field'] = array(
      '#type' => 'select',
      '#title' => t('Name field'),
      '#options' => $fields,
      '#default_value' => $this->options['name_field'],
      '#description' => t('Select the field that contains name of each record.'),
      '#required' => TRUE,
    );
    $form['date_field'] = array(
      '#type' => 'select',
      '#title' => t('Date field'),
      '#options' => $fields,
      '#default_value' => $this->options['date_field'],
      '#description' => t('Select the field that contains the start date (timestamp or valid <a href="http://www.php.net/manual/en/datetime.formats.php" target="_blank">date format</a>) of the node in the selected row.'),
      '#required' => TRUE,
    );
    $form['end_date_field'] = array(
      '#type' => 'select',
      '#title' => t('End date field'),
      '#options' => $fields,
      '#default_value' => $this->options['end_date_field'],
      '#description' => t('Select the field that contains the end date (timestamp or valid <a href="http://www.php.net/manual/en/datetime.formats.php" target="_blank">date format</a>) of the node in the selected row.'),
      '#required' => TRUE,
    );
    $form['progress_field'] = array(
      '#type' => 'select',
      '#title' => t('Progress field'),
      '#options' => $fields,
      '#default_value' => $this->options['progress_field'],
      '#description' => t('Select the field that contains the progress of the node in percents.'),
      '#required' => TRUE,
    );
    $form['project_id_field'] = array(
      '#type' => 'select',
      '#title' => t('Project ID field'),
      '#options' => $fields,
      '#default_value' => $this->options['project_id_field'],
      '#description' => t("Select the field that contains nid of the record's project node."),
      '#required' => TRUE,
    );
    $form['project_node_type'] = array(
      '#type' => 'select',
      '#title' => t('Project node type'),
      '#options' => node_type_get_names(),
      '#default_value' => $this->options['project_node_type'],
      '#description' => t('Select type of project nodes.'),
    );
    $form['project_date_field'] = array(
      '#type' => 'select',
      '#title' => t('Project date field'),
      '#options' => $fields,
      '#default_value' => $this->options['project_date_field'],
      '#description' => t("Select the field that contains the date (timestamp or valid <a href='http://www.php.net/manual/en/datetime.formats.php' target='_blank'>date format</a>) of the record's project node."),
      '#required' => TRUE,
    );
    $form['parent_id_field'] = array(
      '#type' => 'select',
      '#title' => t('Parent ID field'),
      '#options' => $fields,
      '#default_value' => $this->options['parent_id_field'],
      '#description' => t("Select the field that contains nid of the record's parent node."),
    );
    $form['predecessor_id_field'] = array(
      '#type' => 'select',
      '#title' => t('Predecessor ID field'),
      '#options' => $fields,
      '#default_value' => $this->options['predecessor_id_field'],
      '#description' => t("Select the field that contains nid of the record's predecessor node."),
    );
  }
  /**
   * Render the given style.
   */
  function render() {
    // Check for live preview.
    if (isset($this->view->live_preview)) {
      return t('Gantt Chart not compatible with live preview.');
    }   

    $this->options_fields();
    $this->options_node();

    // Get project data.
    if (!$this->get_project()) return;

    // Get array of tasks.
    foreach ($this->view->result as $row) {
      $this->add_task($row);
    }

    foreach ($this->tasks as $key => $task) {
      $this->load_missing_tasks($key);
    }

    // Allow to alter tasks array before next modifications.
    drupal_alter('views_gantt_tasks_prerender', $this->tasks);
    
    // Remove tasks marked for deletion
    foreach ($this->tasks as $key => $value) {
      if ($this->is_delete($key)) {
        unset($this->tasks[$key]);
      }
    }

    $this->fill_child_ids();

    // Build hierarchical tree of tasks and fix incorrect values.
    $tree = $this->build_tree($this->tasks);
    foreach ($tree as $key => $task) {
      $this->check_date($task);
      $this->check_duration($task);
      $this->calculate_progress($task);
    }

    // Exclude incorrect tasks.
    foreach ($this->tasks as $key => $value) {
      $this->check_predecessor($key);
      if (!$this->is_correct($key)) {
        unset($this->tasks[$key]);
      }
    }    

    $this->mark_modified_tasks();

    $this->views_gantt_before_render();
    return parent::render();
  }

  function build_tree($tasks, $parent_id = '', $level = 0) {
    $branch = array();

    foreach ($tasks as $key => $task) {
      if ($task['parent_id'] == $parent_id) {
        $task['id'] = $key;
        $task['level'] = $level;
        $children = $this->build_tree($tasks, $key, $level + 1);
        if ($children) {
          $task['children'] = $children;
        }
        $branch[$key] = $task;
      }
    }

    return $branch;
  }

  function check_date($task, $parent_id = '') {
    if (isset($task['children'])) {
      foreach ($task['children'] as $child) {
        $this->check_date($child, $task['id']);
      }
    }

    $time = $this->get_time($this->tasks[$task['id']]['est']);
    $project_time = $this->get_time($this->project['startdate']);

    if ($parent_id) {
      $end_time = $this->get_time($this->tasks[$task['id']]['end_date']);
      $parent_time = $this->get_time($this->tasks[$parent_id]['est']);
      $parent_end_time = $this->get_time($this->tasks[$parent_id]['end_date']);
      
      if ($time < $parent_time) {
        $this->tasks[$parent_id]['est'] = date('Y,n,j', $time);
        $this->tasks[$parent_id]['est_modified'] = TRUE;
      }

      if ($end_time > $parent_end_time) {
        $this->tasks[$parent_id]['end_date'] = date('Y,n,j', $end_time);
        $this->tasks[$parent_id]['duration_modified'] = TRUE;
      }
    }

    if ($time < $project_time) {
      $this->project['startdate'] = date('Y,n,j', $time);
    }
  }

  function check_duration($task, $parent_id = '') {
    if (!isset($this->tasks[$task['id']]['duration'])) {
      $this->calculate_duration($task['id']);  
    }

    if (isset($task['children'])) {
      foreach ($task['children'] as $child) {
        $this->check_duration($child, $task['id']);
      }
    }

    if ($parent_id) {
      $duration = $this->tasks[$task['id']]['duration'];
      $parent_duration = $this->tasks[$parent_id]['duration'];

      if ($parent_duration < $duration) {
        $this->tasks[$parent_id]['duration'] = $duration;
        $this->tasks[$parent_id]['duration_modified'] = TRUE;
      }
    }     
  }

  function calculate_progress($task, $parent_id = '', &$childs = array()) {
    if (!$parent_id) {
      $childs = array();
    }
    
    $progress = $this->tasks[$task['id']]['percentcompleted'];

    if (isset($task['children'])) {
      $this->tasks[$task['id']]['percentcompleted'] = 0;
      foreach ($task['children'] as $child) {
        $this->calculate_progress($child, $task['id'], $childs);
      }

      if (!empty($childs)) {
        $progress = 0;
        foreach ($childs as $key => $percent) {
          $progress += $this->tasks[$key]['percentcompleted'];
        }
        $progress = (string) ceil($progress / count($childs));
        $this->tasks[$task['id']]['percentcompleted'] = $progress;
      }
    }

    $childs[$task['id']] = $progress;      
  }

  function calculate_duration($task_id) {
    $start_date = $this->get_time($this->tasks[$task_id]['est']);
    $end_date = $this->get_time($this->tasks[$task_id]['end_date']); 
    // We assumed that 1 day = 8 hours
    $duration = ceil(($end_date - $start_date) / (3600 * 3));  
    $this->tasks[$task_id]['duration'] = $duration; 
  }

  /**
    * If predecessor task starts later then child task,
    * we just remove predecessor-child relation.
    */
  function check_predecessor($id) {
    if ($this->tasks[$id]['predecessortasks']) {
      $predecessor = $this->tasks[$id]['predecessortasks'];
      $this->check_predecessor($predecessor);

      if (isset($this->tasks[$predecessor])) {
        $start_time = $this->get_time($this->tasks[$id]['est']);
        $pre_start_time = $this->get_time($this->tasks[$predecessor]['est']);
        $pre_end_time = $this->get_time($this->tasks[$predecessor]['end_date']);

        $remove = $pre_start_time >= $start_time || $pre_end_time > $start_time;
      } else {
        $remove = TRUE;
      }

      if ($remove) {
        $this->tasks[$id]['predecessortasks'] = '';
        $this->tasks[$id]['predecessor_modified'] = TRUE;
      }
    }
  }

  function is_correct($id) {
    $task = $this->tasks[$id];
    $is_correct = $task['duration'] > 0 && $task['est'] && $task['end_date'];
    return $is_correct;
  }  

  function is_delete($id) {
    $task = isset($this->tasks[$id]) ? $this->tasks[$id] : array();
    return isset($task['delete']);
  }

  function get_time($date_string) {
    $date = str_replace(',', '/', $date_string);
    return strtotime($date);
  }

  function fill_child_ids() {
    foreach ($this->tasks as $key => $task) {
      if ($task['parent_id']) {
        $this->tasks[$task['parent_id']]['child_ids'][] = $key;
      }
    }
  }  

  function mark_modified_tasks() {
    foreach ($this->tasks as $key => $task) {
      if (isset($task['est_modified']) || isset($task['duration_modified'])) {
        $this->tasks[$key]['name'] .= ' *DATE COLLISION*';
      }
    }    
  }

  /**
   * Returns value of specific field.
   * 
   * @param object $row
   *   Node object from view result array
   * @param string $field_options_name
   *   Option key from views_gantt_plugin_style_gantt::option_definition()
   * 
   * @return string
   *   Field value from node object
   */
  function views_gantt_get_field_value($row, $field_options_name) {
    $field_name = $this->options[$field_options_name];
    $field_value = '';

    // If field value is array, we try to get it's raw value,
    // if it's not possible, we get rendered value.
    if (isset($this->option_fields[$field_name]) && !empty($this->option_fields[$field_name])) {
      $field_value = $row->{$this->option_fields[$field_name]};
      if (is_array($field_value)) {
        if ($field_options_name == 'end_date_field' && isset($field_value[0]['raw']['value2'])) {
          $field_value = $field_value[0]['raw']['value2'];
        }
        elseif (isset($field_value[0]['raw']['value'])) {
          $field_value = $field_value[0]['raw']['value'];
        }
        elseif (isset($field_value[0]['rendered']['#markup'])) {
          $field_value = $field_value[0]['rendered']['#markup'];
        }
      }

      // If field should provide date, we need to return it's
      // value in specific date format (Y,n,j).
      $date_fields = array('date_field', 'end_date_field', 'project_date_field');
      if (!is_array($field_value) && in_array($field_options_name, $date_fields)) {
        views_gantt_normalize_date_field($field_value);
      }
    }

    return is_array($field_value) && empty($field_value) ? '' : $field_value;
  }

  /**
   * Returns value of specific field from node.
   * 
   * @param object $node
   *   Node object received via node_load()
   * @param string $field_options_name
   *   Option key from views_gantt_plugin_style_gantt::option_definition()
   * 
   * @return string
   *   Field value from node object
   */
  function views_gantt_get_node_field_value($node, $field_options_name) {
    $field_name = $this->options_node[$field_options_name];
    $field_value = '';
    $lang = LANGUAGE_NONE;

    if (isset($node->$field_name) && !empty($node->$field_name)) {
      $field_value = $node->$field_name;
      if (is_array($field_value)) {
        // Get field info.
        $field_info = field_info_field($field_name);

        // If field is translatable, we check if
        // it has an index equals to node language.
        $is_translatable = field_is_translatable('node', $field_info);
        if ($is_translatable && isset($node->{$field_name}[$node->language])) {
          $lang = $node->language;
        }

        $value_keys = array_keys($field_info['columns']);
        $field_value = $node->{$field_name}[$lang][0][$value_keys[0]];
        if ($field_options_name == 'end_date_field' && isset($value_keys[1])) {
          $field_value = $node->{$field_name}[$lang][0][$value_keys[1]];
        }
      }

      // If field should provide date, we need to return it's
      // value in specific date format (Y,n,j).
      $date_fields = array('date_field', 'end_date_field', 'project_date_field');
      if (!is_array($field_value) && in_array($field_options_name, $date_fields)) {
        views_gantt_normalize_date_field($field_value);
      }
    }

    return $field_value;
  }  

  /**
   * Gets real names of fields that we put in style settings.
   * If field come from Fields API, we get it's name.
   * Otherwise (if field is 'node_title' for example) we get field alias.
   */
  function options_fields() {
    $this->option_fields = array();
    $view_fields = $this->view->field;
    foreach ($this->view->display_handler->get_handlers('field') as $key => $handler) {
      if (isset($view_fields[$key]) && isset($handler->field_info)) {
        $this->option_fields[$key] = 'field_' . $key;
      }
      else {
        $this->option_fields[$key] = $handler->field_alias;
      }
    }
  }

  /**
   * Some fields in $this->options can have
   * incorrect names (e.g. field_date_1).
   * We need to create new array which contains
   * correct field names to use it in
   * views_gantt_get_node_field_value() function.
   */
  function options_node() {
    $view_fields = $this->view->field;
    foreach ($this->options as $key => $value) {
      if (is_string($value) && isset($view_fields[$value])) {
        $this->options_node[$key] = $view_fields[$value]->field;
      }
    }
  }

  function get_project() {
    $project_id = $this->views_gantt_get_field_value($this->view->result[0], 'project_id_field');
    $node = node_load($project_id);
    $project_date = $this->views_gantt_get_field_value($this->view->result[0], 'project_date_field');

    $this->project = array(
      'name' => $node->title,
      'id' => $node->nid,
      'startdate' => $project_date,
    );    

    if (!$project_date) {
      drupal_set_message(t('Gantt Chart requires filled project date.'), 'warning');
      $this->project = NULL;
    }

    return $this->project;
  }

  function load_missing_tasks($id) {
    $task = $this->tasks[$id];
    $fields = array('predecessortasks', 'parent_id');

    foreach ($fields as $field) {
      $check_id = $task[$field];
      $new_task_id = TRUE;
      if ($check_id && !isset($this->tasks[$check_id])) {
        $new_task_id = $this->load_task_from_node($check_id);
        if ($new_task_id) {
          $this->load_missing_tasks($new_task_id);
        }
      }

      if (!$new_task_id || $this->is_delete($check_id)) {
        $this->tasks[$id]['delete'] = TRUE;
      }
    }
  }

  function load_task_from_node($nid) {
    $node = node_load($nid);
    if ($node) {
      return $this->add_task($node, 'node');
    }

    return FALSE;
  } 

  function add_task($data, $type = 'view') {
    switch ($type) {
      case 'view':
        $method = 'views_gantt_get_field_value';
        $task_id = $this->$method($data, 'id_field');
        break;
      
      case 'node':
        $method = 'views_gantt_get_node_field_value';
        $task_id = $data->nid;
        break;

      default:
        return;
    }

    $keys = array(
      'name' => 'name_field',
      'est' => 'date_field',
      'end_date' => 'end_date_field',
      'percentcompleted' => 'progress_field',
      'predecessortasks' => 'predecessor_id_field',
      'parent_id' => 'parent_id_field',
    );

    $task = array();
    foreach ($keys as $key => $field) {
      $task[$key] = $this->$method($data, $field);
    }
    $this->tasks[$task_id] = $task + array(
      'childtasks' => array(),
    );

    return $task_id;
  }   

  function views_gantt_before_render() {
    // Save view name to variable.
    variable_set('views_gantt_view_name', $this->view->name);

    // Save data in session to use it when we will build XML file for chart.
    $_SESSION['views_gantt']['project'] = $this->project;
    $_SESSION['views_gantt']['tasks'] = $this->tasks;
    
    // Add dhtmlxgantt library.
    $library = libraries_load('dhtmlxgantt');

    // Add css to fix chart style.
    drupal_add_css(drupal_get_path('module', 'views_gantt') . "/css/reset.css");
    // Add js.
    drupal_add_js(drupal_get_path('module', 'views_gantt') . "/js/views_gantt.js");
    //add the imagepath of gantt path respecting the libraries position
    $img_path = base_path().$library['library path'].'/'.$library['path'].'/codebase/imgs/';
    drupal_add_js(array('views_gantt' => array('img_path' => $img_path)), 'setting');
    
    // Add jquery ui Dialog library.
    drupal_add_library('system', 'ui.dialog');
    
    // Add globals variables to use it in js.
    $settings = array(
      'views_gantt' => array(
        'view_name' => $this->view->name,
        'display_id' => $this->view->current_display,
        'project_id' => $this->project['id'],
        'exposed_input' => $this->view->exposed_input,
        'fullscreen_button' => '<a class="gantt-fullscreen">Fullscreen</a>',
      ),
    );
    drupal_add_js($settings, 'setting');    
  }
}
