<?php

/**
 * @author: Kunal Sengupta
 *
 * This page contains all the major forms used in the system
 *
 * add_author_form: Generates the form for adding authors to a paper.
 *
 * authors_table_form - Selectable table of authors displayed on paper view page.
 *
 * assign_editor_form - Embeds the assign editor field on the paper page. No need to go to the edit page to change editor.
 *
 * reviewer_decision_form - Displays a decision form form for submitting decision letter and approval by eics.
 *
 * reviewer_invite_form - Form for inviting a reviewer not present in the system. Displayed on actions drop down.
 *
 * selectedrev_form - Form to display reviewers that have been added to the paper. Also the status of their activity. (For editors and eic)
 *
 * review_form - Form to submit reviews. Is displayed for reviewer on node page and for editor on Actions dropdown.
 *
 * form_hide_reviews - Displays the hide reviews button on the paper page.
 *
 *
 * allow_cover_letter_form - Allows the edit show_cover_letter field on the paper view page.
 *
 */



/**
 * Custom form that is embedded in node edit for adding authors.
 * Since the actual author field is field_authors_ref which is a user reference
 * Intelligent form, user can add as many authors as needed.
 */
function add_author_form($form, &$form_state, $node = NULL) {
  $form_state['storage']['authors'] =
    isset($form_state['storage']['authors']) ? $form_state['storage']['authors'] : 1;
  $form_state['storage']['removed'] = array();

  $form_author['auth_add']['authors'] = array(
    '#type' => 'container',
    '#tree' => TRUE,
    '#prefix' => '<div id="add-authors-form">',
    '#markup' => '<b>Authors: </b><hr/>',
    '#suffix' => '</div>',
  );

  $form_author['auth_add']['authors']['Title'] = array(
    '#type' => 'item',
    '#tree' => TRUE,
    '#markup' => '<b>Authors: </b>',
  );
  $uids = array();

  //if add button was clicked add a set of fields
  if(isset($form_state['triggering_element']) && $form_state['triggering_element']['#name'] == 'addbutton'){
      $form_state['storage']['authors']++;
   }
  //if remove button was clicked remove the relevant fields
  else if(isset($form_state['triggering_element']) && strpos($form_state['triggering_element']['#name'],'remove-button') !== false){
        $form_state['storage']['removed'][] = $form_state['triggering_element']['#parents'][1];
        if($form_state['storage']['authors'] == 1){
          $form_state['storage']['authors'] = 2;
        }
  }

  else if(isset($form_state['triggering_element']) && strpos($form_state['triggering_element']['#name'],'addme-button') !== false){
    $addme = $form_state['triggering_element']['#parents'][1];

  }else if(!isset($form_state['triggering_element'])){
      if($node){
        $uids = get_authors($node);
        $form_state['storage']['authors'] = count($uids);
      }
  }

    $num_authors = 0;
    for ($i = 0; $i < $form_state['storage']['authors']; $i++) {
      if(in_array($i, $form_state['storage']['removed'])){
        unset($form_author['auth_add']['authors'][$i]);
        continue;
      }

      $num_authors++;

      $form_author['auth_add']['authors'][$i] = array(
        '#type' => 'fieldset',
        '#tree' => TRUE,
      );

      $form_author['auth_add']['authors'][$i]['name'] = array(
        '#title' => t('Name'),
        '#type' => 'textfield',
      );
      $form_author['auth_add']['authors'][$i]['email'] = array(
        '#title' => t('Email'),
        '#type' => 'textfield',
      );

      unset($form_author['auth_add']['authors'][$i]['email']['#value']);
      unset($form_author['auth_add']['authors'][$i]['name']['#value']);
      if(count($uids) > 0){
        $account = user_load($uids[$i]);
        $form_author['auth_add']['authors'][$i]['email']['#default_value'] = $account->mail;
        $form_author['auth_add']['authors'][$i]['name']['#default_value'] = $account->name;

      }
      if(isset($addme) && $addme == $i && !user_is_anonymous()){
        global $user;
        $form_author['auth_add']['authors'][$i]['email']['#value'] = $user->mail;
        $form_author['auth_add']['authors'][$i]['name']['#value'] = $user->name;

      }
      if(!user_is_anonymous()){
      	$form_author['auth_add']['authors'][$i]['addme'] =  array(
              '#type' => 'button',
              '#name' => 'addme-button'.$i,
              '#value' => t('add me'),
              '#href' => '',
              '#limit_validation_errors' => array(),
              '#ajax' => array(
              'callback' => '_ajax_add_author',
              'wrapper' => 'add-authors-form',
             ),
            );
     }
      $form_author['auth_add']['authors'][$i]['delete'] =  array(
              '#type' => 'button',
              '#name' => 'remove-button'.$i,
              '#value' => t('remove'),
              '#href' => '',
              '#limit_validation_errors' => array(),
              '#ajax' => array(
              'callback' => '_ajax_remove_author',
              'wrapper' => 'add-authors-form',
             ),
            );
    }

  $form_state['storage']['authors'] = $num_authors;
  $form_author['auth_add']['add_author'] = array(
    '#type' => 'button',
    '#name' => 'addbutton',
    '#value' => t('Add another author'),
    '#href' => '',
    '#limit_validation_errors' => array(),
    '#ajax' => array(
    'callback' => '_ajax_add_author',
    'wrapper' => 'add-authors-form',
   ),
  );

  $form_author['auth_add']['hline'] = array(
      '#type' => 'item',
      '#name' => 'horiline',
      '#markup' => '<hr/>',
      );
  return $form_author;
}
/**
 * ajax callback for removing author. Just regenerates the form.
 */
function _ajax_remove_author($form, &$form_state) {
    return $form['auth_add']['auth_add']['authors'];
}
/**
 * ajax callback for adding author. Just regenerates the form.
 */
function _ajax_add_author($form, &$form_state) {

  return $form['auth_add']['auth_add']['authors'];
}

/**
 * This function generates a selectable table form for displaying authors
 * The editors and eics can check authors and send them emails.
 */

