<?php
/**
 * Generic callback for modal forms
 * One can create multistep forms using this function.
 * $js - js is enabled
 * $step - the current step, can be used to pass arguments
 * $form_id - id of the form to be generated
 * $path - callback path
 * $order - order of steps, basically names
 * $forms - forms to be displayed at each step
 * $object_id - to be used for caching
 * $params - params to form info
 * $formstate - anything that needs to be added to form state will be passed to all the forms.
 */
function generic_modal_callback($js = NULL, $step = NULL, $form_id, $path, $order, $forms, $object_id, $params = NULL, $formstate = NULL){
  if ($js) {
    ctools_include('modal');
    ctools_include('ajax');
    ctools_include('node.pages', 'node', '');
  }

    $form_info = array(
    'id' => $form_id,
    'path' => "swj/" . ($js ? 'ajax' : 'nojs') . $path,
    'show trail' => $params['show trail'],
    'show back' => $params['show back'],
    'show cancel' => $params['show cancel'],
    'show return' => $params['show return'],
    'next callback' =>  'reviewer_modal_wizard_next',
    'finish callback' => 'reviewer_modal_wizard_finish',
    'cancel callback' => 'reviewer_modal_wizard_cancel',
     'no back validate' => false,
    '#validate' => false,
   // this controls order, as well as form labels
    /*'order' => array(
      'start' => t('Choose animal'),
    ),*/

   'order' => $order,
   // here we map a step to a form id.
   /* 'forms' => array(
      // e.g. this for the step at wombat/create
      'start' => array(
        'form id' => 'ctools_ajax_sample_start'
      ),
    ),*/
   'forms' => $forms,

  );

  // We're not using any real storage here, so we're going to set our
  // object_id to 1. When using wizard forms, id management turns
  // out to be one of the hardest parts. Editing an object with an id
  // is easy, but new objects don't usually have ids until somewhere
  // in creation.
  //
  // We skip all this here by just using an id of 1.

  //$object_id
  $node = "";

  if($step != "step1" && $step != 'step2' && $step != 'step3'){

      $nid = $step;
      $step = "";
      $node = node_load($nid);

  }

  if (empty($step)) {
    // We reset the form when $step is NULL because that means they have
    // for whatever reason started over.
    reviewer_modal_cache_clear($object_id);
    $step = 'step1';
  }

  // This automatically gets defaults if there wasn't anything saved.
  $object = reviewer_modal_cache_get($object_id);

  if(!isset($object->node_id)){
      $object->node_id = $nid;
  }
  $node = node_load($object->node_id);
  reviewer_modal_cache_set($object_id, $object);
  if($form_id == 'reviewers'){
   if(!isset($object->authors)){


        //this will be used to filter out the authors from the table.
        $authoruids = array();
        //need to add garbage as array search is buggy
    	$authoruids[] = '#$#@GIbberris&*&*&';
         foreach($node->field_authors_ref['und'] as $author){
             $authoruids[] = $author['uid'];
         }
         $object->authors = $authoruids;
    }

  }
  //TODO use node id from the argument
  $form_state['ajax'] = $js;
  $form_state['object_id'] = $object_id;
  $form_state['object'] = &$object;

  $form_state['node'] = $node;

  foreach($formstate as $key => $value){
    $form_state[$key] = $value;
  }
  if($form_id == 'edit_content_modal'){

    module_load_include('inc', 'node', 'node.pages');
    form_load_include($form_state, 'inc', 'node', 'node.pages');
    $form_state['submit_handlers'] = array('node_form_submit');
    //form_load_include($form_state, 'inc', 'node', 'node.pages');
  }
  // Send this all off to our form. This is like drupal_get_form only wizardy.
  ctools_include('wizard');
  $form = ctools_wizard_multistep_form($form_info, $step, $form_state);
  $output = drupal_render($form);

  if ($output === FALSE || !empty($form_state['complete'])) {
    //drupal_set_message('Action completed successfully');
  }

  // If $output is FALSE, there was no actual form.
  if ($js) {
    // If javascript is active, we have to use a render array.
    $commands = array();
    if ($output === FALSE || !empty($form_state['complete'])) {
      // Dismiss the modal.
      //$commands[] = ajax_command_html('#ctools-sample', $animal);

       $commands[] = ctools_ajax_command_reload();
      // $commands[] = ctools_modal_command_dismiss();
    }
    else if (!empty($form_state['cancel'])) {
      // If cancelling, return to the activity.
      $commands[] = ctools_modal_command_dismiss();
    }
    else {
      $commands = ctools_modal_form_render($form_state, $output);
    }
    print ajax_render($commands);
    exit;
  }
  else {
    if ($output === FALSE || !empty($form_state['complete'])) {
      return $animal;
    }
    else if (!empty($form_state['cancel'])) {
    //  drupal_goto('ctools_ajax_sample');
    }
    else {
      return $output;
    }
  }
}


