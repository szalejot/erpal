<?php

/**
 * @file handles all functions dealing with timetracking nodes
 */

/**
 * Implements callback for compute function for timetracking_button as computed field
 */
function computed_field_field_timetracking_button_compute(&$entity_field, $entity_type, $entity, $field, $instance, $langcode, $items) {
  if ($entity_type == 'node') {
    if ($entity->type == 'erpal_task') {
      $entity_field[0]['value'] = $entity->nid;
    }
  }
  
}

/**
* Shows a warning if the user has unbooked timetrackings
*/
function _erpal_projects_helper_remind_tmp_timetrackings() {
  global $user;
  
  $timetracking_ids = _timetrackings_by_user($user->uid);
  
  //now show only warning, if there are timetrackings older than 48 hours
  $timetrackings = timetracking_load_multiple($timetracking_ids);
  $two_days_sec = 48*60*60;
  
  $timetrackings_link = l('some unbooked timetrackings', 'projects/timetrackings/tmp');  
  foreach ($timetrackings as $tt) {
    if (!$tt->time_end)
      continue;
      
    if (time() - $tt->time_end > $two_days_sec) {
      drupal_set_message(t("You have !link. Please finalise them!", array('!link' => $timetrackings_link)), 'warning', false);
      break; //one message is enough
    }
  }
}


/**
* renders a block html for the last timetracking of a user, if one is available
*/
function _erpal_projects_helper_last_timetracking_block_render($uid) {
  
  if (!$uid)
    return false;
  
  $last_timetracking = _timetrackings_by_user_latest($uid);
  $lt = $last_timetracking;
  if (!$lt)
    return false; //no timetracking available
    
  $subject_id = $lt->subject_id ? $lt->subject_id : md5($lt->description);
  $state = $lt->time_end ? 'off' : 'on';
  
  //@TODO make this work not only for entity type of node. Therefor we have to save the entity type in the database, @see _timetracking_calculate_current_timetrackings#
  $node_titles = erpal_lib_helper_node_titles(array($lt->subject_id));
  $subject_title = $lt->subject_id ? $node_titles[$lt->subject_id] : $lt->description;
  
  //get total duration of all timetrackings to the given subject
  if (is_numeric($subject_id)) {
    //$total_duration = _timetracking_get_total_duration_by_subject_by_user($uid, $subject_id);
    $entity_link = l($subject_title, 'node/'.$subject_id);  //@TODO should work for all entities not only for nodes
  } else {
    $entity_link = $subject_title;
  }
  _erpal_projects_helper_task_has_timetracking_entity_active($subject_id, $duration);
  $duration = round($duration, 2);
  
  $timekeeping_url = url('projects/timetrackings/tmp');

  $timetracking_button = "<div class='last_timetracking'><a class='timekeeping_link' href='".$timekeeping_url."'>".t('list')."</a><span class='timetracking_subject'>".$entity_link."</span>".theme('timetracking_button', array('entity_type' => 'node', 'entity_id' => $subject_id, 'state' => $state, 'duration' => $duration))."</div>";

  return $timetracking_button;
}

/**
 * Alter the quick timetracking form
 */
function _erpal_projects_helper_timetracking_quick_form_alter(&$form, &$form_state) {

  $qt_link = l(t('Timetracking list'), 'projects/timetrackings/tmp', array('attributes' => array('class' => array('timetracking_list_link'))));
  $form['more_link'] = array(
    '#type' => 'markup',
    '#markup' => $qt_link,
    '#weight' => 100, //at the very bottom
    '#prefix' => '<div class="more_quick_timetracking">',
    '#suffix' => '</div>',
  );
  
}

/**
 * Alter the timetracking node form
 */
