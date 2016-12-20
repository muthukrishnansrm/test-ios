<article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <div class="node-inner">



    <?php print render($title_prefix); ?>
    <?php if ($title || $display_submitted): ?>
      <header<?php print $header_attributes; ?>>

        <?php if ($title && !$page): ?>
          <h1<?php print $title_attributes; ?>>
              <a href="<?php print $node_url; ?>" rel="bookmark"><?php print $title; ?></a>
          </h1>
        <?php endif; ?>

        <?php if ($display_submitted): ?>
          <p class="submitted"><?php print $submitted; ?></p>
        <?php endif; ?>

      </header>
    <?php endif; ?>
    <?php print render($title_suffix); ?>

    <div<?php print $content_attributes; ?>>
    <?php print $user_picture; ?>
    <?php
      hide($content['comments']);
      hide($content['links']);
      if(!isset($in_preview) || !$in_preview){
				  hide($content['field_author']);
				}
				hide($content['field_last_action']);
				//dpm($in_preview);
				hide($content['field_decision']);
				hide($content['field_decision_letter']);
				//hide($content['authors_table']);
				//hide($content['authors_table1']);
				hide($content['actions_eic']);
				if (isset($content['admin_review'])) {
				  hide($content['admin_review']);
				}
				// We hide the comments and links now so that we can render them later.
				//if (isset($content['add_reviewer'])) {
				hide($content['add_reviewer']);
				hide($content['filter']);
				hide($content['invite']);
				//hide($content['field_cover_letter']);
				//}

				if (isset($content['decision'])) {
				  hide($content['decision']);
				}
				if (isset($content['add_review'])) {
				  hide($content['add_review']);
				}
				if (isset($content['actions'])) {
				  hide($content['actions']);
				}
				hide($content['comments']);
				hide($content['links']);
				hide($content['selectedrev']);
                hide($content['hide_review']);
                hide($content['submitted_reviews']);
                hide($content['contact_editor']);
				hide($content['camera_ready_entity_view_1']);
				hide($content['field_editor']);
				hide($content['field_authors_ref']);
				hide($content['allow_cover']);
				hide($content['field_cover_letter']);
				hide($content['update_files']);
				hide($content['field_flag']);
	?>

      <?php print "<h3>Tracking #: $node->nid-$node->vid</h3>"; ?>
      <?php   if($content['field_flag']['#access'] && isset($content[field_flag][0])){

              print ('<h3>Flag : '. $content[field_flag][0]['#markup']. '</h3>');

     }?>
    				<?php if(!$teaser){?>
				<fieldset>
					<!-- legend>
						<span class="fieldset-legend">Paper Data</span>
					</legend -->

					<?php

					if(isset($node->showNotes) && $node->showNotes && isset($content['notes_entity_view_1'])){
					  print ('<div style="background-color: #E3E5E3;border-radius: 5px;padding-top:4px;padding-bottom:4px;padding-left:6px;">');
					  $notes = theme('ctools_collapsible', array('handle' => '<b>Notes</b>', 'content' => render($content['notes_entity_view_1']), 'collapsed' => TRUE));
					  print render($notes);
					  print('</div><br/>');
					}
					?>



					<?php //dpm($content['edit_link_common']);
					 if (isset($content['actions']['history_table'])) {

					  print('<div style="background-color: #E3E5E3;border-radius: 5px;padding-top:4px;padding-bottom:4px;padding-left:6px;">');
					  $hist = theme('ctools_collapsible', array('handle' => '<b>Action History For this Paper</b>', 'content' => render($content['actions']), 'collapsed' => TRUE));
					  print render($hist);

					  print('</div><br/>');

					}
					?>

					<?php
					  if(isset($content['field_authors_ref']) && sizeof($content['field_authors_ref']) > 1){
					  print '<div style="background-color: #E3E5E3;border-radius: 5px;padding-top:4px;padding-bottom:4px;padding-left:6px;">';
                      print render($content['field_authors_ref']);

                      print '</div><br/>';
                      }
                      ?>


					<?php
					  if(isset($content['field_editor']['#access']) || isset($content['field_editor']['#type'])){
                        print '<div style="background-color: #E3E5E3;border-radius: 5px;padding-top:4px;padding-bottom:4px;padding-left:6px;">';
					    print render($content['field_editor']);
                        if(isset($content['contact_editor']['markup'])){
                          print(render ($content['contact_editor']));
                        }
                        print '</div><br/>';
					  }
                    ?>

					<?php
    					hide($content['cam_ready']);
    					hide($content['notes_entity_view_1']);
                    ?>
                    <div style="background-color: #E3E5E3;border-radius:5px;padding-top:4px;padding-bottom:4px;padding-left:6px;">
					<?php
					  print render($content);
					  if(isset($content['update_files'])){
					    print render($content['update_files']);
					  }
					?>
                    </div>
                    <br/>

					<?php
					 if(isset($content['field_cover_letter']['#items']) && ($content['field_cover_letter']['#access'])){
                       print('<div style="background-color: #E3E5E3;border-radius: 5px;padding-top:4px;padding-bottom:4px;padding-left:6px;">');
					   $cover = theme('ctools_collapsible', array('handle' => '<b>Click to Expand/Collapse</b>', 'content' => render($content['field_cover_letter']), 'collapsed' => TRUE));
                       print "<b>Cover Letter:</b>" .  render($cover);
                       if(isset($content['allow_cover']['#form_id'])){
                         print(render ($content['allow_cover']));
                       }
					   print('</div><br/>');
					 }
                    ?>

                    <?php
					if(!isset($node->showFinalVersionLink) || !$node->showFinalVersionLink ){
					  //watchdog('in','here');
					  //hide($content['camera_ready_entity_view_1']);
					  //$content['camera_ready_entity_view_1']	= array();

					  $content['links']['nodereference_url']['#links']['camera_ready_files_field_paper'] = array();

					}else{
					  //dpm($content['links']['nodereference_url']);
					  print('<div style="background-color: #E3E5E3;border-radius: 5px;padding-top:4px;padding-bottom:4px;padding-left:6px;"><h2>');
					  if(!isset($content['camera_ready_entity_view_1']) || sizeof($content['camera_ready_entity_view_1'])<=1){
					    //print_r($content['cam_ready']);

					    print render($content['cam_ready']);
					  }else{
					    print render($content['camera_ready_entity_view_1']);

					  }
					  print('</h2></div><br/>');

					}
                    ?>

                    <?php
                     if(isset($content['field_decision']['#title'])){
                      print('<div style="background-color: #E3E5E3;border-radius: 5px;padding-top:4px;padding-bottom:4px;padding-left:6px;">');
					  print(render($content['field_decision']));
				      if(isset($node->hideit) && !$node->hideit){
				          $dec = theme('ctools_collapsible', array('handle' => '<b>Click to Expand/Collapse</b>', 'content' => render($content['field_decision_letter']), 'collapsed' => TRUE));
                          print "<b>Decision Letter:</b>" . render($dec);
    				  }
                      print('</div><br/>');
                      }
					?>
                    <div id="review">
                    		<?php print render($content['add_review']); ?>
                    	</div>

					<?php
					  if(isset($content['actions_eic']['markup'])){
                        print '<div style="background-color: #E3E5E3;border-radius: 5px;padding-top:4px;padding-bottom:4px;padding-left:6px;">';
					    print render($content['actions_eic']);
					    print '</div><br/>';
					  }
					?>

					<?php
					if(isset($content['selectedrev']['#form_id'])){
					  print('<div style="background-color: #E3E5E3;border-radius: 5px;padding-top:4px;padding-bottom:4px;padding-left:6px;">');
					  print render($content['selectedrev']);
					  print('</div><br/>');
					}
					?>
					<?php
                      //TODO fix
					  if(isset($content['submitted_reviews']) && isset($content['submitted_reviews']['fset1'])){
					    print '<div style="background-color: #E3E5E3;border-radius: 5px;padding-top:4px;padding-bottom:4px;padding-left:6px;">';
					    print ("<b>Solicited Reviews:</b><br/>");
					    //print render(theme('ctools_collapsible', array('handle' => '<b>Click to Expand/Collapse</b>', 'content' => render($content['submitted_reviews']), 'collapsed' => TRUE)));
                        print   render($content['submitted_reviews']);
					    print '</div><br/>';
					  }
					?>
                    <?php
					  //dpm($content['hide_review']['#form_id']);
					  if(isset($content['hide_review']['#form_id'])){
					    print '<div style="background-color: #E3E5E3;border-radius: 5px;padding-top:4px;padding-bottom:4px;padding-left:6px;"><b>Click to hide reviews from users</b>';
					    print render($content['hide_review']);
					    print '</div><br/>';
					  }
					?>

				</fieldset>
				<?php }?>

    </div>

    <div id="admin-review">
		<?php print render($content['admin_review']); ?>
	</div>

	<div id="decision">
		<?php print render($content['decision']); ?>
	</div>




    <?php if ($links = render($content['links'])): ?>
      <nav<?php print $links_attributes; ?>><?php print $links; ?></nav>
    <?php endif; ?>

    <?php print render($content['comments']); ?>

  </div>
  <?php
$sample_style = array(
    'ctools-sample-style' => array(
        'modalSize' => array(
            'type' => 'fixed',
            'width' => 1098,
            'height' => 500,
            'addWidth' => 20,
            'addHeight' => 15,
        ),
        'modalOptions' => array(
            'opacity' => .5,
            'background-color' => '#000',
        ),
        'animation' => 'fadeIn',
        'modalTheme' => 'CToolsSampleModal',
        'throbber' => theme('image', array('path' => ctools_image_path('ajax-loader.gif', 'ctools_ajax_sample'), 'alt' => t('Loading...'), 'title' => t('Loading'))),
    ),
);

drupal_add_js($sample_style, 'setting');
?>
</article>