function authors_table_form($form, &$form_state, $node) {
  drupal_add_js(drupal_get_path('module', 'reviewer_select') . '/authors_table_form.js');
  $uids = get_authors($node);
  foreach ($uids as $uid){
    $author = user_load($uid);

    $rows[$uid] = array('name' => $author->name);
  }

  $header = array('name' => t('Name')
  );

  $form['fset_author'] = array(
      '#title' => 'Authors',
      '#type' => 'fieldset',
  );
  $form['fset_author']['authors'] = array(
      '#type' => 'tableselect',
      '#js_select' => false,
      '#header' => $header,
      '#options' => $rows,
      '#multiple' => true,
      '#attributes' => array(),
      '#empty' => t('No authors have been added to this paper 1'),
  );
  $form['fset_author']['author_nd'] = array(
      '#type' => 'hidden',
      '#value' => $node -> nid
  );
  $form['fset_author']['author_vd'] = array(
      '#type' => 'hidden',
      '#value' => $node -> vid
  );
  $form['fset_author']['authors_email'] = array(
      '#type' => 'submit',
      '#value' => t('Compose Email'),
  );
  $form['fset_author']['#prefix'] = "<b>Authors:</b><br/>";
  $form['fset_author']['#suffix'] = "<hr/>";
  return $form['fset_author'];

}
/**
 * Assign editor form to be embeded in the node view of a paper.
 * Should be visible only to the editors in chief
 */
function assign_editor_form($form, &$form_state, $node_form, $node){

  $form['editor'] = $node_form['field_editor'];

  //unset the value fields so that the form is submitted with edited values
  //Otherwise drupal resets the field values.
  unset($form['editor']['und']['#value']);
  unset($form['editor']['custom_email_editor']['#value']);
  unset($form['editor']['editor_original']['#value']);
  $form['editor']['#weight'] = 1;
  $form['nid'] = array(
      '#type' => 'hidden',
      '#value' => $node->nid,

      );
  $form['vid'] = array(
      '#type' => 'hidden',
      '#value' => $node->vid,

      );
  $form['save'] = array(
      '#type' => 'submit',
      '#value' => 'Update Editor',
      '#weight' => 2,

      );
  /*$tids = array_keys(taxonomy_get_term_by_name('Bidding Started'));
  $bidding_started = FALSE;
  if(isset($node->field_flag['und'][0]['tid']) && $node->field_flag['und'][0]['tid'] == $tids[0]){
    $bidding_started = TRUE;
  }*/

  if(!isset($node->field_editor['und'][0]['uid'])){
  drupal_add_js(drupal_get_path('module', 'reviewer_select') . '/editor_form.js');
  $form['bidding_email'] = array(
      '#id' => 'edit-bidding-email',
      '#title' => 'Email for bidding request',
      '#type' => 'text_format',
      '#format' => 'filtered_html',
      //'#prefix' => 'Please Enter Your Review Comments',
      '#default_value' => variable_get('email_bidding_message', BIDDING_MESSAGE),
      '#cols' => 40,
      '#rows' => 5,
      '#weight' => 3,
      '#required' => TRUE,
      '#prefix' => '<div id="bidding"><hr/>',
      '#suffix' =>'<br/>'
      );
  $form['start_bidding'] = array(
      '#type' => 'submit',
      '#value' => 'Send Bidding Email',
      '#weight' => 3,
      '#suffix' => '<hr/></div>',
      );
  $form['show_bidding'] = array(
      '#type' => 'markup',
      '#markup' => '<input type="button" value="Show Bidding Form" class="form-submit form-button">',
      '#weight' => 3,
      '#prefix' => '<div id ="bidding-show"><hr/>',
      '#suffix' => '<hr/></div>',
      );
  }
  return $form;
}

/**
 * Submit action for the assign editor form
 */
function assign_editor_form_submit($form, &$form_state){
  global $user;

  if($form_state['triggering_element']['#value'] == 'Send Bidding Email'){

    $node_paper = node_load($form_state['values']['nid'], $form_state['values']['vid']);
    $sub = variable_get('email_bidding_subject', BIDDING_SUBJECT);
    $msg = $form_state['values']['bidding_email']['value'];
    $attr['message'] = replace_email_tokens($node_paper->nid, $msg);
    $attr['subject'] = replace_email_tokens($node_paper->nid, $sub);
    $attr['cc'] = get_ea_emails() . ', '.get_eic_emails();
    //$attr['Reply-to'] = 'kunal.nes+abc@gmail.com';
    $email_eb_group = variable_get('review_management_eb_email');
    //send email to editorial board
     drupal_mail('testaction', 'one-one', $email_eb_group, '', $attr);
    //sets the flag to bidding started
    rules_invoke_event('review_management_start_bidding', $node_paper);

    update_actions_table(4, $node_paper->nid, $node_paper->vid, 'Bidding Email Sent <br/>'. '<b>Email Sent<br/>To :</b> ' . $email_eb_group .'<br/><b>subject :</b> ' . $attr['subject'] . '<br/> <b>message: </b>'. $attr['message'], $user -> uid, $user->uid);
    drupal_set_message('Bidding Email Sent');
    return;
  }
  if (isset($form_state['values']['field_editor']['editor_original'])
        && $form_state['values']['field_editor']['und'][0]['uid'] != $form_state['values']['field_editor']['editor_original']) {

      //save the paper with the new editor
      $nid = $form_state['values']['nid'];
      $vid = $form_state['values']['vid'];




            $node_update = node_load($nid, $vid);
            $node_update->field_editor['und'][0]['uid'] = $form_state['values']['field_editor']['und'][0]['uid'];
            $node_update->field_editor_accepted['und'][0]['value'] = 0;
            //Save the node
            node_save($node_update);
       if(!is_null($form_state['values']['field_editor']['und'][0]['uid'])){
            $acct = user_load($form_state['values']['field_editor']['und'][0]['uid']);
            $message = $form_state['values']['field_editor']['custom_email_editor'];
            $sub = variable_get('email_editor_assn_subject', SUBMISSION_EDITOR_SUB);
            $attr['subject'] = str_replace('{{tracking_number}}', $nid . '-' . $vid, $sub);
            $attr['message'] = $message;
            $attr['cc'] = get_ea_emails() . ', '.get_eic_emails();
            drupal_mail('testaction', 'one-one', $acct -> mail, '', $attr);
            //insert into reminder table
            $d = db_insert('editor_reminder') -> fields(array(
                'nid' => $nid,
                'vid' => $vid,
                'ruid' => $acct -> uid,
                'next_reminder' => time() + variable_get('review_management_edit_reminder', 7) * 60 *60 *24,
            )) -> execute();
       }

      if($form_state['values']['field_editor']['editor_original'] != '_none'){
        db_delete('editor_reminder')
          ->condition('nid', $nid, '=')
          ->condition('vid', $vid, '=')
          ->condition('ruid', $form_state['values']['field_editor']['editor_original'], '=')->execute();
      }
      if(is_null($form_state['values']['field_editor']['und'][0]['uid'])){
        update_actions_table(4, $nid, $vid, ' Responsible Editor unassigned <br/>', $user -> uid, '');
      }else{
        update_actions_table(4, $nid, $vid, $acct-> name . ' is made the responsible editor <br/>'. '<b>Email Sent<br/>To :</b> ' . $acct->name .' ('. $acct->mail. ')  <br/><b>subject :</b> ' . $attr['subject'] . '<br/> <b>message: </b>'. $attr['message'], $user -> uid, $acct -> uid);
      }
      drupal_set_message('Responsible Editor has been assigned/changed.');
}
}

 /**
  * The form that is displayed from the actions drop down on the paper page.
  * This form is used to submit and approve a decision letter.
  */