function _erpal_projects_helper_timetracking_node_form_alter(&$form, $form_state) {
  //we alter only, if the timetracking will be new created, not for existing timetrackings
  $nid = isset($form['nid']['#value']) ? $form['nid']['#value'] : false;
  if ($nid) {
    return;
  }

  if (isset($form['field_timetracking_subject'][LANGUAGE_NONE][0]['target_id'])) {
    $target_string = $form['field_timetracking_subject'][LANGUAGE_NONE][0]['target_id']['#default_value'];
    
    //@TODO sometimes string starts with " and ends with ". That breaks the function
    //@see _erpal_basic_helper_get_nid_from_autocomplete_string cause it doesn't allow chars after (NID).
    //to make that work, we remove these chars
    if ($target_string[0] == '"')
      $target_string[0] = '';
    if ($target_string[strlen($target_string) -1]  == '"')
      $target_string[strlen($target_string) -1] = '';

    $target_string = trim($target_string);
    
    if (!$target_string) {
      //there must be a subject, otherwise show access denied and information to choose a task!
      drupal_set_message(t('Please select a task from you projects first to track you time.'), 'error');
      drupal_access_denied();
      exit(0);
    }

    //prefil the title
    $nid = _erpal_basic_helper_get_nid_from_autocomplete_string($target_string);
    $subject_node = node_load($nid);
    $default_title = _erpal_projects_helper_get_timetracking_default_title();
    $default_title = token_replace($default_title, array('subject' => $subject_node));
    $form['title']['#default_value'] = $default_title;

    //prefill the category
    $node = node_load($nid);
    $category_tid = _erpal_projects_helper_get_project_category($node, true);
    if ($category_tid) {
      $form['field_project_tags'][LANGUAGE_NONE]['#default_value'] = $category_tid;
    }
  }
}

/**
 * Prepend timetracking time fields validation
 */
function _erpal_projects_helper_timetracking_add_time_validation(&$form, $form_state){
  // prepend field_timetracking_duration element validation
  array_unshift($form['field_timetracking_duration'][LANGUAGE_NONE][0]['value']['#element_validate'], '_erpal_projects_helper_time_field_validate');
  // prepend field_billing_duration element validation 
  array_unshift($form['field_billing_duration'][LANGUAGE_NONE][0]['value']['#element_validate'], '_erpal_projects_helper_time_field_validate');  
}

/**
 * creates output to show time estimation and tracked time in tree view
 */
function _erpal_projects_helper_direct_time_information($nid) {
  
  $summed_time = _erpal_projects_helper_get_direct_timetracking_sum($nid);
  $summed_time = $summed_time ? $summed_time : '0';
  //we dont load the complete node, just the estimation field
  $field_info = field_info_field('field_estimated_time');
  $sql_arr = $field_info['storage']['details']['sql']['FIELD_LOAD_CURRENT'];
  $field_name = array_keys($sql_arr);
  $table_name = $field_name[0];
  $value_name = $sql_arr[$table_name]['value'];


  $query = db_select('node',"n");
  $query->leftJoin($table_name, 'e', 'n.vid = e.revision_id');
  $query->fields('e', array($value_name));
  $query->condition('n.nid', $nid);

  $res = $query->execute()->fetchAssoc();

  $value = $res[$value_name] ? $res[$value_name] : 0;
 
  $class = 'tree-field time';
  if ($summed_time > $value)
    $class .= ' alert';
  
  return array(
    'summed_time' => $summed_time,
    'estimation' => $value,
    'alert' => $summed_time > $value,
  );
  return "<span class='$class'> $summed_time / $value ".t('h')."</span>";
}