/**
 * Modal callback to submit decision letter and approval of the same.
 */
function decision_modal_callback($js = NULL, $step = NULL) {

  $form_id = 'decision_modal';
  $params = array('show trail' => FALSE,
      'show back' => FALSE,
      'show cancel' => TRUE,
      'show return' => FALSE,);
  $path = '/decision/%step';
  $order = array( // this controls order, as well as form labels
      'step1' => t('Submit Decision Letter'),
      'step1' => t('Again'),
    );

  $forms = array(
      'step1' => array(
        'form id' => 'reviewer_decision_form',
      ),
  );
  $formstate = array();
  $object_id = 4;

  return generic_modal_callback($js, $step,$form_id, $path, $order, $forms, $object_id, $params, $formstate);

}



/*

Muthu modal decisionwarning callback start
*/


function decisionwarning_modal_callback($js = NULL, $step = NULL) {

  $form_id = 'decision_modal';
  $params = array('show trail' => FALSE,
      'show back' => FALSE,
      'show cancel' => TRUE,
      'show return' => FALSE,);
  $path = '/decision/%step';
  $order = array( // this controls order, as well as form labels
      'step1' => t('Submit Decision Letter'),
      'step1' => t('Again'),
    );

  $forms = array(
      'step1' => array(
        'form id' => 'reviewer_decisionwarning_form',
      ),
  );
  $formstate = array();
  $object_id = 4;

  return warningmessage_callback($js, $step,$form_id, $path, $order, $forms, $object_id, $params, $formstate);

}