function reviewer_decision_form($form, &$form_state) {
  global $user;
  global $base_url;
  $isEIC = is_eic_user();
  module_load_include('inc', 'node', 'node.pages');
  $node = node_load($form_state['object']->node_id);

  $form_node = drupal_get_form('submit_paper_node_form', $node);

  drupal_add_js(drupal_get_path('module', 'reviewer_select') . '/review_form.js');
  $form['decision_letter'] = array(
      '#title' => t('Decision Letter'),
      '#type' => 'fieldset',
      '#description' => t('Submit a decision letter to the Eics.')
  );
 $form['decision_letter']['accept_letter'] = array('#type' => 'hidden', '#value' => variable_get('accept_template'));
 $form['decision_letter']['major_letter'] = array('#type' => 'hidden', '#value'=> variable_get('major_template'));
 $form['decision_letter']['minor_letter'] = array('#type' => 'hidden', '#value' => variable_get('minor_template'));
 $form['decision_letter']['reject_letter'] = array('#type' => 'hidden', '#value' => variable_get('reject_template'));
 $form['decision_letter']['reject_pre_letter'] = array('#type' => 'hidden', '#value' => variable_get('reject_prescreening_template'));
  //$form['decision_letter']['status'] = $form_node['field_decision'];
  $form['decision_letter']['status']['#weight'] = 1;
  $form['decision_letter']['status']['#required'] = true;
  $form['decision_letter']['status']['#id'] = 'edit-status-12';
  $form['decision_letter']['status'] = array(
      '#title' => 'Decision/Status',
      '#type' => 'select',
      '#description' => '',
      //'#required' => TRUE,
      '#empty_value' => '',
      '#default_value' => $node->field_decision['und'][0]['value'],
      '#options' => array(
          //'_none' => t('- None -'),
          //'Awaiting Decision' => t('Awaiting Decision'),
          'Accept' => t('Accept'),
          'Minor Revision' => t('Minor Revision'),
          'Major Revision' => t('Major Revision'),
          //'Reject and Resubmit' => t('Reject and Resubmit'),
          'Reject' => t('Reject'),
          //'Reject (Pre-Screening)' => 'Reject (Pre-Screening)',
      )
  );

 /* if($isEIC){
    $form['decision_letter']['status']['#options']['Reject (Pre-Screening)'] = 'Reject (Pre-Screening)';
  }*/
  
  if($isEIC){
     $form['decision_letter']['decision_letter'] = array(
      '#title' => 'Decision Letter',
      '#description' => 'Please don\'t edit the text enclosed in paranthysis, these will be replaced automatically',
      '#id' => 'edit-field-decision-letter',
      '#type' => 'text_format',
      '#format' => 'filtered_html',
      //'#prefix' => 'Please Enter Your Review Comments',
      '#cols' => 40,
      '#rows' => 20,
      '#required' => TRUE,
      '#default_value' => $node->field_decision_letter['und'][0]['value'],
  );

  $form['decision_letter']['field_decision_letter']['#weight'] = 2;
  $form['decision_letter']['nd'] = array(
      '#type' => 'hidden',
      '#value' => $node -> nid,
  );
  
  $form['decision_letter']['approval'] = $form_node['field_approval'];
    $form['decision_letter']['subject'] = array(
        '#title' => 'Email Subject',
        '#type' => 'textfield',
        '#default_value' => replace_email_tokens($node->nid, variable_get('revise_decision_subject', REVISE_DEC_LETTER_SUB)),
        '#required' => TRUE,
        '#states' => array('visible' => array('select#edit-field-approval-und' => array('value' => 'sendback')))
        );
    $form['decision_letter']['email'] = array(
        '#title' => 'Email to editor',
        '#type' => 'textarea',
        '#format' => 1,
        '#rows' => 5,
        '#required' => TRUE,
        '#default_value' => replace_email_tokens($node->nid, variable_get('revise_decision_message', REVISE_DEC_LETTER_MSG)),
        '#states' => array('visible' => array('select#edit-field-approval-und' => array('value' => 'sendback'))),
        );
    $form['#prefix'] = '<div id="eic_decision">';
	
  }
  
  if(!$isEIC){
    $form['decision_letter']['status']['#required'] = TRUE;
  }
/*   $form['decision_letter']['templates'] = array(
         '#type' => 'markup',
         '#markup' => 'You can use the templates available <a target="_blank" href="'.$base_url.'/content/templates-decision-letters">here</a>.'
      ); */
  $form['decision_letter']['decision_letter'] = array(
      '#title' => 'Decision Letter',
      '#description' => 'Please don\'t edit the text enclosed in {{}}, these will be replaced automatically',
      '#id' => 'edit-field-decision-letter',
      '#type' => 'text_format',
      '#format' => 'filtered_html',
      //'#prefix' => 'Please Enter Your Review Comments',
      '#cols' => 40,
      '#rows' => 20,
      '#required' => TRUE,
      '#default_value' => $node->field_decision_letter['und'][0]['value'],
  );

  $form['decision_letter']['field_decision_letter']['#weight'] = 2;
  $form['decision_letter']['nd'] = array(
      '#type' => 'hidden',
      '#value' => $node -> nid,
  );

  if($isEIC && (isset($node -> field_decision['und']) && sizeof($node -> field_decision['und']) > 0)){
    $form['decision_letter']['approval'] = $form_node['field_approval'];
    $form['decision_letter']['subject'] = array(
        '#title' => 'Email Subject',
        '#type' => 'textfield',
        '#default_value' => replace_email_tokens($node->nid, variable_get('revise_decision_subject', REVISE_DEC_LETTER_SUB)),
        '#required' => TRUE,
        '#states' => array('visible' => array('select#edit-field-approval-und' => array('value' => 'sendback')))
        );
    $form['decision_letter']['email'] = array(
        '#title' => 'Email to editor',
        '#type' => 'textarea',
        '#format' => 1,
        '#rows' => 5,
        '#required' => TRUE,
        '#default_value' => replace_email_tokens($node->nid, variable_get('revise_decision_message', REVISE_DEC_LETTER_MSG)),
        '#states' => array('visible' => array('select#edit-field-approval-und' => array('value' => 'sendback'))),
        );
    $form['#prefix'] = '<div id="eic_decision">';
  }else{
    $form['#prefix'] = '<div id="editor_decision">';
  }
  $form['#suffix'] = '</div>';
  $form['decision_letter']['vd'] = array(
      '#type' => 'hidden',
      '#value' => $node -> vid,
  );
  //drupal_add_css('#edit-decision-letter fieldset { display: none; }', array('type' => 'inline')); // visually hide
  $form['decision_letter']['und'][0]['#format'] = 'filtered_html'; // provide default values

  return $form;
}
/**
 * Decision letter form submission
 * It can be submitted by the editor, that is called decision letter submission
 * Or approved by the editor in chief, approval.
 * The editor in chief may send the decision letter back to the editor for corrections/revisions.
 */
