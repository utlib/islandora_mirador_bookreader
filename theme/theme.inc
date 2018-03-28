<?php
/**
 * @file
 * Hooks
 */

/**
 * Implements hook_preprocess_theme().
 */
function islandora_mirador_bookreader_preprocess_islandora_mirador_bookreader(array &$variables) {

  global $user;
  global $base_url;

  module_load_include('inc', 'islandora', 'includes/metadata');
  module_load_include('inc', 'islandora_mirador_bookreader', 'includes/utilities');

  // get metadata below the viewer
  $object = $variables['object']; 
  $pid = $object->id;
  // islandora:pageCModel, islandora:sp_basic_image & islandora:sp_large_image_cmodel does not get the pid. So Manually get it from the url. 
  if (!$pid) $pid = end(explode('/', $_SERVER['REQUEST_URI']));

  if ($object) $variables['metadata'] = islandora_retrieve_metadata_markup($object);

  // get the paths
  $library_path = libraries_get_path('mirador');
  $module_path = drupal_get_path('module', 'islandora_mirador_bookreader');

  // get Drupal configuration values
  $view_type = variable_get('islandora_mirador_bookreader_default_page_view');
  $manifest_list_url = variable_get('islandora_mirador_bookreader_manifest_list_url');
  // $manifest_datastream_id = variable_get('islandora_mirador_bookreader_manifest_datastream_id');
  $iiif_base_url = variable_get('islandora_mirador_bookreader_iiif_base_url');

  // Verify if the manifest_url is valid
	// Set the manifest_url to the IIIF server's manifest object
	$manifest_url = "$iiif_base_url/$pid/manifest";
	if (!checkUrl($manifest_url)) {
		// Re-check by using the new 'IIIF' datastream url
    $manifest_url = "$base_url/islandora/object/$pid/datastream/IIIF/view";
    if (!checkUrl($manifest_url)) {
		  // Re-check by using the legacy 'SC' datastream url
      $manifest_url = "$base_url/islandora/object/$pid/datastream/SC/view";
      if (!checkUrl($manifest_url)) {
        // Finally, Use a dummy as a placeholder
        $manifest_url = "https://iiif.library.utoronto.ca/presentation/v2/collections";
      }
    }
	}

  drupal_add_js(array(
    'islandora_mirador_bookreader' => array(
      'json_file_directory' => $path, 
      'view_type' => $view_type, 
      'manifest_list_url' => $manifest_list_url, 
      'manifest_url' => $manifest_url,
    )), 
    array('type' => 'setting')
  );

  drupal_add_css("$library_path/css/mirador-combined.css");
  drupal_add_css("$module_path/css/mirador_custom.css");

  drupal_add_js("$library_path/mirador.js", array('group' => JS_LIBRARY, 'scope' => 'footer'));
  drupal_add_js("$module_path/js/islandora_mirador.js", array('group' => JS_LIBRARY, 'scope' => 'footer'));
}


function checkURL($url) {
  $headers = @get_headers($url);
  return (!(strpos($headers[0], '200'))===false);
}