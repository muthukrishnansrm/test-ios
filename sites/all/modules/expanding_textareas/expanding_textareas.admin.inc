<?php

function expanding_textareas_admin($form, &$form_state) {

  $form['expanding_textareas_admin_fields'] = array(
    '#type' => 'textarea',
    '#title' => 'Enabled textareas',
    '#description' => t('Add one textarea id per line (not including # sign) or use * to trigger for all textareas.'),
    '#default_value' => variable_get('expanding_textareas_admin_fields', EXPANDING_TEXTAREAS_DEFAULT_ID),
  );

  return system_settings_form($form);
}
