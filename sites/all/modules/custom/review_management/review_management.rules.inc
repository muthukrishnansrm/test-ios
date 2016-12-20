<?php

/**
 * Event Info implementation
 */

function review_management_rules_event_info(){
  $events = array();

  $events['review_management_start_bidding'] = array(
          'label' => t('Sends the bidding email'),
          'group' => t('Review Management'),
          'variables' => array(
                 'paper_node' => array(
                     'type' => 'node',
                     'label' => t('Node Object'),
                     ),
              )
        );
  return $events;
}

/**
 * hook_rules_action_info implementation
 * Provides actions for review management system
 * review_management_set_author_reference - Used to set the author references.
 */
function review_management_rules_action_info(){

  $actions = array(
      'review_management_paper_submitted' => array(
          'label' => t('Do tasks for paper submission, emails. Only to be used with node creation'),
          'group' => t('Review Management'),
          'parameter' => array(
              'node' => array(
                  'type' => 'node',
                  'label' => t('The node that is submitted'),
              ),
          ),
      ),
      'review_management_decision_made' => array(
            'label' => t('Send emails notifying decision'),
            'group' => t('Review Management'),
            'parameter' => array(
              'node' => array(
                  'type' => 'node',
                  'label' => t('The node that is submitted'),
              ),
          ),
       ),
      'review_management_delete_blocked_users' => array(
         'label' => t('Delete users who are inactive and blocked for more than 30 days'),
         'group' => t('Review Management'),
       ),
      'review_management_update_authors_swj' => array(
          'label' => t('Update old author references to be used carefully'),
          'group' => t('Review Management'),
          ),
      'review_management_automatic_reminder' => array(
         'label' => t('This rule sends reminder emails to reviews and editors'),
         'group' => t('Review Management'),
       ),
  );

  return $actions;
}

function review_management_update_authors_swj(){

  $type = "submit_paper";
  $nodeQuery = new EntityFieldQuery();
  $nodeQuery->entityCondition('entity_type', 'node')
    ->propertyCondition('type', 'submit_paper')
    ->propertyOrderBy('changed');
  $nodes = $nodeQuery->execute();
  $nids = array_keys($nodes['node']);

 /*  foreach($nids as $nid){
    $node = node_load($nid);
    watchdog('Title of the node', $node->title);

  } */

   foreach($nids as $nid){

    $node = node_load($nid);
    $authors = $node -> field_author;
    $temp_entity_ids = array();

    //Sanity check if the field author is set for the paper
    //For paper submission we use the field_author field which is a field collection.
    if (isset($node -> field_author['und'])) {
      foreach ($node->field_author['und'] as $a) {
        // fetch the value of the field using the field api.
        $field_value = field_view_value('node', $node, 'field_author', $a, array());

        foreach ($field_value['entity']['field_collection_item'] as $key => $result) {
          $emailString = $result['field_mail'][0]['#markup'];
          $fullName = $result['field_fullname'][0]['#markup'];

        }

        //load user by email
        if($fullName != ''){
          $account = user_load_by_name($fullName);//($emailString);
          $node_updated = node_load($node->nid, $node->vid, true);
          $node_updated->field_authors_ref['und'][] = array('uid' => $account->uid);
          node_save($node_updated);
        }

      }
    }
  }
  drupal_set_message('Papers updated with authors: '. count($nids));
}


/**
 * Function to send review reminders
 */
function review_management_review_reminder($node){
//get the paper with tags under review
//for each such paper get the list of reviewers who have accept as 0,1 and submitted as 0
//send reminders after x days of inactivity. difference between current day and date the reviewer was added.
}


/**
 * Does the notifications when the decision is made about a paper.
 */
