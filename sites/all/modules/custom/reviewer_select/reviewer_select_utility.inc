<?php

/**
 * Returns impression options dropdown with values from 0-100
 */
function get_impression_options(){
  $options = array();
  $options['Excellent'] = 'Excellent';
  $options['Good'] = 'Good';
  $options['Average'] = 'Average';
  $options['Weak'] = 'Weak';
  $options['Bad'] = 'Bad';
  $options['Don\'t Know'] = 'Don\'t Know';
  return $options;
}
/**
 * Returns true if the systems is configured to be a closed review system
 */
function is_closed_system(){
  if(variable_get('review_management_closed_review') == 0){
    return TRUE;
  }

  return FALSE;
}


/**
 * Checker function to check if the decision has been approved.
 */
function is_approved($node){
  if(isset($node->field_approval['und']) && $node->field_approval['und'][0]['value'] != 'approved'){
    return TRUE;
  }
  return FALSE;
}

/**
 * returns the value of approval
 */
function get_approval_value($node){
  if(isset($node->field_approval['und'])){
    return $node->field_approval['und'][0]['value'];
  }else return '_none';
}

/**
 * Returns name of the authors for node preview.
 * See: add_author_form for reference
 */
function get_authors_preview($form, &$form_state, $node){
  $form_author['authors'] = array(
    '#title' => 'Authors',
    '#type' => 'container',
    '#tree' => TRUE,
    '#markup' => '<b>Authors: </b><hr/>',
  );
  $form_author['authors']['title'] = array(
            '#title' => 'Authors',
            '#type' => 'item',
        );
  $output = '';
  foreach ($node->authors as $author){
    if($output !=''){
      $output .= ', ' . $author['name']. ' ['. $author['email'] . ']';
    }else{
      $output =  $author['name']. ' ['. $author['email'] . ']';
    }
  }

  $form_author['authors']['title'] = array(
            '#title' => 'Authors',
            '#type' => 'item',
            '#markup' => $output,
        );


  return $form_author;
}

/**
 * Called from hook_node_submit
 * We have to set the author references from our custom form fields to field_authors_ref.
 */

function set_authors_to_paper(&$node, $authors){
  $checkExisting = TRUE;
  $node_authors = array();

  if(is_null($node->nid) ){
    $checkExisting = FALSE;
  }


  foreach($authors as $author){
    //try to load the email of the author
    $emailString = $author['email'];
    $fullName = $author['name'];

    $account = user_load_by_mail($emailString);

    if (!$account)
    {
      $trialName = $fullName;
      $c = 1;
      while(user_load_by_name($trialName)){
            $trialName = $fullName . $c;
            $c++;
      }
      $account = createUser($emailString, $trialName , 1, $node);
        if($checkExisting){
          $params['account'] = $account;
    	    $params['title'] = $node->title;
    	    $params['tracking_number'] = $node->nid.'-'.$node->vid;
    	    $token = get_token($account);
            $params['direct_url'] = url(drupal_get_path_alias('node/' . $node -> nid), array('absolute' => TRUE, 'query' => array('l' => $token)));
          drupal_mail('testaction', 'submit', $account -> mail, user_preferred_language($account), $params);
        }
     }
     else if($checkExisting && !is_author($account, $node)){
      $params['account'] = $account;
	  $params['title'] = $node->title;
	  $params['tracking_number'] = $node->nid.'-'.$node->vid;
      $token = get_token($account);
      $params['direct_url'] = url(drupal_get_path_alias('node/' . $node -> nid), array('absolute' => TRUE, 'query' => array('l' => $token)));
	  drupal_mail('testaction', 'submit_exist', $account -> mail, user_preferred_language($account), $params);

     }
     $node_authors[] = array('uid' => $account->uid);
    //$node->field_authors_ref['und'][] = array('uid' => $account->uid);
  }

   $node->field_authors_ref['und'] = array();
   $node->field_authors_ref['und'] = $node_authors;

}

/**
 * Checker function to identify if the $account belongs to the author of node.
 */
function is_author($account, $node){
    $uids = get_authors($node);

    foreach($uids as $uid){
      if($account->uid === $uid){
        return TRUE;
      }
    }
    return FALSE;
}
/**
 * Checker function to identify reviewer
 */
function is_reviewer($account, $node){
  $r = db_query("Select count(ruid) from paper_reviewer  where nid =".$node->nid." and vid=".$node->vid." and ruid =" . $account -> uid . " and accept in (0,1)") -> fetchField();
  if($r == 1){
    return TRUE;
  }
  return FALSE;
}
/**
 * Returns a comma separated list of author names.
 */