/**
* returns the sum of all timetrackings booked directly to the given subject node
* @param $reset if true, cached value will be reset
 * CAUTION: This function is also used in a view to calculate the timetracking of a task in the tree by the function
 * @see _erpal_projects_helper_direct_time_information
*/
function _erpal_projects_helper_get_direct_timetracking_sum($node, $reset=false) {
  static $sum = array();
  
  if (is_object($node))
    $nid = $node->nid;
  else
    $nid = $node;
  
  $cache_name = 'erpal_projects_helper_node_direct_time';
  if (!isset($sum[$nid]) || $reset) {

    $cache = cache_get($cache_name);
    $sum = !empty($cache->data) ? $cache->data : array();
    if (!$reset && isset($sum[$nid])) {
      $sum = $cache->data; 
    }    
    else {
      //recalculate the values
      //get table for timetracking field_timetracking_duration
      $field_info = field_info_field('field_timetracking_duration');
      $sql_arr = $field_info['storage']['details']['sql']['FIELD_LOAD_CURRENT'];
      $field_name = array_keys($sql_arr);
      $field_name_table_duration = $field_name[0];
      $value_field_duration = $sql_arr[$field_name_table_duration]['value'];

      //get table for field_timetracking_subject
      $field_info = field_info_field('field_timetracking_subject');
      $sql_arr = $field_info['storage']['details']['sql']['FIELD_LOAD_CURRENT'];
      $field_name = array_keys($sql_arr);
      $field_name_table_subject = $field_name[0];
      $value_field_subject = $sql_arr[$field_name_table_subject]['target_id'];


      $query = db_select('node',"n");
      $query->leftJoin($field_name_table_subject, 's', 'n.nid = s.'.$value_field_subject);
      $query->leftJoin($field_name_table_duration, 'd', 'd.entity_id = s.entity_id');  
      $query->condition('n.nid', $nid);
      $query->condition('n.type', 'erpal_task');
      $query->addExpression("SUM(".$value_field_duration.")", 'duration');
      $res = $query->execute()->fetchAssoc();

      $sum[$nid] = !empty($res['duration']) ? $res['duration'] : 0;
      
      _erpal_projects_helper_set_node_time_cache($cache_name, $sum);      
      
    }
  }
    
  return $sum[$nid];
}
//JUST FOR DEBUGGING
function DEBUG_getSize($arr) {
    $tot = 0;
    foreach($arr as $a) {
        if (is_array($a)) {
            $tot += getSize($a);
        }
        if (is_string($a)) {
            $tot += strlen($a);
        }
        if (is_int($a)) {
            $tot += PHP_INT_SIZE;
        }
    }
    return $tot;
}

/**
 * called in @see erpal_projects_helper_entity_presave - sets the project tags to the timetracking entity
 */
function _erpal_projects_helper_timetracking_entity_set_project_tags($timetracking_entity) {
  if (!isset($timetracking_entity->is_new))
    return;

  $task_nid = $timetracking_entity->subject_id;

  if (!$task_nid)
    return false;

  $task_node = node_load($task_nid);

  $category_tid = _erpal_projects_helper_get_project_category($task_node, true);
  if ($category_tid)
    $timetracking_entity->field_project_tags[LANGUAGE_NONE][0]['tid'] = $category_tid;
}

/**
* Sets the timeinformation cache invalid.
* @param $node this is a node we want to invlaidate
* Anyway the project is set invalid
*/
function _erpal_projects_helper_summed_timeinformation_invalidate($node) {
  $parent_task_nodes = _erpal_projects_helper_get_parent_tasks($node);
  $project_nid = _erpal_projects_helper_has_project($node);
  $cache_name = 'erpal_projects_helper_node_summed_time';
  $cache = cache_get($cache_name);
  $time_info = !empty($cache->data) ? $cache->data : array();

  //invalidate the node itself
  if (isset($time_info[$node->nid]))
    unset($time_info[$node->nid]);
  
  //invalidate project
  if (isset($time_info[$project_nid]))
    unset($time_info[$project_nid]);
    
  //invalidate all parent tasks
  foreach ($parent_task_nodes as $parent_task_node) {
    if (isset($time_info[$parent_task_node->nid]))
      unset($time_info[$parent_task_node->nid]);
  }
  
  _erpal_projects_helper_set_node_time_cache($cache_name, $time_info);   
}

/**
* Sets the direct timetracking information invalid
*/
function _erpal_projects_helper_direct_timetracking_invalidate($node) {
  
  $cache_name = 'erpal_projects_helper_node_direct_time';
  $cache = cache_get($cache_name);
  $time_info = !empty($cache->data) ? $cache->data : array();

  //invalidate the node itself
  if (isset($time_info[$node->nid]))
    unset($time_info[$node->nid]);
  
  //write the cache back
  _erpal_projects_helper_set_node_time_cache($cache_name, $time_info);
}

/**
 * Get timeinformation of a task or a project. We return the summed time needed on subtasks (and if the given node is a task, we add this infos), the time that is left to work, and the total estimated time.
 *@param $node the node from where we start calculation
 *@param $subtask_nids optional we get all child nids already delivered
 * @param boolean $exclude_self
 *  if true, the parent_id itself will not be added to the result set
 */