function review_management_decision_made($node){

  //delete from editor reminder
    db_delete('editor_reminder')
          ->condition('nid', $node->nid, '=')
          ->condition('vid', $node->vid, '=')
          ->execute();

   //remove review reminders
   $d = db_update('paper_reviewer') -> condition('nid', $node -> nid) -> condition('vid', $node -> vid)  -> fields(array('next_reminder' => 0 )) -> execute();
  //Send email to authors.
  //$emails = get_author_emails($node);

  $authors = get_authors($node);
  foreach($authors as $x => $author){
      $auth = user_load($author);
      $params['subject'] = replace_email_tokens($node->nid, variable_get('email_author_dec_subject', REV_DEC_APR_SUB));
      $msg = variable_get('email_author_dec_message', REV_DEC_APR_MSG);
      $msg = str_replace('{{decision_letter}}', $node -> field_decision_letter['und']['0']['value'], $msg);
      $msg = replace_email_tokens($node->nid, $msg);
      $token = get_token($auth);
      $direct_url = url(drupal_get_path_alias('node/' . $node -> nid), array('absolute' => TRUE, 'query' => array('l' => $token)));
      $msg = str_replace('{{direct_url}}', $direct_url, $msg);
      $params['message'] = $msg;
      $params['cc'] = get_eic_emails();
      drupal_mail('testaction', 'one-one', $auth->mail, '', $params);
  }

  //Send email to editor
        $editorobj = user_load(get_responsible_editor($node));
		$params = array();
		$params['subject'] = str_replace('{{tracking_number}}', $node -> nid . '-' . $node -> vid, variable_get('email_editor_dec_subject', REV_DEC_APR_EDITOR_SUB));
		$msg = replace_email_tokens($node->nid, variable_get('email_editor_dec_message', REV_DEC_APR_EDITOR_MSG));
		$params['message'] = $msg;
		drupal_mail('testaction', 'one-one', $editorobj -> mail, '', $params);
  //send email to reviewers
		$reviewers = db_query('select ruid from paper_reviewer where nid=' . $node -> nid . ' and vid=' . $node -> vid .' and submitted = 1');
		foreach ($reviewers as $reviewer) {
			$revobj = user_load($reviewer -> ruid);
			$params = array();
			$params['subject'] = variable_get('email_rev_dec_subject', REV_DEC_APR_REV_SUB);
			$msg = variable_get('email_rev_dec_message', REV_DEC_APR_REV_MSG);
			$msg = str_replace('{{reviewer}}', $revobj -> name, $msg);
			$msg = str_replace('{{title}}', $node -> title, $msg);
			$msg = str_replace('{{url}}', url(drupal_get_path_alias('node/' . $node -> nid), array('absolute' => TRUE)), $msg);
			$msg = replace_email_tokens($node->nid,$msg);
			$params['message'] = $msg;
			drupal_mail('testaction', 'one-one', $revobj -> mail, '', $params);
		}

}
/**
 * This function implements the action to be called after a paper is submitted
 * @param Node object $node
 */
function review_management_paper_submitted($node){
    $uids = get_authors($node);
    watchdog('Rules caled', 'Rules called');
    foreach($uids as $uid){
      $account = user_load($uid);
      if($account->access == 0){
        $params['account'] = $account;
	    $params['title'] = $node->title;
	    $params['tracking_number'] = $node->nid.'-'.$node->vid;
	    $timestamp = REQUEST_TIME;
            $token = get_token($account);
            $params['direct_url'] = url(drupal_get_path_alias('node/' . $node -> nid), array('absolute' => TRUE, 'query' => array('l' => $token)));
//            $params['direct_url'] = url($params['direct_url'], array('query' => array('l' => drupal_get_token($account->mail))));
	drupal_mail('testaction', 'submit', $account -> mail, user_preferred_language($account), $params);
      }else{
        $params['account'] = $account;
	    $params['title'] = $node->title;
	    $params['tracking_number'] = $node->nid.'-'.$node->vid;


            $token = get_token($account);
            $params['direct_url'] = url(drupal_get_path_alias('node/' . $node -> nid), array('absolute' => TRUE, 'query' => array('l' => $token)));
	    drupal_mail('testaction', 'submit_exist', $account -> mail, user_preferred_language($account), $params);
      }
    }
    // notify eics about new submission
    $params['nid'] = $node->nid;
    $params['cc'] = get_eic_emails();
    drupal_mail('testaction', 'eic_submit', get_ea_emails(), user_preferred_language($account), $params);
}

/**
 * This function is a rules action
 * We send reminders to the reviewers and editors for whom action has been pending.
 */
