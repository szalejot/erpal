(function ($) {
  Drupal.behaviors.views_gantt  = {
    attach: function (context) {
      $('#GanttDivFullscreen').appendTo('html').css({
        'width' : $(window).width() + 'px',
        'height' : $(window).height() + 'px'
      });
      ganttFullscreen = ganttInit('GanttDivFullscreen');
      $('#GanttDivFullscreen').hide();

      gantt = ganttInit('GanttDiv');

      // Create dialog
      $(".gantt-task-progress").dialog({
        autoOpen: false,
        title: 'Change progress',
        dialogClass: 'gantt-task-progress-dialog',
        buttons: [ { text: "Ok", click: function() {
          $(this).dialog('close');

          var task_id = $(this).children('[name="task_id"]').val();
          var task_progress = $(this).children('[name="task_progress"]').val();
          progressChange(task_id, task_progress, gantt);
          progressChange(task_id, task_progress, ganttFullscreen)
        }} ]
      }); 
      $('.gantt-task-progress-dialog').appendTo('html');     

      // Go to node after doubleclick on title
      $('.taskNameItem').live('dblclick', function() {
        window.open(Drupal.settings.basePath + 'node/' + $(this).attr('id'));
      }); 

      $('.gantt-fullscreen').live('click', function() {
        toggleFullScreen();
        return false;
      });
    }
  }

  function toggleFullScreen() {
    $('.gantt-task-progress').dialog('close');
    $('body').toggle(); 
    $('#GanttDivFullscreen').toggle().css({
      'width' : $(window).width() + 'px',
      'height' : $(window).height() + 'px'
    });
    if ($('#GanttDivFullscreen').is(':visible')) {
      ganttLoadData(ganttFullscreen, '#GanttDivFullscreen');
    } else {
      ganttLoadData(gantt, '#GanttDiv');
    }
  }

  function ganttInit(selector) {
    var gantt = new GanttChart();
    gantt.setImagePath(Drupal.settings.views_gantt.img_path);
    gantt.setEditable(true);
    gantt.showContextMenu(false);
    gantt.showDescTask(true,'p,n,e');
    gantt.showTooltip(false);

    // Resize tasks
    gantt.attachEvent("onTaskEndResize", function(task) {
      var project_id = Drupal.settings.views_gantt.project_id;
      var project = gantt.getProjectById(project_id);

      jQuery.ajax({
        url: Drupal.settings.basePath + "views_gantt/update/" + task.getId(),
        type: "POST",
        data: {
          fields : {
            end_date_field : Math.round(task.getFinishDate().getTime() / 1000) - task.getEST().getTimezoneOffset() * 60,
            project_date_field : Math.round(project.getStartDate().getTime() / 1000) - task.getEST().getTimezoneOffset() * 60
          },
          project_id : project_id,
          view_name : Drupal.settings.views_gantt.view_name
        }
      });
    });

    // Drag tasks
    gantt.attachEvent("onTaskEndDrag", function(task) {
      var project_id = Drupal.settings.views_gantt.project_id;
      var project = gantt.getProjectById(project_id);

      jQuery.ajax({
        url: Drupal.settings.basePath + "views_gantt/update/" + task.getId(),
        type: "POST",
        data: {
          fields : {
            date_field : Math.round(task.getEST().getTime() / 1000) - task.getEST().getTimezoneOffset() * 60,
            end_date_field : Math.round(task.getFinishDate().getTime() / 1000) - task.getEST().getTimezoneOffset() * 60,
            project_date_field : Math.round(project.getStartDate().getTime() / 1000) - project.getStartDate().getTimezoneOffset() * 60
          },
          action : 'drag',
          project_id : project_id,
          view_name : Drupal.settings.views_gantt.view_name
        }
      });
    });

    // Create gantt chart
    gantt.create(selector);
    ganttLoadData(gantt, '#' + selector);

    var project = gantt.getProjectById(Drupal.settings.views_gantt.project_id);

    // Change the progress after doubleclick on task description
    $('.descTask').live('dblclick', function() {
      var task_id = $(this).prevAll('div:first').attr('id');
      var task = project.getTaskById(task_id);

      $('.gantt-task-progress [name="task_id"]').val(task_id);
      $('.gantt-task-progress [name="task_progress"]').val(task.getPercentCompleted());
      $(".gantt-task-progress").dialog('open');
    });
    
    return gantt;  
  }

  function ganttLoadData(gantt, selector) {
    gantt.loadData(ganttUrl(),true,true);
    var left_menu_offset = 13;
    if (!$(selector + ' .taskPanel').height()) {
      var height = 0;
     left_menu_offset = 15;
      $(selector + ' .taskPanel > div').each(function() {
        height += $(this).height() + 5;
      });
      $(selector + ' .taskPanel').height(height);
      $(selector + ' td div > div').first().height(height);
    }  
    $(selector + ' td div').first().css('top', left_menu_offset + 'px');      
  }

  function progressChange(task_id, progress, gantt) {
    var project_id = Drupal.settings.views_gantt.project_id;
    var project = gantt.getProjectById(project_id);
    var task = project.getTaskById(task_id);
    task.setPercentCompleted(progress);
    project.setPercentCompleted(project.getPercentCompleted());

    if (progress >= 0 && progress <= 100) {
      jQuery.ajax({
        url: Drupal.settings.basePath + "views_gantt/update/" + task_id,
        type: "POST",
        data: {
          fields : {progress_field : progress},
          project_id : project_id,
          view_name : Drupal.settings.views_gantt.view_name
        }
      });
    }
  }

  function ganttUrl() {
    url = Drupal.settings.basePath + 'views_gantt/project.xml?' + 
      'view=' + Drupal.settings.views_gantt.view_name + 
      '&display=' + Drupal.settings.views_gantt.display_id + 
      '&project=' + Drupal.settings.views_gantt.project_id; 

    $.each(Drupal.settings.views_gantt.exposed_input, function(key, val) {
      if (val) {
        url += '&' + key + '=' + val;
      }
    });

    return url;   
  }
})(jQuery);