function reviewer_decision_form_submit($form, $form_state) {
  global $user;
  $node = node_load($form_state['values']['nd'], $form_state['values']['vd']);
  $node -> field_decision['und'][0]['value'] = $form_state['values']['status'];
  $notify = 0;

  if(isset($form_state['input']['field_approval']['und']) && ($form_state['input']['field_approval']['und'] == 'sendback')){
      $params['subject'] = $form_state['values']['subject'];
      $params['message'] = $form_state['values']['email'];
      //update field approaval;
      $responsible_editor = user_load(get_responsible_editor($node));
      $node -> field_approval['und'][0]['value'] = $form_state['input']['field_approval']['und'];
      drupal_mail('testaction', 'one-one', $responsible_editor -> mail, '', $params);
      update_actions_table(3, $form_state['values']['nd'], $form_state['values']['vd'], 'Decision Letter sent back to editor', $user -> uid, '');
      drupal_set_message('Decision letter sent back to Editor.');
      $notify = 2;
  }
  else if(isset($form_state['input']['field_approval']['und']) && ($form_state['input']['field_approval']['und']!='_none')){
    $notify = 1;
    $node -> field_approval['und'][0]['value'] = $form_state['input']['field_approval']['und'];
    $node -> taxonomy_vocabulary_1['und'][0]['tid'] = 2;
  }


  $node -> field_decision_letter['und'][0]['value'] = $form_state['values']['decision_letter']['value'];

  node_save($node);

  if($notify == 0){
    db_delete('editor_reminder')
          ->condition('nid', $form_state['values']['nd'], '=')
          ->condition('vid', $form_state['values']['vd'], '=')
          ->execute();

    update_actions_table(3, $form_state['values']['nd'], $form_state['values']['vd'], 'Decision Letter Submitted By Editor', $user -> uid, $form_state['values']['decision_letter']['value']);
    notifyEicMSG('eic_decision', $node);

    drupal_set_message(t('Decision Letter has been sent to the EICs for approval'));
  }else if ($notify == 1){

    update_actions_table(3, $form_state['values']['nd'], $form_state['values']['vd'], 'Decision Letter has been approved', $user -> uid, $form_state['values']['decision_letter']['value']);
    drupal_set_message(t('The decision letter has been approved.'));
  }
}



/**
 * redirect the call to email_form
 */
function authors_table_form_submit($form, &$form_state) {
  $authors = $form_state['values']['authors'];
  $redirect = 'swj/email';

  $auths = "";

  foreach ($authors as $key => $val) {
    if($val == 0)continue;

    if($auths != ''){
      $auths .= ',' . $val;
    }else {
      $auths .= $val;
    }

  }

  $redirect .= '/' . $form_state['input']['author_nd'] . '/' . $form_state['input']['author_vd'] . '/' . $auths;
  $form_state['redirect'] = $redirect;
}

/**
 * This function returns a form that is used to display the invite reviewer functionality
 * The form is accessible from the actions drop down on paper view page.
 * Invite reviewer not present in the system.
 */

function reviewer_invite_form($form, &$form_state) {
  global $user;
  $node = node_load($form_state['object']->node_id);
  $form['rev_invite'] = array(
      '#title' => 'Invite a Reviewer Not Present in the System',
      '#type' => 'fieldset',
      '#description' => 'Invite additional reviewers that are not in the system.'
  );
  $form['rev_invite']['invite_fname'] = array(
      '#title' => 'Full Name',
      '#type' => 'textfield',
      '#size' => 'small',
      '#required' => true
  );
  $form['rev_invite']['invite_email'] = array(
      '#title' => 'Email',
      '#type' => 'textfield',
      '#size' => 'small',
      '#required' => true
  );
  $body = replace_email_tokens($node->nid, variable_get('email_reviewer_new_assn_message', REVIEWER_ASSIGNMENT_MSG_NEW));

  $form['rev_invite']['email_text'] = array(
      '#type' => 'textarea',
      '#rows' =>15,
      '#title' => t('Email Text'),
      '#description' => t('The fillers enclosed in {{}} will be automatically replaced.'),
      '#required' => false,
      '#default_value' => $body
  );
  $form['rev_invite']['invite_nd'] = array(
      '#type' => 'hidden',
      '#value' => $node -> nid
  );
  $form['rev_invite']['invite_vd'] = array(
      '#type' => 'hidden',
      '#value' => $node -> vid
  );

  return $form;
}

/**
 * Validates the reviewer invite form
 * If the reviewer email id matches with that of an existing user error message is displayed.
 */
function reviewer_invite_form_validate($form, $form_state) {
  module_load_include('module', 'email_verify', 'email_verify');

  if(!valid_email_address($form_state['values']['invite_email'])){
    form_set_error('invite_email', 'Invalid email address');
  }
  if($error = email_verify_check($form_state['values']['invite_email'])){
    form_set_error('invite_email', $error);
  }
  $name = $form_state['values']['invite_fname'];

  $d = db_query("SELECT count(uid) FROM {users} where name = :name or mail = :mail", array(
      ':name' => $name,
      ':mail' => $form_state['values']['invite_email']
  )) -> fetchField();

  if ($d > 0) {
    form_set_error('rev_invite', t('User already exists!'));
  }
}

/*
 * The submit function for invite reviewer form
 */
