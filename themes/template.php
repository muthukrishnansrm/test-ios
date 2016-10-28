<?php
  function bartik_theme() {
  $items = array();
	
  $items['user_login'] = array(
    'render element' => 'form',
    'path' => drupal_get_path('theme', 'bartik') . '/templates',
    'template' => 'user-login',
    'preprocess functions' => array(
       'bartik_preprocess_user_login'
    ),
  );
  $items['user_register_form'] = array(
    'render element' => 'form',
    'path' => drupal_get_path('theme', 'bartik') . '/templates',
    'template' => 'user-register-form',
    'preprocess functions' => array(
      'bartik_preprocess_user_register_form'
    ),
  );
  $items['user_pass'] = array(
    'render element' => 'form',
    'path' => drupal_get_path('theme', 'bartik') . '/templates',
    'template' => 'user-pass',
    'preprocess functions' => array(
      'bartik_preprocess_user_pass'
    ),
  );
  return $items;
}

?>