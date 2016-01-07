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

  // get metadata below the viewer
  $object = $variables['object'];
  module_load_include('inc', 'islandora', 'includes/metadata');
  module_load_include('inc', 'islandora_mirador_bookreader', 'includes/utilities');
  $variables['metadata'] = islandora_retrieve_metadata_markup($object);

  // get the paths
  $library_path = libraries_get_path('mirador');
  $module_path = drupal_get_path('module', 'islandora_mirador_bookreader');

  $view_type = variable_get('islandora_mirador_bookreader_default_page_view');
  $parent_pids_to_include = variable_get('islandora_mirador_bookreader_parent_pid');

  $uri = 'public://';
  $path= file_create_url($uri);

  drupal_add_js(array('islandora_mirador_bookreader' => array('json_file_directory' => $path, 'base_url' => $base_url, 'pid' => $object->id, 'view_type' => $view_type)), array('type' => 'setting'));

  drupal_add_css("$library_path/css/mirador-combined.css");
  drupal_add_css("$module_path/css/mirador_custom.css");

  drupal_add_js("$library_path/mirador.js", array('group' => JS_LIBRARY));
  drupal_add_js("$module_path/js/islandora_mirador.js", array('group' => JS_LIBRARY));
}
