<?php
/**
 * @file
 * Defines the templated used to produce the the Gantt Chart
 */
?>
<?php
	$height = isset($view->style_options['height']) && $view->style_options['height'] ? $view->style_options['height'] : '';
	$style = $height ? 'style="height:'.$height.'px;"' : '';
?>
<div <?php print $style; ?> id="GanttDiv">
	<a class="gantt-fullscreen">Fullscreen</a>
</div>
<div class="gantt-task-progress">
	<label for="task_progress">Set task progress:</label>
	<input type="text" name="task_progress" size="3">
	<input type="hidden" name="task_id" value="">
</div>
<div id="GanttDivFullscreen">
	<a class="gantt-fullscreen">Exit Fullscreen</a>
</div>
