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
/*	'islandora_mirador_bookreader_iiif_server' => array(
		'#type' => 'textfield',
		'#title' => t('IIIF server URL'),
		'#description' => t('URL of the server that serves IIIF compliant images'),
		'#default_value' => $get_default_value('islandora_mirador_bookreader_iiif_server')
	),
*/
	'islandora_mirador_bookreader_default_page_view' => array(
		'#type' => 'select',
	      '#title' => t('Default page view'),
	      '#description' => t('Mirador viewType. https://github.com/IIIF/mirador/blob/11cc39379e7346b1301c3163a5f22c8fe396900f/js/src/settings.js#L41'),
	      '#default_value' => $get_default_value('islandora_mirador_bookreader_default_page_view', 1),
	      '#options' => array(
		1 => 'Image',
		2 => 'Book',
		3 => 'Thumbnails',
	      )
        )
  );
  return system_settings_form($form);
}