function reviewer_invite_form_submit($form, &$form_state) {
  global $user;
  if ($form_state['values']['invite_fname']
      && $form_state['values']['invite_email']) {

    $name = $form_state['values']['invite_fname'];
    $account = createUser($form_state['values']['invite_email'], $name, 1);

    if ($account) {
      $node = node_load($form_state['values']['invite_nd'], $form_state['values']['invite_vd']);
      //read from config
      $reminder = variable_get('review_management_review_reminder', 7) * 24 * 60 * 60 ;
      $d = db_insert('paper_reviewer') -> fields(array(
          'nid' => $node -> nid,
          'vid' => $node -> vid,
          'ruid' => $account -> uid,
          'accept' => 0,
          'added' => REQUEST_TIME,
          'submitted' => 0,
          'next_reminder' => time() + $reminder
      )) -> execute();

      $body = $form_state['values']['email_text'];
      $body = str_replace('{{reviewer}}', $account -> name, $body);
      $body = str_replace('{{confirm_url}}', url('swj/verify/' . $node -> nid . '/' . $node -> vid . '/' . $account -> uid, array('absolute' => TRUE)), $body);

      $params['subject'] = str_replace('{{tracking_number}}', $node -> nid . '-' . $node -> vid, variable_get('email_reviewer_new_assn_subject', REVIEWER_ASSIGNMENT_SUB_NEW));
      $params['Reply-to'] = $user->mail;
      $params['cc'] = $user->mail;
      $token = get_token($account);
      $direct_url = url(drupal_get_path_alias('node/' . $node -> nid), array('absolute' => TRUE, 'query' => array('l' => $token)));
      $body = str_replace('{{direct_url}}', $direct_url, $body);

      $params['message'] = $body;
      drupal_mail('testaction', 'one-one', $account -> mail, '', $params);
      update_actions_table(2, $node->nid, $node->vid, 'Reviewer Invited to paper: ' . $account -> name, $user -> uid, '');

      //Delete from reminders for the editor
      $euid = get_responsible_editor($node);
      db_delete('editor_reminder')
      ->condition('nid', $node->nid, '=')
      ->condition('vid', $node->vid, '=')
      ->condition('ruid', $euid, '=')->execute();


      drupal_set_message(t('User successfully invited.'));
    } else {
      form_set_error('rev_invite', t('User creation failed.'));
    }
  }

}

/**
 * This form displays the table of selected reviewers
 * With status of there review activity for this paper.
 * The form allows deletion of reviewer and sending emails.
 */
function selectedrev_form($form, &$form_state,$node) {
  global $base_url;
  ctools_include('modal');
  ctools_include('ajax');
  drupal_add_js(drupal_get_path('module', 'reviewer_select') . '/review_form.js');
  $form['delete'] = array(
      '#type' => 'button',
      '#value' => t('deletebutton'),
      '#ajax' => array(
          'callback' => 'ajax_reviewer_entry_delete',
          'wrapper' => 'div_two',
          'method' => 'replace',
          'effect' => 'fade',
      )
  );
  $form['nd'] = array(
      '#type' => 'hidden',
      '#value' => $node -> nid,
  );
  $form['vd'] = array(
      '#type' => 'hidden',
      '#value' => $node -> vid,
  );
  $form['delete_reviewer'] = array('#type' => 'hidden', );

  $reviewing_acceptance = array(
      0 => 'No Response',
      1 => 'Accepted Invitation',
      2 => 'Declined Invitation',
      3 => 'Deleted',
      4 => 'Submitted Review'
  );
  if (is_array($node)) {
    $nid = $node['nid'];
    $vid = $node['vid'];
  } else {
    $nid = $node -> nid;
    $vid = $node -> vid;
  }

  $node_loaded = node_load($nid, $vid);
  $results = get_reviewers($node_loaded);

  $header = array(
      'name' => array(
          'data' => t('Username'),
          'field' => 'u.name'
      ),
     'added on' => array(
          'data' => t('Added On'),
          'field' => 'p.added'
      ),
      'agreed' => array('data' => t('Status')),
      'delete' => array('data' => t('Delete')),
  );
  $rows = array();

  $count = 0;
  foreach ($results as $result) {
    $a = 'N';
    if ($result['accept'] == 1) {
      $a = 'Y';
    }

    if ($result['accept'] != 3) {
      $href = '<a href="#" class="delete_reviewer" id="rev-' . $result['uid'] . '">&#10008;</a>';
    } else {
      $href = '';
    }
    if($result['submitted'] ==1){
      $result['accept'] = 4;
    }
    //$last_reminder = date('d/M/Y', $result['last_reminder']) == '31/Dec/1969' ? 'N/A' : date('d/M/Y', $result['last_reminder']);
    //$next_reminder = $result['next_reminder'] == 0 ? 'N/A' : date('d/M/Y', $result['next_reminder']);
    $rows[] = array(
        //'name' => $result['name'] . ' [[<a href="' . $base_url . '/swj/email/' . $nid . '/' . $vid . '/' . $result['uid'] . '">email</a> ]] [['. ' <a href="' .$base_url . '/swj/rev_rem/'. $nid . '/'. $vid . '/'. $result['uid']. '">send reminder</a>]]',
    'name' => $result['name'] . ' [[<a href="' . $base_url . '/swj/email/' . $nid . '/' . $vid . '/' . $result['uid'] . '">email</a> ]]',
        'added on' => date('d/M/Y', $result['added']),
        'agreed' => $reviewing_acceptance[$result['accept']],
                    /* '<b>Response to Invitation</b>: ' . $reviewing_acceptance[$result['accept']]. '<br/>'.
                    '<b>Last Reminder</b>: ' .$last_reminder. '<br/>'.
                    '<b>Next Reminder</b>: ' .$next_reminder */
        'delete' => $href
    );

    $count++;
  }
  $build['form_thisone'] = $form;
  $build['reviewer_table'] = array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $rows,
      '#attributes' => array(),
      '#caption' => '<b>Solicited Reviewers:</b> (Reviewers that have been added to the system)',
      '#empty' => t('No Reviewer has been added to this paper'),

  );
  $txt ="";
  //$txt = render(ctools_modal_text_button(t('Configure review reminders'), $base_url.'/swj/nojs/rev_reminder/'.$nid, t('Configure review reminders'),  'ctools-modal-ctools-sample-style'));


  $ur = url('swj/tags_setting/out_review/' . $node -> nid , array('absolute' => TRUE));
  $build['#prefix'] ='<div id="div_two">';
  $build['#suffix'] ='</div><a href="' . $ur .
  '"><b>Mark out for review</b></a> (Denotes that the all required reviewers have been added to the paper)'.
   '<br/> '.$txt;

  return $build;
}

/**
 * Ajax callback to delete reviewer.
 */
function ajax_reviewer_entry_delete($form, $form_state, $reset) {
  $d = 0;
  if ($form_state['values']['delete_reviewer']) {
    $d = db_update('paper_reviewer')
    ->condition('nid', $form_state['values']['nd'])
    ->condition('vid', $form_state['values']['vd'])
    ->condition('ruid', $form_state['values']['delete_reviewer'])
    ->fields(array('accept' => 3, 'next_reminder' => 0))
    ->execute();
  }
  if ($d != 0) {
    drupal_set_message(t('Reviewer successfully deleted.'));
    $reviewer = user_load($form_state['values']['delete_reviewer']);
    global $user;
    update_actions_table(2, $form_state['values']['nd'], $form_state['values']['vd'], 'Reviewer removed from paper: ' . $reviewer -> name, $user -> uid, $reviewer -> uid);
  } else {
    drupal_set_message(t('Reviewer could not be deleted.'));
  }

  $form = drupal_get_form('selectedrev_form', node_load($form_state['values']['nd']));
  //$str = "<div id=\"div_two\">" . render($form) . "</div>";
  return render($form);
}


