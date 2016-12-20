(function($) {
	Drupal.behaviors.reviewerSelectForm = {
		attach : function(context, settings) {
					
			$('.tabledrag-toggle-weight-wrapper').remove();
			
			function changeText() {
				var val = $('#edit-field-editor-und').find(':selected').val(),
					val_text = $('#edit-field-editor-und').find(':selected').text(),
					old_val = $('input[name="field_editor[editor_original]"]').val();
				
				if (val) {
					// no email will be sent if old value is same as current
					if (val == '_none' || val == old_val) {
						$('#edit-field-editor-custom-email-editor').parent().parent().hide();
					} else {
						// email should be sent, replace contents of email box and show it
						var rx = /Dear.*,/,
							current = $('#edit-field-editor-custom-email-editor').val();
							
						current = current.replace(rx, 'Dear ' + val_text + ',');
						$('#edit-field-editor-custom-email-editor').html(current);
						
						$('#edit-field-editor-custom-email-editor').parent().parent().show();
						
					}
				}
			}
			
			changeText();
			
			// if select box changes
			$('#edit-field-editor-und').change(function() {
				changeText();
			});
		}
	}
})(jQuery);
