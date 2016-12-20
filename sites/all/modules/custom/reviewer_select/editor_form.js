(function($) {
	Drupal.behaviors.editorForm = {
		attach : function(context, settings) {
			$('#bidding').hide(); 
			$('#bidding').find('[value^=Send Bidding Email]').die('click').live('click', function() {
				    cont = confirm('Are sure you want to send the bidding email?');
				    
				if(cont){
                                 return true;
                             }
				
				return false;
                      });
			 
			
			$('#bidding-show').find('[value^=Show Bidding Form]').die('click').live('click', function() {
				$('#bidding').show();
				$(this).parent().hide();
				 $('*[id*=edit-bidding-email-format]:visible').each(function() {
		 				$(this).hide();
					});
			});
		}
	};
})(jQuery);