function erpal_projects_helper_summed_timeinformation($node, $subtask_nids=array(), $reset = false, $exclude_self=false) {
  static $time_info = array();  //statischer Laufzeitcache

  if ($node->type != 'erpal_task' && $node->type != 'erpal_project')
    return false;
  
  if (!isset($time_info[$node->nid]) || $reset) {
    $cache = cache_get('erpal_projects_helper_node_summed_time');
    $time_info = !empty($cache->data) ? $cache->data : array();
    if (!$reset && !empty($time_info[$node->nid])) {
      //HIT
      $time_info = $cache->data;
    }    
    else {
      //MISS
      //recalculate the values
      $nids = array();
      if ($node->type == 'erpal_task') {
        
        if (!$exclude_self)
          $nids = array($node->nid);

        if (!count($subtask_nids)) {
          //get the child nodes of task
          $subtask_nids = _erpal_projects_helper_get_children($node->nid, $exclude_self);
          $nids = array_merge($nids, $subtask_nids);
        } else {
            $nids = $subtask_nids;
        }
      }  
      elseif ($node->type == 'erpal_project') {
        //get all tasks of the project
        $nids = $subtask_nids;
        if (!count($subtask_nids)) {
          $task_nids = _erpal_projects_helper_get_tasks($node->nid, true, true);
          $nids = array_keys($task_nids);
        }
      }

      if (!count($nids))
        return false;

      //get table for timetracking field_timetracking_duration
      $field_info = field_info_field('field_timetracking_duration');
      $sql_arr = $field_info['storage']['details']['sql']['FIELD_LOAD_CURRENT'];
      $field_name = array_keys($sql_arr);
      $field_name_table_duration = $field_name[0];
      $value_field_duration = $sql_arr[$field_name_table_duration]['value'];

      //get table for field_timetracking_subject
      $field_info = field_info_field('field_timetracking_subject');
      $sql_arr = $field_info['storage']['details']['sql']['FIELD_LOAD_CURRENT'];
      $field_name = array_keys($sql_arr);
      $field_name_table_subject = $field_name[0];
      $value_field_subject = $sql_arr[$field_name_table_subject]['target_id'];

      //get the table for field_estimated_time on a task
      $field_info = field_info_field('field_estimated_time');
      $sql_arr = $field_info['storage']['details']['sql']['FIELD_LOAD_CURRENT'];
      $field_name = array_keys($sql_arr);
      $field_name_table_estimated = $field_name[0];
      $value_field_estimated = $sql_arr[$field_name_table_estimated]['value'];

      //get the table for field_progress_percent on a task
      $field_info = field_info_field('field_progress_percent');
      $sql_arr = $field_info['storage']['details']['sql']['FIELD_LOAD_CURRENT'];
      $field_name = array_keys($sql_arr);
      $field_name_table_percent = $field_name[0];
      $value_field_percent = $sql_arr[$field_name_table_percent]['value'];

      //get estimations but without, timetrackings, that will duplicate the rows and return wrong values
      $query = db_select('node',"n");
      $query->leftJoin($field_name_table_estimated, 'e', 'n.nid = e.entity_id');
      $query->leftJoin($field_name_table_percent, 'p', 'n.nid = p.entity_id');
      $query->condition('n.nid', $nids);
      $query->condition('n.type', 'erpal_task');
      $query->addExpression("SUM(".$value_field_estimated.")", 'estimated');
      $query->addExpression("SUM((".$value_field_estimated." / 100) * ".$value_field_percent.")", 'estimate_done');
      $res = $query->execute()->fetchAssoc();

      $time_info[$node->nid]['estimated'] = $res['estimated'];
      $time_info[$node->nid]['estimated_left'] = $res['estimated'] - $res['estimate_done'];

      $query = db_select('node',"n");
      $query->leftJoin($field_name_table_subject, 's', 'n.nid = s.'.$value_field_subject);
      $query->leftJoin($field_name_table_duration, 'd', 'd.entity_id = s.entity_id');  
      $query->condition('n.nid', $nids);
      $query->condition('n.type', 'erpal_task');
      $query->addExpression("SUM(".$value_field_duration.")", 'time');
      $res = $query->execute()->fetchAssoc();

      $time_info[$node->nid]['timetracking'] = $res['time'];

      _erpal_projects_helper_set_node_time_cache('erpal_projects_helper_node_summed_time', $time_info);      

    }
  }  
  
  return $time_info[$node->nid];
}

