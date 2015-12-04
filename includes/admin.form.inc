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
function islandora_mirador_bookreader_admin_settings_form($form, &$form_state) {
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
        ),

	'islandora_mirador_bookreader_parent_pid' => array(
		'#type' => 'textfield',
		'#title' => t('Enter the PID of the parent collection containing the book objects that will display in your site\'s Mirador BookReader, i.e. islandora:root.'),
		'#default_value' => $get_default_value('islandora_mirador_bookreader_parent_pid', ''),
		'#description' => t('Please separate each PID with a comma.')
	)
  );
  return system_settings_form($form);
}

function islandora_mirador_bookreader_generate_json_form($form, &$form_state) {

	$form = array (
	'islandora_mirador_generate_json' => array(
        '#type' => 'submit',
        '#value' => t('Generate JSON file for Mirador'),
        '#weight' => 1,
        '#submit' => array('generate_mirador_submit')
	)
	);

	return $form;

}