function review_management_automatic_reminder(){
    $curr_time = time();
    $sql = "select nid, vid, ruid, next_reminder from paper_reviewer where accept in(0,1) and submitted <> 1 and next_reminder < ".$curr_time;
    $result = db_query($sql);
    drupal_set_message('Current time stamp'+time());
    foreach ($result as $res){
      if($res->next_reminder == 0 || $res->next_reminder == 1){
        continue;
      }
       //drupal_set_message('Updating user '. $res->ruid);
       $reviewer = user_load($res->ruid);

       $sub = variable_get('email_rev_reminder_subject', REV_REMINDER_SUB);
       $message = variable_get('email_rev_reminder_message', REV_REMINDER_MSG);

       $sub = replace_email_tokens($res->nid, $sub);
       $message = replace_email_tokens($res->nid, $message);
       $message = str_replace('{{reviewer}}', $reviewer->name, $message);
       $token = get_token($reviewer);
       $direct_url = url(drupal_get_path_alias('node/' . $res -> nid), array('absolute'=> TRUE, 'query' => array('l' => $token)));
       $message = str_replace('{{direct_url}}', $direct_url, $message);
       $params['subject'] = $sub;
       $params['message'] = $message;
       drupal_mail('testaction', 'one-one', $reviewer->mail, '', $params);

       update_actions_table(4, $res->nid, $res->vid, '<b>Automatic Reminder Sent<br/>To :</b> ' . $reviewer->mail . '<br/><b>subject :</b> ' . $params['subject'] . '<br/> <b>message: </b>' . $params['message'], 1, 1);
       $next_rem = time() + variable_get('review_management_followup', 7) * 24 * 60 * 60;
       $query = db_update('paper_reviewer') -> fields(array(
                'next_reminder' => $next_rem,

                )) -> condition('nid', $res->nid, '=') -> condition('vid', $res->vid, '=') -> condition('ruid', $res->ruid, '=') -> execute();
    }

    //Automatic reminder for editors.
    $sql = "select nid, vid, ruid, next_reminder from editor_reminder where next_reminder < ".$curr_time;
    $result = db_query($sql);
    foreach($result as $res){
        $editor = user_load($res->ruid);
        $sub = variable_get('email_editor_reminder_subject', EDITOR_REMINDER_SUB);
        $msg = variable_get('email_editor_reminder_message', EDITOR_REMINDER_MSG);
        $msg = replace_email_tokens($res->nid, $msg);
        $sub = replace_email_tokens($res->nid, $sub);
        $params = array();
        $params['message'] = $msg;
        $params['subject'] = $sub;

        drupal_mail('testaction', 'one-one', $editor->mail, '', $params);

       update_actions_table(4, $res->nid, $res->vid, '<b>Automatic Reminder Sent<br/>To :</b> ' . $editor->mail . '<br/><b>subject :</b> ' . $params['subject'] . '<br/> <b>message: </b>' . $params['message'], 1, 1);
       $next_rem = time() + variable_get('review_management_edit_followup', 7) * 24 * 60 * 60;
       //udpate next reminder date;
       $query = db_update('editor_reminder') -> fields(array(
                'next_reminder' => $next_rem,

                )) -> condition('nid', $res->nid, '=') -> condition('vid', $res->vid, '=') -> condition('ruid', $res->ruid, '=') -> execute();

    }
}

/**
 * This function is a rules action
 * We delete all users who are blocked and inactive for more than 30 days
 */
function review_management_delete_blocked_users(){
//TODO fix issue with oAuth
  $query = new EntityFieldQuery;
  $result = $query
  ->entityCondition('entity_type', 'user')
  ->propertyCondition('status', 0)
  ->propertyCondition('access', 0)
  ->execute();

  $count =1;
  $deletednames = '';
  foreach ($result['user'] as $usr){
    $auser = user_load($usr->uid);
    $numDays = abs(REQUEST_TIME - $auser->created)/60/60/24;
    watchdog('Number of days', $numDays);
    if($numDays > 30){

      user_delete($usr->uid);
      $deletednames .= "\n".$auser->name;
    }
    $count++;
    if($count>10)break;
  }
  $params['subject'] = '[Review System SWJ] Blocked and Inactive users deleted'. date('d/M/Y', REQUEST_TIME);
  $params['message'] = "Following users have been deleted "+$deletednames;
  drupal_mail('testaction', 'one-one', get_eic_emails(), '', $params);


}
