(function ($) {
  Drupal.behaviors.eurekaAjax = {
    attach: function (context, settings) {
      // Bind an AJAX callback to our link
      var eurekaAjaxLink = $('#eureka-ajax');
       
      eurekaAjaxLink.click(function(event) {
        // Prevent the default link action
        event.preventDefault();
         
        // Get the request URL without the query string
        var ajaxUrl = eurekaAjaxLink.attr('href').split('?');
         
        $.ajax({
          type: "POST",
          url: ajaxUrl[0],
          data: {
            // For server checking
            'from_js': true
          },
          dataType: "json",
          success: function (data) {
            // Display the time from successful response
            if (data.message) {
              $(".messages").remove();
              $("#content").prepend('<div class="messages status">' + data.message + '</div>');
            }
          },
          error: function (xmlhttp) {
            // Error alert for failure
            alert('An error occured: ' + xmlhttp.status);
          }
        });
      });
    }
  };
})(jQuery);