/**
* Write the summed time cache to the database
* @param $time_info the cache array to write to the database
* @param $time the time the cache is valid
*/
function _erpal_projects_helper_set_node_time_cache($cache_name, $time_info) {
  cache_set($cache_name, $time_info, 'cache', time() + 300);  //@TODO may be flexible cache duration instead of fixed 5 minutes      
}

/**
 * Post execute handles timetracking view so we can replace an empty timetracking button computed field the timetracking button using the md5 checksum of the description
 */
function _erpal_projects_helper_view_timetracking_entites_post_execute(&$view) {

  if ($view->name != 'timetracking_entities')
    return;

  foreach ($view->result as $delta=>$result_obj) {
    if (empty($result_obj->field_field_timetracking_button)) {
      //if we have a subject, use this, otherwise use the md5 of the subject.
      $subject_nid = $result_obj->node_timetracking_nid;
      $description = $result_obj->timetracking_description;

      if (!$subject_nid) {
        $subject_nid = md5($description);
      }
      $display_output = _erpal_projects_helper_render_timetracking_button_field($subject_nid);
      $result_obj->field_field_timetracking_button[0] = array(
        'rendered' => array('#markup' => $display_output, '#access' => true),
        'raw' => array('value' => $subject_nid),
      );

      $view->result[$delta] = $result_obj;
    }
  }
}


/**
 * Implements callback for display function for timetracking_button as computed field
 */
function computed_field_field_timetracking_button_display($field, $entity_field_item, $entity_lang, $langcode) {
  $nid = $entity_field_item['value'];

  $display_output = _erpal_projects_helper_render_timetracking_button_field($nid);
  return $display_output;
}

/**
 * Callback for action with the same name definied in hook_action_info
 */
function erpal_projects_helper_timetracking_finalise_action(&$timetrackings, $context) {
  //first validate
  $errors = _erpal_projects_helper_timetracking_finalise_action_validate($timetrackings);

  if ($errors && is_array($errors) && count($errors)) {

    foreach ($errors as $id=>$errors_arr) {
      $entity = $errors_arr['entity'];
      $error_texts = $errors_arr['errors'];
      foreach ($error_texts as $text) {
        drupal_set_message($text, 'error');
      }
    }

    //drupal_goto($_GET['q']);
  } else {
    //no errors so finalise the timetrackings
    foreach ($timetrackings as $timetracking) {

      //if timetracking entity has endtime set but no duration (it should be 0 or not set, just delete the entity
      if ($timetracking->time_end && !$timetracking->duration) {
        $timetracking->delete();
        continue;
      }


      $timetracking_node = _erpal_projects_helper_timetracking_finalise($timetracking);
      //if timetracking node was created, delete the temporary timetracking entity
      if ($timetracking_node->nid) {
        $timetracking->delete();
      } else {
        $timetracking_link = l($timetracking->defaultLabel(), 'timetracking/'.$timetracking->timetracking_id.'/edit');
        drupal_set_message(t('Timetracking !timetracking_link could not be finalised.', array('!timetracking_link' => $timetracking_link)), 'error');
      }
    }
  }
  
}

/**
 * Renders the html code for timetracking button on tasks
 */
function _erpal_projects_helper_render_timetracking_button_field($nid, $start_label=false, $stop_label=false) {
  if (!is_numeric($nid)) {  //it could be an MD5 hash
    //we have no subject but timetracking can be started without subject!
    $node_type = false;
    $node = false;
  } else {
    $node = node_load($nid);
    $node_type = $node->type;
  }

  if ($node_type == 'erpal_task' || !$node_type) {
    //add field to show the timetracking toggle button   
    $tracked_time = 0;
    $has_timetracking_active = _erpal_projects_helper_task_has_timetracking_entity_active($nid, $tracked_time);
    $has_timetracking_active_str = $has_timetracking_active ? 'on' : 'off';

    $timetracking_button = theme('timetracking_button', array('entity_type' => 'node', 'entity_id' =>$nid, 'state' => $has_timetracking_active_str, 'duration' => $tracked_time, 'start_label' => $start_label, 'stop_label' => $stop_label));

    return $timetracking_button;
  }
  
}

