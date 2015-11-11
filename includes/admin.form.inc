<?php

/**
 * @file
 * Handles the display/submission of the admin settings form for this module.
 */

/**
 * Defines the admin settings form.
 *
 * @param array $form
 *   The Drupal form definition.
 * @param array $form_state
 *   The Drupal form state.
 *
 * @return array
 *   The Drupal form definition.
 */
function islandora_mirador_bookreader_admin_settings_form(array $form, array &$form_state) {
  $get_default_value = function($name, $default) use($form_state) {
    return isset($form_state['values'][$name]) ? $form_state['values'][$name] : variable_get($name, $default);
  };
  $solr_enabled = module_exists('islandora_solr');
  $form = array(
	'islandora_mirador_bookreader_iiif_server' => array(
		'#type' => 'textfield',
		'#title' => t('IIIF server URL'),
		'#description' => t('URL of the server that serves IIIF compliant images'),
		'#default_value' => variable_get('islandora_mirador_bookreader_iiif_server')
	),
	'islandora_mirador_bookreader_manifest_ds' => array(
                '#type' => 'textfield',
                '#title' => t('Manifest Datastream'),
                '#description' => t('Name of the datastream of the Fedora object that is the image'),
		'#default_value' => variable_get('islandora_mirador_bookreader_manifest_ds')
        )
  );
  return system_settings_form($form);
}
