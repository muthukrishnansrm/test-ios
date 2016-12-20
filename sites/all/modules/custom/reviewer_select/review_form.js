(function($) {
	Drupal.behaviors.reviewForm = {
		attach : function(context, settings) {
			//$('#edit-review-comments-format').hide();	
                        //$('#edit-comment-for-edit-format').hide();
                        $('*[id*=edit-review-comments-format]:visible').each(function() {
    				$(this).hide();
			});
			$('*[id*=edit-comment-for-edit-format]:visible').each(function() {
    				$(this).hide();
			});
			
                        //if($('#edit-field-decision-letter-format-help').length>0){
  			   $('[id^=edit-decision-letter-format]').hide();	                        
			//}	
			//$('#modal-content').find('[class^=fieldset-wrapper]').hide();
			$('#modal-content').find('[value^=Finish]').die('click').live('click', function(e) {
                            if($('#review_form').length >0){			    	
			           var answer = confirm('Please review the changes before submitting. Press ok to submit.');
                                   if(answer){
                                      return true;
                                   }
				   //$('#modal-content').find('[value^=Continue]').unbind('click');
				   return false;	
			    	}

                           
			    	
			});
			
			$('#editor_decision').find('[id^=edit-status]').change('click', function(){
				var selectedVal = $(this).val();
				
				var letterBox = $('#editor_decision').find('[id^=edit-decision-letter-value]');
				
				if(selectedVal == 'Accept'){
					letterBox.val($('#editor_decision').find('[name^=accept_letter]').val());
				}else if(selectedVal == 'Minor Revision'){
					letterBox.val($('#editor_decision').find('[name^=minor_letter]').val());
				}else if(selectedVal == 'Major Revision'){
					letterBox.val($('#editor_decision').find('[name^=major_letter]').val());
				}else if(selectedVal == 'Reject'){
					letterBox.val($('#editor_decision').find('[name^=reject_letter]').val());
				}else if(selectedVal == 'Reject (Pre-Screening)'){
					letterBox.val($('#editor_decision').find('[name^=reject_pre_letter]').val());
				}
				//$('#editor_decision').find('[id^=edit-decision-letter]').val = 
			});
                        $('#editor_decision').find('[value^=Finish]').die('click').live('click', function() {
				    cont = confirm('You can only submit the decision letter once. Are you sure you want to submit?');
				    
				if(cont){
                                    return true;
                                }
				
				return false;
                         });
			//alert($('#div_two').find('input[id^=edit-delete').length);
			$('#div_two').find('input[id^=edit-delete]').hide();
			$('#div_two').find('a.delete_reviewer').die('click').live('click', function() {
				var id = $(this).attr('id').split('rev-'),
				    cont = confirm('Are you sure you want to delete this reviewer?');
				    
				if (id.length == 2 && cont) {
				    $('input[name=\"delete_reviewer\"]').val(id[1]);
				    
				    $('#div_two').find('input[id^=edit-delete]').trigger('mousedown');
				}
				
				return false;
                         });
			
			$('#cv_form').find('[id^=edit-field-show-cover-letter-und]').die('click').live('click', function() {
				console.log($(this).attr('checked'));
				var confirmAction = false;
				if($(this).attr('checked')){
					confirmAction = confirm('Do you actually want to grant access to Cover letter and supplementary files to the reviewers?'); 
				}else{
					confirmAction = confirm('Do you actually want to revoke access to Cover letter and supplementary files from the reviewers?');
				}
				
				if(!confirmAction){
					return false;
				}
				$('#cv_form').find('form').submit();
			});
			
		}
	}
})(jQuery);