/**
 * The form for review submission
 * This form opens in two modes
 * 1. For a reviewer to submit a review as usual
 * 2. For a responsible editor or EIC to submit review on a reviewer's behalf.
 */
function review_form($form, &$form_state, $node=null, $user, $type = "") {
  if(isset($form_state['node']) && isset($form_state['type'])){
    $node = node_load($form_state['object']->node_id);
    $type = $form_state['type'];
  }

  drupal_add_js(drupal_get_path('module', 'reviewer_select') . '/review_form.js');
  $form['fset_review'] = array(
      '#title' => 'Add Review',
      '#type' => 'fieldset',
  );

  if ($type == 'admin') {
    $form['fset_review']['#description'] = "You can submit a review on behalf of a reviewer. Please use the reviewer dropdown to select the reviewer. NOTE: Reviewers who have already submitted a review don't appear in the dropdown.";
    $sql = 'select ruid, name from {paper_reviewer} p,{users} u where nid = :nid and p.ruid = u.uid and u.uid not in (select uid from paper_review where nid = :nid) and accept in (0,1)';

    $results = db_query($sql, array(':nid' => $node -> nid));
    $options = array();
    foreach ($results as $res) {
      $options[$res -> ruid] = $res -> name;
    }
    if (sizeof($options) == 0) {
      return $form;
    }
    $form['fset_review']['reviewer'] = array(
        '#title' => 'Reviewer',
        '#type' => 'select',
        '#description' => '',
        '#required' => True,
        '#empty_value' => '',
        '#options' => $options
    );
  }

  if($type == 'admin_edit'){
    $form['fset_review']['reviewer'] = array(
        '#title' => 'Reviewer',
        '#type' => 'hidden',
        '#default_value' => $user->uid,

    );
  }


  $form['fset_review']['comment_for_edit'] = array(
      '#title' => '<b>Comments For Editor Only</b><br/>',
      '#type' => 'text_format',
      '#format' => 'filtered_html',
      '#title_display' => 'before',
      '#description' => '(Please use this box only for comments that you want to be withheld from authors. Use as many lines as needed.)',
      '#cols' => 40,
      '#rows' => 10,
  );
  //overall rating field


  $form['fset_review']['notice'] = array(
       '#title' => '',
       '#type'  => 'markup',
       '#markup' => '<br/>EVERYTHING BELOW THIS LINE WILL BE RETURNED TO THE AUTHORS<br/><hr/>',

      );
  if(is_closed_system()){
    $form['fset_review']['anonym'] = array(
      '#title' => 'Anonymous',
      '#type' => 'hidden',
      '#value' => 0,
     );
  }else{
    $form['fset_review']['anonym'] = array(
        '#title' => '<b>Reviewer\'s Name</b> (note that, as a journal\'s policy, we encourage open reviews as a default. Select "Remain anonymous" if you don\'t want your identity to be revealed to authors)' ,
        '#type' => 'checkboxes',
        '#options' => array('anonymous' => 'Remain Anonymous'),
        '#description' => 'If you check this option your name will not be disclosed.'
    );
  }
  $form['fset_review']['impression'] = array(
       '#title' => '<b>Overall impression</b>',
       '#type'  => 'select',
       '#description' => 'Please indicate your overall impression of the paper.',
       '#options' => get_impression_options(),
       '#required' => TRUE,
      );
  $form['fset_review']['suggestion'] = array(
      '#title' => '<b>Suggested decision</b>',
      '#type' => 'select',
      '#description' => '',
      '#required' => TRUE,
      '#empty_value' => '',
      '#options' => array(
          'accept' => t('Accept'),
          'minor' => t('Minor revision'),
          'major' => t('Major revisions'),
          'rej resub' => t('Reject and resubmit'),
          'reject' => t('Reject')
      )
  );
  $form['fset_review']['content'] = array(
       '#title' => '<b>CONTENT</b>',
       '#type'  => 'markup',
       '#markup' => '<b>CONTENT</b>',

      );
    $form['fset_review']['quality'] = array(
       '#title' => '<b>Technical Quality of the paper</b>',
       '#type'  => 'radios',
       '#attributes' => array('class' => array('container-inline')),
       '#required' => TRUE,
       '#empty_value' => '',
       '#options' => array(
          'Excellent' => t('Excellent'),
          'Good' => t('Good'),
          'Average' => t('Average'),
          'Weak' => t('Weak'),
          'Bad' => t('Bad'),
          'Don\'t know' => t('Don\'t Know'),
      )

      );
    $form['fset_review']['originality'] = array(
       '#title' => '<b>Originality of the paper</b>',
       '#type'  => 'radios',
       '#attributes' => array('class' => array('container-inline')),
       '#required' => TRUE,
       '#empty_value' => '',
       '#options' => array(
          'Yes' => t('Yes'),
          'Yes, but limited' => t('Yes, but limited'),
          'No' => t('No'),
      )
      );
    $form['fset_review']['bib_adequacy'] = array(
       '#title' => '<b>Adequacy of the bibliography</b>',
       '#type'  => 'radios',
       '#attributes' => array('class' => array('container-inline')),
       '#required' => TRUE,
       '#empty_value' => '',
       '#options' => array(
          'Yes' => t('Yes'),
          'Yes, but see detailed comments' => t('Yes, but see detailed comments'),
          'No' => t('No'),
      )
      );
    $form['fset_review']['presentation'] = array(

       '#type'  => 'markup',
       '#markup' => '<b>PRESENTATION</b>',

      );

    $form['fset_review']['abstract'] = array(
       '#title' => '<b>Adequacy of the abstract</b>',
       '#type'  => 'radios',
       '#attributes' => array('class' => array('container-inline')),
       '#required' => TRUE,
       '#empty_value' => '',
       '#options' => array(
          'Yes' => t('Yes'),
          'No' => t('No'),

      )
      );
    $form['fset_review']['background'] = array(
       '#title' => '<b>Introduction:  background and motivation </b>',
       '#type'  => 'radios',
       '#attributes' => array('class' => array('container-inline')),
       '#required' => TRUE,
       '#empty_value' => '',
       '#options' => array(
          'Good' => t('Good'),
          'Limited' => t('Limited'),
          'Bad' => t('Bad'),
      )

      );
    $form['fset_review']['organization'] = array(
       '#title' => '<b>Organization of the paper </b>',
       '#type'  => 'radios',
       '#attributes' => array('class' => array('container-inline')),
       '#required' => TRUE,
       '#empty_value' => '',
       '#options' => array(
          'Satisfactory' => t('Satisfactory'),
          'Needs improvement' => t('Needs improvement'),
          'Poor' => t('Poor'),
      )

      );
    $form['fset_review']['english'] = array(
       '#title' => '<b>Level of English</b>',
      '#type'  => 'radios',
       '#attributes' => array('class' => array('container-inline')),
       '#required' => TRUE,
       '#empty_value' => '',
       '#options' => array(
          'Satisfactory' => t('Satisfactory'),
          'Unsatisfactory' => t('Unsatisfactory'),

      )

      );

    $form['fset_review']['overall_presentation'] = array(
       '#title' => '<b>Overall presentation</b>',
      '#type'  => 'radios',
       '#attributes' => array('class' => array('container-inline')),
       '#required' => TRUE,
       '#empty_value' => '',
       '#options' => array(
          'Excellent' => t('Excellent'),
          'Good' => t('Good'),
          'Average' => t('Average'),
          'Weak' => t('Weak'),
          'Bad' => t('Bad'),
      )

      );

     $form['fset_review'] ['review_upload'] = array(
          '#title' => t('Upload the document(optional)'),
         	'#type' => 'managed_file',
	//	'#required' => 'TRUE',
        '#upload_location' => 'private://review_document/',
		'#default_value' => $review_upload,
        '#description' => t('Supports only .pdf .doc .docx .zip files'),
         '#upload_validators' => array(
        'file_validate_extensions' => array('pdf doc docx zip'),
	   	 
      ),
    );
	




  $form['fset_review']['review_comments'] = array(
      '#title' => '<b>Detailed Comments</b>',
      '#type' => 'text_format',
      '#format' => 'filtered_html',
      //'#prefix' => 'Please Enter Your Review Comments',
      '#cols' => 40,
      '#rows' => 10,
      '#required' => TRUE,
  );

  $form['fset_review']['nd'] = array(
      '#type' => 'hidden',
      '#value' => $node -> nid,
  );
  $form['fset_review']['vd'] = array(
      '#type' => 'hidden',
      '#value' => $node -> vid,
  );



  $form['fset_review']['#prefix']= "<div id=\"review_form\">";
  $form['fset_review']['#suffix'] = "</div>";
  if ($type != 'admin' && $type != 'admin_edit') {
    $form['fset_review']['submit'] = array(
        '#title' => 'Submit',
        '#type' => 'submit',
        '#value' => t('Submit Review'),
        '#prefix' => '<br/>',

    );
  }
  drupal_add_css('#edit-fset-review--2 fieldset { display: none; }', array('type' => 'inline'));
  drupal_add_css('#edit-fset-review fieldset { display: none; }', array('type' => 'inline'));

  return $form;
}

