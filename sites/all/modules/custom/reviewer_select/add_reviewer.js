(function($) {
	Drupal.behaviors.reviewerSelectFormAddReviewer = {
		attach : function(context, settings) {
                
            /* meta function to show/hide custom email box and fill it with proper values. */
			
			
            /* attach handlers when values change */
            //showHide();
	    
	    	$('#modal-content').find('[value^=Continue]').die('click').live('click', function(e) {
                            if($('#one').length >0){			    	
			    if ($('#one').find('#edit-fset-review table input:checked').length == 0) {
                                   alert("You must select a reviewer to continue");
                                   
				   //$('#modal-content').find('[value^=Continue]').unbind('click');
				   return false;	
			    } 	}

                           
			    	
			});
		$('#modal-content').find('[value^=Finish]').die('click').live('click', function(e) {
                            if($('#email').length >0){			    	
			    if ($('#email').find('#edit-fset-review table input:checked').length == 0) {
                                   var answer = confirm("This action will add the reviewer, Are you sure you want to continue?");
                                   if(answer){
                                      return true;
                                   }
				   //$('#modal-content').find('[value^=Continue]').unbind('click');
				   return false;	
			    } 	}

                           
			    	
			});
			/*$('#one').find('[id^=edit-fset-review] table input:radio').live('click', function(e) {
			    showHide();

			});
			$('#one').find('#edit-update').live('click', function() {
			    showHide();
			});*/
			
			/* adding reviewers */
			$('#one').find('[id^=edit-options]').hide();
			$('#one').find('[id^=edit-preview]').die('click').live('click', function(e) {			
				var content = '';
				$.each($('#one').find('[id^=edit-fset-review] table input:checked'), function() {
					content += $(this).parent().parent().parent().find('td:nth-child(2)').find('a').html();
					content += '\n';
				});
				
				var answer = confirm('The following reviewers will be added and notified via email:\n' + content + '\n\n\nClick "OK" to continue and "Cancel" to make changes.');
				
				if (answer) {
					$('#one').find('input[id^=edit-options]').trigger('mousedown');
				}
				
				e.preventDefault();
			});
			
			
			/* Deleting reviewers */
			
			
			
			// reviewer pager
			$('#one').find('[id^=edit-reviewer-pager-submit]').hide();
			$('form[id^=review-select-mform] ul.pager a').die('click').live('click', function() {
                        
                var page = $(this).attr('href').split('#')[1],
                    current = parseInt($('form[id^=review-select-mform]').find('.pager-current').html());
                    
                if (page == 'next') {
                    page = current+1;
                } else if (page == 'previous') {
                    page = current-1;
                }
                
                if (page) {
                        $('input[name=reviewer_pager]').val(page);
               	 	$('#one').find('[id^=edit-reviewer-pager-submit]').trigger('click');
               	}
                
                return false;
            });
            
            // if its stupid and it works, then its not stupid
            $('#one').ajaxComplete(function(e, xhr, settings) {
                $('#one').find('[class^=wizard-trail]').hide();
		$('#one').find('[class^=form-actions]').hide();                
		var $content = $('#one').find('.pager-current'),
                    item = $content.find('a').html();
                if (item) $content.html(item);
            });
            
            // filter reset button
            $('body').find('input[id^=edit-reset]').bind('mousedown', function(e) {
                $('body').find('input[id^=edit-name]').val(''); 
            });
            
		}
	}
})(jQuery);

