(function($) {

  $(document).ready(function() {
    erpal_calendar_helper_page_handler();
  });

  Drupal.behaviors.erpal_calendar_helper = {
    attach: function(context) {
      erpal_calendar_helper_page_handler();
    }
  };

  /**
   * Helper function. Handles page process.
   */
  function erpal_calendar_helper_page_handler() {
    // Append "add date" link into each day cell.
    $('div.view-full-calendar div.fc-view-month td > div > div.fc-day-number').each(function() {
      // Check if link already exists.
      if ($(this).find('div.fc-day-number > a.erpal-fc-add-date').size() == 0) {
        // Append "add date" link.
        $(this).append('<a href="#" class="erpal-fc-add-date">+</a>');
      }
    });
  }


  /**
   * Add custom erpal_fullcalendar plujin
   */
  Drupal.fullcalendar.plugins.erpal_fullcalendar = {
    options: function(fullcalendar, settings) {

      var options = {
        dayClick: function(date, allDay, jsEvent, view) {
          // Get date of current clicked day
          var formatted_date = $.fullCalendar.formatDate(date, 'yyyy-MMM-dd');
          var link = 'node/add/erpal-date?erpal_date=' + formatted_date;
          
          // Redirect to "add date" page on "+" click
          if($(jsEvent.target).hasClass('erpal-fc-add-date')){
             window.open(link, '_blank');
          }
          
          return false;
        }
      };

      // Merge  optionsd in settings.
      $.extend(options, settings.fullcalendar);

      return options;
    }
  };

}(jQuery));