/**
 * Ajax callback for submit review
 */
function ajax_sub_review_callback($form, $form_state) {
  $str = review_submit($form, $form_state);
  return $str;
}

/**
 * Function for updating reviews
 * @param unknown_type $isNew
 * @param unknown_type $form_state
 */
function update_review($isNew, $form_state, $reviewer){
   $anonm = 0;
    $test = $form_state['values']['anonym']['anonymous'];
    if (is_string($test)) {
      $anonm = 1;
    }
    if($isNew){
        $d = db_insert('paper_review') -> fields(array(
      'nid' => $form_state['values']['nd'],
      'uid' => $reviewer -> uid,
      'vid' => $form_state['values']['vd'],
      'created' => REQUEST_TIME,
      'comment' => $form_state['values']['review_comments']['value'],
      'comment_format' => $form_state['values']['review_comments']['format'],
      'p_comment' => $form_state['values']['comment_for_edit']['value'],
      'p_comment_format' => $form_state['values']['comment_for_edit']['format'],
      'anon' => $anonm,
      'suggestion' => $form_state['values']['suggestion'],
      'impression' => $form_state['values']['impression'],
      'technical_quality' => $form_state['values']['quality'],
      'originality' => $form_state['values']['originality'],
      'bibliography' => $form_state['values']['bib_adequacy'],
      'abstract_adequacy' => $form_state['values']['abstract'],
      'introduction' => $form_state['values']['background'],
      'organization' => $form_state['values']['organization'],
      'english' => $form_state['values']['english'],
      'presentation' => $form_state['values']['overall_presentation'],
      'review_attachment' => $form_state['values']['review_upload'],


        )) -> execute();

        $query = db_update('paper_reviewer') -> fields(array(
            'accept' => 1,
            'submitted' => 1,
            'next_reminder' => 0
        )) -> condition('nid', $form_state['values']['nd'], '=') -> condition('vid', $form_state['values']['vd'], '=') -> condition('ruid', $reviewer->uid, '=') -> execute();

    }else{
      db_update('paper_review')
         ->condition('nid', $form_state['values']['nd'], '=')
         ->condition('vid', $form_state['values']['vd'], '=')
         ->condition('uid', $reviewer->uid, '=')
         -> fields(array(
                'comment' => $form_state['values']['review_comments']['value'],
                'comment_format' => $form_state['values']['review_comments']['format'],
                'p_comment' => $form_state['values']['comment_for_edit']['value'],
                'p_comment_format' => $form_state['values']['comment_for_edit']['format'],
                'anon' => $anonm,
                'suggestion' => $form_state['values']['suggestion'],
                'impression' => $form_state['values']['impression'],
                'technical_quality' => $form_state['values']['quality'],
                'originality' => $form_state['values']['originality'],
                'bibliography' => $form_state['values']['bib_adequacy'],
                'abstract_adequacy' => $form_state['values']['abstract'],
                'introduction' => $form_state['values']['background'],
                'organization' => $form_state['values']['organization'],
                'english' => $form_state['values']['english'],
                'presentation' => $form_state['values']['overall_presentation'],
                'review_attachment' => $form_state['values']['review_upload'],


        )) -> execute();
    }
}
/**
 * Form to submit review
 */
