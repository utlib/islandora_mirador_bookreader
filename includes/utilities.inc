<?php

/**
 * @file
 * Helper functions.
 */

function get_book_objects_sc_manifest($list_of_pid) {
  global $base_url;

  if (!libraries_load('utlfedoraobject'))
    return array();

  $pids = explode(",", $list_of_pid);

  $user = user_load(1);
  $fo = new UTLFedoraObject($user->name, $user->pass);

  $manifest_url_list = array();

  foreach ($pids as $pid) {
    $child_objs = $fo->get_children($pid);

    foreach ($child_objs as $child_obj) {
      $pid = $child_obj['pid']['value'];

      $child_obj_islandora = $fo->get_object($pid);

      $manifest_datastream_id = Drupal.settings.islandora_mirador_bookreader.manifest_datastream_id;
      if (isset($child_obj_islandora[manifest_datastream_id])) {
	
        $manifest_url = $base_url."/islandora/object/".$pid."/datastream/" . manifest_datastream_id . "/";
        $manifest_url_list[] = array("manifestUri" => $manifest_url);

      }
    }
  }

  return $manifest_url_list;

}
