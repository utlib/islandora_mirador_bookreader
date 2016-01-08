<?php

/**
 * @file
 * Houses the administration for the islandora_mirador_bookreader module.
 */

/**
 * Creates the administration form for the islandora_mirador_bookreader module.
 *
 * @param array $form
 *   An array representing a Drupal form.
 * @param array $form_state
 *   An array containing the form state.
 *
 * @return array
 *   A renderable array representing the islandora_mirador_bookreader administration form.
 */
function islandora_mirador_bookreader_admin_settings_form($form, &$form_state) {
  $get_default_value = function($name, $default) use($form_state) {
    return isset($form_state['values'][$name]) ? $form_state['values'][$name] : variable_get($name, $default);
  };
  //$solr_enabled = module_exists('islandora_solr');
  $form = array(
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

	'islandora_mirador_bookreader_manifest_list_url' => array(
		'#type' => 'textfield',
		'#title' => t('Manifest list URL'),
		'#description' => t('Enter the link for an JSON array of links to manifests. This array will be used as the "data" attribute when launching Mirador on a Book Object page.'),
		'#default_value' => ''
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

	$scmanifest_json_file_uri = 'public://sc_manifest_list.json';

	if (!file_exists($scmanifest_json_file_uri)) {
		$form['title'] = array(
      		'#markup' => t("There's no JSON file, please click the button below to generate JSON file\n")
    	);
    	$form['islandora_mirador_generate_json'] = array (
	        '#type' => 'submit',
	        '#value' => t('Generate JSON file for Mirador'),
	        '#weight' => 1,
	        '#submit' => array('__generate_mirador_submit__')
		);
	} else {
		$file_url = file_create_url($scmanifest_json_file_uri);
		$form['title'] = array(
      		'#markup' => t("JSON file was created at ".date ("F d Y H:i:s.", filemtime($scmanifest_json_file_uri))."<br> <a href='@url' target='_blank'>View JSON file</a><br>", array('@url' => url($file_url)))
    	);
    	$form['islandora_mirador_generate_json'] = array (
	        '#type' => 'submit',
	        '#value' => t('Re-generate JSON file for Mirador'),
	        '#weight' => 1,
	        '#submit' => array('__generate_mirador_submit__')
		);
	}



	return $form;

}

function __generate_mirador_submit__($form, &$form_state) {

	module_load_include('inc', 'islandora_mirador_bookreader', 'includes/utilities');

	$parent_pids_to_include = variable_get('islandora_mirador_bookreader_parent_pid');

	$json_to_be_written = get_book_objects_sc_manifest($parent_pids_to_include);

	if (file_save_data(json_encode($json_to_be_written), 'public://sc_manifest_list.json', FILE_EXISTS_REPLACE)) {
		drupal_set_message(t('Successfully generated sc_manifest_list.json file'), 'status');
	}
}