function review_submit($form, $form_state) {
  global $user;

  $count = db_query('Select count(*) from paper_review where nid=' . $form_state['values']['nd'] . ' and uid=' . $user -> uid . ' and vid=' . $form_state['values']['vd']) -> fetchField;
  if ($count == 1) {
    drupal_set_error(t('Review previously submitted, please refresh page.'));
    return "";
  }

  update_review(TRUE, $form_state, $user);

  $node_accessed = node_load($form_state['values']['nd'], $form_state['values']['vd']);

  $euid = get_responsible_editor($node_accessed);
  update_review_status($node_accessed, $user);
  $header = array('name' => array('data' => t('Your Review Comment')));
  $rows = array();

  $rows[] = array('name' => '<p><b>Suggested Decision: </b>  ' . get_decision_from_key($form_state['values']['suggestion']) .
                  '</p><b>Review Comment: </b><br/>' . check_markup($form_state['values']['review_comments']['value'], $form_state['values']['review_comments']['format']) .
                  '</p><p><b>Comment for editor: </b><br/>' . check_markup($form_state['values']['comment_for_edit']['value'], $form_state['values']['comment_for_edit']['format']).
                  '</p><p><b>Submitted on: </b><br/>' .  date('d/M/Y', REQUEST_TIME) . '</p>', );

  $build['reviewer_table'] = array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $rows,
      '#attributes' => array(),
  );


  drupal_set_message(t('Review has been successfully submitted.'));
  return "<div id=\"review\">" . render($build) . "</div>";
}

/**
 * Review form submission
 */
function review_form_submit($form, &$form_state) {
  global $user;
  $form_state['node'] = node_load($form_state['values']['nd']);
  if(isset($form_state['values']['reviewer'])){
    $form_state['object']->reviewer = $form_state['values']['reviewer'];
  }
  $uid = isset($form_state['values']['reviewer'])? $form_state['values']['reviewer']: $user->uid;
  //global $user;
  $count = db_query('Select count(*) from paper_review where nid=' . $form_state['values']['nd'] . ' and uid=' . $uid . ' and vid=' . $form_state['values']['vd'])->fetchField();

  if ($count == 1) {
    form_set_error('', t('Review previously submitted, please refresh page.'));
    //return "";
  }
  drupal_set_message("Review submitted successfully");
  $reviewer = user_load($uid);
  update_review(TRUE, $form_state, $reviewer);

  $node_accessed = node_load($form_state['values']['nd'], $form_state['values']['vd']);
  $euid = get_responsible_editor($node_accessed);
  update_review_status($node_accessed, $reviewer);

}

/**
 * Sets flags, sends email to editor.
 */
function update_review_status($node, $reviewer){
    global $user;
    $params['subject'] = str_replace('{{tracking_number}}', $node -> nid . '-' . $node -> vid, variable_get('email_review_rec_subject', REV_SUBMIT_SUB));
    $msg = replace_email_tokens($node->nid, variable_get('email_review_rec_message', REVIEW_SUBMIT_MSG));
    $msg = str_replace('{{reviewer}}', $reviewer->name ,$msg);
    $msg = str_replace('{{review}}', get_review_html($node, $reviewer), $msg);
    $params['message'] = $msg;
    $editor = user_load(get_responsible_editor($node));
    drupal_mail('testaction', 'one-one', $editor->mail, '', $params);

    $tids = array_keys(taxonomy_get_term_by_name('Out For Review'));
    if($node->field_flag['und'][0]['tid'] == $tids[0]){
        $nbr_rev = db_query("SELECT count(ruid) FROM {paper_reviewer} where nid = :nid and vid = :vid and accept in (0,1)", array(
      ':nid' => $node->nid,
      ':vid' => $node->vid,
      )) -> fetchField();
      $nbr_rev_submitted = db_query("SELECT count(ruid) FROM {paper_reviewer} where nid = :nid and vid = :vid and submitted = 1 and accept in (0,1)", array(
          ':nid' => $node->nid,
          ':vid' => $node->vid,
      )) -> fetchField();

      if($nbr_rev == $nbr_rev_submitted){
        $revtags = array_keys(taxonomy_get_term_by_name('Review Received'));
        $node->field_flag['und'][0]['tid'] = $revtags[0];
        node_save($node);
        $params['cc'] = get_ea_emails().', '.get_ea_emails();
        $params['subject'] = str_replace('{{tracking_number}}', $node-> nid . '-' . $node -> vid, variable_get('email_min_rev_subject', REV_DEC_EDITOR_SUB));
        $params['message'] = replace_email_tokens($node->nid,variable_get('email_min_rev_subject_message', REV_DEC_EDITOR_MSG));
        drupal_mail('testaction', 'one-one', $editor -> mail, '', $params);
      }
    }

    update_actions_table(2, $node->nid, $node->vid, 'Reviewer submitted review', $user->uid, '');

}

/** Form to embed hide reviews functionality
 *  The editors and eics can choose to hide reviews for a given paper.
 *
 */
function form_hide_reviews($form, &$form_state, $node){
  $form['nid'] = array(
      '#type' => 'hidden',
      '#value' => $node->nid,
      );
  $form['vid'] = array(
      '#type' => 'hidden',
      '#value' => $node->vid,
      );
  $val = 'Hide Reviews';
  if(isset($node->field_hidereviews['und']) && $node->field_hidereviews['und'][0]['value'] == 1){
    $val = 'Show Reviews';
  }
  $form['hide'] = array(
      '#type' => 'submit',
      '#value' => $val,
      );
  return $form;
}
/**
 * Submit function for hide reviews
 * sets field_hidereviews, if this is set then reviews are hidden from the anonymous users.
 */
function form_hide_reviews_submit($form, &$form_state){
    $node = node_load($form_state['values']['nid'], $form_state['values']['vid'], true);

    if(isset($node->field_hidereviews['und']) && $node->field_hidereviews['und'][0]['value'] == 0){
      $node->field_hidereviews['und'][0]['value'] = 1;
    }else{
      $node->field_hidereviews['und'][0]['value'] = 0;
    }
    node_save($node);
}

/**
 * Lets the editor decide if the reviewers should see the cover letter
 * Check box display right below the cover letter field on the paper view page.
 */
function allow_cover_letter_form($form, &$form_state, $node_form, $node){
  $form['allow_cover'] = $node_form['field_show_cover_letter'];
  unset($form['allow_cover']['und']['#value']);
  $form['allow_cover']['#weight'] =1;
  $form['allow_cover']['description'] = "";
  $form['nid'] = array(
      '#type' => 'hidden',
      '#value' => $node->nid,

      );
  $form['vid'] = array(
      '#type' => 'hidden',
      '#value' => $node->vid,

      );
/*   $form['save'] = array(
      '#type' => 'submit',
      '#value' => 'Update',
      '#weight' => 2,

      ); */
  $form['#prefix'] = '<div id="cv_form">';
  $form['#suffix'] = '</div>';
  return $form;
}

/**
 * Form submit for allow conver letter
 * sets field_show_cover_letter value
 */
function allow_cover_letter_form_submit($form, &$form_state){
  $node = node_load($form_state['values']['nid']);

  if($form_state['values']['field_show_cover_letter']['und'][0]['value'] == 1){
    $node->field_show_cover_letter['und'][0]['value'] = 1;
  }else{
    $node->field_show_cover_letter['und'][0]['value'] = 0;
  }
  node_save($node);
}

