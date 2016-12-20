(function($) {
	Drupal.behaviors.reviewerSelectFormAddReviewer = {
		attach : function(context, settings) {
$('#div_two').find('input[id^=edit-delete]').hide();
			$('#div_two').find('a.delete_reviewer').die('click').live('click', function() {
				var id = $(this).attr('id').split('rev-'),
				    cont = confirm('Are you sure you want to delete this reviewer?');
				    
				if (id.length == 2 && cont) {
				    $('input[name="delete_reviewer"]').val(id[1]);
				    
				    $('#div_two').find('input[id^=edit-delete]').trigger('mousedown');
				}
				
				return false;
			});