function get_author_names($node){
  $uids = get_authors($node);
  $concat_name = '';
  foreach($uids as $uid){
    $author = user_load($uid);
    if($concat_name != ''){
      $concat_name .= ', '. $author->name;
    }else{
      $concat_name .= $author->name;
    }

  }
  return $concat_name;
}

/**
 * get author emails
 */
function get_author_emails($node){
  $uids = get_authors($node);
  $concat_name = '';
  foreach($uids as $x => $uid){
    $author = user_load($uid);
    if($concat_name != ''){
      $concat_name .= ', '. $author->mail;
    }else{
      $concat_name .= $author->mail;
    }

  }

  return $concat_name;
}

/**
 * This function returns array of uids of authors for a given paper.
 * @param $node: The paper.
 */
function get_authors($node){
  $uids = array();
  foreach ($node->field_authors_ref['und'] as $usr){
    if($usr['uid'] != ''){
      $uids[] = $usr['uid'];
    }

  }

 return $uids;
}

/**
 * this function returns an array of reviewers for a given paper (node)
 */
function get_reviewers($node){
  $sql = "select ruid, name, mail, accept, added, submitted  from paper_reviewer, users where nid = "
          .$node->nid ." and vid = ".$node->vid . " and users.uid = ruid";
  /* $sql = "select ruid, name, mail, accept, added, submitted, next_reminder, rem_frequency, last_reminder, sen_reminder, reminders_sent  from paper_reviewer, users where nid = "
          .$node->nid ." and vid = ".$node->vid . " and users.uid = ruid"; */
  $results = db_query($sql);

  $reviewers = array();
  $count = 1;
  foreach ($results as $res){
    $reviewers[$count]['uid'] = $res -> ruid;
    $reviewers[$count]['mail'] = $res -> mail;
    $reviewers[$count]['name'] = $res -> name;
    $reviewers[$count]['added'] = $res -> added;
    $reviewers[$count]['accept'] = $res -> accept;
    $reviewers[$count]['submitted'] = $res -> submitted;
    /* $reviewers[$count]['rem_frequency'] = $res -> rem_frequency;
    $reviewers[$count]['last_reminder'] = $res -> last_reminder;
    $reviewers[$count]['sen_reminder'] = $res -> sen_reminder;
    $reviewers[$count]['reminders_sent'] = $res -> reminders_sent;
    $reviewers[$count]['next_reminder'] = $res -> next_reminder; */
    $count++;
  }

  return $reviewers;
}

/**
 * Returns the uid of the resposible editor
 * argument: $node the $node of type 'submit_paper'
 */
function get_responsible_editor($node){
  $euid = '';
  if (isset($node -> field_editor['und'][0])) {
    $euid = $node -> field_editor['und'][0]['uid'];

  } else if (isset($node -> field_editor[0])) {
    $euid = $node -> field_editor[0]['uid'];
  }
  return $euid;
}

/**
 * Returns TRUE if the logged in user has access to camera ready files
 * TRUE if the user is an author, editor of the paper or is the eic.
 */
function showCameraReady($node){
  global $user;
  if($node->field_decision['und'][0]['value'] != 'Accept'){

    return false;
  }
  if(is_responsible_editor($node) || is_eic_user()){

	return true;
  }
  if(!isset($user->mail)){
    return false;
  }
  $results = array();
  $uids = get_authors($node);
  foreach ($uids as $uid){
    if($user->uid == $uid){
      return true;
    }
  }
  return false;
}


function showImmediatePublication($node){
  global $user;
  if($node->field_decision['und'][0]['value'] != 'Accept'){

    return false;
  }
  if(is_responsible_editor($node) || is_eic_user()){

	return true;
  }
  if(!isset($user->mail)){
    return false;
  }
  $results = array();
  $uids = get_authors($node);
  foreach ($uids as $uid){
    if($user->uid == $uid){
      return true;
    }
  }
  return false;
}
/** Actions drop down menu on the paper page
 *
 */