/**
 * Checks if there are timetracking entity (temporary) that have the given node as subject_id and have no duration set
 * @param $nid can be a numeric nid or a md5 string of the description of the timetracking, if timetracking has no subject, yet
 * @return false if no timetracking entities are running, otherwise true
 */
function _erpal_projects_helper_task_has_timetracking_entity_active($nid, &$tracked_time) {
  global $user;

  if (!is_numeric($nid)) { //timetrackings without subject but md5 subject
    $timetracking_ids = _timetrackings_by_user($user->uid, false);
    //check if there is one timetracking without subject
    $timetracking_ids_no_subject = array();
    foreach ($timetracking_ids as $timetracking_id) {
      $timetracking = timetracking_load($timetracking_id);
      $equal_description = $nid == md5($timetracking->description);
      if (!$timetracking->subject_id && $equal_description) {  //it has no subject node but it must match the md5 description, otherwise the timetrcking was for another subject text.
      
        $timetracking_ids_no_subject[] = $timetracking_id;
      }
    }

    $timetracking_ids = $timetracking_ids_no_subject;
  } else
    $timetracking_ids = _timetrackings_by_user($user->uid, $nid);

  //load all entities and calculate the total time.
  $timetrackings = timetracking_load_multiple($timetracking_ids);

  $total = 0;
  $has_running = false;
  foreach ($timetrackings as $timetracking) {
    if ($timetracking->time_end) {
      $duration = $timetracking->duration;
    } else {
      $date_end = _timetracking_get_minute_granularity(time());
      $date_start = _timetracking_get_minute_granularity($timetracking->time_start);
      $duration = ($date_end - $date_start) / (60*60);
      $has_running = true;
    }

    $total += $duration;
  }

  $tracked_time = round($total, 2);

  return $has_running;
}

/**
 * Get autocomplete path for tasks by project
 */
function _erpal_projects_helper_get_tasks_by_project_autocomplete_path($project_nid=0) {
  return 'projects/tasks/autocomplete/'.$project_nid;
}

/**
 * Submit callback when project is chosen in timetracking block and we want wo actualise the autocomplete path for tasks
 */
function _erpal_projects_helper_timetracking_ajax_project_select($form, $form_state) {
  $values = $form_state['values'];
  $project_nid = $values['project_nid'];

  //if there is a project nid, subject will be selected by select box, not autocomplete
  if ($project_nid) {
    //we do this because just switching to #type = select doesn't work....so introduce a new element
    $form['subject_select']['#prefix'] = $form['subject']['#prefix'];
    $form['subject_select']['#suffix'] = $form['subject']['#suffix'];
    $form['subject_select']['#type'] = 'select';
    $form['subject_select']['#name'] = 'subject';
    $task_nids = _erpal_projects_helper_get_tasks_by_project($project_nid);
    $tasks = _erpal_basic_helper_nids_for_form_select($task_nids);
    $form['subject_select']['#options'] = $tasks;
    return $form['subject_select'];
  } else {
    $form['subject']['#autocomplete_path'] = _erpal_projects_helper_get_tasks_by_project_autocomplete_path($project_nid);
  }

  return $form['subject'];
}

/**
 * Create a real timetracking node from a temporary timetracking entity
 */
function _erpal_projects_helper_timetracking_finalise($timetracking) {
  $timetracking->close();  //it should already be closed
  $subject_nid = $timetracking->subject_id;
  $subject_node = node_load($subject_nid);
  //create a timetracking
  $tt = new stdClass();
  $tt->language = LANGUAGE_NONE;
  $tt->type = 'erpal_timetracking';
  $tt->title = $timetracking->description ? $timetracking->description : $subject_node->title;
  $tt->field_timetracking_subject[LANGUAGE_NONE][]['target_id'] = $timetracking->subject_id;
  $tt->field_date_time[LANGUAGE_NONE][0]['value'] = $timetracking->time_start;
  $tt->field_date_time[LANGUAGE_NONE][0]['value2'] = $timetracking->time_end;
  $tt->field_billing_duration[LANGUAGE_NONE][0]['value'] = $timetracking->duration;
  $tt->uid = $timetracking->uid;
  $tt->created = $timetracking->created;
  $tt->changed = $timetracking->changed;

  //add the project_tags value from the timetracking entity
  if (isset($timetracking->field_project_tags[LANGUAGE_NONE][0]['tid']))
    $tt->field_project_tags[LANGUAGE_NONE][0]['tid'] = $timetracking->field_project_tags[LANGUAGE_NONE][0]['tid'];

  node_object_prepare($tt);
  node_save($tt);

  return $tt;
}

