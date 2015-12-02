<?php

/**
 * @file
 * Miscellaneous helper functions.
 */

/**
 * Remap the more general structure of the from islandora_paged_content.
 *
 * IA Bookreader requires a different structure than that which
 * islandora_paged_content provides.
 */
function islandora_internet_archive_bookreader_remap_highlighting_for_bookreader_results($original_results) {
  $results = array(
    'matches' => array(),
  );

  foreach ($original_results as $pid => $info) {
    foreach ($info['snippets'] as $snippet => $bounding_boxes) {
      $match = array(
        'text' => preg_replace('/[^a-zA-Z0-9-\n {}]/', '', $snippet),
        'par' => array(
          array(
            'page' => intval($info['page']['sequence_number']),
            'boxes' => array(),
          ),
        ),
      );

      foreach ($bounding_boxes as $bounding_box) {
        $match['par'][0]['boxes'][] = array(
          'l' => $bounding_box['left'],
          't' => $bounding_box['top'],
          'r' => $bounding_box['right'],
          'b' => $bounding_box['bottom'],
          'page' => $info['page']['sequence_number'],
        );
      }

      $results['matches'][] = $match;
    }
  }

  return $results;
}

function get_book_objects_sc_manifest($list_of_pid) {
  global $base_url;

  $pids = explode(",", $list_of_pid);

  $user = user_load(1);
  $fo = new MyFedoraObject($user->name, $user->pass);

  $manifest_url_list = array();

  foreach ($pids as $pid) {
    $child_objs = $fo->get_children($pid);

    foreach ($child_objs as $child_obj) {
      $pid = $child_obj['pid']['value'];

      $child_obj_islandora = $fo->get_object($pid);

      if (isset($child_obj_islandora['SC'])) {
        $manifest_url = $base_url."/islandora/object/".$pid."/datastream/SC/";
        $manifest_url_list[] = array("manifestUri" => $manifest_url, "location" => "University of Toronto");

      }
    }

  }

  return $manifest_url_list;

}
