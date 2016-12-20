(function($) {
	Drupal.behaviors.historyTableAjax = {
		attach : function(context, settings) {
            $('#history_table ul.pager a').live('click', function() {
                var page = $(this).attr('href').split('#')[1];
                var current = parseInt($('#history_table').find('.pager-current').html());
                
                if (page == 'next') {
                    page = current+1;
                } else if (page == 'previous') {
                    page = current-1;
                }
                
                $.ajax({
                    url: $('input[name=history_table_callback]').val(),
                    type: 'GET',
                    cache: false,
                    data: {
                        'page': page,
                        'nid': $('input[name=nd]').val(),
                        'vid': $('input[name=vd]').val(),
                    },
                    success: function(data) {
                        if (data.length > 0 && data[1]['data']) {
                            $('#history_table').html(data[1]['data']);
                            
                            // drupal's js gets in the way after ajax call
                            var $content = $('#history_table').find('.pager-current');
                            var item = $content.find('a').html();
                            if (item) $content.html(item);
                        }
                    },
                    error: function(data) {
                        //console.log(data);
                    },
                });
                return false;
            });
            
            
            
            function addAddMeBtn() {
				var $athrs = jQuery("[id^=edit-field-author] table[id^=field-author-values]");
				var $addme = jQuery("<a />");
				$addme.attr({"href": "#", "class": "add-me-btn"})
					.html("Add Me")
					.css({"float": "right"});
					
				var $existing = $athrs.find("tr td:nth-child(2) a.add-me-btn");
				if ($existing.length < 1) {
					$athrs.find("tr td:nth-child(2)").prepend($addme);
					
					$athrs.find("tr td:nth-child(2) a").click(function() {
						var $fn = jQuery("input[name=user_info_first_name]"),
							$ln = jQuery("input[name=user_info_last_name]"),
							$em = jQuery("input[name=user_info_email]"),
							$prt = jQuery(this).parent("td");
						
						$prt.find("div.field-name-field-fname input").val($fn.val());
						$prt.find("div.field-name-field-lname input").val($ln.val());
						$prt.find("div.field-name-field-email input").val($em.val());
						return false;
					});
				}
			}
			
			function trimEmails() {
				$('#history_table').find('td.email').each(function() {
					if ($(this).html().length > 60) {
						var content = $(this).html(),
							$fullcontent = $('<span />'),
							$trimcontent = $('<span />');
						
						$fullcontent.addClass('full-content')
							.html(content + '<br /><a href="#" class="less-link">(less)</a>')
							.hide();
						$trimcontent.addClass('trim-content')
							.html(content.substr(0, content.indexOf('message')) + ' <a href="#" class="more-link">...(more)</a>');
						
						$fullcontent.find('a.less-link').click(function() {
							$fullcontent.hide();
							$trimcontent.show();
							return false;
						});
						$trimcontent.find('a.more-link').click(function() {
							$trimcontent.hide();
							$fullcontent.show();
							return false;
						});
						
						$(this).empty()
							.append($fullcontent)
							.append($trimcontent);
					}
				});
				
			}
			
			trimEmails();
			$("body").ajaxComplete(function() {
				trimEmails();
			});
            
		}
	}
})(jQuery);
