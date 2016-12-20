(function($) {
	Drupal.behaviors.verifyForm = {
		attach : function(context, settings) {

			$('input[name=status]').click(function() {
			    if ($(this).val() == 1) {
			        $('div.form-item-reason').hide();
			    } else {
			        $('div.form-item-reason').show();
			    }
			});
			
			$('div.form-item-reason').hide();
		}
	}
})(jQuery);