/**
 * Validate all timetracking of the bulk operation erpal_projects_helper_timetracking_finalise_action
 * @param $timetrackings
 * @return array of array with the timetracking and an errormessage 
 */
function _erpal_projects_helper_timetracking_finalise_action_validate($timetrackings) {
  $errors = false;

  foreach ($timetrackings as $timetracking) {
    //error if timetracking has no subject
    $timetracking_link = l($timetracking->defaultLabel(), 'timetracking/'.$timetracking->timetracking_id.'/edit', array('query' => array('destination' => $_GET['q'])));
    if (!$timetracking->subject_id) {
      $errors[$timetracking->timetracking_id]['entity'] = $timetracking;
      $errors[$timetracking->timetracking_id]['errors'][] = t('To finalise a timetracking, ensure that a subject task is set for !timetracking_link', array('!timetracking_link' => $timetracking_link));
    } elseif (!$timetracking->time_end) {
      //if we dont have a duration the timetracking is still running and cannot be finalised!
      $errors[$timetracking->timetracking_id]['entity'] = $timetracking;
      $errors[$timetracking->timetracking_id]['errors'][] = t('To finalise the timetracking !timetracking_link, ensure that it is not still tracking the time!', array('!timetracking_link' => $timetracking_link));
    }
  }

  return $errors;
}

/**
 * Presave hook a timetracking node 
 */
function erpal_projects_helper_node_presave_timetracking($node) {

  if (isset($node->nid)) {
    //load the old timetracking node to add its billing_duration, not the new current one
    $old_node = node_load($node->nid);
    _erpal_projects_helper_restore_timetracking_budget($old_node);
  }

  //if no value is available, we caclulate the value using start and end time
  $start_time = $node->field_date_time[LANGUAGE_NONE][0]['value'];
  $end_time = isset($node->field_date_time[LANGUAGE_NONE][0]['value2']) ? $node->field_date_time[LANGUAGE_NONE][0]['value2'] : $node->field_date_time[LANGUAGE_NONE][0]['value'];

  $diff_duration = $end_time - $start_time;
  $diff_duration = $diff_duration / (60 * 60);//calculate hours
  $time_duration = round($diff_duration, 2); //round with 2 digits

  $duration = 0;
  if (isset($node->field_timetracking_duration[LANGUAGE_NONE][0]['value']))
    $duration = $node->field_timetracking_duration[LANGUAGE_NONE][0]['value'];

  if (!$duration)
    $node->field_timetracking_duration[LANGUAGE_NONE][0]['value'] = $time_duration;

  $billing_duration = 0;
  if (isset($node->field_billing_duration[LANGUAGE_NONE][0]))
    if (isset($node->field_billing_duration[LANGUAGE_NONE][0]['value']))
      $billing_duration = $node->field_billing_duration[LANGUAGE_NONE][0]['value'];

  if (!$billing_duration)
    $node->field_billing_duration[LANGUAGE_NONE][0]['value'] = $node->field_timetracking_duration[LANGUAGE_NONE][0]['value'];

  //if node doesn't have a duration, but billing duration, set duration to billing duration.
  if (!$duration && $billing_duration && !(isset($node->nid) && $node->nid)) {
    $node->field_timetracking_duration[LANGUAGE_NONE][0]['value'] = $billing_duration;
  }

  //may be the duration was set to -1 in _erpal_projects_billable_book_timetracking_to_budget which signals that we dont want to change that value in presave routine.
  if ($node->field_timetracking_duration[LANGUAGE_NONE][0]['value'] < 0)
    $node->field_timetracking_duration[LANGUAGE_NONE][0]['value'] = 0;

  return $duration;
}


/**
 * @param a timetracking node
 * @return a float value with the billing duration. If billing duration is set, the value is returned itself, otherwise the
 *   duration value is set. This is the duration in hours
 */
