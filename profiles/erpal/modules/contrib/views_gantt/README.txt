Views Gantt
http://drupal.org/project/views_gantt

This module provides a views display plugin to show tasks in a GANTT Chart
using the dhtmlx GANTT javascript library. Views Gantt
uses the libraries API. Please upload the dhtmlx GANTT library
and put it in you libraries folder if you want to use this module.

Installation:
------------
1. Download and unpack the Libraries module directory in your modules folder
   (this will usually be "sites/all/modules/").
   Link: http://drupal.org/project/libraries
2. Download and unpack the Views module directory in your modules folder
   (this will usually be "sites/all/modules/").
3. Download and unpack the Views Gantt module directory in your modules folder
   (this will usually be "sites/all/modules/").
4. Download and unpack the dhtmlx GANTT js library in "sites/all/libraries".
    Make sure the path to the plugin files becomes:
    "sites/all/libraries/dhtmlxgantt/codebase/dhtmlxgantt.css",
    "sites/all/libraries/dhtmlxgantt/codebase/dhtmlxcommon.js",
    "sites/all/libraries/dhtmlxgantt/codebase/dhtmlxgantt.js",
   Link: http://www.dhtmlx.com/docs/products/dhtmlxGantt/
5. Go to "Administer" -> "Modules" and enable the Views Gantt module.
6. Create view with Gantt style and set all required options in the settings.
	- required
		ID field - task nid (numeric).
		Name field - task title (string).
		Date field - task start date (timestamp or date string in right format for strtotime()).
		End date field - task end date (timestamp or date string in right format for strtotime()).
		Progress field - task progress in percent (numeric).
		Project ID field - project nid, can be node reference field in task (numeric).
		Project node type - type of project nodes.
    Project date field - project start date (timestamp or date string in right format for strtotime()).

	-optional
		Parent ID field - task parent nid (numeric).
		Predecessor ID field - task predecessor nid (numeric).
		Height of Gantt Chart - height value in px

7. Date and end date fields in tasks and project can't be empty.


If you find a problem, incorrect comment, obsolete or improper code or such,
please let us know by creating a new issue at
http://drupal.org/project/issues/views_gantt
