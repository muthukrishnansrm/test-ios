<?php
/**
 * @file
 * orchid_user_prefs.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function orchid_user_prefs_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'user-user-field_email_activitycomment'.
  $field_instances['user-user-field_email_activitycomment'] = array(
    'bundle' => 'user',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 23,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_email_activitycomment',
    'label' => 'Email notify when user receives wall comment reply.',
    'required' => 0,
    'settings' => array(
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => 23,
    ),
  );

  // Exported field_instance: 'user-user-field_email_badge'.
  $field_instances['user-user-field_email_badge'] = array(
    'bundle' => 'user',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 22,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_email_badge',
    'label' => 'Email notify when user receives a badge.',
    'required' => 0,
    'settings' => array(
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => 22,
    ),
  );

  // Exported field_instance: 'user-user-field_email_badgerequest'.
  $field_instances['user-user-field_email_badgerequest'] = array(
    'bundle' => 'user',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 20,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_email_badgerequest',
    'label' => 'Email notify when a new badge is requested.',
    'required' => 0,
    'settings' => array(
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => 21,
    ),
  );

  // Exported field_instance: 'user-user-field_email_bookmarkcomment'.
  $field_instances['user-user-field_email_bookmarkcomment'] = array(
    'bundle' => 'user',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 21,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_email_bookmarkcomment',
    'label' => 'Email notify when user receives a reply to a bookmarked topic.',
    'required' => 0,
    'settings' => array(
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => 20,
    ),
  );

  // Exported field_instance: 'user-user-field_email_conversationmessage'.
  $field_instances['user-user-field_email_conversationmessage'] = array(
    'bundle' => 'user',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 24,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_email_conversationmessage',
    'label' => 'Email notify when user receives a private message.',
    'required' => 0,
    'settings' => array(
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => 24,
    ),
  );

  // Exported field_instance: 'user-user-field_email_discussioncomment'.
  $field_instances['user-user-field_email_discussioncomment'] = array(
    'bundle' => 'user',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 25,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_email_discussioncomment',
    'label' => 'Email notify when user receives a topic reply.',
    'required' => 0,
    'settings' => array(
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => 19,
    ),
  );

  // Exported field_instance: 'user-user-field_email_mention'.
  $field_instances['user-user-field_email_mention'] = array(
    'bundle' => 'user',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 27,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_email_mention',
    'label' => 'Email notify when user is mentioned.',
    'required' => 0,
    'settings' => array(
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => 25,
    ),
  );

  // Exported field_instance: 'user-user-field_email_wallcomment'.
  $field_instances['user-user-field_email_wallcomment'] = array(
    'bundle' => 'user',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 26,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_email_wallcomment',
    'label' => 'Email notify when user receives a wall post.',
    'required' => 0,
    'settings' => array(
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => 29,
    ),
  );

  // Exported field_instance: 'user-user-field_popup_activitycomment'.
  $field_instances['user-user-field_popup_activitycomment'] = array(
    'bundle' => 'user',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 19,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_popup_activitycomment',
    'label' => 'Popup notify when user receives wall comment reply.',
    'required' => 0,
    'settings' => array(
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => 28,
    ),
  );

  // Exported field_instance: 'user-user-field_popup_badge'.
  $field_instances['user-user-field_popup_badge'] = array(
    'bundle' => 'user',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 17,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_popup_badge',
    'label' => 'Popup notify when user receives a badge.',
    'required' => 0,
    'settings' => array(
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => 27,
    ),
  );

  // Exported field_instance: 'user-user-field_popup_badgerequest'.
  $field_instances['user-user-field_popup_badgerequest'] = array(
    'bundle' => 'user',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 13,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_popup_badgerequest',
    'label' => 'Popup notify when a new badge is requested.',
    'required' => 0,
    'settings' => array(
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => 26,
    ),
  );

  // Exported field_instance: 'user-user-field_popup_bookmarkcomment'.
  $field_instances['user-user-field_popup_bookmarkcomment'] = array(
    'bundle' => 'user',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 12,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_popup_bookmarkcomment',
    'label' => 'Popup notify when user receives a reply to a bookmarked topic.',
    'required' => 0,
    'settings' => array(
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => 30,
    ),
  );

  // Exported field_instance: 'user-user-field_popup_conversationmessage'.
  $field_instances['user-user-field_popup_conversationmessage'] = array(
    'bundle' => 'user',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 14,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_popup_conversationmessage',
    'label' => 'Popup notify when user receives a private message.',
    'required' => 0,
    'settings' => array(
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => 18,
    ),
  );

  // Exported field_instance: 'user-user-field_popup_discussioncomment'.
  $field_instances['user-user-field_popup_discussioncomment'] = array(
    'bundle' => 'user',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 18,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_popup_discussioncomment',
    'label' => 'Popup notify when user receives a topic reply.',
    'required' => 0,
    'settings' => array(
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => 15,
    ),
  );

  // Exported field_instance: 'user-user-field_popup_mention'.
  $field_instances['user-user-field_popup_mention'] = array(
    'bundle' => 'user',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 15,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_popup_mention',
    'label' => 'Popup notify when user is mentioned.',
    'required' => 0,
    'settings' => array(
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => 16,
    ),
  );

  // Exported field_instance: 'user-user-field_popup_wallcomment'.
  $field_instances['user-user-field_popup_wallcomment'] = array(
    'bundle' => 'user',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 16,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_popup_wallcomment',
    'label' => 'Popup notify when user receives a wall post.',
    'required' => 0,
    'settings' => array(
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => 17,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Email notify when a new badge is requested.');
  t('Email notify when user is mentioned.');
  t('Email notify when user receives a badge.');
  t('Email notify when user receives a private message.');
  t('Email notify when user receives a reply to a bookmarked topic.');
  t('Email notify when user receives a topic reply.');
  t('Email notify when user receives a wall post.');
  t('Email notify when user receives wall comment reply.');
  t('Popup notify when a new badge is requested.');
  t('Popup notify when user is mentioned.');
  t('Popup notify when user receives a badge.');
  t('Popup notify when user receives a private message.');
  t('Popup notify when user receives a reply to a bookmarked topic.');
  t('Popup notify when user receives a topic reply.');
  t('Popup notify when user receives a wall post.');
  t('Popup notify when user receives wall comment reply.');

  return $field_instances;
}
