<?php
/**
 * @file
 * Any hooks/functions used by this modules theme's.
 */

/**
 * Implements hook_preprocess_theme().
 */
function islandora_mirador_bookreader_preprocess_islandora_mirador_bookreader(array &$variables) {

  global $user;

  // get metadata below the viewer
  $object = $variables['object'];
  module_load_include('inc', 'islandora', 'includes/metadata');
  $variables['metadata'] = islandora_retrieve_metadata_markup($object);

  // get the paths
  $library_path = libraries_get_path('mirador');
  $module_path = drupal_get_path('module', 'islandora_mirador_bookreader');

  $view_type = variable_get('islandora_mirador_bookreader_default_page_view');
  
/*
  module_load_include('inc', 'islandora', 'includes/authtokens');
  $pages = array();
  foreach ($variables['pages'] as $page_pid => $info) {
    $token = islandora_get_object_token($page_pid, $dsid, 2);

    // TODO: Slap the widths/heights for pages in here, and make 'em be used in
    // on the JS side...  Probably break out this structure generation into a
    // separate function?
    $pages[] = $info + array(
      'uri' => url("islandora/object/{$page_pid}/datastream/{$dsid}/view", array(
        'absolute' => TRUE,
        'query' => array(
          'token' => $token,
        ),
      )),
    );
  }

  global $base_url;
  $data_array = array(
    'islandoraInternetArchiveBookReader' => array(
      'book' => $object->id,
      'info' => theme('islandora_internet_archive_bookreader_book_info', array('object' => $object)),
      'label' => $object->label,
      'searchUri' => $search_uri,
      'textUri' => url('internet_archive_bookreader_text/PID', array('absolute' => TRUE)),
      'dimensionsUri' => url('internet_archive_bookreader_dimensions/PID', array('absolute' => TRUE)),
      'djatokaUri' => variable_get('islandora_paged_content_djatoka_url', 'http://localhost:8080/adore-djatoka'),
      'imagesFolderUri' => url("$base_url/$library_path/BookReader/images/", array('absolute' => TRUE, 'external' => TRUE)),
      'compression' => variable_get('islandora_internet_archive_bookreader_compression', '4'),
      'pageProgression' => $variables['page_progression'],
      'pages' => $pages,
      'pageCount' => count($pages),
      'overlayOpacity' => variable_get('islandora_internet_archive_bookreader_overlay_opacity', '0.5'),
      'mode' => (int) variable_get('islandora_internet_archive_bookreader_default_page_view', 1),
      'mobilize' => variable_get('islandora_internet_archive_bookreader_mobile_full_screen', FALSE),
      'content_type' => variable_get('islandora_internet_archive_bookreader_content_type', 'book'),
    ),
  );
*/
  drupal_add_js(array('islandora_mirador_bookreader' => array('pid' => $object->id, 'view_type' => $view_type)), array('type' => 'setting'));

  drupal_add_css("$library_path/css/mirador-combined.css");
  drupal_add_css("$module_path/css/mirador_custom.css");

  drupal_add_js("$library_path/mirador.js", array('group' => JS_LIBRARY));
  drupal_add_js("$module_path/js/islandora_mirador.js", array('group' => JS_LIBRARY));
/*
  drupal_add_library('system', 'effects');
  drupal_add_library('system', 'ui.slider');
  drupal_add_library('system', 'ui.draggable');
*/
}

/**
 * Implements theme_hook().
 */
function theme_islandora_mirador_bookreader_book_info(array $variables) {
  module_load_include('inc', 'islandora', 'includes/metadata');

  $object = $variables['object'];

  // As IAV presents the metadata within a Colorbox window request for the
  // metadata in printable form.
  $metadata = islandora_retrieve_metadata_markup($object, TRUE);
  $viewer = variable_get('islandora_metadata_display', 'dublin_core');
  // Let's default back to what IAV had before for a default.
  if ($viewer != 'dublin_core' && $metadata) {
    $content = $metadata;
  }
  else {
    $fields = islandora_internet_archive_bookreader_info_fields($object);
    $convert_to_string = function($o) {
      return implode('<br/>', $o);
    };
    $fields = array_map($convert_to_string, $fields);
    $rows = array_map(NULL, array_keys($fields), array_values($fields));
    dpm($rows);
    $content = theme('table', array(
      'caption' => '',
      'empty' => t('No Information specified.'),
      'attributes' => array(),
      'colgroups' => array(),
      'header' => array(t('Field'), t('Values')),
      'rows' => $rows,
      'sticky' => FALSE));
  }
  return $content;
}

/**
 * Retrieves fields to display in the BookReader's "info" modal dialog box.
 *
 * @param AbstractObject $object
 *   The object to fetch the information from.
 *
 * @return array
 *   Any associative array where the key is the label and the second the
 *   fields value(s).
 */
function islandora_mirador_bookreader_info_fields(AbstractObject $object) {
  if (!(isset($object['MODS']) && islandora_datastream_access(ISLANDORA_VIEW_OBJECTS, $object['MODS']))) {
    return array();
  }
  $fields = array(
    'Title' => '//mods:title',
    'Subtitle' => '//mods:subTitle',
    'Date' => '//mods:dateCreated | //mods:dateIssued',
    'Name' => array('//mods:name', 'mods:namePart'),
    'Abstract' => '//mods:abstract',
    'Identifier' => '//mods:identifier',
    'Physical Description' => array('//mods:physicalDescription', 'mods:extent | mods:form | mods:note[not(@*)] | mods:note[@type="physical"] | mods:note[@type="details"] | mods:scale | mods:coordinates'),
    'Topic' => '/mods:mods/mods:subject/mods:topic',
    'Continent' => '//mods:continent',
    'Country' => '//mods:country',
    'Province' => '//mods:province',
    'County' => '//mods:county',
    'Region/Lot' => '//mods:region',
    'City' => '//mods:city',
    'City Section' => '//mods:citySection',
    'Use and Reproduction' => '//mods:accessCondition[@type="useAndReproduction"]',
    'Restrictions on Access' => '//mods:accessCondition[@type="restrictionOnAccess"]',
    'Physical Location' => '//mods:physicalLocation',
  );
  $xml = simplexml_load_string($object['MODS']->content);
  $xml->registerXPathNamespace('mods', 'http://www.loc.gov/mods/v3');
  $to_string = function($o) {
    return (string) $o;
  };
  // Query each context node with the given xpath.
  $query_each_context = function (array $contexts, $xpath) {
    $query = function(&$context, $key, $xpath) {
      $context->registerXPathNamespace('mods', 'http://www.loc.gov/mods/v3');
      $context = $context->xpath($xpath);
    };
    // Map values to each context node.
    array_walk($contexts, $query, $xpath);
    // Flatten to an array of values.
    return count($contexts) ? call_user_func_array('array_merge', $contexts) : array();
  };
  // Query the given xpath. If the xpath is any array the first value is the
  // xpath for the context node(s) and the second the path to the value fields.
  $query = function(SimpleXMLElement $xml, $xpath) use(&$query_each_context) {
    return is_string($xpath) ? $xml->xpath($xpath) : $query_each_context($xml->xpath($xpath[0]), $xpath[1]);
  };
  foreach ($fields as $label => $xpath) {
    $results = $query($xml, $xpath);
    // Remove empty values.
    $fields[$label] = array_filter(array_map($to_string, $results));
  }
  // Remove empty fields.
  return array_filter($fields);
}