function warningmessage_callback($js = NULL) {
  // Content that we place in the popup.
  $popup_content = t('<b>Dear Editor</b>,</br> <p> This paper does not have a responsible editor yet. To submit a decision letter the paper needs a handling editor and at least one review.</br>
  Thank you.</p>');

  if (!$js) {
    return $popup_content;
  }

  ctools_include('modal');
  ctools_include('ajax');

  $output = array();
  $output[] = ctools_modal_command_display(t('Please appoint a responsible editor'), $popup_content);
 // $commands[] = ctools_ajax_command_redirect("$node/ ");
  //return array('#type' => 'ajax',  '#commands' => $commands);
  print ajax_render($output);
  drupal_exit();
}

/*

Muthu modal decisionwarning callbackend 
*/






/**
 * Modal callback to email eics
 */
function email_eic_modal_callback($js = NULL, $step = NULL){
  $form_id = 'email_eic';
  $params = array('show trail' => FALSE,
      'show back' => FALSE,
      'show cancel' => TRUE,
      'show return' => FALSE,);
  $path = '/email_eic/%step';
  $order = array( // this controls order, as well as form labels
      'step1' => t('Compose Email'),
    );
  $forms = array(
      'step1' => array(
          'form id' => 'eic_email_form'),
      );
  $formstate = array();
  $object_id = 5;
  return generic_modal_callback($js, $step, $form_id, $path, $order, $forms, $object_id, $params, $formstate);
}

/**
 * Modal callback to configure review reminders
 */
function rev_reminder_modal_callback($js = NULL, $step = NULL){

  $form_id = 'rev_reminder';
  $params = array('show trail' => FALSE,
      'show back' => FALSE,
      'show cancel' => TRUE,
      'show return' => FALSE,);
  $path = '/rev_reminder/%step';
  $order = array( // this controls order, as well as form labels
      'step1' => t('Configure Review Reminder'),
    );
  $forms = array(
      'step1' => array(
          'form id' => 'rev_reminder_form'),
      );
  $formstate = array();
  $object_id = 6;
  return generic_modal_callback($js, $step, $form_id, $path, $order, $forms, $object_id, $params, $formstate);
}

/**
 * Modal callback to email eics
 */
function edit_common_modal_callback($js = NULL, $step = NULL){
  $form_id = 'edit_content_modal';
  $params = array('show trail' => FALSE,
      'show back' => FALSE,
      'show cancel' => TRUE,
      'show return' => FALSE,);
  $path = '/edit_content_modal/%step';
  $order = array( // this controls order, as well as form labels
      'step1' => t('Edit Paper Data'),
    );
  $forms = array(
      'step1' => array(
          'form id' => 'edit_content_common'),
      );
  $formstate = array();
  $object_id = 6;
  return generic_modal_callback($js, $step, $form_id, $path, $order, $forms, $object_id, $params, $formstate);
}

/**
 * Modal callback to invite a reviewer
 */
function invite_reviewer_modal_callback($js = NULL, $step = NULL) {
  $form_id = 'review_invite';
  $path = '/invite/%step';
  $params = array('show trail' => FALSE,
      'show back' => FALSE,
      'show cancel' => TRUE,
      'show return' => FALSE,);
  $order = array( // this controls order, as well as form labels
                'step1' => t('Invite Reviewer')
           );
  $forms =  array( // here we map a step to a form id.
                  'step1' => array( //What we're doing here is telling the wizard when step1 is passed as arg show the form with form_id d7_step_1
                  'form id' => 'reviewer_invite_form',
                  )
            );
  $object_id = 3;
  $formstate = array();
  return generic_modal_callback($js, $step, $form_id, $path, $order, $forms, $object_id, $params, $formstate);
}

/**
 * Modal call back for adding a reviewer.

 */
function add_review_modal_callback($js = NULL, $step = NULL) {
  $form_id = 'review';
  $path = '/review/%step';
  $order = array( // this controls order, as well as form labels
      'step1' => t('Add Review')
    );
  $forms = array( // here we map a step to a form id.
          'step1' => array( //What we're doing here is telling the wizard when step1 is passed as arg show the form with form_id d7_step_1
          'form id' => 'review_form'
      ),
  );
  $params = array('show trail' => FALSE,
      'show back' => FALSE,
      'show cancel' => TRUE,
      'show return' => FALSE,);
  $formstate = array();
  $formstate['type'] = "admin";
  $object_id = 2;

  return generic_modal_callback($js, $step, $form_id, $path, $order, $forms, $object_id, $params, $formstate);
}
/**
 * A modal callback for adding a reviewer.
 */
function reviewer_modal_callback($js = NULL, $step = NULL) {

  $form_id = 'reviewers';
  $path = '/reviewer/%step';
  $params = array('show trail' => TRUE,
            'show back' => TRUE,
            'show cancel' => TRUE,
            'show return' => FALSE,
            );
  $order = array( // this controls order, as well as form labels
              'step1' => t('Search reviewer'),
              'step2' => t('Select reviewer'),
              'step3' => t('Customize email')
           );
  $forms = array( // here we map a step to a form id.
            'step1' => array( //What we're doing here is telling the wizard when step1 is passed as arg show the form with form_id d7_step_1
              'form id' => 'reviewer_filter_mform'
            ),
            'step2' => array(
              'form id' => 'review_select_mform'
            ),
            'step3' => array(
              'form id' => 'edit_memail'
            ),
         );
  $object_id = 1;
  $formstate = array();
  return generic_modal_callback($js, $step, $form_id, $path, $order, $forms, $object_id, $params, $formstate);
}




// ---------------------------------------------------------------------------
// Wizard caching helpers.

/**
 * Store our little cache so that we can retain data from form to form.
 */
function reviewer_modal_cache_set($id, $object) {
  ctools_include('object-cache');
  ctools_object_cache_set('reviewer_modal', $id, $object);
}

/**
 * Get the current object from the cache, or default.
 */
function reviewer_modal_cache_get($id) {
  ctools_include('object-cache');
  $object = ctools_object_cache_get('reviewer_modal', $id);
  if (!$object) {
    // Create a default object.
    $object = new stdClass;
    $object->type = 'unknown';
    $object->name = '';
  }

  return $object;
}

/**
 * Clear the wizard cache.
 */
function reviewer_modal_cache_clear($id) {
  ctools_include('object-cache');
  ctools_object_cache_clear('reviewer_modal', $id);
}

// ---------------------------------------------------------------------------
// Wizard in-between helpers; what to do between or after forms.

/**
 * Handle the 'next' click on the add/edit pane form wizard.
 *
 * All we need to do is store the updated pane in the cache.
 */
function reviewer_modal_wizard_next(&$form_state) {

  reviewer_modal_cache_set($form_state['object_id'], $form_state['object']);
}

/**
 * Handle the 'finish' click on teh add/edit pane form wizard.
 *
 * All we need to do is set a flag so the return can handle adding
 * the pane.
 */
function reviewer_modal_wizard_finish(&$form_state) {
  $form_state['complete'] = TRUE;
}

/**
 * Handle the 'cancel' click on the add/edit pane form wizard.
 */
function reviewer_modal_wizard_cancel(&$form_state) {
  $form_state['cancel'] = TRUE;
}

//Lets the editor/eic configure review reminders for a given paper
function rev_reminder_form($form, &$form_state){
  $node = node_load($form_state['object']->node_id);
  $form['main']  = array('#type'=> 'fieldset',
                          '#title'=> '<b>Configure automatic reminders</b>',
                          '#description' => 'Note: Reviewers with the following status are not shown below: (1) Rejected invitation or (2) Submitted review<br/>',
                          );
  $reviewers = get_reviewers($node);
  foreach($reviewers as $reviewer){
    if($reviewer['accept'] !=2 && $reviewer['submitted'] != 1){

      $form['main'][$reviewer['uid']]['name'] = array(
                                                '#type' => 'markup',
                                                '#markup' => '<b>Reminder Settings For <i>'. $reviewer['name'] . '</i></b>');
      $form['main'][$reviewer['uid']]['num_days'] = array('#type' => 'textfield',
                                                  '#title' => 'Reminder Frequency',
                                                  '#default_value' => $reviewer['rem_frequency'],
                                                  '#attributes' => array('size' =>10),
                                                  '#description' => 'Reminder will be sent every X days, where X is the number in the above box.'  );
      $form['main'][$reviewer['uid']]['send'] = array('#type' => 'checkbox',
                                                  '#title' => 'Send Reminders',
                                                  '#default_value' => 1,
                                                  '#description' => 'Uncheck if you want to stop sending reminders to this reviewer',
                                                  '#suffix' => '<hr/>');
    }
  }

  return $form;
}
// ---------------------------------------------------------------------------
// Wizard forms for our simple info collection wizard.
/**
 * generates form for email eic
 */
function eic_email_form($form, &$form_state){

  $node = node_load($form_state['object']->node_id);
  $emails = get_eic_emails();

  $forms = email_form_gen('', $emails, $node->nid, $node->vid);
  $form['email'] = array(
      '#title' => 'Email eics',
      '#type' => 'fieldset',
      //'#collapsible' => true,
      //'#collapsed' => true,

  );

  foreach($forms as $key => $val){
    $form['email'][$key] = $val;
  }
  unset($form['email']['submit']);
  return $form;
}
function eic_email_form_submit($form, &$form_state){

//   foreach($form_state['values']['email'] as $key => $val){
//     $form_state['values'][$key] = $val;
//   }
  email_form_gen_submit($form, $form_state);

}

/**
 *
 */
function edit_content_common($form, &$form_state){


  $node = node_load(arg(2), arg(3));
  //$form['name'] = array('#type' => 'markup', '#markup' => 'haha');
  //return $form;
 // $node = node_load($form_state['object']->node_id);
  //watchdog('nid', $nid);
  //$node = node_load($nid);

  module_load_include('inc', 'node', 'node.pages');
  form_load_include($form_state, 'inc', 'node', 'node.pages');
  $form['common_content'] = array
        ('#type' => 'fieldset',
         '#title' => 'Edit Content',
        );
 // $form_state['build_info']['args'] = array($node);
  $form = drupal_get_form('submit_paper_node_form',$node);

 // file_field_load('node', array($node), $field, $instances, $langcode, $items, $age)
  // file_field_widget_form($form, $form_state, $field, $instance, $langcode, $items, $delta, $element)
  /*  $form['common_content']['field_submission_type'] = $form_node['field_submission_type'];
  $form['common_content']['field_abstract'] = $form_node['field_abstract'];
  $form['common_content']['field_pdf'] = $form_node['field_pdf'];
  $form['common_content']['field_supplementary_files'] = $form_node['field_supplementary_files'];
  $form['common_content']['field_tags'] = $form_node['field_tags'];
  $form['common_content']['field_flag'] = $form_node['field_flag'];
  $form['common_content']['actions'] = $form_node['actions'];
 */
  foreach(array_keys($form) as $key){
    if(strpos($key, 'field_') === 0 && !((strcmp($key, 'field_pdf')  === 0)  || (strcmp($key, 'field_supplementary_files') === 0 ))){

        $form[$key]['#access'] = FALSE;
    }
  }

  unset($form['field_submission_type']['und']['#value']);

  unset($form['field_abstract']['und'][0]['value']['#value']);
  unset($form['field_pdf']['und']['#value']);
  unset($form['field_supplementary_files']['und']['#value']);
  unset($form['field_tags']['und']['#value']);
  unset($form['field_flag']['und']['#value'] );
  //dpm($form_node);

  //dpm($form);

  return drupal_render($form);
}

function edit_content_common_submit($form, &$form_state){

  $form_state['object']->node = $form_state['node'];
  //dpm($form_state);
}

function edit_memail_submit($form, &$form_state){
   $form_state['object']->node = $form_state['node'];
   $form_state['object']->name = $form_state['values']['name'];
   $form_state['object']->selected = $form_state['values']['selected'];
   $form_state['object']->node_id = $form_state['values']['nd'];

           global $user;
        module_load_include('module', 'testaction', 'testaction');

        $node = node_load($form_state['values']['nd'], $form_state['values']['vd']);

        // load reviewer, if available
        $reviewer = user_load($form_state['values']['selected']);
        if ($reviewer === false) {
                drupal_set_message(t('Reviewer could not be added.'), 'error');
                return;
        }

        $reminder_date = time() + variable_get('review_management_review_reminder', 7) * 24 * 60 * 60;
        // update database status
        $d = db_merge('paper_reviewer') -> key(array(
                'ruid' => $reviewer->uid,
                'nid' => $form_state['values']['nd'],
                'vid' => $form_state['values']['vd']
        )) -> fields(array(
                'added' => REQUEST_TIME,
               'submitted' => 0,
                'accept' => 0,
                'next_reminder' => $reminder_date,
        )) -> execute();

        update_actions_table(2, $form_state['values']['nd'], $form_state['values']['vd'], 'Added reviewer: ' . $reviewer->name, $user->uid, $reviewer->uid);
        $params['subject'] = str_replace('{{tracking_number}}', $node->nid . '-' . $node->vid, variable_get('email_reviewer_assn_subject', REVIEWER_ASSIGNMENT_SUB));
        $message = $form_state['values']['custom_email'];
        $token = get_token($reviewer);
        $direct_url = url(drupal_get_path_alias('node/' . $node -> nid), array('absolute'=> TRUE, 'query' => array('l' => $token)));
        $message = str_replace('{{direct_url}}', $direct_url, $message);
        $params['message'] = $message;
        $params['Reply-to'] = $user->mail;
        $params['cc'] = $user->mail;
        drupal_mail('testaction', 'one-one', $reviewer->mail, '', $params);

        //Delete from reminders for the editor
        $euid = get_responsible_editor($node);
      db_delete('editor_reminder')
      ->condition('nid', $node->nid, '=')
      ->condition('vid', $node->vid, '=')
      ->condition('ruid', $euid, '=')->execute();

        drupal_set_message(t('Successfully added ' . $reviewer->name . ' as a reviewer.'));

}

function edit_memail($form, &$form_state, $currentPage = 1, $hideTable = false){
        global $user;
        $form_state['values']['name'] = $form_state['object']->name;
        $account = user_load($form_state['object']->selected);
        $node = node_load($form_state['object']->node_id);
        if(isset($form_state['values']['default_email'])){
          $body = $form_state['values']['default_email'];//['default_email'];
        }else{
          $body = $form_state['object']-> default_email;
        }
        $body = replace_email_tokens($node->nid, $body);
        $body = str_replace('{{reviewer}}', $account->name, $body);
        $form['fset_review']['To'] = array(
                        '#title' => 'Email Id:',
                        '#type' => 'item',

                        '#markup'=>$account->mail,
                );
        $form['fset_review']['custom_email'] = array(
                        '#title' => 'Email body',
                        '#type' => 'textarea',
                        '#description' => 'You can change the default text to be sent to the editor.',
                        '#cols' => 40,
                        '#rows' => 20,
                        '#required' => FALSE,
                        '#default_value'=>$body,
                );

                $form['fset_review']['name'] = array('#type' => 'hidden','#default_value'=>$account->name);
                $form['fset_review']['nd'] = array('#type' => 'hidden','#default_value'=>$node->nid);
                $form['fset_review']['vd'] = array('#type' => 'hidden','#default_value'=>$node->vid);
                $form['fset_review']['selected'] = array('#type' => 'hidden','#default_value'=>$form_state['object']->selected);
                $form['#prefix'] = "<div id='email'>";
                $form['#suffix'] = "</div>";
          return $form;

}


function theme_reviewer_modal_dropdown($vars) {
  // Provide a unique identifier for every dropdown on the page.
  static $id = 0;
  $id++;

  $class = 'ctools-dropdown-no-js ctools-dropdown' . ($vars['class'] ? (' ' . $vars['class']) : '');

  ctools_add_js('dropdown');
  ctools_add_css('dropdown');

  $output = '';

  $output .= '<div class="' . $class . '" id="ctools-dropdown-' . $id . '">';
  $output .= '<div class="ctools-dropdown-link-wrapper">';
  if ($vars['image']) {
    $output .= '<a href="#" class="ctools-dropdown-link ctools-dropdown-image-link">' . $vars['title'] . '</a>';
  }
  else {
    $output .= '<a href="#" class="ctools-dropdown-link ctools-dropdown-text-link">' . check_plain($vars['title']) . '</a>';
  }

  $output .= '</div>'; // wrapper
  $output .= '<div class="ctools-dropdown-container-wrapper">';
  $output .= '<div class="ctools-dropdown-container">';
  $output .= theme('item_list', array('items' => $vars['links'], 'title' => t('Actions')));//theme_links(array('links' => $vars['links'], 'attributes' => array(), 'heading' => ''));
  $output .= '</div>'; // container
  $output .= '</div>'; // container wrapper
  $output .= '</div>'; // dropdown
  return $output;
}

function ajax_modal_pager($form, $form_state) {

	$args = array(
		'nid' => $form_state['values']['nd'],
		'vid' => $form_state['values']['vd']
	);
	if (isset($form_state['values']['name'])) {
		$args['name'] = $form_state['values']['name'];

	}
	if (isset($form_state['values']['lname'])) {
		$args['lname'] = $form_state['values']['lname'];

	}

	$pager = 4;
	if (isset($form_state['values']['reviewer_pager'])) {
		$pager = intval($form_state['values']['reviewer_pager']);
	}

	$form2 = render(drupal_get_form('review_select_mform', $args));
	$str = '<div id="one">' . $form2 . "</div>";

	return $str;
}

function review_select_mform_validate(){
   //drupal_set_error('Bad');
}

function review_select_mform_submit($form, &$form_state){
  $form_state['object']->name = $form_state['values']['name'];

   $form_state['object']->node_id = $form_state['values']['nd'];
   $form_state['object']->selected = $form_state['values']['accounts'];
   $form_state['object']->currentPage = $form_state['input']['reviewer_pager'];
   $form_state['object']-> default_email = $form_state['values']['default_email'];
}
function review_select_mform($form, &$form_state, $currentPage = 1, $hideTable = false) {
	global $base_url;
	drupal_add_js(drupal_get_path('module', 'reviewer_select') . '/add_reviewer.js');
        /*if(isset(form_state['values']['reviewer_pager']) && form_state['values']['reviewer_pager']!=1){
        }*/
	if (isset($form_state['input']['reviewer_pager'])){
		$currentPage = $form_state['input']['reviewer_pager'];
        }
        else if(isset($form_state['object']->currentPage)){
		$currentPage = $form_state['object']->currentPage;
	}
    $node = node_load($form_state['object']->node_id);
	$pageLimit = 10;
	$pagerSize = 10;
        //$nameVal = $form_state['values']['name'];//['name'];
	if (is_array($node)) {
		$nid = $node['nid'];
		$vid = $node['vid'];
		if (isset($node['name'])) {
			$nameVal = $node['name'];
		}

	} else {
		$nid = $node -> nid;
		$vid = $node -> vid;
	}

         $uids = $form_state['object']->authors;
	// decide when to show the available reviewers to add to paper
	// defaults to showing the table
	if (!$hideTable) {
		$header = array(
			'name' => array(
				'data' => t('Username'),
				'field' => 'u.name'
			),
			'status' => array(
				'data' => t('Reviews assigned'),
				'field' => 'u.status'
			),
			'submitted' => array('data' => t('Reviews Submitted')),
			'roles' => array('data' => t('Roles')),
		);

		// friendly reviewer search, allows case insensitive searching between first OR
		// last name
		$like = '';

                //$form_state_copy = clone($form_state);
                $nameVal = $form_state['object']->name;
                $form_state['values']['name'] = $nameVal;
                $like = 'and u.name like \'%'.$nameVal.'%\'';
		// run ranged query and counting query
		$lower = ($currentPage - 1) * $pageLimit;
		$upper = $pageLimit;
		
               	$result = db_query("SELECT u.name, u.mail, u.status, u.uid, COUNT(ruid) as num_reviews, IFNULL(SUM(submitted), 0) as reviews_submitted FROM users u LEFT JOIN paper_reviewer on ruid = u.uid WHERE NOT EXISTS (SELECT p.ruid, p.nid, p.vid FROM paper_reviewer p WHERE u.uid = p.ruid AND p.nid = $nid AND p.vid = $vid AND p.accept in (0,1)) $like AND u.status <> 0 GROUP BY u.uid ORDER BY u.name ASC LIMIT $lower, $upper");
               	$count = db_query("SELECT COUNT(uid) as num_reviews FROM users u LEFT JOIN paper_reviewer on ruid = u.uid WHERE NOT EXISTS (SELECT p.ruid, p.nid, p.vid FROM paper_reviewer p WHERE u.uid = p.ruid AND p.nid = $nid AND p.vid = $vid AND p.accept in (0,1)) $like AND u.status <> 0")->fetchField();
//		$count = db_query("SELECT COUNT(u.uid) FROM users u WHERE NOT EXISTS (SELECT p.ruid, p.nid, p.vid FROM paper_reviewer p WHERE u.uid = p.ruid AND p.nid = $nid AND p.vid = $vid) $like AND u.status <> 0") -> fetchField();

		$txt = "";

    	if($count == 0){
    	   $txt = 'It appears that the reviewer you are searching for is not present in the system. You can '.render(ctools_modal_text_button(t('Invite a Reviewer (Not Present in the System)'), $base_url.'/swj/nojs/invite/'.$nid, t('Invite a Reviewer not present in the system'),  'ctools-modal-ctools-sample-style'));
    	}
		// test if user is eic
		module_load_include('module', 'testaction', 'testaction');
		global $user;
		$r = db_query("Select count(u.uid) from users_roles u INNER JOIN role r on u.rid = r.rid where u.uid =" . $user -> uid . " and r.name='" . EIC_ROLE . "'") -> fetchField();
		if ($r > 0) $is_eic = true;
		else $is_eic = false;

		// build results
		$status = array(
			t('blocked'),
			t('active')
		);
		$roles = array_map('check_plain', user_roles(TRUE));
		$accounts = array();
		$options = array();
		foreach ($result as $account) {
                        if(array_search($account->uid, $uids)>=1){
                          continue;
			}
			$users_roles = array();
			$roles_result = db_query('SELECT rid FROM {users_roles} WHERE uid = :uid', array(':uid' => $account -> uid));
			foreach ($roles_result as $user_role) {
				$users_roles[] = $roles[$user_role -> rid];
			}
			asort($users_roles);

			//if ($is_eic) $name_view = "<a href=\"$base_url/swj/reviewer/profile/$account->uid/$nid\" target=\"_blank\">$account->name</a>";
			 $name_view = $account->name;

			$options[$account -> uid] = array(
				'name' => $name_view,
				'status' => $account -> num_reviews,
				'roles' => theme('item_list', array('items' => $users_roles)),
				'submitted' => $account -> reviews_submitted,

			);

		}
		// build pager
		$numPages = ceil($count / $pageLimit);
		$pages = '<div class="item-list"><ul class="pager">';
		if ($numPages > 1 && $currentPage != 1)
			$pages .= '<li class="pager-previous"><a href="#previous" title="Go to previous page">‹ previous</a></li>';
		if ($currentPage % 10 == 0) {
			$i = $currentPage - ($pagerSize - 1);
		} else {
			$i = $currentPage - (($currentPage % $pagerSize) - 1);
		}
		$j = $i + $pagerSize - 1;

		for (; $i <= $numPages && $i <= $j; $i++) {
			if ($i == $currentPage) {
				$pages .= '<li class="pager-current">' . $i . '</li>';
			} else {
				$pages .= '<li class="pager-item"><a href="#' . $i . '" title="Go to page ' . $i . '">' . $i . '</li>';
			}
		}
		if ($numPages > 1 && $currentPage != $numPages)
			$pages .= '<li class="pager-next"><a href="#next" title="Go to next page">next ›</a></li>';
		$pages .= '</ul></div>';
		$pager = array('#markup' => $pages);

		// set elements in the form
		$form['fset_review'] = array(
			'#title' => 'Available Reviewers',
			'#type' => 'fieldset',
			'#attributes' => array('id' => 'edit-fset-review')
		);
		if($count !=0){
    		$form['fset_review']['accounts'] = array(
    			//'#title' => 'Reviewer',
                            '#type' => 'tableselect',
    			'#js_select' => FALSE,
    			'#header' => $header,
    			'#options' => $options,
    			'#multiple' => false,
                            //'#required' => true,
    			'#empty' => t('No people available.'),
    			'#suffix' => render($pager),
    			'#prefix' => '<div id="selected_reviewers_hide">' // used for hiding with js
    		);
		}else{
		    $form['fset_review']['acc'] = array('#type' => 'markup', '#markup' => $txt);
		}
                if(isset($form_state['object']->selected)){
		     $form['fset_review']['accounts']['#default_value'] = $form_state['object']->selected;
		}
                //$form['fset_review']['pager'] = array('#theme' => 'pager', '#tags' => array() );

		$form['fset_review']['reviewer_pager'] = array(
			'#type' => 'hidden',
			'#default_value' => (isset($form_state['values']['reviewer_pager']) ? $form_state['values']['reviewer_pager'] : $currentPage)
		);
                $form['fset_review']['name'] = array('#type' => 'hidden','#default_value'=>$nameVal);
		$form['fset_review']['reviewer_pager_submit'] = array(
			'#type' => 'submit',
			'#value' => t('Pager'),
                        '#attributes' => array('class' => array('ctools-use-ajax','form-submit')),
			/*'#ajax' => array(
				'callback' => 'ajax_modal_pager',
				'wrapper' => 'one',
				'method' => 'replace',
				'effect' => 'fade',
			)*/
		);

		$form['fset_review']['nd'] = array(
			'#type' => 'hidden',
			'#value' => $nid,
		);
		$form['fset_review']['vd'] = array(
			'#type' => 'hidden',
			'#value' => $vid,
		);
                $form['fset_review']['default_email'] = array(
			'#title' => 'Email body',
			'#type' => 'hidden',
			'#required' => FALSE,
			'#value' => variable_get('email_reviewer_assn_message', REVIEWER_ASSIGNMENT_MSG),
		);



		$form['fset_review']['confirm_url'] = array(
			'#type' => 'hidden',
			'#value' => url('swj/verify/' . $nid . '/' . $vid . '/', array('absolute' => TRUE))
		);
		$form['fset_review']['current_url'] = array(
			'#type' => 'hidden',
			'#value' => url('node/' . $nid, array('absolute' => TRUE))
		);
                $form['fset_review']['#needs_validation'] = false;

	}
	$form['fset_selected_reviewers']['nd'] = array(
		'#type' => 'hidden',
		'#value' => $nid,
	);
	$form['fset_selected_reviewers']['vd'] = array(
		'#type' => 'hidden',
		'#value' => $vid,
	);

	$form['fset_review']['#prefix'] = '<div id="one">';
        $form['fset_review']['#suffix'] = '</div>';
	return $form;
}

function reviewer_filter_mform_submit($form, &$form_state){
      $form_state['object']->name = $form_state['values']['name'];
      $form_state['object']->node_id = $form_state['values']['nd'];
}
function reviewer_filter_mform($form, &$form_state) {
        if(isset($form_state['object']->name)){
          $nameVal = $form_state['object']->name;
	}
        $node = array();
        if(isset($form_state['object']->node_id)){
            $node = node_load($form_state['object']->node_id);
	}else{
	$node = $form_state['node'];
        }
        //$form_state['title'] ="Enter the name of the person you are searching for:";

	$form['nd'] = array(
		'#type' => 'hidden',
		'#value' => $node -> nid,
	);
	$form['vd'] = array(
		'#type' => 'hidden',
		'#value' => $node -> vid,
	);
	$form['name'] = array(
		'#title' => 'Name',
		'#type' => 'textfield',
		'#size' => 'small',
                '#default_value' => $nameVal,
	);

	return $form;
}

function reviewer_modal_init() {

}