function getDropDownMenu($nid, $hide){
  global $base_url;
  ctools_include('ajax');
  ctools_include('modal');

  ctools_modal_add_js();
  global $user;
  $isEIC = is_eic_user();


  // Create our own javascript that will be used to theme a modal.
  $sample_style = array(
      'ctools-sample-style' => array(
          'modalSize' => array(
              'type' => 'fixed',
              'width' => 500,
              'height' => 350,
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

  ctools_add_js('ctools-ajax-sample', 'ctools_ajax_sample');
  ctools_add_css('ctools-ajax-sample', 'ctools_ajax_sample');

  // Create a list of clickable links.
  $links = array();
  //Find if reviewers are available for this paper
  $numReviewers = db_query("select count(ruid) from {paper_reviewer} p,{users} u where nid = $nid and p.ruid = u.uid and u.uid not in (select uid from paper_review where nid = $nid) and accept in (0,1)")->fetchField();



  $links[] = ctools_modal_text_button(t('Invite Reviewer'), $base_url.'/swj/nojs/reviewer/'.$nid, t('Add a Reviewer'),  'ctools-modal-ctools-sample-style');
  if($numReviewers > 0){
//    $links[] = ctools_modal_text_button(t('Add Review'), $base_url.'/swj/nojs/review/'.$nid, t('Add Review'),  'ctools-modal-ctools-sample-style');
  }
  //$links[] = ctools_modal_text_button(t('Invite a Reviewer (Not Present in the System)'), $base_url.'/swj/nojs/invite/'.$nid, t('Invite a Reviewer not present in the system'),  'ctools-modal-ctools-sample-style');
  /* if($isEIC){
    $links[] = ctools_modal_text_button('Edit Paper Fields', $base_url.'/swj/nojs/edit_content_modal/'.$nid, t('Edit Paper Fields'),  'ctools-modal-ctools-sample-style');
  } */
  if(!$hide || $isEIC){
    $text_label = "Submit Decision Letter";
    if($hide){
      $text_label ="Approve Decision";
    }
    $links[] = ctools_modal_text_button($text_label, $base_url.'/swj/nojs/decision/'.$nid, t('Submit Decision Letter'),  'ctools-modal-ctools-sample-style');
  }
  $links[] = ctools_modal_text_button(t('Email editors in chief'), $base_url.'/swj/nojs/email_eic/'.$nid, t('Email editors in chief'),  'ctools-modal-ctools-sample-style');
  $output = '<div><h2><b>' . t('Actions:').'</b></h2>'. '<h4> (Invite Reviewer, Add Review, Submit Decision) </h4>' ;
  $output .= reviewer_actions_dropdown(array('title' => t('Choose an Action'), 'links' => $links));//theme('ctools_dropdown', array('title' => t('Choose an Action'), 'links' => $links));
  $output .= "</div>";
  return array('markup' => array('#markup' => $output));
}

//hacking theme function
function reviewer_actions_dropdown($vars) {

  // Provide a unique identifier for every dropdown on the page.
  static $id = 0;
  $id++;

  $class = 'ctools-dropdown-no-js ctools-dropdown'; //. ($vars['class'] ? (' ' . $vars['class']) : '');

  ctools_add_js('dropdown');
  ctools_add_css('dropdown');

  $output = '';

  $output .= '<div class="' . $class . '" id="ctools-dropdown-' . $id . '">';
  $output .= '<div class="ctools-dropdown-link-wrapper">';
  // if ($vars['image']) {
  // $output .= '<a href="#" class="ctools-dropdown-link ctools-dropdown-image-link">' . $vars['title'] . '</a>';
  //}
  //else {
  $output .= '<a href="#" class="ctools-dropdown-link ctools-dropdown-text-link">' . check_plain($vars['title']) . '</a>';
  //}

  $output .= '</div>'; // wrapper
  $output .= '<div class="ctools-dropdown-container-wrapper">';
  $output .= '<div class="ctools-dropdown-container">';
  $output .= theme('item_list', array('items' => $vars['links'], 'title' => t('Actions')));//theme_links(array('links' => $vars['links'], 'attributes' => array(), 'heading' => ''));
  $output .= '</div>'; // container
  $output .= '</div>'; // container wrapper
  $output .= '</div>'; // dropdown
  return $output;
}

/**
 * Returns submitted reviews inside a formset
 *
*/
function get_submitted_reviews($form, &$form_state, $node){
        global $user;
        //If system is closed and user is not logged in then don't show reviews
        if(is_closed_system() && user_is_anonymous()){
          return array();
        }

        //If decision is not approved don't show reviews to non-editor and non-eic users
        if(!is_responsible_editor($node) && !is_eic_user()){
          if(!isset($node->field_approval['und']) || (isset($node->field_approval['und']) && $node->field_approval['und'][0]['value'] != 'approved')){
            return array();
          }
        }
        if(isset($node->field_hidereviews['und']) && $node->field_hidereviews['und'][0]['value'] == 1){

          if(!in_array($user->uid, get_authors($node)) && !is_responsible_editor($node) && ! is_eic_user()){
            $form = array(
                '#type' => 'fieldset',
                '#title' => 'Reviews',
                '#description' => 'Reviews have been hidden by the admin.',
                );

            return $form;
          }
        }
        global $base_url;
                $sql = 'select uid, created, anon from paper_review where nid = '.$node->nid.' and vid = '.$node->vid;
                $results = db_query($sql);
                $local_count = 1;
                $outputStr = '';
			foreach ($results as $result) {
			  $reviewer = user_load($result->uid);
			  $outputStr = get_review_html($node, $reviewer);
			  if(is_responsible_editor($node) || is_eic_user()){
			    $outputStr .= '<a href="'.$base_url .'/node/swj/edit_review/' . $node -> nid . '/' . $node -> vid . '/' . $result -> uid . '">Edit </a><br/>';
			  }

			  $byvalue = '<strong> By ' . $reviewer -> name . ' submitted on ' . date('d/M/Y', $result -> created) . '</strong>';
			  if (isset($result -> anon) && $result -> anon == 1 && !(is_responsible_editor($node) || is_eic_user())) {
			    $byvalue = '<strong><em>Anonymous</em> submitted on ' . date('d/M/Y', $result -> created) . '</strong>';
			  }
			  if(!(is_responsible_editor($node) || is_eic_user()) && is_closed_system()){
			    $byvalue = '<strong><em>Anonymous</em> submitted on ' . date('d/M/Y', $result -> created) . '</strong>';
			  }
			  $form['fset' . $local_count] = array(
			      '#title' => 'Review #' . $local_count .' '.$byvalue,
			      '#type' => 'fieldset',
			      '#description' => 'Review Details<br/><hr/>',
			      '#collapsible' => TRUE,
			      '#collapsed' => TRUE,

			  );
			  $form['fset' . $local_count]['nd'] = array(
			      '#title' => t('Reviews'),
			      '#type' => 'text',
			      '#value' => 'dummy',
			      '#suffix' => $outputStr,

			  );
			  $local_count++;
			}
			if ($outputStr == '') {
			  $outputStr = 'No reviews submitted for this paper.<br/>';
			}else{
			  //$outputStr = dpm($form);//theme('ctools_collapsible', array('handle' => '<b>Click to Expand/Collapse</b>', 'content' => render($form), 'collapsed' => TRUE));
			}

        return $form;
}

/**
 * This function returns a paginated display of actions history table.
 * from the table swj_actions.
 * The action history table displayed on the node view page.
 */
function get_history($node, $currentPage = 1) {
  //include js file required for implementing pagination.
  //Note for some reason drupal table pager does not work. We implement our own.
  drupal_add_js(drupal_get_path('module', 'reviewer_select') . '/history_table.js');
  $pageLimit = 5;

  $query = db_select('swj_actions', 'p');
  $query -> condition('p.nid', $node -> nid, '=');
  $query -> condition('p.vid', $node -> vid, '=');
  $user_alias = $query -> join('users', 'u', '%alias.uid = p.action_by');
  $query -> fields('p', array(
      'action_by',
      'adate',
      'type',
      'description'
  ));
  $query -> fields('u', array('name'));
  $query = $query -> extend('TableSort');
  $query -> orderBy('adate', 'DESC');
  $results = $query -> execute();

  $header = array(
      'date' => array('data' => t('Action Date')),
      'desc' => array('data' => t('Description')),
      'user' => array('data' => t('Action By'))
  );
  $rows = array();
  $count = 0;
  foreach ($results as $result) {
    // only add results within the paged range
    if ($count >= ($currentPage - 1) * $pageLimit && $count < $currentPage * $pageLimit) {

      $description = str_replace(',', ', ',$result->description);
      $rows[] = array (
          'date' => date("d/M/Y H:i", $result->adate),
          'desc' => array(
              'class' => ($result->type == 4 ? 'email' : 'other'),
              'data' => '<p>'.$description.'</p>',
          ),
          'user' => $result -> name,
      );
    }
    $count++;
  }

  // create pager links
  $numPages = ceil($results -> rowCount() / $pageLimit);
  $pages = '<div class="item-list"><ul class="pager">';
  if ($numPages > 1 && $currentPage != 1)
    $pages .= '<li class="pager-previous"><a href="#previous" title="Go to previous page">‹ previous</a></li>';

  for ($i = 1; $i <= $numPages; $i++) {
    if ($i == $currentPage) {
      $pages .= '<li class="pager-current">' . $i . '</li>';
    } else {
      $pages .= '<li class="pager-item"><a href="#' . $i . '" title="Go to page ' . $i . '">' . $i . '</li>';
    }
  }
  if ($numPages > 1 && $currentPage != $numPages)
    $pages .= '<li class="pager-next"><a href="#next" title="Go to next page">next ›</a></li>';
  $pages .= '</ul></div>';

  if ($numPages == 1) {
    $pages = "";
  }
  $table = array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $rows,
      '#attributes' => array(),
  );
  $callback = array(
      '#type' => 'hidden',
      '#attributes' => array('name' => 'history_table_callback'),
      '#value' => url('swj/reviewselect/history/pager', array('absolute' => TRUE))
  );
  $nd = array(
      '#type' => 'hidden',
      '#attributes' => array('name' => 'nd'),
      '#value' => $node -> nid
  );
  $vd = array(
      '#type' => 'hidden',
      '#attributes' => array('name' => 'vd'),
      '#value' => $node -> vid
  );
  $pager = array('#markup' => $pages);
  $form1= array('#type' => 'fieldset', '#title' => 'Action History','#collapsible'=> true,'#attributes'=>array('id'=>'action_fieldset'));
  $form1['history'] = $table;
  $form1['history']['#suffix'] = render($pager);
  //$build['history_table'] = array('#markup' => '<div id="history_table"><span id="action_history"><b>Action History:</b><br/><br/></span><span id="actions_table_table">' . render($callback) . render($nd) . render($vd) . render($form1['history'])  . '</span><hr/></div>',);
  $build['history_table'] = array('#markup' => '<div id="history_table"><span id="action_history"><br/></span><span id="actions_table_table">' . render($callback) . render($nd) . render($vd) . render($form1['history'])  . '</span><hr/></div>',);

  return $build;
}

function _history_pager_callback() {
  if (!isset($_GET['nid']) || !isset($_GET['vid']) || !isset($_GET['page'])) {
    return '';
  }

  $node = node_load($_GET['nid'], $_GET['vid']);
  return ajax_deliver(render(get_history($node, $_GET['page'])));
}


function _history_delete_callback() {

  return ajax_deliver(render(get_history($node, $_GET['page'])));
}

function set_out_for_review($nid){
  $node_update = node_load($nid);
  $tids = array_keys(taxonomy_get_term_by_name('Out For Review'));
        //Set flag out for review

  if(!isset($node_update->field_flag['und']) ||  !($node_update->field_flag['und'][0]['tid'] == $tids[0])){
          $node_update->field_flag['und'][0]['tid'] = $tids[0];
          node_save($node_update);
  }
 drupal_set_message('Paper has been marked as out for review');
 drupal_goto(url(drupal_get_path_alias('node/' . $node_update -> nid), array('absolute' => TRUE)));
}

/**
* generates token for login
*/

function get_token($account){
    $sql = "select token from login_data where uid =".$account->uid;
    $result = db_query($sql);

    foreach($result as $res){
      return $res->token;
    }
    $token = drupal_get_token($account->mail);
    db_insert('login_data') -> fields(array(
          'uid' => $account -> uid,
          'token' => $token,
          'created' => REQUEST_TIME,
      )) -> execute();

    return $token;
}

/**
 * boolean value true if the logged in user is an editorial assistant
 */
function is_editorial_assitant(){
  global $user;

  $r = db_query("Select count(u.uid) from users_roles u INNER JOIN role r on u.rid = r.rid where u.uid =" . $user -> uid . " and r.name='" . EA_ROLE . "'") -> fetchField();
  if ($r == 1) {
    return TRUE;
  }
  return FALSE;
}

/**
 * Returns emails of the editorial assistant
*/
function get_ea_emails(){
   $emails = '';
   $ea = EA_ROLE;
                        $result = db_query("Select distinct u.uid from users_roles u INNER JOIN role r on u.rid = r.rid where r.name='" . $ea . "'");
                        $first = true;
                        foreach ($result as $row) {
                        if($emails == ''){
				        	$emails = user_load($row -> uid)->mail;

				        }else{
                                $emails .= ','.user_load($row -> uid)->mail;
				        }
                        }

   return $emails;
}