function _erpal_projects_helper_get_billing_duration($node) {

  $billing_duration = $node->field_billing_duration[LANGUAGE_NONE][0]['value'];

  if ($billing_duration)
    return $billing_duration;

  $duration = $node->field_timetracking_duration[LANGUAGE_NONE][0]['value'];

  if ($duration)
    return $duration;

  //if no value is available, we caclulate the value using start and end time
  $start_time = $node->field_date_time[LANGUAGE_NONE][0]['value'];
  $end_time = $node->field_date_time[LANGUAGE_NONE][0]['value2'];

  $duration = $end_time - $start_time;
  $duration = $duration / (60 * 60);//calculate hours
  $duration = round($duration, 2); //round with 2 digits

  return $duration;
}

/**
 * Return all timetracking nids that reference directely one of the given nids
 */
function _erpal_projects_helper_get_direct_timetrackings($nids) {

  $timetracking_nids = array();

  if (!$nids || !count($nids))
    return $timetracking_nids;

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'erpal_timetracking')
    ->fieldCondition('field_timetracking_subject', 'target_id', $nids, 'IN')
    ->addMetaData('account', user_load(1)); // run the query as user 1 to get all nodes

  $result = $query->execute();

  if (isset($result['node'])) {
    $timetracking_nids = array_keys($result['node']);
  }

  return $timetracking_nids;
}

/**
 * Return all timetracking nids that reference directely one of the given nids
 * @param $date_from if set, the date where to start for the timetracking field_date_time[value]
 * @param $date_till if set, the date where to end for the timetracking field_date_time[values2]
 */
function _erpal_projects_helper_get_direct_timetrackings_by_date_range($nids, $date_from, $date_till) {

  $timetracking_nids = array();

  if (!$nids || !count($nids))
    return $timetracking_nids;

  if (!$date_from)
    $date_from = 0;
  if (!$date_till)
    $date_till = PHP_INT_MAX;

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'erpal_timetracking')
    ->fieldCondition('field_timetracking_subject', 'target_id', $nids, 'IN')
    ->fieldCondition('field_date_time', 'value', $date_from, '>=')
    ->fieldCondition('field_date_time', 'value2', $date_till, '<=')
    ->fieldOrderBy('field_date_time', 'value', 'ASC')
    ->addMetaData('account', user_load(1)); // run the query as user 1 to get all nodes

  $result = $query->execute();

  if (isset($result['node'])) {
    $timetracking_nids = array_keys($result['node']);
  }

  return $timetracking_nids;
}

/**
 * Return all timetrackings that reference to a given budget_id
 * @param $budget_id the budget id that the returned timetracking nodes must referr to
 * @return an array with all nids of timetrackgins
 */
function _erpal_projects_helper_get_timetrackings_by_budget($budget_id) {
  $timetracking_nids = array();

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'erpal_timetracking')
    ->fieldCondition('field_budget', 'target_id', $budget_id)
    ->addMetaData('account', user_load(1)); // run the query as user 1 to get all nodes

  $result = $query->execute();

  if (isset($result['node'])) {
    $timetracking_nids = array_keys($result['node']);
  }

  return $timetracking_nids;
}

/**
 * Function returns the price of a billable that was created by the timetracking. It is used in php field of timetracking view
 */
function _erpal_projects_helper_timetracking_view_field_billable($nid) {

  $value = _erpal_projects_helper_get_timetracking_price_of_billable($nid, true);
  return $value;
}


/**
 * Returns the price of a billable that is create for a timetracking node
 * @param $check_permissions if true, the price is returned if the user has permissions to view prices
 */
function _erpal_projects_helper_get_timetracking_price_of_billable($nid, $check_permissions=true) {
  
  //we dont call this if projects billable module is not enabled
  if (!module_exists('erpal_projects_billable')) 
    return false;
  
  $billables = _billable_get_billables_by_subject(array($nid));

  if ($check_permissions && !user_access('field view pricing')) {
    return false;
  }

  $sum = 0;
  foreach ($billables as $billable_id) {
    $billable = billable_load($billable_id);

    //we add only price form billables where the contractor is the own company, because if a freelancer tracked time, there will also be a billable where the freelancer is the contractor.
    $contractor_nid = $billable->contractor_nid;
    $own_company_nid = _erpal_basic_helper_get_own_company_nid(false);
    if ($contractor_nid != $own_company_nid)
      continue;

    $sum += $billable->total_price_no_vat;
  }

  return $sum;
}